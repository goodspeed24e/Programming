//
// Example from ESTL Item 40
//

#include <list>
#include <iostream>
#include "Widget.h"
#include "ESTLUtil.h"

bool isInteresting(const Widget *pw)
{
	return pw->getVal() % 2 == 0;	// interesting == even
}

template<typename T>
class MeetsThreshold: public std::unary_function<Widget, bool> {
private:
        const T threshold;
public:
        MeetsThreshold(const T& threshold) : threshold(threshold) {}
        bool operator()(const Widget &w) const { return w.getVal() >= threshold; }
        // ...
};

struct WidgetNameCompare:
        std::binary_function<Widget, Widget, bool> {
        bool operator()(const Widget& lhs, const Widget& rhs) const {
			return lhs.getVal() <= rhs.getVal();
		}
};

struct PtrWidgetNameCompare:
        std::binary_function<const Widget*, const Widget*, bool> {
        bool operator()(const Widget* lhs, const Widget* rhs) const;
};



int main()
{
	using namespace std;
	using namespace ESTLUtils;

	list<Widget*> widgetPtrs;

	widgetPtrs.push_back(new Widget(1));
	widgetPtrs.push_back(new Widget(2));
	widgetPtrs.push_back(new Widget(3));
	widgetPtrs.push_back(new Widget(4));
	widgetPtrs.push_back(new Widget(5));

	list<Widget*>::iterator i =
			find_if( widgetPtrs.begin(), widgetPtrs.end(),
                        isInteresting);
	if (i != widgetPtrs.end()) {
		cout << "First interesting Widget = " << **i << endl;    // process the first
	}                                                           // interesting
	else											            // pointer-to-widget
		cout << "No interesting Widgets." << endl;
                                                   

/*
	{
		list<Widget*>::iterator i =
        find_if(widgetPtrs.begin(), widgetPtrs.end(),
                not1(isInteresting));                         // error! won’t compile
	}
*/
	
	{
		list<Widget*>::iterator i =
			find_if(widgetPtrs.begin(), widgetPtrs.end(),
					not1(ptr_fun(isInteresting)));			  // fine
		if (i != widgetPtrs.end()) {
			cout << "First dull Widget = " << **i << endl;    // process the first
		}                                                     //  dull ptr-to-Widget
		else
			cout << "No dull Widgets." << endl;
	}


	list<Widget> widgets;

	widgets.push_back(Widget(13));
	widgets.push_back(Widget(25));
	widgets.push_back(Widget(3));
	widgets.push_back(Widget(30));
	widgets.push_back(Widget(40));
	widgets.push_back(Widget(50));

	printContainer("\nwidgets", widgets);

	list<Widget>::reverse_iterator i1 =                      // find the last widget 
			find_if(widgets.rbegin(), widgets.rend(),        // that fails to meet the 
					not1(MeetsThreshold<int>(10)));          // threshold of 10

	if (i1.base() != widgets.end())
		cout << "Last widget failing to meet threshold is " << *i1 << endl; 
	else
		cout << "All Widgets meet threshold!" << endl;

	Widget w(10);

	list<Widget>::iterator i2 =                             // find the first widget
			find_if(widgets.begin(), widgets.end(),         // that precedes w in the
					bind2nd(WidgetNameCompare(), w));       // sort order defined by
															// WidgetNameCompare
	if (i2 != widgets.end())
		cout << "First Widget that precedes w (" << w.getVal() << ") is "
						<< *i2 << endl; 
	else
		cout << "No Widgets precede w (" << w.getVal() << ")!" << endl;


	return 0;
}
