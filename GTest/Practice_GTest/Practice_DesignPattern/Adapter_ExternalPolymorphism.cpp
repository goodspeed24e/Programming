

// Purpose. Adapter desing pattern ( external polymorphism demo)
/*
1. specify the new desired interface
2. Desing a "wrapper" class that can "impedance match" the old to the new
3. the client uses( is coupled to) the new interface
4. the adapter/wrapper "maps" to the legacy implementation
*/

#include <iostream>
using namespace std;

class ExecuteInterface { 
public:												// 1. Specify the new i/f
   virtual ~ExecuteInterface() { }
   virtual void execute() = 0;
};

template <class TYPE>                             // 2. Design a "wrapper" or "adapter" class
class ExecuteAdapter : public ExecuteInterface {
public:
   ExecuteAdapter( TYPE* o, void (TYPE::*m)() ){
	   object = o;  method =m; 
   }
   ~ExecuteAdapter(){
	   delete object; 
   }
   // 4. The adapter/wrapper "maps" the new to the legacy implementation
   void execute()             /* the new */     { 
	   (object->*method)(); 
   }
private:                             
   TYPE* object;                                  // ptr-to-object attribute
   void (TYPE::*method)();    /* the old */       // ptr-to-member-function
};                                                //   attribute

// The old: three totally incompatible classes    // no common base class,
class Fea { 
public:                               // no hope of polymorphism
   ~Fea(){
	   cout << "Fea::dtor" << endl; 
   }
   void doThis() { 
	   cout << "Fea::doThis()" << endl; 
   }
};

class Feye { 
public:
   ~Feye()       { cout << "Feye::dtor" << endl; }
   void doThat() {
	   cout << "Feye::doThat()" << endl; 
   }
};

class Pheau { 
public:
   ~Pheau()          { cout << "Pheau::dtor" << endl; }
   void doTheOther() {
	   cout << "Pheau::doTheOther()" << endl;
   }
};

/* the new is returned */ 
ExecuteInterface** initialize() {
   ExecuteInterface** array = new ExecuteInterface*[3]; /* the old is below */
   array[0] = new ExecuteAdapter<Fea>(   new Fea(),     &Fea::doThis       );
   array[1] = new ExecuteAdapter<Feye>(  new Feye(),    &Feye::doThat      );
   array[2] = new ExecuteAdapter<Pheau>( new Pheau(),   &Pheau::doTheOther );
   return array;
}

void main( void ) {
   ExecuteInterface** objects = initialize();
	int i;
   for ( i=0; i < 3; i++) 
	   objects[i]->execute();  // 3. Client uses the new
                                                     //    (polymporphism)
   for (i=0; i < 3; i++) delete objects[i];
   delete objects;
}