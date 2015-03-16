#ifndef _DOSIPMI_H_
#define _DOSIPMI_H_

#define MAX_CMD_LEN	256

//KCS interface
#define KCS_GET_STATUS	0x60
#define KCS_ABORT				0x60
#define KCS_WRITE_START	0x61
#define KCS_WRITE_END		0x62
#define KCS_READ				0x68

#define IDLE_STATE  0x00
#define READ_STATE	0x40
#define WRITE_STATE 0x80
#define ERROR_STATE 0xC0

#define BMC_TIMEOUT	4000 //等待BMC回應的時間

#define RETRY_OUT	5 //kcs time重試次數

BYTE IPMI_request[MAX_CMD_LEN],IPMI_response[MAX_CMD_LEN];
WORD KCS_DATA,KCS_STATUS,KCS_CTRL;
int IPMI_reqlen,IPMI_rsplen;


//in kcs.c
int Send2KCS(void);

#endif
