#include <gtest/gtest.h>
#include <parse_functions.h>

#include <limits>
#include <sstream>
#include <string>

using namespace CmdLineParser;

TEST(ParseDouble, Parse_dec)
{
	std::ostringstream oss;
	oss << std::setprecision(std::numeric_limits<double>::max_digits10) << std::numeric_limits<double>::max();

	EXPECT_NEAR(ParseDouble(oss.str().c_str()), std::numeric_limits<double>::max(), std::abs(std::numeric_limits<double>::max() * 1e-10));

	oss.str("");
	oss.clear();
	oss << std::setprecision(std::numeric_limits<double>::max_digits10) << std::numeric_limits<double>::min();

	EXPECT_NEAR(ParseDouble(oss.str().c_str()), std::numeric_limits<double>::min(), std::abs(std::numeric_limits<double>::min() * 1e-10));
}

TEST(ParseDouble, Parse_scientific)
{
	EXPECT_EQ(ParseDouble("3.14159e-4"), 3.14159e-4);
	EXPECT_EQ(ParseDouble("-3.14159e4"), -3.14159e4);
}

TEST(ParseDouble, ThrowOnTooBig)
{
	std::ostringstream oss;
	oss << std::setprecision(std::numeric_limits<double>::max_digits10) << std::numeric_limits<double>::max();

	std::string str(std::move(oss.str()));
	str[0] += 1;

	EXPECT_THROW(ParseDouble(str.c_str()), std::out_of_range);
}

TEST(ParseDouble, ThrowOnTooSmall)
{
	std::ostringstream oss;
	oss << std::setprecision(std::numeric_limits<double>::max_digits10) << std::numeric_limits<double>::min();

	std::string str(std::move(oss.str()));
	str[0] -= 1;

	EXPECT_THROW(ParseDouble(str.c_str()), std::out_of_range);
}

TEST(ParseDouble, ThrowOnInvalid)
{
	EXPECT_THROW(ParseDouble("invalid"), std::invalid_argument);
}