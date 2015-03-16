#include <iostream>
using namespace std;
 
class Base { public:
   virtual void process1( Base& ) = 0;
   virtual void process2( class A& ) = 0;
   virtual void process2( class B& ) = 0;
   virtual void process2( class C& ) = 0;
};
 
class A : public Base { public:
   /*virtual*/ void process1( Base& second ) { second.process2( *this ); }
   /*virtual*/ void process2( class A& first ) {
      cout << "first is A, second is A\n"; }
   /*virtual*/ void process2( class B& first ) {
      cout << "first is B, second is A\n"; }
   /*virtual*/ void process2( class C& first ) {
      cout << "first is C, second is A\n"; }
};
 
class B : public Base { public:
   /*virtual*/ void process1( Base& second ) { second.process2( *this ); }
   /*virtual*/ void process2( class A& first ) {
      cout << "first is A, second is B\n"; }
   /*virtual*/ void process2( class B& first ) {
      cout << "first is B, second is B\n"; }
   /*virtual*/ void process2( class C& first ) {
      cout << "first is C, second is B\n"; }
};
 
class C : public Base { public:
   /*virtual*/ void process1( Base& second ) { second.process2( *this ); }
   /*virtual*/ void process2( class A& first ) {
      cout << "first is A, second is C\n"; }
   /*virtual*/ void process2( class B& first ) {
      cout << "first is B, second is C\n"; }
   /*virtual*/ void process2( class C& first ) {
      cout << "first is C, second is C\n"; }
};
 
/**
 * \brief
 * Double dispatch (within a single hierarchy)
 * We would like to declare a function like:
 * void process( virtual Base* object1, virtual Base* object2 )
 * that does the right thing based on the type of 2 objects that come from
 * a single inheritance hierarchy.  The only problem is that the keyword
 * "virtual" may not be used to request dynamic binding for an object being
 * passed as an argument.  C++ will only "discriminate" the type of an object
 * being messaged, not the type of an object being passed.  So in order for
 * the type of 2 objects to be discriminated, each object must be the
 * receiver of a virtual function call.  Here, when process1() is called on
 * the first object, its type becomes "known" at runtime, but the type of
 * the second is still UNknown.  process2() is then called on the second
 * object, and the identity (and type) of the first object is passed as an
 * argument.  Flow of control has now been vectored to the spot where the
 * type (and identity) of both objects are known.
 * 
 * \remarks
 * Write remarks for main here.
 */
void main( void ) {
   Base* array[] = { &A(), &B(), &C() };
   for (int i=0; i < 3; i++)
      for (int j=0; j < 3; j++)
         array[i]->process1( *array[j] );
}
 
// first is A, second is A
// first is A, second is B
// first is A, second is C
// first is B, second is A
// first is B, second is B
// first is B, second is C
// first is C, second is A
// first is C, second is B
// first is C, second is C