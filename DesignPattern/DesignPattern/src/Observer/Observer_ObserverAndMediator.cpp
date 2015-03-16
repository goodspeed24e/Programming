
/*
 *  Observer and Mediator Demo
 * Observer -	1. Sender is coupled to a Receiver interface
 *						2. Receivers register with Sender
 *						3. Sender broadcasts ( in the blind) to all Receivers
 *
 * Mediator -	4. Sender(s) has har ndle to Mediator
 *						5. Mediator has handle to Receiver(s)
 *						6. Sender(s) sends to Mediator
 *						7. Mediato sends to Receiver(s)
 */

#include <Windows.h>
#include <iostream>
#include <vector>
using namespace std;

void gotoxy(int x, int y) 
{
	COORD coord; 
	coord.X = x; coord.Y = y; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class Observer{
public:
	virtual void update(int) = 0;
};

class Mediator{
private:
	// 1. sender is coupled to an interface
	vector<Observer*> groups[3];
public:
	// 1. sender is coupled to an interface
	enum Message { ODD, EVEN, THREE};
	void attach(Observer* o, Message type){
		groups[type].push_back(o);
	}
	// 3, 7. sender/mediator broadcasts
	void disseminate(int num) {
		if (num % 2 == 1)
			for (int i = 0 ; i < groups[0].size(); i++)
				groups[0][i]->update(num);
		else
			for ( int i = 0 ; i < groups[1].size(); i++)
				groups[1][i]->update(num);
		if (num%3==0)
			for ( int i = 0 ; i < groups[2].size(); i++)
				groups[2][i]->update(num);
	}
};

class OddObserver: public Observer {
private:
	int col, row;
public:
	OddObserver(Mediator& med, int c) {
		col = c; row = 3;
		gotoxy(col, 1); cout << "Odd";
		gotoxy(col, 2); cout << "-----";
		// 2, 5. Receivers register with Sender
		med.attach(this, Mediator::ODD);
	}
	void update(int num){ gotoxy(col, row++); cout << num; }
};

class EvenObserver : public Observer {
private:
   int col, row;
public:
   EvenObserver( Mediator& med, int c ) {
      col = c;           row = 3;
      gotoxy( col, 1 );  cout << "/2";
      gotoxy( col, 2 );  cout << "--";
      med.attach( this, Mediator::EVEN );
   }
   void update( int num ) { gotoxy( col, row++ ); cout << num; }
};

class ThreeObserver : public Observer {
private:
   int col, row;
public:
   ThreeObserver( Mediator& med, int c ) {
      col = c;           row = 3;
      gotoxy( col, 1 );  cout << "/3";
      gotoxy( col, 2 );  cout << "--";
      med.attach( this, Mediator::THREE );
   }
   void update( int num ) { gotoxy( col, row++ );  cout << num; }
};

// 6. sender sends to Mediator
class Publisher {
public:
	Publisher ( Mediator& med) {
		for ( int i = 1; i< 10; i++)
			med.disseminate(i);
	}
};

void main(void)
{
	Mediator mediator;
	OddObserver( mediator, 1);
	EvenObserver( mediator, 11);
	ThreeObserver( mediator, 21);
	// 4. sender has handle to Mediator
	Publisher producer(mediator);
}

