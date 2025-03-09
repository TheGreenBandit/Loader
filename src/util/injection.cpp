#include "injection.hpp"

namespace loader
{

	void injection::auto_inject()
	{
		std::thread([&] {
			while (active) {
				static bool injected;
				if (!injected)
				{
					auto i = g.auto_inject;
					if (i.content_warning || i.gtav || i.lethal_company || i.phasmophobia)
						inject(); //different games are already handled here
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}
			}).detach();
	}

	void injection::inject()
	{
		g_logger.log("called inject");
		if (g_gui.tab == LETHAL_COMPANY || g_gui.tab == CONTENT_WARNING)
		{
			g_logger.log("using mono inject");
			mono_inject(g_gui.tab);
			active = false;
		}
		else if (g_gui.tab == GTAV || g_gui.tab == PHASMOPHOBIA)
		{
			inject_dll(g_gui.tab);
			active = false;
		}
	}

	void injection::inject_dll(etab tab, std::string_view npath, std::string_view nwindow) {
		std::thread([=] {
			fs::path path = npath;
			if (npath == "")
			{
				if (tab == GTAV)
					g.gtav.alternate_path != "" ? path = g.gtav.alternate_path : path = fs::current_path() / "Blade" / "Blade.dll";
				else
					path = fs::current_path() / "Phasmenu" / "Phasmenu.dll";
			}
			auto window = nwindow.data();
			if (nwindow == "")
			{
				if (tab == GTAV)
					window = "Grand Theft Auto V";
				else
					window = "Phasmophobia";
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
			}).detach();
	};

	void injection::mono_inject(etab tab)
	{
		fs::path path = (tab == LETHAL_COMPANY) ? "Menus\\LethalMenu\\LethalMenu.dll" : "Menus\\SpookSuite\\spooksuite.dll";
		auto window = (tab == LETHAL_COMPANY) ? "Lethal Company" : "Content Warning",
			_namespace = (tab == LETHAL_COMPANY) ? "LethalMenu" : "SpookSuite",
			_class = "Loader", _method = "Init";
		//smi.exe inject -p "Content Warning" -a "Menus/SpookSuite/spooksuite.dll" -n "SpookSuite" -c "Loader" -m "Init"
		HWND hwnd = FindWindowA(NULL, window);
		DWORD pid; GetWindowThreadProcessId(hwnd, &pid);
		std::string command = std::format(
			"smi.exe inject -p \"{}\" -a \"{}\" -n \"{}\" -c \"{}\" -m \"{}\"",
			window, path.string(), _namespace, _class, _method
		);
		system(command.c_str()); 
		return;
		//process.Attach(pid);

		//auto barrier = process.core().native()->GetWow64Barrier().type;
		//if (barrier == (blackbone::wow_64_64 || blackbone::wow_32_32))
		//	return util::log("Cannot call function through wow_64");
		//module_data = process.modules().GetModule(L"mono.dll");
		//process.remote().CreateRPCEnvironment(blackbone::Worker_CreateNew);
		//thread = process.remote().getWorker();
		//auto data = util::read_all_bytes(path.string());
		//intptr_t domain = get_root_domain();
		//thread_attatch(domain);
		//security_set_mode(0);
		//intptr_t assembly = assembly_load_from_full(image_open_from_data_full(data));
		//intptr_t class_id = get_class_from_name(assembly_get_image(assembly), _namespace, _class);
		//unlink_assembly(domain); //test
		//runtime_invoke_method(get_method_from_name(class_id, _method));
	}
	//todo get all this actually working
	intptr_t injection::get_root_domain()
	{
		//using mono_get_root_domain = intptr_t(__cdecl*)();
		//auto mono_get_root_export = process.modules().GetExport(module_data, "mono_get_root_domain");
		//if (!mono_get_root_export)
		//	throw std::runtime_error("Could not find mono_get_root_domain export.");
		//blackbone::RemoteFunction<mono_get_root_domain> mono_get_root_function{ process, mono_get_root_export->procAddress };
		//blackbone::RemoteFunction<mono_get_root_domain>::CallArguments args;
		//auto result = mono_get_root_function.Call(args, thread);
		//if (!result.success())
		//	throw std::runtime_error("Could not call mono_get_root_domain");
		//return result.result();
	}

	intptr_t injection::get_domain()
	{
		/*using mono_domain_get = intptr_t(__cdecl*)();

		auto mono_domain_get_export = process.modules().GetExport(module_data, "mono_domain_get");

		blackbone::RemoteFunction<mono_domain_get> mono_domain_get_function{ process, mono_domain_get_export->procAddress };
		decltype(mono_domain_get_function)::CallArguments args{};

		auto result = mono_domain_get_function.Call(args, thread);
		if (!result.success())
			throw std::runtime_error("Could not call mono_domain_get");

		return result.result();*/
	}

	intptr_t injection::thread_attatch(intptr_t domain)
	{
		//using mono_thread_attach = intptr_t(__cdecl*)(intptr_t /*domain*/);

		//auto mono_thread_attach_export = process.modules().GetExport(module_data, "mono_thread_attach");

		//blackbone::RemoteFunction<mono_thread_attach> mono_thread_attach_function{ process, mono_thread_attach_export->procAddress };
		//decltype(mono_thread_attach_function)::CallArguments args{
		//	domain
		//};

		//auto result = mono_thread_attach_function.Call(args, thread);
		//if (!result.success())
		//	throw std::runtime_error("Could not call mono_thread_attach");

		//return result.result();
	}

	void injection::security_set_mode(int mode)
	{
		//using mono_security_set_mode = void(__cdecl*)(int /*mode*/);

		//auto mono_security_set_mode_export = process.modules().GetExport(module_data, "mono_security_set_mode");

		//blackbone::RemoteFunction<mono_security_set_mode> mono_security_set_mode_function{ process, mono_security_set_mode_export->procAddress };
		//decltype(mono_security_set_mode_function)::CallArguments args{
		//	mode
		//};

		//auto result = mono_security_set_mode_function.Call(args, thread);
		//if (!result.success())
		//	throw std::runtime_error("Could not call mono_security_set_mode");
	}

	intptr_t injection::image_open_from_data_full(const std::vector<char>& image)
	{
		//using mono_image_open_from_data = intptr_t(__cdecl*)(intptr_t /*image*/, uint32_t /*data_len*/, int /*need_copy*/, int* /*status*/, int /*refonly*/);

		//auto mono_image_open_from_data_export = process.modules().GetExport(module_data, "mono_image_open_from_data_full");

		//auto memblock = process.memory().Allocate(image.size(), PAGE_READWRITE);
		//memblock->Write(0, image.size(), image.data());

		//int status;

		//blackbone::RemoteFunction<mono_image_open_from_data> mono_image_open_from_data_function{ process, mono_image_open_from_data_export->procAddress };
		//decltype(mono_image_open_from_data_function)::CallArguments args{
		//	memblock->ptr<intptr_t>(),
		//	static_cast<uint32_t>(image.size()),
		//	1,
		//	&status,
		//	0
		//};

		//auto result = mono_image_open_from_data_function.Call(args, thread);

		//memblock->Free();

		//if (!result.success())
		//	throw std::runtime_error("Could not call mono_image_open_from_data_full");

		//return result.result();
	}

	intptr_t injection::assembly_load_from_full(intptr_t raw_image)
	{
		//using mono_assembly_load_from = intptr_t(__cdecl*)(intptr_t /*image*/, int* /*fname*/, int* /*status*/, bool /*refonly*/);
		//auto mono_assembly_load_from_export = process.modules().GetExport(module_data, "mono_assembly_load_from_full");
		//int status;
		//blackbone::RemoteFunction<mono_assembly_load_from> mono_assembly_load_from_function{ process, mono_assembly_load_from_export->procAddress };
		//decltype(mono_assembly_load_from_function)::CallArguments args{
		//	raw_image,
		//	nullptr,
		//	&status,
		//	false
		//};
		//auto result = mono_assembly_load_from_function.Call(args, thread);
		//if (!result.success())
		//	throw std::runtime_error("Could not call mono_assembly_load_from_full");
		//return result.result();
	}

	intptr_t injection::assembly_get_image(intptr_t assembly)
	{
		//using mono_assembly_get_image = intptr_t(__cdecl*)(intptr_t /*assembly*/);
		//auto mono_assembly_get_image_export = process.modules().GetExport(module_data, "mono_assembly_get_image");
		//blackbone::RemoteFunction<mono_assembly_get_image> mono_assembly_get_image_function{ process, mono_assembly_get_image_export->procAddress };
		//decltype(mono_assembly_get_image_function)::CallArguments args{
		//	assembly
		//};
		//auto result = mono_assembly_get_image_function.Call(args, thread);
		//if (!result.success())
		//	throw std::runtime_error("Could not call mono_assembly_get_image");
		//return result.result();
	}

	intptr_t injection::get_class_from_name(intptr_t image, const char* name_space, const char* class_name)
	{
		//using mono_class_from_name = intptr_t(__cdecl*)(intptr_t /*image*/, const char* /*name_space*/, const char* /*class*/);
		//auto mono_class_from_name_export = process.modules().GetExport(module_data, "mono_class_from_name");
		//blackbone::RemoteFunction<mono_class_from_name> mono_class_from_name_function{ process, mono_class_from_name_export->procAddress };
		//decltype(mono_class_from_name_function)::CallArguments args{
		//	image,
		//	name_space,
		//	class_name
		//};
		//auto result = mono_class_from_name_function.Call(args, thread);
		//if (!result.success())
		//	throw std::runtime_error("Could not call mono_class_from_name");
		//return result.result();
	}

	intptr_t injection::get_method_from_name(intptr_t class_id, const char* method_name)
	{
		//using mono_class_get_method_from_name = intptr_t(__cdecl*)(intptr_t /*class*/, const char* /*method_name*/, int /*param_count*/);
		//auto mono_class_get_method_export = process.modules().GetExport(module_data, "mono_class_get_method_from_name");
		//blackbone::RemoteFunction<mono_class_get_method_from_name> mono_class_get_method_function{ process, mono_class_get_method_export->procAddress };
		//decltype(mono_class_get_method_function)::CallArguments args{
		//	class_id,
		//	method_name,
		//	0
		//};
		//auto result = mono_class_get_method_function.Call(args, thread);
		//if (!result.success())
		//	throw std::runtime_error("Could not call mono_class_get_method_from_name");
		//return result.result();
	}

	intptr_t injection::runtime_invoke_method(intptr_t method_id)
	{
		//using mono_runtime_invoke = intptr_t(__cdecl*)(intptr_t /*method*/, void* /*obj*/, void** /*params*/, int** /*exc*/);
		//auto mono_runtime_invoke_export = process.modules().GetExport(module_data, "mono_runtime_invoke");
		//blackbone::RemoteFunction<mono_runtime_invoke> mono_runtime_invoke_function{ process, mono_runtime_invoke_export->procAddress };
		//decltype(mono_runtime_invoke_function)::CallArguments args{
		//	method_id,
		//	nullptr,
		//	nullptr,
		//	nullptr
		//};
		//auto result = mono_runtime_invoke_function.Call(args, thread);
		//if (!result.success())
		//	throw std::runtime_error("Could not call mono_runtime_invoke");
		//return result.result();
	}

	int injection::thread_detach(intptr_t domain)
	{
		//using mono_thread_detach = int(__cdecl*)(intptr_t /*domain*/);
		//auto mono_thread_detach_export = process.modules().GetExport(module_data, "mono_thread_detach");
		//blackbone::RemoteFunction<mono_thread_detach> mono_thread_detach_function{ process, mono_thread_detach_export->procAddress };
		//decltype(mono_thread_detach_function)::CallArguments args{
		//	domain
		//};
		//auto result = mono_thread_detach_function.Call(args, thread);
		//if (!result.success())
		//	throw std::runtime_error("Could not call mono_thread_detach");
		//return result.result();
	}

	NTSTATUS injection::unlink_assembly(intptr_t domain)
	{
//		// Last loaded assembly should be the first in the array
//
//		auto pAsm = blackbone::AsmFactory::GetAssembler(process.modules().GetMainModule()->type);
//		auto& a = *pAsm;
//
//		a.GenPrologue();
//
//		a->push(a->zdi);
//		a->push(a->zcx);
//
//		a->mov(a->zdi, domain);
//
//#if _WIN64
//		a->add(a->zdi, 0xc0);
//#else
//		a->add(a->zdi, 0x6c);
//#endif
//
//		a->mov(a->zcx, a->intptr_ptr(a->zdi)); // GSList* tmp = domain->domain_assemblies
//
//#if _WIN64
//		a->add(a->zcx, 0x8);
//#else
//		a->add(a->zcx, 0x4);
//#endif
//
//		a->mov(a->zcx, a->intptr_ptr(a->zcx)); // tmp = tmp->next
//		a->mov(a->intptr_ptr(a->zdi), a->zcx); // domain->domain_assemblies = tmp
//
//		a->pop(a->zcx);
//		a->pop(a->zdi);
//
//		process.remote().AddReturnWithEvent(a);
//
//		a.GenEpilogue();
//
//		uint64_t result = NULL;
//		auto status = process.remote().ExecInWorkerThread(a->make(), a->getCodeSize(), result);
//
//		return status;
	}
}