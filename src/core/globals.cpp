#include "../common.hpp"

namespace loader
{
	globals::globals()//make seperate thread!! otherwisw will freeze
	{
		//std::ofstream file("loader.settings", std::ios::trunc);
		//nlohmann::json data = nlohmann::json::parse(file);
		while (active)
		{
			return;
			//if (file.is_open())
			{

			}
			//start saving all
		}
		//unload
	}
}