#pragma once

#include "../common.hpp"

namespace loader
{
	inline class discord_util
	{
		bool rpc_enabled = true;
		std::string webhook = "none";
	public:;
		void send_bot_message(const std::string& channel_id, const std::string& message);
		std::vector<std::string> read_channel_messages(const std::string& channel_id);		
	} discord_util;
}