#include "../gui.hpp"
#include "../../util/gui_util.hpp"

namespace loader
{
	void gui::home_tab()
	{
		ImGui::TextWrapped("You may receive anti-virus alerts where it'll detect the loader as a virus. If this happens follow this video to fix it!");
		g_gui_util.push_font_size(20);
		ImGui::Text("Announcement!");
		g_gui_util.pop_font_size();
		ImGui::Text("");
		if (ImGui::Button("Video Tutorial")) 
			ShellExecuteA(0, 0, "https://www.youtube.com/watch?v=BonLkFNnO9w", 0, 0, SW_HIDE);
		if (ImGui::Button("Community Discord!"))
			ShellExecuteA(0, 0, "https://discord.gg/cMMwtUQhpE", 0, 0, SW_HIDE);
	}
}