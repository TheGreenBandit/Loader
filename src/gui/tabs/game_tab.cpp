#include "../gui.hpp"
#include "../../util/gui_util.hpp"
#include "../../util/injection.hpp"
#include "shellapi.h"

namespace loader
{
    void launch_game(egame game)
    {
        switch (game)
        {
        case GTAV:
            ShellExecuteA(0, "open", "com.epicgames.launcher://apps/0584d2013f0149a791e7b9bad0eec102%3A6e563a2c0f5f46e3b4e88b5f4ed50cca%3A9d2d0eb64d5c44529cece33fe2a46482?action=launch&silent=true", 0, 0, SW_HIDE); break;
        case REPO:
            ShellExecuteA(0, "open", "steam://rungameid/3241660", 0, 0, SW_HIDE); break;
        case CONTENT_WARNING:
            ShellExecuteA(0, "open", "steam://rungameid/2881650", 0, 0, SW_HIDE); break;
        case LETHAL_COMPANY:
            ShellExecuteA(0, "open", "steam://rungameid/1966720", 0, 0, SW_HIDE); break;
        }
    }

    void gui::game_tab()
    {
        const char* name = "";
        const char* name2 = "";
        ImVec4 col = ImVec4(0, 0, 0, 0);
        const char* gamename = "";
        const char* desc = "";
        std::map<int, std::pair<std::string, Image*>> map;
        switch (game)
        {
        case 0:
        {
            map = blade_map;
            name = "Blade";
            name2 = "Menu";
            col = ImVec4(0, 1, 0, 1);
            gamename = "GTAV";
            desc = "A dual UI, personal pet project of mine. Not meant for online as there is zero protection from the anticheat in it.";
        }break;
        case 1:
        {
            map = unk_map;
            name = "Unk";
            name2 = "";
            col = ImVec4(1, 0, 1, 1);
            gamename = "R.E.P.O";
            desc = "The most advanced menu for R.E.P.O.";
        }break;
        case 2:
        {
            map = spooksuite_map;
            name = "Spook";
            name2 = "Suite";
            col = ImVec4(1, 0, 1, 1);
            gamename = "Content Warning";
            desc = "A old joint collaboration.";
        }break;
        case 3:
        {
            map = lethalmenu_map;
            name = "Lethal";
            name2 = "Menu";
            col = ImVec4(1, 0, 0, 1);
            gamename = "Lethal Company";
            desc = "A menu for Lethal Company.";
        }break;
        }
        static int img = 0;//make this in gui.hpp and reset it when clicking on a different game tab
        ImGui::BeginGroup();
        ImVec2 c = ImGui::GetCursorPos();
        accent_color = col;
        if (img == 0)
            ImGui::Image(game_to_background(game)->view, ImVec2(578, 325));
        else
            ImGui::Image(map.find(img)->second.second->view, ImVec2(578, 325));
        
        ImGui::PushStyleColor(ImGuiCol_Border, col);
        ImGui::PushStyleColor(ImGuiCol_Button, col);
        ImVec4 hov = ImVec4(col.x - .3, col.y - .3, col.z - .3, col.w);
        ImVec4 act = ImVec4(col.x - .4, col.y - .4, col.z - .4, col.w);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hov);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, act);
        ImGui::SetCursorPos(ImVec2(c.x, c.y + 162));
        if (ImGui::Button(ICON_FA_ARROW_LEFT))
        {
            img--;
            if (img < 0)
                img = map.size();
        }
        ImGui::SetCursorPos(ImVec2(c.x + 548, c.y + 162));
        if (ImGui::Button(ICON_FA_ARROW_RIGHT))
        {
            img++;
            if (img > map.size())
                img = 0;
        }

        std::string txt = (img == 0) ? "Press on the arrows to see pictures of the menu!" : map.find(img)->second.first;
        ImGui::SetCursorPos(ImVec2(c.x + (572 - ImGui::CalcTextSize(txt.c_str()).x) / 2, c.y + 300));
        ImGui::Text(txt.c_str());

        ImGui::EndGroup();
        ImGui::SameLine();
        ImGui::BeginGroup();
        ImGui::PushFont(NULL, 35);
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
        ImGui::PushFont(NULL, 25);
        if (ImGui::Button("Launch Game", ImVec2(155, 30)))
            launch_game(game);
        if (util::is_dev() && (game == GTAV))
        {
            if (ImGui::Button("Dev", ImVec2(75, 30)))
                g_inject.inject_dll(g_gui.game, "C:\\Users\\TGB\\Blade\\build\\RelWithDebInfo\\Blade.dll");
            ImGui::SameLine();
        }
        if (ImGui::Button("Inject", ImVec2((util::is_dev() && (game == GTAV)) ? 75 : 155, 30)))
            g_inject.inject();
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