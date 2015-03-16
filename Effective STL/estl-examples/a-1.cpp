//
// Example from ESTL Appendix A
//

#include <string>
#include <iostream>
#include <cstdio>
#include <cctype>

// fix filter to deal with the following lines missing?
#include <functional>
#include <algorithm>

#include "ESTLUtil.h"

struct lt_nocase
    : public std::binary_function<char, char, bool> {
	bool operator()(char x, char y) const {
		return std::toupper(static_cast<unsigned char>(x)) <
		std::toupper(static_cast<unsigned char>(y));
    }
};


struct lt_str_1 : public std::binary_function<std::string, std::string, bool>
{
        struct lt_char {
                const std::ctype<char>& ct;
                lt_char(const std::ctype<char>& c) : ct(c) {}
                bool operator()(char x, char y) const {
                        return ct.toupper(x) < ct.toupper(y);
                }
        };
        std::locale loc;
        const std::ctype<char>& ct;
        lt_str_1(const std::locale& L = std::locale::classic())
                : loc(L), ct(std::use_facet<std::ctype<char> >(loc)) {}
        bool operator()(const std::string& x, const std::string& y) const {
                return std::lexicographical_compare(x.begin(), x.end(),
                                                y.begin(), y.end(),
                                                lt_char(ct));
        }
};



int main()
{
	using namespace std;
	using namespace ESTLUtils;

	string x("TanGerInE"), y("Tangerine");

	cout << "Using '<', x < y: ";
	if (x < y)
		cout << "true" << endl;
	else
		cout << "false" << endl;
	

	cout << "using lexicographical_compare, x < y: ";
	if (std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()))
		cout << "true" << endl;
	else
		cout << "false" << endl;

	cout << "using lexicographical_compare w/lt_nocase, x < y: ";
	if (std::lexicographical_compare(x.begin(), x.end(),
					y.begin(), y.end(), lt_nocase()))
		cout << "true" << endl;
	else
		cout << "false" << endl;

	cout << "using lexicographical_compare w/lt_nocase, y < x: ";
	if (std::lexicographical_compare(y.begin(), y.end(),
					x.begin(), x.end(), lt_nocase()))
		cout << "true" << endl;
	else
		cout << "false" << endl;


	{
		const char* s1 = "GEW\334RZTRAMINER";
		const char* s2 = "gew\374rztraminer";
		printf("s1 = %s, s2 = %s\n", s1, s2);
		printf("s1 < s2: %s\n",
			std::lexicographical_compare(s1, s1 + 14, s2, s2 + 14, lt_nocase())
				 ? "true" : "false");
	}


	{
		const char* s1 = "GEW\334RZTRAMINER";
		const char* s2 = "gew\374rztraminer";
		setlocale(LC_ALL, "de");
		printf("s1 = %s, s2 = %s\n", s1, s2);
		printf("s1 < s2: %s\n",
			std::lexicographical_compare(s1, s1 + 14, s2, s2 + 14, lt_nocase())
				 ? "true" : "false");
	}

	std::locale L = std::locale::classic();

	char c1 = 'a', c2 = 'A';
	const std::ctype<char>& ct = std::use_facet<std::ctype<char> >(L);
	bool result = ct.toupper(c1) < ct.toupper(c2);
	cout << "c1 < c2: " << (result ? "yes" : "no") << endl;

	result = std::toupper(c1, L) < std::toupper(c2, L);
	cout << "c1 < c2: " << (result ? "yes" : "no") << endl;

	return 0;
}
