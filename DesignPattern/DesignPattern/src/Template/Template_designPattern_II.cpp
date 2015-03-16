#include <iostream>
using namespace std;

class Template_IncompleteAlgorithm {
public:
   void doIt() {       // this is the Template Method
      stepOne();       // invariant, standard
      stepTwo();       // invariant, standard
      stepThree();     // variable,  supplied by subclass
      stepFour(); }    // variable,  default provided
private:
   void stepOne() {
      cout << "IncompleteAlgorithm::stepOne" << endl; }
   void stepTwo() {
      cout << "IncompleteAlgorithm::stepTwo" << endl; }
   virtual void stepThree() = 0;
protected:
   virtual void stepFour() {
      cout << "IncompleteAlgorithm::stepFour" << endl; }
};

class Template_FillInTheTemplate : public Template_IncompleteAlgorithm {
   /* virtual */ void stepThree() {
      cout << "FillInTheTemplate::stepThree" << endl; }
   /* virtual */ void stepFour() {
      Template_IncompleteAlgorithm::stepFour();
      cout << "FillInTheTemplate::stepFour" << endl; }
};

/**
 * \brief Template Method design pattern demo
 * The "template method" establishes the steps to be
 * performed.  All standard, or invariant, steps have their implementation
 * provided by the abstract base class.  All variable steps are not
 * defined in the base class, but must be defined by concrete derived
 * classes.  "stepFour" below is an embellishment on the design pattern
 * where the base class provides a default implementation, and then the
 * derived class may extend that method by: overriding the method,
 * "calling-back" to the base class to leverage its implementation, and
 * then adding its own peculiar behavior.
 */
void main() {
   Template_FillInTheTemplate  theThingToDo;
   theThingToDo.doIt();
}

// IncompleteAlgorithm::stepOne
// IncompleteAlgorithm::stepTwo
// FillInTheTemplate::stepThree
// IncompleteAlgorithm::stepFour
// FillInTheTemplate::stepFour
