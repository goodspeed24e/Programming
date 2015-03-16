/*
1. Design an "extra level of indirection" wrapper class
2. The wrapper class holds a pointer to the real class
3. The pointer is initialized to null
4. when a request comes in, the real object is created "on first use" (aka lazy intialization)
5. The request is always delegated
*/

#include <iostream>
using namespace std;

class RealImage{
public:
	RealImage(int i){  ID = i; 		cout << "       $$ ctor:  " << ID << endl; }
	~RealImage(){						cout << "     dtor: " << ID << endl; }
	void draw() {						cout << "		drawing image" << ID << endl;}
private:
	int ID;
};

// 1. Design an "extra level of indirection" wrapper class
class Image{
public:
	Image(){ ID = next++; theRealThing = 0; } // 3. Initialized to null
	~Image(){ delete theRealThing; }
	void draw(){ 
		// 4. when a request comes in, the real object is created "on first use"
		if (!theRealThing) theRealThing = new RealImage(ID);
		// 5. the request is always delegated
		theRealThing->draw();
	}
private:
	// 2. The wrapper class holds a pointer to the real class
	RealImage* theRealThing;
	int	ID;
	static int next;
};
int Image::next = 1;

void main(void){
	Image images[5];
	int i;
	cout << "Exit[0], Image[1-5]: "; cin >> i;
	while(i){
		images[i-1].draw();
		cout << "Exit[0], Image[1-5]: "; cin >> i;
	}
}