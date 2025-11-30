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
		CHAT,
		CHANGELOG,
		FAQ,
		SETTINGS
	};

	enum egame : uint32_t
	{
		//mono
		LETHAL_COMPANY,
		CONTENT_WARNING,
		REPO,
		GTAG,
		//dll
		GTAV,
		//PHASMOPHOBIA
	};

	struct Image
	{
		int size[2] = { 0, 0 };
		ID3D11ShaderResourceView* view = nullptr;
	};

	inline class gui
	{
	public:
		std::string_view game_to_name(egame tab)
		{
			switch (tab)
			{
				case LETHAL_COMPANY: return "Lethal Company";
				case CONTENT_WARNING: return "Content Warning";
				case REPO: return "R.E.P.O";
				case GTAG: return "Gorilla Tag";
				case GTAV: return "GTAV";
				default: return "NULL";
			}
		}

		std::string_view tab_to_name(etab tab)
		{
			switch (tab)
			{
				case HOME: return "Home";
				case CHAT: return "Chat";
				case CHANGELOG: return "Changelog";
				case FAQ: return "FAQ";
				case SETTINGS: return "Settings";
				default: return "NULL";
			}
		}

		const char* get_tab_icon(etab tab)
		{
			switch (tab)
			{
			case HOME: return ICON_FA_HOME;
			case CHAT: return ICON_FA_BIOHAZARD;
			case CHANGELOG: return ICON_FA_BOOK;
			case FAQ: return ICON_FA_QUESTION_CIRCLE;
			case SETTINGS: return ICON_FA_COG;
			default: return "NULL";
			}
		}

		void initialize();
		void render();

		void home_tab();
		void chat_tab();
		void changelog_tab();
		void faq_tab();
		void settings_tab();

		bool load_texture_from_file(const char* path, ID3D11Device* d3dDevice, Image** image);

		ImVec2 size = { 800, 600 };
		egame game;
		etab tab;
		ImFont* default_font;
		ImFont* segoeui_font_20px;
		ImFont* segoeui_font_25px;
		ImFont* segoeui_font_30px;
		ImFont* segoeui_font_35px;
		ImFont* segoeui_font_40px;
		std::vector<Image*> unkimages;
		Image* icon;
		Image* gta_icon;
		Image* gta_background;
		Image* repo_icon;
		Image* content_warning_icon;
		Image* lethal_company_icon;

		//debug
		float x = 200, y = 305, custom_float = 40;
	} g_gui;
}