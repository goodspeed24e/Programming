struct RSDP
{
	char signature[8];
	BYTE checksum;
	char OEMID[6];
	BYTE revision;
	DWORD rsdt_addr;
	DWORD length;
	DWORD xsdt_addr[2];
	BYTE ex_checksum;
	char reserved[3];
};

struct DESC_TABLE_HEAD
{
	char signature[4];
	DWORD length;
	BYTE revision;
	BYTE checksum;
	char OEMID[6];
	char OEM_table_ID[8];
	DWORD OEM_revision;
	DWORD creator_id;
	DWORD creator_revision;
};

#define ACPI_DESC_HEADER  DESC_TABLE_HEAD header;

struct RSDT
{
	ACPI_DESC_HEADER
	DWORD entry[30]; //n個
};

struct XSDT
{
	ACPI_DESC_HEADER
	DWORD entry[30][2]; //n個
};

struct FADT//FACP
{
	ACPI_DESC_HEADER
	DWORD firmware_ctrl;
	DWORD DSDT;
	BYTE reserved1;
	BYTE preferred_pm_profile;
	WORD sci_int;
	DWORD smi_cmd;
	BYTE acpi_enable;
	BYTE acpi_disable;
	BYTE s4bios_req;
	BYTE pstate_cnt;
	DWORD pm1a_evt_blk;
	DWORD pm1b_evt_blk;
	DWORD pm1a_cnt_blk;
	DWORD pm1b_cnt_blk;
	DWORD pm2_cnt_blk;
	DWORD pm_tmr_blk;
	DWORD gpe0_blk;
	DWORD gpe1_blk;
	BYTE pm1_evt_len;
	BYTE pm1_cnt_len;
	BYTE pm2_cnt_len;
	BYTE pm_tmr_len;
	BYTE gpe0_blk_len;
	BYTE gpe1_blk_len;
	BYTE gpe1_base;
	BYTE cst_cnt;
	WORD p_lvl2_lat;
	WORD p_lvl3_lat;
	WORD flush_size;
	WORD flush_stride;
	BYTE duty_offset;
	BYTE duty_width;
	BYTE day_alrm;
	BYTE mon_alrm;
	BYTE century;
	WORD iapc_boot_arch;
	BYTE reserved2;
	DWORD flags;
	BYTE reset_reg[12];
	BYTE reset_value;
	BYTE reserved3[3];
	BYTE x_firmware_ctrl[8];
	BYTE x_dsdt[8];
	BYTE x_pm1a_evt_blk[12];
	BYTE x_pm1b_evt_blk[12];
	BYTE x_pm1a_cnt_blk[12];
	BYTE x_pm1b_cnt_blk[12];
	BYTE x_pm2_cnt_blk[12];
	BYTE x_pm_tmr_blk[12];
	BYTE x_gpe0_blk[12];
	BYTE x_gpe1_blk[12];
};

struct FACS
{
	char signature[4];
	DWORD length;
	char hardware_signature[4];
	DWORD firmware_waking_vector;
	DWORD global_lock;
	DWORD flags;
	DWORD x_firmware_waking_vector[2];
	BYTE version;
	BYTE reserved[31];
};

/*struct APIC
{
	BYTE type;
	BYTE length;
	BYTE IO_apic_id;
	BYTE reserved;
	DWORD IO_apic_address;
	DWORD global_system_int_base;
};*/

struct DSDT
{
	ACPI_DESC_HEADER
	//BYTE definition;  // n-byte
};

struct SSDT
{
	ACPI_DESC_HEADER
	//BYTE definition;  // n-byte
};

//PSDT參考 SSDT

struct MADT
{
	ACPI_DESC_HEADER
	DWORD local_acpi_address;
	DWORD flags;
	//BYTE apic_struct;  // n堆資料
};

struct SBST
{
	ACPI_DESC_HEADER
	DWORD warning_energy_level;
	DWORD low_energy_level;
	DWORD critical_energy_level;
};

struct ECDT
{
	ACPI_DESC_HEADER
	BYTE ec_control[12];
	BYTE ec_data[12];
	DWORD uid;
	BYTE gpe_bit;
	//BYTE ec_id; //長字串
};

struct SRAT
{
	ACPI_DESC_HEADER
	DWORD reserved[3];
	//BYTE static_resource_struct; //n堆struct
};

struct SLIT
{
	ACPI_DESC_HEADER
	DWORD number_system_localities[2];
	//BYTE entry; //n堆struct
};

struct MCFG
{
	ACPI_DESC_HEADER
	//BYTE base_address; //n堆struct
};

struct BOOT
{
	ACPI_DESC_HEADER
	BYTE cmos_index;
	BYTE reserved[3];
};

struct HPET
{
	ACPI_DESC_HEADER
	DWORD event_timer_block_id;
	BYTE base_address_low_32[12];
	BYTE hpet_number;
	WORD main_counter;
	BYTE page_protection;
};

struct CPEP
{
	ACPI_DESC_HEADER
	BYTE reserved[8];
	//一堆structure
};

struct DBGP
{//http://www.microsoft.com/whdc/archive/dbgportspec.mspx
	ACPI_DESC_HEADER
	BYTE interface_type;
	BYTE reserved[3];
	BYTE base_address[12];
};

struct SPRC
{
	ACPI_DESC_HEADER
	BYTE interface_type;
	BYTE reserved[3];
	BYTE base_address[12];
	BYTE interrupt_type;
	BYTE irq;
	DWORD global_system_interrupt;
	BYTE baud_rate;
	BYTE parity;
	BYTE stop_bits;
	BYTE flow_control;
	BYTE terminal_type;
	BYTE reserved2;
	WORD pci_device_id;
	WORD pci_vendor_id;
	BYTE pci_bus_number;
	BYTE pci_device_number;
	BYTE pci_func_number;
	DWORD pci_flags;
	BYTE pci_segment;
	DWORD reserved3;
};

struct SPMI
{
	ACPI_DESC_HEADER
	BYTE interface_type;
	BYTE reserved;
	WORD specification_rev;
	BYTE interrupt_type;
	BYTE gpe;
	BYTE reserved2;
	BYTE pci_device_flag;
	DWORD global_system_interrupt;
	BYTE base_address[12];
	BYTE pci_segment_group_number;
	BYTE pci_bus_number;
	BYTE pci_device_number;
	BYTE pci_func_number;
	BYTE reserved3;
};

//TCPA


struct WDAT
{
	ACPI_DESC_HEADER
	DWORD watchdog_header_length;
	WORD pci_segment;
	BYTE pci_bus_number;
	BYTE pci_device_number;
	BYTE pci_func_number;
	BYTE reserved[3];
	DWORD timer_period;
	DWORD maximum_count;
	DWORD minimum_count;
	BYTE watchdog_flag;
	BYTE reserved2[3];
	DWORD number_watchdog_instruction_entries;
	//一堆structure
};

struct WDRT
{//http://www.microsoft.com/whdc/system/CEC/watchdog.mspx
	ACPI_DESC_HEADER
	BYTE control_register_address[12];
	BYTE count_register_address[12];
	WORD pci_device_id;
	WORD pci_vendor_id;
	BYTE pci_bus_number;
	BYTE pci_device_number;
	BYTE pci_func_number;
	BYTE pci_segment;
	WORD max_count;
	BYTE units;
};

//WSPT



struct ERST
{
	ACPI_DESC_HEADER
	DWORD serialization_header_size;
	DWORD reserved;
	DWORD Instruction_entry_count;
	//一堆資料
};

struct ERST_ACTION_TABLE
{
	BYTE serialization_action;
	BYTE instruction;
	BYTE flags;
	BYTE reserved;
	DWORD register_region_low;
	DWORD register_region_mid;
	DWORD register_region_hi;
	DWORD value_low;
	DWORD value_hi;
	DWORD mask_low;
	DWORD mask_hi;
};


struct BERT
{
	ACPI_DESC_HEADER
	DWORD boot_error_region_length;
	DWORD boot_error_region_low;
	DWORD boot_error_region_hi;
};


struct BOOT_ERROR_REGION
{
	DWORD block_status;
	DWORD raw_data_offset;
	DWORD raw_data_length;
	DWORD data_length;
	DWORD error_severity;
	//一堆資料
	
};




struct HEST
{
	ACPI_DESC_HEADER
	DWORD error_source_count;
	//一堆資料
};


struct MEST_ERROR
{
	WORD type;
	WORD source_id;
	WORD configuration_write_enable;
	BYTE flasg;
	BYTE reserved;
	DWORD number_of_records_to_pre_allocate;
	DWORD max_sections_per_record;
};


struct EINJ
{
	ACPI_DESC_HEADER
	DWORD injection_header_size;
	BYTE reserved;
	DWORD injection_entry_count;
	//一堆資料
};

struct INJECTION_INSTRUCTION_ENTRY
{
	BYTE injection_action;
	BYTE instruction;
	BYTE flags;
	BYTE reserved;
	DWORD register_region_low;
	DWORD register_region_mid;
	DWORD register_region_hi;
	DWORD value_low;
	DWORD value_hi;
	DWORD mask_low;
	DWORD mask_hi;
};

