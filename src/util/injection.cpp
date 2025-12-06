#include "injection.hpp"

namespace loader
{

	void injection::auto_inject()
	{
		std::thread([&] {
			while (true || active) 
			{
				static bool injected;
				if (!injected)
				{
					auto i = g.auto_inject;
					if (i.content_warning || i.gtav || i.lethal_company || i.phasmophobia || i.repo)
						inject(); //different games are already handled here
					injected = true;
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}
			}).detach();
	}

	void injection::inject()
	{
		g_logger.log("called inject");
		switch (g_gui.game)
		{
			case LETHAL_COMPANY:
			{
				g_logger.log("Injecting LethalMenu");
				/*I have to do this here because i cant make releases for them lol*/ if (!std::filesystem::is_directory(std::filesystem::current_path() / "Menus" / "LethalMenu")) std::filesystem::create_directory(std::filesystem::current_path() / "Menus" / "LethalMenu");
				g_cpr_client.download("https://icyrelic.com/release/lethalmenu/LethalMenu.dll", (fs::current_path() / "Menus" / "LethalMenu" / "lethalmenu.dll"));
				mono_inject(g_gui.tab);
			}break;
			case CONTENT_WARNING:
			{
				g_logger.log("Injecting Spooksuite");
				util::download_menu("IcyRelic", "SpookSuite");
				mono_inject(g_gui.tab);
			}break;
			case REPO:
			{
				g_logger.log("Injecting Unk");
				util::download_menu("TheGreenBandit", "Unk");
				mono_inject(g_gui.tab);
			}break;
			case GTAV:
			{
				g_logger.log("Injecting Blade");
				util::download_menu("TheGreenBandit", "Blade");
				inject_dll(g_gui.game);
			}break;
			//case PHASMOPHOBIA:
			//{
			//	util::download_menu("TheGreenBandit", "PhasmoMenu");
			//	inject_dll(g_gui.tab);
			//}break;
			default: break;
		}
	}

	void injection::inject_dll(egame game, std::string_view npath, std::string_view nwindow) {
		std::thread([=] 
			{
				fs::path path = npath;
				if (npath == "")
				{
					if (game == GTAV)
						g.gtav.alternate_path != "" ? path = g.gtav.alternate_path : path = fs::current_path() / "Blade" / "Blade.dll";
				}
				auto window = nwindow.data();
				if (nwindow == "")
				{
					if (game == GTAV)
						window = "Grand Theft Auto V";
				}

				//std::this_thread::sleep_for(std::chrono::milliseconds(globals.injection_delay)); implement me?
				HWND hwnd = FindWindowA(NULL, window);
				DWORD pid; GetWindowThreadProcessId(hwnd, &pid);
				HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
				LPVOID pDllPath = VirtualAllocEx(handle, 0, strlen(path.string().c_str()) + 1, MEM_COMMIT, PAGE_READWRITE);
				WriteProcessMemory(handle, pDllPath, (LPVOID)path.string().c_str(), strlen(path.string().c_str()) + 1, 0);
				HANDLE hLoadThread = CreateRemoteThread(handle, 0, 0, (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"), "LoadLibraryA"), pDllPath, 0, 0);
				WaitForSingleObject(hLoadThread, INFINITE);
				VirtualFreeEx(handle, pDllPath, strlen(path.string().c_str()) + 1, MEM_RELEASE);

				if (g.auto_close)
					active = false;
			}

		).detach();
	};

	void injection::mono_inject(etab tab)//todo remove legacy etab usage
	{
		fs::path path;
		const char* window = "";
		const char* _namespace = "";
		auto _class = "Loader", _method = "Init";//

		switch (g_gui.game)
		{
			case LETHAL_COMPANY:
			{
				path = "Menus\\LethalMenu\\LethalMenu.dll";
				window = "Lethal Company";
				_namespace = "LethalMenu";
			}break;
			case CONTENT_WARNING:
			{
				path = "Menus\\SpookSuite\\SpookSuite.dll";
				window = "Content Warning";
				_namespace = "SpookSuite";
			}break;
			case REPO:
			{
				path = "Menus\\Unk\\Unk.dll";
				window = "REPO";
				_namespace = "Unk";
			}break;
			default: { g_logger.log("Game is not valid, returning"); return; }
		}
		g_logger.log(window);
		g_logger.log(path.string());
		g_logger.log(_namespace);
		//smi.exe inject -p "Content Warning" -a "Menus/SpookSuite/spooksuite.dll" -n "SpookSuite" -c "Loader" -m "Init"
		HWND hwnd = FindWindowA(NULL, window);
		//if (hwnd == nullptr) //this is always true???????????????????
		//	return g_logger.log("failed to find game window, cancelling injection.");

		DWORD pid; GetWindowThreadProcessId(hwnd, &pid);
		std::string command = std::format(
			"smi.exe inject -p \"{}\" -a \"{}\" -n \"{}\" -c \"{}\" -m \"{}\"",
			window, path.string(), _namespace, _class, _method
		);
		g_logger.log(command);
		system(command.c_str()); 
		if (g.auto_close)
			active = false;
	}
}