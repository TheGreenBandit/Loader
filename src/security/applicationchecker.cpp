#include "applicationchecker.hpp"
#include "../common.hpp"

namespace loader
{
	void security::loop()
	{
		checkforprocesses();
	}

	void security::checkforprocesses()
	{
		for (auto name : windownames)
			if (FindWindowW(NULL, (LPCWSTR)name))
				exit(0);
	}
}