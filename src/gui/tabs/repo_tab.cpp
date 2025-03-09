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
        if (ImGui::Button("Load Menu"))
            g_inject.inject();
        if (ImGui::Button("Launch Game"))
            ShellExecuteA(0, "open", "steam://rungameid/3241660", 0, 0, SW_HIDE);
        //if (ImGui::Button("Open Game Folder"))

    }
}