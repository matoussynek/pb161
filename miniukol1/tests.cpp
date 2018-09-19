#include "catch.hpp"
#include <string>

using namespace std;

bool isEmailAddress(string const &s);

TEST_CASE("Email address tests") {
	CHECK(!isEmailAddress("email ova@adresa.cz"));
    CHECK(isEmailAddress("vladimir.iljic.lenin@leningrad.sssr"));
	CHECK(!isEmailAddress("vladimir@"));
	CHECK(!isEmailAddress("honza@moje_domena.cz"));
	CHECK(isEmailAddress("jan@123.cz"));
}
