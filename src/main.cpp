#include <d3d11.h>
#include "common.hpp"
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_dx11.h"
#include "gui/gui.hpp"
#include "util/injection.hpp"
#include "util/gui_util.hpp"
#include "util/message_system.hpp"
#include "util/discord_util.hpp"
#include "util/cpr_client.hpp"
#include "widgets/imgui_notify.h"
//#pragma comment(lib, "libcurl.lib")
#pragma warning (disable: 4996)

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

using namespace loader;
static inline bool outdated = false;
static inline HWND hwnd = NULL;

void handle_window_movement()//todo clean this up
{
    POINT cursor;
    GetCursorPos(&cursor);
    
    if (!ImGui::IsAnyItemHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
    {
        static POINT prev = cursor;
        RECT rect;
        GetWindowRect(hwnd, &rect);
        MoveWindow(hwnd, rect.left + (cursor.x - prev.x), rect.top + (cursor.y - prev.y), rect.right - rect.left, rect.bottom - rect.top, TRUE);

        prev = cursor;
    }
    else
        static POINT prev = cursor;
}
void create_dir_if_noexist(fs::path path)
{
    if (!fs::is_directory(path)) fs::create_directory(path);
}
void download_if_noexist(fs::path path, cpr::Url link)
{
    if (!fs::exists(path) || outdated)
        g_cpr_client.download(link, path);
}
Image* download_img_if_noexist(fs::path path, cpr::Url link)
{
    Image* ret = new Image();
    if (!fs::exists(path) || outdated)
        g_cpr_client.download(link, path);

    g_gui.load_texture_from_file(path.string().c_str(), g_pd3dDevice, &ret);
    return ret;
}

void add_to_map(std::map<std::string, Image*>& image_map, std::string name, const char* semilink)
{
    image_map.emplace(name, download_img_if_noexist(fs::current_path() / "Resources" / std::format("{}.png", name), std::format("https://github.com/TheGreenBandit/Loader/releases/download/resources/{}.png", semilink).c_str()));
}
void add_to_menu_map(std::map<int, std::pair<std::string, Image*>>& image_map, int position, std::string menu, std::string name, const char* semilink)
{
    image_map.emplace(position, std::make_pair(name, download_img_if_noexist(fs::current_path() / "Resources" / menu / std::format("{}.png", name), std::format("https://github.com/TheGreenBandit/Loader/releases/download/resources/{}.png", semilink).c_str())));
}

void initialize()
{
    g_gui.initialize();
    g_inject.auto_inject();
    g_message_system.loop();
    g_cpr_client.setup_cpr_client();
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
    //Unk
    add_to_menu_map(g_gui.unk_map, 1, "Unk", "unk_self", "unkself");
    add_to_menu_map(g_gui.unk_map, 2, "Unk", "unk_visual", "unkvisual");
    //SpookSuite
    add_to_menu_map(g_gui.spooksuite_map, 1, "Spooksuite", "spooksuite_self", "spooksuite_self");

    download_if_noexist((fs::current_path() / "smi.exe"), "https://github.com/TheGreenBandit/Loader/releases/download/resources/smi.exe");
    download_if_noexist((fs::current_path() / "SharpMonoInjector.dll"), "https://github.com/TheGreenBandit/Loader/releases/download/resources/SharpMonoInjector.dll");

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
    g_logger.clear_log();
    g_logger.log("Welcome!");
    util::write_update_bat();

#ifdef USE_INTERENT
    if (std::string title = util::get_release_title("TheGreenBandit", "Loader"); title != VERSION)
    {
        if ((title == "Failed, check internet.") || (title == "Failed, couldn't get release title."))
        {
            g_logger.log(title);
            exit(0);
        }
        g_logger.log(std::format("The loader is outdated! Closing and downloading the newest version. \nCurrent Version: {}\nNew Version: {}", VERSION, title));
        outdated = true;
    }
#endif

    WNDCLASSEXW wc = { sizeof(WNDCLASSEXW), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandleW(NULL), NULL, NULL, NULL, NULL, L"Loader", NULL};
    RegisterClassExW(&wc);

    hwnd = ::CreateWindowExW(0, wc.lpszClassName, L"Loader", WS_POPUPWINDOW, 0, 0, 805, 366, NULL, NULL, wc.hInstance, NULL);

    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ShowWindow(GetConsoleWindow(), SW_HIDE);
    UpdateWindow(GetConsoleWindow());

    ShowWindow(hwnd, SW_SHOW);//required to use a window on new imgui for some reason, unless i fucked up something
    UpdateWindow(hwnd);

    ImGui_ImplWin32_EnableDpiAwareness();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

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
        loader::g_gui.segoeui_font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 20.0f, &fnt_cfg,
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

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    active = true;
    initialize();

    while (active)
    {
        security.loop();

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

        if (g_SwapChainOccluded && g_pSwapChain->Present(0, DXGI_PRESENT_TEST) == DXGI_STATUS_OCCLUDED)
        {
            ::Sleep(10);
            continue;
        }
        g_SwapChainOccluded = false;

        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
            g_ResizeWidth = g_ResizeHeight = 0;
            CreateRenderTarget();
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        g_gui.render();
		handle_window_movement();
        ImGui::EndFrame();
        ImGui::Render();

        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, g.gui.color.WindowBg);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        HRESULT hr = g_pSwapChain->Present(1, 0);
        g_SwapChainOccluded = (hr == DXGI_STATUS_OCCLUDED);
    }

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
    g_logger.log("goodbye");
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

    sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer = nullptr;
    if (g_pSwapChain)
    {
        if (SUCCEEDED(g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer))))
        {
            if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
            g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
            pBackBuffer->Release();
        }
    }
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
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
        g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
        g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    default:
        break;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}
