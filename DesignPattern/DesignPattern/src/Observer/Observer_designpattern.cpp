
/*
 * Observer design pattern
 * 1. Model the "indpendent" functioinality with a "subject" abstraction
 * 2. Model the "dependent" functionality with "observer" hierarchy
 * 3. The Subject is coupled only to the Observer base class
 * 4. Observers register themselves with the Subject
 * 5. The subject broadcasts events to all registered Observers
 * 6. Observers "pull" the information they need from the Subject
 * 7. Client configures the number and type of Observers
 */
#include <iostream>
#include <vector>
using namespace std;

// 1. "independent" functionality
class Subject {
private:
	// coupled only to "interface"
	vector <class Observer*> views;
	int value;
public:
	void attach(Observer* obs)	{ views.push_back(obs);}
	void setVal(int val)					{ value = val; notify();}
	int	getVal()							{ return value;}
	void notify();
};

// 2. "dependent" functionality
class Observer{
private:
	Subject* model;
	int denom;
public:
	Observer( Subject* mod, int div) {
		model = mod, denom = div;
		// 4. Observers register themselves with the Subject
		model->attach(this);
	}
	virtual void update() = 0;
protected:
	Subject*	getSubject() { return model; }
	int			getDivisor() { return denom;}
};

void Subject::notify(){
	// 5. publisher broadcasts
	for ( int i = 0; i < views.size(); i++)
		views[i]->update();

}

class DivObserver: public Observer{
public:
	DivObserver(Subject* mod, int div) : Observer( mod, div) {}
	void update() {
		// 6. "pull" information of interest
		int v = getSubject()->getVal();
		int d = getDivisor();
		cout << v << " div " << d << " is " << v / d << "\n";
	}
};

class ModObserver: public Observer {
public:
	ModObserver(Subject* mod, int div): Observer(mod, div) {}
	void update() {
		// 6. "pull" information of interest
		int v = getSubject()->getVal();
		int d = getDivisor();
		cout << v << " div " << d << " is " << v/d << "\n";
	}
};

void main(void) 
{
	Subject subj;
	// 7. Client configures the number and type of Observers
	DivObserver divObs1( &subj, 4);
	DivObserver divObs2( &subj, 3);
	ModObserver modObs3( &subj, 3);
	subj.setVal(14);
}