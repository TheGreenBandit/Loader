#pragma once

#include "../common.hpp"
#include <d3d11.h>

namespace loader 
{
	//data
	static ID3D11Device* g_pd3dDevice = nullptr;
	static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
	static IDXGISwapChain* g_pSwapChain = nullptr;
	static bool g_SwapChainOccluded = false;
	static UINT g_ResizeWidth = 0, g_ResizeHeight = 0;
	static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

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
		int size[2] = { 0, 0 };
		ID3D11ShaderResourceView* view = nullptr;
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

		bool load_texture_from_file(const char* path, ID3D11Device* d3dDevice, Image** image);

		etab tab;
		ImFont* default_font;
		ImFont* segoeui_font;
		std::vector<Image*> unkimages;
		Image* icon;
		Image* unkself;


	} g_gui;
}