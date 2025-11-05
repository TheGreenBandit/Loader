#pragma once

namespace loader
{
	inline class security
	{
	private:
		const char* windownames[1] = { "Cheat Engine 7.5" };
	public: 
		void loop();
		void checkforprocesses();
	} security;
	
}