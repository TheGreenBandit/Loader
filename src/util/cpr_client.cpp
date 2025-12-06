#include "cpr_client.hpp"

namespace loader
{
	void cpr_client::setup_cpr_client()
	{
		m_session.SetTimeout(5000);
		m_session.SetConnectTimeout(1000);
		m_session.SetProxies({ {"http", ""}, {"https", ""} });//skip windows wpad, makes it insanely faster
	}

	cpr::Response cpr_client::post(const cpr::Url& url, cpr::Header headers, cpr::Body body)
	{
		m_session.SetUrl(url);
		m_session.SetHeader(headers);
		m_session.SetBody(body);

		return m_session.Post();
	}

	cpr::Response cpr_client::get(const cpr::Url& url, cpr::Header headers, cpr::Parameters query_params)
	{
		m_session.SetUrl(url);
		m_session.SetHeader(headers);
		m_session.SetParameters(query_params);

		return m_session.Get();
	}

	bool cpr_client::download(const cpr::Url& url, const std::filesystem::path& path, cpr::Header headers, cpr::Parameters query_params)
	{
		m_session.SetUrl(url);
		m_session.SetHeader(headers);
		m_session.SetParameters(query_params);

		std::ofstream of(path, std::ios::binary);
		auto res = m_session.Download(of);

		return res.status_code == 200;
	}
}