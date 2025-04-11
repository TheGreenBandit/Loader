#include "RPC.hpp"
#include "Features/Features.hpp"
#include "Util/Util.hpp"

namespace base {
	void discordRPC::init() {
		ZeroMemory(&m_handlers, sizeof(m_handlers));
		m_handlers.joinGame = &joinGame;
		m_handlers.spectateGame = &spectateGame;
		m_handlers.joinRequest = &joinRequest;
		Discord_Initialize(xorstr_("1055221243059642398"), &m_handlers, TRUE, nullptr);
	}
	void discordRPC::uninit() {
		for (auto& r : m_requests)
			respondToRequest(r, DISCORD_REPLY_NO);
		Discord_ClearPresence();
		Discord_Shutdown();
	}

	void discordRPC::joinGame(const char* joinSecret) {
		features::ridJoinSIAPE(std::stoull(joinSecret));
	}
	void discordRPC::spectateGame(const char* spectateSecret) {
		auto previousState = features::joinInsideSCTVSlots;
		features::joinInsideSCTVSlots = true;
		joinGame(spectateSecret);
		if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("maintransition"_joaat) != 0) {
			features::joinInsideSCTVSlots = previousState;
		}
	}
	void discordRPC::joinRequest(const DiscordJoinRequest* request) {
		g_discordRPC.m_requests.insert(std::make_pair(std::strtoull(request->userId, 0, 16), *request));
	}

	void discordRPC::respondToRequest(std::pair<uint64_t, DiscordJoinRequest> request, uint32_t type) {
		Discord_Respond(request.second.userId, type);
		m_requests.erase(request.first);
	}

	std::string discordRPC::getMatchData() {
		if (util::network::isSessionActive()) {
			return std::to_string(util::network::getHostCNetGamePlayer()->GetGamerInfo()->m_unk_gamer_handle.m_rockstar_id);
		}
		return std::string("NULL");
	}
	std::string discordRPC::getState() {
		if (util::network::isSessionActive()) {
			std::string sessionType{};
			std::string characterType{};
			std::string aliasValue{};
			if (NETWORK::NETWORK_SESSION_IS_SOLO())
				sessionType = xorstr_("Solo");
			else if (NETWORK::NETWORK_SESSION_IS_VISIBLE())
				sessionType = xorstr_("Public");
			else if (NETWORK::NETWORK_SESSION_IS_PRIVATE())
				sessionType = xorstr_("Private");
			else if (NETWORK::NETWORK_SESSION_IS_CLOSED_FRIENDS())
				sessionType = xorstr_("Closed Friends");
			else if (NETWORK::NETWORK_SESSION_IS_CLOSED_CREW())
				sessionType = xorstr_("Closed Crew");
			switch (util::ped::g_handle->m_model_info->m_model) {
			case "mp_f_freemode_01"_joaat: {
				characterType = xorstr_("female");
			} break;
			case "mp_m_freemode_01"_joaat: {
				characterType = xorstr_("male");
			} break;
			}
			aliasValue = features::spoofing::name.first.empty() ? util::player::g_networkHandle->GetName() : features::spoofing::name.first;
			return sessionType + xorstr_(" Session playing as a ") + characterType + xorstr_(" character under the alias ") + aliasValue;
		}
		else {
			std::string pedType{};
			rage::joaat_t model{};
			if (util::ped::g_handle && model != util::ped::g_handle->m_model_info->m_model) {
				model = util::ped::g_handle->m_model_info->m_model;
			}
			switch (model) {
			case "player_zero"_joaat: {
				pedType = xorstr_("Michael De Santa");
			} break;
			case "player_one"_joaat: {
				pedType = xorstr_("Franklin Clinton");
			} break;
			case "player_two"_joaat: {
				pedType = xorstr_("Trevor Philips");
			} break;
			}
			if (!pedType.empty())
				return xorstr_("Story Mode playing as ") + pedType;
		}
		return xorstr_("Story Mode");
	}
	std::string discordRPC::getModuleType() {
		std::string moduleKey{ "RGS" };
		if (GetModuleHandleA("EOSSDK-Win64-Shipping.dll")) {
			moduleKey = "EGS";
		}
		else if (GetModuleHandleA("steam_api64.dll")) {
			moduleKey = "Steam";
		}
		return xorstr_("Playing Grand Theft Auto V (") + moduleKey + xorstr_(")");
	}
	void discordRPC::update() {
		if (m_active) {
			ZeroMemory(&m_presence, sizeof(m_presence));
			stopwatch s{};
			bool onceEveryStateChange{};
			bool idle{ util::ped::g_handle ? util::ped::g_handle->get_speed() < 0.5f : true };
			std::string state{ std::format("{} in {}", idle ? "Idle" : "Roaming", getState()) };
			std::string details{ getModuleType() };
			m_presence.state = state.c_str();
			m_presence.details = details.c_str();
			m_presence.startTimestamp = std::chrono::system_clock::to_time_t(g_injectionTime);
			m_presence.endTimestamp = NULL;
			m_presence.largeImageKey = xorstr_("foxhead");
			m_presence.largeImageText = xorstr_("foxycheats.lol");
			m_presence.smallImageKey = NULL;
			m_presence.smallImageText = xorstr_("foxycheats.lol");
			if (util::network::isSessionActive() && util::player::g_networkHandle && util::player::g_handle && m_joinButton) {
				static auto str{ std::format("{}", util::player::g_networkHandle->m_player_id) };
				m_presence.partyId = str.c_str();
			}
			else {
				if (m_presence.partyId && strcmp(m_presence.partyId, ""))
					m_presence.partyId = NULL;
			}
			m_presence.partyId = NULL;
			m_presence.partySize = util::network::isSessionActive() ? util::network::getPlayerCount() : 0;
			m_presence.partyMax = util::network::isSessionActive() ? 32 : 0;
			/*m_presence.matchSecret = !getMatchData().compare(xorstr_("NULL")) ? getMatchData().c_str() : NULL;
			m_presence.spectateSecret = !getMatchData().compare(xorstr_("NULL")) ? getMatchData().c_str() : NULL;*/
			m_presence.matchSecret = NULL;
			m_presence.spectateSecret = NULL;
			if (util::network::isSessionActive())
				m_presence.joinSecret = m_presence.matchSecret;
			else
				m_presence.joinSecret = NULL;
			m_presence.instance = 1;
			Discord_UpdatePresence(&m_presence);
			Discord_UpdateHandlers(&m_handlers);
		}
		else {
			Discord_ClearPresence();
		}
		Discord_RunCallbacks();
	}
	void discordRPC::fiber() {
		g_discordRPC.init();
		while (true) {
			g_discordRPC.update();
			fiber::cur()->wait();
		}
	}
}