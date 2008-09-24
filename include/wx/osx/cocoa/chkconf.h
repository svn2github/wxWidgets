/*
 * Name:        wx/osx/cocoa/chkconf.h
 * Purpose:     Compiler-specific configuration checking
 * Author:      Stefan Csomor
 * Modified by:
 * Created:     2008-07-30
 * RCS-ID:      $Id: chkconf.h 54833 2008-07-29 21:03:18Z SC $
 * Copyright:   (c) Stefan Csomor
 * Licence:     wxWindows licence
 */

#ifndef _WX_OSX_COCOA_CHKCONF_H_
#define _WX_OSX_COCOA_CHKCONF_H_

/*
 * native (1) or emulated (0) toolbar
 */

#ifndef wxOSX_USE_NATIVE_TOOLBAR
    #define wxOSX_USE_NATIVE_TOOLBAR 1
#endif

/* 
 * text rendering system 
 */

#if MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_5

    #define wxOSX_USE_CORE_TEXT 1
    #define wxOSX_USE_ATSU_TEXT 0

#else // platform < 10.5

    #if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
        #define wxOSX_USE_CORE_TEXT 1
    #else
        #define wxOSX_USE_CORE_TEXT 0
    #endif
    #define wxOSX_USE_ATSU_TEXT 1

#endif

/*
 * turning off capabilities that don't work under cocoa yet
 */

#if wxUSE_DATAVIEWCTRL
#undef wxUSE_DATAVIEWCTRL
#define wxUSE_DATAVIEWCTRL 0
#endif

#endif
    /* _WX_MAC_CHKCONF_H_ */

