
// Purpose. Memento Design Pattern

 /* 1. Assign the roles of "caretaker" and "originator"
  * 2. Create a "memento" class and declare the originator a friend
  * 3. Caretaker knows when to "check point" the originator
  * 4. Originator creates a memento and copies its state to the memento
  * 5. Caretaker holds on to ( but cannot peek in to) the memento
  * 6. Caretaker knows when to "roll back" the originator
  * 7. Originator reinstates itself using the saved state in the memento
  */

#include <iostream>
#include <string>
using namespace std;

// 2. create a "Memento" class and declare the originator a friend
class Memento {
	friend class Stack;
	int *items, num;
	Memento(int *arr, int n) {
		items = new int[num = n];
		for ( int i = 0; i < num; i++) 
			items[i] = arr[i];
	}
public:
	~Memento() { delete [] items;}
};

// 1. Stack is the "originator"
class Stack{
private:
	int items[10], sp;
public:
	Stack() { sp = -1; }
	void push( int in) {
		items[++sp] = in;
	}
	int pop() {
		return items[sp--];
	}
	bool isEmpty() {
		return sp == -1;
	};
	// 4. Originator creates a memento and copies its state to the memento
	Memento* checkPoint() {
		return new Memento(items, sp+1);
	}
	// 7. Originator reinstates itself using the save state in the memento
	void RollBack( Memento* m) {
		sp = m->num - 1;
		for (int i = 0 ; i < m->num; i ++)
			items[i] = m->items[i];
	}
	friend ostream& operator<< (ostream& os, const Stack& s) {
		string buf("[ ");
		for (int i = 0 ; i < s.sp+1; i++) {
			buf += s.items[i]+48;
			buf += ' ';
		}
		buf += ']';
		return os << buf;
	}
};

// 1. main is the caretaker
void main()
{
	Stack s;
	for (int i = 0 ; i < 5; i++)
		s.push(i);
	cout << "stack is " << s << "\n";
	// 3. caretaker knows when to save
	Memento* first = s.checkPoint();

	// 5. caretaker holds on to memento
	for ( int i = 5; i < 10; i++ )
		s.push(i);
	cout << "stack is " << s << "\n";
	// 3. caretaker know when to save
	Memento *second = s.checkPoint();

	// 5. caretaker holds on to memento
	cout << "popping stack:";
	while ( !s.isEmpty()) {
		cout << s.pop() << "  " ;
	}
	cout << "stack is " << s << "\n";
	// 6. caretaker knows when to undo
	s.RollBack(second);
	cout << "second is" << s << "\n";
	s.RollBack(first);
	cout << "first is " << s << "\n";
	cout << "popping stack:";
	while (!s.isEmpty())
		cout << s.pop() << " ";
	delete first;
	delete second;
}


