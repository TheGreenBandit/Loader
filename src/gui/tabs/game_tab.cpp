#include "../gui.hpp"
#include "../../util/gui_util.hpp"

namespace loader
{
    void gui::game_tab()
    {
        Image* img = new Image();
        const char* name = "";
        const char* name2 = "";
        ImVec4 col = ImVec4(0, 0, 0, 0);
        const char* gamename = "";
        const char* desc = "";

        switch (game)
        {
        case 0:
        {
            img = gta_background;
            name = "Blade";
            name2 = "Menu";
            col = ImVec4(0, 1, 0, 1);
            gamename = "GTAV";
            desc = "A dual UI, personal pet project of mine. Not meant for online as there is zero protection from the anticheat in it.";
        }break;
        case 1:
        {
            img = repo_background;
            name = "Unk";
            name2 = "";
            col = ImVec4(1, 0, 1, 1);
            gamename = "R.E.P.O";
            desc = "The most advanced menu for R.E.P.O.";
        }break;
        case 2:
        {
            img = content_warning_background;
            name = "Blade";
            name2 = "Menu";
            col = ImVec4(1, 0, 1, 1);
            gamename = "Content Warning";
            desc = "A old joint collaboration.";
        }break;
        case 3:
        {
            img = lethal_company_background;
            name = "Lethal";
            name2 = "Menu";
            col = ImVec4(1, 0, 0, 1);
            gamename = "Lethal Company";
            desc = "A menu for Lethal Company.";
        }break;
        }
        ImGui::BeginGroup();
        ImGui::Image(img->view, ImVec2(578, 325));//todo now make this a image selector with pictures of menus
        ImGui::EndGroup();
        ImGui::SameLine();
        ImGui::BeginGroup();
        ImGui::PushFont(segoeui_font_35px);
        ImGui::TextColored(col, name);
        if (name2 != "")
        {
            ImGui::SameLine();
            ImGui::Text(name2);
        }
        ImGui::PopFont();
        ImGui::Text(std::format("For {}", gamename).c_str());
        ImGui::BeginChild("Desc Framing", ImVec2(155, 190));
        ImGui::TextWrapped(desc);
        ImGui::EndChild();
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
        ImGui::PushStyleColor(ImGuiCol_Border, col);
        ImGui::PushStyleColor(ImGuiCol_Button, col);
        ImVec4 hov = ImVec4(col.x - .3, col.y - .3, col.z - .3, col.w);//fixme
        ImVec4 act = ImVec4(col.x - .4, col.y - .4, col.z - .4, col.w);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hov);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, act);
        ImGui::PushFont(segoeui_font_25px);
        if (ImGui::Button("Launch Game", ImVec2(155, 30))) active = false;//these buttons are static and broken somehow
        if (ImGui::Button("Run Menu", ImVec2(155, 30))) active = false;
        ImGui::PopFont();
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
        ImGui::PopStyleVar();
        ImGui::EndGroup();
    }
}