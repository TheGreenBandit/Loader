#pragma once
#include "common.hpp"
#include "gui/gui.hpp"

namespace loader
{
	struct gui_util
	{
		inline void image_showcase(std::map<int, std::pair<std::string, Image*>> map, ImVec2 specified_size = ImVec2(0, 0), std::string default_tx = "")
		{
			ImGui::BeginGroup();
			ImVec2 c = ImGui::GetCursorPos();
			if (g_gui.selected_img == 0)
				ImGui::Image(g_gui.game_to_background(g_gui.game)->view, specified_size);
			else
				ImGui::Image(map.find(g_gui.selected_img)->second.second->view, specified_size);

			ImGui::PushStyleColor(ImGuiCol_Border, g_gui.accent_color);
			ImGui::PushStyleColor(ImGuiCol_Button, g_gui.accent_color);
			ImVec4 hov = ImVec4(g_gui.accent_color.x - .3, g_gui.accent_color.y - .3, g_gui.accent_color.z - .3, g_gui.accent_color.w);
			ImVec4 act = ImVec4(g_gui.accent_color.x - .4, g_gui.accent_color.y - .4, g_gui.accent_color.z - .4, g_gui.accent_color.w);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hov);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, act);
			if (map.size() > 0)
			{
				ImGui::SetCursorPos(ImVec2(c.x, c.y + 162));
				if (ImGui::Button(ICON_FA_ARROW_LEFT))
				{
					g_gui.selected_img--;
					if (g_gui.selected_img < 0)
						g_gui.selected_img = map.size();
				}
				ImGui::SetCursorPos(ImVec2(c.x + (specified_size.x - 30), c.y + (specified_size.y / 2)));
				if (ImGui::Button(ICON_FA_ARROW_RIGHT))
				{
					g_gui.selected_img++;
					if (g_gui.selected_img > map.size())
						g_gui.selected_img = 0;
				}
				std::string txt = (g_gui.selected_img == 0) ? default_tx : map.find(g_gui.selected_img)->second.first;
				ImGui::SetCursorPos(ImVec2(c.x + (specified_size.x - ImGui::CalcTextSize(txt.c_str()).x) / 2, c.y + (specified_size.y - 25)));
				ImGui::Text(txt.c_str());
			}
			ImGui::EndGroup();
		}

		inline void centeredchild(const char* name, ImVec2 size, bool border, std::function<void()> options) // works!
		{
			ImGui::SetCursorPosX((ImGui::GetContentRegionAvail().x / 2) - (size.x / 2));
			ImGui::BeginChild(name, size, border);
			options();
			ImGui::EndChild();
		}
		inline void center(std::function<void()> control, float x)
		{
			ImGui::SetCursorPosX((ImGui::GetContentRegionAvail().x / 2) - (x /2));
			ImGui::BeginGroup();
			control();
			ImGui::EndGroup();
		}

		inline void centertext(std::string_view text, bool seperator = false, bool usemax = false)
		{
			ImGui::SetCursorPosX(
				((usemax ? ImGui::GetContentRegionMax().x : ImGui::GetContentRegionAvail().x) / 2) - (ImGui::CalcTextSize(text.data()).x / 2));
			ImGui::Text(text.data());
		
			if (seperator)
				ImGui::Separator();
		}

		inline void righttext(std::string_view text, bool seperator = false)
		{
			ImGui::SetCursorPosX(ImGui::GetContentRegionAvail().x - (ImGui::CalcTextSize(text.data()).x / 1.25));
			ImGui::Text(text.data());
			if (seperator)
				ImGui::Separator();
		}
	};
	static gui_util g_gui_util;
}