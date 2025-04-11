#include "../gui.hpp"
#include "../../util/gui_util.hpp"

namespace loader
{
    static int selected_image = 0;
    static int selected_log = 0;

    void switchbutton(const char* name, int id)
    {
        ImGui::PushStyleColor(ImGuiCol_Text, (id == selected_log) ? (&ImGui::GetStyle())->Colors[ImGuiCol_WindowBg] : (&ImGui::GetStyle())->Colors[ImGuiCol_Text]);
        if (ImGui::Button(name))
        {
            selected_log = id;
            selected_image = 0;
        }
        ImGui::PopStyleColor();
    }

    void gui::changelog_tab()
    {
        switchbutton("Loader", 0);
        ImGui::SameLine();
        switchbutton("Lethal Menu", 1);
        ImGui::SameLine();
        switchbutton("Spooksuite", 2);
        ImGui::SameLine();
        switchbutton("Unk", 3);
        ImGui::SameLine();
        switchbutton("Acid", 4);

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
            case 4:
            {
                ImGui::BeginChild("acidchangelog", ImVec2(530, 440), true);
                ImGui::TextWrapped(util::read_file((fs::current_path() / "Resources" / "Acid" / "Changelog.txt").string()).c_str());
                ImGui::EndChild();
            }
        }
    }
}