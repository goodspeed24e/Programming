
/*
The boss's behavior is "morphing" radically as a funtion of his mood.
Operations have large "case" constructs that depend on this "state" attribute.
Like larget  producedures, large conditional stmts are undesirable.
They are monolithic, and tend to make maintenance very difficult. The 
State pattern models individual states with derived classes of an inheritance
hierarchy with an "interface" object that knows its "current" state.
this partitions and localizes all state-specific responsiblilities; allowing for a cleaner
implementation of dynamic behavior that must change as internal state changes.
*/

#include <iostream>
using namespace std;

class BOSS{
public:
	BOSS(){
		mood_ = DilbertZone;
	}
	void decide(){
		if (mood_ == DilbertZone){
			cout << "Eenie, meenie,";
			cout << "mynie, moe.\n";
		}else if (mood_ == Sunny){
			cout << "You need it -- you";
			cout << "got it.\n";
		}
		toggle();
	}
	void direct(){
		if (mood_ == DilbertZone){
			cout << "My whim -- you're";
			cout << "nightmare.\n";
		}else if (mood_ == Sunny){
			cout << "Follow me.\n";
		}
		toggle();
	}
private:
	enum Disposition{ Sunny, DilbertZone};
	Disposition mood_;
	void toggle() { mood_ = (Disposition)(!mood_);}
};

void main(void)
{
	BOSS ph;
	for (int i = 0; i < 2 ; i++)
	{
		ph.decide();
		ph.decide();
		ph.direct();
	}

}