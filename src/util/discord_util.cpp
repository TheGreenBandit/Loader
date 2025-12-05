#include "discord_util.hpp"
#include "../gui/gui.hpp"
#include "../token.hpp"

namespace loader
{
	discord_util::discord_util()
	{
	}

	discord_util::~discord_util()
	{
	}

    void discord_util::update()
    {
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

    void discord_util::send_bot_message(const std::string& channel_id, const std::string& message)
    {
        std::string escaped_message = escape_json_string(message);
        std::string json_data = "{ \"content\": \"" + escaped_message + "\" }";
        std::string url = "https://discord.com/api/v10/channels/" + channel_id + "/messages";

        std::vector<std::string> headers = { std::string("Authorization: Bot ") + DISCORD_TOKEN, "Content-Type: application/json", "User-Agent: Loader" };
        
        //g_curl_util.post(url, json_data, 0, headers);
    }

    std::vector<std::string> discord_util::read_channel_messages(const std::string& channel_id)
    {
        std::vector<std::string> messages;
        std::string url = "https://discord.com/api/v10/channels/" + channel_id + "/messages";

        std::vector<std::string> headers = { std::string("Authorization: Bot ") + DISCORD_TOKEN, "Content-Type: application/json", "User-Agent: Loader" };
        
        std::string response /*= g_curl_util.post(url, "", 0, headers)*/;

        try
        {
            auto json = nlohmann::json::parse(response);

            for (const auto& msg : json)
            {
                if (msg.contains("content") && msg["content"].is_string())
                    messages.push_back(escape_json_string(msg["content"].get<std::string>()));
            }
        }
        catch (const std::exception& e)
        {
            g_logger.log(std::format("Discord read_channel_messages JSON error: {}", e.what()));
        }

        return messages;
    }
}