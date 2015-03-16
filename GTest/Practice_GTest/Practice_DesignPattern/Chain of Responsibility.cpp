#include "iostream"
#include "vector"
#include "ctime"
using namespace std;

class CBase{
	CBase *next;						// 1. "next" pointer in the base class
public:
	CBase() {next = 0;}
	void setNext(CBase *n) { next = n;}
	void add(CBase* n) {
		(next) ?  next->add(n) : next = n;
	}
	// 2. the "Chain" method in the base class always delegates to the next obj
	virtual void handle(int i) {
		next->handle(i);
	}
};

class Handle1:public CBase{
public:
	void handle(int i){
		if (rand()%3){					// 3. Don't handle requests 3 time out of 4
			cout << "H1 passed " << i << " ";
			CBase::handle(i);			// 3. Deletate to the base class
		}else{
			cout << "H1 handle " << i << " ";
		}
	}
};

class Handle2: public CBase{
	// virtual
	void handle(int i){
		if (rand()%3) {
			cout << "H2 passed " << i << " ";
			CBase::handle(i);
		}else{
			cout << "H2 handled "<< i << " ";
		}
	}
};

class Handle3: public CBase{
	// virtual 
	void handle(int i)
	{
		if (rand()%3){
			cout << "H3 passed " << i << " ";
			CBase::handle(i);
		}else{
			cout << "H3 handled" << i << " ";
		}
	}
};

void main(void){
	//srand( time(NULL));
	Handle1 root;
	Handle2 two;
	Handle3 thr;
	root.add(&two);
	root.add(&thr);
	thr.setNext(&root);
	for (int i = 0 ; i < 10 ; i++){
		root.handle(i);
		cout << "\n";
	}
}