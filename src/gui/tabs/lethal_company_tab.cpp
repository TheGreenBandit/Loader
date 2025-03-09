#include "../gui.hpp"
#include <format>
#include <filesystem>
#include "../../util/gui_util.hpp"
#include "../../util/injection.hpp"

namespace fs = std::filesystem;

namespace loader
{
	void gui::lethal_company_tab()
	{
        auto path = fs::current_path() / "Menus" / "LethalMenu" / "lethalmenu.dll";
        if (!fs::exists(path))
        {
            ImGui::Text("It seems the menu is not yet installed...");
            ImGui::Text(std::format("Would you like to download it to {}?", path.string()).c_str());
            if (ImGui::Button("Download"))
            {
                if (!fs::is_directory(fs::current_path() / "Menus" / "LethalMenu")) fs::create_directory(fs::current_path() / "Menus" / "LethalMenu");
                util::download_file(path.string(), "https://icyrelic.com/release/lethalmenu/LethalMenu.dll");
            }
        }
        else
        {
            if (ImGui::Button("Redownload"))
            {
                if (!fs::is_directory(fs::current_path() / "Menus" / "LethalMenu")) fs::create_directory(fs::current_path() / "Menus" / "LethalMenu");
                util::download_file(path.string(), "https://icyrelic.com/release/lethalmenu/LethalMenu.dll");
            }
            if (ImGui::Button("Load Menu"))
                g_inject.inject();
        }
        if (ImGui::Button("Launch Game"))
            ShellExecuteA(0, "open", "steam://rungameid/1966720", 0, 0, SW_HIDE);

	}
}