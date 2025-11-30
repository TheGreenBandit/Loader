#pragma once
#include "../common.hpp"

namespace loader
{
	struct gui_util
	{
		inline const char* s(std::string_view string)
		{
			return string.data();
		}

		inline void image_showcase(int* selected, std::vector<Image*> images, ImVec2 specified_size = ImVec2(0,0))
		{
			ImVec2 s = (specified_size.x == 0 || specified_size.y == 0) ? ImVec2(images[*selected]->size[0],
				images[*selected]->size[1]) : specified_size;
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyleColorVec4(ImGuiCol_WindowBg));
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
			ImVec2 c = { s.x + 40, s.y };
			centeredchild("", c, false, [=]
				{				
					int ret = *selected;
					float opos = ImGui::GetCursorPosY();
					float npos = (ImGui::GetContentRegionAvail().y / 2) - 20;
					ImGui::SetCursorPosY(opos);
					if (ImGui::Button(ICON_FA_ARROW_LEFT, ImVec2(20, c.y)))
						ret --;
					ImGui::SameLine();
					ImGui::SetCursorPosY(opos);
					ImGui::Image((void*)images[*selected]->view, s);
					ImGui::SameLine();
					ImGui::SetCursorPosY(opos);

					if (ImGui::Button(ICON_FA_ARROW_RIGHT, ImVec2(20, c.y)))
						ret ++;
					if (ret > (images.size() - 1)) ret = 0;//back and forth function
					if (ret < 0) ret = (images.size() - 1);
					*selected = ret;
				});
			ImGui::PopStyleVar();
			ImGui::PopStyleVar();
			ImGui::PopStyleColor();
		}

		inline Image* download_and_load_image_to_list(const char* path, const char* link, std::vector<loader::Image*>* image_dir = nullptr)
		{
			util::download_file(path, link);
			loader::Image* ret = new loader::Image();
			g_gui.load_texture_from_file(path, g_pd3dDevice, &ret);

			if (image_dir != nullptr)
				image_dir->push_back(ret);
			return ret;
		}

		inline void tab(etab tab)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, (g_gui.tab == tab) ? (&ImGui::GetStyle())->Colors[ImGuiCol_WindowBg] : (&ImGui::GetStyle())->Colors[ImGuiCol_Text]);
			if (ImGui::Button(std::format("{} {}", g_gui.get_tab_icon(tab), g_gui.tab_to_name(tab).data()).c_str()))
				g_gui.tab = tab;
			ImGui::PopStyleColor();
		}
		//get me working

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

		inline void push_font_size(float size)//remove me
		{
			g_gui.segoeui_font_20px->FontSize = size;
		}

		inline void pop_font_size()
		{
			g_gui.segoeui_font_20px->FontSize = 20;
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