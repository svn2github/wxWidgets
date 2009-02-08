///////////////////////////////////////////////////////////////////////////////
// Name:        wx/persist/window.h
// Purpose:     wxPersistentWindow declaration
// Author:      Vadim Zeitlin
// Created:     2009-01-23
// RCS-ID:      $Id$
// Copyright:   (c) 2009 Vadim Zeitlin <vadim@wxwidgets.org>
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#ifndef _WX_PERSIST_WINDOW_H_
#define _WX_PERSIST_WINDOW_H_

#include "wx/persist.h"

#include "wx/window.h"

// ----------------------------------------------------------------------------
// wxPersistentWindow: base class for persistent windows, uses the window name
//                     as persistent name by default and automatically reacts
//                     to the window destruction
// ----------------------------------------------------------------------------

// type-independent part of wxPersistentWindow
class wxPersistentWindowBase :
#if wxEVENTS_COMPATIBILITY_2_8
    // in compatibility mode we need to derive from wxEvtHandler to be able to
    // handle events
    public wxEvtHandler ,
#endif
    public wxPersistentObject
{
public:
    wxPersistentWindowBase(wxWindow *win)
        : wxPersistentObject(win)
    {
        win->Connect
             (
                wxEVT_DESTROY,
                wxWindowDestroyEventHandler(
                    wxPersistentWindowBase::HandleDestroy),
                NULL,
                this
             );
    }

    virtual wxString GetName() const
    {
        const wxString name = GetWindow()->GetName();
        wxASSERT_MSG( !name.empty(), "persistent windows should be named!" );

        return name;
    }

protected:
    wxWindow *GetWindow() const { return static_cast<wxWindow *>(GetObject()); }

private:
    void HandleDestroy(wxWindowDestroyEvent& event)
    {
        event.Skip();

        // this will delete this object itself
        wxPersistenceManager::Get().SaveAndUnregister(GetWindow());
    }

    wxDECLARE_NO_COPY_CLASS(wxPersistentWindowBase);
};

template <class T>
class wxPersistentWindow : public wxPersistentWindowBase
{
public:
    typedef T WindowType;

    wxPersistentWindow(WindowType *win)
        : wxPersistentWindowBase(win)
    {
    }

    WindowType *Get() const { return static_cast<WindowType *>(GetWindow()); }
};

#endif // _WX_PERSIST_WINDOW_H_

