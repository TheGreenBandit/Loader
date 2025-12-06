#pragma once

#include "../common.hpp"
#include <cpr/cpr.h>

namespace loader
{
	class cpr_client
	{
		cpr::Session m_session;
	public:
		void setup_cpr_client();

		bool download(const cpr::Url& url, const std::filesystem::path& path, cpr::Header headers = {}, cpr::Parameters query_params = {});
		cpr::Response get(const cpr::Url& url, cpr::Header headers = {}, cpr::Parameters query_params = {});
		cpr::Response post(const cpr::Url& url, cpr::Header headers = {}, cpr::Body body = {});
	};
	static cpr_client g_cpr_client;
}