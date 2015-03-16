//
// Widget.h:
//
// Trivial "Widget" class wrapping an int value.
// Methods:
//		a c'tor (value defaults to 0),
//		== and != operators,
//		inserter/extractor.
//		draw(double ScaleFactor)
//

#include <iostream>

class Widget {
public:
	Widget(int i = 0) : val(i), valid(true) {}
	virtual void draw(double ScaleFactor = 1) const;
	int getVal() const { return val; }

	int redraw() const { std::cout << "Drawing Widget(" << val << ")\n"; return 0; }
	bool isCertified() /*const*/ { return val % 2 == 0;}	// whether the Widget is certified
	friend std::ostream &operator<<(std::ostream &, const Widget &);
	friend std::istream &operator>>(std::istream &, Widget &);
	friend bool operator!=(const Widget &, const Widget &);
	friend bool operator==(const Widget &, const Widget &);
	friend bool operator<(const Widget &, const Widget &);
	int test();				// perform a self-test; mark *this
protected:
	int val;
private:
	bool valid;
};

void Widget::draw(double ScaleFactor) const
{
	std::cout << "Drawing widget (val = " << val << ") using ScaleFactor " <<
			ScaleFactor << "..." << std::endl;
}

inline bool operator!=(const Widget &w1, const Widget &w2)
{
	return (w1.val != w2.val);
}

inline bool operator==(const Widget &w1, const Widget &w2)
{
	return (w1.val == w2.val);
}

inline bool operator<(const Widget &w1, const Widget &w2)
{
	return (w1.val < w2.val);
}


inline std::ostream &operator<<(std::ostream &o, const Widget &w)
{
	return o << w.val;
}

inline std::istream &operator>>(std::istream &o, Widget &w)
{
	return o >> w.val;
}

inline int Widget::test()				// perform a self-test; mark *this
{
	return valid = (val % 2 == 0);				// only "valid" if it is even
}

// End Widget.h

