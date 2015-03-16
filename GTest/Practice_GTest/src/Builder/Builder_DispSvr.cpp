#include <iostream>
#include <string.h>
using namespace std;

enum {_NVIDIA, _AMD, _INTEL, _D3D};

class PlugIn{
public:
	virtual void _SetDevice() = 0;
	virtual void ShowGUID() = 0;
};

/** NvAPI */
class Nvidia: public PlugIn{
public: 
	void _SetDevice(){
		GUID = _NVIDIA;
		cout << "Nvidia==" << GUID << endl;
	}
	void ShowGUID(){
		cout << "GUID:" << GUID << " " << endl;
	}
private:
	int GUID;
};

/** PCOM */
class AMD: public PlugIn{
public: 
	void _SetDevice(){
		GUID = _AMD;
		cout << "AMD==" << GUID << endl;
	}
	void ShowGUID(){
		cout << "GUID:" << GUID << " " << endl;
	}
private:
	int GUID;
};

/** FastCOM */
class Intel: public PlugIn{
public: 
	void _SetDevice(){
		GUID = _INTEL;
		cout << "Intel==" << GUID << endl;
	}
	void ShowGUID(){
		cout << "GUID:" << GUID << " " << endl;
	}
private:
	int GUID;
};

/** D3D */
class MS: public PlugIn{
public: 
	void _SetDevice(){
		GUID = _D3D;
		cout << "MS==" << GUID << endl;
	}
	void ShowGUID(){
		cout << "GUID:" << GUID << " " << endl;
	}
private:
	int GUID;
};


/** RenderEngine */
class Builder{
public : 
	virtual void ConfigureResource(int i) = 0;	
};

class Build:public Builder{
public:
	void ConfigureResource(int i){
		cout << "Create resource" << endl;
		switch(i)
		{
		case _NVIDIA:
			plg = new Nvidia;
			break;
		case _AMD:
			plg = new AMD;
			break;
		case _INTEL:
			plg = new Intel;
			break;
		default:
			plg = new MS;
			break;
		}
		// Set Device
		plg->_SetDevice();
	}

	PlugIn* Get_Configure(){
		return plg;
	}
private:
	PlugIn *plg;
};

/** ResourceManager */
class Director{
public:
	Director (Builder *b){
		setBuilder(b);
	}
	void setBuilder(Builder* b){
		bldr = b;
	}
	/** ActivateMixerPresenter */
	void construct(int i){
		bldr->ConfigureResource(i);
	}
private:
	Builder* bldr;
};


void main(){
	Build bld;			// RenderEngine
	Director dir(&bld);	// ResourceManager

	dir.construct(2);
	bld.Get_Configure()->ShowGUID();
}