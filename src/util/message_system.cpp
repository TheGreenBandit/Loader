#include "message_system.hpp"
#include "discord_util.hpp"

namespace loader
{
	void message_system::loop()
	{
		std::thread([&] {
			while (true)
			{
				update_messages();
				std::this_thread::sleep_for(1s);
			}
			}).detach();
	}

	void message_system::update_messages()
	{
		auto raw = discord_util.read_channel_messages(CHANNEL_ID, BOT_TOKEN);
		std::reverse(raw.begin(), raw.end());
		messages = raw;
	}

	void message_system::send_message(std::string_view message)
	{
		std::string user = std::string(util::get_username().data());
		auto now = std::chrono::system_clock::now();
		g_logger.log("checking size");
		if (message.size() < 50)
		{
			g_logger.log(std::string("sending message: ") + message.data());
			if (user != "TGB")
			{
				if ((now - last_sent) <= 5s)
				{
					g_logger.log("ratelimit hit");
					return;
				}			
			}
				
			last_sent = now;
			std::time_t now_time = std::chrono::system_clock::to_time_t(now);
			struct tm time_info;
			localtime_s(&time_info, &now_time);  // thread-safe version
			char time_str[32];
			strftime(time_str, sizeof(time_str), "%H:%M:%S", &time_info);

			std::string formatted_message = std::format("[{}] {}: {}", time_str, user, message);//temp fix for username 
			g_logger.log(formatted_message);
			discord_util.send_bot_message(CHANNEL_ID, BOT_TOKEN, formatted_message);
			g_logger.log("message should be sent");
		}
	}

	void message_system::display_messages()
	{
		for (auto message : messages)
		{
			if (message.find("TGB") != std::string::npos) //dev thing, yes it is important
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