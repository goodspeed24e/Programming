#include <iostream>
using namespace std;

class Color {
public:
   virtual void count() = 0;
   virtual void call()  = 0;
   static void reportNum() {
      cout << "Reds " << numRed_ <<
      ", Blus " << numBlu_ <<endl; }
protected:
   static int numRed_, numBlu_;
};
int Color::numRed_ = 0;
int Color::numBlu_ = 0;

class Red : public Color { 
public:
   void count() { numRed_++; } 
   void call() { eye(); }
   void eye() { cout << "Red::eye\n";}
};

class Blu : public Color { 
public:
   void count() { numBlu_++; }
   void call() { sky(); }
   void sky() { cout << "Blu::sky\n";}
};

/**
 * \brief
 * Visitor (adding ops)
 * 
 * adding new operations requires modifying all the current classes.
 * if we introduce an extra level of indirection( a Visitor hierarchy),
 * then operations capable of be added without modifying any existing code.
 *
 * \remarks
 * Write remarks for main here.
 * 
 */
void main( void )
{
   Color* set[] = { new Red, new Blu,
      new Blu, new Red, new Red, 0 };   // Red::eye
   for (int i=0; set[i]; i++) {         // Blu::sky
      set[i]->count();                  // Blu::sky
      set[i]->call(); }                 // Red::eye
    Color::reportNum();                 // Red::eye
} 