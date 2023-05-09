#include "ip_address.h"
#include <string>
#include <stdexcept>
#include <regex>



//const size_t MAX_OCTET_SIZE = 3;
//const size_t MAX_IP_ADDRESS_SIZE = 15;
static std::regex IP_REG("^([01]?\\d\\d?|2[0-4]\\d|25[0-5])"
						 "\\.([01]?\\d\\d?|2[0-4]\\d|25[0-5])"
						 "\\.([01]?\\d\\d?|2[0-4]\\d|25[0-5])"
						 "\\.([01]?\\d\\d?|2[0-4]\\d|25[0-5])$");


ipv4_address::ipv4_address() noexcept
{

}

ipv4_address::ipv4_address(const std::string& t_ip) :
	m_ip(t_ip)
{
	std::smatch m;
	if (!std::regex_match(t_ip, m, IP_REG)) {
		throw std::invalid_argument("Invalid IP");
	}
	for (int i = 1; i < 5; ++i) {
		m_octets[i - 1] = static_cast<unsigned>(std::stoi(m[i].str()));
	}
}

ipv4_address::ipv4_address(const char* t_ip) :
	ipv4_address(std::string(t_ip))
{
//	if (strlen(t_ip) > MAX_IP_ADDRESS_SIZE) {
//		throw std::length_error("IP address length exceeded");
//	}

//	int octetsCounter = 0;
//	char separator = '.';
//	int i = 0;
//	std::string octet;
//	while (t_ip[i] != '\0') {
//		if (!std::isdigit(t_ip[i])) {
//			if (t_ip[i] != separator ||
//				octet.size() > MAX_OCTET_SIZE ||
//				octet.empty() ||
//				octetsCounter > 3)
//			{
//				throw std::invalid_argument("Invalid IP");
//			}

//			unsigned octetInt = 0;
//			try {
//				octetInt = std::stoi(octet);
//			}
//			catch (...) {
//				throw std::invalid_argument("Invalid IP");
//			}

//			if (octetInt < 0 && octetInt > 255) {
//				throw std::invalid_argument("Invalid IP");
//			}

//			m_octets[octetsCounter++] = octetInt;
//			octet.clear();
//		} else {
//			if (octetsCounter > 3) {
//				throw std::invalid_argument("Invalid IP");
//			}
//			octet += t_ip[i];
//		}

//		++i;
//	}
}

bool ipv4_address::existsNumber(Octet t_octet, unsigned t_number) const noexcept
{
	switch (t_octet) {
		case Octet_1:
		case Octet_2:
		case Octet_3:
		case Octet_4:
			return m_octets[t_octet] == t_number;
		case Octet_Any:
			for (int i = 0; i < 4; ++i) {
				if (m_octets[i] == t_number) {
					return true;
				}
			}
			return false;
		default:
			return false;
	}
}

std::string ipv4_address::str() const noexcept
{
	return m_ip;
}


bool ipv4_address::operator<(const ipv4_address& t_ip) const noexcept
{
	for (int i = 0; i < 4; ++i) {
		if (m_octets[i] < t_ip.m_octets[i]) {
			return true;
		}
		if (m_octets[i] > t_ip.m_octets[i]) {
			return false;
		}
	}
	return false;
}

bool ipv4_address::operator>(const ipv4_address& t_ip) const noexcept
{
	return t_ip < *this;
}

ipv4_address& ipv4_address::operator=(const std::string& t_ip)
{
	ipv4_address tmp(t_ip);

	std::swap(*this, tmp);

	return *this;
}
