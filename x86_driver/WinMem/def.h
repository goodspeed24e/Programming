enum
{
	WM_MSG_STATUS=(WM_USER + 1)
};

typedef struct
{
	DWORD sh_start;
	DWORD sh_end;
	int sh_type;
	char sh_value[100];
}SEARCH_INFO;
