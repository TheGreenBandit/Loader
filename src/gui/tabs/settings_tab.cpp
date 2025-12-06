#include "../gui.hpp"
#include "../../util/gui_util.hpp"

namespace loader
{
	void gui::settings_tab()
	{
		static char key_text;
		//325 total height
		ImGui::BeginChild("pt1", ImVec2(737, 75), 1);//hmmm what to put here
		ImGui::Text("Wtf to put up here");//center me!
		ImGui::EndChild();
		ImGui::BeginChild("key?", ImVec2(737, 50), 1);//prob not i dont make paid 
		ImGui::InputText("tf to put here?", &key_text, sizeof(key_text));
		ImGui::EndChild();
		ImGui::BeginChild("main_settings_1", ImVec2(566, 190), 1);
		ImGui::Text("Main Settings");//center me!
		ImGui::Separator();
		ImGui::Checkbox("Close On Inject", &active);
		ImGui::Checkbox("Another option dude", &active);
		ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginChild("main_settings_2", ImVec2(166, 190), 1);
		g_gui_util.centertext("Auto Inject", 1);
		//ImGui::Text("Auto Inject");//center me!
		//ImGui::Separator();
		ImGui::Checkbox("GtaV", &active);
		ImGui::Checkbox("Repo", &active);
		ImGui::Checkbox("Content Warning", &active);
		ImGui::Checkbox("Lethal Company", &active);
		ImGui::EndChild();
	}
}