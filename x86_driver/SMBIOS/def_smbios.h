


struct SMBStructHeader
{
	BYTE	type;
	BYTE	length;
	WORD	handle;
};
#define SMB_STRUCT_HEADER  SMBStructHeader header;


struct SMB_ENTRY_POINT
{
	char	anchor[4];
	BYTE	checksum;
	BYTE	length;
	BYTE	majorVer;
	BYTE	minorVer;
	WORD	maxSize;
	BYTE	entryRev;
	BYTE	FA[5];
	BYTE	dmi_anchor[5];
	BYTE	dmi_checksum;
	WORD	tableLength;
	DWORD	tableAddress;
	WORD	structureCount;
	BYTE	bcdRevision;
};

//
// BIOS Information (Type 0)
//
struct SMBStructBIOSInformation
{
	SMB_STRUCT_HEADER               // Type 0
	BYTE  vendor;              // BIOS vendor name
	BYTE  version;             // BIOS version
	WORD	startSegment;        // BIOS segment start
	BYTE  releaseDate;         // BIOS release date
	BYTE	romSize;             // (n); 64K * (n+1) bytes
	BYTE	characteristics[8];     // supported BIOS functions
	//2.1+ spec
	BYTE	characteristicsExByte1; //optional space reserved
	//2.3+ spec
	BYTE	characteristicsExByte2; //optional space reserved
	//2.5+ spec
	BYTE	biosMajorRelease; //identifies the major release of bios
	BYTE	biosMinorRelease; //identifies the minor release of bios
//	char	string[3][100];
};

//
// System Information (Type 1)
//
struct SMBStructSystemInformation
{
	// 2.0+ spec (8 bytes)
	SMB_STRUCT_HEADER               // Type 1
	BYTE  manufacturer;
	BYTE  productName;
	BYTE  version;
	BYTE  serialNumber;
	// 2.1+ spec (25 bytes)
	BYTE	uuids[16];            // can be all 0 or all 1's
	BYTE	wakeupType;        // event for system wakeup
	//2.4+ spec
	BYTE	skuNumber;		//
	BYTE	family;		//
//	char string[6][200];
};

//
//Base Board Information (Type 2)
//
struct SMBStructBaseBoardInformation
{
	SMB_STRUCT_HEADER
	BYTE	manufacturer;
	BYTE	product;
	BYTE	version;
	BYTE	serialNumber;
	BYTE	assetTag;
	BYTE	featureFlags;
	BYTE	locationInChassis;
	WORD	chassisHandle;
	BYTE	boardType;
	BYTE	numberOfContainObjectHandles;
	WORD	containedObjectHandles[256]; //maximum 0-255
//	char string[10][100];
};

//
// System Enclosure (Type 3)
//
struct SMBStructSystemEnclosure
{
	SMB_STRUCT_HEADER               // Type 3
	BYTE  manufacturer;
	BYTE	type;
	BYTE  version;
	BYTE  serialNumber;
	BYTE  assetTagNumber;
	BYTE	bootupState;
	BYTE	powerSupplyState;
	BYTE	thermalState;
	BYTE	securityStatus;
	//2.3+spec
	DWORD	oemDefined;
	BYTE	height;
	BYTE	numberOfCords;
	BYTE	containedElementCount;
	BYTE	containedElementRecordLength;
	BYTE	containedElements[256][256];
//	char string[4][100];
};

//
// Processor Information (Type 4)
//
struct SMBStructProcessorInformation
{
	// 2.0+ spec (26 bytes)
	SMB_STRUCT_HEADER               // Type 4
	BYTE  socketDesignation;
	BYTE	processorType;       // CPU = 3
	BYTE	processorFamily;     // processor family enum
	BYTE  manufacturer;
	BYTE  processorID[8];         // based on CPUID
	BYTE  processorVersion;
	BYTE	voltage;             // bit7 cleared indicate legacy mode
	WORD	externalClock;       // external clock in MHz
	WORD	maximumClock;        // max internal clock in MHz
	WORD	currentClock;        // current internal clock in MHz
	BYTE	status;
	BYTE	processorUpgrade;    // processor upgrade enum
	// 2.1+ spec (32 bytes)
	WORD	L1CacheHandle;
	WORD	L2CacheHandle;
	WORD	L3CacheHandle;
	// 2.3+ spec (35 bytes)
	BYTE  serialNumber;
	BYTE  assetTag;
	BYTE  partNumber;
	// 2.5+ spec
	BYTE	coreCount;
	BYTE	coreEnabled;
	BYTE	threadCount;
	WORD	processorCharacteristics;
	WORD	processorFamily2;
//	char string[10][100];
};

//
// Memory Controller Information (Type 5)
//
struct SMBStructMemoryController
{
	SMB_STRUCT_HEADER
	BYTE	errorDetectingMethod;
	BYTE	errorCorrectingCapability;
	BYTE	supportedInterleave;
	BYTE	currentInterleave;
	BYTE	maximumMemoryModuleSize;
	WORD	supportedSpeeds;
	WORD	supportedMemoryTypes;
	BYTE	memoryModuleVoltage;
	BYTE	numberOfAssociatedMemorySlot;
	WORD	memoryModuleConfigurationHandles[256];
	BYTE	enabledErrorCorrectingCapabilites;
};

//
// Memory Module Information (Type 6)
// Obsoleted since SMBIOS version 2.1
//
struct SMBStructMemoryModule
{
	SMB_STRUCT_HEADER               // Type 6
	BYTE	socketDesignation;
	BYTE	bankConnections;
	BYTE	currentSpeed;
	WORD	currentMemoryType;
	BYTE	installedSize;
	BYTE	enabledSize;
	BYTE	errorStatus;
//	char	string[10][100];
};

//
// Cache Information (Type 7)
//
struct SMBStructCacheInformation
{
	SMB_STRUCT_HEADER               // Type 7
	BYTE  socketDesignation;
	WORD	cacheConfiguration;
	WORD	maximumCacheSize;
	WORD	installedSize;
	WORD	supportedSRAMType;
	WORD	currentSRAMType;
	BYTE	cacheSpeed;
	BYTE	errorCorrectionType;
	BYTE	systemCacheType;
	BYTE	associativity;
//	char	string[10][100];
};

//
// Port Connector Information (Type 8)
//
struct SMBStructPortConnectorInformation
{
	SMB_STRUCT_HEADER               // Type 8
	BYTE	internalReferenceDesignator;
	BYTE	internalConnectorType;
	BYTE	externalReferenceDesignator;
	BYTE	externalConnectorType;
	BYTE	portType;
//	char	string[2][100];
};

//
// System Slots (Type 9)
//
struct SMBStructSystemSlots
{
	SMB_STRUCT_HEADER               // Type 9
	BYTE	slotDesignation;
	BYTE	slotType;
	BYTE	slotDataBusWidth;
	BYTE	currentUsage;
	BYTE	slotLength;
	WORD	slotID;
	BYTE	slotCharactertics1;
	BYTE	slotCharactertics2;
	WORD	segmentGroupNumber;
	BYTE	busNumber;
	BYTE	deviceFunctionNumber;
//	char	string[10][200];
};

struct deviceTypes
{
	BYTE	deviceType;
	BYTE	descriptionString;
};

//
// on board device Information (Type 10)
//
struct SMBStructOnBoardDeviceInformation
{
	SMB_STRUCT_HEADER               // Type 10
	deviceTypes	devices[256];
//	char string[256][200];
};

//
// OEM String (Type 11)
//
struct SMBStructOEMString
{
	SMB_STRUCT_HEADER               // Type 11
	BYTE	count;
//	char string[10][200];
};

//
// system configuration options (Type 12)
//
struct SMBStructSystemConfigurationOptions
{
	SMB_STRUCT_HEADER               // Type 12
	BYTE	count;
//	char	string[2][100];
};

//
// BIOS language Information (Type 13)
//
struct subSMBStructBIOSLanguageInformation
{
	BYTE	reserved[15];
	BYTE	currentLanguage;
};

struct SMBStructBIOSLanguageInformation
{
	SMB_STRUCT_HEADER               // Type 13
	BYTE	installableLanguages;
	BYTE	flags; //since 2.1
	struct subSMBStructBIOSLanguageInformation *sub;
	//BYTE	reserved[15];
	//BYTE	currentLanguage;
};


//
// group assocications (Type 14)
//
struct SMBStructGroupAssociations
{
	SMB_STRUCT_HEADER               // Type 14
	BYTE	groupName;
	BYTE	itemType;
	WORD	itemHandle;
//	char	string[2][100];
};

struct listOfSupportedEventLog
{
	BYTE	logType;
	BYTE	variableDataFromatType;
};

//
// system event log (Type 15)
//
struct SMBStructSystemEventLog
{
	SMB_STRUCT_HEADER               // Type 15
	WORD	logAreaLength;
	WORD	logHeaderStartOffset;
	WORD	logDataStartOffset;
	BYTE	accessMethod;
	BYTE	logStatus;
	DWORD	logChangeToken;
	DWORD accessMethodAddress;
	BYTE	logHeaderFormat;
	BYTE	numberOfSupportedLogTypeDescription;
	BYTE	lengthOfEachLogTypeDescriptor;
	listOfSupportedEventLog	eventLog[512];
};

//
// Physical Memory Array (Type 16)
//
struct SMBStructPhysicalMemoryArray
{
	// 2.1+ spec (15 bytes)
	SMB_STRUCT_HEADER               // Type 16
	BYTE    physicalLocation;    // physical location
	BYTE    arrayUse;            // the use for the memory array
	BYTE    errorCorrection;     // error correction/detection method
	DWORD   maximumCapacity;     // maximum memory capacity in kilobytes
	WORD    errorHandle;         // handle of a previously detected error
	WORD    numMemoryDevices;    // number of memory slots or sockets
	//char unsued;
};

//
// Memory Device (Type 17)
//
struct SMBStructMemoryDevice
{
	// 2.1+ spec (21 bytes)
	SMB_STRUCT_HEADER               // Type 17
	WORD	arrayHandle;         // handle of the parent memory array
	WORD	errorHandle;         // handle of a previously detected error
	WORD	totalWidth;          // total width in bits; including ECC bits
	WORD	dataWidth;           // data width in bits
	WORD	memorySize;          // bit15 is scale, 0 = MB, 1 = KB
	BYTE	formFactor;          // memory device form factor
	BYTE	deviceSet;           // parent set of identical memory devices
	BYTE  deviceLocator;       // labeled socket; e.g. "SIMM 3"
	BYTE  bankLocator;         // labeled bank; e.g. "Bank 0" or "A"
	BYTE	memoryType;          // type of memory
	WORD	memoryTypeDetail;    // additional detail on memory type
	// 2.3+ spec (27 bytes)
	WORD	memorySpeed;         // speed of device in MHz (0 for unknown)
	BYTE  manufacturer;
	BYTE  serialNumber;
	BYTE  assetTag;
	BYTE  partNumber;
	BYTE	attributes;
//	char	string[7][100];
};

//
// 32-bit Memory Error Information (Type 18)
//
struct SMBStruct32MemoryErrorInformation
{
	SMB_STRUCT_HEADER               // Type 18
	BYTE	errorType;
	BYTE	errorGranularity;
	BYTE	errorOperation;
	DWORD	vendorSyndrome;
	DWORD	memoryArrayErrorAddress;
	DWORD	deviceErrorAddress;
	DWORD errorResolution;
};

//
// Memory Array Mapped Address (Type 19)
//
struct SMBStructMemoryArrayMappedAddress
{
	SMB_STRUCT_HEADER               // Type 19
	DWORD	startingAddress;
	DWORD	endingAddress;
	WORD	memoryArrayHandle;
	BYTE	partitionWidth;
};

//
// Memory Device Mapped Address (Type 20)
//
struct SMBStructMemoryDeviceMappedAddress
{
	SMB_STRUCT_HEADER               // Type 20
	DWORD	startingAddress;
	DWORD	endingAddress;
	WORD	memoryDeviceHandle;
	WORD	memoryArrayMappedAddressHandle;
	BYTE	partitionRowPosition;
	BYTE	interleavePosition;
	BYTE	interleaveDataDepth;
};

//
// Build-in pointing device (Type 21)
//
struct SMBStructBuildInPointingDevice
{
	SMB_STRUCT_HEADER               // Type 21
	BYTE	type;
	BYTE	interfaceType;
	BYTE	numberOfButtons;
};

//
// Portable Battery (Type 22)
//
struct SMBStructPortableBattery
{
	SMB_STRUCT_HEADER               // Type 22
	BYTE	location;
	BYTE	manufacturer;
	BYTE	manufactureDate;
	BYTE	serialNumber;
	BYTE	deviceName;
	BYTE	deviceChemistry;
	WORD	designCapacity;
	WORD	designVlotage;
	BYTE	SBDSVersionNumber;
	BYTE	maximumErrorInBatteryData;
	WORD	SBDSSerialNumber;
	WORD	SBDSManufactureDate;
	BYTE	SBDSDeviceChemistry;
	BYTE	designCapacityMultiplier;
	DWORD	OEM;
//	char	string[10][100];
};

//
// System reset (Type 23)
//
struct SMBStructSystemReset
{
	SMB_STRUCT_HEADER               // Type 23
	BYTE	capabilities;
	WORD	resetCount;
	WORD	resetLimit;
	WORD	timerInterval;
	WORD	timeout;
};

//
// Hardware Security (Type 24)
//
struct SMBStructHardwareSecurity
{
	SMB_STRUCT_HEADER               // Type 24
	BYTE	hardwareSecuritySettings;
};

//
// System Power Controls (Type 25)
//
struct SMBStructSystemPowerControls
{
	SMB_STRUCT_HEADER               // Type 25
	BYTE	nextScheduledPowerOnMonth;
	BYTE	nextScheduledPowerOnDayOfMonth;
	BYTE	nextScheduledPowerOnHour;
	BYTE	nextScheduledPowerOnMinute;
	BYTE	nextScheduledPowerOnSecond;
};

//
// Voltage Probe (Type 26)
//
struct SMBStructVoltageProbe
{
	SMB_STRUCT_HEADER               // Type 26
	BYTE	description;
	BYTE	locationAndStatus;
	WORD	maximumValue;
	WORD	minimumValue;
	WORD	resolution;
	WORD	tolerance;
	WORD	accuracy;
	DWORD	OEM;
	WORD	nominalValue;
//	char	string[10][100];
};

//
// Cooling Device (Type 27)
//
struct SMBStructCoolingDevice
{
	SMB_STRUCT_HEADER               // Type 27
	WORD	temperatureProbeHandle;
	BYTE	deviceTypeAndStatus;
	BYTE	coolingUnitGroup;
	DWORD	OEM;
	WORD	nominalSpeed;
};

//
// Temperature Probe (Type 28)
//
struct SMBStructTemperatureProbe
{
	SMB_STRUCT_HEADER               // Type 28
	BYTE	description;
	BYTE	locationAndStatus;
	WORD	maximumValue;
	WORD	minimumValue;
	WORD	resolution;
	WORD	tolerance;
	WORD	accuracy;
	DWORD	OEM;
	WORD	nominalValue;
//	char	string[10][100];
};

//
// Electrical Current Probe (Type 29)
//
struct SMBStructElectricalCurrentProbe
{
	SMB_STRUCT_HEADER               // Type 29
	BYTE	description;
	BYTE	locationAndStatus;
	WORD	maximumValue;
	WORD	minimumValue;
	WORD	resolution;
	WORD	tolerance;
	WORD	accuracy;
	DWORD	OEM;
	WORD	nominalValue;
//	char	string[10][100];
};

//
// Out-of-Band Remote Access (Type 30)
//
struct SMBStructOutOfBandRemoteAccess
{
	SMB_STRUCT_HEADER               // Type 30
	BYTE	manufacturerName;
	BYTE	connections;
//	char	string[10][100];
};

//
// Boot Integrity Services Entry Point (Type 31)
//
/*struct SMBStruct
{
	SMB_STRUCT_HEADER               // Type 31
};*/

//
// System Boot Information (Type 32)
//
struct SMBStructSystemBootInformation
{
	SMB_STRUCT_HEADER               // Type 32
	BYTE	reserved[6];
	BYTE	bootStatus[246];
};

//
// Memory Error Information (Type 33)
//
struct SMBStructMemoryErrorInformation
{
	SMB_STRUCT_HEADER               // Type 33
	BYTE	errorType;
	BYTE	errorGranularity;
	BYTE	errorOperation;
	DWORD	vendorSyndrome;
	BYTE	memoryArrayErrorAddress[8];
	BYTE deviceErrorAddress[8];
	DWORD	errorResolution;
};

//
// Management Device (Type 34)
//
struct SMBStructManagementDevice
{
	SMB_STRUCT_HEADER               // Type 34
	BYTE	description;
	BYTE	type;
	DWORD	address;
	BYTE	addressType;
//	char	string[10][100];
};

//
// Management Device Component (Type 35)
//
struct SMBStructManagementDeviceComponent
{
	SMB_STRUCT_HEADER               // Type 35
	BYTE	description;
	WORD	managementDeviceHandle;
	WORD	componentHandle;
	WORD	thresholdHandle;
//	char	string[10][100];
};

//
// Management Device Threshold Data (Type 36)
//
struct SMBStructManagementDeviceThresholdData
{
	SMB_STRUCT_HEADER               // Type 36
	WORD	lowerThreshold_non_Critical;
	WORD	upperThreshold_non_Critical;
	WORD	lowerThreshold_Critical;
	WORD	upperThreshold_Critical;
	WORD	lowerThreshold_non_Recoverable;
	WORD	upperThreshold_non_Recoverable;
};


struct memoryNload
{
	BYTE	memoryDeviceLoad;
	WORD	memoryDeviceHandle;
};

//
// Memory Channel (Type 37)
//
struct SMBStructMemoryChannel
{
	SMB_STRUCT_HEADER               // Type 37
	BYTE	channelType;
	BYTE	maximumChannelLoad;
	BYTE	memoryDeviceCount;
	BYTE	memoryDeviceLoad;
	WORD	memoryDeviceHandle;

	memoryNload memoryDeviceN[256];

};

//
// IPMI	Device Information (Type 38)
//
struct SMBStructIPMIDeviceInformation
{
	SMB_STRUCT_HEADER               // Type 38
	BYTE	interfaceType;
	BYTE	ipmiSpecificationRevision;
	BYTE	i2cSlaveAddress;
	BYTE	nvStorageDeviceAddress;
	BYTE	baseAddress[8];
};

//
// System Power Supply (Type 39)
//
struct SMBStructSystemPowerSupply
{
	SMB_STRUCT_HEADER               // Type 39
	BYTE	powerUnitGroup;
	BYTE	location;
	BYTE	deviceName;
	BYTE	manufacturer;
	BYTE	serialNumber;
	BYTE	assetTagNumber;
	BYTE	modelPartNumber;
	BYTE	revisionLevel;
	WORD	maxPowerCapacity;
	WORD	powerSupplyCharacteristics;
	WORD	inputVoltageProbeHandle;
	WORD	coolingDeviceHandle;
	WORD	inputCurrentProbeHandle;
//	char	string[7][100];
};



