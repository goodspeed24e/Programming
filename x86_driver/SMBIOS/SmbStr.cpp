char TableName[][33]=
	{
	 {"Entry Point Structure"}, //-1
	 {"BIOS Information"}, //0
	 {"System Information"},
	 {"Base Board Information"},
	 {"System Enclosure or Chassis"},
	 {"Processor Information"},
	 {"Memory Controller Information"},
	 {"Memory Module Information"},
	 {"Cache Information"},
	 {"Port Connector Information"},
	 {"System Slots"},
	 {"On Board Devices Information"}, //10
	 {"OEM String"},
	 {"System Configuration Options"},
	 {"BIOS Language Information"},
	 {"Group Associations"},
	 {"System Event Log"},
	 {"Physical Memory Array"},
	 {"Memory Device"},
	 {"32-bit Memory Error Information"},
	 {"Memory Array Mapped Address"},
	 {"Memory Device Mapped Address"}, //20
	 {"Build-in Pointing Device"},
	 {"Portable Battery"},
	 {"System Reset"},
	 {"Hardware Security"},
	 {"System Power Controls"},
	 {"Voltage Probe"},
	 {"Cooling Device"},
	 {"Temperature Probe"},
	 {"Electrical Current Probe"},
	 {"Out-of-Band Remote Access"}, //30
	 {""},
	 {"System Boot Information"},
	 {"Memory Error Information"},
	 {"Management Device"},
	 {"MAnagement Device Component"},
	 {"Management Device Threshold Data"},
	 {"Memory Channel"},
	 {"IPMI Device Information"},
	 {"System Power Supply"}
	};

char tp0_str1[][90]=
	{
		"Reserved",
		"Resvered",
		"Unknown",
		"BIOS Characteristics Not Supported",
		"ISA is supported",
		"MCA is supported",
		"EISA is supported",
		"PCI is supported",
		"PCI Card(PCMCIA) is supported",
		"Plug and Play is supported",
		"APM is supported",
		"BIOS is Upgradeable(Flash)",
		"BIOS shadowing is allowed",
		"VL-VESA is supported",
		"ESCD support is available",
		"Boot from CD is supported",
		"Selectable Boot is supported",
		"BIOS ROM is socketed",
		"Boot From PC Card(PCMCIA) is supported",
		"EDD(Ehanced Disk Drive) Specification is supported",
		"Int 13h - Japanese Floppy for NEC 9800 1.2mb(3.5\", 1k Byte/Sector, 360 RPM) is supported",
		"Int 13h - Japanese Floppy for Toshiba 1.2mb(3.5\", 360 RPM) is supported",
		"Int 13h - 5.25\"/360KB Floppy Services are supported",
		"Int 13h - 5.25\"/1.2MB Floppy Services are supported",
		"Int 13h - 5.25\"/720KB Floppy Services are supported",
		"Int 13h - 5.25\"/2.88MB Floppy Services are supported",
		"Int 5h, Print Screen Service is supported",
		"Int 9h, 8042 Keyboard services are supported",
		"Int 14h, Serial Services are supported",
		"Int 17h, Printer Services are supported",
		"Int 10h, CGA/Mono Video Services are supported",
		"NEC PC-98"
	};
char tp0_str2[][34]=
	{
		"ACPI supported",
		"USB Legacy is supported",
		"AGP is supported",
		"I2O boot is supported",
		"LS-120 boot is supported",
		"ATAPI ZIP Drive boot is supported",
		"1394 boot is supported",
		"Smart Battery supported",
	};
char tp0_str3[][52]=
	{
		"BIOS Boot Specification supported",
		"Function key-initiated Network Service boot support",
		"Enable Targetd Content Distribution",
	};
char tp1_str1[][18]=
	{
		"Reserved",
		"Other",
		"Unknown",
		"APM Timer",
		"Modem Ring",
		"LAN Remote",
		"Power Switch",
		"PCI PME#",
		"AC Power Restored"
	};
char tp2_str1[][55]=
	{
		"Board is a host board",
		"Board requires at least on daughter board or auxiliary",
		"Board is removable",
		"Board is replaceable",
		"Board is hot swappable"
	};
char tp2_str2[][49]=
	{
		"null",
		"Unknown",
		"Other",
		"Server Blade",
		"Connectivity Switch",
		"System Management Module",
		"Processor Module",
		"I/O Module",
		"Memory Module",
		"Daughter board",
		"Motherboard(includes processor, memory, and I/O)",
		"Processor/Memory Module",
		"Processor/IO Module",
		"Interconnect Board"
	};
char tp3_str1[][22]=
	{
		"null",
		"Other",
		"Unknown",
		"Desktop",
		"Low Profile Desktop",
		"Pizza Box",
		"Mini Tower",
		"Tower",
		"Portable",
		"LapTap",
		"Notebook",
		"Hand Held",
		"Docking Station",
		"All in One",
		"Sub Notebook",
		"Space-saving",
		"Lunch Box",
		"Main Server Chassis",
		"Expansion Chassis",
		"SubChassis",
		"Bus Expansion Chassis",
		"Peripheral Chassis",
		"RAID Chassis",
		"Rack Mount Chassis",
		"Sealed-case PC",
		"Mini-system chassis",
		"CompactPCI",
		"AdvancedTCA",
		"Blade",
		"Blade Enclosure"
	};
char tp3_str2[][16]=
	{
		"null",
		"Other",
		"Unknown",
		"Safe",
		"Warning",
		"Critical",
		"Non-recoverable"
	};
char tp3_str3[][30]=
	{
		"null",
		"Other",
		"Unknown",
		"None",
		"External interface locked out",
		"External interface enabled"
	};
char tp4_str1[][18]=
	{
		"null",
		"Other",
		"Unknown",
		"Central Processor",
		"Math Processor",
		"DSP Processor",
		"Video Processor"
	};
char tp4_str2[][76]=
	{
		"Other", //1
		"Unknown",
		"8086",
		"80286",
		"Intel386 Processor",
		"Intel486 Processor",
		"8087",
		"80287",
		"80387",
		"80487",
		"Pentium processor Family",
		"Pentium Pro processor",
		"Pentium II processor",
		"Pentium processor with MMX technology",
		"Celeron processor",
		"Pentium II Xeon processor",
		"Pentium III processor",
		"M1 Family",
		"M2 Family",
		"AMD Duron Processor Family", //18h
		"K5 Family",
		"K6 Family",
		"K6-2",
		"K6-3",
		"AMD Athlon Processor Family",
		"AMD2900 Family",
		"K6-2+",
		"Power PC Family",
		"Power PC 601",
		"Power PC 603",
		"Power PC 603+",
		"Power PC 604",
		"Power PC 620",
		"Power PC x704",
		"Power PC 750",
		"Alpha Family 3", //30h
		"Alpha 21064",
		"Alpha 21066",
		"Alpha 21164",
		"Alpha 21164PC",
		"Alpha 21164a",
		"Alpha 21264",
		"Alpha 21364",
		"MIPS Family", //40h
		"MIPS R4000",
		"MIPS R4200",
		"MIPS R4400",
		"MIPS R4600",
		"MIPS R10000",
		"SPARC Family", //50h
		"SuperSPARC",
		"SuperSPARC II",
		"SuperSPARC IIep",
		"UltraSPARC",
		"UltraSPARC II",
		"UltraSPARC IIi",
		"UltraSPARC III",
		"UltraSPARC IIIi",
		"68040 Family", //60h
		"68xxx",
		"68000",
		"68010",
		"68020",
		"68030",
		"Hobbit Family", //70h
		"Crusoe TM5000 Family", //78h
		"Crusoe TM3000 Family",
		"Crusoe TM8000 Family",
		"Weitek", //80h
		"Itanium processor", //82h
		"AMD Athlon 64 Processor Family",
		"AMD Opteron 64 Processor Family",
		"AMD Sempron 64 Processor Family",
		"AMD Turion 64 Mobile Technoogy",
		"Dual-Core AMD Opteron Processor Family",
		"AMD Athlon 64x2 Dual-Core Processor Family",
		"AMD Turion 64x2 Mobile Technology"
		"PA-RISC Family", //90h
		"PA-RISC 8500",
		"PA-RISC 8000",
		"PA-RISC 7300LC",
		"PA-RISC 7200",
		"PA-RISC 7100LC",
		"PA-RISC 7100",
		"V30 Family", //A0h
		"Pentium III Xeon processor", //B0h
		"Pentium III Processor with Intel SpeedStep Technology",
		"Pentium 4 Processor",
		"Intel Xeon",
		"AS400 Family",
		"Intel Xeon processor MP",
		"AMD Athlon XP Processor Family",
		"AMD Athlon MP Processor Family",
		"Intel Itanium 2 processor",
		"Intel Pentium M processor",
		"Intel Celeron D processor",
		"Intel Pentium D processor",
		"Intel Pentium Processor Extreme Edition",
		"Intel Core Solo Processor",
		"Reserved",
		"Intel Core 2 Duo Processor",
		"IBM390 Family", //C8
		"G4",
		"G5",
		"ESA/390 G6",
		"z/Architecture base",
		"VIA C7-M Processor Family",
		"VIA C7-D Processor Family",
		"VIA C7 Processor Family",
		"VIA Eden Processor Family"
		"i860", //FA
		"i960",
		"Indicator to obtain the processor family from the Processor Family 2 field",
		"Reserved",
		"SH-3",
		"SH-4",
		"ARM",
		"StrongARM",
		"6x86",
		"MediaGX",
		"MII",
		"WinChip",
		"DSP",
		"Video Processor",
		"Reserved"
	};
char tp4_str3[][9]=
	{
		"5V",
		"3.3V",
		"2.9V",
		"Resvered"
	};
char tp4_str4[][23]=
	{
		"null",
		"Other",
		"Unknown",
		"Daughter Board",
		"ZIF Socket",
		"Replaceable Piggy Back",
		"None",
		"LIF Socket",
		"Slot 1",
		"Slot 2",
		"370-pin socket",
		"Slot A",
		"Slot M",
		"Socket 423",
		"Socket A(Socket 462)",
		"Socket 478",
		"Socket 754",
		"Socket 940",
		"Socket 939",
		"Socket mPGA604",
		"Socket LGA771",
		"Socket LGA775"
	};
char tp4_str5[][15]=
	{
		"Reserved",
		"Unknown",
		"64-bit capable"
	};
char tp5_str1[][13]=
	{
		"null",
		"Other",
		"Unknown",
		"None",
		"8-bit Parity",
		"32-bit ECC",
		"64-bit ECC",
		"128-bit ECC",
		"CRC"
	};
char tp5_str2[][28]=
	{
		"Other",
		"Unknown",
		"None",
		"Single Bit Error Correcting",
		"Double Bit Error Correcting",
		"Error Scrubbing"
	};
char tp5_str3[][23]=
	{
		"null",
		"Other",
		"Unknown",
		"One Way Interleave",
		"Two Way Interleave",
		"Four Way Interleave",
		"Eight Way Interleave",
		"Sixteen Way Interleave"
	};
char tp5_str4[][8]=
	{
		"Other",
		"Unknown",
		"70ns",
		"60ns",
		"50ns"
	};
char tp6_str1[][15]=
	{
		"Other",
		"Unknown",
		"Standard",
		"Fast Page Mode",
		"EDO",
		"Parity",
		"ECC",
		"SIMM",
		"DIMM",
		"Burst EDO",
		"SDRAM"
	};
char tp6_str2[][52]=
	{
		"Not determinable(Installed Size only)",
		"Module is installed, but no memory has been enabled",
		"Not installed"
	};
char tp7_str1[][15]=
	{
		"Other",
		"Unknown",
		"Non-Burst",
		"Burst",
		"Pipeline Burst",
		"Synchronous",
		"Asynchronous"
	};
char tp7_str2[][15]=
	{
		"null",
		"Other",
		"Unknown",
		"None",
		"Parity",
		"Single-bit ECC",
		"Multi-bit ECC"
	};
char tp7_str3[][12]=
	{
		"null",
		"Other",
		"Unknown",
		"Instruction",
		"Data",
		"Unified"
	};
char tp7_str4[][23]=
	{
		"null",
		"Other",
		"Unknown",
		"Direct Mapped",
		"2-way Set-Associative",
		"4-way Set-Associative",
		"Fully Associative",
		"8-way Set-Associative",
		"16-way Set-Associative"
	};
char tp8_str1[][33]=
	{
		"None",
		"Centronics",
		"Mini Centronics",
		"Proprietary",
		"DB-25 pin male",
		"DB-25 pin female",
		"DB-15 pin male",
		"DB-15 pin female",
		"DB-9 pin male",
		"DB-9 pin female",
		"RJ-11",
		"RJ-45",
		"50 Pin MiniSCSI",
		"Mini-DIN",
		"Micro-DIN",
		"PS/2",
		"Infrared",
		"HP-HIL",
		"Access Bus(USB)",
		"SSA SCSI",
		"Circular DIN-8 male",
		"Circular DIN-8 female",
		"On Board IDE",
		"On Board Floppy",
		"9 Pin Dual Inline(pin 10 cut)",
		"25 Pin Dual Inline(pin 26 cut)",
		"50 Pin Dual Inline",
		"68 Pin Dual Inline",
		"On Board Sound Input from CD-ROM",
		"Mini-Centronics Type-14",
		"Mini-Centronics Type-26",
		"BNC",
		"1394",
		"SAS/SATA Plug Receptacle",
		"PC-98",
		"PC-98Hireso",
		"PC-H98",
		"PC-98Note",
		"PC-98Full",
		"Other"
	};
char tp8_str2[][31]=
	{
		"None",
		"Parallel Port XT/AT Compatible",
		"Parallel Port PS/2",
		"Parallel Port ECP",
		"Parallel Port EPP",
		"Parallel Port ECP/EPP",
		"Serial Port XT/AT Compatible",
		"Serial Port 16450 Compatible",
		"Serial Port 16550 Compatible",
		"Serial Port 16550A Compatible",
		"SCSI Port",
		"MIDI Port",
		"Joy Stick Port",
		"Keyboard Port",
		"Mouse Port",
		"SSA SCSI",
		"USB",
		"FireWire(IEEE 1394)",
		"PCMCIA Type I",
		"PCMCIA Type II",
		"PCMCIA Type III",
		"Cardbus",
		"Access Bus Port",
		"SCSI II",
		"SCSI Wide",
		"PC-98",
		"PC-98-Hireso",
		"PC-H98",
		"Video Port",
		"Audio Port",
		"Modem Port",
		"Network Port",
		"SATA",
		"SAS",
		"8251 Compatible",
		"8251 FIFO Compatible",
		"Other"
	};
char tp9_str1[][29]=
	{
		"null",
		"Other",
		"Unknown",
		"ISA",
		"MCA",
		"EISA",
		"PCI",
		"PC Card(PCMCIA)",
		"VL-VESA",
		"Proprietary",
		"Processor Card Slot",
		"Proprietary Memory Card Slot",
		"I/O Riser Card Slot",
		"NuBus",
		"PCI-66MHz Capable",
		"AGP",
		"AGP 2X",
		"AGP 4X",
		"PCI-X",
		"AGP 8X",
		"PC-98/C20",
		"PC-98/C24",
		"PC-98/E",
		"PC-98/Local Bus",
		"PC-98/Card",
		"PCI Express"
	};
char tp9_str2[][11]=
	{
		"null",
		"Other",
		"Unknown",
		"8 bit",
		"16 bit",
		"32 bit",
		"64 bit",
		"128 bit",
		"1x or x1",
		"2x or x2",
		"4x or x4",
		"8x or x8",
		"12x or x12",
		"16x or x16",
		"32x or x32"
	};
char tp9_str3[][10]=
	{
		"null",
		"Other",
		"Unknown",
		"Available",
		"In use"
	};
char tp9_str4[][13]=
	{
		"null",
		"Other",
		"Unknown",
		"Short Length",
		"Long Length"
	};
char tp9_str5[][43]=
	{
		"Characteristics Unknown",
		"Provides 5.0 Volts",
		"Provides 3.3 Volts",
		"Slot's opening is shared with another slot",
		"PC Card slot supports PC Card-16",
		"PC Card slot supports CardBus",
		"PC Card slot supports Zoom Video",
		"PC Card slot supports Modem Ring Resume"
	};
char tp9_str6[][55]=
	{
		"PCI slot supports Power Management Enable(PME#) signal",
		"Slot supports hot-plug devices",
		"PCI slot supports SMBus signal"
	};
char tp10_str1[][16]=
	{
		"null",
		"Other",
		"Unknown",
		"Video",
		"SCSI Controller",
		"Ethernet",
		"Token Ring",
		"Sound",
		"PATA Controller",
		"SATA Controller",
		"SAS Controller"
	};
char tp15_str1[][78]=
	{
		"Reserved",
		"Single-bit ECC memory error",
		"Multi-bit ECC memory error",
		"Parity memory error",
		"Bus time-out",
		"I/O Channel Check",
		"Software NMI",
		"POST Memory Resize",
		"POST Error",
		"PCI Parity Error",
		"PCI System Error",
		"CPU Failure",
		"EISA FailSafe Timer time-out",
		"Correctable memory log disabled",
		"Logging disabled for a specific Event Type - too many errors of the same type",
		"Reserved",
		"System Limit Exceeded",
		"Asynchronous hardware timer expired and issued a system reset",
		"System configuration information",
		"Hard-disk information",
		"System reconfigured",
		"Uncorrectable CPU-complex error",
		"Log Area Reset/Cleared",
		"System boot"
	};
char tp15_str2[][38]=
	{
		"None",
		"Handle",
		"Multiple-Event",
		"Multiple-Event Handle",
		"POST Results Bitmap",
		"System Management",
		"Multiple-Event System Management type"
	};
char tp16_str1[][28]=
	{
		"null",
		"Other",
		"Unknown",
		"System board or motherboard",
		"ISA add-on card",
		"EISA add-on card",
		"PCI add-on card",
		"MCA add-on card",
		"PCMCIA add-on card",
		"Proprietary add-on card",
		"NuBus",
		"PC-98/C20 add-on card",
		"PC-98/C24 add-on card",
		"PC-98/E add-on card",
		"PC-98/Local bus add-on card"
	};
char tp16_str2[][16]=
	{
		"null",
		"Other",
		"Unknown",
		"System memory",
		"Video memory",
		"Flash memoty",
		"Non-vlatile RAM",
		"Cahe memory"
	};
char tp16_str3[][15]=
	{
		"null",
		"Other",
		"Unknown",
		"None",
		"Parity",
		"Signal-bit ECC",
		"Multi-bit ECC",
		"CRC"
	};
char tp17_str1[][17]=
	{
		"null",
		"Other",
		"Unknown",
		"SIMM",
		"SIP",
		"Chip",
		"DIP",
		"ZIP",
		"Proprietary Card",
		"DIMM",
		"TSOP",
		"Row of chips",
		"RIMM",
		"SODIMM",
		"SRIMM",
		"FB-DIMM"
	};
char tp17_str2[][13]=
	{
		"null",
		"Other",
		"Unknown",
		"DRAM",
		"EDRAM",
		"VRAM",
		"SRAM",
		"RAM",
		"ROM",
		"FLASH",
		"EEPROM",
		"FEPROM",
		"EPROM",
		"CDRAM",
		"3DRAM",
		"SDRAM",
		"SGRAM",
		"RDRAM",
		"DDR",
		"DDR2",
		"DDR2 FB-DIMM"
	};
char tp17_str3[][14]=
	{
		"Reserved",
		"Other",
		"Unknown",
		"Fast-paged",
		"Static column",
		"Pseudo-static",
		"RAMBUS",
		"Synchronous",
		"CMOS",
		"EDO",
		"Window DRAM",
		"Cache DRAM",
		"Non-volatile"
	};
char tp18_str1[][27]=
	{
		"null",
		"Other",
		"Unknown",
		"OK",
		"Bad read",
		"Parity error",
		"Signal-bit error",
		"Double-bit error",
		"Multi-bit error",
		"Nibble error",
		"Checksum error",
		"CRC error",
		"Corrected single-bit error",
		"Corrected error",
		"Uncorrectable error"
	};
char tp18_str2[][23]=
	{
		"null",
		"Other",
		"Unknown",
		"Device level",
		"Memory partition level"
	};
char tp18_str3[][14]=
	{
		"null",
		"Other",
		"Unknown",
		"Read",
		"Write",
		"Partial write"
	};
char tp21_str1[][15]=
	{
		"null",
		"Other",
		"Unknown",
		"Mouse",
		"Track Ball",
		"Track Point",
		"Glide Point",
		"Touch Pad",
		"Touch Screen",
		"Optical Sensor"
	};
char tp21_str2[][23]=
	{
		"null",
		"Other",
		"Unknown",
		"Serial",
		"PS/2",
		"Infrared",
		"HP-HIL",
		"Bus mouse",
		"ADB(Apple Desktop Bus)",
		"Bus mouse DB-9",
		"Bus mouse micro-DIN",
		"USB"
	};
char tp22_str1[][21]=
	{
		"null",
		"Other",
		"Unknown",
		"Lead Acid",
		"Nickel Cadmium",
		"Nickel metal hydride",
		"Lithium-ion",
		"Zinc air",
		"Lithium Polymer"
	};
char tp26_str1[][25]=
	{
		"Other",
		"Unknown",
		"OK",
		"Non-critical",
		"Critical",
		"Non-recoverable",
		"Other",
		"Unknown",
		"Processor",
		"Disk",
		"Peripheral Bay",
		"System Management Module",
		"Motherboard",
		"Memory Module",
		"Processor Module",
		"Power Unit",
		"Add-in Card"
	};
char tp27_str1[][25]=
	{
		"Other",
		"Unknown",
		"OK",
		"Non-critical",
		"Critical",
		"Non-recoverable",
		"Other",
		"Unknown",
		"Fan",
		"Centrifugal Blower",
		"Chip Fan",
		"Cabinet Fan",
		"Power Suply Fan",
		"Heat Pipe",
		"Integrated Refrigeration",
		"Active Cooling",
		"Passive Cooling"
	};
char tp28_str1[][25]=
	{
		"Other",
		"Unknown",
		"OK",
		"Non-critical",
		"Critical",
		"Non-recoverable",
		"Other",
		"Unknown",
		"Processor",
		"Disk",
		"Peripheral Bay",
		"System Mamagement Module",
		"Motherboard",
		"Memory Module",
		"Processor Module",
		"Power Unit",
		"Add-in Card",
		"Front Panel Board",
		"Back Panel Board",
		"Power System Board",
		"Drive Back Plane"
	};
char tp29_str1[][25]=
	{
		"Other",
		"Unknown",
		"OK",
		"Non-critical",
		"Critical",
		"Non-recoverable",
		"Other",
		"Unknown",
		"Processor",
		"Disk",
		"Peripheral Bay",
		"System Mamagement Module",
		"Motherboard",
		"Memory Module",
		"Processor Module",
		"Power Unit",
		"Add-in Card"
	};
char tp34_str1[][28]=
	{
		"null",
		"Other",
		"Unknown",
		"National Semiconductor LM75",
		"National Semiconductor LM78",
		"National Semiconductor LM79",
		"National Semiconductor LM80",
		"National Semiconductor LM81",
		"Analog Devices ADM9240",
		"Dallas Semiconductot DS1780",
		"Maxim 1617",
		"Genesys GL518SM",
		"Winbond W83781D",
		"Holtek HT82H791"
	};
char tp34_str2[][9]=
	{
		"null",
		"Other",
		"Unknown",
		"I/O Port",
		"Memory",
		"SM Bus"
	};
char tp37_str1[][9]=
	{
		"null",
		"Other",
		"Unknown",
		"RamBus",
		"SyncLink"
	};
char tp38_str1[][39]=
	{
		"Unknown",
		"KCS: Keyboard Controller Style",
		"SMIC: Server Management Interface Chip",
		"BT: Block Transfer"
	};
char tp39_str1[][10]=
	 {
	 	"Other",
	 	"Unknown",
	 	"Linear",
	 	"Switching",
	 	"Battery",
	 	"UPS",
	 	"Converter",
	 	"Regulator"
	 };
char tp39_str2[][64]=
	  {
	  	"Other",
	  	"Unknown",
	  	"OK",
	  	"Non-critical",
	  	"critical, power supply has failed and has been taken off-line"
	  };
char tp39_str3[][17]=
	  {
	  	"Other",
	  	"Unknown",
	  	"Manual",
	  	"Auto-switch",
	  	"Wide range",
	  	"Not applicable"
	  };
