
/*
//  Strategy Pattern = polymorphism
// The notion of "sort" has been promoted to full object status
// The Stat client is abstractly coupled to a Sort object of
// unknown implementatiion, and the end-user of Stat can affect
// the choice of implementation
*/

#include <iostream>
using std::cout;

class SortImpl {
public:
    virtual void sort(int [], int);
};

class SortBubble: public SortImpl{
public:
	void sort(int v[], int n)
	{
		for (int i= n - 1; i > 0; --i)
		{
			for (int j = 0 ; j < i; j++)
			{
				if (v[j] > v[j+1])
				{
					int t = v[j];
					v[j] = v[j+1];
					v[j+1] = t;
				}	
			}
		}
		cout << "Bubble: ";
		for ( int k = 0 ; k < n; ++k)
		{
				cout << v[k] << ' ';
		}
		cout << "\n";
	}
};

class SortShell: public SortImpl{
public:
	void sort(int v[], int n)
	{
		for ( int g = n/2; g > 0; g /=2)
		{
			for ( int i = g; i < n; ++i)
			{
				for (int j =  i - g ; j >= 0; j -= g)
				{
					if (v[j] > v[j+g])
					{
						int tmp = v[j];
						v[j] = v[j+g];
						v[j+g] = tmp;
					}
				}
			}
		}
		cout << "Shell : ";
		for ( int k = 0 ; k < n ;++k)
		{
			cout << v[k] << "  ";
		}
		cout << "\n";
	}
};

class Stat{
public:
	Stat()
	{
		m_impl = new SortBubble;
	}
	~Stat()
	{
		delete m_impl;
		m_impl = NULL;
	}
	void upGrade()
	{
		delete m_impl;
		m_impl = new SortShell;
	}
	void downGrade()
	{
		delete m_impl;
		m_impl = new SortBubble;
	}
	void readVector( int v[], int n)
	{
		m_impl->sort(v,n);
		m_min = v[0];
		m_max = v[n-1];
		m_median = v[n/2];
	}
    int getMin()				{ return m_min;}
	int getMedian()		{ return m_median;}
	int getMax()				{ return m_max;}
private:
	int m_min, m_max, m_median;
	SortImpl *m_impl;
}; // end of Stat class

int main(void){
	const int NUM = 9;
   int       array1[NUM], array2[NUM];
//   srand( time(0) );
   cout << "Vector: ";

   for (int i=0; i < NUM; ++i) {
      array1[i] = array2[i] = rand() % 9 + 1;
      cout << array1[i] << ' '; }
   cout << '\n';

   Stat  obj;
   obj.upGrade();
   obj.readVector( array1, NUM );
   cout << "min is " << obj.getMin() << ", max is " << obj.getMax()
        << ", median is " << obj.getMedian() << '\n';
   obj.downGrade();
   obj.readVector( array2, NUM );
   cout << "min is " << obj.getMin() << ", max is " << obj.getMax()
        << ", median is " << obj.getMedian() << '\n';
}

// Vector: 7 4 2 6 5 7 7 5 1
// Shell:  1 2 4 5 5 6 7 7 7
// min is 1, max is 7, median is 5
// Bubble: 1 2 4 5 5 6 7 7 7
// min is 1, max is 7, median is 5