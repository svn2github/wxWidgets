/////////////////////////////////////////////////////////////////////////////
// Name:        src/mgl/window.cpp
// Purpose:     wxWindow
// Author:      Vaclav Slavik
//              (based on GTK & MSW implementations)
// RCS-ID:      $Id$
// Copyright:   (c) 2001 SciTech Software, Inc. (www.scitechsoft.com)
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// ===========================================================================
// declarations
// ===========================================================================

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#ifdef __GNUG__
    #pragma implementation "window.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/window.h"
    #include "wx/accel.h"
    #include "wx/setup.h"
    #include "wx/dc.h"
    #include "wx/dcclient.h"
    #include "wx/utils.h"
    #include "wx/app.h"
    #include "wx/panel.h"
    #include "wx/caret.h"
#endif

#if wxUSE_DRAG_AND_DROP
    #include "wx/dnd.h"
#endif

#include "wx/log.h"
#include "wx/sysopt.h"
#include "wx/mgl/private.h"
#include "wx/intl.h"
#include "wx/dcscreen.h"

#include <mgraph.hpp>

#if wxUSE_TOOLTIPS
    #include "wx/tooltip.h"
#endif

// ---------------------------------------------------------------------------
// global variables
// ---------------------------------------------------------------------------

// MGL window manager and associated DC.
winmng_t *g_winMng = NULL;
MGLDevCtx *g_displayDC = NULL;

extern wxList WXDLLEXPORT wxPendingDelete;
 // FIXME_MGL -- ???
 
static wxWindowMGL *g_focusedWindow;

// ---------------------------------------------------------------------------
// constants
// ---------------------------------------------------------------------------

// Custom identifiers used to distinguish between various event handlers 
// and capture handlers passed to MGL_wm
enum
{
    wxMGL_CAPTURE_MOUSE = 1,
    wxMGL_CAPTURE_KEYB  = 2
};


// ---------------------------------------------------------------------------
// private functions
// ---------------------------------------------------------------------------

static void wxWindowPainter(window_t *wnd, MGLDC *dc);

// wxCreateMGL_WM creates MGL display DC and associates it with winmng_t
// structure. Dimensions and depth of the DC are fetched from wxSystemOptions
// object. 
// This function is *not* called from wxApp's initialization but rather at
// the time when WM is needed, i.e. when first wxWindow is created. This 
// has two important effects:
//   a) it is possible to write windowless wxMGL apps
//   b) the app has plenty of time in wxApp::OnInit to feed wxSystemOptions
//      with desired settings

bool wxCreateMGL_WM()
{
    int mode;
    int width = 640, height = 480, depth = 16;
    int refresh = MGL_DEFAULT_REFRESH;
    
#if wxUSE_SYSTEM_OPTIONS
    if ( wxSystemOptions::HasOption(wxT("mgl.screen-width") )
        width = wxSystemOptions::GetOptionInt(wxT("mgl.screen-width"));
    if ( wxSystemOptions::HasOption(wxT("mgl.screen-height") )
        height = wxSystemOptions::GetOptionInt(wxT("mgl.screen-height"));
    if ( wxSystemOptions::HasOption(wxT("mgl.screen-depth") )
        depth = wxSystemOptions::GetOptionInt(wxT("mgl.screen-depth"));
    if ( wxSystemOptions::HasOption(wxT("mgl.screen-refresh") )
        refresh = wxSystemOptions::GetOptionInt(wxT("mgl.screen-refresh"));
#endif
        
    mode = MGL_findMode(width, height, depth);
    if ( mode == -1 )
    {
        wxLogWarning(_("Mode %ix%i-%i not available, falling back to default mode."), width, height, depth);
        mode = 0; // always available
    }
    g_displayDC = new MGLDisplayDC(mode, 1, refresh);
    if ( !g_displayDC->isValid() )
    {
        delete g_displayDC;
        g_displayDC = NULL;
        return FALSE;
    }
    
    g_winMng = MGL_wmCreate(g_displayDC->getDC());
    if (!g_winMng)
        return FALSE;
    
    return TRUE;
}

void wxDestroyMGL_WM()
{
    if (g_winMng)
    {
        MGL_wmDestroy(g_winMng);
        g_winMng = NULL;
    }
    delete g_displayDC;
    g_displayDC = NULL;
}


// ---------------------------------------------------------------------------
// event tables
// ---------------------------------------------------------------------------

// in wxUniv/MSW this class is abstract because it doesn't have DoPopupMenu()
// method
IMPLEMENT_ABSTRACT_CLASS(wxWindowMGL, wxWindowBase)

BEGIN_EVENT_TABLE(wxWindowMGL, wxWindowBase)
    EVT_ERASE_BACKGROUND(wxWindowMGL::OnEraseBackground)
    EVT_SET_FOCUS(wxWindowMGL::OnSetFocus)
END_EVENT_TABLE()

// ===========================================================================
// implementation
// ===========================================================================

// ----------------------------------------------------------------------------
// constructors and such
// ----------------------------------------------------------------------------

void wxWindowMGL::Init()
{
    // generic:
    InitBase();

    // mgl specific:
    if ( !g_winMng && !wxCreateMGL_WM() )
        wxFatalError(_T("Can't initalize MGL, aborting!"));

    m_wnd = NULL;
    m_isShown = TRUE;
    m_isBeingDeleted = FALSE;
    m_isEnabled = TRUE;
    m_frozen = FALSE;
    m_paintMGLDC = NULL;
}

// Destructor
wxWindowMGL::~wxWindowMGL()
{
    m_isBeingDeleted = TRUE;

    if ( g_focusedWindow == this )
        g_focusedWindow = NULL;
#if 0 // -- fixme - do we need this?
    // VS: make sure there's no wxFrame with last focus set to us:
    for (wxWindow *win = GetParent(); win; win = win->GetParent())
    {
        wxFrame *frame = wxDynamicCast(win, wxFrame);
        if ( frame )
        {
            if ( frame->GetLastFocus() == this )
                frame->SetLastFocus((wxWindow*)NULL);
            break;
        }
    }
#endif

    // VS: destroy children first and _then_ detach *this from its parent.
    //     If we'd do it the other way around, children wouldn't be able
    //     find their parent frame (see above).
    DestroyChildren();

    if ( m_parent )
        m_parent->RemoveChild(this);

    if ( m_wnd )
        MGL_wmDestroyWindow(m_wnd);
}

// real construction (Init() must have been called before!)
bool wxWindowMGL::Create(wxWindow *parent,
                         wxWindowID id,
                         const wxPoint& pos,
                         const wxSize& size,
                         long style,
                         const wxString& name)
{
    wxCHECK_MSG( parent, FALSE, wxT("can't create wxWindow without parent") );

    if ( !CreateBase(parent, id, pos, size, style, wxDefaultValidator, name) )
        return FALSE;

    parent->AddChild(this);

    if ( style & wxPOPUP_WINDOW )
    {
        // it is created hidden as other top level windows
        m_isShown = FALSE;
    }

    m_wnd = MGL_wmCreateWindow(g_winMng,
                               parent ? parent->GetHandle() : NULL,
                               pos.x, pos.y, size.x, size.y);
    MGL_wmSetWindowUserData(m_wnd, (void*) this);
    MGL_wmSetWindowPainter(m_wnd, wxWindowPainter);
    return TRUE;
}

// ---------------------------------------------------------------------------
// basic operations
// ---------------------------------------------------------------------------

void wxWindowMGL::SetFocus()
{
    if (g_focusedWindow)
        g_focusedWindow->KillFocus();
    
    g_focusedWindow = this;
    
    MGL_wmCaptureEvents(GetHandle(), EVT_KEYEVT | EVT_JOYEVT, wxMGL_CAPTURE_KEYB);

    wxPanel *panel = wxDynamicCast(GetParent(), wxPanel);
    if (panel)
        panel->SetLastFocus((wxWindow*)this);

#if wxUSE_CARET
    // caret needs to be informed about focus change
    wxCaret *caret = GetCaret();
    if (caret)
        caret->OnSetFocus();
#endif // wxUSE_CARET

    if (IsTopLevel())
    {
        wxActivateEvent event(wxEVT_ACTIVATE, TRUE, GetId());
        event.SetEventObject(this);
        GetEventHandler()->ProcessEvent(event);
    }
    
    wxFocusEvent event(wxEVT_SET_FOCUS, GetId());
    event.SetEventObject(this);
    GetEventHandler()->ProcessEvent(event);
}

void wxWindowMGL::KillFocus()
{
    if ( g_focusedWindow != this ) return;
    g_focusedWindow = NULL;

    MGL_wmUncaptureEvents(GetHandle(), wxMGL_CAPTURE_KEYB);

#if wxUSE_CARET
    // caret needs to be informed about focus change
    wxCaret *caret = GetCaret();
    if (caret)
        caret->OnKillFocus();
#endif // wxUSE_CARET

    if (IsTopLevel())
    {
        wxActivateEvent event(wxEVT_ACTIVATE, FALSE, GetId());
        event.SetEventObject(this);
        GetEventHandler()->ProcessEvent(event);
    }

    wxFocusEvent event(wxEVT_KILL_FOCUS, GetId());
    event.SetEventObject(this);
    GetEventHandler()->ProcessEvent(event);
}

// ----------------------------------------------------------------------------
// this wxWindowBase function is implemented here (in platform-specific file)
// because it is static and so couldn't be made virtual
// ----------------------------------------------------------------------------
wxWindow *wxWindowBase::FindFocus()
{
    return (wxWindow*)g_focusedWindow;
}

bool wxWindowMGL::Show(bool show)
{
    if ( !wxWindowBase::Show(show) )
        return FALSE;

    MGL_wmShowWindow(m_wnd, show);
    return TRUE;
}

// Raise the window to the top of the Z order
void wxWindowMGL::Raise()
{
    MGL_wmRaiseWindow(m_wnd);
}

// Lower the window to the bottom of the Z order
void wxWindowMGL::Lower()
{
    MGL_wmLowerWindow(m_wnd);
}

void wxWindowMGL::CaptureMouse()
{
    MGL_wmCaptureEvents(m_wnd, EVT_MOUSEEVT, wxMGL_CAPTURE_MOUSE);
}

void wxWindowMGL::ReleaseMouse()
{
    MGL_wmUncaptureEvents(m_wnd, wxMGL_CAPTURE_MOUSE);
}

/* static */ wxWindow *wxWindowBase::GetCapture()
{
    for (captureentry_t *c = g_winMng->capturedEvents; c; c = c->next)
    {
        if ( c->id == wxMGL_CAPTURE_MOUSE )
            return (wxWindow*)c->wnd->userData;
    }
    return NULL;
}

bool wxWindowMGL::SetCursor(const wxCursor& cursor)
{
    if ( !wxWindowBase::SetCursor(cursor) )
    {
        // no change
        return FALSE;
    }

    if ( m_cursor.Ok() )
        MGL_wmSetWindowCursor(m_wnd, *m_cursor.GetMGLCursor());

    return TRUE;
}

void wxWindowMGL::WarpPointer(int x, int y)
{
    ClientToScreen(&x, &y);
    EVT_setMousePos(x, y);
}

#if WXWIN_COMPATIBILITY
// If nothing defined for this, try the parent.
// E.g. we may be a button loaded from a resource, with no callback function
// defined.
void wxWindowMGL::OnCommand(wxWindow& win, wxCommandEvent& event)
{
    if ( GetEventHandler()->ProcessEvent(event)  )
        return;
    if ( m_parent )
        m_parent->GetEventHandler()->OnCommand(win, event);
}
#endif // WXWIN_COMPATIBILITY_2

#if WXWIN_COMPATIBILITY
wxObject* wxWindowMGL::GetChild(int number) const
{
    // Return a pointer to the Nth object in the Panel
    wxNode *node = GetChildren().First();
    int n = number;
    while (node && n--)
        node = node->Next();
    if ( node )
    {
        wxObject *obj = (wxObject *)node->Data();
        return(obj);
    }
    else
        return NULL;
}
#endif // WXWIN_COMPATIBILITY

// Set this window to be the child of 'parent'.
bool wxWindowMGL::Reparent(wxWindowBase *parent)
{
    if ( !wxWindowBase::Reparent(parent) )
        return FALSE;

    MGL_wmReparentWindow(m_wnd, parent->GetHandle());

    return TRUE;
}


// ---------------------------------------------------------------------------
// drag and drop
// ---------------------------------------------------------------------------

#if wxUSE_DRAG_AND_DROP

void wxWindowMGL::SetDropTarget(wxDropTarget *pDropTarget)
{
    if ( m_dropTarget != 0 ) {
        m_dropTarget->Revoke(m_hWnd);
        delete m_dropTarget;
    }

    m_dropTarget = pDropTarget;
    if ( m_dropTarget != 0 )
        m_dropTarget->Register(m_hWnd);
}
// FIXME_MGL
#endif // wxUSE_DRAG_AND_DROP

// old style file-manager drag&drop support: we retain the old-style
// DragAcceptFiles in parallel with SetDropTarget.
void wxWindowMGL::DragAcceptFiles(bool accept)
{
#if 0 // FIXME_MGL
    HWND hWnd = GetHwnd();
    if ( hWnd )
        ::DragAcceptFiles(hWnd, (BOOL)accept);
#endif
}

// ---------------------------------------------------------------------------
// moving and resizing
// ---------------------------------------------------------------------------

// Get total size
void wxWindowMGL::DoGetSize(int *x, int *y) const
{
    if (x) *x = m_wnd->width;
    if (y) *y = m_wnd->height;
}

void wxWindowMGL::DoGetPosition(int *x, int *y) const
{
    if (x) *x = m_wnd->x;
    if (y) *y = m_wnd->y;
}

void wxWindowMGL::DoScreenToClient(int *x, int *y) const
{
    int ax, ay;
    wxPoint co = GetClientAreaOrigin();

    MGL_wmCoordGlobalToLocal(m_wnd, m_wnd->x, m_wnd->y, &ax, &ay);
    ax -= co.x;
    ay -= co.y;
    if (x)
        *x = ax;
    if (y)
        *y = ay;
}

void wxWindowMGL::DoClientToScreen(int *x, int *y) const
{
    int ax, ay;
    wxPoint co = GetClientAreaOrigin();

    MGL_wmCoordGlobalToLocal(m_wnd, m_wnd->x+co.x, m_wnd->y+co.y, &ax, &ay);
    if (x)
        *x = ax;
    if (y)
        *y = ay;
}

// Get size *available for subwindows* i.e. excluding menu bar etc.
void wxWindowMGL::DoGetClientSize(int *x, int *y) const
{
    DoGetSize(x, y);
}

void wxWindowMGL::DoMoveWindow(int x, int y, int width, int height)
{
    MGL_wmSetWindowPosition(GetHandle(), x, y, width, height);
}

// set the size of the window: if the dimensions are positive, just use them,
// but if any of them is equal to -1, it means that we must find the value for
// it ourselves (unless sizeFlags contains wxSIZE_ALLOW_MINUS_ONE flag, in
// which case -1 is a valid value for x and y)
//
// If sizeFlags contains wxSIZE_AUTO_WIDTH/HEIGHT flags (default), we calculate
// the width/height to best suit our contents, otherwise we reuse the current
// width/height
void wxWindowMGL::DoSetSize(int x, int y, int width, int height, int sizeFlags)
{
    // get the current size and position...
    int currentX, currentY;
    GetPosition(&currentX, &currentY);
    int currentW,currentH;
    GetSize(&currentW, &currentH);

    // ... and don't do anything (avoiding flicker) if it's already ok
    if ( x == currentX && y == currentY &&
         width == currentW && height == currentH )
    {
        return;
    }

    if ( x == -1 && !(sizeFlags & wxSIZE_ALLOW_MINUS_ONE) )
        x = currentX;
    if ( y == -1 && !(sizeFlags & wxSIZE_ALLOW_MINUS_ONE) )
        y = currentY;

#if 0 // FIXME_MGL -- what's this good for?
    AdjustForParentClientOrigin(x, y, sizeFlags);
#endif

    wxSize size(-1, -1);
    if ( width == -1 )
    {
        if ( sizeFlags & wxSIZE_AUTO_WIDTH )
        {
            size = DoGetBestSize();
            width = size.x;
        }
        else
        {
            // just take the current one
            width = currentW;
        }
    }

    if ( height == -1 )
    {
        if ( sizeFlags & wxSIZE_AUTO_HEIGHT )
        {
            if ( size.x == -1 )
            {
                size = DoGetBestSize();
            }
            //else: already called DoGetBestSize() above

            height = size.y;
        }
        else
        {
            // just take the current one
            height = currentH;
        }
    }

    DoMoveWindow(x, y, width, height);

    wxSizeEvent event(wxSize(width, height), GetId());
    event.SetEventObject(this);
    GetEventHandler()->ProcessEvent(event);
}

void wxWindowMGL::DoSetClientSize(int width, int height)
{
    SetSize(width, height);
}

// ---------------------------------------------------------------------------
// text metrics
// ---------------------------------------------------------------------------

int wxWindowMGL::GetCharHeight() const
{
    wxScreenDC dc;
    dc.SetFont(m_font);
    return dc.GetCharHeight();
}

int wxWindowMGL::GetCharWidth() const
{
    wxScreenDC dc;
    dc.SetFont(m_font);
    return dc.GetCharWidth();
}

void wxWindowMGL::GetTextExtent(const wxString& string,
                             int *x, int *y,
                             int *descent, int *externalLeading,
                             const wxFont *theFont) const
{
    wxScreenDC dc;
    if (!theFont)
        theFont = &m_font;
    dc.GetTextExtent(string, x, y, descent, externalLeading, (wxFont*)theFont);
}

#if wxUSE_CARET && WXWIN_COMPATIBILITY
// ---------------------------------------------------------------------------
// Caret manipulation
// ---------------------------------------------------------------------------

void wxWindowMGL::CreateCaret(int w, int h)
{
    SetCaret(new wxCaret(this, w, h));
}

void wxWindowMGL::CreateCaret(const wxBitmap *WXUNUSED(bitmap))
{
    wxFAIL_MSG("not implemented");
}

void wxWindowMGL::ShowCaret(bool show)
{
    wxCHECK_RET( m_caret, "no caret to show" );

    m_caret->Show(show);
}

void wxWindowMGL::DestroyCaret()
{
    SetCaret(NULL);
}

void wxWindowMGL::SetCaretPos(int x, int y)
{
    wxCHECK_RET( m_caret, "no caret to move" );

    m_caret->Move(x, y);
}

void wxWindowMGL::GetCaretPos(int *x, int *y) const
{
    wxCHECK_RET( m_caret, "no caret to get position of" );

    m_caret->GetPosition(x, y);
}
#endif // wxUSE_CARET


// ---------------------------------------------------------------------------
// activation/focus
// ---------------------------------------------------------------------------

void wxWindowMGL::OnSetFocus(wxFocusEvent& event)
{
    // panel wants to track the window which was the last to have focus in it,
    // so we want to set ourselves as the window which last had focus
    //
    // notice that it's also important to do it upwards the tree becaus
    // otherwise when the top level panel gets focus, it won't set it back to
    // us, but to some other sibling
    wxWindow *win = (wxWindow *)this;
    while ( win )
    {
        wxWindow *parent = win->GetParent();
        wxPanel *panel = wxDynamicCast(parent, wxPanel);
        if ( panel )
        {
            panel->SetLastFocus(win);
        }

        win = parent;
    }

    event.Skip();
}


// ---------------------------------------------------------------------------
// painting
// ---------------------------------------------------------------------------

void wxWindowMGL::Clear()
{
    wxClientDC dc((wxWindow *)this);
    wxBrush brush(GetBackgroundColour(), wxSOLID);
    dc.SetBackground(brush);
    dc.Clear();
}

void wxWindowMGL::Refresh(bool WXUNUSED(eraseBack), const wxRect *rect)
{
    if ( rect )
    {
        rect_t r;
        r.left = rect->GetLeft(), r.right = rect->GetRight();
        r.top = rect->GetTop(), r.bottom = rect->GetBottom();
        MGL_wmInvalidateWindowRect(GetHandle(), &r);
    }
    else
        MGL_wmInvalidateWindow(GetHandle());
}

void wxWindowMGL::Update()
{
    Refresh();
    if ( !m_frozen )
        MGL_wmUpdateDC(g_winMng);
}

void wxWindowMGL::Freeze()
{
    m_frozen = TRUE;
    m_refreshAfterThaw = FALSE;
}

void wxWindowMGL::Thaw()
{
    m_frozen = FALSE;
    if ( m_refreshAfterThaw )
        Refresh();
}

static void wxWindowPainter(window_t *wnd, MGLDC *dc)
{
    wxWindow *w = (wxWindow*) wnd->userData;
    if (w)
    {
        MGLDevCtx ctx(dc);
        w->HandlePaint(&ctx);
    }
}

void wxWindowMGL::HandlePaint(MGLDevCtx *dc)
{
    if ( m_frozen )
    {
        // Don't paint anything if the window is frozen. 
        return;
    }

    region_t *clip = NULL;
    MGL_getClipRegionDC(*dc, clip);
    m_updateRegion = wxRegion(MGLRegion(clip));
    m_paintMGLDC = dc;

    wxEraseEvent eventEr(m_windowId, NULL);
    eventEr.SetEventObject(this);
    GetEventHandler()->ProcessEvent(eventEr);

    wxNcPaintEvent eventNc(GetId());
    eventNc.SetEventObject(this);
    GetEventHandler()->ProcessEvent(eventNc);
    
    wxPaintEvent eventPt(GetId());
    eventPt.SetEventObject(this);
    GetEventHandler()->ProcessEvent(eventPt);
}

void wxWindowMGL::OnEraseBackground(wxEraseEvent& event)
{
    Clear();
}


// Find the wxWindow at the current mouse position, returning the mouse
// position.
wxWindow* wxFindWindowAtPointer(wxPoint& pt)
{
    return wxFindWindowAtPoint(pt = wxGetMousePosition());
}

wxWindow* wxFindWindowAtPoint(const wxPoint& pt)
{
    window_t *wnd = MGL_wmGetWindowAtPosition(g_winMng, pt.x, pt.y);
    return (wxWindow*)wnd->userData;
}
