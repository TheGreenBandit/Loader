#include "gui.hpp"
#include "../common.hpp"
#include "../util/util.hpp"
#include "../util/gui_util.hpp"

#include <d3d11.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../widgets/stb_image.h"
#include "../util/injection.hpp"

namespace loader
{
    void gui::initialize()
    {
        ImVec4* colors = ImGui::GetStyle().Colors;
        {
            colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
            colors[ImGuiCol_ChildBg] = ImVec4(0.3f, 0.3f, 0.3f, 1.00f);
            colors[ImGuiCol_Border] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
            colors[ImGuiCol_FrameBg] = ImColor(50, 50, 50, 255);
            colors[ImGuiCol_FrameBgHovered] = ImColor(11, 11, 11, 255);
            colors[ImGuiCol_FrameBgActive] = ImVec4(0.228f, .8f, 0.2f, 255);
            colors[ImGuiCol_Button] = ImVec4(0.228f, .8f, 0.2f, 255);
            colors[ImGuiCol_ButtonActive] = ImVec4(0.328f, .9f, 0.3f, 255);
            colors[ImGuiCol_ButtonHovered] = ImVec4(0.128f, .7f, .1f, 255);
            colors[ImGuiCol_TextSelectedBg] = ImVec4(0.328f, .9f, 0.3f, 255);
            colors[ImGuiCol_TextDisabled] = ImVec4(0.37f, 0.37f, 0.37f, 1.00f);
            colors[ImGuiCol_CheckMark] = ImVec4(0.328f, .9f, 0.3f, 255);
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

    const char* games[3]
    {
        "Lethal Company",
        "Content Warning",
        "R.E.P.O"
    };
    //temp, needa get paddding working on the left main child
    inline void adjust()
    {
        auto p = ImGui::GetCursorPos();
        ImGui::SetCursorPos(ImVec2(p.x + 4, p.y));
    }

    void gui::render()
    {
        if (loader::active)
        {
            ImGui::SetNextWindowSize(size);
            if (ImGui::Begin(WINDOW_NAME, &active, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
            {
                ImGui::BeginGroup();
                {
                    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(18, 18));
                    ImGui::BeginChild("Left Main", ImVec2(210, size.y - (&ImGui::GetStyle())->WindowPadding.y * 1.5));
                    {
                        auto p = ImGui::GetCursorPos(); //padding, could definitetly simplify but fuckit
                        ImGui::SetCursorPos(ImVec2(p.x + 4, p.y + 4));
                        ImGui::Image((void*)icon->view,
                            ImVec2(200, 200),
                            ImVec2(0, 0),
                            ImVec2(1, 1),
                            ImVec4(255, 255, 255, 255));
                        adjust();
                        g_gui_util.push_font_size(24);
                        if (ImGui::BeginCombo("", games[game])) //fixme
                        {
                            for (int game_ = 0; game_ <= 2; game_++)
                            {
                                if (ImGui::Selectable(games[game_], game_ == game))
                                    game = (egame)game_;
                                if (game_to_name(game) == games[game_])
                                    ImGui::SetItemDefaultFocus();
                            }
                            ImGui::EndCombo();
                        }
                        g_gui_util.pop_font_size();
                        adjust();
                        if (ImGui::Button(g_gui_util.s(std::string("Start ") + ICON_FA_ARROW_RIGHT), ImVec2(ImGui::GetContentRegionAvail().x - 4, 40)))
                            g_inject.inject();
                        adjust();
                        if (ImGui::Button("Launch Game"))
                        {
                            if (game == LETHAL_COMPANY)
                                ShellExecuteA(0, "open", "steam://rungameid/1966720", 0, 0, SW_HIDE);
                            if (game == CONTENT_WARNING)
                                ShellExecuteA(0, "open", "steam://rungameid/2881650", 0, 0, SW_HIDE);
                            if (game == REPO)
                                ShellExecuteA(0, "open", "steam://rungameid/3241660", 0, 0, SW_HIDE);
                        }
                            
                        adjust();
                        g_gui_util.push_font_size(24);
                        ImGui::Text(VERSION);
                        adjust();
                        ImGui::Text("Last Updated 3/12/2025");
                        adjust();
                        ImGui::BeginGroup();
                        //user icon
                        //ImGui::Sameline();
                        ImGui::Text((std::string("Welcome Back ") + util::get_username().data()).c_str());
                        ImGui::EndGroup();
                        g_gui_util.pop_font_size();
                    }
                    ImGui::EndChild();
                    ImGui::PopStyleVar();
                }
                ImGui::SameLine();
                ImGui::BeginGroup();
                {
                    ImGui::BeginChild("Main Tab Bar", ImVec2(ImGui::GetContentRegionAvail().x + (((&ImGui::GetStyle())->WindowPadding.x) + ((&ImGui::GetStyle())->FramePadding.x)), 60), true);
                    {
                        g_gui_util.tab(HOME);
                        ImGui::SameLine();
                        g_gui_util.tab(CHAT);
                        ImGui::SameLine();
                        g_gui_util.tab(CHANGELOG);
                        ImGui::SameLine();
                        g_gui_util.tab(FAQ);
                        ImGui::SameLine();
                        g_gui_util.tab(SETTINGS);
                        ImGui::SameLine();
                        ImGui::SetCursorPosX(ImGui::GetContentRegionMax().x - ImGui::CalcTextSize(" X ").x * 2);
                        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(-3, -3));
                        if (ImGui::Button("X", ImVec2(20, 20)))
                            active = !active;
                        ImGui::PopStyleVar();
                    }
                    ImGui::EndChild();

                    ImGui::BeginChild("Main Tab Display", ImVec2(ImGui::GetContentRegionAvail().x + (((&ImGui::GetStyle())->WindowPadding.x) + ((&ImGui::GetStyle())->FramePadding.x)), ImGui::GetContentRegionAvail().y), true);
                    {
                        switch (tab)
                        {
                            case HOME: home_tab(); break;
                            case CHAT: chat_tab(); break;
                            case CHANGELOG: changelog_tab(); break;
                            case FAQ: faq_tab(); break;
                            case SETTINGS: settings_tab(); break;
                            default: break;
                        }
                    }
                    ImGui::EndChild();
                }
                ImGui::EndGroup();

                ImGui::Separator();
                g_gui_util.centertext(tab_to_name(tab), 1);
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