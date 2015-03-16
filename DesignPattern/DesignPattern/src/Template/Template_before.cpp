// Purpose.  No reuse

#include <iostream>
using namespace std;

class Template_TemplateOne {
   void a() { cout << "a  "; }
   void b() { cout << "b  "; }
   void c() { cout << "c  "; }
   void d() { cout << "d  "; }
   void e() { cout << "e  "; }
public:
   void execute() { a();  b();  c();  d();  e(); }
};

class Template_TemplateTwo {
   void a()  { cout << "a  "; }
   void _2() { cout << "2  "; }
   void c()  { cout << "c  "; }
   void _4() { cout << "4  "; }
   void e()  { cout << "e  "; }
public:
   void execute() { a();  _2();  c();  _4();  e(); }
};

void main( void ) {
   Template_TemplateOne first;
   first.execute();
   cout << '\n';
   Template_TemplateTwo second;
   second.execute();
   cout << '\n';
}