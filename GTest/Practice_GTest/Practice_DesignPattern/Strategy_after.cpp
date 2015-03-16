/* 
-- Refine: StereoVidexMixer 
-- Pattern: Strategy
-- Input: video or graphic stream
-- Output: a blended rendertarget
-- Member: 
   P1. video processor
   P2. Output
*/

#include <iostream>
#include <time.h>
using std::cout;

enum{
	_Intel,
	_Nvidia,
	_PCOM,
	_DXVAHD,
	_DXVA2
};

class VPImpl {
public:
	virtual void doVP( int[], int ) = 0;
};
class DXVAHD : public VPImpl {
public:
	void doVP( int v[], int n ) {
	
	}
};
class DXVA2 : public VPImpl {
public:
	void doVP( int v[], int n ) {
		
	}
};
class PCOM : public VPImpl {
public:
	void doVP( int v[], int n ) {
		
	}
};

class Stat {
public:
	Stat() { m_impl = new DXVAHD; }

	void setVP(int iv) {
		delete m_impl;
		switch (iv)
		{
		case _Intel: 
			m_impl = new DXVA2; break;
		case _Nvidia: 
			m_impl = new DXVA2; break;
		case _PCOM: 
			m_impl = new PCOM; break;
		case _DXVAHD: 
			m_impl = new DXVAHD; break;
		case _DXVA2: 
			m_impl = new DXVA2; break;
		default: 
			m_impl = new DXVA2; break;
		}
	}

	void iStream( ) {
		
	}
	void Output( ) {
		
	}
	int getMin()    { return m_min; }
	int getMax()    { return m_max; }
	int getMedian() { return m_median; }
private:
	int m_min, m_max, m_median;
	VPImpl*  m_impl;
};

int main( void ) {

	int iVendor = 0;
	Stat  obj;
	obj.setVP(iVendor);
	obj.iStream();
	
	obj.setVP(iVendor);
	obj.iStream();
}