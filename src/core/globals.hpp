#pragma once
#include "../../includes/json/json.hpp"

namespace loader
{
	struct globals
	{
		globals();

		struct gtav
		{
			const char* alternate_path = "";
		} gtav;

		struct auto_inject
		{
			bool gtav = false;
			bool content_warning = false;
			bool lethal_company = false;
			bool phasmophobia = false;
			//NLOHMANN_DEFINE_TYPE_INTRUSIVE(auto_inject, gtav, content_warning, lethal_company, phasmophobia)
		} auto_inject;
		bool auto_close = false;
		//NLOHMANN_DEFINE_TYPE_INTRUSIVE(globals, auto_inject)
	};
	static globals g;
}