///////////////////////////////////////////////////////////////////////////////
// Name:        wx/window.h
// Purpose:     wxWindowBase class - the interface of wxWindow
// Author:      Vadim Zeitlin
// Modified by: Ron Lee
// Created:     01/02/97
// RCS-ID:      $Id$
// Copyright:   (c) wxWidgets team
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#ifndef _WX_WINDOW_H_BASE_
#define _WX_WINDOW_H_BASE_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma interface "windowbase.h"
#endif

// ----------------------------------------------------------------------------
// headers which we must include here
// ----------------------------------------------------------------------------

#include "wx/event.h"           // the base class

#include "wx/list.h"            // defines wxWindowList

#include "wx/cursor.h"          // we have member variables of these classes
#include "wx/font.h"            // so we can't do without them
#include "wx/colour.h"
#include "wx/region.h"
#include "wx/utils.h"

#include "wx/validate.h"        // for wxDefaultValidator (always include it)

#if wxUSE_PALETTE
    #include "wx/palette.h"
#endif // wxUSE_PALETTE

#if wxUSE_ACCEL
    #include "wx/accel.h"
#endif // wxUSE_ACCEL

#if wxUSE_ACCESSIBILITY
#include "wx/access.h"
#endif

// when building wxUniv/Foo we don't want the code for native menu use to be
// compiled in - it should only be used when building real wxFoo
#ifdef __WXUNIVERSAL__
    #define wxUSE_MENUS_NATIVE 0
#else // __WXMSW__
    #define wxUSE_MENUS_NATIVE wxUSE_MENUS
#endif // __WXUNIVERSAL__/__WXMSW__

// ----------------------------------------------------------------------------
// forward declarations
// ----------------------------------------------------------------------------

class WXDLLEXPORT wxCaret;
class WXDLLEXPORT wxControl;
class WXDLLEXPORT wxCursor;
class WXDLLEXPORT wxDC;
class WXDLLEXPORT wxDropTarget;
class WXDLLEXPORT wxItemResource;
class WXDLLEXPORT wxLayoutConstraints;
class WXDLLEXPORT wxResourceTable;
class WXDLLEXPORT wxSizer;
class WXDLLEXPORT wxToolTip;
class WXDLLEXPORT wxWindowBase;
class WXDLLEXPORT wxWindow;

#if wxUSE_ACCESSIBILITY
class WXDLLEXPORT wxAccessible;
#endif

// ----------------------------------------------------------------------------
// helper stuff used by wxWindow
// ----------------------------------------------------------------------------

// struct containing all the visual attributes of a control
struct WXDLLEXPORT wxVisualAttributes
{
    // the font used for control label/text inside it
    wxFont font;

    // the foreground colour
    wxColour colFg;

    // the background colour, may be wxNullColour if the controls background
    // colour is not solid
    wxColour colBg;
};

// different window variants, on platforms like eg mac uses different
// rendering sizes
enum wxWindowVariant
{
    wxWINDOW_VARIANT_NORMAL,  // Normal size
    wxWINDOW_VARIANT_SMALL,   // Smaller size (about 25 % smaller than normal)
    wxWINDOW_VARIANT_MINI,    // Mini size (about 33 % smaller than normal)
    wxWINDOW_VARIANT_LARGE,   // Large size (about 25 % larger than normal)
    wxWINDOW_VARIANT_MAX
};

#if wxUSE_SYSTEM_OPTIONS
    #define wxWINDOW_DEFAULT_VARIANT wxT("window-default-variant")
#endif

// ----------------------------------------------------------------------------
// (pseudo)template list classes
// ----------------------------------------------------------------------------

WX_DECLARE_LIST_3(wxWindow, wxWindowBase, wxWindowList, wxWindowListNode, class WXDLLEXPORT);

// ----------------------------------------------------------------------------
// global variables
// ----------------------------------------------------------------------------

WXDLLEXPORT_DATA(extern wxWindowList) wxTopLevelWindows;

// ----------------------------------------------------------------------------
// wxWindowBase is the base class for all GUI controls/widgets, this is the public
// interface of this class.
//
// Event handler: windows have themselves as their event handlers by default,
// but their event handlers could be set to another object entirely. This
// separation can reduce the amount of derivation required, and allow
// alteration of a window's functionality (e.g. by a resource editor that
// temporarily switches event handlers).
// ----------------------------------------------------------------------------

class WXDLLEXPORT wxWindowBase : public wxEvtHandler
{
public:
    // creating the window
    // -------------------

        // default ctor, initializes everything which can be initialized before
        // Create()
    wxWindowBase() ;

        // pseudo ctor (can't be virtual, called from ctor)
    bool CreateBase(wxWindowBase *parent,
                    wxWindowID winid,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    long style = 0,
                    const wxValidator& validator = wxDefaultValidator,
                    const wxString& name = wxPanelNameStr);

    virtual ~wxWindowBase();

    // deleting the window
    // -------------------

        // ask the window to close itself, return true if the event handler
        // honoured our request
    bool Close( bool force = false );

        // the following functions delete the C++ objects (the window itself
        // or its children) as well as the GUI windows and normally should
        // never be used directly

        // delete window unconditionally (dangerous!), returns true if ok
    virtual bool Destroy();
        // delete all children of this window, returns true if ok
    bool DestroyChildren();

        // is the window being deleted?
    bool IsBeingDeleted() const { return m_isBeingDeleted; }

    // window attributes
    // -----------------

        // NB: in future versions of wxWidgets Set/GetTitle() will only work
        //     with the top level windows (such as dialogs and frames) and
        //     Set/GetLabel() only with the other ones (i.e. all controls).

        // the title (or label, see below) of the window: the text which the
        // window shows
    virtual void SetTitle( const wxString& WXUNUSED(title) ) {}
    virtual wxString GetTitle() const { return wxEmptyString; }

        // label is just the same as the title (but for, e.g., buttons it
        // makes more sense to speak about labels)
    virtual void SetLabel(const wxString& label) { SetTitle(label); }
    virtual wxString GetLabel() const { return GetTitle(); }

        // the window name is used for ressource setting in X, it is not the
        // same as the window title/label
    virtual void SetName( const wxString &name ) { m_windowName = name; }
    virtual wxString GetName() const { return m_windowName; }

    // sets the window variant, calls internally DoSetVariant if variant has changed
    void SetWindowVariant( wxWindowVariant variant ) ;
    wxWindowVariant GetWindowVariant() const { return m_windowVariant ; }


        // window id uniquely identifies the window among its siblings unless
        // it is wxID_ANY which means "don't care"
    void SetId( wxWindowID winid ) { m_windowId = winid; }
    wxWindowID GetId() const { return m_windowId; }

        // generate a control id for the controls which were not given one by
        // user
    static int NewControlId() { return --ms_lastControlId; }
        // get the id of the control following the one with the given
        // (autogenerated) id
    static int NextControlId(int winid) { return winid - 1; }
        // get the id of the control preceding the one with the given
        // (autogenerated) id
    static int PrevControlId(int winid) { return winid + 1; }

    // moving/resizing
    // ---------------

        // set the window size and/or position
    void SetSize( int x, int y, int width, int height,
                  int sizeFlags = wxSIZE_AUTO )
        {  DoSetSize(x, y, width, height, sizeFlags); }

    void SetSize( int width, int height )
        { DoSetSize( wxDefaultCoord, wxDefaultCoord, width, height, wxSIZE_USE_EXISTING ); }

    void SetSize( const wxSize& size )
        { SetSize( size.x, size.y); }

    void SetSize(const wxRect& rect, int sizeFlags = wxSIZE_AUTO)
        { DoSetSize(rect.x, rect.y, rect.width, rect.height, sizeFlags); }

    void Move(int x, int y, int flags = wxSIZE_USE_EXISTING)
        { DoSetSize(x, y, wxDefaultCoord, wxDefaultCoord, flags); }

    void Move(const wxPoint& pt, int flags = wxSIZE_USE_EXISTING)
        { Move(pt.x, pt.y, flags); }

        // Z-order
    virtual void Raise() = 0;
    virtual void Lower() = 0;

        // client size is the size of area available for subwindows
    void SetClientSize( int width, int height )
        { DoSetClientSize(width, height); }

    void SetClientSize( const wxSize& size )
        { DoSetClientSize(size.x, size.y); }

    void SetClientSize(const wxRect& rect)
        { SetClientSize( rect.width, rect.height ); }

        // get the window position and/or size (pointers may be NULL)
    void GetPosition( int *x, int *y ) const { DoGetPosition(x, y); }
    wxPoint GetPosition() const
    {
        int w, h;
        DoGetPosition(&w, &h);

        return wxPoint(w, h);
    }

    void SetPosition( const wxPoint& pt ) { Move( pt ) ; }

    void GetSize( int *w, int *h ) const { DoGetSize(w, h); }
    wxSize GetSize() const
    {
        int w, h;
        DoGetSize(& w, & h);
        return wxSize(w, h);
    }

    wxRect GetRect() const
    {
        int x, y, w, h;
        GetPosition(& x, & y);
        GetSize(& w, & h);

        return wxRect(x, y, w, h);
    }

    void GetClientSize( int *w, int *h ) const { DoGetClientSize(w, h); }
    wxSize GetClientSize() const
    {
        int w, h;
        DoGetClientSize(& w, & h);

        return wxSize(w, h);
    }

        // get the origin of the client area of the window relative to the
        // window top left corner (the client area may be shifted because of
        // the borders, scrollbars, other decorations...)
    virtual wxPoint GetClientAreaOrigin() const;

        // get the client rectangle in window (i.e. client) coordinates
    wxRect GetClientRect() const
    {
        return wxRect(GetClientAreaOrigin(), GetClientSize());
    }

        // get the size best suited for the window (in fact, minimal
        // acceptable size using which it will still look "nice" in
        // most situations)
    wxSize GetBestSize() const
    {
        if (m_bestSizeCache.IsFullySpecified())
            return m_bestSizeCache;
        return DoGetBestSize();
    }
    void GetBestSize(int *w, int *h) const
    {
        wxSize s = GetBestSize();
        if ( w )
            *w = s.x;
        if ( h )
            *h = s.y;
    }

        // reset the cached best size value so it will be recalculated the
        // next time it is needed.
    void InvalidateBestSize();
    void CacheBestSize(const wxSize& size) const
        { wxConstCast(this, wxWindowBase)->m_bestSizeCache = size; }

        // There are times (and windows) where 'Best' size and 'Min' size
        // are vastly out of sync.  This should be remedied somehow, but in
        // the meantime, this method will return the larger of BestSize
        // (the window's smallest legible size), and any user specified
        // MinSize hint.
    wxSize GetAdjustedBestSize() const
    {
        wxSize  s( GetBestSize() );
        return wxSize( wxMax( s.x, GetMinWidth() ), wxMax( s.y, GetMinHeight() ) );
    }

        // This function will merge the window's best size into the window's
        // minimum size, giving priority to the min size components, and
        // returns the results.
    wxSize GetBestFittingSize() const;

        // A 'Smart' SetSize that will fill in default size values with 'best'
        // size.  Sets the minsize to what was passed in.
    void SetBestFittingSize(const wxSize& size=wxDefaultSize);

        // the generic centre function - centers the window on parent by`
        // default or on screen if it doesn't have parent or
        // wxCENTER_ON_SCREEN flag is given
    void Centre( int direction = wxBOTH );
    void Center( int direction = wxBOTH ) { Centre(direction); }

        // centre on screen (only works for top level windows)
    void CentreOnScreen(int dir = wxBOTH) { Centre(dir | wxCENTER_ON_SCREEN); }
    void CenterOnScreen(int dir = wxBOTH) { CentreOnScreen(dir); }

        // centre with respect to the the parent window
    void CentreOnParent(int dir = wxBOTH) { Centre(dir | wxCENTER_FRAME); }
    void CenterOnParent(int dir = wxBOTH) { CentreOnParent(dir); }

        // set window size to wrap around its children
    virtual void Fit();

        // set virtual size to satisfy children
    virtual void FitInside();

        // set min/max size of the window
    virtual void SetSizeHints( int minW, int minH,
                               int maxW = wxDefaultCoord, int maxH = wxDefaultCoord,
                               int incW = wxDefaultCoord, int incH = wxDefaultCoord )
    {
        DoSetSizeHints(minW, minH, maxW, maxH, incW, incH);
    }

    void SetSizeHints( const wxSize& minSize,
                       const wxSize& maxSize=wxDefaultSize,
                       const wxSize& incSize=wxDefaultSize)
    {
        DoSetSizeHints(minSize.x, minSize.y,
                       maxSize.x, maxSize.y,
                       incSize.x, incSize.y);
    }

    virtual void DoSetSizeHints(int minW, int minH,
                                int maxW = wxDefaultCoord, int maxH = wxDefaultCoord,
                               int incW = wxDefaultCoord, int incH = wxDefaultCoord );

    virtual void SetVirtualSizeHints( int minW, int minH,
                                      int maxW = wxDefaultCoord, int maxH = wxDefaultCoord );
    void SetVirtualSizeHints( const wxSize& minSize,
                              const wxSize& maxSize=wxDefaultSize)
    {
        SetVirtualSizeHints(minSize.x, minSize.y, maxSize.x, maxSize.y);
    }

    virtual int GetMinWidth() const { return m_minWidth; }
    virtual int GetMinHeight() const { return m_minHeight; }
    int GetMaxWidth() const { return m_maxWidth; }
    int GetMaxHeight() const { return m_maxHeight; }

        // Override this method to control the values given to Sizers etc.
    virtual wxSize GetMaxSize() const { return wxSize( m_maxWidth, m_maxHeight ); }
    virtual wxSize GetMinSize() const { return wxSize( m_minWidth, m_minHeight ); }

    void SetMinSize(const wxSize& minSize) { SetSizeHints(minSize); }
    void SetMaxSize(const wxSize& maxSize) { SetSizeHints(GetMinSize(), maxSize); }

        // Methods for accessing the virtual size of a window.  For most
        // windows this is just the client area of the window, but for
        // some like scrolled windows it is more or less independent of
        // the screen window size.  You may override the DoXXXVirtual
        // methods below for classes where that is is the case.

    void SetVirtualSize( const wxSize &size ) { DoSetVirtualSize( size.x, size.y ); }
    void SetVirtualSize( int x, int y ) { DoSetVirtualSize( x, y ); }

    wxSize GetVirtualSize() const { return DoGetVirtualSize(); }
    void GetVirtualSize( int *x, int *y ) const
    {
        wxSize s( DoGetVirtualSize() );

        if( x )
            *x = s.GetWidth();
        if( y )
            *y = s.GetHeight();
    }

        // Override these methods for windows that have a virtual size
        // independent of their client size.  eg. the virtual area of a
        // wxScrolledWindow.  Default is to alias VirtualSize to ClientSize.

    virtual void DoSetVirtualSize( int x, int y );
    virtual wxSize DoGetVirtualSize() const; // { return m_virtualSize; }

        // Return the largest of ClientSize and BestSize (as determined
        // by a sizer, interior children, or other means)

    virtual wxSize GetBestVirtualSize() const
    {
        wxSize  client( GetClientSize() );
        wxSize  best( GetBestSize() );

        return wxSize( wxMax( client.x, best.x ), wxMax( client.y, best.y ) );
    }

    // window state
    // ------------

        // returns true if window was shown/hidden, false if the nothing was
        // done (window was already shown/hidden)
    virtual bool Show( bool show = true );
    bool Hide() { return Show(false); }

        // returns true if window was enabled/disabled, false if nothing done
    virtual bool Enable( bool enable = true );
    bool Disable() { return Enable(false); }

    bool IsShown() const { return m_isShown; }
    bool IsEnabled() const { return m_isEnabled; }

        // get/set window style (setting style won't update the window and so
        // is only useful for internal usage)
    virtual void SetWindowStyleFlag( long style ) { m_windowStyle = style; }
    virtual long GetWindowStyleFlag() const { return m_windowStyle; }

        // just some (somewhat shorter) synonims
    void SetWindowStyle( long style ) { SetWindowStyleFlag(style); }
    long GetWindowStyle() const { return GetWindowStyleFlag(); }

    bool HasFlag(int flag) const { return (m_windowStyle & flag) != 0; }
    virtual bool IsRetained() const { return HasFlag(wxRETAINED); }

        // extra style: the less often used style bits which can't be set with
        // SetWindowStyleFlag()
    virtual void SetExtraStyle(long exStyle) { m_exStyle = exStyle; }
    long GetExtraStyle() const { return m_exStyle; }

        // make the window modal (all other windows unresponsive)
    virtual void MakeModal(bool modal = true);


    // (primitive) theming support
    // ---------------------------

    virtual void SetThemeEnabled(bool enableTheme) { m_themeEnabled = enableTheme; }
    virtual bool GetThemeEnabled() const { return m_themeEnabled; }

        // Returns true if this class should have the background colour
        // changed to match the parent window's theme.  For example when a
        // page is added to a notebook it and its children may need to have
        // the colours adjusted depending on the current theme settings, but
        // not all windows/controls can do this without looking wrong.
    virtual void ApplyParentThemeBackground(const wxColour& WXUNUSED(bg))
        { /* do nothing */ }


    // focus and keyboard handling
    // ---------------------------

        // set focus to this window
    virtual void SetFocus() = 0;

        // set focus to this window as the result of a keyboard action
    virtual void SetFocusFromKbd() { SetFocus(); }

        // return the window which currently has the focus or NULL
    static wxWindow *FindFocus();

    static wxWindow *DoFindFocus() /* = 0: implement in derived classes */;

        // can this window have focus?
    virtual bool AcceptsFocus() const { return IsShown() && IsEnabled(); }

        // can this window be given focus by keyboard navigation? if not, the
        // only way to give it focus (provided it accepts it at all) is to
        // click it
    virtual bool AcceptsFocusFromKeyboard() const { return AcceptsFocus(); }

        // NB: these methods really don't belong here but with the current
        //     class hierarchy there is no other place for them :-(

        // get the default child of this parent, i.e. the one which is
        // activated by pressing <Enter>
    virtual wxWindow *GetDefaultItem() const { return NULL; }

        // set this child as default, return the old default
    virtual wxWindow *SetDefaultItem(wxWindow * WXUNUSED(child))
        { return NULL; }

        // set this child as temporary default
    virtual void SetTmpDefaultItem(wxWindow * WXUNUSED(win)) { }

        // navigates in the specified direction by sending a wxNavigationKeyEvent
    virtual bool Navigate(int flags = wxNavigationKeyEvent::IsForward);

        // move this window just before/after the specified one in tab order
        // (the other window must be our sibling!)
    void MoveBeforeInTabOrder(wxWindow *win)
        { DoMoveInTabOrder(win, MoveBefore); }
    void MoveAfterInTabOrder(wxWindow *win)
        { DoMoveInTabOrder(win, MoveAfter); }


    // parent/children relations
    // -------------------------

        // get the list of children
    const wxWindowList& GetChildren() const { return m_children; }
    wxWindowList& GetChildren() { return m_children; }

    // needed just for extended runtime
    const wxWindowList& GetWindowChildren() const { return GetChildren() ; }

        // get the parent or the parent of the parent
    wxWindow *GetParent() const { return m_parent; }
    inline wxWindow *GetGrandParent() const;

        // is this window a top level one?
    virtual bool IsTopLevel() const;

        // it doesn't really change parent, use Reparent() instead
    void SetParent( wxWindowBase *parent ) { m_parent = (wxWindow *)parent; }
        // change the real parent of this window, return true if the parent
        // was changed, false otherwise (error or newParent == oldParent)
    virtual bool Reparent( wxWindowBase *newParent );

        // implementation mostly
    virtual void AddChild( wxWindowBase *child );
    virtual void RemoveChild( wxWindowBase *child );

    // looking for windows
    // -------------------

        // find window among the descendants of this one either by id or by
        // name (return NULL if not found)
    wxWindow *FindWindow(long winid) const;
    wxWindow *FindWindow(const wxString& name) const;

        // Find a window among any window (all return NULL if not found)
    static wxWindow *FindWindowById( long winid, const wxWindow *parent = NULL );
    static wxWindow *FindWindowByName( const wxString& name,
                                       const wxWindow *parent = NULL );
    static wxWindow *FindWindowByLabel( const wxString& label,
                                        const wxWindow *parent = NULL );

    // event handler stuff
    // -------------------

        // get the current event handler
    wxEvtHandler *GetEventHandler() const { return m_eventHandler; }

        // replace the event handler (allows to completely subclass the
        // window)
    void SetEventHandler( wxEvtHandler *handler ) { m_eventHandler = handler; }

        // push/pop event handler: allows to chain a custom event handler to
        // alreasy existing ones
    void PushEventHandler( wxEvtHandler *handler );
    wxEvtHandler *PopEventHandler( bool deleteHandler = false );

        // find the given handler in the event handler chain and remove (but
        // not delete) it from the event handler chain, return true if it was
        // found and false otherwise (this also results in an assert failure so
        // this function should only be called when the handler is supposed to
        // be there)
    bool RemoveEventHandler(wxEvtHandler *handler);

    // validators
    // ----------

#if wxUSE_VALIDATORS
        // a window may have an associated validator which is used to control
        // user input
    virtual void SetValidator( const wxValidator &validator );
    virtual wxValidator *GetValidator() { return m_windowValidator; }
#endif // wxUSE_VALIDATORS


    // dialog oriented functions
    // -------------------------

        // validate the correctness of input, return true if ok
    virtual bool Validate();

        // transfer data between internal and GUI representations
    virtual bool TransferDataToWindow();
    virtual bool TransferDataFromWindow();

    virtual void InitDialog();

#if wxUSE_ACCEL
    // accelerators
    // ------------
    virtual void SetAcceleratorTable( const wxAcceleratorTable& accel )
        { m_acceleratorTable = accel; }
    wxAcceleratorTable *GetAcceleratorTable()
        { return &m_acceleratorTable; }

#endif // wxUSE_ACCEL

#if wxUSE_HOTKEY
    // hot keys (system wide accelerators)
    // -----------------------------------

    virtual bool RegisterHotKey(int hotkeyId, int modifiers, int keycode);
    virtual bool UnregisterHotKey(int hotkeyId);
#endif // wxUSE_HOTKEY


    // dialog units translations
    // -------------------------

    wxPoint ConvertPixelsToDialog( const wxPoint& pt );
    wxPoint ConvertDialogToPixels( const wxPoint& pt );
    wxSize ConvertPixelsToDialog( const wxSize& sz )
    {
        wxPoint pt(ConvertPixelsToDialog(wxPoint(sz.x, sz.y)));

        return wxSize(pt.x, pt.y);
    }

    wxSize ConvertDialogToPixels( const wxSize& sz )
    {
        wxPoint pt(ConvertDialogToPixels(wxPoint(sz.x, sz.y)));

        return wxSize(pt.x, pt.y);
    }

    // mouse functions
    // ---------------

        // move the mouse to the specified position
    virtual void WarpPointer(int x, int y) = 0;

        // start or end mouse capture, these functions maintain the stack of
        // windows having captured the mouse and after calling ReleaseMouse()
        // the mouse is not released but returns to the window which had had
        // captured it previously (if any)
    void CaptureMouse();
    void ReleaseMouse();

        // get the window which currently captures the mouse or NULL
    static wxWindow *GetCapture();

        // does this window have the capture?
    virtual bool HasCapture() const
        { return (wxWindow *)this == GetCapture(); }

    // painting the window
    // -------------------

        // mark the specified rectangle (or the whole window) as "dirty" so it
        // will be repainted
    virtual void Refresh( bool eraseBackground = true,
                          const wxRect *rect = (const wxRect *) NULL ) = 0;

        // a less awkward wrapper for Refresh
    void RefreshRect(const wxRect& rect) { Refresh(true, &rect); }

        // repaint all invalid areas of the window immediately
    virtual void Update() { }

        // clear the window background
    virtual void ClearBackground();

        // freeze the window: don't redraw it until it is thawed
    virtual void Freeze() { }

        // thaw the window: redraw it after it had been frozen
    virtual void Thaw() { }

        // adjust DC for drawing on this window
    virtual void PrepareDC( wxDC & WXUNUSED(dc) ) { }

        // the update region of the window contains the areas which must be
        // repainted by the program
    const wxRegion& GetUpdateRegion() const { return m_updateRegion; }
    wxRegion& GetUpdateRegion() { return m_updateRegion; }

        // get the update rectangleregion bounding box in client coords
    wxRect GetUpdateClientRect() const;

        // these functions verify whether the given point/rectangle belongs to
        // (or at least intersects with) the update region
    bool IsExposed( int x, int y ) const;
    bool IsExposed( int x, int y, int w, int h ) const;

    bool IsExposed( const wxPoint& pt ) const
        { return IsExposed(pt.x, pt.y); }
    bool IsExposed( const wxRect& rect ) const
        { return IsExposed(rect.x, rect.y, rect.width, rect.height); }

    // colours, fonts and cursors
    // --------------------------

        // get the default attributes for the controls of this class: we
        // provide a virtual function which can be used to query the default
        // attributes of an existing control and a static function which can
        // be used even when no existing object of the given class is
        // available, but which won't return any styles specific to this
        // particular control, of course (e.g. "Ok" button might have
        // different -- bold for example -- font)
    virtual wxVisualAttributes GetDefaultAttributes() const
    {
        return GetClassDefaultAttributes(GetWindowVariant());
    }

    static wxVisualAttributes
    GetClassDefaultAttributes(wxWindowVariant variant = wxWINDOW_VARIANT_NORMAL);

        // set/retrieve the window colours (system defaults are used by
        // default): SetXXX() functions return true if colour was changed,
        // SetDefaultXXX() reset the "m_inheritXXX" flag after setting the
        // value to prevent it from being inherited by our children
    virtual bool SetBackgroundColour(const wxColour& colour);
    void SetOwnBackgroundColour(const wxColour& colour)
    {
        if ( SetBackgroundColour(colour) )
            m_inheritBgCol = false;
    }
    wxColour GetBackgroundColour() const;

    // if the window shouldn't inherit its colour from the parent, override
    // this function to return true
    //
    // this is currently only used by wxMSW and wxUniv but should be useful for
    // the other ports too
    virtual bool ProvidesBackground() const { return false; }

    virtual bool SetForegroundColour(const wxColour& colour);
    void SetOwnForegroundColour(const wxColour& colour)
    {
        if ( SetForegroundColour(colour) )
            m_inheritFgCol = false;
    }
    wxColour GetForegroundColour() const;

        // Set/get the background style.
        // Pass one of wxBG_STYLE_SYSTEM, wxBG_STYLE_COLOUR, wxBG_STYLE_CUSTOM
    virtual bool SetBackgroundStyle(wxBackgroundStyle style) { m_backgroundStyle = style; return true; }
    virtual wxBackgroundStyle GetBackgroundStyle() const { return m_backgroundStyle; }

        // returns true if the control has "transparent" areas such as a
        // wxStaticText and wxCheckBox and the background should be adapted
        // from a parent window
    virtual bool HasTransparentBackground() { return false; }

        // set/retrieve the font for the window (SetFont() returns true if the
        // font really changed)
    virtual bool SetFont(const wxFont& font) = 0;
    void SetOwnFont(const wxFont& font)
    {
        if ( SetFont(font) )
            m_inheritFont = false;
    }
    wxFont GetFont() const;

        // set/retrieve the cursor for this window (SetCursor() returns true
        // if the cursor was really changed)
    virtual bool SetCursor( const wxCursor &cursor );
    const wxCursor& GetCursor() const { return m_cursor; }

#if wxUSE_CARET
        // associate a caret with the window
    void SetCaret(wxCaret *caret);
        // get the current caret (may be NULL)
    wxCaret *GetCaret() const { return m_caret; }
#endif // wxUSE_CARET

        // get the (average) character size for the current font
    virtual int GetCharHeight() const = 0;
    virtual int GetCharWidth() const = 0;

        // get the width/height/... of the text using current or specified
        // font
    virtual void GetTextExtent(const wxString& string,
                               int *x, int *y,
                               int *descent = (int *) NULL,
                               int *externalLeading = (int *) NULL,
                               const wxFont *theFont = (const wxFont *) NULL)
                               const = 0;

    // client <-> screen coords
    // ------------------------

        // translate to/from screen/client coordinates (pointers may be NULL)
    void ClientToScreen( int *x, int *y ) const
        { DoClientToScreen(x, y); }
    void ScreenToClient( int *x, int *y ) const
        { DoScreenToClient(x, y); }

        // wxPoint interface to do the same thing
    wxPoint ClientToScreen(const wxPoint& pt) const
    {
        int x = pt.x, y = pt.y;
        DoClientToScreen(&x, &y);

        return wxPoint(x, y);
    }

    wxPoint ScreenToClient(const wxPoint& pt) const
    {
        int x = pt.x, y = pt.y;
        DoScreenToClient(&x, &y);

        return wxPoint(x, y);
    }

        // test where the given (in client coords) point lies
    wxHitTest HitTest(wxCoord x, wxCoord y) const
        { return DoHitTest(x, y); }

    wxHitTest HitTest(const wxPoint& pt) const
        { return DoHitTest(pt.x, pt.y); }

    // misc
    // ----

    // get the window border style from the given flags: this is different from
    // simply doing flags & wxBORDER_MASK because it uses GetDefaultBorder() to
    // translate wxBORDER_DEFAULT to something reasonable
    wxBorder GetBorder(long flags) const;

    // get border for the flags of this window
    wxBorder GetBorder() const { return GetBorder(GetWindowStyleFlag()); }

    // send wxUpdateUIEvents to this window, and children if recurse is true
    virtual void UpdateWindowUI(long flags = wxUPDATE_UI_NONE);

    // do the window-specific processing after processing the update event
    virtual void DoUpdateWindowUI(wxUpdateUIEvent& event) ;

#if wxUSE_MENUS
    bool PopupMenu(wxMenu *menu, const wxPoint& pos = wxDefaultPosition)
        { return DoPopupMenu(menu, pos.x, pos.y); }
    bool PopupMenu(wxMenu *menu, int x, int y)
        { return DoPopupMenu(menu, x, y); }
#endif // wxUSE_MENUS

    // scrollbars
    // ----------

        // does the window have the scrollbar for this orientation?
    bool HasScrollbar(int orient) const
    {
        return (m_windowStyle &
                (orient == wxHORIZONTAL ? wxHSCROLL : wxVSCROLL)) != 0;
    }

        // configure the window scrollbars
    virtual void SetScrollbar( int orient,
                               int pos,
                               int thumbvisible,
                               int range,
                               bool refresh = true ) = 0;
    virtual void SetScrollPos( int orient, int pos, bool refresh = true ) = 0;
    virtual int GetScrollPos( int orient ) const = 0;
    virtual int GetScrollThumb( int orient ) const = 0;
    virtual int GetScrollRange( int orient ) const = 0;

        // scroll window to the specified position
    virtual void ScrollWindow( int dx, int dy,
                               const wxRect* rect = (wxRect *) NULL ) = 0;

        // scrolls window by line/page: note that not all controls support this
        //
        // return true if the position changed, false otherwise
    virtual bool ScrollLines(int WXUNUSED(lines)) { return false; }
    virtual bool ScrollPages(int WXUNUSED(pages)) { return false; }

        // convenient wrappers for ScrollLines/Pages
    bool LineUp() { return ScrollLines(-1); }
    bool LineDown() { return ScrollLines(1); }
    bool PageUp() { return ScrollPages(-1); }
    bool PageDown() { return ScrollPages(1); }

    // context-sensitive help
    // ----------------------

    // these are the convenience functions wrapping wxHelpProvider methods

#if wxUSE_HELP
        // associate this help text with this window
    void SetHelpText(const wxString& text);
        // associate this help text with all windows with the same id as this
        // one
    void SetHelpTextForId(const wxString& text);
        // get the help string associated with this window (may be empty)
    wxString GetHelpText() const;
#endif // wxUSE_HELP

    // tooltips
    // --------

#if wxUSE_TOOLTIPS
        // the easiest way to set a tooltip for a window is to use this method
    void SetToolTip( const wxString &tip );
        // attach a tooltip to the window
    void SetToolTip( wxToolTip *tip ) { DoSetToolTip(tip); }
        // get the associated tooltip or NULL if none
    wxToolTip* GetToolTip() const { return m_tooltip; }
    wxString GetToolTipText() const ;
#else
        // make it much easier to compile apps in an environment
        // that doesn't support tooltips, such as PocketPC
    inline void SetToolTip( const wxString & WXUNUSED(tip) ) {}
#endif // wxUSE_TOOLTIPS

    // drag and drop
    // -------------
#if wxUSE_DRAG_AND_DROP
        // set/retrieve the drop target associated with this window (may be
        // NULL; it's owned by the window and will be deleted by it)
    virtual void SetDropTarget( wxDropTarget *dropTarget ) = 0;
    virtual wxDropTarget *GetDropTarget() const { return m_dropTarget; }
#endif // wxUSE_DRAG_AND_DROP

    // constraints and sizers
    // ----------------------
#if wxUSE_CONSTRAINTS
        // set the constraints for this window or retrieve them (may be NULL)
    void SetConstraints( wxLayoutConstraints *constraints );
    wxLayoutConstraints *GetConstraints() const { return m_constraints; }

        // implementation only
    void UnsetConstraints(wxLayoutConstraints *c);
    wxWindowList *GetConstraintsInvolvedIn() const
        { return m_constraintsInvolvedIn; }
    void AddConstraintReference(wxWindowBase *otherWin);
    void RemoveConstraintReference(wxWindowBase *otherWin);
    void DeleteRelatedConstraints();
    void ResetConstraints();

        // these methods may be overriden for special layout algorithms
    virtual void SetConstraintSizes(bool recurse = true);
    virtual bool LayoutPhase1(int *noChanges);
    virtual bool LayoutPhase2(int *noChanges);
    virtual bool DoPhase(int phase);

        // these methods are virtual but normally won't be overridden
    virtual void SetSizeConstraint(int x, int y, int w, int h);
    virtual void MoveConstraint(int x, int y);
    virtual void GetSizeConstraint(int *w, int *h) const ;
    virtual void GetClientSizeConstraint(int *w, int *h) const ;
    virtual void GetPositionConstraint(int *x, int *y) const ;

#endif // wxUSE_CONSTRAINTS

        // when using constraints or sizers, it makes sense to update
        // children positions automatically whenever the window is resized
        // - this is done if autoLayout is on
    void SetAutoLayout( bool autoLayout ) { m_autoLayout = autoLayout; }
    bool GetAutoLayout() const { return m_autoLayout; }

        // lay out the window and its children
    virtual bool Layout();

        // sizers
    void SetSizer(wxSizer *sizer, bool deleteOld = true );
    void SetSizerAndFit( wxSizer *sizer, bool deleteOld = true );

    wxSizer *GetSizer() const { return m_windowSizer; }

    // Track if this window is a member of a sizer
    void SetContainingSizer(wxSizer* sizer);
    wxSizer *GetContainingSizer() const { return m_containingSizer; }

    // accessibility
    // ----------------------
#if wxUSE_ACCESSIBILITY
    // Override to create a specific accessible object.
    virtual wxAccessible* CreateAccessible();

    // Sets the accessible object.
    void SetAccessible(wxAccessible* accessible) ;

    // Returns the accessible object.
    wxAccessible* GetAccessible() { return m_accessible; };

    // Returns the accessible object, creating if necessary.
    wxAccessible* GetOrCreateAccessible() ;
#endif

    // implementation
    // --------------

        // event handlers
    void OnSysColourChanged( wxSysColourChangedEvent& event );
    void OnInitDialog( wxInitDialogEvent &event );
    void OnMiddleClick( wxMouseEvent& event );
#if wxUSE_HELP
    void OnHelp(wxHelpEvent& event);
#endif // wxUSE_HELP

        // virtual function for implementing internal idle
        // behaviour
        virtual void OnInternalIdle() {}

        // call internal idle recursively
//        void ProcessInternalIdle() ;

        // get the handle of the window for the underlying window system: this
        // is only used for wxWin itself or for user code which wants to call
        // platform-specific APIs
    virtual WXWidget GetHandle() const = 0;
        // associate the window with a new native handle
    virtual void AssociateHandle(WXWidget WXUNUSED(handle)) { }
        // dissociate the current native handle from the window
    virtual void DissociateHandle() { }

#if wxUSE_PALETTE
        // Store the palette used by DCs in wxWindow so that the dcs can share
        // a palette. And we can respond to palette messages.
    wxPalette GetPalette() const { return m_palette; }

        // When palette is changed tell the DC to set the system palette to the
        // new one.
    void SetPalette(const wxPalette& pal);

        // return true if we have a specific palette
    bool HasCustomPalette() const { return m_hasCustomPalette; }

        // return the first parent window with a custom palette or NULL
    wxWindow *GetAncestorWithCustomPalette() const;
#endif // wxUSE_PALETTE

    // inherit the parents visual attributes if they had been explicitly set
    // by the user (i.e. we don't inherit default attributes) and if we don't
    // have our own explicitly set
    virtual void InheritAttributes();

    // returns false from here if this window doesn't want to inherit the
    // parents colours even if InheritAttributes() would normally do it
    //
    // this just provides a simple way to customize InheritAttributes()
    // behaviour in the most common case
    virtual bool ShouldInheritColours() const { return false; }

protected:
    // event handling specific to wxWindow
    virtual bool TryValidator(wxEvent& event);
    virtual bool TryParent(wxEvent& event);

    // common part of MoveBefore/AfterInTabOrder()
    enum MoveKind
    {
        MoveBefore,     // insert before the given window
        MoveAfter       // insert after the given window
    };
    virtual void DoMoveInTabOrder(wxWindow *win, MoveKind move);

#if wxUSE_CONSTRAINTS
    // satisfy the constraints for the windows but don't set the window sizes
    void SatisfyConstraints();
#endif // wxUSE_CONSTRAINTS

    // Send the wxWindowDestroyEvent
    void SendDestroyEvent();

    // returns the main window of composite control; this is the window
    // that FindFocus returns if the focus is in one of composite control's
    // windows
    virtual wxWindow *GetMainWindowOfCompositeControl()
        { return (wxWindow*)this; }

    // the window id - a number which uniquely identifies a window among
    // its siblings unless it is wxID_ANY
    wxWindowID           m_windowId;

    // the parent window of this window (or NULL) and the list of the children
    // of this window
    wxWindow            *m_parent;
    wxWindowList         m_children;

    // the minimal allowed size for the window (no minimal size if variable(s)
    // contain(s) wxDefaultCoord)
    int                  m_minWidth,
                         m_minHeight,
                         m_maxWidth,
                         m_maxHeight;

    // event handler for this window: usually is just 'this' but may be
    // changed with SetEventHandler()
    wxEvtHandler        *m_eventHandler;

#if wxUSE_VALIDATORS
    // associated validator or NULL if none
    wxValidator         *m_windowValidator;
#endif // wxUSE_VALIDATORS

#if wxUSE_DRAG_AND_DROP
    wxDropTarget        *m_dropTarget;
#endif // wxUSE_DRAG_AND_DROP

    // visual window attributes
    wxCursor             m_cursor;
    wxFont               m_font;                // see m_hasFont
    wxColour             m_backgroundColour,    //     m_hasBgCol
                         m_foregroundColour;    //     m_hasFgCol

#if wxUSE_CARET
    wxCaret             *m_caret;
#endif // wxUSE_CARET

    // the region which should be repainted in response to paint event
    wxRegion             m_updateRegion;

#if wxUSE_ACCEL
    // the accelerator table for the window which translates key strokes into
    // command events
    wxAcceleratorTable   m_acceleratorTable;
#endif // wxUSE_ACCEL

    // the tooltip for this window (may be NULL)
#if wxUSE_TOOLTIPS
    wxToolTip           *m_tooltip;
#endif // wxUSE_TOOLTIPS

    // constraints and sizers
#if wxUSE_CONSTRAINTS
    // the constraints for this window or NULL
    wxLayoutConstraints *m_constraints;

    // constraints this window is involved in
    wxWindowList        *m_constraintsInvolvedIn;
#endif // wxUSE_CONSTRAINTS

    // this window's sizer
    wxSizer             *m_windowSizer;

    // The sizer this window is a member of, if any
    wxSizer             *m_containingSizer;

    // Layout() window automatically when its size changes?
    bool                 m_autoLayout:1;

    // window state
    bool                 m_isShown:1;
    bool                 m_isEnabled:1;
    bool                 m_isBeingDeleted:1;

    // was the window colours/font explicitly changed by user?
    bool                 m_hasBgCol:1;
    bool                 m_hasFgCol:1;
    bool                 m_hasFont:1;

    // and should it be inherited by children?
    bool                 m_inheritBgCol:1;
    bool                 m_inheritFgCol:1;
    bool                 m_inheritFont:1;

    // window attributes
    long                 m_windowStyle,
                         m_exStyle;
    wxString             m_windowName;
    bool                 m_themeEnabled;
    wxBackgroundStyle    m_backgroundStyle;
#if wxUSE_PALETTE
    wxPalette            m_palette;
    bool                 m_hasCustomPalette;
#endif // wxUSE_PALETTE

#if wxUSE_ACCESSIBILITY
    wxAccessible*       m_accessible;
#endif

    // Virtual size (scrolling)
    wxSize                m_virtualSize;

    int                   m_minVirtualWidth;    // VirtualSizeHints
    int                   m_minVirtualHeight;
    int                   m_maxVirtualWidth;
    int                   m_maxVirtualHeight;

    wxWindowVariant       m_windowVariant ;

    // override this to change the default (i.e. used when no style is
    // specified) border for the window class
    virtual wxBorder GetDefaultBorder() const;

    // Get the default size for the new window if no explicit size given. TLWs
    // have their own default size so this is just for non top-level windows.
    static int WidthDefault(int w) { return w == wxDefaultCoord ? 20 : w; }
    static int HeightDefault(int h) { return h == wxDefaultCoord ? 20 : h; }


    // Used to save the results of DoGetBestSize so it doesn't need to be
    // recalculated each time the value is needed.
    wxSize m_bestSizeCache;

    // keep the old name for compatibility, at least until all the internal
    // usages of it are changed to SetBestFittingSize
    void SetBestSize(const wxSize& size) { SetBestFittingSize(size); }

    // set the initial window size if none is given (i.e. at least one of the
    // components of the size passed to ctor/Create() is wxDefaultCoord)
    //
    // normally just calls SetBestSize() for controls, but can be overridden
    // not to do it for the controls which have to do some additional
    // initialization (e.g. add strings to list box) before their best size
    // can be accurately calculated
    virtual void SetInitialBestSize(const wxSize& WXUNUSED(size)) {}



    // more pure virtual functions
    // ---------------------------

    // NB: we must have DoSomething() function when Something() is an overloaded
    //     method: indeed, we can't just have "virtual Something()" in case when
    //     the function is overloaded because then we'd have to make virtual all
    //     the variants (otherwise only the virtual function may be called on a
    //     pointer to derived class according to C++ rules) which is, in
    //     general, absolutely not needed. So instead we implement all
    //     overloaded Something()s in terms of DoSomething() which will be the
    //     only one to be virtual.

    // coordinates translation
    virtual void DoClientToScreen( int *x, int *y ) const = 0;
    virtual void DoScreenToClient( int *x, int *y ) const = 0;

    virtual wxHitTest DoHitTest(wxCoord x, wxCoord y) const;

    // capture/release the mouse, used by Capture/ReleaseMouse()
    virtual void DoCaptureMouse() = 0;
    virtual void DoReleaseMouse() = 0;

    // retrieve the position/size of the window
    virtual void DoGetPosition( int *x, int *y ) const = 0;
    virtual void DoGetSize( int *width, int *height ) const = 0;
    virtual void DoGetClientSize( int *width, int *height ) const = 0;

    // get the size which best suits the window: for a control, it would be
    // the minimal size which doesn't truncate the control, for a panel - the
    // same size as it would have after a call to Fit()
    virtual wxSize DoGetBestSize() const;

    // this is the virtual function to be overriden in any derived class which
    // wants to change how SetSize() or Move() works - it is called by all
    // versions of these functions in the base class
    virtual void DoSetSize(int x, int y,
                           int width, int height,
                           int sizeFlags = wxSIZE_AUTO) = 0;

    // same as DoSetSize() for the client size
    virtual void DoSetClientSize(int width, int height) = 0;

    // move the window to the specified location and resize it: this is called
    // from both DoSetSize() and DoSetClientSize() and would usually just
    // reposition this window except for composite controls which will want to
    // arrange themselves inside the given rectangle
    virtual void DoMoveWindow(int x, int y, int width, int height) = 0;

#if wxUSE_TOOLTIPS
    virtual void DoSetToolTip( wxToolTip *tip );
#endif // wxUSE_TOOLTIPS

#if wxUSE_MENUS
    virtual bool DoPopupMenu(wxMenu *menu, int x, int y) = 0;
#endif // wxUSE_MENUS

    // Makes an adjustment to the window position to make it relative to the
    // parents client area, e.g. if the parent is a frame with a toolbar, its
    // (0, 0) is just below the toolbar
    virtual void AdjustForParentClientOrigin(int& x, int& y,
                                             int sizeFlags = 0) const;

    // implements the window variants
    virtual void DoSetWindowVariant( wxWindowVariant variant ) ;

private:
    // contains the last id generated by NewControlId
    static int ms_lastControlId;

    // the stack of windows which have captured the mouse
    static struct WXDLLEXPORT wxWindowNext *ms_winCaptureNext;

    DECLARE_ABSTRACT_CLASS(wxWindowBase)
    DECLARE_NO_COPY_CLASS(wxWindowBase)
    DECLARE_EVENT_TABLE()
};

// ----------------------------------------------------------------------------
// now include the declaration of wxWindow class
// ----------------------------------------------------------------------------

// include the declaration of the platform-specific class
#if defined(__WXPALMOS__)
    #ifdef __WXUNIVERSAL__
        #define wxWindowNative wxWindowPalm
    #else // !wxUniv
        #define wxWindowPalm wxWindow
    #endif // wxUniv/!wxUniv
    #include "wx/palmos/window.h"
#elif defined(__WXMSW__)
    #ifdef __WXUNIVERSAL__
        #define wxWindowNative wxWindowMSW
    #else // !wxUniv
        #define wxWindowMSW wxWindow
    #endif // wxUniv/!wxUniv
    #include "wx/msw/window.h"
#elif defined(__WXMOTIF__)
    #include "wx/motif/window.h"
#elif defined(__WXGTK__)
    #ifdef __WXUNIVERSAL__
        #define wxWindowNative wxWindowGTK
    #else // !wxUniv
        #define wxWindowGTK wxWindow
    #endif // wxUniv
    #include "wx/gtk/window.h"
#elif defined(__WXX11__)
    #ifdef __WXUNIVERSAL__
        #define wxWindowNative wxWindowX11
    #else // !wxUniv
        #define wxWindowX11 wxWindow
    #endif // wxUniv
    #include "wx/x11/window.h"
#elif defined(__WXMGL__)
    #ifdef __WXUNIVERSAL__
        #define wxWindowNative wxWindowMGL
    #else // !wxUniv
        #define wxWindowMGL wxWindow
    #endif // wxUniv
    #include "wx/mgl/window.h"
#elif defined(__WXMAC__)
    #ifdef __WXUNIVERSAL__
        #define wxWindowNative wxWindowMac
    #else // !wxUniv
        #define wxWindowMac wxWindow
    #endif // wxUniv
    #include "wx/mac/window.h"
#elif defined(__WXCOCOA__)
    #ifdef __WXUNIVERSAL__
        #define wxWindowNative wxWindowCocoa
    #else // !wxUniv
        #define wxWindowCocoa wxWindow
    #endif // wxUniv
    #include "wx/cocoa/window.h"
#elif defined(__WXPM__)
    #ifdef __WXUNIVERSAL__
        #define wxWindowNative wxWindowOS2
    #else // !wxUniv
        #define wxWindowOS2 wxWindow
    #endif // wxUniv/!wxUniv
    #include "wx/os2/window.h"
#endif

// for wxUniversal, we now derive the real wxWindow from wxWindow<platform>,
// for the native ports we already have defined it above
#if defined(__WXUNIVERSAL__)
    #ifndef wxWindowNative
        #error "wxWindowNative must be defined above!"
    #endif

    #include "wx/univ/window.h"
#endif // wxUniv

// ----------------------------------------------------------------------------
// inline functions which couldn't be declared in the class body because of
// forward dependencies
// ----------------------------------------------------------------------------

inline wxWindow *wxWindowBase::GetGrandParent() const
{
    return m_parent ? m_parent->GetParent() : (wxWindow *)NULL;
}

// ----------------------------------------------------------------------------
// global functions
// ----------------------------------------------------------------------------

// Find the wxWindow at the current mouse position, also returning the mouse
// position.
WXDLLEXPORT extern wxWindow* wxFindWindowAtPointer(wxPoint& pt);

// Get the current mouse position.
WXDLLEXPORT extern wxPoint wxGetMousePosition();

// get the currently active window of this application or NULL
WXDLLEXPORT extern wxWindow *wxGetActiveWindow();

// get the (first) top level parent window
WXDLLEXPORT wxWindow* wxGetTopLevelParent(wxWindow *win);

// deprecated (doesn't start with 'wx' prefix), use wxWindow::NewControlId()
inline int NewControlId() { return wxWindowBase::NewControlId(); }

#if wxUSE_ACCESSIBILITY
// ----------------------------------------------------------------------------
// accessible object for windows
// ----------------------------------------------------------------------------

class WXDLLEXPORT wxWindowAccessible: public wxAccessible
{
public:
    wxWindowAccessible(wxWindow* win): wxAccessible(win) { if (win) win->SetAccessible(this); }
    virtual ~wxWindowAccessible() {}

// Overridables

        // Can return either a child object, or an integer
        // representing the child element, starting from 1.
    virtual wxAccStatus HitTest(const wxPoint& pt, int* childId, wxAccessible** childObject);

        // Returns the rectangle for this object (id = 0) or a child element (id > 0).
    virtual wxAccStatus GetLocation(wxRect& rect, int elementId);

        // Navigates from fromId to toId/toObject.
    virtual wxAccStatus Navigate(wxNavDir navDir, int fromId,
                int* toId, wxAccessible** toObject);

        // Gets the name of the specified object.
    virtual wxAccStatus GetName(int childId, wxString* name);

        // Gets the number of children.
    virtual wxAccStatus GetChildCount(int* childCount);

        // Gets the specified child (starting from 1).
        // If *child is NULL and return value is wxACC_OK,
        // this means that the child is a simple element and
        // not an accessible object.
    virtual wxAccStatus GetChild(int childId, wxAccessible** child);

        // Gets the parent, or NULL.
    virtual wxAccStatus GetParent(wxAccessible** parent);

        // Performs the default action. childId is 0 (the action for this object)
        // or > 0 (the action for a child).
        // Return wxACC_NOT_SUPPORTED if there is no default action for this
        // window (e.g. an edit control).
    virtual wxAccStatus DoDefaultAction(int childId);

        // Gets the default action for this object (0) or > 0 (the action for a child).
        // Return wxACC_OK even if there is no action. actionName is the action, or the empty
        // string if there is no action.
        // The retrieved string describes the action that is performed on an object,
        // not what the object does as a result. For example, a toolbar button that prints
        // a document has a default action of "Press" rather than "Prints the current document."
    virtual wxAccStatus GetDefaultAction(int childId, wxString* actionName);

        // Returns the description for this object or a child.
    virtual wxAccStatus GetDescription(int childId, wxString* description);

        // Returns help text for this object or a child, similar to tooltip text.
    virtual wxAccStatus GetHelpText(int childId, wxString* helpText);

        // Returns the keyboard shortcut for this object or child.
        // Return e.g. ALT+K
    virtual wxAccStatus GetKeyboardShortcut(int childId, wxString* shortcut);

        // Returns a role constant.
    virtual wxAccStatus GetRole(int childId, wxAccRole* role);

        // Returns a state constant.
    virtual wxAccStatus GetState(int childId, long* state);

        // Returns a localized string representing the value for the object
        // or child.
    virtual wxAccStatus GetValue(int childId, wxString* strValue);

        // Selects the object or child.
    virtual wxAccStatus Select(int childId, wxAccSelectionFlags selectFlags);

        // Gets the window with the keyboard focus.
        // If childId is 0 and child is NULL, no object in
        // this subhierarchy has the focus.
        // If this object has the focus, child should be 'this'.
    virtual wxAccStatus GetFocus(int* childId, wxAccessible** child);

        // Gets a variant representing the selected children
        // of this object.
        // Acceptable values:
        // - a null variant (IsNull() returns true)
        // - a list variant (GetType() == wxT("list")
        // - an integer representing the selected child element,
        //   or 0 if this object is selected (GetType() == wxT("long")
        // - a "void*" pointer to a wxAccessible child object
    virtual wxAccStatus GetSelections(wxVariant* selections);
};

#endif // wxUSE_ACCESSIBILITY


#endif
    // _WX_WINDOW_H_BASE_

