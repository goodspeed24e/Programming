
/*
 * Memento design pattern
 *  A memento is an object that sotres a snapshot of internal 
 * state of another object. It can be leveraged to support multi-
 * level undo of the Command pattern. In this example, before 
 * a command is run against the Number object, Number's current
 * state is saved in Command's static memento history list, and
 * the command itself is saved in the static command history list. 
 * undo simply "pops" the memento history list and reinstates Number's
 * state from the memento. Redo() "pops" the command history list. Note
 * that Number's encapsulation is preserved, and Memento is wide open
 * to Number.
*/

#include <iostream>
using namespace std;

#define MAXSTEP 6

class Memento {
public:
	Memento(int val) { _state = val; }
private:
	// not essential, but p287 suggests this
	friend class Number;
	int _state;
};

class Number {
public:
	Number( int value)		{ _value = value;}
	void dubble()				{ _value = 2 * _value;}
	void half()					{ _value = _value / 2;}
	int getValue()				{ return _value; }
	Memento *createMemento( ) {
		return new Memento(_value);
	}
	void reinstateMemento(Memento* m) {
		_value = m->_state;
	}
private:
	int _value;
};

class Command {
public:
	typedef void (Number::*Action)();
	Command(Number* receiver, Action action) {
		_receiver = receiver;
		_action = action;
	}
	virtual void execute() {
		_mementoList[_numCommands] = _receiver->createMemento();
		_commandList[_numCommands] = this;
		if (_numCommands > _highWater) 
			_highWater = _numCommands;
		_numCommands++;
		(_receiver->*_action)();
	}
	static void undo() {
		if (_numCommands == 0) {
			cout << "*** Attempt to run off the end!! ***" << "\n";
			return ;
		}
		_commandList[_numCommands-1]->_receiver->reinstateMemento(
			_mementoList[_numCommands-1]);
		_numCommands--;
	}
	void static redo() {
		if (_numCommands > _highWater) {
			cout << "*** Attempt to run off the end!! ***" << "\n";
			return ;
		}
		(_commandList[_numCommands]->_receiver->*(
			_commandList[_numCommands]->_action)) ();
		_numCommands++;
	}
protected:
	Number* _receiver;
	Action		_action;
	static Command* _commandList[MAXSTEP];
	static Memento* _mementoList[MAXSTEP];
	static int				_numCommands;
	static int				_highWater;
};

Command* Command::_commandList[];
Memento* Command::_mementoList[];
int      Command::_numCommands = 0;
int      Command::_highWater   = 0;

void main() {
   int i;
   cout << "Integer: ";
   cin >> i;
   Number*   object = new Number(i);

   Command*  commands[3];
   commands[1] = new Command( object, &Number::dubble );
   commands[2] = new Command( object, &Number::half );

   cout << "Exit[0], Double[1], Half[2], Undo[3], Redo[4]: ";
   cin >> i;

   while (i)
   {
      if (i == 3)
         Command::undo();
      else if (i == 4)
         Command::redo();
      else
         commands[i]->execute();
      cout << "   " << object->getValue() << endl;
      cout << "Exit[0], Double[1], Half[2], Undo[3], Redo[4]: ";
      cin >> i;
   }
}

// Integer: 11
// Exit[0], Double[1], Half[2], Undo[3], Redo[4]: 2
//    5
// Exit[0], Double[1], Half[2], Undo[3], Redo[4]: 1
//    10
// Exit[0], Double[1], Half[2], Undo[3], Redo[4]: 2
//    5
// Exit[0], Double[1], Half[2], Undo[3], Redo[4]: 3
//    10
// Exit[0], Double[1], Half[2], Undo[3], Redo[4]: 3
//    5
// Exit[0], Double[1], Half[2], Undo[3], Redo[4]: 3
//    11
// Exit[0], Double[1], Half[2], Undo[3], Redo[4]: 3
// *** Attempt to run off the end!! ***
//    11
// Exit[0], Double[1], Half[2], Undo[3], Redo[4]: 4
//    5
// Exit[0], Double[1], Half[2], Undo[3], Redo[4]: 4
//    10
// Exit[0], Double[1], Half[2], Undo[3], Redo[4]: 4
//    5
// Exit[0], Double[1], Half[2], Undo[3], Redo[4]: 4
// *** Attempt to run off the end!! ***
//    5