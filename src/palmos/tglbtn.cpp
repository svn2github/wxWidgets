/////////////////////////////////////////////////////////////////////////////
// Name:        src/palmos/tglbtn.cpp
// Purpose:     Definition of the wxToggleButton class, which implements a
//              toggle button.
// Author:      William Osborne - minimal working wxPalmOS port
// Modified by:
// Created:     10/13/04
// RCS-ID:      $Id$
// Copyright:   (c) William Osborne
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declatations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "wx/tglbtn.h"

#if wxUSE_TOGGLEBTN

#ifndef WX_PRECOMP
    #include "wx/button.h"
    #include "wx/brush.h"
    #include "wx/dcscreen.h"
    #include "wx/settings.h"

    #include "wx/log.h"
#endif // WX_PRECOMP

#include "wx/palmos/private.h"

// ----------------------------------------------------------------------------
// macros
// ----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC_CLASS(wxToggleButton, wxControl)
DEFINE_EVENT_TYPE(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED)

#define BUTTON_HEIGHT_FROM_CHAR_HEIGHT(cy) (11*EDIT_HEIGHT_FROM_CHAR_HEIGHT(cy)/10)

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// wxToggleButton
// ----------------------------------------------------------------------------

bool wxToggleButton::MSWCommand(WXUINT WXUNUSED(param), WXWORD WXUNUSED(id))
{
   wxCommandEvent event(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, m_windowId);
   event.SetInt(GetValue());
   event.SetEventObject(this);
   ProcessCommand(event);
   return TRUE;
}

// Single check box item
bool wxToggleButton::Create(wxWindow *parent, wxWindowID id,
                            const wxString& label,
                            const wxPoint& pos,
                            const wxSize& size, long style,
                            const wxValidator& validator,
                            const wxString& name)
{
    return false;
}

wxBorder wxToggleButton::GetDefaultBorder() const
{
    return wxBORDER_NONE;
}

WXDWORD wxToggleButton::MSWGetStyle(long style, WXDWORD *exstyle) const
{
    return 0;
}

void wxToggleButton::SetLabel(const wxString& label)
{
}

wxSize wxToggleButton::DoGetBestSize() const
{
   return wxSize(0,0);
}

void wxToggleButton::SetValue(bool val)
{
}

#ifndef BST_CHECKED
#define BST_CHECKED 0x0001
#endif

bool wxToggleButton::GetValue() const
{
    return false;
}

void wxToggleButton::Command(wxCommandEvent & event)
{
}

#endif // wxUSE_TOGGLEBTN

