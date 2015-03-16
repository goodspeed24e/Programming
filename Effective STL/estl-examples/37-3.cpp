//
// Yet more from ESTL Item 37
//

#include <iostream>
#include <numeric>
#include <string>
#include <set>
#include <vector>
#include <list>
#include "ESTLUtil.h"
using namespace std;

string::size_type									// see below for info
stringLengthSum(string::size_type sumSoFar,			// on string::size_type 
					const string& s)
{
	return sumSoFar + s.size();
}

struct Point {
	Point(double initX, double initY): x(initX), y(initY) {}
	double x, y;
};


class PointAverage:
	public binary_function<Point, Point, Point> {						// see Item 40
public:
	PointAverage(): xSum(0), ySum(0), numPoints(0) {}

	const Point operator()(const Point& avgSoFar, const Point& p)
	{
		++numPoints;
		xSum += p.x;
		ySum += p.y;

		return Point(xSum/numPoints, ySum/numPoints);
	}

private:
	size_t numPoints;
	double xSum;
	double ySum;
};

int main()
{
	using namespace std;
	using namespace ESTLUtils;

	string s1("this is a");
	string s2("test of the");
	string s3("emergency broadcast system");

	set<string> ss;						// create container of strings,
										// and populate it

	ss.insert(s1);
	ss.insert(s2);
	ss.insert(s3);
	
	string::size_type lengthSum =				// set lengthSum to the result
		accumulate(ss.begin(), ss.end(),		// of calling stringLengthSum on
		  static_cast<string::size_type>(0), stringLengthSum);	// each element in ss, using 0
												// as the initial summary value

	cout << "Total of sizes = " << lengthSum << endl;


	/////////////////////////////////////////////////////////////////////

	vector<float> vf;					// create container of floats
										// and populate it

	vf.push_back(.5);
	vf.push_back(1);
	vf.push_back(.5);
	
	float product =							// set product to the result of
		accumulate(vf.begin(), vf.end(),	// calling times<float> on each
		float(1.0f), multiplies<float>());	// element in vf, using 1.0f as the
											// initial summary value

	cout << "product of .5 , 1 and .5 = " << product << endl;

	////////////////////////////////////////////////////////////////////


	list<Point> lp;
	lp.push_back(Point(1.1,2.2));
	lp.push_back(Point(2.2,4.4));
	lp.push_back(Point(4.4,8.8));


	Point avg =							// average the points in lp
		accumulate(	lp.begin(), lp.end(),
			Point(0, 0), PointAverage());


	cout << "Point avg = (" << avg.x << "," << avg.y << ")" << endl;
	return 0;
}
