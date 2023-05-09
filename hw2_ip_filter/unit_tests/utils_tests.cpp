#include <gtest/gtest.h>
#include <sstream>
#include <filesystem>
#include <fstream>
#include "../utils.h"


TEST(UTILS_COMMON, ParseArguments)
{
	const int argc1 = 1, argc2 = 2, argc3 = 2, argc4 = 3;
	char* argv1[1] = {"path/to/ip_config"};
	char* argv2[2] = {"path/to/ip_config", "--help"};
	char* argv3[2] = {"path/to/ip_config", "path/to/some/file"};
	char* argv4[3] = {"path/to/ip_config", "argument1", "argument2"};


	EXPECT_EQ(parseArgs(argc1, argv1), ArgsSet::StdIstream);
	EXPECT_EQ(parseArgs(argc2, argv2), ArgsSet::Help);
	EXPECT_EQ(parseArgs(argc3, argv3), ArgsSet::File);
	EXPECT_EQ(parseArgs(argc4, argv4), ArgsSet::InvalidArgs);
}

TEST(UTILS_COMMON, PrintHelp)
{
	std::ostringstream fakeStream;
	std::string content;

	printHelp(fakeStream);
	content = fakeStream.str();

	ASSERT_FALSE(content.empty());
}

TEST(UTILS_COMMON, ReadAddresses)
{
	std::string content = 
		"192.168.131.32\tsome\ttext\n"
		"1.2.3.4\tsome\ttext\n"
		"255.255.255.255\tsome\ttext\n";
	const size_t addressesCount = 3;
	std::istringstream fakeStream;
	Addresses addresses;

	fakeStream.str(content);

	readAddresses(fakeStream, addresses);
	ASSERT_EQ(addresses.size(), addressesCount);
}


struct UTILS_PrintIp : public ::testing::Test
{
protected:
	virtual void SetUp() {
		addresses.insert(ipv4_address("192.168.131.36"));
		addresses.insert(ipv4_address("1.2.3.4"));
		addresses.insert(ipv4_address("1.10.1.1"));
		addresses.insert(ipv4_address("255.255.255.255"));
		addresses.insert(ipv4_address("168.10.88.94"));
	}

	virtual void TearDown() {

	}

protected:
	Addresses addresses;
	std::ostringstream fakeStream;
	std::string content;
};



TEST_F(UTILS_PrintIp, PrintAddressesWithoutFilters)
{
	std::string expected =
		"255.255.255.255\n"
		"192.168.131.36\n"
		"168.10.88.94\n"
		"1.10.1.1\n"
		"1.2.3.4\n";

	printAddressesIf(fakeStream, addresses);
	content = fakeStream.str();

	ASSERT_EQ(content, expected);
}

TEST_F(UTILS_PrintIp, PrintAddressesWithOneFilter)
{
	std::string expected =
		"1.10.1.1\n"
		"1.2.3.4\n";

	printAddressesIf(fakeStream, addresses, std::list<Filter>{Filter(ipv4_address::Octet_1, 1)});
	content = fakeStream.str();

	ASSERT_EQ(content, expected);
}

TEST_F(UTILS_PrintIp, PrintAddressesWithSeveralFilters)
{
	std::string expected =
		"192.168.131.36\n";

	printAddressesIf(fakeStream, addresses, std::list<Filter>{	Filter(ipv4_address::Octet_Any, 168),
																Filter(ipv4_address::Octet_4, 36)});
	content = fakeStream.str();

	ASSERT_EQ(content, expected);
}
