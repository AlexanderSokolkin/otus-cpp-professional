#pragma once
#include <string>



class ipv4_address
{
public:

	enum Octet : int {
		Octet_1 = 0,
		Octet_2 = 1,
		Octet_3 = 2,
		Octet_4 = 3,
		Octet_Any
	};


	ipv4_address() noexcept;
	explicit ipv4_address(const std::string& t_ip);
	explicit ipv4_address(const char* t_ip);


	bool existsNumber(Octet t_octet, unsigned t_number) const noexcept;
	std::string str() const noexcept;


	bool operator<(const ipv4_address& t_ip) const noexcept;
	bool operator>(const ipv4_address& t_ip) const noexcept;
	ipv4_address& operator=(const std::string& t_ip);


private:
	std::string m_ip;
	unsigned m_octets[4];
};

