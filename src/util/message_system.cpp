#include "message_system.hpp"

namespace loader
{
	void message_system::loop()
	{
		std::thread([&] {
			while (true)
			{
				clear_messages();
				std::this_thread::sleep_for(1s);
			}
			}).detach();
	}

	void message_system::clear_messages()
	{
		if (messages.size() > 500)//make me go off a file or something
			messages.clear();
	}

	void message_system::send_message(std::string_view message)
	{
		if (message.size() < 50)
			messages.push_back(std::format("{} {} {}", ICON_FA_USER, util::get_username().data(), message.data()));
	}

	void message_system::display_messages()
	{
		for (auto message : messages)
		{
			if (message.find("tgb") != std::string::npos) //dev thing, yes it is important
			{
				ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyleColorVec4(ImGuiCol_Button));
				ImGui::TextWrapped(message.c_str());
				ImGui::PopStyleColor();
			}
			else
				ImGui::TextWrapped(message.c_str());
		}
	}
}