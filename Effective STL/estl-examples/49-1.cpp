//
// Example from ESTL Item 49
//

#include <string>
#include <vector>
#include <iostream>
#include <list>
#include "ESTLUtil.h"
#include <map>
using namespace std;

class NiftyEmailProgram {
private:
	typedef map<string, string> NicknameMap;

	NicknameMap nicknames;				// map from nicknames to 
										// email addresses
public:
//	void showEmailAddress(const string& nickname) const;
		void showEmailAddress(const string& nickname);
};

void NiftyEmailProgram::showEmailAddress(const string& nickname)
{
	//...
	NicknameMap::iterator i = nicknames.find(nickname);
	if (i != nicknames.end())
		cout << "Not found" << endl;
	//...
}


int main()
{
	using namespace std;
	using namespace ESTLUtils;

	vector<string*> v;						// try to print a container
	copy(v.begin(), v.end(),				// of string* pointers as
		ostream_iterator<string>(cout));	// string objects

	list<int>::iterator i1, i2;				// pass bidirectional iterators to
	sort(i1, i2);							// an algorithm requiring random
											// access iterators


	return 0;
}
