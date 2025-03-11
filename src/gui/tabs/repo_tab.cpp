#include "../gui.hpp"
#include "../../util/injection.hpp"
#include "../../util/gui_util.hpp"

namespace fs = std::filesystem;

namespace loader
{
    int selected_image = 0;
    void gui::repo_tab()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(1, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
        g_gui_util.image_showcase(&selected_image, unkimages, ImVec2(400, 200));
        ImGui::PopStyleVar();
        ImGui::PopStyleVar();
        if (ImGui::Button("Load Menu"))
            g_inject.inject();
        if (ImGui::Button("Launch Game"))
            ShellExecuteA(0, "open", "steam://rungameid/3241660", 0, 0, SW_HIDE);
    }
}