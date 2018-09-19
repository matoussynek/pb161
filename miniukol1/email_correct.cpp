#include <cassert>
#include <iostream>
#include <string>

using namespace std;

bool localPartMayContain(size_t pos, bool isEscaped, char c, char prev) {
	if (isEscaped) {
		if (c == ' ')
			return true;
		if (c == '\\')
			return true;
		return false;
	}

	if (isalnum(c))
		return true;

	if (c == '.') {
		if (pos == 0)
			return false;
		if (prev == '.')
			return false;

		return true;
	}

	if (c == '\\')
		return true;

	return false;
}

bool isEmailLocalPart(string const &s) {
	if (s.empty())
		return false;

	bool isEscaped = false;
	for (size_t i = 0; i < s.size(); i++) {
		char const curr = s[i];
		char const prev = i == 0 ? 0 : s[i - 1];
		bool const may = localPartMayContain(i, isEscaped, curr, prev);
		if (!may)
			return false;

		isEscaped = !isEscaped && s[i] == '\\';
	}

	if (isEscaped)
		return false;

	return true;
}

bool isAllowedCharacterForDomain(char c) {
	if (isalnum(c))
		return true;

	if (c == '-')
		return true;

	if (c == '.')
		return true;

	return false;
}

bool domainContainsOnlyAllowedCharacters(string const &s) {
	for (char c : s) {
		if (!isAllowedCharacterForDomain(c))
			return false;
	}
	return true;
}

bool noTwoConsecutiveDots(string const &s) {
	for (size_t i = 0; i < s.size(); i++) {
		if (s[i] == '.' && (i == 0 || s[i - 1] == '.'))
			return false;
	}
	return true;
}

bool domainLabelIsOk(string const &label) {
	assert(label.size() != 0);

	if (label[0] == '-')
		return false;
	if (label[label.size() - 1] == '-')
		return false;

	return true;
}

/**
 * @pre noTwoConsecutiveDots(s);
 */
bool domainLabelsOk(string const &s) {
	size_t b = 0;
	for (size_t i = 0; i < s.size(); i++) {
		if (s[i] != '.')
			continue;

		// It was checked earlier, so we can assert that.
		assert(i != 0);
		if (!domainLabelIsOk(s.substr(b, i - b)))
			return false;
		b = i + 1;
	}

	if (s[s.size() - 1] != '.') {
		if (!domainLabelIsOk(s.substr(b)))
			return false;
	}

	return true;
}

bool lastDomainLabelContainsNonnumericCharacter(string const &s) {
	assert(!s.empty());
	size_t const end = s[s.size() - 1] == '.' ? s.size() - 2 : s.size() - 1;
	size_t const res = s.rfind(".", end);
	size_t const start = (res == string::npos) ? 0 : res + 1;
	string const last_label = s.substr(start, 1 + end - start);

	for (char c : last_label) {
		if (!isdigit(c))
			return true;
	}
	return false;
}

bool isEmailDomain(string const &s) {
	if (s.empty())
		return false;
	if (!noTwoConsecutiveDots(s))
		return false;
	if (!domainContainsOnlyAllowedCharacters(s))
		return false;
	if (!domainLabelsOk(s))
		return false;
	if (!lastDomainLabelContainsNonnumericCharacter(s))
		return false;
	return true;
}

bool isEmailAddress(string const &s) {
	// Split it to 'local-part@domain'
	size_t at_count = 0;
	size_t at_index = s.size();
	for (size_t i = 0; i < s.size(); i++) {
		if (s[i] == '@') {
			at_count++;
			at_index = i;
		};
	}

	if (at_count != 1)
		return false;

	if (!isEmailLocalPart(s.substr(0, at_index)))
		return false;

	if (!isEmailDomain(s.substr(at_index + 1)))
		return false;

	return true;
}
