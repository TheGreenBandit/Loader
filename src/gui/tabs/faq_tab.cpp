#include "../gui.hpp"
#include "../../util/gui_util.hpp"

namespace loader
{
    inline void QA(const char* q, const char* a, const char* link = "")
    {
        ImGui::Text(std::format("{} {}", ICON_FA_QUESTION, q).c_str());
        ImGui::Text(std::format("{} {}", ICON_FA_BRAIN, a).c_str());
        if (link != "")
        {
            ImGui::SameLine();
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, -2));
            if (ImGui::Button("Here", ImVec2(40, ImGui::CalcTextSize("Here").y)))
                ShellExecuteA(0, "open", "", 0, 0, SW_HIDE);
            ImGui::PopStyleVar();
        }
        ImGui::Separator();
    }

    void gui::faq_tab()
    {
        QA("Is this a virus?", "No, the source to the loader can be viewed on my github", "https://github.com/TheGreenBandit/Loader");
        QA("How do i download one of the menus?", "The loader will automatically download the latest dll of the menu once you press start!");
        QA("The loader doesn't seem to load the menu!", "1. Try running the loader as an administrator,\n 2. make sure the loader's folder that it is in is excluded from windows defender.\n 3.If these dont work send your loader.log and if you have one DebugLog.txt to the #support channle in the discord.");
    }
}