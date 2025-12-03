#include "../common.hpp"
#include "../../includes/Curl/curl.h"

namespace loader
{
	class curl_util
	{
		CURL* m_curl;
		struct curl_slist* m_headers;

		bool set_url(std::string url);
		bool set_follow_location(bool follow);
		bool set_header(std::string header);
		bool set_headers(std::vector<std::string> headers);
		bool set_post_fields(std::string fields);
		bool set_write_function(curl_write_callback callback);
		bool set_write_data(void* data);
		CURLcode preform();
		static size_t write_callback(char* ptr, size_t size, size_t nmemb, void* data);
		static size_t header_callback(char* ptr, size_t size, size_t nmemb, void* data);
	public:
		void setup_curl();
		void destroy_curl();
		std::string post(const std::string url, const std::string data, const std::vector<std::string> headers = {});
	};
	curl_util g_curl_util;
}