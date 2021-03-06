/*----------------------------------------------------------------------------
| File        : xlCANFunctions.cpp
| Project     : Vector CAN Example 
|
| Description : Shows the basic CAN functionality for the XL Driver Library
|-----------------------------------------------------------------------------
| $Author: J�rg $    $Locker: $   $Revision: 11 $
| $Header: /VCANDRV/XLAPI/samples/xlCANcontrol/xlCANFunctions.cpp 11    14.11.05 10:59 J�rg $
|-----------------------------------------------------------------------------
| Copyright (c) 2004 by Vector Informatik GmbH.  All rights reserved.
|---------------------------------------------------------------------------*/

//#include "stdafx.h"
//#include "xlCANcontrol.h"
#include "xlCANFunctions.h"
//#include "debug.h"
/*
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
*/
//////////////////////////////////////////////////////////////////////
// globals
//////////////////////////////////////////////////////////////////////

TStruct g_th0, g_th1;
BOOL    g_bThreadRun;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCANFunctions::CCANFunctions()
{
  m_xlChannelMask[CHAN01] = 0;
  m_xlChannelMask[CHAN02] = 0;
  Steering_Angle = 0;
  Speed = 0;
  m_xlPortHandle0= XL_INVALID_PORTHANDLE;
}

CCANFunctions::~CCANFunctions()
{
  if (m_xlPortHandle0!= XL_INVALID_PORTHANDLE) {
   CloseHandle(m_hThread0);
   CloseHandle(m_hThread1);
//   CloseHandle(m_hMsgEvent0);
//   CloseHandle(m_hMsgEvent1);

   }
}

////////////////////////////////////////////////////////////////////////////

//! CANInit

//! Open the driver, get the channelmasks and create the RX thread.
//! 
//!
//////////////////////////////////////////////////////////////////////////// 

XLstatus CCANFunctions::CANInit()
{
  XLstatus        xlStatus = XL_ERROR;
  char            tmp[100];

  xlStatus = xlOpenDriver();
 // sprintf(tmp, "xlOpenDriver, stat: %d", xlStatus);
 // DEBUG(DEBUG_ADV, tmp);
  if (xlStatus != XL_SUCCESS) return xlStatus;

  // ---------------------------------------
  // Get/Set the application within VHWConf
  // ---------------------------------------
  xlStatus = canGetChannelMask();
 // if ( (xlStatus) || (m_xlChannelMask[CHAN01] == 0) || (m_xlChannelMask[CHAN02] == 0) ) return XL_ERROR;

  // ---------------------------------------
  // Open ONE port for EACH channel (2 channels)
  // ---------------------------------------
  xlStatus = canInit();
  if (xlStatus) return xlStatus;

  // ---------------------------------------
  // Create ONE thread for each channel (2 threads)
  // ---------------------------------------
  xlStatus = canCreateRxThread();
  if (xlStatus) return xlStatus;

  return xlStatus;
}

////////////////////////////////////////////////////////////////////////////

//! canGetChannelMask

//! parse the registry to get the channelmask
//!
//////////////////////////////////////////////////////////////////////////// 

XLstatus CCANFunctions::canGetChannelMask()
{
 /* XLstatus        xlStatus = XL_ERROR;
  char            tmp[100];

  // default values
  unsigned int  hwType     = 0;
  unsigned int  hwIndex    = 0;
  unsigned int  hwChannel  = 0;
  unsigned int  appChannel = 0;
  unsigned int  busType    = XL_BUS_TYPE_CAN;   
  unsigned int  i; 

  XLdriverConfig  xlDrvConfig;

   //check for hardware:
  xlStatus = xlGetDriverConfig(&xlDrvConfig);
  if (xlStatus) return xlStatus;
  
  // we check only if there is an application registered or not.
  xlStatus = xlGetApplConfig("xlCANcontrol", CHAN01, &hwType, &hwIndex, &hwChannel, busType); 
 
  // Set the params into registry (default values...!)
  if (xlStatus) {
    DEBUG(DEBUG_ADV,"set in VHWConf");

    for (i=0; i < xlDrvConfig.channelCount; i++) {

      sprintf (tmp, "hwType: %d, bustype: %d, hwChannel: %d, cap: 0x%x", 
        xlDrvConfig.channel[i].hwType, 
        xlDrvConfig.channel[i].connectedBusType,
        xlDrvConfig.channel[i].hwChannel,
        xlDrvConfig.channel[i].channelBusCapabilities);
      DEBUG(DEBUG_ADV,tmp);

      // we search not the first CAN cabs
      if ( (xlDrvConfig.channel[i].channelBusCapabilities & XL_BUS_ACTIVE_CAP_CAN) && (appChannel < 2) ) {

        hwType    = xlDrvConfig.channel[i].hwType;
        hwIndex   = xlDrvConfig.channel[i].hwIndex;
        hwChannel = xlDrvConfig.channel[i].hwChannel;

        xlStatus = xlSetApplConfig( // Registration of Application with default settings
        "xlCANcontrol",             // Application Name
        appChannel,                 // Application channel 0 or 1
        hwType,                     // hwType  (CANcardXL...)    
        hwIndex,                    // Index of hardware (slot) (0,1,...)
        hwChannel,                  // Index of channel (connector) (0,1,...)
        busType);                   // the application is for CAN.

        m_xlChannelMask[appChannel] = xlGetChannelMask(hwType, hwIndex, hwChannel);
        sprintf (tmp, "Register CAN hWType: %d, CM: 0x%I64x", hwType, m_xlChannelMask[appChannel]);
        DEBUG(DEBUG_ADV,tmp);

        m_pHardware->InsertString(-1, xlDrvConfig.channel[i].name);

        appChannel++;
      }

    }
  }
  else {

    m_xlChannelMask[CHAN01] = xlGetChannelMask(hwType, hwIndex, hwChannel);
    sprintf (tmp, "Found CAN in VHWConf, hWType: %d, CM: 0x%I64x", hwType, m_xlChannelMask[CHAN01]);
    DEBUG(DEBUG_ADV,tmp);
 
    for (i=0; i < xlDrvConfig.channelCount; i++) {

      if ( xlDrvConfig.channel[i].channelMask == m_xlChannelMask[CHAN01])
        m_pHardware->AddString(xlDrvConfig.channel[i].name);
    }

    // get the second channel
    xlStatus = xlGetApplConfig("xlCANcontrol", CHAN02, &hwType, &hwIndex, &hwChannel, busType); 
    if (xlStatus) return xlStatus;

    m_xlChannelMask[CHAN02] = xlGetChannelMask(hwType, hwIndex, hwChannel);
    sprintf (tmp, "Found CAN in VHWConf, hWType: %d, CM: 0x%I64x", hwType, m_xlChannelMask[CHAN02]);
    DEBUG(DEBUG_ADV,tmp);

    for (i=0; i < xlDrvConfig.channelCount; i++) {

      if ( xlDrvConfig.channel[i].channelMask == m_xlChannelMask[CHAN02])
        m_pHardware->AddString(xlDrvConfig.channel[i].name);
    }
 
  }   

  return xlStatus;
  */

  unsigned int  hwType     = -1;
  unsigned int  hwIndex    = -1;
  unsigned int  hwChannel  = 0;

  m_xlChannelMask[0] = xlGetChannelMask(hwType, hwIndex, hwChannel);
  hwChannel  = 1;
  m_xlChannelMask[1] = xlGetChannelMask(hwType, hwIndex, hwChannel);

  XLstatus xlStatus = XL_SUCCESS;
  return xlStatus;
}

////////////////////////////////////////////////////////////////////////////

//! canInit

//! xlCANcontrol use ONE port for both channels.
//!
//////////////////////////////////////////////////////////////////////////// 

XLstatus CCANFunctions::canInit()
{
  XLstatus         xlStatus = XL_ERROR;
  XLaccess         xlPermissionMask0, xlPermissionMask1;
  char             tmp[100];

  // ---------------------------------------
  // Open ONE port for each channel
  // ---------------------------------------

  // calculate the channelMask for both channel
  m_xlChannelMask0 = m_xlChannelMask[0];
  m_xlChannelMask1 = m_xlChannelMask[1];
  xlPermissionMask0 = m_xlChannelMask0;
  xlPermissionMask1 = m_xlChannelMask1;

  xlStatus = xlOpenPort(&m_xlPortHandle0, "UPM", m_xlChannelMask0, &xlPermissionMask0, 256, XL_INTERFACE_VERSION, XL_BUS_TYPE_CAN);
  xlStatus = xlOpenPort(&m_xlPortHandle1, "UPM", m_xlChannelMask1, &xlPermissionMask1, 256, XL_INTERFACE_VERSION, XL_BUS_TYPE_CAN);
 // sprintf(tmp, "xlOpenPort: PortHandle: %d; Permissionmask: 0x%I64x; Status: %d", m_xlPortHandle, xlPermissionMask, xlStatus);
  //DEBUG(DEBUG_ADV, tmp);

 // if (m_xlPortHandle == XL_INVALID_PORTHANDLE) return XL_ERROR;
 // if (xlStatus == XL_ERR_INVALID_ACCESS) return xlStatus;

  return xlStatus;
}

////////////////////////////////////////////////////////////////////////////

//! canCreateRxThread

//! set the notification and creates the thread.
//!
////////////////////////////////////////////////////////////////////////////

XLstatus CCANFunctions::canCreateRxThread()
{
  
  XLstatus      xlStatus = XL_ERROR;
  DWORD         ThreadId=0;
  char          tmp[100];

  if (m_xlPortHandle0!= XL_INVALID_PORTHANDLE) {

    // Send a event for each Msg!!!
    xlStatus = xlSetNotification (m_xlPortHandle0, &m_hMsgEvent0, 1);
    xlStatus = xlSetNotification (m_xlPortHandle1, &m_hMsgEvent1, 1);

    //sprintf(tmp, "SetNotification '%d', xlStatus: %d", m_hMsgEvent, xlStatus);
    //DEBUG(DEBUG_ADV, tmp);

    // for the RxThread
    g_th0.xlPortHandle = m_xlPortHandle0;
    g_th0.hMsgEvent    = m_hMsgEvent0;
    g_th0.Result = &Steering_Angle;
    g_th1.xlPortHandle = m_xlPortHandle1;
    g_th1.hMsgEvent    = m_hMsgEvent1;
    g_th1.Result = &Speed;
    g_th1.Throttle = &Throttle;
    g_th1.Brake = &Brake;



    m_hThread0 = CreateThread(0, 0x1000, RxThread0, (LPVOID) &g_th0, 0, &ThreadId);
    m_hThread1 = CreateThread(0, 0x1000, RxThread1, (LPVOID) &g_th1, 0, &ThreadId);

    
  }
  return xlStatus;
}


////////////////////////////////////////////////////////////////////////////

//! CANGoOnBus

//! set the selected baudrate and go on bus.
//!
////////////////////////////////////////////////////////////////////////////

XLstatus CCANFunctions::CANGoOnBus(unsigned long baudrate0, unsigned long baudrate1)
{
  XLstatus      xlStatus = XL_ERROR;
  char          tmp[100];


  //Set channel bit rate
  xlStatus = xlCanSetChannelBitrate(m_xlPortHandle0, m_xlChannelMask0, baudrate0);
  xlStatus = xlCanSetChannelBitrate(m_xlPortHandle1, m_xlChannelMask1, baudrate1);

  //set output mode to silent mode (no ACK sending) --> (XL_OUTPUT_MODE_SILENT, XL_OUTPUT_MODE_NORMAL)
  xlStatus = xlCanSetChannelOutput (m_xlPortHandle0, m_xlChannelMask0, XL_OUTPUT_MODE_NORMAL);
  xlStatus = xlCanSetChannelOutput (m_xlPortHandle1, m_xlChannelMask1, XL_OUTPUT_MODE_SILENT);

  //Flush receive queue
  xlStatus = xlFlushReceiveQueue (m_xlPortHandle0);
  xlStatus = xlFlushReceiveQueue (m_xlPortHandle1);

  //Activate each channel
  xlStatus = xlActivateChannel(m_xlPortHandle0, m_xlChannelMask0, XL_BUS_TYPE_CAN, XL_ACTIVATE_RESET_CLOCK);
  xlStatus = xlActivateChannel(m_xlPortHandle1, m_xlChannelMask1, XL_BUS_TYPE_CAN, XL_ACTIVATE_RESET_CLOCK);


  return xlStatus;
}

////////////////////////////////////////////////////////////////////////////

//! CANGoOffBus

//! Deactivate the channel
//!
////////////////////////////////////////////////////////////////////////////

XLstatus CCANFunctions::CANGoOffBus()
{
  XLstatus      xlStatus = XL_ERROR;
  char          tmp[100];

  //End the reception threads
  g_bThreadRun = false;

  xlStatus = xlDeactivateChannel(m_xlPortHandle0, m_xlChannelMask0);
  xlStatus = xlDeactivateChannel(m_xlPortHandle1, m_xlChannelMask1);
  xlStatus = xlClosePort (m_xlPortHandle0);
  xlStatus = xlClosePort (m_xlPortHandle1);
  xlStatus = xlCloseDriver();

  return xlStatus;
}

////////////////////////////////////////////////////////////////////////////

//! CANSend

//! transmit a CAN message to the selected channel with the give values.
//!
////////////////////////////////////////////////////////////////////////////

XLstatus CCANFunctions::CANSend(XLevent xlEvent, int channel)
{
  
  XLstatus      xlStatus;
  char          tmp[100];
  unsigned int  messageCount = 1;

  if (channel == 0)
    xlStatus = xlCanTransmit(m_xlPortHandle0, m_xlChannelMask[channel], &messageCount, &xlEvent);
  else
    xlStatus = xlCanTransmit(m_xlPortHandle1, m_xlChannelMask[channel], &messageCount, &xlEvent);

  return xlStatus;
}

////////////////////////////////////////////////////////////////////////////

//! CANResetFilter

//! Reset the acceptance filter
//distinguish whether the filter is reset for standard or extended identifiers.
//  - XL_CAN_STD Opens the filter for standard message IDs
//  - XL_CAN_EXT Opens the filter for extended message IDs
//!
////////////////////////////////////////////////////////////////////////////

XLstatus CCANFunctions::CANResetFilter()
{
  XLstatus      xlStatus;
  char          tmp[100];

  xlStatus = xlCanResetAcceptance(m_xlPortHandle0, m_xlChannelMask0, XL_CAN_STD);
  xlStatus = xlCanResetAcceptance(m_xlPortHandle1, m_xlChannelMask1, XL_CAN_STD);


  return xlStatus;
}

////////////////////////////////////////////////////////////////////////////

//! CANSetFilter

//! Configure the acceptance filter
//!
// Accept if ((id ^ code) & mask) == 0)

//Set acceptance filter for several IDs (formula)
//    code = id(1)
//    mask = 0XFFF
//    loop over id(1) ... id(n)
//      mask = (!(id(n)&mask)xor(code&mask))& mask
////////////////////////////////////////////////////////////////////////////

XLstatus CCANFunctions::CANSetFilter(unsigned long first_id, unsigned long last_id)
{
  XLstatus      xlStatus;
  char          tmp[100];
  
  // because there all filters open, we close all.                       //code //mask
  xlStatus = xlCanSetChannelAcceptance(m_xlPortHandle0, m_xlChannelMask0, 0x000, 0x000, XL_CAN_STD);
  xlStatus = xlCanSetChannelAcceptance(m_xlPortHandle1, m_xlChannelMask1, 0x000, 0x000, XL_CAN_STD);

  
  // and now we can set the acceptance filter range.
  //xlStatus = xlCanAddAcceptanceRange(m_xlPortHandle, m_xlChannelMask_both, first_id, last_id);

  
  
  return xlStatus;
}

///////////////////////////////////////////////////////////////////////////

//! RxThread0

//! thread to readout the message queue and parse the incoming messages in channel 0
//!
////////////////////////////////////////////////////////////////////////////

DWORD WINAPI RxThread0(LPVOID par)
{

  XLstatus        xlStatus;

  unsigned int    msgsrx = 1;
  XLevent         xlEvent;
  char            tmp[110];


  g_bThreadRun = TRUE;

  TStruct *g_th;

  g_th = (TStruct*) par;  
  int angle;
  double Steering_Angle;
  unsigned char d0, d1;

  while (g_bThreadRun) {
   
    WaitForSingleObject(g_th->hMsgEvent,10);
    
    xlStatus = XL_SUCCESS;
   
    while (!xlStatus) {
        
	  msgsrx = 1;
      xlStatus = xlReceive(g_th->xlPortHandle, &msgsrx, &xlEvent);	
		
    if ( xlStatus!=XL_ERR_QUEUE_IS_EMPTY ) {
      if (xlEvent.tagData.msg.id == 0x305){
        d0 = xlEvent.tagData.msg.data[0];
        d1 = xlEvent.tagData.msg.data[1];
        angle = d0*256+d1;
      if (angle>7200)
        angle -= 65535;
      Steering_Angle=((angle*0.1)*360/277.5)-35.0;
      //offset porque el sensor se ha soltado +35�
      *g_th->Result=Steering_Angle;
      }
    }
    }//while

  }
  return NO_ERROR;
}

///////////////////////////////////////////////////////////////////////////

//! RxThread1

//! thread to readout the message queue and parse the incoming messages in channel 1
//!
////////////////////////////////////////////////////////////////////////////

DWORD WINAPI RxThread1(LPVOID par)
{

  XLstatus        xlStatus;

  unsigned int    msgsrx = 1;
  XLevent         xlEvent;
  char            tmp[110];


  g_bThreadRun = TRUE;

  TStruct *g_th;

  g_th = (TStruct*) par;
  int speed;
  double Speed;
  int throttle;
  double Throttle;
  int brake;
  unsigned char d0, d1;

  while (g_bThreadRun) {

    WaitForSingleObject(g_th->hMsgEvent,10);

    xlStatus = XL_SUCCESS;

    while (!xlStatus) {

	  msgsrx = 1;
      xlStatus = xlReceive(g_th->xlPortHandle, &msgsrx, &xlEvent);

    if ( xlStatus!=XL_ERR_QUEUE_IS_EMPTY ) {

      //Speed
      if (xlEvent.tagData.msg.id == 0x38D){
        d0 = xlEvent.tagData.msg.data[0];
        d1 = xlEvent.tagData.msg.data[1];
        speed = d0*256+d1;
        Speed = speed*0.01;
       *g_th->Result=Speed;
        }

       //throttle
       if (xlEvent.tagData.msg.id == 0x208){ //Byte 3
        d0 = xlEvent.tagData.msg.data[3];
        throttle = d0;
        Throttle = throttle*0.5;
        *g_th->Throttle = Throttle;
       }

       //brake
       if (xlEvent.tagData.msg.id == 0x208){ //Byte 4, bit 1
        d0 = xlEvent.tagData.msg.data[4];
        brake = d0 & 0x2;
        *g_th->Brake = brake;
       }
     }

    }//while
          
  }
  return NO_ERROR;
}
