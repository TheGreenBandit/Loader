#pragma once
#include "../common.hpp"

namespace loader
{
	class logger
	{
	public:
		void log(std::string string);
		void clear_log();
	};
	inline logger g_logger;
}