#include "../gui.hpp"
#include "../../util/gui_util.hpp"

namespace loader
{
    inline void userchat(std::string user, std::string string)
    {
        if (user.size() > 20 || user.size() < 3)
            return;

        if (string.size() < 150)
            messages.push_back()
            ImGui::TextWrapped(std::format("{} {}: {}", ICON_FA_USER, user, string).c_str());
    }
    void gui::chat_tab()
    {
        std::vector<const char*> messages;
        static char message = 'HI';
        ImGui::Text("I'm still deliberating and figuring out how to add this tab.");
        ImGui::BeginChild("chatmain", ImVec2(530, 240), true);
        for (auto message : messages)
            ImGui::TextWrapped(
        userchat("TheGreenBandit", "Welcome to the loader! I'm still figuring out this tab. Check back later!");
        userchat("Loader User", "Hi!");
        ImGui::EndChild();
        ImGui::Dummy(ImVec2(0, 20));
        ImGui::BeginChild("chatsender", ImVec2(530, 180), true);
        ImGui::InputText(std::format("Message {}/50:", sizeof(message)).c_str(), &message, 50);
        ImGui::SameLine();
        if (ImGui::Button("Send"))
            userchat("username", &message); //send chat logic
        ImGui::EndChild();
    }
}