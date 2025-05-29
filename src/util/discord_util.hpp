#pragma once

#include "../common.hpp"

#include "../../includes/Discord/Library/include/discord_register.h"
#include "../../includes/Discord/Library/include/discord_rpc.h"

extern DISCORD_EXPORT void Discord_Initialize(const char* applicationId,
	DiscordEventHandlers* handlers,
	int autoRegister,
	const char* optionalSteamId);

namespace loader
{
	inline class discord_util
	{
		bool rpc_enabled = true;
		DiscordEventHandlers handlers;
		DiscordRichPresence presence;
		std::string webhook = "none";
	public:
        discord_util();
        ~discord_util();

		void send_message(std::string_view message);
		void send_bot_message(const std::string& channel_id, const std::string& bot_token, const std::string& message);
		std::vector<std::string> read_channel_messages(const std::string& channel_id, const std::string& bot_token);

		void update();
		void update_rpc();
		
	} discord_util;
}