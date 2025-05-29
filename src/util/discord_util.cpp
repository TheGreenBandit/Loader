#include "discord_util.hpp"
#include "../gui/gui.hpp"

namespace loader
{
	discord_util::discord_util()//discord rpc is also a todo
	{
        ZeroMemory(&handlers, sizeof(handlers));

        //Discord_Initialize("", &handlers, TRUE, "");
	}

	discord_util::~discord_util()
	{
        //Discord_ClearPresence();
        //Discord_Shutdown();
	}

    void discord_util::update()
    {
        update_rpc();
    }

    void discord_util::update_rpc()
    {
        if (rpc_enabled)
        {
            ZeroMemory(&presence, sizeof(presence));
            presence.state = std::format("Modding {}", g_gui.game_to_name(g_gui.game)).c_str();
            presence.startTimestamp = std::chrono::system_clock::to_time_t(g.start_time);
        }
        //else
            //Discord_ClearPresence();
        //Discord_RunCallbacks();
    }

    std::string escape_json_string(const std::string& input) {
        std::ostringstream oss;
        for (char c : input) {
            switch (c) {
            case '"':  oss << "\\\""; break;
            case '\\': oss << "\\\\"; break;
            case '\b': oss << "\\b"; break;
            case '\f': oss << "\\f"; break;
            case '\n': oss << "\\n"; break;
            case '\r': oss << "\\r"; break;
            case '\t': oss << "\\t"; break;
            default:
                if (static_cast<unsigned char>(c) < 0x20)
                    oss << "\\u" << std::hex << std::setw(4) << std::setfill('0') << (int)c;
                else
                    oss << c;
            }
        }
        return oss.str();
    }

    void discord_util::send_message(std::string_view message) //with webhook
    {
        try {
            std::string escaped_message = escape_json_string(std::string(message));
            std::string json_data = "{ \"content\": \"" + escaped_message + "\" }";
            URL_COMPONENTSA urlComp = { sizeof(URL_COMPONENTSA) };
            char hostName[256], urlPath[1024];

            urlComp.lpszHostName = hostName;
            urlComp.dwHostNameLength = sizeof(hostName);
            urlComp.lpszUrlPath = urlPath;
            urlComp.dwUrlPathLength = sizeof(urlPath);

            if (!InternetCrackUrlA(webhook.c_str(), 0, 0, &urlComp)) 
            {
                g_logger.log("Failed to parse webhook URL.");
                return;
            }
            HINTERNET hInternet = InternetOpenA("DiscordWebhookClient", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
            if (!hInternet)
            {
                g_logger.log("InternetOpenA failed!");
                return;
            }

            HINTERNET hConnect = InternetConnectA(hInternet, hostName, urlComp.nPort, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
            if (!hConnect) 
            {
                g_logger.log("InternetConnectA failed!");
                InternetCloseHandle(hInternet);
                return;
            }

            const char* acceptTypes[] = { "application/json", NULL };
            HINTERNET hRequest = HttpOpenRequestA(hConnect, "POST", urlPath, NULL, NULL, acceptTypes, INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE, 0);
            if (!hRequest) 
            {
                g_logger.log("HttpOpenRequestA failed!");
                InternetCloseHandle(hConnect);
                InternetCloseHandle(hInternet);
                return;
            }

            std::string headers = "Content-Type: application/json\r\n";
            BOOL result = HttpSendRequestA(hRequest, headers.c_str(), headers.length(), (LPVOID)json_data.c_str(), json_data.length());

            if (!result)
                g_logger.log("HttpSendRequestA failed!");
            else 
            {
                DWORD statusCode = 0;
                DWORD size = sizeof(statusCode);
                if (HttpQueryInfoA(hRequest, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &statusCode, &size, NULL))
                {
                    if (statusCode == 204)
                        g_logger.log("Message sent successfully!");
                    else 
                    {
                        g_logger.log("Failed to send message. Status Code: " + std::to_string(statusCode));

                        char buffer[4096] = { 0 };
                        DWORD bytesRead;
                        if (InternetReadFile(hRequest, buffer, sizeof(buffer) - 1, &bytesRead)) 
                        {
                            std::string response_body(buffer, bytesRead);
                            g_logger.log("Response Body: " + response_body);
                        }
                    }
                }
                else
                    g_logger.log("Failed to query status code.");
            }

            InternetCloseHandle(hRequest);
            InternetCloseHandle(hConnect);
            InternetCloseHandle(hInternet);

        }
        catch (const std::exception& e) 
        {
            g_logger.log(std::string("Exception: ") + e.what());
        }
    }

    void discord_util::send_bot_message(const std::string& channel_id, const std::string& bot_token, const std::string& message)
    {
        std::string escaped_message = escape_json_string(message);
        std::string json_data = "{ \"content\": \"" + escaped_message + "\" }";
        std::string endpoint = "/api/v10/channels/" + channel_id + "/messages";
        HINTERNET hInternet = InternetOpenA("DiscordBotClient", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
        if (!hInternet) return;

        HINTERNET hConnect = InternetConnectA(hInternet, "discord.com", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
        if (!hConnect) 
        {
            InternetCloseHandle(hInternet);
            return;
        }

        HINTERNET hRequest = HttpOpenRequestA(hConnect, "POST", endpoint.c_str(), NULL, NULL, NULL, INTERNET_FLAG_SECURE | INTERNET_FLAG_RELOAD, 0);
        if (!hRequest) 
        {
            InternetCloseHandle(hConnect);
            InternetCloseHandle(hInternet);
            return;
        }

        std::string headers = "Authorization: Bot " + bot_token + "\r\nContent-Type: application/json\r\n";

        BOOL result = HttpSendRequestA(hRequest, headers.c_str(), headers.length(), (LPVOID)json_data.c_str(), json_data.length());

        DWORD status_code = 0;
        DWORD size = sizeof(status_code);
        if (HttpQueryInfoA(hRequest, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &status_code, &size, NULL)) 
        {
            g_logger.log("Status Code: " + std::to_string(status_code));

            if (status_code != 200 && status_code != 204) 
            {
                char buffer[4096] = { 0 };
                DWORD bytes_read = 0;
                if (InternetReadFile(hRequest, buffer, sizeof(buffer) - 1, &bytes_read)) 
                {
                    std::string response_body(buffer, bytes_read);
                    g_logger.log("Response Body: " + response_body);
                }
            }
        }
        else
            g_logger.log("Failed to get status code");

        InternetCloseHandle(hRequest);
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
    }

    std::vector<std::string> discord_util::read_channel_messages(const std::string& channel_id, const std::string& bot_token)
    {
        std::vector<std::string> messages;

        std::string endpoint = "/api/v10/channels/" + channel_id + "/messages";

        HINTERNET internet = InternetOpenA("discord_bot_reader", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
        if (!internet) return messages;

        HINTERNET connection = InternetConnectA(internet, "discord.com", INTERNET_DEFAULT_HTTPS_PORT,
            NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
        if (!connection) 
        {
            InternetCloseHandle(internet);
            return messages;
        }

        HINTERNET request = HttpOpenRequestA(connection, "GET", endpoint.c_str(), NULL, NULL, NULL,
            INTERNET_FLAG_SECURE | INTERNET_FLAG_RELOAD, 0);
        if (!request) 
        {
            InternetCloseHandle(connection);
            InternetCloseHandle(internet);
            return messages;
        }

        std::string headers =
            "Authorization: Bot " + bot_token + "\r\n"
            "Content-Type: application/json\r\n";

        BOOL result = HttpSendRequestA(request, headers.c_str(), headers.length(), NULL, 0);
        if (!result) 
        {
            InternetCloseHandle(request);
            InternetCloseHandle(connection);
            InternetCloseHandle(internet);
            return messages;
        }

        char buffer[8192];
        DWORD bytes_read;
        std::string response;

        while (InternetReadFile(request, buffer, sizeof(buffer), &bytes_read) && bytes_read != 0)
            response.append(buffer, bytes_read);

        InternetCloseHandle(request);
        InternetCloseHandle(connection);
        InternetCloseHandle(internet);

        try
        {
            const std::string key = "\"content\":\"";
            size_t pos = 0;

            while ((pos = response.find(key, pos)) != std::string::npos)
            {
                pos += key.length();
                std::string content;
                bool in_escape = false;

                while (pos < response.size())
                {
                    char c = response[pos++];

                    if (in_escape)
                    {
                        switch (c)
                        {
                        case 'n': content += '\n'; break;
                        case 't': content += '\t'; break;
                        case '\\': content += '\\'; break;
                        case '"': content += '"'; break;
                            // skip others
                        default: break;
                        }
                        in_escape = false;
                    }
                    else if (c == '\\')
                        in_escape = true;
                    else if (c == '"')
                        break;
                    else
                        content += c;
                }

                messages.push_back(content);
            }
        }
        catch (const std::exception& e) 
        {}

        return messages;
    }
}