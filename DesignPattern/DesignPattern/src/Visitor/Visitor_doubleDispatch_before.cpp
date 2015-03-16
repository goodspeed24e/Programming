#include <iostream>
using std::cout;

int  current = 0;
enum CmdTyp { OnT, OffT };
 
class Cmd { 
public:
   virtual CmdTyp typ() = 0;
};
class On : public Cmd { 
public:
   CmdTyp typ() { return OnT; }
};
class Off : public Cmd {
public:
   CmdTyp typ() { return OffT; }
};

class State {
public:
   virtual void process( Cmd* c ) {
      cout << "ERROR\n"; }
};
class One : public State { 
public:
   void process( Cmd* c ) {
      if (c->typ() == OnT) {
         current = 1;
         cout << "One,On => Two\n"; }
      else if (c->typ() == OffT)
         State::process( c );
   }
};
class Two : public State { 
public:
   void process( Cmd* c ) {
      if (c->typ() == OnT)
         State::process( c );
      else if (c->typ() == OffT) {
         current = 0;
         cout << "Two,Off => One\n"; }
   }
};
 
State* states[] = { new One, new Two };
 
/**
 * \brief
 * the State derived classes must query the type of the Cmd
 * objects they receive, in order to identify what the next course
 * of action is. "case" stmts are always a maintenance headache.
 * 
 * \remarks
 * Write remarks for main here.
 * 
 */
void main( void )
{
   Cmd* c[] = { new Off,
        new On, new Off, new Off, 0 };
   for (int i=0; c[i]; i++)
      states[current]->process( c[i] );
}
 
// ERROR
// One,On => Two
// Two,Off => One
// ERROR