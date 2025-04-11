#pragma once

#include "Library/include/discord_rpc.h"
#include "Library/include/discord_register.h"

namespace base {
	inline std::chrono::system_clock::time_point g_injectionTime{ std::chrono::system_clock::now() };
	class discordRPC {
	public:
		void init();
		void uninit();
	public:
		static void joinGame(const char* joinSecret);
		static void spectateGame(const char* spectateSecret);
		static void joinRequest(const DiscordJoinRequest* request);
	public:
		void respondToRequest(std::pair<uint64_t, DiscordJoinRequest> request, uint32_t type);
	public:
		std::string getMatchData();
		std::string getState();
		std::string getModuleType();
		void update();
	public:
		static void fiber();
	public:
		std::map<uint64_t, DiscordJoinRequest> m_requests{};
		bool m_joinButton{ true };
		bool m_active{ true };
		uint64_t m_joinId{};
		DiscordEventHandlers m_handlers{};
		DiscordRichPresence m_presence{};
	};
	inline discordRPC g_discordRPC{};
}