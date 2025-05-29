#pragma once

#include "../common.hpp"

namespace loader
{
	inline class message_system
	{
		std::vector<std::string> messages;
		std::chrono::system_clock::time_point last_sent = std::chrono::system_clock::now();
	public:
		void loop();
		void update_messages();
	public:
		void send_message(std::string_view message);
		void display_messages();
	} g_message_system;
}