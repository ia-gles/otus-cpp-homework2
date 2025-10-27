#define BOOST_TEST_MODULE test_version

#include <iostream>
#include <string>
#include <vector>

#include "lib.h"
#include "IP.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_version)

BOOST_AUTO_TEST_CASE(test_valid_version) {
	BOOST_CHECK(version() > 0);

	const std::size_t size0 = 0;
	const std::size_t size1 = 4;
	const std::size_t size2 = 16;
	const std::size_t size3 = 8;

	std::vector<std::string> normal{"111", "111", "111", "111"};
	std::vector<std::string> normal16{"aaaa", "111f", "a111", "bc11", "1d1f"};

	std::vector<std::string> s1{"", "111", "111", "111"};
	std::vector<std::string> s2{"111", "", "111", "111"};
	std::vector<std::string> s3{"111", "111", "", "111"};
	std::vector<std::string> s4{"111", "111", "111", ""};
	std::vector<std::string> s5{"111", "", "", "111"};
	std::vector<std::string> s6{"256", "111", "111", "111"};
	std::vector<std::string> s7{"-111", "111", "111", "111"};
	std::vector<std::string> s8{"111", "aaa", "111", "111"};
	std::vector<std::string> s9{"111", "", "-111", "1a1"};
	

	BOOST_CHECK_THROW(new IP<size0>(normal), std::invalid_argument);
	BOOST_CHECK_NO_THROW(new IP<size1>(normal));
	BOOST_CHECK_NO_THROW(new IP<size2>(normal16));
	BOOST_CHECK_THROW(new IP<size3>(normal), std::invalid_argument);

	BOOST_CHECK_THROW(new IP<size1>(s1), std::invalid_argument);
	BOOST_CHECK_THROW(new IP<size1>(s2), std::invalid_argument);
	BOOST_CHECK_THROW(new IP<size1>(s3), std::invalid_argument);
	BOOST_CHECK_THROW(new IP<size1>(s4), std::invalid_argument);
	BOOST_CHECK_THROW(new IP<size1>(s5), std::invalid_argument);
	BOOST_CHECK_THROW(new IP<size1>(s6), std::invalid_argument);
	BOOST_CHECK_THROW(new IP<size1>(s7), std::invalid_argument);
	BOOST_CHECK_THROW(new IP<size1>(s8), std::invalid_argument);
	BOOST_CHECK_THROW(new IP<size1>(s9), std::invalid_argument);

}

BOOST_AUTO_TEST_SUITE_END()
