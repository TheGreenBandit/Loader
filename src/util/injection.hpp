#pragma once
#include "../common.hpp"
#include "../gui/gui.hpp"
//#include "../../includes/BlackBone/src/BlackBone/Process/RPC/RemoteFunction.hpp"
//#include "../../includes/BlackBone/src/BlackBone/Process/Process.h"

namespace fs = std::filesystem;

namespace loader
{
	inline class injection
	{
	public:
		void auto_inject();
		void inject();
		void mono_inject(etab tab);
		void inject_dll(etab tab, std::string_view npath = "", std::string_view nwindow = "");
	} g_inject;
}