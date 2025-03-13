#include "../gui.hpp"
#include "../../util/gui_util.hpp"

namespace loader
{
	void gui::settings_tab()
	{
        ImGui::BeginGroup();
        {
            ImGui::Text("Settings are being worked upon, please suggest in the discord!");
            g_gui_util.centeredchild("Settings", ImVec2(180, 110), true, [] {
                static bool checkbox = false;
                ImGui::Checkbox("Close On Inject", &g.auto_close);
                });
            //ImGui::BeginChild("Auto Inject", ImVec2(180, 110), true);
            //g_gui_util.centertext("Auto Inject", 1);
            //{
            //    ImGui::Checkbox("Lethal Company", &g.auto_inject.lethal_company);
            //    ImGui::Checkbox("Content Warning", &g.auto_inject.content_warning);
            //    ImGui::Checkbox("R.E.P.O", &g.auto_inject.repo);
            //}
            //ImGui::EndChild();

            //ImGui::BeginChild("Settings", ImVec2(180, 110), true);
            //g_gui_util.centertext("Settings", 1);
            //{
            //    ImGui::Checkbox("Close On Inject", &g.auto_close);
            //}
            //ImGui::EndChild();
        }
        ImGui::EndGroup();
        ImGui::SameLine();
        ImGui::BeginGroup();
        {
            //ImGui::BeginChild("");

            //ImGui::EndChild();
        }
        ImGui::EndGroup();
	}
}