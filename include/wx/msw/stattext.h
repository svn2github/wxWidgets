/////////////////////////////////////////////////////////////////////////////
// Name:        stattext.h
// Purpose:     wxStaticText class
// Author:      Julian Smart
// Modified by:
// Created:     01/02/97
// RCS-ID:      $Id$
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_STATTEXT_H_
#define _WX_STATTEXT_H_

#ifdef __GNUG__
    #pragma interface "stattext.h"
#endif

#include "wx/control.h"

WXDLLEXPORT_DATA(extern const wxChar*) wxStaticTextNameStr;

class WXDLLEXPORT wxStaticText : public wxControl
{
DECLARE_DYNAMIC_CLASS(wxStaticText)

public:
    wxStaticText() { }

    wxStaticText(wxWindow *parent,
                 wxWindowID id,
                 const wxString& label,
                 const wxPoint& pos = wxDefaultPosition,
                 const wxSize& size = wxDefaultSize,
                 long style = 0,
                 const wxString& name = wxStaticTextNameStr)
    {
        Create(parent, id, label, pos, size, style, name);
    }

    bool Create(wxWindow *parent,
                wxWindowID id,
                const wxString& label,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = 0,
                const wxString& name = wxStaticTextNameStr);

    // accessors
    void SetLabel(const wxString& label);
    bool SetFont( const wxFont &font );

    // overriden base class virtuals
    virtual bool AcceptsFocus() const { return FALSE; }

    // callbacks
    virtual long MSWWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam);

protected:
    virtual wxSize DoGetBestSize() const;
};

#endif
    // _WX_STATTEXT_H_
