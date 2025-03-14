#pragma once

#include "../common.hpp"

namespace loader
{
	class message_system
	{
		void loop();
		void clear_messages();
	public:
		//i will manually remove the messages from the file once a week or so. or if reaches certain size
		std::vector<std::string> messages;
		
	public:

	};
}