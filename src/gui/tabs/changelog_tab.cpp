#include "../gui.hpp"
#include "../../util/gui_util.hpp"

namespace loader
{
    void gui::changelog_tab()
    {
        static int selected_image = 0;
        static int selected_log = 0;
        if (ImGui::Button("Loader"))
        {
            selected_log = 0;
            selected_image = 0;//reset image showcase for each on switch tab
        }
        ImGui::SameLine();
        if (ImGui::Button("Lethal Menu"))
        {
            selected_log = 1;
            selected_image = 0;
        }
        ImGui::SameLine();
        if (ImGui::Button("SpookSuite"))
        {
            selected_log = 2;
            selected_image = 0;
        }
        ImGui::SameLine();
        if (ImGui::Button("Unk"))
        {
            selected_log = 3;
            selected_image = 0;
        }
        
        ImGui::Separator();

        switch (selected_log)
        {
            case 0: 
            {
                ImGui::Text("Loader changelog, add stuff here");
            }break;
            case 1:
            {
                ImGui::BeginChild("lethalmenuchangelog", ImVec2(530, 440), true);
                ImGui::TextWrapped(util::read_file((fs::current_path() / "Resources" / "Lethal Menu" / "Changelog.txt").string()).c_str());
                ImGui::EndChild();
            }break;
            case 2:
            {
                ImGui::BeginChild("spooksuitechangelog", ImVec2(530, 440), true);
                ImGui::TextWrapped(util::read_file((fs::current_path() / "Resources" / "Spooksuite" / "Changelog.txt").string()).c_str());
                ImGui::EndChild();
            }break;
            case 3:
            {
                //todo
                g_gui_util.image_showcase(&selected_image, unkimages, ImVec2(400, 200));
                ImGui::BeginChild("unkchangelog", ImVec2(530, 440), true);
                ImGui::TextWrapped(util::read_file((fs::current_path() / "Resources" / "Unk" / "Changelog.txt").string()).c_str());
                ImGui::EndChild();
            }break;
        }
    }
}