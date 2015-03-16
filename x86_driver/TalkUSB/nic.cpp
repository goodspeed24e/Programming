#include "nic.h"
#include "stdio.h"

BOOL init_flag = FALSE;
SOCKET m_Socket=INVALID_SOCKET,kb_Socket;

BOOL NicInit(void)
{
	WSAData wsa_data;
/*	char bb[100];
		sprintf(bb,"%08lx",SD_SEND);
		MessageBox(NULL,bb,"note",MB_OK);*/
	
	if(!init_flag)
	{
		try
		{
			if(WSAStartup(0x0101,&wsa_data) != 0)
			{
				MessageBox(NULL,"WSAStartup FAIL","Error",MB_OK | MB_ICONSTOP);
				return FALSE; // ��l�ƥ��� //
			}
			init_flag = TRUE;
		}
		catch(...)
		{
			MessageBox(NULL,"try WSAStartup FAIL","Error",MB_OK | MB_ICONSTOP);
			return FALSE;
		}
	}
	return TRUE;
}

void Terminate(void)
{
	if(init_flag)
	{
		try
		{
			WSACleanup();
			init_flag = FALSE;
		}
		catch(...)
		{
		}
	}
}

BOOL IsLocalHost(char* hostname)
//�����G�ˬd�O�_��localhost�I�s
//��J�Ghostname = Server��}
//�Ǧ^�G�O�_��localhost�I�s
{
	if(hostname == NULL)
		return TRUE;
	if(*hostname == 0)
		return TRUE;
	if(!stricmp(hostname,"localhost"))
		return TRUE;
	if(!strcmp(hostname,"127.0.0.1"))
		return TRUE;
	return FALSE;
}

BOOL IsOpened(void)
{
	if(m_Socket == INVALID_SOCKET)
		return FALSE;
	return TRUE;
}

BOOL NicOpen(char* hostname, int port, int type)
//�����G�}�һPServer���s�u
//��J�Ghostname,port = Server��}�P�q�T��
//�Ǧ^�G���ѶǦ^false
{
	struct sockaddr_in sock_addr;
	struct hostent *hostinfo;
	
	NicClose();
	if(!NicInit())
	{
		return FALSE;
	}
	
	// �ѥXsocket address //
	if(IsLocalHost(hostname))
	{
		hostname = "127.0.0.1";
	}
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(port);
	
	hostinfo = gethostbyname(hostname);
	if(hostinfo == NULL)
	{
		MessageBox(NULL,"GetHostByName() Fail","Error",MB_OK | MB_ICONSTOP);
		return FALSE;
	}
	sock_addr.sin_addr = *(struct in_addr *) hostinfo->h_addr;
	// �إ�socket //
	try
	{
		//SOCK_STREAM(TCP) or SOCK_DGRAM(UDP)
		m_Socket = socket(AF_INET,type,0);
		if(m_Socket == INVALID_SOCKET)
		{
			MessageBox(NULL,"Socket() Fail","Error",MB_OK | MB_ICONSTOP);
			return FALSE;
		}
	}
	catch(...)
	{
		MessageBox(NULL,"try Socket() FAIL","Error",MB_OK | MB_ICONSTOP);
		m_Socket = INVALID_SOCKET;
		return FALSE;
	}
	
	// �}�l�s�u //
	try
	{
		if(connect(m_Socket,(struct sockaddr*)&sock_addr,sizeof(sock_addr)) != 0)
		{
			char mm[10];
			
			sprintf(mm,"%ld",WSAGetLastError());
			MessageBox(NULL,mm,"Error",MB_OK | MB_ICONSTOP);
			//MessageBox(NULL,"Connect() Fail","Error",MB_OK | MB_ICONSTOP);
		}
		else
		{
			return TRUE;
		}
	}
	catch(...)
	{
		MessageBox(NULL,"try Connect() Fail","Error",MB_OK | MB_ICONSTOP);
	}

	// ���B�i�H�[�J�@�ǿ��~�B�z... //
  NicClose();
	return FALSE;
}

void NicClose(void)
{
	if(!IsOpened())
	return;
	
	try
	{
		shutdown(m_Socket,1);
	}
	catch(...)
	{
	}

	try
	{
		closesocket(m_Socket);
	}
	catch(...)
	{
	}
	m_Socket = INVALID_SOCKET;
}

BOOL NicListen(int port,int type)
{
	struct sockaddr_in sock_addr;
	int on = 1,rc;
	
	NicClose();
	if(!NicInit())
		return FALSE;
	
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_addr.s_addr = INADDR_ANY;
	sock_addr.sin_port = htons(port);
	// �إ�socket //
	try
	{
		m_Socket = socket(AF_INET,type,0);
		if(m_Socket == INVALID_SOCKET)
			return FALSE;
	}
	catch(...)
	{
		m_Socket = INVALID_SOCKET;
		return FALSE;
	}
	
	// Bind socket //
	setsockopt(m_Socket,SOL_SOCKET,SO_REUSEADDR,(char*)&on,sizeof(on));

	try
	{
		rc = bind(m_Socket,(struct sockaddr*)&sock_addr,sizeof(sock_addr));
	}
	catch(...)
	{
		rc = SOCKET_ERROR;
	}
	if (rc == SOCKET_ERROR) 
	{
		NicClose();
		return FALSE;
	}
	
	// Listen socket //
	try
	{
		rc = listen(m_Socket,SOMAXCONN);
	}
	catch(...)
	{
		rc = SOCKET_ERROR;
	}
	if (rc == SOCKET_ERROR) 
	{
		NicClose();
		return FALSE;
	}
	return TRUE;
}

BOOL Accept(SOCKET &socket)
{
	struct sockaddr_in from;
	int fromlen;
	
	socket = INVALID_SOCKET;
	
	if (!IsOpened())
		return FALSE;
	
	fromlen = sizeof(from);
	try
	{
		socket = accept(m_Socket,(struct sockaddr*)&from,&fromlen);
	}
	catch(...)
	{
		socket = INVALID_SOCKET;
		return FALSE;
	}
	return TRUE;
}

void SetSocket(SOCKET socket)
//�����G�]�w�s�u��socket
//��J�Gsocket = �s�u��socket
{
	///NicClose();
	m_Socket = socket;
}

void BkSocket(void)
{
	kb_Socket = m_Socket;
}

void RsSocket(void)
{
	m_Socket = kb_Socket;
}

BOOL WaitInputData(int seconds) //��J�Gseconds = ���ݬ��
{
	struct timeval timeout;
	
	if(!IsOpened())
		return FALSE;
	// �]�wdescriptor sets //
	fd_set socket_set;
	FD_ZERO(&socket_set);
	FD_SET((unsigned int)m_Socket,&socket_set);
	
	// �]�wtimeout�ɶ� //
	timeout.tv_sec = seconds;
	timeout.tv_usec = 0;
	// �����O�_����� //
	try
	{
		if(select(FD_SETSIZE,&socket_set,NULL,NULL,&timeout) <= 0)
			return FALSE;
	}
	catch(...)
	{
		return FALSE;
	}
	return TRUE;
}

//��J�Gdata, len = ��ƽw�İϻP�j�p
//��X�Gdata = Ū�������, ret_len = ���Ū������Ƥj�p�A0����w�_�u
BOOL Read(void* data, int len, int *ret_len)
{
	*ret_len = 0;
	if (!IsOpened())
		return TRUE;

	try
	{
		*ret_len = recv(m_Socket,(char*)data,len,0);
	}
	catch(...)
	{
		*ret_len = SOCKET_ERROR;
	}
	if (*ret_len < 0)
	{
		*ret_len = 0;
		return FALSE;
	}
	return TRUE;
}

BOOL Write(void* data, int len)
{
	int write_len;
	
	if(!IsOpened())
		return FALSE;
	if(len <= 0)
		return FALSE;
	
	try
	{
		write_len = send(m_Socket,(char*)data,len,0);
	}
	catch(...)
	{
		write_len = SOCKET_ERROR;
	}
	if(write_len != len)
		return FALSE;
	return TRUE;
}

BOOL GetHostIP(char* hostname, unsigned char &ip1, unsigned char &ip2, unsigned char &ip3, unsigned char &ip4)
{
	struct hostent *hostinfo;
	char* addr;
	
	if(IsLocalHost(hostname))
	{
		// �����X��ڪ�hostname //
		hostinfo = gethostbyname("localhost");
		if(hostinfo == NULL)
			return FALSE;
		hostname = hostinfo->h_name;
	}
	
	hostinfo = gethostbyname(hostname);
	if(hostinfo == NULL)
		return FALSE;
	addr = hostinfo->h_addr_list[0];
	ip1 = (unsigned char) addr[0];
	ip2 = (unsigned char) addr[1];
	ip3 = (unsigned char) addr[2];
	ip4 = (unsigned char) addr[3];
	return TRUE;
}

//�����G�]�w������ǰe (����Nagle Algorithm)
BOOL SetNoDelay(void)
{
	int on = 1;
	
	if (!IsOpened())
		return FALSE;
	
	if(setsockopt(m_Socket,IPPROTO_TCP,TCP_NODELAY,(char*)&on,sizeof(on)) != 0)
		return FALSE;
	return TRUE;
}
