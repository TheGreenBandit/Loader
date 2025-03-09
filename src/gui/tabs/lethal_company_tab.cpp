#include "../gui.hpp"
#include <format>
#include <filesystem>
#include "../../util/gui_util.hpp"
#include "../../util/injection.hpp"

namespace fs = std::filesystem;

namespace loader
{
	void gui::lethal_company_tab()
	{
        if (ImGui::Button("Load Menu"))
            g_inject.inject();
        if (ImGui::Button("Launch Game"))
            ShellExecuteA(0, "open", "steam://rungameid/1966720", 0, 0, SW_HIDE);

	}
}