#include "../gui.hpp"
#include <format>
#include <filesystem>
#include "../../util/gui_util.hpp"
#include "../../util/injection.hpp"

namespace fs = std::filesystem;

namespace loader
{
    void gui::repo_tab()
    {
        auto path = fs::current_path() / "Menus" / "unk" / "unk.dll";
        if (!fs::exists(path))
        {
            ImGui::Text("It seems the menu is not yet installed...");
            ImGui::Text(std::format("Would you like to download it to {}?", path.string()).c_str());
            if (ImGui::Button("Download"))
            {
                if (!fs::is_directory(fs::current_path() / "Menus" / "unk")) fs::create_directory(fs::current_path() / "Menus" / "unk");
                util::download_file(path.string(), "https://github.com/TheGreenBandit/unk/releases/download/release/unk.dll");
            }
        }
        else if (ImGui::Button("Load Menu"))
            g_inject.inject();
        if (ImGui::Button("Launch Game"))
            ShellExecuteA(0, "open", "steam://rungameid/3241660", 0, 0, SW_HIDE);
        //if (ImGui::Button("Open Game Folder"))

    }
}