/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/toplevel.h
// Purpose:
// Author:      Robert Roebling
// Id:          $Id$
// Copyright:   (c) 1998 Robert Roebling, Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_GTK_TOPLEVEL_H_
#define _WX_GTK_TOPLEVEL_H_

//-----------------------------------------------------------------------------
// wxTopLevelWindowGTK
//-----------------------------------------------------------------------------

class WXDLLIMPEXP_CORE wxTopLevelWindowGTK : public wxTopLevelWindowBase
{
public:
    // construction
    wxTopLevelWindowGTK() { Init(); }
    wxTopLevelWindowGTK(wxWindow *parent,
                        wxWindowID id,
                        const wxString& title,
                        const wxPoint& pos = wxDefaultPosition,
                        const wxSize& size = wxDefaultSize,
                        long style = wxDEFAULT_FRAME_STYLE,
                        const wxString& name = wxFrameNameStr)
    {
        Init();

        Create(parent, id, title, pos, size, style, name);
    }

    bool Create(wxWindow *parent,
                wxWindowID id,
                const wxString& title,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = wxDEFAULT_FRAME_STYLE,
                const wxString& name = wxFrameNameStr);

    virtual ~wxTopLevelWindowGTK();

    // implement base class pure virtuals
    virtual void Maximize(bool maximize = true);
    virtual bool IsMaximized() const;
    virtual void Iconize(bool iconize = true);
    virtual bool IsIconized() const;
    virtual void SetIcons(const wxIconBundle& icons);
    virtual void Restore();

    virtual bool EnableCloseButton(bool enable = true);

    virtual bool ShowFullScreen(bool show, long style = wxFULLSCREEN_ALL);
    virtual bool IsFullScreen() const { return m_fsIsShowing; };

    virtual bool SetShape(const wxRegion& region);

    virtual void RequestUserAttention(int flags = wxUSER_ATTENTION_INFO);

    virtual void SetWindowStyleFlag( long style );

    virtual bool Show(bool show = true);

    virtual void Raise();

    virtual bool IsActive();

    virtual void SetTitle( const wxString &title );
    virtual wxString GetTitle() const { return m_title; }

    virtual bool SetTransparent(wxByte alpha);
    virtual bool CanSetTransparent();

    // Experimental, to allow help windows to be
    // viewable from within modal dialogs
    virtual void AddGrab();
    virtual void RemoveGrab();
    virtual bool IsGrabbed() const { return m_grabbed; }

    // implementation from now on
    // --------------------------

    // GTK callbacks
    virtual void OnInternalIdle();

    // do *not* call this to iconize the frame, this is a private function!
    void SetIconizeState(bool iconic);

    GtkWidget    *m_mainWidget;

    bool          m_fsIsShowing;         /* full screen */
    int           m_fsSaveGdkFunc, m_fsSaveGdkDecor;
    wxRect        m_fsSaveFrame;

    // m_windowStyle translated to GDK's terms
    int           m_gdkFunc,
                  m_gdkDecor;

    // private gtk_timeout_add result for mimicing wxUSER_ATTENTION_INFO and
    // wxUSER_ATTENTION_ERROR difference, -2 for no hint, -1 for ERROR hint, rest for GtkTimeout handle.
    int m_urgency_hint;

    // give hints to the Window Manager for how the size
    // of the TLW can be changed by dragging
    virtual void DoSetSizeHints( int minW, int minH,
                                 int maxW = wxDefaultCoord, int maxH = wxDefaultCoord,
                                 int incW = wxDefaultCoord, int incH = wxDefaultCoord );

    // return the size of the window without WM decorations
    void GTKDoGetSize(int *width, int *height) const;

    // whether frame extents are accurate
    virtual bool IsDecorCacheable() const;

protected:
    // common part of all ctors
    void Init();

    // move the window to the specified location and resize it
    virtual void DoMoveWindow(int x, int y, int width, int height);

    // take into account WM decorations here
    virtual void DoSetSize(int x, int y,
                           int width, int height,
                           int sizeFlags = wxSIZE_AUTO);

    // override these methods to take into account tool/menu/statusbars
    virtual void DoGetClientSize(int *width, int *height) const;

    // string shown in the title bar
    wxString m_title;

private:
    // is the frame currently iconized?
    bool m_isIconized;

    // is the frame currently grabbed explicitly by the application?
    bool m_grabbed;
};

#endif // _WX_GTK_TOPLEVEL_H_
