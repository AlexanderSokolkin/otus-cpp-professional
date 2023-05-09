#pragma once

#include "constants.h"
#include "ip_address.h"

#include <iostream>
#include <sstream>
#include <set>
#include <list>
#include <algorithm>


typedef std::multiset<ipv4_address, std::greater<ipv4_address>> Addresses;
typedef std::pair<ipv4_address::Octet, unsigned> Filter;


ArgsSet parseArgs(int argc, char* argv[]) noexcept;
void printHelp(std::ostream& out);
int version_patch() noexcept;

bool fileExists(const char* filename) noexcept;


template <class _Elem, class _Traits>
void readAddresses(std::basic_istream<_Elem, _Traits>& istream,
				   Addresses& addresses) noexcept
{
	std::string row;
	while (!istream.eof()) {
		std::getline(istream, row);
		std::istringstream rowStream;
		rowStream.str(row);
		std::string ip;
		if (std::getline(rowStream, ip, '\t')) {
			try {
				addresses.emplace(ip);
			}
			catch (const std::exception& e) {
				std::cerr << ip << " - " << e.what() << std::endl;
			}
		}
	}
}

template <class _Elem, class _Traits>
void printAddressesIf(std::basic_ostream<_Elem, _Traits>& out,
					  const Addresses& addresses,
					  const std::list<Filter>& filters = std::list<Filter>()) noexcept
{
	std::for_each(addresses.cbegin(), addresses.cend(),
		[&out, &filters](const ipv4_address& ip){
			for (auto& filter : filters) {
				if (!ip.existsNumber(filter.first, filter.second)) {
					return;
				}
			}
			out << ip.str() << std::endl;
		}
	);
}

