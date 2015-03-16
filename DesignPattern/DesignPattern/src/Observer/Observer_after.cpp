#include <iostream>
using std::cout;

class Subject {
public:
	Subject();
	void attach( class Obs*);
	void setVal( int);
	int getVal();
	void notify();
private:
	class Obs* obs_[10];
	int num_, val_;
};

class Obs {
public:
	virtual void update() = 0;
protected:
	Subject* sub_;
	int div_;
};

class DivObs: public Obs{
public:
	DivObs( Subject*, int);
	void update();
};

class ModObs: public Obs{
public:
	ModObs( Subject*, int);
	void update();
};

Subject::Subject() { num_ = 0;}

int Subject::getVal() { return val_;}

void Subject::attach(Obs* O) {
	obs_[num_++] = O;
}

void Subject::setVal(int v) {
	val_ = v; notify();
}

void Subject::notify() {
	for ( int i = 0 ;  i < num_; i++)
		obs_[i]->update();
}

DivObs::DivObs( Subject* s, int d) {
	sub_ = s; div_ = d;
	sub_->attach(this);
}

void DivObs::update() {
	int v = sub_->getVal();
	cout << v << " div " << div_ << " is " << v / div_ << "\n";
}

ModObs::ModObs(Subject *s, int d) {
	sub_ = s; div_ = d;
	sub_->attach(this);
}

void ModObs::update() {
	int v = sub_->getVal();
	cout << v << " mod " << div_ <<" is " << v % div_ << "\n";
}

/**
 * \brief
 * Subject is decoupled from the number, type,
 * and declaration of concrete Obs subclasses;
 * the Obs objects accept polymorphism; and
 * Subject broadcasts that a change has occurred
 * followed by Obs objects requesting just the info
 * that they want.
 */
void main(void)
{
	Subject subj;
	DivObs divObs1(&subj, 4);
	DivObs divObs2(&subj, 3);
	ModObs modObs3(&subj, 3);
	subj.setVal(14);
}