#pragma once

#include "../common.hpp"
#include <d3d11.h>

namespace loader 
{
	enum etab : uint32_t
	{
		HOME,
		//mono
		LETHAL_COMPANY,
		CONTENT_WARNING,
		REPO,
		//dll
		GTAV,
		PHASMOPHOBIA,
		SETTINGS
	};

	struct Image
	{
		int x, y;
	};

	inline class gui
	{
	public:
		std::string_view tab_to_name(etab tab)
		{
			switch (tab)
			{
			case HOME: return "Home";
			case LETHAL_COMPANY: return "Lethal Company";
			case CONTENT_WARNING: return "Content Warning";
			case REPO: return "R.E.P.O";
			case SETTINGS: return "Settings";
			}
		}

		void initialize();
		void render();

		void home_tab();
		void content_warning_tab();
		void lethal_company_tab();
		void repo_tab();
		void settings_tab();

		bool load_texture_from_file(const char* path, ID3D11Device* d3dDevice, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);

		etab tab;
		ImFont* default_font;
		ImFont* segoeui_font;
		ID3D11ShaderResourceView* icon;
		Image icon_size = { 0, 0 };
	} g_gui;
}