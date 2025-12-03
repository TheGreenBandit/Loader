#include "curl_util.hpp"

namespace loader
{
	void curl_util::setup_curl()
	{
		curl_global_init(CURL_GLOBAL_ALL);
		m_curl = curl_easy_init();
	}

	void curl_util::destroy_curl()
	{
		curl_easy_cleanup(m_curl);
		curl_global_cleanup();
	}

	bool curl_util::set_url(std::string url)
	{
		return curl_easy_setopt(m_curl, CURLOPT_URL, url) == CURLE_OK;
	}

	bool curl_util::set_follow_location(bool follow)
	{
		return curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, follow ? 1L : 0L) == CURLE_OK;
	}

	bool curl_util::set_header(std::string header)
	{
		m_headers = curl_slist_append(m_headers, header.c_str());
		return curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_headers) == CURLE_OK;
	}

	bool curl_util::set_headers(std::vector<std::string> headers)
	{
		for (const auto& header : headers)
			m_headers = curl_slist_append(m_headers, header.c_str());

		return curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_headers) == CURLE_OK;
	}

	bool curl_util::set_post_fields(std::string fields)
	{
		if (curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, fields.c_str()) == CURLE_OK)
			return curl_easy_setopt(m_curl, CURLOPT_POSTFIELDSIZE, static_cast<long>(fields.length())) == CURLE_OK;
	}

	bool curl_util::set_write_function(curl_write_callback callback)
	{
		return curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, callback) == CURLE_OK;
	}

	bool curl_util::set_write_data(void* data)
	{
		return curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, data) == CURLE_OK;
	}

	CURLcode curl_util::preform()
	{
		return curl_easy_perform(m_curl);
	}

	std::string curl_util::post(const std::string url, const std::string data, const std::vector<std::string> headers = {})
	{
		std::string ret = "";
		set_url(url);
		curl_easy_setopt(m_curl, CURLOPT_POST, 1);
		set_follow_location(1);
		set_headers(headers);
		set_post_fields(data);
		set_write_function(write_callback);
		set_write_data(&ret);
		if (auto r = preform(); r != CURLE_OK)
			g_logger.log(std::format("CURL ERROR! URL: {}, ", url, curl_easy_strerror(r)));
		return ret;
	}

	size_t curl_util::write_callback(char* ptr, size_t size, size_t nmemb, void* data) 
	{
		size_t numBytes = size * nmemb;
		std::string* response = static_cast<std::string*>(data);
		response->append(ptr, numBytes);
		return numBytes;
	}

	size_t curl_util::header_callback(char* ptr, size_t size, size_t nmemb, void* data) 
	{
		size_t numBytes = size * nmemb;
		std::string* response = static_cast<std::string*>(data);
		response->append(ptr, numBytes);
		return numBytes;
	}
}