#include "gui/gui.hpp"
#include "util/message_system.hpp"
#include "util/gui_util.hpp"

namespace loader
{
	void gui::home_tab()
	{
        static int changelog_game = 1;

        ImGui::BeginGroup();
        ImGui::BeginChild("main_changelog_child", ImVec2(300, y), 0, ImGuiWindowFlags_NoBackground);//needed for changelog centertext
        g_gui_util.centertext("Changelogs", 1);//center me
        if (ImGui::BeginCombo("", games[changelog_game]))
        {
            for (int game_ = 0; game_ <= LETHAL_COMPANY; game_++)
            {
                if (ImGui::Selectable(games[game_], game_ == changelog_game))
                    changelog_game = game_;
                if (games[changelog_game] == games[game_])
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        ImGui::BeginChild("changelogs", ImVec2(300, 265), 1);
        std::string menu = "";
        if (changelog_game == 0) menu = "Blade";
        if (changelog_game == 1) menu = "Unk";
        if (changelog_game == 2) menu = "Spooksuite";
        if (changelog_game == 3) menu = "Lethal Menu";
        ImGui::TextWrapped(util::read_file((fs::current_path() / "Resources" / menu / "Changelog.txt").string()).c_str());
        ImGui::EndChild();
        ImGui::EndChild();
        ImGui::EndGroup();

        ImGui::SameLine();

        ImGui::BeginGroup();
        static char message;
        ImGui::BeginChild("chatmain", ImVec2(430, 255), true);
        g_message_system.display_messages();
        ImGui::EndChild();
        ImGui::Dummy(ImVec2(0, 5));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
        ImGui::BeginChild("chatsender", ImVec2(430, 50), true);
        ImGui::SetNextItemWidth(250);
        ImGui::InputText("Message", &message, 50);
        ImGui::SameLine();
        ImGui::Text(std::format("{}/50", std::string((&message)).size()).c_str());
        ImGui::SameLine();
        if (ImGui::Button("Send"))
            g_message_system.send_message(&message);

        ImGui::EndChild();
        ImGui::PopStyleVar();
        ImGui::EndGroup();
	}
}