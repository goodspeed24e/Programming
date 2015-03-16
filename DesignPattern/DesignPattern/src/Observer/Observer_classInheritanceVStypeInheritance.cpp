
/*
 * Observer design patter , class inheritance vs type inheritance
 * 
 * SensorSystem is the "subject". Lighting, Gates, and Surveillance are
 * the "views". The subject is only coupled to the "abstraction" of AlarmListener.
 *
 * An object's class defines how the object is implemented. in contrast, an
 * object's type only refers to its interface. Class inheritance defines an
 * object's implementation in terms of another object's implementation. Type
 * inheritance describes when an object can be used in place of another.
 */

#include <iostream>
#include <vector>
using namespace std;

class AlarmListener {
public:
	virtual void alarm() = 0;
};

class SensorSystem {
private:
	vector <AlarmListener*> listeners;
public:
	void attach(AlarmListener* al) {
		listeners.push_back(al);
	}
	void soundTheAlarm() {
		for ( int i = 0; i < listeners.size(); i++) {
			listeners[i]->alarm();
		}
	}
};

class Lighting: public AlarmListener {
public:
	void alarm() { cout << " lights up" << "\n"; }
};

class Gates: public AlarmListener {
public:
	void alarm() { cout << "gates close" << "\n"; }
};

class CheckList {
private:
	virtual void localize()	{ cout << " establish a perimeter" << "\n";}
	virtual void isolate()	{ cout << " isolate the grid" << "\n";}
	virtual void identify()	{ cout << " identify the source" << "\n";}
public:
	void byTheNumbers() {
		// Template method design pattern
		localize();
		isolate();
		identify();
	}
};
                           
class Surveillance:
	public CheckList, // class inheri.
	public AlarmListener // type inheritance
{
private:
	void isolate() {		cout << " train the cameras" << "\n";}
	void alarm() {
		cout << "Surveillance - by the numbers:" << "\n";
		byTheNumbers();
	}
};

void main(void) {
	SensorSystem ss;
	ss.attach(&Gates());
	ss.attach(&Lighting());
	ss.attach(&Surveillance());
	ss.soundTheAlarm();
}

// gates close
// lights up
// Surveillance - by the numbers:
//    establish a perimeter
//    train the cameras
//    identify the source

