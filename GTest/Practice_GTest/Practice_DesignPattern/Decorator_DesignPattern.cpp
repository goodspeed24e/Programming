

/*
1. create a "lowest common denominator" that makes classes interchangeable
2. create a second level base class for optional  functionality
3. "Core" class and "Decorator" class declare an "isa" relationship
4. Decorator class "hasa" instance of the "lowest common denominator" 
5. Decorator class delegates to the "hasa" object
6. create a Decorator derived class to each optional embellishment
7, Decorator derived class delegate to base class AND add extra stuff
8. Client has the responsibility to compose desired configurations

*/

#include <iostream>
using namespace std;

class Widget{ 
public:
	virtual void draw() = 0;			// 1. lowest common denom
};

class TextField: public Widget{	// 3. "Core" class & "isa"
private:
	int width, height;
public:
	TextField(int w, int h){
		width = w; height = h;
	}
	void draw(){ 
		cout << "TextField: " << width <<", " << height << endl;
	}
};

class Decorator: public Widget{	// 2. 2nd level base
private:										// 3. "isa" relationship
	Widget* wid;							//	4. "hasa" relationship
public:
	Decorator ( Widget *w) { wid = w;}
	void draw() {							// Delegation
		cout << "  Delegation" << endl;
			wid->draw();
	}		
};

class BorderDecorator: public Decorator{			// 6. optional embellishment
public:
	BorderDecorator(Widget* w):Decorator(w){}
	void draw() {
		Decorator::draw();										// 7. Deledate to base class and add extra stuff
		cout << "  BorderDecorator" << endl;
	}
};

class ScrollDecorator: public Decorator{
public:
	ScrollDecorator(Widget* w):Decorator(w){}
	void draw() {
		Decorator::draw();
		cout << "  ScrollDecorator" << endl;
	}
};

void main( void ){
	// 8. client has the responsibility to compose desire confgurations
	Widget* aWidget = 
		//new BorderDecorator(
		//	new BorderDecorator(
			new ScrollDecorator(
				new TextField( 80, 24) );// ) );
	aWidget->draw();
}
