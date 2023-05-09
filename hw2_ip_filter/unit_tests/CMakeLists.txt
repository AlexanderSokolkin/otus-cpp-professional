add_executable(ip_filter_test
	main.cpp
	utils_tests.cpp
	ipv4_address_tests.cpp
	../utils.cpp
	../ip_address.cpp
)

find_package(GTest REQUIRED)

target_include_directories(ip_filter_test
	PRIVATE ${GTEST_INCLUDE_DIRS}
	PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(ip_filter_test
	PRIVATE
		GTest::gtest
		GTest::gtest_main
)

set_target_properties(ip_filter_test
	PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
)


enable_testing()
add_test(ip_filter_test ip_filter_test)
		