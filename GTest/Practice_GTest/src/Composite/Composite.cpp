// purpose: composite desing pattern
// 1. Identify the scalar/primitive classes and vector/container classes
// 2. Create an "interface" (lowest common denominator) that can make all concerete class "interchangeable"
// 3. All concrete classes declare an "is a" relationship to the interface
// 4. All "container" classes couple themselves to the interface ( recursive composition, Composite "has a" set of children up the "is a" hierarchy)
// 5. "container" classes use polymorphism as they deledate to their children

#include <iostream>
#include <vector>
using namespace std;

// 2. Create an "interface" (lowest common denominator)
class Component{
public: 
	virtual void traverse() = 0;
};

class Leaf:public Component{		// 1. Scalar class 3. "isa" releationship
	int value;
public:
	Leaf(int val)	{ value = val;}
	void traverse()	{ cout << value << ' ';}
};

class Composite:public Component{	// 1. vector calss 3. "isa" relationship
	vector<Component*> children;	// 4. "Container" coupled to the interface
public:
	// 4. "container" class coupled to the interface
	void add(Component *ele){
		children.push_back(ele);
	}
	void traverse(){
		for (int i = 0; i < children.size(); i++)
			// 5. use polymorphism to deledate to children
			children[i]->traverse();
	}
};

void main(void)
{
	Composite containers[4];

	int i = 0;
	for (i=0; i < 4; i++)
		for (int j=0; j < 3; j++)
			containers[i].add( new Leaf( i * 3 + j ) );

	for (i=1; i < 4; i++)
		containers[0].add( &(containers[i]) );

	for (i=0; i < 4; i++) {
		containers[i].traverse();
		cout << endl;
	}
}