#ifndef _NIC_H_
#define _NIC_H_
#include "windows.h"

BOOL NicInit(void);
void Terminate(void);
BOOL NicOpen(char* hostname, int port, int type);
void NicClose(void);

BOOL NicListen(int port,int type);
BOOL Accept(SOCKET &socket);
void SetSocket(SOCKET socket);
void BkSocket(void);
void RsSocket(void);
BOOL WaitInputData(int seconds);
BOOL Read(void* data, int len, int *ret_len);
BOOL Write(void* data, int len);
BOOL GetHostIP(char* hostname, unsigned char &ip1, unsigned char &ip2, unsigned char &ip3, unsigned char &ip4);
BOOL SetNoDelay(void);
#endif
