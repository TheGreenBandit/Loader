#include "../gui.hpp"
#include "../../util/gui_util.hpp"
#include "../../util/message_system.hpp"
#include "../../util/discord_util.hpp"

namespace loader
{
    void gui::chat_tab()
    {
        static char message = ' ';
        ImGui::BeginChild("chatmain", ImVec2(530, 360), true);
        g_message_system.display_messages();      
        ImGui::EndChild();
        ImGui::Dummy(ImVec2(0, 20));
        ImGui::BeginChild("chatsender", ImVec2(530, 70), true);
        ImGui::InputText(std::format("Message {}/50:", "0"/*, std::string((&message)).size() this works but every time you type it boots you out of typing*/).c_str(), &message, 50);
        ImGui::SameLine();
        if (ImGui::Button("Send"))
            g_message_system.send_message(&message);
            
        ImGui::EndChild();
    }
}