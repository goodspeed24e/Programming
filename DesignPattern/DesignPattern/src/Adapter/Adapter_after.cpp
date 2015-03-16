
#include <iostream>
#include <stdio.h>
#include <time.h>
using namespace std;

class ManlyTime{
public:
	char *getTime(){
		static char buf[32];
		time_t lt;
		tm*		ltStruct;
		time( &lt);
		ltStruct = localtime(&lt);
		strftime(buf,32,"%H%M",ltStruct);
		return buf;
	}
};

class WimpyTime: private ManlyTime{
public:
	char* getTime(){
			static char buf[32];
			char *ptr, mi[3], am[3];
			int hr;
			ptr = ManlyTime::getTime();
			cout << "old interface time is" << ptr << endl;
			strcpy(mi, &(ptr[2]));
			ptr[2] = '\0';
			sscanf(ptr, "%d", &hr);
			strcpy(am,"AM");
			if (hr > 12){
				hr -= 12;
				strcpy(am, "PM");
			}
			sprintf(buf, "%d:%s %s", hr, mi, am);
			return buf;
		}
};

void main(void)
{
	WimpyTime newT;
	char* ptr;
	ptr = newT.getTime();
	cout << "new interface time is" << ptr << endl;
}