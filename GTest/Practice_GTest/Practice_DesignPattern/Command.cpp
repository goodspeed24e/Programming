//Command
// 1. Create a class that encapsulates some number of the following:
//		a. "receiver" object
//		 the mehtod to invoke
//		 the arguments to pass
// 2. Instantiate an object for each "callback"
// 3. Pass each object to its future "sender"
// 4. When the sender is ready to callback to the receiver, it calls execute()

#include <iostream>
#include <string>
using namespace std;

class Person;
class Command{					// 1. create a class that encapsulates an object
	Person* object;				// and a member function
	void (Person::*method) ();	// a pointer to a member function ( the attribute's name is "method")
public:
	Command(Person* obj = 0, void (Person::*meth)() = 0 ){
		object = obj;			// the argument's name is "meth"
		method = meth;
	}
	void execute(){
		(object->*method)();	// invoke the method on the object
	}
};

class Person{
	string name;				// cmd is a "black box", it's a method invocation promoted to "full object status"
	Command cmd;	
public:
	Person(string n, Command c): cmd(c){
		name = n;
	}
	void talk(){				// "this" is the sender, cmd has the receiver
		cout << name << " is talking" << endl;
		cmd.execute();
	}
	void passOn(){
		cout << name << " is passing on" << endl;
		cmd.execute();
	}
	void gossip(){
		cout << name << " is gossiping" << endl;
		cmd.execute();
	}
	void listen(){
		cout << name << " is listening" << endl;
	}
};

void main(void)
{
	// Fred will "execute" Barney which will result in a call to Passon()
	// Barney will "execute" Bettery which will result in a call to gossop()
	// Betty will "execute" wilma which will result in a call to listen()
	Person wilma("Wilma", Command());
	// 2. instantiate an object for each "callback"
	// 3. pass each object to its future "sender"
	Person betty( "Betty"	, Command( &wilma, &Person::listen ) );
	Person barney( "Barney"	, Command( &betty, &Person::gossip ) );
	Person fred( "Fred"		, Command( &barney,&Person::passOn ) );
	fred.talk();
}