#include <iostream>
using std::cout;

class  DivObs { 
 public:
	DivObs(int);
	void update(int);
private:
	int div_;
 };

class ModObs {
public:
	ModObs(int);
	void update(int);
private:
	int div_;
};

class Subject {
public:
	Subject();
	void setVal(int);
private:
	int val_;
	DivObs div_;
	ModObs mod_;
};

Subject::Subject() : div_(4), mod_(3) {}

void Subject::setVal(int v) {
	val_ = v;
	div_.update(val_);
	mod_.update(val_);
};

DivObs::DivObs( int d ){
	div_ = d;
}

void DivObs::update(int v){
	cout << v << " div " << div_ << " is " << v/div_ << "\n";
}

ModObs::ModObs(int d) { div_ = d;}

void ModObs::update(int v){
	cout << v << " mod " << div_ << " is " << v % div_ << "\n";
}

/**
 * \brief
 * Observer
 * 
 * Subject has hard-wired the number and type
 * of "dependent" objects, the compiler must 
 * have the declaration of the concrete Obs
 * classes to cimpile Subject's decl, the Obs
 * class execise no reuse of i/f or impl, and
 * Subject "pushes" updates to the Obs object.
 */

void main(void)
{
	Subject subj;
	subj.setVal(14);
}
