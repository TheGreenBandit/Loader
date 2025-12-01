#include "../includes/ImGui/imgui_impl_win32.h"
#include "../includes/ImGui/imgui_impl_dx11.h"
#include "gui/gui.hpp"
#include <d3d11.h>
#include "common.hpp"
#include "util/injection.hpp"
#include "util/gui_util.hpp"
#include "widgets/imgui_notify.h"
#include "util/message_system.hpp"
#include "util/discord_util.hpp"

#pragma warning (disable: 4996)

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

using namespace loader;
static inline bool outdated = false;
//util functions todo move me, maybe just incorporte into original functions ffs
void create_dir_if_noexist(fs::path path)
{
    if (!fs::is_directory(path)) fs::create_directory(path);
}
void download_if_noexist(fs::path path, const char* link)
{
    if (!fs::exists(path) || outdated)
        util::download_file(path.string(), link);
}
Image* download_img_if_noexist(fs::path path, const char* link, std::vector<loader::Image*>* image_dir = nullptr)
{
    loader::Image* ret = new loader::Image();
    if (!fs::exists(path) || outdated)
        ret = g_gui_util.download_and_load_image_to_list(path.string().c_str(), link, image_dir);
    else
    {
        g_gui.load_texture_from_file(path.string().c_str(), g_pd3dDevice, &ret);
        if (image_dir != nullptr)
            image_dir->push_back(ret);
    }
    return ret;
}

void add_to_map(std::map<std::string, Image*>& image_map, std::string name, const char* semilink)//semilink for naming descrepancies, name can be used for titling/searching
{
    image_map.emplace(name, download_img_if_noexist(fs::current_path() / "Resources" / std::format("{}.png", name), std::format("https://github.com/TheGreenBandit/Loader/releases/download/resources/{}.png", semilink).c_str()));
}
void add_to_menu_map(std::map<int, std::pair<std::string, Image*>>& image_map, int position, std::string menu, std::string name, const char* semilink)//semilink for naming descrepancies, name can be used for titling/searching
{
    image_map.emplace(position, std::make_pair(name, download_img_if_noexist(fs::current_path() / "Resources" / menu / std::format("{}.png", name), std::format("https://github.com/TheGreenBandit/Loader/releases/download/resources/{}.png", semilink).c_str())));
}

void initialize()
{
    g_gui.initialize();
    g_inject.auto_inject();
    g_message_system.loop();
    g.start_time = std::chrono::system_clock::now();
#ifdef USE_INTERENT
    //base stuff
    create_dir_if_noexist(fs::current_path() / "Resources");
    create_dir_if_noexist(fs::current_path() / "Resources" / "Lethal Menu");
    create_dir_if_noexist(fs::current_path() / "Resources" / "Spooksuite");
    create_dir_if_noexist(fs::current_path() / "Resources" / "Unk");
    create_dir_if_noexist(fs::current_path() / "Resources" / "Acid");
    create_dir_if_noexist(fs::current_path() / "Menus");
    //icon mapping
    add_to_map(g_gui.icon_map, "main_icon", "106003542");
    add_to_map(g_gui.icon_map, "gta_icon", "gta_icon");
    add_to_map(g_gui.icon_map, "repo_icon", "repo_icon");
    add_to_map(g_gui.icon_map, "content_warning_icon", "Content-Warning-Logo-500x281");
    add_to_map(g_gui.icon_map, "lethal_company_icon", "lethal_company_icon");
    add_to_map(g_gui.icon_map, "gear_icon", "gear_icon");
    //background mapping
    add_to_map(g_gui.background_map, "gta_background", "gta_background");
    add_to_map(g_gui.background_map, "repo_background", "repo_background");
    add_to_map(g_gui.background_map, "content_warning_background", "content_warning_background");
    add_to_map(g_gui.background_map, "lethal_company_background", "lethal_company_background");
    //menus
    //blade
    //add_to_map(g_gui.menus_map, "", "");
    //Unk
    add_to_menu_map(g_gui.unk_map, 1, "Unk", "unk_self", "unkself");
    add_to_menu_map(g_gui.unk_map, 2, "Unk", "unk_visual", "unkvisual");
    //todo add menu images to their own maps
    download_if_noexist((fs::current_path() / "smi.exe"), "https://github.com/TheGreenBandit/Loader/releases/download/resources/smi.exe");
    download_if_noexist((fs::current_path() / "SharpMonoInjector.dll"), "https://github.com/TheGreenBandit/Loader/releases/download/resources/SharpMonoInjector.dll");

    //Unk images
    download_img_if_noexist((fs::current_path() / "Resources" / "Unk" / "unkself.png"), "https://github.com/TheGreenBandit/Loader/releases/download/resources/unkself.png", &g_gui.unkimages);
    download_img_if_noexist((fs::current_path() / "Resources" / "Unk" / "unksvisual.png"), "https://github.com/TheGreenBandit/Loader/releases/download/resources/unkvisual.png", &g_gui.unkimages);

    //Spooksuite images

    //lethalmenu images

    //changelogs
    download_if_noexist((fs::current_path() / "Resources" / "Lethal Menu" / "Changelog.txt"), "https://github.com/IcyRelic/LethalMenu/raw/refs/heads/master/LethalMenu/Resources/Changelog.txt");
    download_if_noexist((fs::current_path() / "Resources" / "Spooksuite" / "Changelog.txt"), "https://github.com/IcyRelic/SpookSuite/raw/refs/heads/master/SpookSuite/Resources/Changelog.txt");
    download_if_noexist((fs::current_path() / "Resources" / "Unk" / "Changelog.txt"), "https://github.com/thegreenbandit/Unk/raw/refs/heads/master/Unk/Resources/Changelog.txt");
    download_if_noexist((fs::current_path() / "Resources" / "Acid" / "Changelog.txt"), "https://raw.githubusercontent.com/TheGreenBandit/Acid/refs/heads/main/Changelog.txt");
    if (outdated)
    {
        system("update.bat");
        exit(0);
    }
#endif
    g_logger.log("Menu Initialized");
}

int main(int, char**)
{
    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    loader::g_logger.clear_log();
    loader::g_logger.log("Welcome!");
    loader::util::write_update_bat();
#ifdef USE_INTERENT
    if (loader::util::get_release_title("TheGreenBandit", "Loader") != VERSION)
    {
        if (loader::util::get_release_title("TheGreenBandit", "Loader") == "FAILED")
        {
            g_logger.log("Failed to fetch internet, check your connection");
            exit(0);
        }
        if (loader::util::get_release_title("TheGreenBandit", "Loader") == "Release title not found!")
        {
            g_logger.log("FAILED TO FIND RELEASE TITLE");
            exit(0);
        }
        loader::g_logger.log(std::format("The loader is outdated! Closing and downloading the newest version. \nCurrent Version: {}\nNew Version: {}", VERSION, loader::util::get_release_title("TheGreenBandit", "Loader")));
        outdated = true;
        //system("update.bat");
        //exit(0);
    }
#endif
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T(WINDOW_NAME), NULL };
    RegisterClassEx(&wc);
    HWND hwnd = ::CreateWindow(wc.lpszClassName, _T(WINDOW_NAME), WS_POPUPWINDOW, 0, 0, 50, 50, NULL, NULL, wc.hInstance, NULL);
    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ShowWindow(GetConsoleWindow(), SW_HIDE);
    UpdateWindow(GetConsoleWindow());
    
    ShowWindow(hwnd, SW_HIDE);
    UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 4.0f;
        style.Colors[ImGuiCol_WindowBg].w = .3f;
    }

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(loader::g_pd3dDevice, loader::g_pd3dDeviceContext);

    fs::path w = std::getenv("SYSTEMROOT");
    fs::path windows_fonts = w.string() + "//Fonts";
    fs::path font_file_path = windows_fonts /= "./msyh.ttc";
    if (!fs::exists(font_file_path))
        font_file_path = windows_fonts /= "./msyh.ttf";
    auto font_file = std::ifstream(font_file_path, std::ios::binary | std::ios::ate);
    const auto font_data_size = static_cast<int>(font_file.tellg());
    const auto font_data = std::make_unique<std::uint8_t[]>(font_data_size);

    font_file.seekg(0);
    font_file.read(reinterpret_cast<char*>(font_data.get()), font_data_size);
    font_file.close();

    {
        ImFontConfig fnt_cfg{};
        fnt_cfg.FontDataOwnedByAtlas = false;
        strcpy(fnt_cfg.Name, "Fnt20px");
        loader::g_gui.segoeui_font_20px = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 20.0f, &fnt_cfg,
            io.Fonts->GetGlyphRangesDefault());
        fnt_cfg.MergeMode = true;
        io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 20.f, &fnt_cfg, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
        io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 20.f, &fnt_cfg, io.Fonts->GetGlyphRangesCyrillic());
        ImGui::MergeIconsWithLatestFont(20.f);
        static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
        ImFontConfig icons_config;
        icons_config.MergeMode = true;
        icons_config.PixelSnapH = false;
        io.Fonts->AddFontFromFileTTF("widgets/font_awesome_5", 20.f, &icons_config, icons_ranges);
        io.Fonts->Build();
    }
    {
        ImFontConfig fnt_cfg{};
        fnt_cfg.FontDataOwnedByAtlas = false;
        strcpy(fnt_cfg.Name, "Fnt25px");
        loader::g_gui.segoeui_font_25px = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 25.f, &fnt_cfg,
            io.Fonts->GetGlyphRangesDefault());
        fnt_cfg.MergeMode = true;
        io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 25.f, &fnt_cfg, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
        io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 25.f, &fnt_cfg, io.Fonts->GetGlyphRangesCyrillic());
        ImGui::MergeIconsWithLatestFont(25.f);
        static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
        ImFontConfig icons_config;
        icons_config.MergeMode = true;
        icons_config.PixelSnapH = false;
        io.Fonts->AddFontFromFileTTF("widgets/font_awesome_5", 25.f, &icons_config, icons_ranges);
        io.Fonts->Build();
    }
    {
        ImFontConfig fnt_cfg{};
        fnt_cfg.FontDataOwnedByAtlas = false;
        strcpy(fnt_cfg.Name, "Fnt30px");
        loader::g_gui.segoeui_font_30px = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 30.f, &fnt_cfg,
            io.Fonts->GetGlyphRangesDefault());
        fnt_cfg.MergeMode = true;
        io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 30.f, &fnt_cfg, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
        io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 30.f, &fnt_cfg, io.Fonts->GetGlyphRangesCyrillic());
        ImGui::MergeIconsWithLatestFont(30.f);
        static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
        ImFontConfig icons_config;
        icons_config.MergeMode = true;
        icons_config.PixelSnapH = false;
        io.Fonts->AddFontFromFileTTF("widgets/font_awesome_5", 30.f, &icons_config, icons_ranges);
        io.Fonts->Build();
    }
    {
        ImFontConfig fnt_cfg{};
        fnt_cfg.FontDataOwnedByAtlas = false;
        strcpy(fnt_cfg.Name, "Fnt35px");
        loader::g_gui.segoeui_font_35px = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 35.f, &fnt_cfg,
            io.Fonts->GetGlyphRangesDefault());
        fnt_cfg.MergeMode = true;
        io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 35.f, &fnt_cfg, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
        io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 35.f, &fnt_cfg, io.Fonts->GetGlyphRangesCyrillic());
        ImGui::MergeIconsWithLatestFont(35.f);
        static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
        ImFontConfig icons_config;
        icons_config.MergeMode = true;
        icons_config.PixelSnapH = false;
        io.Fonts->AddFontFromFileTTF("widgets/font_awesome_5", 35.f, &icons_config, icons_ranges);
        io.Fonts->Build();
    }
    {
        ImFontConfig fnt_cfg{};
        fnt_cfg.FontDataOwnedByAtlas = false;
        strcpy(fnt_cfg.Name, "Fnt40px");
        loader::g_gui.segoeui_font_40px = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 40.f, &fnt_cfg,
            io.Fonts->GetGlyphRangesDefault());
        fnt_cfg.MergeMode = true;
        io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 40.f, &fnt_cfg, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
        io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 40.f, &fnt_cfg, io.Fonts->GetGlyphRangesCyrillic());
        ImGui::MergeIconsWithLatestFont(40.f);
        static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
        ImFontConfig icons_config;
        icons_config.MergeMode = true;
        icons_config.PixelSnapH = false;
        io.Fonts->AddFontFromFileTTF("widgets/font_awesome_5", 40.f, &icons_config, icons_ranges);
        io.Fonts->Build();
    }
    active = true;//hmm
    initialize();
    // Main
    while (active)
    {
        security.loop();
        discord_util.update();
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                active = false;
        }
        if (!active)
            break;
        // Handle window being minimized or screen locked
        if (loader::g_SwapChainOccluded && loader::g_pSwapChain->Present(0, DXGI_PRESENT_TEST) == DXGI_STATUS_OCCLUDED)
        {
            ::Sleep(10);
            continue;
        }
        loader::g_SwapChainOccluded = false;

        // Handle window resize (we don't resize directly in the WM_SIZE handler)
        if (loader::g_ResizeWidth != 0 && loader::g_ResizeHeight != 0)
        {
            CleanupRenderTarget();
            loader::g_pSwapChain->ResizeBuffers(0, loader::g_ResizeWidth, loader::g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
            loader::g_ResizeWidth = loader::g_ResizeHeight = 0;
            CreateRenderTarget();
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        loader::g_gui.render();
        ImGui::EndFrame();

        ImGui::Render();
        loader::g_pd3dDeviceContext->OMSetRenderTargets(1, &loader::g_mainRenderTargetView, nullptr);
        loader::g_pd3dDeviceContext->ClearRenderTargetView(loader::g_mainRenderTargetView, g.gui.color.WindowBg);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        // Present
        HRESULT hr = loader::g_pSwapChain->Present(1, 0);   // Present with vsync
        //HRESULT hr = g_pSwapChain->Present(0, 0); // Present without vsync
        loader::g_SwapChainOccluded = (hr == DXGI_STATUS_OCCLUDED);
    }

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
    loader::g_logger.log("goodbye");
    return 0;
}

bool CreateDeviceD3D(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &loader::g_pSwapChain, &loader::g_pd3dDevice, &featureLevel, &loader::g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &loader::g_pSwapChain, &loader::g_pd3dDevice, &featureLevel, &loader::g_pd3dDeviceContext);
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (loader::g_pSwapChain) { loader::g_pSwapChain->Release(); loader::g_pSwapChain = nullptr; }
    if (loader::g_pd3dDeviceContext) { loader::g_pd3dDeviceContext->Release(); loader::g_pd3dDeviceContext = nullptr; }
    if (loader::g_pd3dDevice) { loader::g_pd3dDevice->Release(); loader::g_pd3dDevice = nullptr; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    loader::g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    loader::g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &loader::g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (loader::g_mainRenderTargetView) { loader::g_mainRenderTargetView->Release(); loader::g_mainRenderTargetView = nullptr; }
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        loader::g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
        loader::g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    case WM_MOUSEMOVE: //make window move
        if (ImGui::IsAnyItemActive())
            break;
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        MoveWindow(hWnd, x, y, 200, 200, TRUE);
        break;
;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}