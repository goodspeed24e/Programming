
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Array{
public:
	void addFront( char c ){
		lst.push_front(c);
	}
	void addBack( char c ){
		lst.push_back(c);
	}
	void traverse(){
		int i;
		for ( i = 0; i < lst.size(); i++)
			cout << lst[i] << ' ';
		cout << endl;
	}
private: 
	deque<char> lst;
};

string in[]= { "fa", "bb", "fc", "bd", "fe", "bf", "fg", "bh"};

void main( void ){
	Array list;
	for ( int i = 0; i < 8; i++)
	{
		if ( in[i][0] == 'f')
			list.addFront(in[i][1]);
		else if ( in[i][0] == 'b' )
			list.addBack(in[i][1]);
	}
	list.traverse();
}