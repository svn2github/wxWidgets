/////////////////////////////////////////////////////////////////////////////
// Name:        choice.cpp
// Purpose:     wxChoice
// Author:      Julian Smart
// Modified by: Vadim Zeitlin to derive from wxChoiceBase
// Created:     04/01/98
// RCS-ID:      $Id$
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma implementation "choice.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#if wxUSE_CHOICE

#ifndef WX_PRECOMP
    #include "wx/choice.h"
    #include "wx/utils.h"
    #include "wx/log.h"
    #include "wx/brush.h"
    #include "wx/settings.h"
#endif

#include "wx/msw/private.h"

#if wxUSE_EXTENDED_RTTI
WX_DEFINE_FLAGS( wxChoiceStyle )

WX_BEGIN_FLAGS( wxChoiceStyle )
    // new style border flags, we put them first to
    // use them for streaming out
    WX_FLAGS_MEMBER(wxBORDER_SIMPLE)
    WX_FLAGS_MEMBER(wxBORDER_SUNKEN)
    WX_FLAGS_MEMBER(wxBORDER_DOUBLE)
    WX_FLAGS_MEMBER(wxBORDER_RAISED)
    WX_FLAGS_MEMBER(wxBORDER_STATIC)
    WX_FLAGS_MEMBER(wxBORDER_NONE)
    
    // old style border flags
    WX_FLAGS_MEMBER(wxSIMPLE_BORDER)
    WX_FLAGS_MEMBER(wxSUNKEN_BORDER)
    WX_FLAGS_MEMBER(wxDOUBLE_BORDER)
    WX_FLAGS_MEMBER(wxRAISED_BORDER)
    WX_FLAGS_MEMBER(wxSTATIC_BORDER)
    WX_FLAGS_MEMBER(wxNO_BORDER)

    // standard window styles
    WX_FLAGS_MEMBER(wxTAB_TRAVERSAL)
    WX_FLAGS_MEMBER(wxCLIP_CHILDREN)
    WX_FLAGS_MEMBER(wxTRANSPARENT_WINDOW)
    WX_FLAGS_MEMBER(wxWANTS_CHARS)
    WX_FLAGS_MEMBER(wxNO_FULL_REPAINT_ON_RESIZE)
    WX_FLAGS_MEMBER(wxALWAYS_SHOW_SB )
    WX_FLAGS_MEMBER(wxVSCROLL)
    WX_FLAGS_MEMBER(wxHSCROLL)

WX_END_FLAGS( wxChoiceStyle )

IMPLEMENT_DYNAMIC_CLASS_XTI(wxChoice, wxControl,"wx/choice.h")

WX_BEGIN_PROPERTIES_TABLE(wxChoice)
	WX_DELEGATE( OnSelect , wxEVT_COMMAND_CHOICE_SELECTED , wxCommandEvent )

    WX_PROPERTY( Font , wxFont , SetFont , GetFont  , , 0 /*flags*/ , wxT("Helpstring") , wxT("group"))
    WX_PROPERTY_COLLECTION( Choices , wxArrayString , wxString , AppendString , GetStrings , 0 /*flags*/ , wxT("Helpstring") , wxT("group"))
	WX_PROPERTY( Selection ,int, SetSelection, GetSelection, , 0 /*flags*/ , wxT("Helpstring") , wxT("group"))
    WX_PROPERTY_FLAGS( WindowStyle , wxChoiceStyle , long , SetWindowStyleFlag , GetWindowStyleFlag , , 0 /*flags*/ , wxT("Helpstring") , wxT("group")) // style
WX_END_PROPERTIES_TABLE()

WX_BEGIN_HANDLERS_TABLE(wxChoice)
WX_END_HANDLERS_TABLE()

WX_CONSTRUCTOR_4( wxChoice , wxWindow* , Parent , wxWindowID , Id , wxPoint , Position , wxSize , Size ) 
#else
IMPLEMENT_DYNAMIC_CLASS(wxChoice, wxControl)
#endif
/*
	TODO PROPERTIES
		selection (long)
		content (list)
			item
*/

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// creation
// ----------------------------------------------------------------------------

bool wxChoice::Create(wxWindow *parent,
                      wxWindowID id,
                      const wxPoint& pos,
                      const wxSize& size,
                      int n, const wxString choices[],
                      long style,
                      const wxValidator& validator,
                      const wxString& name)
{
    if ( !CreateControl(parent, id, pos, size, style, validator, name) )
        return FALSE;

    long msStyle = WS_CHILD | CBS_DROPDOWNLIST | WS_TABSTOP | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL /* | WS_CLIPSIBLINGS */;
    if ( style & wxCB_SORT )
        msStyle |= CBS_SORT;

    if ( style & wxCLIP_SIBLINGS )
        msStyle |= WS_CLIPSIBLINGS;


    // Experience shows that wxChoice vs. wxComboBox distinction confuses
    // quite a few people - try to help them
    wxASSERT_MSG( !(style & wxCB_DROPDOWN) &&
                  !(style & wxCB_READONLY) &&
                  !(style & wxCB_SIMPLE),
                  _T("this style flag is ignored by wxChoice, you ")
                  _T("probably want to use a wxComboBox") );

    if ( !MSWCreateControl(wxT("COMBOBOX"), msStyle) )
        return FALSE;

    // A choice/combobox normally has a white background (or other, depending
    // on global settings) rather than inheriting the parent's background colour.
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

    for ( int i = 0; i < n; i++ )
    {
        Append(choices[i]);
    }

    SetSize(pos.x, pos.y, size.x, size.y);

    return TRUE;
}

wxChoice::~wxChoice()
{
    Free();
}

// ----------------------------------------------------------------------------
// adding/deleting items to/from the list
// ----------------------------------------------------------------------------

int wxChoice::DoAppend(const wxString& item)
{
    int n = (int)SendMessage(GetHwnd(), CB_ADDSTRING, 0, (LONG)item.c_str());
    if ( n == CB_ERR )
    {
        wxLogLastError(wxT("SendMessage(CB_ADDSTRING)"));
    }

    return n;
}

int wxChoice::DoInsert(const wxString& item, int pos)
{
    wxCHECK_MSG(!(GetWindowStyle() & wxCB_SORT), -1, wxT("can't insert into sorted list"));
    wxCHECK_MSG((pos>=0) && (pos<=GetCount()), -1, wxT("invalid index"));

    int n = (int)SendMessage(GetHwnd(), CB_INSERTSTRING, pos, (LONG)item.c_str());
    if ( n == CB_ERR )
    {
        wxLogLastError(wxT("SendMessage(CB_INSERTSTRING)"));
    }

    return n;
}

void wxChoice::Delete(int n)
{
    wxCHECK_RET( n < GetCount(), wxT("invalid item index in wxChoice::Delete") );

    if ( HasClientObjectData() )
    {
        delete GetClientObject(n);
    }

    SendMessage(GetHwnd(), CB_DELETESTRING, n, 0);
}

void wxChoice::Clear()
{
    Free();

    SendMessage(GetHwnd(), CB_RESETCONTENT, 0, 0);
}

void wxChoice::Free()
{
    if ( HasClientObjectData() )
    {
        size_t count = GetCount();
        for ( size_t n = 0; n < count; n++ )
        {
            delete GetClientObject(n);
        }
    }
}

// ----------------------------------------------------------------------------
// selection
// ----------------------------------------------------------------------------

int wxChoice::GetSelection() const
{
    return (int)SendMessage(GetHwnd(), CB_GETCURSEL, 0, 0);
}

void wxChoice::SetSelection(int n)
{
    SendMessage(GetHwnd(), CB_SETCURSEL, n, 0);
}

// ----------------------------------------------------------------------------
// string list functions
// ----------------------------------------------------------------------------

int wxChoice::GetCount() const
{
    return (int)SendMessage(GetHwnd(), CB_GETCOUNT, 0, 0);
}

int wxChoice::FindString(const wxString& s) const
{
#if defined(__WATCOMC__) && defined(__WIN386__)
    // For some reason, Watcom in WIN386 mode crashes in the CB_FINDSTRINGEXACT message.
    // wxChoice::Do it the long way instead.
    int count = GetCount();
    for ( int i = 0; i < count; i++ )
    {
        // as CB_FINDSTRINGEXACT is case insensitive, be case insensitive too
        if ( GetString(i).IsSameAs(s, FALSE) )
            return i;
    }

    return wxNOT_FOUND;
#else // !Watcom
    int pos = (int)SendMessage(GetHwnd(), CB_FINDSTRINGEXACT,
                               (WPARAM)-1, (LPARAM)s.c_str());

    return pos == LB_ERR ? wxNOT_FOUND : pos;
#endif // Watcom/!Watcom
}

void wxChoice::SetString(int n, const wxString& s)
{
    wxCHECK_RET( n >= 0 && n < GetCount(),
                 wxT("invalid item index in wxChoice::SetString") );

    // we have to delete and add back the string as there is no way to change a
    // string in place

    // we need to preserve the client data
    void *data;
    if ( m_clientDataItemsType != wxClientData_None )
    {
        data = DoGetItemClientData(n);
    }
    else // no client data
    {
        data = NULL;
    }

    ::SendMessage(GetHwnd(), CB_DELETESTRING, n, 0);
    ::SendMessage(GetHwnd(), CB_INSERTSTRING, n, (LPARAM)s.c_str() );

    if ( data )
    {
        DoSetItemClientData(n, data);
    }
    //else: it's already NULL by default
}

wxString wxChoice::GetString(int n) const
{
    int len = (int)::SendMessage(GetHwnd(), CB_GETLBTEXTLEN, n, 0);

    wxString str;
    if ( len != CB_ERR && len > 0 )
    {
        if ( ::SendMessage
               (
                GetHwnd(),
                CB_GETLBTEXT,
                n,
                (LPARAM)(wxChar *)wxStringBuffer(str, len)
               ) == CB_ERR )
        {
            wxLogLastError(wxT("SendMessage(CB_GETLBTEXT)"));
        }
    }

    return str;
}

// ----------------------------------------------------------------------------
// client data
// ----------------------------------------------------------------------------

void wxChoice::DoSetItemClientData( int n, void* clientData )
{
    if ( ::SendMessage(GetHwnd(), CB_SETITEMDATA,
                       n, (LPARAM)clientData) == CB_ERR )
    {
        wxLogLastError(wxT("CB_SETITEMDATA"));
    }
}

void* wxChoice::DoGetItemClientData( int n ) const
{
    LPARAM rc = SendMessage(GetHwnd(), CB_GETITEMDATA, n, 0);
    if ( rc == CB_ERR )
    {
        wxLogLastError(wxT("CB_GETITEMDATA"));

        // unfortunately, there is no way to return an error code to the user
        rc = (LPARAM) NULL;
    }

    return (void *)rc;
}

void wxChoice::DoSetItemClientObject( int n, wxClientData* clientData )
{
    DoSetItemClientData(n, clientData);
}

wxClientData* wxChoice::DoGetItemClientObject( int n ) const
{
    return (wxClientData *)DoGetItemClientData(n);
}

// ----------------------------------------------------------------------------
// wxMSW specific helpers
// ----------------------------------------------------------------------------

void wxChoice::DoMoveWindow(int x, int y, int width, int height)
{
    // here is why this is necessary: if the width is negative, the combobox
    // window proc makes the window of the size width*height instead of
    // interpreting height in the usual manner (meaning the height of the drop
    // down list - usually the height specified in the call to MoveWindow()
    // will not change the height of combo box per se)
    //
    // this behaviour is not documented anywhere, but this is just how it is
    // here (NT 4.4) and, anyhow, the check shouldn't hurt - however without
    // the check, constraints/sizers using combos may break the height
    // constraint will have not at all the same value as expected
    if ( width < 0 )
        return;

    wxControl::DoMoveWindow(x, y, width, height);
}

void wxChoice::DoSetSize(int x, int y,
                         int width, int WXUNUSED(height),
                         int sizeFlags)
{
    // Ignore height parameter because height doesn't mean 'initially
    // displayed' height, it refers to the drop-down menu as well. The
    // wxWindows interpretation is different; also, getting the size returns
    // the _displayed_ size (NOT the drop down menu size) so
    // setting-getting-setting size would not work.

    wxControl::DoSetSize(x, y, width, -1, sizeFlags);
}

wxSize wxChoice::DoGetBestSize() const
{
    // find the widest string
    int wLine;
    int wChoice = 0;
    int nItems = GetCount();
    for ( int i = 0; i < nItems; i++ )
    {
        wxString str(GetString(i));
        GetTextExtent(str, &wLine, NULL);
        if ( wLine > wChoice )
            wChoice = wLine;
    }

    // give it some reasonable default value if there are no strings in the
    // list
    if ( wChoice == 0 )
        wChoice = 100;

    // the combobox should be larger than the widest string
    int cx, cy;
    wxGetCharSize(GetHWND(), &cx, &cy, &GetFont());

    wChoice += 5*cx;

    // Choice drop-down list depends on number of items (limited to 10)
    size_t nStrings = nItems == 0 ? 10 : wxMin(10, nItems) + 1;
    int hChoice = EDIT_HEIGHT_FROM_CHAR_HEIGHT(cy)*nStrings;

    return wxSize(wChoice, hChoice);
}

long wxChoice::MSWWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam)
{
    if ( nMsg == WM_LBUTTONUP )
    {
        int x = (int)LOWORD(lParam);
        int y = (int)HIWORD(lParam);

        // Ok, this is truly weird, but if a panel with a wxChoice loses the
        // focus, then you get a *fake* WM_LBUTTONUP message with x = 65535 and
        // y = 65535. Filter out this nonsense.
        //
        // VZ: I'd like to know how to reproduce this please...
        if ( x == 65535 && y == 65535 )
            return 0;
    }

    return wxWindow::MSWWindowProc(nMsg, wParam, lParam);
}

bool wxChoice::MSWCommand(WXUINT param, WXWORD WXUNUSED(id))
{
    if ( param != CBN_SELCHANGE)
    {
        // "selection changed" is the only event we're after
        return FALSE;
    }

    int n = GetSelection();
    if (n > -1)
    {
        wxCommandEvent event(wxEVT_COMMAND_CHOICE_SELECTED, m_windowId);
        event.SetInt(n);
        event.SetEventObject(this);
        event.SetString(GetStringSelection());
        if ( HasClientObjectData() )
            event.SetClientObject( GetClientObject(n) );
        else if ( HasClientUntypedData() )
            event.SetClientData( GetClientData(n) );
        ProcessCommand(event);
    }

    return TRUE;
}

WXHBRUSH wxChoice::OnCtlColor(WXHDC pDC, WXHWND WXUNUSED(pWnd), WXUINT WXUNUSED(nCtlColor),
                               WXUINT WXUNUSED(message),
                               WXWPARAM WXUNUSED(wParam),
                               WXLPARAM WXUNUSED(lParam)
     )
{
    HDC hdc = (HDC)pDC;
    wxColour colBack = GetBackgroundColour();

    if (!IsEnabled())
        colBack = wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE);

    ::SetBkColor(hdc, wxColourToRGB(colBack));
    ::SetTextColor(hdc, wxColourToRGB(GetForegroundColour()));

    wxBrush *brush = wxTheBrushList->FindOrCreateBrush(colBack, wxSOLID);

    return (WXHBRUSH)brush->GetResourceHandle();
}

#endif // wxUSE_CHOICE
