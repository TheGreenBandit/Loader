#include "../gui.hpp"
#include <format>
#include <filesystem>
#include "../../util/injection.hpp"

namespace fs = std::filesystem;

namespace loader
{
    void gui::content_warning_tab()
	{
        auto path = fs::current_path() / "Menus" / "SpookSuite" / "spooksuite.dll";
        if (!fs::exists(path))
        {
            ImGui::Text("It seems the menu is not yet installed...");
            ImGui::Text(std::format("Would you like to download it to {}?", path.string()).c_str());
            if (ImGui::Button("Download")) //fixme
            {
                if (!fs::is_directory(fs::current_path() / "Menus" / "SpookSuite")) fs::create_directory(fs::current_path() / "Menus" / "SpookSuite");
                util::download_file(path.string(), "https://github.com/IcyRelic/SpookSuite/releases/download/release/spooksuite.dll");
            }
        }
        else
        {
            if (ImGui::Button("Redownload"))
            {
                if (!fs::is_directory(fs::current_path() / "Menus" / "SpookSuite")) fs::create_directory(fs::current_path() / "Menus" / "SpookSuite");
                util::download_file(path.string(), "https://github.com/IcyRelic/SpookSuite/releases/download/release/spooksuite.dll");
            }
            if (ImGui::Button("Load Menu"))
                g_inject.inject();
        }
        if (ImGui::Button("Launch Game"))
            ShellExecuteA(0, "open", "steam://rungameid/2881650", 0, 0, SW_HIDE);
	}
}