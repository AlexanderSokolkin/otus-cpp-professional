#include "constants.h"
#include "utils.h"
#include "ip_address.h"

#include <iostream>
#include <fstream>



int main(int argc, char* argv[])
{
	Addresses addresses;
	switch (parseArgs(argc, argv)) {
		case Help:
			printHelp(std::cout);
			break;
		case StdIstream:
			readAddresses(std::cin, addresses);
			break;
		case File:
		{
			if (!fileExists(argv[1])) {
				std::cout << "file " << argv[1] << " not found!\n";
				return 1;
			}
			std::ifstream file(argv[1]);
			readAddresses(file, addresses);
			break;
		}
		case InvalidArgs:
		default:
			std::cout << "invalid input data!\n";
			printHelp(std::cout);
			return 2;
	}


	printAddressesIf(std::cout, addresses);
	printAddressesIf(std::cout, addresses, std::list<Filter>{Filter(ipv4_address::Octet_1, 1)});
	printAddressesIf(std::cout, addresses, std::list<Filter>{Filter(ipv4_address::Octet_1, 46),
															 Filter(ipv4_address::Octet_2, 70)});
	printAddressesIf(std::cout, addresses, std::list<Filter>{Filter(ipv4_address::Octet_Any, 46)});

	return 0;
}
