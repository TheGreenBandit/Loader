#include "../gui.hpp"
#include "../../util/gui_util.hpp"

namespace loader
{
	void gui::home_tab()
	{
		ImGui::Text("The repo menu will probably only receive weekly updates,\n this is as i work part time and go to school. If a critical bug or update happens i will probably fix same day.");
		ImGui::Text("You may receive anti-virus alerts where it'll detect the loader as a virus.\n If this happens follow this video to fix it!");
		if (ImGui::Button("Video Tutorial")) 
			ShellExecuteA(0, 0, "https://www.youtube.com/watch?v=BonLkFNnO9w", 0, 0, SW_HIDE);
		g_gui_util.push_font_size(24);
		ImGui::Text("Icyrelic banned me from his server.\n Stay in contact with me below");
		if (ImGui::Button("NEW DISCORD!"))
			ShellExecuteA(0, 0, "https://discord.gg/cMMwtUQhpE", 0, 0, SW_HIDE);
		g_gui_util.pop_font_size();
	}
}