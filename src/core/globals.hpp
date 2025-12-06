#pragma once
#include "nlohmann/json.hpp"

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
			bool repo = false;
			//NLOHMANN_DEFINE_TYPE_INTRUSIVE(auto_inject, gtav, content_warning, lethal_company, phasmophobia)
		} auto_inject;
		bool auto_close = false;
		std::chrono::system_clock::time_point start_time = std::chrono::system_clock::now();
		//NLOHMANN_DEFINE_TYPE_INTRUSIVE(globals, auto_inject)

		struct gui
		{
			float size = 1.f;
			bool info = false;
			float fontscale = 1.f;
			struct style
			{
				float WindowPadding[2] = { 5.f, 5.f };
				float PopupRounding = 1.f;
				float FramePadding[2] = { 6.f, 4.f };
				float ItemSpacing[2] = { 5.f, 5.f };
				float ItemInnerSpacing[2] = { 10.f, 6.f };
				float TouchExtraPadding[2] = { 0.f, 0.f };
				float IndentSpacing = 1.f;
				float ScrollbarSize = 5.f;
				float GrabMinSize = 2.f;
				float WindowBorderSize = 1.f;
				float ChildBorderSize = 1.f;
				float PopupBorderSize = 1.f;
				float FrameBorderSize = 1.f;
				float TabBorderSize = 1.f;
				float WindowRounding = 0.f;
				float ChildRounding = 5.f;
				float FrameRounding = 30.f;
				float ScrollbarRounding = 10.f;
				float GrabRounding = 10.f;
				float TabRounding = 1.f;
				float WindowTitleAlign[2] = { 0.f, 0.5f };
				float ButtonTextAlign[2] = { 0.5f, 0.65f };
				float DisplaySafeAreaPadding[2] = { 3.f, 3.f };

				/*NLOHMANN_DEFINE_TYPE_INTRUSIVE(style, WindowPadding, PopupRounding, FramePadding, ItemSpacing, ItemInnerSpacing, TouchExtraPadding,
					IndentSpacing, ScrollbarSize, GrabMinSize, WindowBorderSize, ChildBorderSize, PopupBorderSize,
					FrameBorderSize, TabBorderSize, WindowRounding, ChildRounding, FrameRounding, ScrollbarRounding, GrabRounding,
					TabRounding, WindowTitleAlign, ButtonTextAlign, DisplaySafeAreaPadding)*/
			} style{};

				struct color
				{
					bool Textr = false;
					bool TextDisabledr = false;
					bool WindowBgr = false;
					bool ChildBgr = false;
					bool PopupBgr = false;
					bool Borderr = false;
					bool BorderShadowr = false;
					bool FrameBgr = false;
					bool FrameBgHoveredr = false;
					bool FrameBgActiver = false;
					bool TitleBgr = false;
					bool TitleBgActiver = false;
					bool TitleBgCollapsedr = false;
					bool MenuBarBgr = false;
					bool ScrollbarBgr = false;
					bool ScrollbarGrabr = false;
					bool ScrollbarGrabHoveredr = false;
					bool ScrollbarGrabActiver = false;
					bool CheckMarkr = false;
					bool SliderGrabr = false;
					bool SliderGrabActiver = false;
					bool Buttonr = false;
					bool ButtonHoveredr = false;
					bool ButtonActiver = false;
					bool Headerr = false;
					bool HeaderHoveredr = false;
					bool HeaderActiver = false;
					bool Separatorr = false;
					bool SeparatorHoveredr = false;
					bool SeparatorActiver = false;
					bool ResizeGripr = false;
					bool ResizeGripHoveredr = false;
					bool ResizeGripActiver = false;
					bool Tabr = false;
					bool TabHoveredr = false;
					bool TabActiver = false;
					bool TabUnfocusedr = false;
					bool TabUnfocusedActiver = false;
					bool PlotLinesr = false;
					bool PlotLinesHoveredr = false;
					bool PlotHistogramr = false;
					bool PlotHistogramHoveredr = false;
					bool TextSelectedBgr = false;
					bool DragDropTargetr = false;
					bool NavHighlightr = false;
					bool NavWindowingHighlightr = false;
					bool NavWindowingDimBgr = false;
					bool ModalWindowDimBgr = false;

					float Text[4] = { 1.00f, 1.00f, 1.00f, 1.00f };
					float TextDisabled[4] = { 0.10f, 0.40f, 0.1f, 1.00f };
					float WindowBg[4] = { 0.f, 0.f, 0.f, .8f };
					float ChildBg[4] = { 0.05f, 0.05f, 0.05f, 1.00f };
					float PopupBg[4] = { 0.08f, 0.08f, 0.08f, 0.94f };
					float Border[4] = { 0.0f, 0.50f, 0.00f, 1.0f };
					float BorderShadow[4] = { 0.00f, 0.00f, 0.00f, 0.00f };
					float FrameBg[4] = { 0.21f, 0.21f, 0.21f, 0.54f };
					float FrameBgHovered[4] = { 0.21f, 0.21f, 0.21f, 0.78f };
					float FrameBgActive[4] = { 0.28f, 0.27f, 0.27f, 0.54f };
					float TitleBg[4] = { 0.17f, 0.17f, 0.17f, 1.00f };
					float TitleBgActive[4] = { 0.19f, 0.19f, 0.19f, 1.00f };
					float TitleBgCollapsed[4] = { 0.00f, 0.00f, 0.00f, 0.51f };
					float MenuBarBg[4] = { 0.14f, 0.14f, 0.14f, .07f };
					float ScrollbarBg[4] = { 0.02f, 0.02f, 0.02f, 0.53f };
					float ScrollbarGrab[4] = { 0.31f, 0.31f, 0.31f, 1.00f };
					float ScrollbarGrabHovered[4] = { 0.41f, 0.41f, 0.41f, 1.00f };
					float ScrollbarGrabActive[4] = { 0.51f, 0.51f, 0.51f, 1.00f };
					float CheckMark[4] = { 0.0f, 0.5f, 0.0f, 1.00f };
					float SliderGrab[4] = { 0.34f, 0.34f, 0.34f, 1.00f };
					float SliderGrabActive[4] = { 0.39f, 0.38f, 0.38f, 1.00f };
					float Button[4] = { 0.228f, 0.856f, 0.0f, 0.72f };
					float ButtonHovered[4] = { 0.6f, .8f, .6f, .72f };
					float ButtonActive[4] = { 0.5f, 0.7f, 0.5f, 0.72f };
					float Header[4] = { 0.37f, 0.37f, 0.37f, 0.31f };
					float HeaderHovered[4] = { 0.38f, 0.38f, 0.38f, 0.37f };
					float HeaderActive[4] = { 0.37f, 0.37f, 0.37f, 0.51f };
					float Separator[4] = { 0.38f, 0.38f, 0.38f, 0.50f };
					float SeparatorHovered[4] = { 0.46f, 0.46f, 0.46f, 0.50f };
					float SeparatorActive[4] = { 0.46f, 0.46f, 0.46f, 0.64f };
					float ResizeGrip[4] = { 0.26f, 0.26f, 0.26f, 1.00f };
					float ResizeGripHovered[4] = { 0.31f, 0.31f, 0.31f, 1.00f };
					float ResizeGripActive[4] = { 0.35f, 0.35f, 0.35f, 1.00f };
					float Tab[4] = { 0.21f, 0.21f, 0.21f, 0.86f };
					float TabHovered[4] = { 0.27f, 0.27f, 0.27f, 0.86f };
					float TabActive[4] = { 0.34f, 0.34f, 0.34f, 0.86f };
					float TabUnfocused[4] = { 0.10f, 0.10f, 0.10f, 0.97f };
					float TabUnfocusedActive[4] = { 0.15f, 0.15f, 0.15f, 1.00f };
					float PlotLines[4] = { 0.61f, 0.61f, 0.61f, 1.00f };
					float PlotLinesHovered[4] = { 1.00f, 0.43f, 0.35f, 1.00f };
					float PlotHistogram[4] = { 0.90f, 0.70f, 0.00f, 1.00f };
					float PlotHistogramHovered[4] = { 1.00f, 0.60f, 0.00f, 1.00f };
					float TextSelectedBg[4] = { 0.26f, 0.59f, 0.98f, 0.35f };
					float DragDropTarget[4] = { 1.00f, 1.00f, 0.00f, 0.90f };
					float NavHighlight[4] = { 0.26f, 0.59f, 0.98f, 1.00f };
					float NavWindowingHighlight[4] = { 1.00f, 1.00f, 1.00f, 0.70f };
					float NavWindowingDimBg[4] = { 0.80f, 0.80f, 0.80f, 0.20f };
					float ModalWindowDimBg[4] = { 0.80f, 0.80f, 0.80f, 0.35f };

					/*NLOHMANN_DEFINE_TYPE_INTRUSIVE(color, Text, TextDisabled, WindowBg, ChildBg, PopupBg, Border,
						BorderShadow, FrameBg, FrameBgHovered, FrameBgActive, TitleBg, TitleBgActive, TitleBgCollapsed,
						MenuBarBg, ScrollbarBg, ScrollbarGrab, ScrollbarGrabHovered, ScrollbarGrabActive, CheckMark,
						SliderGrab, SliderGrabActive, Button, ButtonHovered, ButtonActive, Header, HeaderHovered,
						HeaderActive, Separator, SeparatorHovered, SeparatorActive, ResizeGrip, ResizeGripHovered,
						ResizeGripActive, Tab, TabHovered, TabActive, TabUnfocused, TabUnfocusedActive, PlotLines,
						PlotLinesHovered, PlotHistogram, PlotHistogramHovered, TextSelectedBg, DragDropTarget,
						NavHighlight, NavWindowingHighlight, NavWindowingDimBg, ModalWindowDimBg)*/
				} color{};

					//NLOHMANN_DEFINE_TYPE_INTRUSIVE(gui, size, style, color, info)
		} gui{};
	};
	static globals g;
}