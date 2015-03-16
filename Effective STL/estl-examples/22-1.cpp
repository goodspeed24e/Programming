//
// Example from ESTL Item 22
//

#include <map>
#include <iostream>
#include "ESTLUtil.h"

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	map<int, string> m;
	typedef map<int, string>::value_type mtype;
	
	m.insert(mtype(10, "hello"));
	m.insert(mtype(20, "goodbye"));

	show(m);
	
	m.begin()->first = 10;		// error! map keys can't be changed

	multimap<int, string> mm;

	m.insert(mtype(30, "hello again"));
	m.insert(mtype(40, "goodbye again"));
	m.insert(mtype(40, "goodbye again"));

	mm.begin()->first = 20;		// error! multimap keys can't 
								// be changed, either

	return 0;
}
