#pragma once

#include "../common.hpp"
#include "cpr_client.hpp"
#include "logger.hpp"

namespace loader::util
{
    inline std::string get_release_title(const std::string& owner, const std::string& repo)
    {
        std::string url = "https://api.github.com/repos/" + owner + "/" + repo + "/releases/latest";
        auto response = g_cpr_client.get(url, { {"User-Agent", "Loader"}, {"Accept", "application/vnd.github+json"} });
        if (response.status_code != 200)
            return "Failed to get release title.";

        try
        {
            auto jsonData = nlohmann::json::parse(response.text);

            if (jsonData.contains("name"))
                return jsonData["name"];
            else
                return "Release title not found!";
        }
        catch (const std::exception& e)
        {
            return std::string("JSON parsing error: ") + e.what();
        }
		return std::string("");
    }

    inline std::string get_latest_release_url(const std::string& owner, const std::string& repo)
    {
        std::string url = "https://api.github.com/repos/" + owner + "/" + repo + "/releases/latest";
        g_logger.log("l0");
        auto response = g_cpr_client.get(url, { {"User-Agent", "Loader"}, {"Accept", "application/vnd.github+json"} });
        g_logger.log("L1");
        if (response.status_code != 200)
            return "Failed to post";

        try
        {
            auto jsonData = nlohmann::json::parse(response.text);
            if (jsonData.contains("assets") && !jsonData["assets"].empty())
                return jsonData["assets"][0]["browser_download_url"];
            else return "Could not find a release.";
        }
        catch (const std::exception& e)
        {
            return std::string("JSON parsing error: ") + e.what();
        }
        return std::string("");
    }

    inline void download_menu(std::string owner, std::string repo)
    {
        if (!std::filesystem::is_directory(std::filesystem::current_path() / "Menus" / repo)) std::filesystem::create_directory(std::filesystem::current_path() / "Menus" / repo);
        g_cpr_client.download(get_latest_release_url(owner, repo), (std::filesystem::current_path() / "Menus" / repo / (repo + ".dll")));
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

    inline bool is_dev()
    {
        return get_username().data() == "TGB";
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