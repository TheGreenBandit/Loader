#include "../gui.hpp"
#include "../../util/injection.hpp"
#include "../../util/gui_util.hpp"

namespace fs = std::filesystem;

namespace loader
{
    int selected_image = 0;
    void gui::repo_tab()
    {
        g_gui_util.image_showcase(&selected_image, unkimages, ImVec2(400, 200));
        ImGui::Dummy(ImVec2(0, 20));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0, 20));
        if (ImGui::Button("Load Menu"))
            g_inject.inject();
        if (ImGui::Button("Launch Game"))
            ShellExecuteA(0, "open", "steam://rungameid/3241660", 0, 0, SW_HIDE);
    }
}