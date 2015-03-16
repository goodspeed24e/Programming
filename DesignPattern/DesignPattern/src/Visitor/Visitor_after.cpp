#include <iostream>
using std::cout;

class Visitor;

class Color { 
public:
	virtual void accept( Visitor& ) = 0;
};

class Red : public Color { 
public:
	void accept( Visitor& );
	void eye() { cout << "Red::eye\n"; }
};

class Blu : public Color { 
public:
	void accept( Visitor& );
	void sky() { cout << "Blu::sky\n"; }
};

class Visitor { 
	public:
	virtual void visit( Red& ) = 0;
	virtual void visit( Blu& ) = 0;
};

class CountV : public Visitor {
public:
	CountV() { numRed_ = numBlu_ = 0; }
	virtual void visit( Red& ) {
		numRed_++; 
	}
	virtual void visit( Blu& ) {
		numBlu_++; 
	}

	void reportNum() {
		cout << "Reds " << numRed_ <<
			", Blus " << numBlu_ << "\n";
	}
 private:
	int  numRed_, numBlu_;
};

class CallV : public Visitor { 
public:
	virtual void visit( Red& r ) {
		r.eye(); 
	}
	virtual void visit( Blu& b ) { 
		b.sky(); 
	}
};

 void Red::accept( Visitor& v ) {
	v.visit( *this ); 
 }

 void Blu::accept( Visitor& v ) {
	v.visit( *this ); 
}

 /**
  * \brief
  * Visitor (adding ops)
  * 
  * an entry point for all future operations has been
  * add in the form of the accept() method. Each of the 
  * previous operations has been encapsulated in its own 
  * derived Visitor class. Any new operations simply require
  * addition of a new Visitor class.
  * 
  * \remarks
  * When we call accept() on the color object, dynamic binding
  * gets us to the correct derived class of color. Then when we call
  * visit() on the Visitor object, dynamic binding gets us to the 
  * correct derived class of Visitor. [Visitors and Colors can be passed
  * by address of passed by reference]
  * 
  */
 void main( void )
{
	Color* set[] = { new Red, new Blu,
	new Blu, new Red, new Red, 0 };
	CountV  countOp;
	CallV   callOp;
	for (int i=0; set[i]; i++) {
		set[i]->accept( countOp );
		set[i]->accept( callOp );
	}
		countOp.reportNum();
}