#pragma once

#include "common.hpp"
#include "util/curl_util.hpp"

namespace loader::util
{ 
    inline std::string download_string(const std::string& url) {
        HINTERNET hInternet, hConnect;
        DWORD bytesRead;
        char buffer[4096];
        std::string result;

        hInternet = InternetOpenW(L"Loader", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
        if (hInternet == NULL)
        {
            std::cerr << "InternetOpen failed!" << std::endl;
            return "FAILED";
        }

        hConnect = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
        if (hConnect == NULL) 
        {
            std::cerr << "InternetOpenUrlA failed!" << std::endl;
            InternetCloseHandle(hInternet);
            return "FAILED";
        }
        while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0)
            result.append(buffer, bytesRead);

        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);

        return result;
    }

    inline std::string get_release_title(const std::string& owner, const std::string& repo) 
    {
        std::string url = "https://api.github.com/repos/" + owner + "/" + repo + "/releases/latest";
        std::vector<std::string> headers = { "User-Agent: Loader", "Accept: application/vnd.github+json" };
        std::string response = g_curl_util.post(url, "", headers);

        try
        {
            auto jsonData = nlohmann::json::parse(response);
            return jsonData.contains("name") ? jsonData["name"] : "Release title not found!";
        }
        catch (const std::exception& e)
        {
            return std::string("JSON parsing error: ") + e.what();
        }
    }

    inline std::string get_latest_release_url(const std::string& owner, const std::string& repo)
    {
        std::string url = "https://api.github.com/repos/" + owner + "/" + repo + "/releases/latest";
        std::vector<std::string> headers = { "User-Agent: Loader", "Accept: application/vnd.github+json" };
        std::string response = g_curl_util.post(url, "", headers);

        try
        {
            auto jsonData = nlohmann::json::parse(response);
            if (jsonData.contains("assets") && !jsonData["assets"].empty())
                return jsonData["assets"][0]["browser_download_url"];
            else return "Error: No downloadable assets found in the release data.";
        }
        catch (const std::exception& e)
        {
            return std::string("JSON parsing error: ") + e.what();
        }
    }

    inline void download_file(std::string path, std::string url)
    {
        std::vector<std::string> headers = { "User-Agent: LoaderClient", "Accept: application/octet-stream" };
        std::string response = g_curl_util.post(url, "", headers);
        std::ofstream out(path, std::ios::binary);
        out.write(response.data(), response.size());
    }

    inline void download_menu(std::string owner, std::string repo)
    {
        if (!std::filesystem::is_directory(std::filesystem::current_path() / "Menus" / repo)) std::filesystem::create_directory(std::filesystem::current_path() / "Menus" / repo);
        download_file((std::filesystem::current_path() / "Menus" / repo / (repo + ".dll")).string(), get_latest_release_url(owner, repo));
        return;
    }

    inline std::vector<char> read_all_bytes(std::string_view path) noexcept
    {
        std::ifstream input(path.data(), std::ios::binary);
        if (input.is_open())
        {
            std::vector<char> buffer((std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>()));
            return buffer;
        }

        return std::vector<char>();
    }

    inline std::string read_file(std::string_view path) noexcept
    {
        std::ifstream file(path.data());
        if (!file.is_open())
            return "";
        std::stringstream buf;
        buf << file.rdbuf();
        return buf.str();
    }

    inline std::string_view get_username()
    {
        char user[25];
        DWORD user_len = sizeof(user);
        GetUserNameA(user, &user_len);
        return user;
    }

    inline void write_update_bat()
    {
        std::ofstream bat_file("update.bat", std::ios::trunc);
        if (bat_file.is_open()) {
            bat_file <<
                "@echo off\n"
                "Title Download and Run Loader from GitHub\n\n"
                "set \"url=https://api.github.com/repos/TheGreenBandit/Loader/releases/latest\"\n"
                "set \"File=%~dp0Loader.exe\"\n\n"

                "taskkill /F /IM loader.exe >nul 2>&1\n\n"

                "call :Download \"%url%\" \"%File%\"\n\n"
                "if exist \"%File%\" (\n"
                "    echo Download successful. Running Loader...\n"
                "    start \"\" \"%File%\"\n"
                ") else (\n"
                "    echo Failed to download the file.\n"
                ")\n\n"

                "start \"\" \"%File%\"\n\n"

                "exit\n\n"

                "::*********************************************************************************\n"
                ":Download\n"
                ":: Powershell command to download the file from the GitHub API with authentication\n"
                "powershell -Command ^\n"
                "    $url = '%1'; ^\n"
                "    $token = '%3'; ^\n"
                "    $headers = @{ 'User-Agent' = 'Mozilla/5.0' }; ^\n"
                "    $response = Invoke-RestMethod -Uri $url -Headers $headers; ^\n"
                "    $downloadUrl = $response.assets[0].browser_download_url; ^\n"
                "    Invoke-WebRequest -Uri $downloadUrl -OutFile '%2';\n"
                "exit /b\n";
            bat_file.close();
        }
    }
}