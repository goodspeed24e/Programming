
#include <iostream>
#include <list>
using namespace std;

class CUIMgr {
};

struct sPlayerProp
{
	int cameraID;
};

class CVDec{
public:
	CVDec(bool bDXVA2): m_bDXVA2(bDXVA2){}
	bool SetMode(bool bHW) 
	{
		if (m_bDXVA2 == bHW)
			return false;
		
		ResetDec();
		return true;
	}

private:
	void ResetDec() { cout << "Flush... Reset Status... Restart Decoder";}
	bool m_bDXVA2;
};

class CPlayer {
public:
	CPlayer(): m_state(PLAY), m_VDec(new CVDec(true)) {}
	~CPlayer() { delete m_VDec; m_VDec = NULL; }
	bool CheckOnStatus() { return m_state == STOP ? true : false; }
	void QueryStatus(int &_state) {_state = m_state;}
	void OnPlay() {m_state = PLAY;}
	void OnPause() {m_state = PAUSE;}
	void OnStop() {m_state = STOP;}
	bool SetProperty(const sPlayerProp *prop) { m_Prop = *prop;}
	bool GetProperty(sPlayerProp &prop) { prop = m_Prop;}
	bool SetHWVDecAcc(bool bHW) { return m_VDec->SetMode(bHW);}

private:
  enum States {PLAY, PAUSE, STOP};
  int m_state;
  
  sPlayerProp m_Prop;
  CVDec *m_VDec;
};

const int MAXPLAYER = 64;
typedef std::list<CPlayer*>  PalyerQue;
typedef

class CLayoutMgr {
public:
	CLayoutMgr(int tt = 0): m_TourTimerPerSec(tt){}
	void UpdateTimer(int tt) { m_TourTimerPerSec = tt;}
	bool addPlayer(int nIndex, const sPlayerProp *prop)
	{	
		for (PalyerQue::iterator it = m_Players->begin(); it != m_Players->end(); it++)
		{
			if (1/**it.CheckOnStatus()*/)
			{
				//m_Players[nIndex].Setprop()
			}
		}
		return true;
	}
private:
	int m_TourTimerPerSec;
	PalyerQue m_Players[MAXPLAYER];

};