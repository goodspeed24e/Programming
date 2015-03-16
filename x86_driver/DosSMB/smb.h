
#define PCI_DEVICE_ID_NVIDIA_NFORCE4_SMBUS  0x0052
#define NFORCE_PCI_SMB1		0x50
#define NFORCE_PCI_SMB2		0x54

#define NVIDIA_SMB_PRTCL	0x00       /* protocol, PEC */
#define NVIDIA_SMB_STS		0x01       /* status */
#define NVIDIA_SMB_ADDR		0x02       /* address */
#define NVIDIA_SMB_CMD		0x03       /* command */
#define NVIDIA_SMB_DATA		0x04       /* 32 data registers */
#define NVIDIA_SMB_BCNT		0x24       /* number of data bytes */
#define NVIDIA_SMB_ALRM_A	0x25       /* alarm address */
#define NVIDIA_SMB_ALRM_D	0x26       /* 2 bytes alarm data */
       
#define NVIDIA_SMB_STS_DONE	0x80
#define NVIDIA_SMB_STS_ALRM	0x40
#define NVIDIA_SMB_STS_RES	0x20
#define NVIDIA_SMB_STS_STATUS	0x1f

#define NVIDIA_SMB_PRTCL_WRITE	0x00
#define NVIDIA_SMB_PRTCL_READ	0x01
#define NVIDIA_SMB_PRTCL_QUICK	0x02
#define NVIDIA_SMB_PRTCL_BYTE	0x04
#define NVIDIA_SMB_PRTCL_BYTE_DATA	0x06
#define NVIDIA_SMB_PRTCL_WORD_DATA	0x08
#define NVIDIA_SMB_PRTCL_BLOCK_DATA	0x0a
#define NVIDIA_SMB_PRTCL_PROC_CALL	0x0c
#define NVIDIA_SMB_PRTCL_BLOCK_PROC_CALL	0x0d
#define NVIDIA_SMB_PRTCL_I2C_BLOCK_DATA		0x4a
#define NVIDIA_SMB_PRTCL_PEC	0x80

#define MAX_TIMEOUT 1000

#define SMBHSTSTS	0x0    // smbus host status register    
#define SMBHSTCNT	0x2    // smbus host control register   
#define SMBHSTCMD	0x3    // smbus host command register   
#define SMBHSTADD	0x4    // smbus host address register   
#define SMBHSTDAT0	0x5    // smbus host data 0 register    
#define SMBHSTDAT1	0x6    // smbus host data 1 register    
#define SMBBLKDAT	0x7    // smbus block data register 

#define START_RW	0x40   // Start R/W Command
#define SMB_HOST_BUSY		1      // smb host is busy              
#define SMB_INTERRUPT		2      // smb interrupt flag            
#define SMB_DEVICE_ERROR	4      // device error                  
#define SMB_BUS_COLLISION	8      // transation collision          
#define SMB_FAIL		16     // transation fail
#define BYTE_DATA_READ_OR_WRITE	(2*4)	// Byte data read or write


BOOL Search_Device( BYTE Classtype,BYTE Subclass1,BYTE Subclass2,WORD *vd,BYTE *Bus, BYTE *Dev, BYTE *Func );
void read_spd(void);
BYTE read_nv_slave_data(BYTE slave_address, BYTE offset);
BYTE read_it_slave_data(BYTE slave_address, BYTE offset);
void Delay_1us( WORD usecs );
void quit( int errorlevel );

void GUI(void);
void Block( BYTE sx,BYTE sy,BYTE ex,BYTE ey,BYTE color );
void Col_NO(void);
void detect_device(void);
void Get_Content(void);
void tool_bar(int sld);
void show_device(void);
void draw_select(void);
