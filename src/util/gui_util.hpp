#pragma once
#include "../common.hpp"

namespace loader
{
	struct gui_util
	{
		inline void image_showcase(int* selected, std::vector<Image*> images, ImVec2 specified_size = ImVec2(0,0))
		{
			ImVec2 s = (specified_size.x == 0 || specified_size.y == 0) ? ImVec2(images[*selected]->size[0],
				images[*selected]->size[1]) : specified_size;
			centeredchild("", ImVec2(s.x + 15, s.y), false, [=]
				{
					int ret = *selected;
					float opos = ImGui::GetCursorPosY();
					float npos = ImGui::GetContentRegionAvail().y / 2;
					ImGui::SetCursorPosY(npos);
					if (ImGui::Button("<"))
						ret --;
					ImGui::SameLine();
					ImGui::SetCursorPosY(opos);
					ImGui::Image((void*)images[*selected]->view, s);
					ImGui::SameLine();
					ImGui::SetCursorPosY(npos);
					if (ImGui::Button(">"))
						ret ++;
					if (ret > (images.size() - 1)) ret = 0;//back and forth function
					if (ret < 0) ret = (images.size() - 1);
					*selected = ret;
				});
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
			if (ImGui::Button(g_gui.tab_to_name(tab).data()))
				g_gui.tab = tab;
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