/////////////////////////////////////////////////////////////////////////////
// PCQNG_IOCTL.h
// User-mode interface header to PCQNG.QNG driver.
//
//      Copyright © 2001 The Quantum World Corporation. All rights reserved
//
// History:
// 6Aug2001		Release Candidate 1					PAW
//
// Include this header in Win32 applications after WINIOCTL.H
//


#ifndef PCQNG_IOCTL_H
#define PCQNG_IOCTL_H

#define IOCTL_READ \
   CTL_CODE(FILE_DEVICE_UNKNOWN,0x801,METHOD_BUFFERED,FILE_ANY_ACCESS)

#define IOCTL_START_BURST \
   CTL_CODE(FILE_DEVICE_UNKNOWN,0x806,METHOD_BUFFERED,FILE_ANY_ACCESS)

#define IOCTL_SET_MODE \
   CTL_CODE(FILE_DEVICE_UNKNOWN,0x811,METHOD_BUFFERED,FILE_ANY_ACCESS)

#define IOCTL_GET_MODE \
   CTL_CODE(FILE_DEVICE_UNKNOWN,0x812,METHOD_BUFFERED,FILE_ANY_ACCESS)

#endif // ifndef PCQNG_IOCTL_H
