
/*
Frameworks are applications ( or subsystems) with "holes" in them.
Each framework specifies the infrastructure, superstructure, and flow of control
for its "domain", and the client of the framework may: exercise the framework,
or replace selection pieces. The Factory Method pattern addresses the notion of 
"creation" in the context of frameworks. In the examples, the framework knows 
WHEN a new document should be created, not WHAT kind of Document to create.
The "placeholder" Application::CreateDocument() has been declared by the framework,
and the client is expected to "fill in the black" for his/her specific document(s). Then,
when the client asks for Application::NewDocument(), the framework will subsequently
call the client's MyApplication::CreateDocument().
*/
#include <iostream>
#include <string.h>
using namespace std;

// Abstruct base class declared by framework
class Document{
public:
	Document(char *fn) { strcpy(Name,fn);}
	virtual void Open() = 0;
	virtual void Close() = 0;
	char* GetName() { return Name;}
private:
	char Name[32];
};

// Concrete derived class defined by client
class MyDocument : public Document{
public:
	MyDocument(char *fn) : Document(fn) {}
	void Open() { cout << "MyDocument: Open" << endl;}
	void Close() { cout <<"MyDocument:Close" << endl;}
};

// Framework declaration
class Application{
public:
	Application() : _index(0) { cout << "Application:ctor" << endl; }
	// Framework declares a "hole"  for client to customize
	virtual Document* CreateDocument( char* ) = 0;

	// The client will call this entry point of the framework
	void NewDocument( char* name ){
		cout << "Application: New Document()" << endl;
		// Framework calls the "hole"reserved for client customization
		_docs[_index] = CreateDocument( name );
		_docs[_index++]->Open();
	}
	void OpenDocument()  { }

	void ReportDocs();
private:
	int _index;
	// Framework uses Document's base class
	Document* _docs[16];
};

void Application::ReportDocs(){
	cout << "Application: ReportDocs()" << endl;
	for (int i = 0; i <_index; i++)
		cout << "          " << _docs[i]->GetName() << endl;
}

// Cuustomization of framework defined by client
class MyApplication : public Application{
public:
	MyApplication() { cout << "MyApplication: ctor" << endl; }
	// Client defines Framework's "hole"
	Document* CreateDocument(char *fn){
		cout << " MyApplication: CreateDocument() "<< endl;
		return new MyDocument( fn ); 
	}
};

void main(){
	// client's customization of the Framework
	MyApplication  myApp;
	
	myApp.NewDocument("foo");
	myApp.NewDocument("bar");
	myApp.ReportDocs();
}