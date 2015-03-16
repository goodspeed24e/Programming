

/*
Purpose. Adapter desing pattern demo

Discussion. LegacyRectangle's interface is not compatible with the 
system that would like to reuse it. An abstract base class is created
that specifies the desired interface. An "adapter" class is defined
that publicly inherits the interface of the abstract class, and privately
inherits the implementation of the legacy comonent. This adapter class
"maps" or "impedance matches" the new interface to the old implementation.
*/

#include <iostream>
using namespace std;

typedef int Coordinate;
typedef int Dimension;

// Desired interface //
class Rectangle{
public:
	virtual void draw() = 0;
};

// Legacy component //
class LegacyRectangle{
public:
	LegacyRectangle( Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2){
		x1_ = x1 ; y1_ = y1; x2_ = x2; y2_ = y2;
		cout << "LegacyRectangle: Create . (" << x1_ << "," << y1_ << ") => (" << x2_ << "," << y2_ << ")" << endl;
	}
   void oldDraw() {
      cout << "LegacyRectangle:  oldDraw.  (" << x1_ << "," << y1_ << ") => (" << x2_ << "," << y2_ << ")" << endl;
   }
private:
	Coordinate x1_;
	Coordinate x2_;
	Coordinate y1_;
	Coordinate y2_;
};

class RectangleAdapter: public Rectangle, private LegacyRectangle{
public:
	RectangleAdapter( Coordinate x, Coordinate y, Dimension w, Dimension h):
	  LegacyRectangle( x, y, x+w, y+h)
	  {
		cout << "RectangleAdapter: create.  (" << x << "," << y  << "), width = " << w << ", height = " << h << endl; 
	  }
   virtual void draw() {
      cout << "RectangleAdapter: draw." << endl;
      oldDraw(); 
   }
};

void main() {
   Rectangle*  r = new RectangleAdapter( 120, 200, 60, 40 );
   r->draw();
}