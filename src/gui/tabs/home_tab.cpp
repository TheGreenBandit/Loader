#include "../gui.hpp"

namespace loader
{
	void gui::home_tab()
	{
		ImGui::Image((void*)icon->view,
			ImVec2(100, 100),
			ImVec2(0, 0),
			ImVec2(1, 1),
			ImVec4(255, 255, 255, 255));

		ImGui::Text((std::string("Welcome ") + util::get_username().data()).c_str());
		ImGui::Text(VERSION);
		ImGui::Text("You may receive anti-virus alerts where it'll detect the loader as a virus.\n If this happens follow this video to fix it!");
		
		if (ImGui::Button("Video Tutorial")) 
			ShellExecuteA(0, 0, "https://www.youtube.com/watch?v=BonLkFNnO9w", 0, 0, SW_HIDE);
		//if (ImGui::Button("Join the discord here!"))
		//	ShellExecuteA(0, 0, "https://discord.gg/eVBBZrEy8j", 0, 0, SW_HIDE);
	}
}