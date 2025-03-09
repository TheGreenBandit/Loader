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
                "SET \"EXE_PATH=%~dp0loader.exe\"\n"
                "SET \"UPDATE_PATH=%~dp0temp\\new_loader.exe\"\n"
                "SET \"URL=https://github.com/thegreenbandit/main-loader/releases/latest/loader.exe\"\n\n"
                "taskkill /F /IM loader.exe\n\n"
                "echo Downloading new version...\n"
                "curl -L -o \"%UPDATE_PATH%\" \"%URL%\"\n\n"
                "echo Replacing old version...\n"
                "copy /Y \"%UPDATE_PATH%\" \"%EXE_PATH%\"\n\n"
                "echo Restarting the loader...\n"
                "start \"\" \"%EXE_PATH%\"\n\n"
                "del \"%UPDATE_PATH%\"\n\n"
                "exit\n";
            bat_file.close();
        }
    }
}