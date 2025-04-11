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
		std::string webhook = WEBHOOK;
	public:
        discord_util();
        ~discord_util();

		void send_message(std::string_view message);

		void update();
		void update_rpc();
		
	} discord_util;
}