#pragma once

#include "../common.hpp"

namespace loader::util
{ 
    inline std::string download_string(const std::string& url) {
        HINTERNET hInternet, hConnect;
        DWORD bytesRead;
        char buffer[4096];
        std::string result;

        hInternet = InternetOpen(L"Loader", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
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
        std::string readBuffer = download_string(url);

        if (readBuffer.empty())
            return "Error: Failed to retrieve release data.";

        try 
        {
            auto jsonData = nlohmann::json::parse(readBuffer);

            if (jsonData.contains("name"))
                return jsonData["name"];
            else
                return "Release title not found!";
        }
        catch (const std::exception& e) 
        {
            return std::string("JSON parsing error: ") + e.what();
        }
    }

    inline void download_file(std::string path, std::string link)
    {
        char sysdir[MAX_PATH] = { 0 };
        char Path[MAX_PATH] = { 0 };
        GetWindowsDirectoryA(sysdir, MAX_PATH);
        sprintf_s(Path, path.c_str(), sysdir);
        
        auto res = URLDownloadToFileA(NULL, link.c_str(), Path, 0, NULL);
       // return log((FAILED(res) ? "Failed" : "Success"));
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

                ":: GitHub API URL for the latest release\n"
                "set \"url=https://api.github.com/repos/TheGreenBandit/Loader/releases/latest\"\n\n"

                ":: Local path to save the downloaded file\n"
                "set \"File=%~dp0Loader.exe\"\n\n"

                ":: GitHub Personal Access Token (replace this with your actual token)\n"
                "set \"GITHUB_TOKEN=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\"\n\n"

                ":: Call the Download function to fetch the latest release\n"
                "call :Download \"%url%\" \"%File%\" \"%GITHUB_TOKEN%\"\n\n"

                ":: Check if the file was downloaded successfully and display it\n"
                "if exist \"%File%\" (\n"
                "    echo Download successful. Running Loader...\n"
                "    start \"\" \"%File%\"\n"
                ") else (\n"
                "    echo Failed to download the file.\n"
                ")\n\n"

                ":: End the script\n"
                "pause>nul\n"
                "exit /b\n\n"

                "::*********************************************************************************\n"
                ":Download\n"
                ":: Powershell command to download the file from the GitHub API with authentication\n"
                "powershell -Command ^\n"
                "    $url = '%1'; ^\n"
                "    $token = '%3'; ^\n"
                "    $headers = @{ 'User-Agent' = 'Mozilla/5.0'; 'Authorization' = 'token ' + $token }; ^\n"
                "    $response = Invoke-RestMethod -Uri $url -Headers $headers; ^\n"
                "    $downloadUrl = $response.assets[0].browser_download_url; ^\n"
                "    Invoke-WebRequest -Uri $downloadUrl -OutFile '%2'; \n"
                "exit /b\n";
            bat_file.close();
        }
    }
}