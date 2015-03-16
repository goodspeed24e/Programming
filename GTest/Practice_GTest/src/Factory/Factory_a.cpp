
#include <iostream>
#include <vector>
using namespace std;

class Stooge{
public:
	static Stooge* make_stooge( int choice );
	virtual void slap_stick() = 0;
};

class Larry: public Stooge{
public: 
	void slap_stick(){
		cout << "Larry: poke eyes\n";
	}
};

class Moe: public Stooge{
public:
	void slap_stick(){
		cout <<"Moe: slap head\n";
	}
};

class Curly: public Stooge{
public:
	void slap_stick(){
		cout << "Curly: suffer abuse\n";
	}
};

Stooge* Stooge::make_stooge( int choice){
	if ( choice == 1)
		return new Larry;
	else if ( choice == 2)
		return new Moe;
	else if ( choice == 3)
		return new Curly;
}
int main ( void ){
	vector<Stooge*> roles;
	int	choice=0;
	while( true ){
		cout << "Larry (1) Moe(2) Curly(3) Go(0): ";
		cin >> choice;
		if ( choice  == 0 )
			break;
		roles.push_back( Stooge::make_stooge( choice ));
	}
	for ( int i = 0 ; i < roles.size(); i++)
		roles[i]->slap_stick();
	for ( int i = 0; i < roles.size(); i++)
		delete roles[i];
}