#pragma once
#include "../common.hpp"

namespace loader
{
	struct gui_util
	{
		inline void tab(etab tab)
		{
			if (ImGui::Button(g_gui.tab_to_name(tab).data()))
				g_gui.tab = tab;
		}
		//get me working
		inline void center(std::function<void()> control, float y_offset = 0, float spacing_below = 0, float spacing_up = 0) const
		{
			ImVec2 original_pos = ImGui::GetCursorPos();
			ImGui::SetCursorPos(ImVec2(-10000.0f, -10000.0f)); //render out of frame to get size
			control();
			ImVec2 control_size = ImGui::GetItemRectSize();
			ImGui::Dummy(ImVec2(0, spacing_up));
			ImGui::SetCursorPos(ImVec2((ImGui::GetContentRegionAvail().x - control_size.x) / 2.9, original_pos.y + y_offset));
			control();
			ImGui::Dummy(ImVec2(0, spacing_below));
		}

		inline void centertext(std::string_view text, bool seperator = false, bool usemax = false)
		{
			if (!usemax)
			{
				ImGui::SetCursorPosX(
					((ImGui::GetContentRegionAvail().x) / 2) - (ImGui::CalcTextSize(text.data()).x / 2));
				ImGui::Text(text.data());
			}
			else
			{
				ImGui::SetCursorPosX(
					(ImGui::GetContentRegionMax().x / 2) - (ImGui::CalcTextSize(text.data()).x / 2));
				ImGui::Text(text.data());
			}
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