// ka_pci.h
//
// Copyright (c) 1998-1999 Symbian Ltd.  All rights reserved.
// Copyright 2000 ARM Limited.
//

#ifndef __KA_PCI_H__
#define __KA_PCI_H__

#include <m32std.h>

typedef struct {
    TUint32	devid;
	TUint16 vendor;
	TUint16 device;
	TUint16 command;	// command register
	TUint16 status;		// status register
	TUint32 class_rev;	// class+revision
	TUint8  cache_line_size;// cache line size
	TUint8  latency_timer;	// latency timer
	TUint32 header_type;    // header type
	TUint8  bist;		// Built-in Self-Test
	TUint32 base_address[6];// Memory base address registers
	TUint32 virt_base_address[6];// virtual mapped address of base_address

	// The following fields are used by the resource allocation
	// routines to keep track of allocated resources.
	TUint32 base_size[6];    // Memory size for each base address
	TUint32 base_map[6];     // Physical address mapped
	TUint32 vector;          // interrupt vector

	struct {
	    TUint32  cardbus_cis;    // CardBus CIS Pointer
            TUint16  sub_vendor;     // subsystem vendor id
            TUint16  sub_id;         // subsystem id
            TUint32  rom_address;    // ROM address register
            TUint8   cap_list;       // capability list
            TUint8   reserved1[7];
            TUint8   int_line;       // interrupt line
            TUint8   int_pin;        // interrupt pin
            TUint8   min_gnt;        // timeslice request
            TUint8   max_lat;        // priority-level request
        } normal;
} DevInfo; 

#define SZ_256M                         0x10000000

#define INTA 	13	// EIntPci0
#define INTB 	14	// EIntPci1
#define INTC 	15	// EIntPci2
#define INTD 	16	// EIntPci3

#define PCI_MAX_BUS	1  // Just the one for now
#define PCI_MIN_DEV	10
#define PCI_MAX_DEV	13
#define PCI_MAX_FN	8
#define PCI_MAX_BAR	6

#define PCI_IO_ENABLE                   0x0001
#define PCI_MEM_ENABLE                  0x0002
#define PCI_MASTER_ENABLE               0x0004
#define PCI_MEM_WRINVALID               0x0010
#define PCI_FAST_B2B                    0x0200

//
// V3 access routines
//
#define _V3Write16(o,v) (*(volatile TUint16 *)(KHwV3Base + (TUint32)(o)) = (TUint16)(v))
#define _V3Read16(o)    (*(volatile TUint16 *)(KHwV3Base + (TUint32)(o)))

#define _V3Write32(o,v) (*(volatile TUint32 *)(KHwV3Base + (TUint32)(o)) = (TUint32)(v))
#define _V3Read32(o)    (*(volatile TUint32 *)(KHwV3Base + (TUint32)(o)))

#define PCI_DEV_MAKE_ID(bus,devfn)	(((bus)<<16)|((devfn)<<8))
#define PCI_DEV_GET_BUS(devid) 		((devid>>16)&0xFF)
#define PCI_DEV_GET_DEVFN(devid) 	((devid>>8)&0xFF)
#define PCI_DEV_MAKE_DEVFN(dev, fn) 	(((dev)<<3)|(fn))
#define PCI_DEV_GET_DEV(devfn) 		((devfn>>3)&0x1f)
#define PCI_DEV_GET_FN(devfn) 		(devfn&0x7)

#define PCI_COMMAND_ACTIVE	(0x0001 | 0x0002 | 0x0004)

#define PCI_BAR_SPACE_MASK      	0x00000001
#define PCI_BAR_SPACE_MEM       	0x00000000
#define PCI_BAR_SPACE_IO        	0x00000001

#define PCI_PRI_BAR_MEM_TYPE_MASK	0x00000006
#define PCI_PRI_BAR_MEM_TYPE_32		0x00000000
#define PCI_PRI_BAR_MEM_TYPE_1M		0x00000002
#define PCI_PRI_BAR_MEM_TYPE_64		0x00000004
#define PCI_PRI_BAR_IO_MASK		0xfffffffc

#define PCI_PRI_BAR_MEM_MASK		0xfffffff0


#define PCI_HEADER_TYPE_MASK		0x7f

/**
 * 
 * philk - L999
 * Changed a bunch of the vaddr defines below since the Symbian
 * base port had a different paddr/vaddr mapping for the IO space.
 */

class TPCICard
{
public:
    enum TPciAddresses
	{

	/* 
	 * philk 
 	 * Do this by looking at the BDB entries in the bootstrap code. Fun.
	 */

	KHwSCBaseLin		= 0x58001000,	// Linear address
	KHwCpuPciIoAdrsLin	= 0x5800C000,	// PCI I/O space base 	@ 0x60000000
	KHwPciConfigBaseLinJ11	= 0x5801C000,	// PCI Config area 	@ 0x61200000
	KHwPciConfigBaseLinJ10	= 0x5801D000,	// PCI Config area 	@ 0x61400000
	KHwPciConfigBaseLinJ9	= 0x5801E000,	// PCI Config area 	@ 0x61800000
	KHwV3BaseLin		= 0x5801F000,	// V360EPC registers 	@ 0x62000000

	/* 
	 * philk - obviously all these are OK!!
	 */

	KHwPhysPciBase		= 0x40000000, 
	KHwPhysSCBase		= 0x11000000,	// System Controller physical address
	KHwPhysV3Base		= 0x62000000,	// V360EPC registers
	KHwPhysBootRomBase	= 0x20000000,	// Boot ROM base physical address
	KHwPhysHdr0SDRAMBase 	= 0x80000000,	// HDR0 SDRAM
	KHwPhysCpuPciIoAdrs	= 0x60000000, 	// PCI I/O space base
	KHwPhysPciConfigBase	= 0x61000000,

	KHwV3Base		= KHwV3BaseLin
	};

    enum TPciRegisters
	{
	ESC_PCIENABLE		= 0x00000018,
	EV3_PCI_VENDOR		= 0x00000000,
	EV3_PCI_DEVICE		= 0x00000002,
	EV3_PCI_CMD		= 0x00000004,
	EV3_PCI_STAT		= 0x00000006,
	EV3_PCI_CC_REV		= 0x00000008,
	EV3_PCI_HDR_CFG		= 0x0000000C,
	EV3_PCI_LATENCY_TIMER	= 0x0000000D,
	EV3_PCI_HEADER_TYPE	= 0x0000000E,
	EV3_PCI_BIST		= 0x0000000F,
	EV3_PCI_IO_BASE 	= 0x00000010,
	EV3_PCI_BAR_0		= 0x00000010,
	EV3_PCI_BAR_1		= 0x00000014,
	EV3_PCI_BAR_2		= 0x00000018,
	EV3_PCI_BAR_3		= 0x0000001C,
	EV3_PCI_BAR_4		= 0x00000020,
	EV3_PCI_BAR_5		= 0x00000014,
	EV3_PCI_BASE0		= 0x00000014,
	EV3_PCI_BASE1		= 0x00000018,
	EV3_PCI_CARDBUS_CIS	= 0x00000028,
	EV3_PCI_SUB_VENDOR 	= 0x0000002C,
	EV3_PCI_SUB_ID		= 0x0000002E,
	EV3_PCI_ROM		= 0x00000030,
	EV3_PCI_CAP_LIST	= 0x00000034,
	EV3_PCI_BPARAM		= 0x0000003C,
	EV3_PCI_INT_LINE	= 0x0000003C,
	EV3_PCI_INT_PIN		= 0x0000003D,
	EV3_PCI_MIN_GNT		= 0x0000003E,
	EV3_PCI_MAX_LAT		= 0x0000003F,
	EV3_PCI_MAP0		= 0x00000040,
	EV3_PCI_MAP1		= 0x00000044,
	EV3_PCI_INT_STAT	= 0x00000048,
	EV3_PCI_INT_CFG 	= 0x0000004C,
	EV3_LB_BASE0		= 0x00000054,
	EV3_LB_BASE1		= 0x00000058,
	EV3_LB_MAP0		= 0x0000005E,
	EV3_LB_MAP1		= 0x00000062,
	EV3_LB_BASE2		= 0x00000064,
	EV3_LB_MAP2		= 0x00000066,
	EV3_LB_SIZE		= 0x00000068,
	EV3_LB_IO_BASE		= 0x0000006E,
	EV3_FIFO_CFG		= 0x00000070,
	EV3_FIFO_PRIORITY 	= 0x00000072,
	EV3_FIFO_STAT		= 0x00000074,
	EV3_LB_ISTAT		= 0x00000076,
	EV3_LB_IMASK		= 0x00000077,
	EV3_SYSTEM		= 0x00000078,
	EV3_LB_CFG		= 0x0000007A,
	EV3_PCI_CFG		= 0x0000007C,
	EV3_DMA_PCI_ADR0	= 0x00000080,
	EV3_DMA_PCI_ADR1	= 0x00000090,
	EV3_DMA_LOCAL_ADR0 	= 0x00000084,
	EV3_DMA_LOCAL_ADR1 	= 0x00000094,
	EV3_DMA_LENGTH0 	= 0x00000088,
	EV3_DMA_LENGTH1		= 0x00000098,
	EV3_DMA_CSR0		= 0x0000008B,
	EV3_DMA_CSR1		= 0x0000009B,
	EV3_DMA_CTLB_ADR0	= 0x0000008C,
	EV3_DMA_CTLB_ADR1	= 0x0000009C,
	EV3_DMA_DELAY		= 0x000000E0,
	EV3_MAIL_DATA		= 0x000000C0,
	EV3_PCI_MAIL_IEWR 	= 0x000000D0,
	EV3_PCI_MAIL_IERD 	= 0x000000D2,
	EV3_LB_MAIL_IEWR 	= 0x000000D4,
	EV3_LB_MAIL_IERD 	= 0x000000D6,
	EV3_MAIL_WR_STAT 	= 0x000000D8,
	EV3_MAIL_RD_STAT 	= 0x000000DA,
	EV3_QBA_MAP		= 0x000000DC,
	// System register bits
	EV3_SYSTEM_M_RST_OUT	= (1 << 15),
	EV3_SYSTEM_M_LOCK	= (1 << 14),
	// PCI COMMAND REGISTER bits
	EV3_COMMAND_M_FBB_EN	= (1 << 9),
	EV3_COMMAND_M_SERR_EN	= (1 << 8),
	EV3_COMMAND_M_PAR_EN	= (1 << 6),
	EV3_COMMAND_M_MASTER_EN = (1 << 2),
	EV3_COMMAND_M_MEM_EN	= (1 << 1),
	EV3_COMMAND_M_IO_EN	= (1 << 0),
	// PCI_CFG bits
	EV3_PCI_CFG_M_RETRY_EN	= (1 << 10),
	EV3_PCI_CFG_M_AD_LOW1	= (1 << 9),
	EV3_PCI_CFG_M_AD_LOW0	= (1 << 8),

	// PCI MAP register bits (PCI -> Local bus)
	EV3_PCI_MAP_M_MAP_ADR	= 0xFFF00000,
	EV3_PCI_MAP_M_RD_POST_INH = (1 << 15),
	EV3_PCI_MAP_M_ROM_SIZE	= (1 << 11) + (1 << 10),
	EV3_PCI_MAP_M_SWAP	= (1 << 9) + (1 << 8),
	EV3_PCI_MAP_M_ADR_SIZE	= 0x000000F0,
	EV3_PCI_MAP_M_REG_EN	= (1 << 1),
	EV3_PCI_MAP_M_ENABLE	= (1 << 0),

	// 9 => 512M window size
	EV3_PCI_MAP_M_ADR_SIZE_512M  = 0x00000090,
	// A => 1024M window size
	EV3_PCI_MAP_M_ADR_SIZE_1024M = 0x000000A0,

	// LB_BASE register bits (Local bus -> PCI)
	EV3_LB_BASE_M_MAP_ADR	= 0xFFF00000,
	EV3_LB_BASE_M_SWAP	= (1 << 9) + (1 << 8),
	EV3_LB_BASE_M_ADR_SIZE	= 0x000000F0,
	EV3_LB_BASE_M_PREFETCH	= (1 << 3),
	EV3_LB_BASE_M_ENABLE	= (1 << 0),

	// Header type
	EV3_PCI_HEADER_TYPE_MASK= 0x7f,
	EV3_PCI_HEADER_TYPE_MF  = 0x80
	};

public:
	IMPORT_C TPCICard();
	
	IMPORT_C void Init();

	IMPORT_C TUint32 MemoryBase() const;
	IMPORT_C TUint32 IOBase() const;

	IMPORT_C TBool PCIFindDevice( TUint16 vendor, TUint16 device, TUint32 *devid );
	IMPORT_C TBool PCIFindClass(TUint32 dev_class, TUint32 *devid );
	IMPORT_C TAny TPCICard::PCIGetDeviceInfo(TUint32 dev);
	IMPORT_C TBool PCIConfigureDevice();

	IMPORT_C TUint8 PCICfgRead8(TUint32 bus, TUint32 device, TUint32 function, TUint32 offset);
	IMPORT_C TUint16 PCICfgRead16(TUint32 bus, TUint16 device, TUint16 function, TUint16 offset);
	IMPORT_C TUint32 PCICfgRead32(TUint32 bus, TUint32 device, TUint32 function, TUint32 offset);

	IMPORT_C void PCICfgWrite8(TUint32 bus, TUint32 device, TUint32 function, 
				 TUint32 offset, TUint8 data);
	IMPORT_C void PCICfgWrite16(TUint32 bus, TUint32 device, TUint32 function, 
				  TUint32 offset, TUint16 data);
	IMPORT_C void PCICfgWrite32(TUint32 bus, TUint32 device, TUint32 function, 
				  TUint32 offset, TUint32 data);

	IMPORT_C TUint32 PCIRead32(TInt region, TUint32 addr);
	IMPORT_C TAny    PCIWrite8(TInt region, TUint32 addr, TUint8 value);
	IMPORT_C TAny    PCIWrite16(TInt region, TUint32 addr, TUint16 value);
	IMPORT_C TAny    PCIWrite32(TInt region, TUint32 addr, TUint32 value);
	IMPORT_C TAny    PCIReadFile(TInt region, TUint32 addr, TInt count, TUint8 *ucode);
	IMPORT_C TUint32 PCIRegionInfo(TInt region, TInt info);
	IMPORT_C TAny 	 PCISetRegionInfo(TInt region, TUint32 virt_addr);

	IMPORT_C TAny PCIDisplayCardInfo();
	IMPORT_C void PCIMemoryEnable();

protected:
	inline void _V3OpenConfigWindow(void);
	inline void _V3CloseConfigWindow(void);
	inline TUint32 PCIMakeConfigAddress(TUint32 bus, TUint32 device, 
					    TUint32 function, TUint32 offset);

	inline TUint8 PCIMapInterrupt( TUint32 bus, TUint32 devfn);

	TBool PCIFindNext( TUint32 devid, TUint32 *next_devid );
	TBool PCIAllocateMemoryPriv(TUint32 bar, TUint32 *assigned_addr);

	TBool PCIAllocateMemory(TUint32 bar);
	TBool PCIAllocateIoPriv(TUint32 bar, TUint32 *assigned_addr);
	TBool PCIAllocateIo(TUint32 bar);

	TAny PCITranslateInterrupt(TUint8 *vec );

private:
	// keep track of where we are in allocating space to the PCI cards
	TUint32 pciMemoryBase;
	TUint32 pciIoBase;

	DevInfo info;	
};

#endif
