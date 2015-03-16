
/*
 * TypedMessage - embellished Observer, decoupled messaging
 *
 * Messages inherit from TypedMessage<self>
 * Message listeners inherit from many Message::Handlers
 * Application tells message to publish/broadcast/nofigy
 * Messages are the subject( receive registeratiions from subscribers)
 * Subsystems are the observers ( receive broadcast message)
 * TypedMessage accomodates everthing: registeration, containment, and
 *   notification of observers
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Handler;

// vector<TypedMessage<On>::Handler*> TypedMessage<On>::registry;

template<class T>
class TypedMessage {
private:
	static vector<Handler* > registry;
public:
	class Handler {
	public: 
		Handler() { 
			TypedMessage<T>::registerHandler(this);
		}
		virtual void handleEvent( const T* t) = 0;
	};

	virtual void notify() {
		for (int i = 0; i < registry.size(); i++)
			registry.at(i)->handleEvent( (T*) this);
	}
	static void registerHandler( Handler *h){
		registry.push_back(h);
	}
};

class On: public TypedMessage<On> {
private:
	string comment;
public:
	On(string str)			{ comment = str;}
	void start() const		{ 
		cout << "OnEvent.start - " << comment << "\n";
	}
};

vector<TypedMessage<On>::Handler*> TypedMessage<On>::registry;

class Off : public TypedMessage<Off> {
private:
	string comment;
public:
	Off(string str)			{ comment = str;}
	void stop() const		{
		cout << "OffEvent.Stop - " << comment << "\n";
	}
};

vector<TypedMessage<Off>::Handler*> TypedMessage<Off>::registry;

class MasterConsole: 
	public On::Handler,
	public Off::Handler {
public:
	void handleEvent( const On* msg) {
		cout << "MasterConsole - "; 
		msg->start();
	}
	void handleEvent( const Off* msg) {
		cout << " MatsterConsole - ";
		msg->stop();
	}
};

class PowerMonitor: public On::Handler
{
public:
	void handleEvent( const On* msg) {
		cout << "PowerMonitor - ";
		msg->start();
	}
};

void main( void ) {
   MasterConsole  mc;
   PowerMonitor   pm;
   On oneEvent( "lights" );  Off thrEvent( "elevators" );
   On twoEvent( "hvac" );    Off fouEvent( "frontDoor" ); 
   oneEvent.notify();  twoEvent.notify();
   thrEvent.notify();  fouEvent.notify();
}

// MasterConsole - OnEvent.start - lights
// PowerMonitor - OnEvent.start - lights
// MasterConsole - OnEvent.start - hvac
// PowerMonitor - OnEvent.start - hvac
// MasterConsole - OffEvent.stop - elevators
// MasterConsole - OffEvent.stop - frontDoor

