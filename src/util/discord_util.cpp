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

    std::string escape_json_string(const std::string& input)
    {
        std::string output;
        for (char c : input) {
            if (c == '"') output += "\\\"";
            else if (c == '\\') output += "\\\\";
            else if (c == '\n') output += "\\n";
            else if (c == '\r') output += "\\r";
            else if (c == '\t') output += "\\t";
            else output += c;
        }
        return output;
    }

    void discord_util::send_message(std::string_view message) //todo, nomatter what i get error 400
    {
        try
        {
            std::string escaped_message = escape_json_string(std::string(message.data()));
            std::string json_data = "{\n  \"content\": \"" + escaped_message + "\"\n}";

            g_logger.log("Sending JSON: " + json_data);
            g_logger.log("Webhook URL: " + webhook);

            HINTERNET hInternet = InternetOpen(L"Discord Webhook Shit", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
            if (hInternet == NULL)
                return g_logger.log("InternetOpen failed!");

            HINTERNET hConnect = InternetOpenUrlA(hInternet, webhook.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
            if (hConnect == NULL) 
            {
                InternetCloseHandle(hInternet);
                return g_logger.log("InternetOpenUrlA failed!");
            }

            std::string content_length = "Content-Length: " + std::to_string(json_data.size()) + "\r\n";
            std::string headers = "Content-Type: application/json\r\n" + content_length;
            headers += "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36\r\n";

            DWORD bytesWritten;
            BOOL result = HttpSendRequestA(hConnect, headers.c_str(), headers.length(), (LPVOID)json_data.c_str(), json_data.size());

            if (!result)
                g_logger.log("HttpSendRequestA failed!");
            else 
            {
                DWORD statusCode = 0;
                DWORD size = sizeof(statusCode);
                if (HttpQueryInfoA(hConnect, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &statusCode, &size, NULL)) {
                    if (statusCode == 204)
                        g_logger.log("Message sent successfully!");
                    else 
                    {
                        DWORD bufferSize = 4096;
                        char buffer[4096] = { 0 };
                        DWORD bytesRead;
                        if (InternetReadFile(hConnect, buffer, bufferSize, &bytesRead)) {
                            std::string response_body(buffer, bytesRead);
                            g_logger.log("Failed to send message. Status Code: " + std::to_string(statusCode));
                            g_logger.log("Response Body: " + response_body);
                        }
                        else
                            g_logger.log("Failed to read response body!");
                    }
                }
                else
                    g_logger.log("Failed to get status code!");
            }

            InternetCloseHandle(hConnect);
            InternetCloseHandle(hInternet);
        }
        catch (std::exception& e) {
            g_logger.log(e.what());
        }
    }
}