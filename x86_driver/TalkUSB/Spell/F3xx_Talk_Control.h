//-----------------------------------------------------------------------------
// F3xx_Blink_Control.h
//-----------------------------------------------------------------------------
// Copyright 2005 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// This file includes all of the Report IDs and variables needed by
// USB_ReportHandler.c to process input and output reports,
// as well as initialization routine prototypes.
//
//
// How To Test:    See Readme.txt
//
//
// FID:            3XX000010
// Target:         C8051F3xx
// Tool chain:     Keil C51 7.50 / Keil EVAL C51
//                 Silicon Laboratories IDE version 2.6
// Command Line:   See Readme.txt
// Project Name:   F3xx_BlinkyExample
//
// Release 1.1
//    -Added feature reports for dimming controls
//    -Added PCA dimmer functionality
//    -16 NOV 2006
// Release 1.0
//    -Initial Revision (PD)
//    -07 DEC 2005
//

#ifndef  _TALK_C_H_
#define  _TALK_C_H_

//extern unsigned char xdata TALK_ENABLE;
extern unsigned char xdata TALK_STATE;

extern unsigned char xdata OUT_PACKET[];
extern unsigned char xdata IN_PACKET[];

void System_Init(void);
void Usb_Init(void);


// ----------------------------------------------------------------------------
// Report IDs
// ----------------------------------------------------------------------------
#define OUT_TALK_ENABLEID      0x01
#define IN_TALK_STATSID        0x02

// ----------------------------------------------------------------------------
// Report Sizes (in bytes)
// ----------------------------------------------------------------------------
#define OUT_TALK_ENABLESize     0x01
#define IN_TALK_STATSSIZE       0x01
//#define FEATURE_BLINK_DIMMERSIZE 0x01

#endif