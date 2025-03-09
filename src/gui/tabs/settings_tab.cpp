#include "../gui.hpp"
#include "../../util/gui_util.hpp"

namespace loader
{
	void gui::settings_tab()
	{
        ImGui::BeginGroup();
        {
            ImGui::BeginChild("Auto Inject", ImVec2(180, 110), true);
            g_gui_util.centertext("Auto Inject", 1);
            {
                ImGui::Checkbox("Lethal Company", &g.auto_inject.lethal_company);
                ImGui::Checkbox("Content Warning", &g.auto_inject.content_warning);
            }
            ImGui::EndChild();

            ImGui::BeginChild("Settings");
            g_gui_util.centertext("Settings", 1);
            {
                ImGui::Checkbox("Close On Inject", &g.auto_close);
            }
            ImGui::EndChild();
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