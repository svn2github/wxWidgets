/////////////////////////////////////////////////////////////////////////////
// Name:        timer.cpp
// Purpose:     wxTimer implementation
// Author:      David Webster
// Modified by:
// Created:     10/17/99
// RCS-ID:      $Id$
// Copyright:   (c) David Webster
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#include "wx/window.h"
#include "wx/os2/private.h"

#ifndef WX_PRECOMP
    #include "wx/setup.h"
    #include "wx/list.h"
    #include "wx/event.h"
    #include "wx/app.h"
#endif

#include "wx/intl.h"
#include "wx/log.h"

#include "wx/timer.h"

#include <time.h>
#include <sys/types.h>

#include <sys/timeb.h>
// ----------------------------------------------------------------------------
// private functions
// ----------------------------------------------------------------------------

wxList wxTimerList(wxKEY_INTEGER);
ULONG wxTimerProc(HWND hwnd, ULONG, int nIdTimer, ULONG);

// ----------------------------------------------------------------------------
// macros
// ----------------------------------------------------------------------------

IMPLEMENT_ABSTRACT_CLASS(wxTimer, wxObject)

void wxTimer::Init()
{
    m_ulId = 0;
}

wxTimer::~wxTimer()
{
    Stop();
    wxTimer::Stop();
    wxTimerList.DeleteObject(this);
}

void wxTimer::Notify()
{
    //
    // The base class version generates an event if it has owner - which it
    // should because otherwise nobody can process timer events, but it does
    // not use the OS's ID, which OS/2 must have to figure out which timer fired
    //
    wxCHECK_RET( m_owner, _T("wxTimer::Notify() should be overridden.") );

    wxTimerEvent                    vEvent( m_ulId
                                           ,m_milli
                                          );

    (void)m_owner->ProcessEvent(vEvent);
} // end of wxTimer::Notify

bool wxTimer::Start(
  int                               nMilliseconds
, bool                              bOneShot
)
{
    (void)wxTimerBase::Start( nMilliseconds
                             ,bOneShot
                            );

    wxCHECK_MSG( m_milli > 0L, FALSE, wxT("invalid value for timer") );

    wxTimerList.DeleteObject(this);

    //
    // Create a windowless timer
    //
    m_ulId = ::WinStartTimer( m_Hab
                             ,NULLHANDLE
                             ,0
                             ,(ULONG)nMilliseconds
                            );
    if (m_ulId > 0L)
    {
        wxTimerList.Append( m_ulId
                           ,this
                          );
        return(TRUE);
    }
    else
    {
        wxLogSysError(_("Couldn't create a timer"));

        return(FALSE);
    }
}

void wxTimer::Stop()
{
    if ( m_ulId )
    {
        ::WinStopTimer(m_Hab, NULL, m_ulId);
        wxTimerList.DeleteObject(this);
    }
}

// ----------------------------------------------------------------------------
// private functions
// ----------------------------------------------------------------------------

void wxProcessTimer(
  wxTimer&                          rTimer
)
{
    //
    // Avoid to process spurious timer events
    //
    if (rTimer.m_ulId == 0L)
        return;

    if (rTimer.IsOneShot())
        rTimer.Stop();

    rTimer.Notify();
}

ULONG wxTimerProc(
  HWND                              WXUNUSED(hwnd)
, ULONG
, int                               nIdTimer
, ULONG
)
{
    wxNode*                         pNode = wxTimerList.Find((ULONG)nIdTimer);

    wxCHECK_MSG(pNode, 0, wxT("bogus timer id in wxTimerProc") );

    wxProcessTimer(*(wxTimer *)pNode->Data());
    return 0;
}

