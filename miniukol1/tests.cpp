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
	CHECK(!isEmailAddress("aaa@a a.aa"));
	CHECK(!isEmailAddress("aa\\a@aa.aa"));
	CHECK(!isEmailAddress("aa@aa\\.aa"));
	CHECK(!isEmailAddress("a@.."));
	CHECK(!isEmailAddress("A@aa.?"));
	CHECK(!isEmailAddress(""));
	CHECK(isEmailAddress("a@a"));
	CHECK(!isEmailAddress("a@-"));
	CHECK(!isEmailAddress("a@a-"));
	CHECK(!isEmailAddress(""));
	CHECK(!isEmailAddress(".a@aa.aa"));
	CHECK(!isEmailAddress("a..@aa.aa"));
	CHECK(!isEmailAddress("A@ .aa"));
	CHECK(!isEmailAddress("@aa.aa"));
	CHECK(!isEmailAddress("A@a.5"));
	CHECK(!isEmailAddress("A@.aa"));
	CHECK(isEmailAddress("a\\ a@aa.aa"));
	CHECK(!isEmailAddress("A\\\\ @aa.aa"));
	CHECK(isEmailAddress("a\\\\\\ @aa.aa"));
	CHECK(!isEmailAddress("A\\\\\\@aa.aa"));
        CHECK(!isEmailAddress("??@aa.aa"));
}
