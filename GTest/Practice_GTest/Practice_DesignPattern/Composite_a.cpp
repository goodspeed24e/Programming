
/*
    Strategy. Use recursive composition to create a heterogeneous aggregate
	that can be treated homogeneously.

	Benefint. No more type checking and type casting( coupling between Dir and File is gone,
	Dir is only coupled to abstract base class)
*/

#include <iostream>
using namespace std;

class AbsFile{
public:
	virtual void ls() = 0;
protected:
	char		name_[16];
	static int indent_;
};

int AbsFile::indent_ = 0;

class File: public AbsFile{
public:
	File( char* n){
		strcpy(name_, n);
	}
	void ls(){
		for (int i = 0; i < indent_; i++)
			cout << ' ';
		cout << name_ << endl;
	}
};

class Dir: public AbsFile{
public:
	Dir(char* n){
		strcpy( name_, n);
		total_ = 0;
	}
	void add( AbsFile* f){
		files_[total_++] = f;
	}
	void ls(){
		for (int i=0; i < indent_; i++)
			cout << ' ';
		cout << name_ << ":" << endl;
		indent_ +=3;
		for (int i = 0; i < total_; i++)
			files_[i]->ls();
		indent_ -= 3;
	}
private:
	AbsFile*		files_[10];
	int				total_;
};

void main( void )
{
	Dir one("1"), two("2"), thr("3");
	File	a("a"), b("b"), c("c"), d("d"), e("e");
	one.add( &a);
	one.add( &two);
	one.add( &b);
	one.add( &c);
	one.add( &d);
	one.add( &thr);
	one.add( &e);
	one.ls();
}