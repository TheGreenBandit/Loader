#pragma once

#include "../common.hpp"

namespace loader
{
	inline class discord_util
	{
		bool rpc_enabled = true;
		std::string webhook = "none";
	public:
        discord_util();
        ~discord_util();

		void send_message(std::string_view message);
		void send_bot_message(const std::string& channel_id, const std::string& message);
		std::vector<std::string> read_channel_messages(const std::string& channel_id);

		void update();
		
	} discord_util;
}