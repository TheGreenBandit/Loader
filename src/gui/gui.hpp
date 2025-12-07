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
		GAMES,
		SETTINGS
	};

	enum egame : uint32_t
	{
		GTAV,
		//PHASMOPHOBIA maybe make menu for me, or minecraft java
		REPO,
		CONTENT_WARNING,
		LETHAL_COMPANY
	};

	struct Image
	{
		int size[2] = { 0, 0 };
		ID3D11ShaderResourceView* view = nullptr;
	};

	inline class gui
	{
	public:
		const char* games[4]
		{
			"GTAV",
			"R.E.P.O",
			"Content Warning",
			"Lethal Company"
		};
	public:
		void game_select_button(egame game)
		{
			if (ImGui::ImageButton(game_to_name(game).data(), game_to_icon(game)->view, ImVec2(45, 45)))
			{
				selected_img = 0;
				g_gui.game = game;
				tab = GAMES;
			}
		}

		Image* game_to_icon(egame game)
		{
			switch (game)
			{
				case GTAV: return icon_map.find("gta_icon")->second; break;
				case REPO: return icon_map.find("repo_icon")->second; break;
				case CONTENT_WARNING: return icon_map.find("content_warning_icon")->second; break;
				case LETHAL_COMPANY: return icon_map.find("lethal_company_icon")->second; break;
				default: return new Image();//
			}
			return new Image();//this should never happen but still catching it
		}

		Image* game_to_background(egame game)
		{
			switch (game)
			{
			case GTAV: return background_map.find("gta_background")->second; break;
			case REPO: return background_map.find("repo_background")->second; break;
			case CONTENT_WARNING: return background_map.find("content_warning_background")->second; break;
			case LETHAL_COMPANY: return background_map.find("lethal_company_background")->second; break;
			default: return new Image();//
			}
			return new Image();//this should never happen but still catching it
		}

		std::string_view game_to_name(egame tab)
		{
			switch (tab)
			{				
				case GTAV: return "GTAV";
				case REPO: return "R.E.P.O";
				case CONTENT_WARNING: return "Content Warning";
				case LETHAL_COMPANY: return "Lethal Company";

				default: return "NULL";
			}
		}

		void initialize();
		void render();

		void home_tab();
		void game_tab();
		void settings_tab();

		bool load_texture_from_file(fs::path path, ID3D11Device* d3dDevice, Image** image);

		int selected_img = 0;
		ImVec2 size = { 800, 600 };
		egame game;
		etab tab;
		ImVec4 accent_color;
		ImFont* default_font;
		ImFont* segoeui_font;
		std::vector<Image*> unkimages;
		std::map<std::string, Image*> icon_map;
		std::map<std::string, Image*> background_map;
		std::map<int, std::pair<std::string, Image*>> blade_map;
		std::map<int, std::pair<std::string, Image*>> unk_map;
		std::map<int, std::pair<std::string, Image*>> spooksuite_map;
		std::map<int, std::pair<std::string, Image*>> lethalmenu_map;
		//debug
		float x = 200, y = 415, custom_float = 40;
	} g_gui;
}