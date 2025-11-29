#include "gui.hpp"
#include "../common.hpp"
#include "../util/util.hpp"
#include "../util/gui_util.hpp"

#include <d3d11.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../widgets/stb_image.h"
#include "../util/injection.hpp"
#include <windows.h>
#include <iostream>
#include <Windows.System.UserProfile.h>

using namespace ABI::Windows::System::UserProfile;

namespace loader
{
    void updatecolstyl()
    {

        auto& style = ImGui::GetStyle();
        style.WindowPadding = { g.gui.style.WindowPadding[0], g.gui.style.WindowPadding[1] };
        style.PopupRounding = g.gui.style.PopupRounding;
        style.FramePadding = { g.gui.style.FramePadding[0], g.gui.style.FramePadding[1] };
        style.ItemSpacing = { g.gui.style.ItemSpacing[0], g.gui.style.ItemSpacing[1] };
        style.ItemInnerSpacing = { g.gui.style.ItemInnerSpacing[0], g.gui.style.ItemInnerSpacing[1] };
        style.TouchExtraPadding = { g.gui.style.TouchExtraPadding[0], g.gui.style.TouchExtraPadding[1] };
        style.IndentSpacing = g.gui.style.IndentSpacing;
        style.ScrollbarSize = g.gui.style.ScrollbarSize;
        style.GrabMinSize = g.gui.style.GrabMinSize;
        style.WindowBorderSize = g.gui.style.WindowBorderSize;
        style.ChildBorderSize = g.gui.style.ChildBorderSize;
        style.PopupBorderSize = g.gui.style.PopupBorderSize;
        style.FrameBorderSize = g.gui.style.FrameBorderSize;
        style.TabBorderSize = g.gui.style.TabBorderSize;
        style.WindowRounding = g.gui.style.WindowRounding;
        style.ChildRounding = g.gui.style.ChildRounding;
        style.FrameRounding = g.gui.style.FrameRounding;
        style.ScrollbarRounding = g.gui.style.ScrollbarRounding;
        style.GrabRounding = g.gui.style.GrabRounding;
        style.TabRounding = g.gui.style.TabRounding;
        style.WindowTitleAlign = { g.gui.style.WindowTitleAlign[0], g.gui.style.WindowTitleAlign[1] };
        style.ButtonTextAlign = { g.gui.style.ButtonTextAlign[0], g.gui.style.ButtonTextAlign[1] };
        style.DisplaySafeAreaPadding = { g.gui.style.DisplaySafeAreaPadding[0], g.gui.style.DisplaySafeAreaPadding[1] };

        auto& colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_Text] = { g.gui.color.Text[0], g.gui.color.Text[1], g.gui.color.Text[2], g.gui.color.Text[3] };
        colors[ImGuiCol_TextDisabled] = { g.gui.color.TextDisabled[0], g.gui.color.TextDisabled[1], g.gui.color.TextDisabled[2], g.gui.color.TextDisabled[3] };
        colors[ImGuiCol_WindowBg] = { g.gui.color.WindowBg[0], g.gui.color.WindowBg[1], g.gui.color.WindowBg[2], g.gui.color.WindowBg[3] };
        colors[ImGuiCol_ChildBg] = { g.gui.color.ChildBg[0], g.gui.color.ChildBg[1], g.gui.color.ChildBg[2], g.gui.color.ChildBg[3] };
        colors[ImGuiCol_Border] = { g.gui.color.Border[0], g.gui.color.Border[1], g.gui.color.Border[2], g.gui.color.Border[3] };
        colors[ImGuiCol_BorderShadow] = { g.gui.color.BorderShadow[0], g.gui.color.BorderShadow[1], g.gui.color.BorderShadow[2], g.gui.color.BorderShadow[3] };
        colors[ImGuiCol_FrameBg] = { g.gui.color.FrameBg[0], g.gui.color.FrameBg[1], g.gui.color.FrameBg[2], g.gui.color.FrameBg[3] };
        colors[ImGuiCol_FrameBgHovered] = { g.gui.color.FrameBgHovered[0], g.gui.color.FrameBgHovered[1], g.gui.color.FrameBgHovered[2], g.gui.color.FrameBgHovered[3] };
        colors[ImGuiCol_FrameBgActive] = { g.gui.color.FrameBgActive[0], g.gui.color.FrameBgActive[1], g.gui.color.FrameBgActive[2], g.gui.color.FrameBgActive[3] };
        colors[ImGuiCol_TitleBg] = { g.gui.color.TitleBg[0], g.gui.color.TitleBg[1], g.gui.color.TitleBg[2], g.gui.color.TitleBg[3] };
        colors[ImGuiCol_TitleBgActive] = { g.gui.color.TitleBgCollapsed[0], g.gui.color.TitleBgCollapsed[1], g.gui.color.TitleBgCollapsed[2], g.gui.color.TitleBgCollapsed[3] };
        colors[ImGuiCol_TitleBgCollapsed] = { g.gui.color.TitleBgCollapsed[0], g.gui.color.TitleBgCollapsed[1], g.gui.color.TitleBgCollapsed[2], g.gui.color.TitleBgCollapsed[3] };
        colors[ImGuiCol_MenuBarBg] = { g.gui.color.MenuBarBg[0], g.gui.color.MenuBarBg[1], g.gui.color.MenuBarBg[2], g.gui.color.MenuBarBg[3] };
        colors[ImGuiCol_ScrollbarBg] = { g.gui.color.ScrollbarBg[0], g.gui.color.ScrollbarBg[1], g.gui.color.ScrollbarBg[2], g.gui.color.ScrollbarBg[3] };
        colors[ImGuiCol_ScrollbarGrab] = { g.gui.color.ScrollbarGrab[0], g.gui.color.ScrollbarGrab[1], g.gui.color.ScrollbarGrab[2], g.gui.color.ScrollbarGrab[3] };
        colors[ImGuiCol_ScrollbarGrabHovered] = { g.gui.color.ScrollbarGrabHovered[0], g.gui.color.ScrollbarGrabHovered[1], g.gui.color.ScrollbarGrabHovered[2], g.gui.color.ScrollbarGrabHovered[3] };
        colors[ImGuiCol_ScrollbarGrabActive] = { g.gui.color.ScrollbarGrabActive[0], g.gui.color.ScrollbarGrabActive[1], g.gui.color.ScrollbarGrabActive[2], g.gui.color.ScrollbarGrabActive[3] };
        colors[ImGuiCol_CheckMark] = { g.gui.color.CheckMark[0], g.gui.color.CheckMark[1], g.gui.color.CheckMark[2], g.gui.color.CheckMark[3] };
        colors[ImGuiCol_SliderGrab] = { g.gui.color.SliderGrab[0], g.gui.color.SliderGrab[1], g.gui.color.SliderGrab[2], g.gui.color.SliderGrab[3] };
        colors[ImGuiCol_SliderGrabActive] = { g.gui.color.SliderGrabActive[0], g.gui.color.SliderGrabActive[1], g.gui.color.SliderGrabActive[2], g.gui.color.SliderGrabActive[3] };
        colors[ImGuiCol_Button] = { g.gui.color.Button[0], g.gui.color.Button[1], g.gui.color.Button[2], g.gui.color.Button[3] };
        colors[ImGuiCol_ButtonHovered] = { g.gui.color.ButtonHovered[0], g.gui.color.ButtonHovered[1], g.gui.color.ButtonHovered[2], g.gui.color.ButtonHovered[3] };
        colors[ImGuiCol_ButtonActive] = { g.gui.color.ButtonActive[0], g.gui.color.ButtonActive[1], g.gui.color.ButtonActive[2], g.gui.color.ButtonActive[3] };
        colors[ImGuiCol_Header] = { g.gui.color.Header[0], g.gui.color.Header[1], g.gui.color.Header[2], g.gui.color.Header[3] };
        colors[ImGuiCol_HeaderHovered] = { g.gui.color.HeaderHovered[0], g.gui.color.HeaderHovered[1], g.gui.color.HeaderHovered[2], g.gui.color.HeaderHovered[3] };
        colors[ImGuiCol_HeaderActive] = { g.gui.color.HeaderActive[0], g.gui.color.HeaderActive[1], g.gui.color.HeaderActive[2], g.gui.color.HeaderActive[3] };
        colors[ImGuiCol_Separator] = { g.gui.color.Separator[0], g.gui.color.Separator[1], g.gui.color.Separator[2], g.gui.color.Separator[3] };
        colors[ImGuiCol_SeparatorHovered] = { g.gui.color.SeparatorHovered[0], g.gui.color.SeparatorHovered[1], g.gui.color.SeparatorHovered[2], g.gui.color.SeparatorHovered[3] };
        colors[ImGuiCol_SeparatorActive] = { g.gui.color.SeparatorActive[0], g.gui.color.SeparatorActive[1], g.gui.color.SeparatorActive[2], g.gui.color.SeparatorActive[3] };
        colors[ImGuiCol_ResizeGrip] = { g.gui.color.ResizeGrip[0], g.gui.color.ResizeGrip[1], g.gui.color.ResizeGrip[2], g.gui.color.ResizeGrip[3] };
        colors[ImGuiCol_ResizeGripHovered] = { g.gui.color.ResizeGripHovered[0], g.gui.color.ResizeGripHovered[1], g.gui.color.ResizeGripHovered[2], g.gui.color.ResizeGripHovered[3] };
        colors[ImGuiCol_ResizeGripActive] = { g.gui.color.ResizeGripActive[0], g.gui.color.ResizeGripActive[1], g.gui.color.ResizeGripActive[2], g.gui.color.ResizeGripActive[3] };
        colors[ImGuiCol_Tab] = { g.gui.color.Tab[0], g.gui.color.Tab[1], g.gui.color.Tab[2], g.gui.color.Tab[3] };
        colors[ImGuiCol_TabHovered] = { g.gui.color.TabHovered[0], g.gui.color.TabHovered[1], g.gui.color.TabHovered[2], g.gui.color.TabHovered[3] };
        colors[ImGuiCol_TabActive] = { g.gui.color.TabActive[0], g.gui.color.TabActive[1], g.gui.color.TabActive[2], g.gui.color.TabActive[3] };
        colors[ImGuiCol_TabUnfocused] = { g.gui.color.TabUnfocused[0], g.gui.color.TabUnfocused[1], g.gui.color.TabUnfocused[2], g.gui.color.TabUnfocused[3] };
        colors[ImGuiCol_TabUnfocusedActive] = { g.gui.color.TabUnfocusedActive[0], g.gui.color.TabUnfocusedActive[1], g.gui.color.TabUnfocusedActive[2], g.gui.color.TabUnfocusedActive[3] };
        colors[ImGuiCol_PlotLines] = { g.gui.color.PlotLines[0], g.gui.color.PlotLines[1], g.gui.color.PlotLines[2], g.gui.color.PlotLines[3] };
        colors[ImGuiCol_PlotLinesHovered] = { g.gui.color.PlotLinesHovered[0], g.gui.color.PlotLinesHovered[1], g.gui.color.PlotLinesHovered[2], g.gui.color.PlotLinesHovered[3] };
        colors[ImGuiCol_PlotHistogram] = { g.gui.color.PlotHistogram[0], g.gui.color.PlotHistogram[1], g.gui.color.PlotHistogram[2], g.gui.color.PlotHistogram[3] };
        colors[ImGuiCol_PlotHistogramHovered] = { g.gui.color.PlotHistogramHovered[0], g.gui.color.PlotHistogramHovered[1], g.gui.color.PlotHistogramHovered[2], g.gui.color.PlotHistogramHovered[3] };
        colors[ImGuiCol_TextSelectedBg] = { g.gui.color.TextSelectedBg[0], g.gui.color.TextSelectedBg[1], g.gui.color.TextSelectedBg[2], g.gui.color.TextSelectedBg[3] };
        colors[ImGuiCol_DragDropTarget] = { g.gui.color.DragDropTarget[0], g.gui.color.DragDropTarget[1], g.gui.color.DragDropTarget[2], g.gui.color.DragDropTarget[3] };
        colors[ImGuiCol_NavHighlight] = { g.gui.color.NavHighlight[0], g.gui.color.NavHighlight[1], g.gui.color.NavHighlight[2], g.gui.color.NavHighlight[3] };
        colors[ImGuiCol_NavWindowingHighlight] = { g.gui.color.NavWindowingHighlight[0], g.gui.color.NavWindowingHighlight[1], g.gui.color.NavWindowingHighlight[2], g.gui.color.NavWindowingHighlight[3] };
        colors[ImGuiCol_NavWindowingDimBg] = { g.gui.color.NavWindowingDimBg[0], g.gui.color.NavWindowingDimBg[1], g.gui.color.NavWindowingDimBg[2], g.gui.color.NavWindowingDimBg[3] };
        colors[ImGuiCol_ModalWindowDimBg] = { g.gui.color.ModalWindowDimBg[0], g.gui.color.ModalWindowDimBg[1], g.gui.color.ModalWindowDimBg[2], g.gui.color.ModalWindowDimBg[3] };
    }

    void gui::initialize()
    {
        ImVec4* colors = ImGui::GetStyle().Colors;
        {
            colors[ImGuiCol_WindowBg] = ImVec4(0.03f, 0.03f, 0.03f, 1.00f);   // near black
            colors[ImGuiCol_ChildBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);   // dark grey/black
            colors[ImGuiCol_Border] = ImVec4(0.10f, 0.30f, 0.10f, 1.00f);   // subtle green tint

            colors[ImGuiCol_FrameBg] = ImColor(20, 20, 20, 255);
            colors[ImGuiCol_FrameBgHovered] = ImColor(15, 40, 15, 255);             // dark green hover
            colors[ImGuiCol_FrameBgActive] = ImVec4(0.0f, 0.9f, 0.2f, 1.f);        // bright green

            // Buttons
            colors[ImGuiCol_Button] = ImVec4(0.0f, 0.7f, 0.15f, 1.f);       // green
            colors[ImGuiCol_ButtonHovered] = ImVec4(0.0f, 0.85f, 0.25f, 1.f);      // lighter green
            colors[ImGuiCol_ButtonActive] = ImVec4(0.0f, 1.0f, 0.30f, 1.f);       // neon green

            // Text / selection
            colors[ImGuiCol_TextSelectedBg] = ImVec4(0.0f, 0.9f, 0.25f, 1.f);
            colors[ImGuiCol_TextDisabled] = ImVec4(0.30f, 0.40f, 0.30f, 1.00f);
            colors[ImGuiCol_CheckMark] = ImVec4(0.0f, 1.0f, 0.30f, 1.f);
        }

        ImGuiStyle* style = &ImGui::GetStyle();
        {
            style->WindowPadding = ImVec2(14, 14);
            style->WindowBorderSize = 10.f;
            style->WindowRounding = 15.f;

            style->FramePadding = ImVec2(6, 6);
            style->FrameRounding = 3.f;
            style->FrameBorderSize = 2.f;

            style->ChildBorderSize = 1.f;
            style->ChildRounding = 5.f;
        }

    }

    const char* games[5]
    {
        "Lethal Company",
        "Content Warning",
        "R.E.P.O",
        "Gorilla Tag",
        "GTAV"
    };
    //temp, needa get paddding working on the left main child
    inline void adjust()
    {
        auto p = ImGui::GetCursorPos();
        ImGui::SetCursorPos(ImVec2(p.x + 5, p.y));
    }

    void game_select_button(egame game)
    {
        //ImGui::ImageButton
    }

    void gui::render()
    {
        updatecolstyl();
        if (loader::active)
        {
            if (ImGui::Begin("Blade", &active, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar))
            {
                static char search;//feature search
                g_logger.log("b1");
                ImGui::Image(icon->view, ImVec2(50, 50));
                ImGui::SameLine();
                g_gui.segoeui_font->FontSize = 10;
                ImGui::TextColored(ImVec4(0, 255, 0, 255), "Blade");
                ImGui::SameLine();
                ImGui::Text("Menu");
                g_gui.segoeui_font->FontSize = 20;
                ImGui::SameLine();
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
                ImGui::BeginGroup();
                //ImGui::PushStyleVar(ImGuiStyleVar_::, ImVec2(5, 20)); todo figure out way to center
                ImGui::Text(ICON_FA_SEARCH);
                ImGui::SameLine();
                ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - 70);
                ImGui::InputTextWithHint("", "Search...", &search, sizeof(search) + 1);
                ImGui::SameLine();
                if (ImGui::Button(ICON_FA_COGS))
                    active = false;
                ImGui::SameLine();
                if (ImGui::Button("X"))
                    active = false;
                ImGui::EndGroup();
                ImGui::Separator();
                ImGui::Text("stuff");
                ImGui::End();
            }

            if (ImGui::Begin("debug menu", &active))
            {
                static int menu_select = 0;
                if (ImGui::Button("STYLE"))
                    menu_select = 0;
                ImGui::SameLine();
                if (ImGui::Button("COLOR"))
                    menu_select = 1;
                ImGui::Separator();
                if (!menu_select)
                {
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputFloat2("WindowPadding", g.gui.style.WindowPadding, "%.1f");
                    ImGui::InputFloat("PopupRounding", &g.gui.style.PopupRounding);
                    ImGui::InputFloat2("FramePadding", g.gui.style.FramePadding);
                    ImGui::InputFloat2("ItemSpacing", g.gui.style.ItemSpacing);
                    ImGui::InputFloat2("ItemInnerSpacing", g.gui.style.ItemInnerSpacing);
                    ImGui::InputFloat2("TouchExtraPadding", g.gui.style.TouchExtraPadding);
                    ImGui::InputFloat("IndentSpacing", &g.gui.style.IndentSpacing);
                    ImGui::InputFloat("ScrollbarSize", &g.gui.style.ScrollbarSize);
                    ImGui::InputFloat("GrabMinSize", &g.gui.style.GrabMinSize);
                    ImGui::InputFloat("WindowBorderSize", &g.gui.style.WindowBorderSize);
                    ImGui::InputFloat("ChildBorderSize", &g.gui.style.ChildBorderSize);
                    ImGui::InputFloat("PopupBorderSize", &g.gui.style.PopupBorderSize);
                    ImGui::InputFloat("FrameBorderSize", &g.gui.style.FrameBorderSize);
                    ImGui::InputFloat("TabBorderSize", &g.gui.style.TabBorderSize);
                    ImGui::InputFloat("WindowRounding", &g.gui.style.WindowRounding);
                    ImGui::InputFloat("ChildRounding", &g.gui.style.ChildRounding);
                    ImGui::InputFloat("FrameRounding", &g.gui.style.FrameRounding);
                    ImGui::InputFloat("ScrollbarRounding", &g.gui.style.ScrollbarRounding);
                    ImGui::InputFloat("GrabRounding", &g.gui.style.GrabRounding);
                    ImGui::InputFloat("TabRounding", &g.gui.style.TabRounding);
                    ImGui::InputFloat2("WindowTitleAlign", g.gui.style.WindowTitleAlign);
                    ImGui::InputFloat2("ButtonTextAlign", g.gui.style.ButtonTextAlign);
                    ImGui::InputFloat2("DisplaySafeAreaPadding", g.gui.style.DisplaySafeAreaPadding);
                }
                else
                {
                    ImGui::Text("color bs");
                    ImGui::InputFloat4("text", g.gui.color.Text);
                    ImGui::InputFloat4("textdisabled", g.gui.color.TextDisabled);
                    ImGui::InputFloat4("window bg", g.gui.color.WindowBg);
                    ImGui::InputFloat4("child bg", g.gui.color.ChildBg);
                    ImGui::InputFloat4("PopupBg", g.gui.color.PopupBg);
                    ImGui::InputFloat4("Border", g.gui.color.Border);
                    ImGui::InputFloat4("BorderShadow", g.gui.color.BorderShadow);
                    ImGui::InputFloat4("FrameBg", g.gui.color.FrameBg);
                    ImGui::InputFloat4("FrameBgHovered", g.gui.color.FrameBgHovered);
                    ImGui::InputFloat4("FrameBgActive", g.gui.color.FrameBgActive);
                    ImGui::InputFloat4("TitleBg", g.gui.color.TitleBg);
                    ImGui::InputFloat4("TitleBgActive", g.gui.color.TitleBgActive);
                    ImGui::InputFloat4("TitleBgCollapsed", g.gui.color.TitleBgCollapsed);
                    ImGui::InputFloat4("MenuBarBg", g.gui.color.MenuBarBg);
                    ImGui::InputFloat4("ScrollbarBg", g.gui.color.ScrollbarBg);
                    ImGui::InputFloat4("ScrollbarGrab", g.gui.color.ScrollbarGrab);
                    ImGui::InputFloat4("ScrollbarGrabHovered", g.gui.color.ScrollbarGrabHovered);
                    ImGui::InputFloat4("ScrollbarGrabActive", g.gui.color.ScrollbarGrabActive);
                    ImGui::InputFloat4("CheckMark", g.gui.color.CheckMark);
                    ImGui::InputFloat4("SliderGrab", g.gui.color.SliderGrab);
                    ImGui::InputFloat4("SliderGrabActive", g.gui.color.SliderGrabActive);
                    ImGui::InputFloat4("Button", g.gui.color.Button);
                    ImGui::InputFloat4("ButtonHovered", g.gui.color.ButtonHovered);
                    ImGui::InputFloat4("ButtonActive", g.gui.color.ButtonActive);
                    ImGui::InputFloat4("Header", g.gui.color.Header);
                    ImGui::InputFloat4("HeaderHovered", g.gui.color.HeaderHovered);
                    ImGui::InputFloat4("HeaderActive", g.gui.color.HeaderActive);
                    ImGui::InputFloat4("Separator", g.gui.color.Separator);
                    ImGui::InputFloat4("SeparatorHovered", g.gui.color.SeparatorHovered);
                    ImGui::InputFloat4("SeparatorActive", g.gui.color.SeparatorActive);
                    ImGui::InputFloat4("ResizeGrip", g.gui.color.ResizeGrip);
                    ImGui::InputFloat4("ResizeGripHovered", g.gui.color.ResizeGripHovered);
                    ImGui::InputFloat4("ResizeGripActive", g.gui.color.ResizeGripActive);
                    ImGui::InputFloat4("Tab", g.gui.color.Tab);
                    ImGui::InputFloat4("TabHovered", g.gui.color.TabHovered);
                    ImGui::InputFloat4("TabActive", g.gui.color.TabActive);
                    ImGui::InputFloat4("TabUnfocused", g.gui.color.TabUnfocused);
                    ImGui::InputFloat4("TabUnfocusedActive", g.gui.color.TabUnfocusedActive);
                    ImGui::InputFloat4("PlotLines", g.gui.color.PlotLines);
                    ImGui::InputFloat4("PlotLinesHovered", g.gui.color.PlotLinesHovered);
                    ImGui::InputFloat4("PlotHistogram", g.gui.color.PlotHistogram);
                    ImGui::InputFloat4("PlotHistogramHovered", g.gui.color.PlotHistogramHovered);
                    ImGui::InputFloat4("TextSelectedBg", g.gui.color.TextSelectedBg);
                    ImGui::InputFloat4("DragDropTarget", g.gui.color.DragDropTarget);
                    ImGui::InputFloat4("NavHighlight", g.gui.color.NavHighlight);
                    ImGui::InputFloat4("NavWindowingHighlight", g.gui.color.NavWindowingHighlight);
                    ImGui::InputFloat4("NavWindowingDimBg", g.gui.color.NavWindowingDimBg);
                    ImGui::InputFloat4("ModalWindowDimBg", g.gui.color.ModalWindowDimBg);
                }
                ImGui::End();
            }
            ImGui::SetNextWindowSize(size);
            if (ImGui::Begin(WINDOW_NAME, &active, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
            {
                ImGui::BeginChild("Top Row + Logo", ImVec2(size.x, 50));
                ImGui::Image(icon->view, ImVec2(50, 50));
                ImGui::SameLine();
                ImGui::Button("Home");
                ImGui::SameLine();
                ImGui::Button("Changelog");
                ImGui::SameLine();
                ImGui::Button("Chat");
                ImGui::SameLine();
                ImGui::Button("Settings");
                ImGui::SameLine();
                ImGui::Button("X");
                ImGui::EndChild();
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
                ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Border , ImVec4(0, 0, 0, 0));
                ImGui::BeginGroup();
                ImGui::BeginChild("SideBar", ImVec2(50, size.y - 50));
                if (ImGui::ImageButton(g_gui.gta_icon->view, ImVec2(45, 45)))
                {
                    return;
                }
                ImGui::Button("REPO Logo");
                ImGui::Button("CONTENTW Logo");
                ImGui::Button("LC Logo");
                ImGui::PopStyleColor();
                ImGui::PopStyleVar();
                ImGui::EndChild();
                ImGui::EndGroup();

                ImGui::SameLine();

                ImGui::BeginGroup();
                //game background image https://imgs.search.brave.com/Gjz7rBGy5hALKJVl1mlkV7mGG9A-BUPE7Xob-jOXzcg/rs:fit:500:0:1:0/g:ce/aHR0cHM6Ly93YWxs/cGFwZXJjYXZlLmNv/bS93cC93cDc2NDQ4/MzUuanBn
                //launch button
                ImGui::EndGroup();
            }
            ImGui::End();
        }
        else
            exit(0);
    }

    bool gui::load_texture_from_file(const char* path, ID3D11Device* d3dDevice, Image** image) 
    {
        Image* ret = new Image();
        ret->size[0] = 0;
        ret->size[1] = 0;
        ret->view = nullptr;

        unsigned char* image_data = stbi_load(path, &ret->size[0], &ret->size[1], NULL, 4);
        if (image_data == NULL)
        {
            g_logger.log("FAILED TO LOAD IMAGE! Code 1");
            return false;
        } 
        // Create texture 
        D3D11_TEXTURE2D_DESC desc;
        ZeroMemory(&desc, sizeof(desc));
        desc.Width = ret->size[0];
        desc.Height = ret->size[1];
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        desc.CPUAccessFlags = 0;

        ID3D11Texture2D* pTexture = NULL;
        D3D11_SUBRESOURCE_DATA subResource;
        subResource.pSysMem = image_data;
        subResource.SysMemPitch = desc.Width * 4;
        subResource.SysMemSlicePitch = 0;
        d3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);

        // Create texture view 
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
        ZeroMemory(&srvDesc, sizeof(srvDesc));
        srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = desc.MipLevels;
        srvDesc.Texture2D.MostDetailedMip = 0;
        d3dDevice->CreateShaderResourceView(pTexture, &srvDesc, &ret->view);

        pTexture->Release();
        *image = ret;
        stbi_image_free(image_data); 
        return true; 
    }
}