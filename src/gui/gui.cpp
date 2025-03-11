#include "gui.hpp"
#include "../common.hpp"
#include "../util/util.hpp"
#include "../util/gui_util.hpp"

#include <d3d11.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../widgets/stb_image.h"

namespace loader
{
    void gui::initialize()
    {
        ImVec4* colors = ImGui::GetStyle().Colors;
        {
            colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
            colors[ImGuiCol_Border] = ImVec4(0.00f, 1.00f, 0.00f, 1.00f);
            colors[ImGuiCol_FrameBg] = ImColor(50, 50, 50, 255);
            colors[ImGuiCol_FrameBgHovered] = ImColor(11, 11, 11, 255);

            colors[ImGuiCol_Button] = ImVec4(0.228f, .8f, 0.2f, 255);
            colors[ImGuiCol_ButtonActive] = ImVec4(0.328f, .9f, 0.3f, 255);
            colors[ImGuiCol_ButtonHovered] = ImVec4(0.128f, .7f, .1f, 255);

            colors[ImGuiCol_TextDisabled] = ImVec4(0.37f, 0.37f, 0.37f, 1.00f);
            colors[ImGuiCol_ChildBg] = ImVec4(0.3f, 0.3f, 0.3f, 1.00f);
        }

        ImGuiStyle* style = &ImGui::GetStyle();
        {
            style->WindowPadding = ImVec2(14, 14);
            style->WindowBorderSize = 10.f;
            style->WindowRounding = 15.f;

            style->FramePadding = ImVec2(8, 6);
            style->FrameRounding = 3.f;
            style->FrameBorderSize = 1.5f;

            style->ChildBorderSize = 1.f;
            style->ChildRounding = 5.f;
        }
    }

    void gui::render()
    {
        if (loader::active)
        {
            ImGui::SetNextWindowSize(ImVec2(800, 600));
            ImGui::Begin(WINDOW_NAME, &active, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
            {
                ImGui::TextDisabled("X");
                active = !ImGui::IsItemClicked();
                ImGui::SameLine();
                ImGui::Text(WINDOW_NAME);
                ImGui::Separator();
                g_gui_util.tab(HOME);
                ImGui::SameLine();
                g_gui_util.tab(LETHAL_COMPANY);
                ImGui::SameLine();
                g_gui_util.tab(REPO);
                ImGui::SameLine();
                g_gui_util.tab(CONTENT_WARNING);
                ImGui::SameLine();
                g_gui_util.tab(SETTINGS);

                ImGui::Separator();
                g_gui_util.centertext(tab_to_name(tab), 1);

                switch (tab)
                {
                    case HOME: home_tab(); break;
                    case LETHAL_COMPANY: lethal_company_tab(); break;
                    case REPO: repo_tab(); break;
                    case CONTENT_WARNING: content_warning_tab(); break;
                    case SETTINGS: settings_tab(); break;
                    default: break;
                }
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