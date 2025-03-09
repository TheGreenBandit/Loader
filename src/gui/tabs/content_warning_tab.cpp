#include "../gui.hpp"
#include "../../util/injection.hpp"

namespace loader
{
    void gui::content_warning_tab()
	{
        if (ImGui::Button("Load Menu"))
            g_inject.inject();
        if (ImGui::Button("Launch Game"))
            ShellExecuteA(0, "open", "steam://rungameid/2881650", 0, 0, SW_HIDE);
	}
}