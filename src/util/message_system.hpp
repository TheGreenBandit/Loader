#pragma once

#include "../common.hpp"

namespace loader
{
	inline class message_system
	{
		std::vector<std::string> messages;
	private:
		void loop();
		void clear_messages();

	public:
		
	public:
		void send_message(std::string_view message);
		void display_messages();
	} g_message_system;
}