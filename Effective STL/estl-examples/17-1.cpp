//
// Example from Item 17
//
// Fails under MSVC/native lib, g++ (string lacks push_back)
//

#include <iostream>
#include <vector>

#include "ESTLUtil.h"


class Contestant { };

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	vector<Contestant> contestants;

	for (int i = 0; i < 1000; i++)
		contestants.push_back(Contestant());

	cout << "After init, contestants.size() = " << contestants.size();
	cout << ", contestants.capacity() = " << contestants.capacity() << endl;
	
	contestants.erase(contestants.begin() + 500, contestants.begin() + 600);

	cout << "After deleting 100, contestants.size() = " << contestants.size();
	cout << ", contestants.capacity() = " << contestants.capacity() << endl;

	vector<Contestant>(contestants).swap(contestants);

	cout << "After shrink-to-fit, contestants.size() = " << contestants.size();
	cout << ", contestants.capacity() = " << contestants.capacity() << endl;

// Do the string:

	string s;

					// make s large, then erase most 
					// of its characters
	for (int j = 0; j < 1000; j++)
		s.push_back('x');

	cout << "\nAfter init, s.size() = " << s.size();
	cout << ", s.capacity() = " << s.capacity() << endl;

	s.erase(s.begin(), s.begin()+900);

	cout << "After deleting 900, s.size() = " << s.size();
	cout << ", s.capacity() = " << s.capacity() << endl;

// Originally:
	string(s).swap(s);					// do a “shrink-to-fit” on s

// updated to:
	string(s.begin(), s.end()).swap(s);
	
	cout << "After shrink-to-fit, s.size() = " << s.size();
	cout << ", s.capacity() = " << s.capacity() << endl;


	vector<Contestant> v;
//	string s;							// use s from above


	v = contestants;					// use v and s


	vector<Contestant>().swap(v);		// clear v and minimize its capacity
	string().swap(s);					// clear s and minimize its capacity


	cout << "\nAfter minimization, v.size() = " << v.size();
	cout << ", v.capacity() = " << v.capacity() << endl;

	cout << "After minimization, s.size() = " << s.size();
	cout << ", s.capacity() = " << s.capacity() << endl;


	return 0;
}
