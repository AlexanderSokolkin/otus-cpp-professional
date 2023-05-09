#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
#include "../ip_address.h"





TEST(IPV4_ADDRESS, ConstructorWithCorrectData)
{
	ASSERT_NO_THROW(ipv4_address("192.168.131.255"));
	ASSERT_NO_THROW(ipv4_address(std::string("192.168.131.255")));
}

TEST(IPV4_ADDRESS, ConstructorWithInvalidData)
{
	EXPECT_THROW(ipv4_address("256.1.1.1"),			std::invalid_argument);
	EXPECT_THROW(ipv4_address("1.1.1.1.1"),			std::invalid_argument);
	EXPECT_THROW(ipv4_address("1,1,2,3"),			std::invalid_argument);
	EXPECT_THROW(ipv4_address("-1.2.3.4"),			std::invalid_argument);
	EXPECT_THROW(ipv4_address("192.168..131.85"),	std::invalid_argument);
	EXPECT_THROW(ipv4_address("127.0.0.1."),		std::invalid_argument);
	EXPECT_THROW(ipv4_address("256.12.1a.1"),		std::invalid_argument);
}

TEST(IPV4_ADDRESS, AssignmentOperatorWithCorrectData)
{
	std::string ipStr = "1.2.3.4";
	ipv4_address ip;

	ASSERT_NO_THROW(ip = ipStr);
	ASSERT_EQ(ip.str(), ipStr);
}

TEST(IPV4_ADDRESS, AssignmentOperatorWithInvalidData)
{
	std::string ipStr = "1.2.3.444";
	ipv4_address ip;

	ASSERT_THROW(ip = ipStr, std::invalid_argument);
}

TEST(IPV4_ADDRESS, CheckExistsNumbersInSpecificPositions)
{
	std::string ipStr = "192.168.131.201";
	ipv4_address ip(ipStr);
	unsigned values[] = { 192, 168, 131, 201 };


	for (int i = 0; i < 4; ++i) {
		EXPECT_TRUE(ip.existsNumber(static_cast<ipv4_address::Octet>(i), values[i])) << 
				"octet " << i + 1 << " in " << ipStr << " is invalid";
	}
}

TEST(IPV4_ADDRESS, CheckExistsNumbersInAnyPositions)
{
	std::string ipStr = "85.49.100.200";
	ipv4_address ip(ipStr);
	unsigned values[] = { 100, 85, 200, 49 };

	for (int i = 0; i < 4; ++i) {
		EXPECT_TRUE(ip.existsNumber(ipv4_address::Octet_Any, values[i])) << 
				"value " << values[i] << " in " << ipStr;
	}
}


TEST(IPV4_ADDRESS, Comparison)
{
	ipv4_address lessIp("192.168.13.100");
	ipv4_address greaterIp("192.168.131.100");

	ASSERT_LT(lessIp, greaterIp);
}
