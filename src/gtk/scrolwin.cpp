/////////////////////////////////////////////////////////////////////////////
// Name:        gtk/scrolwin.cpp
// Purpose:     wxScrolledWindow implementation
// Author:      Julian Smart
// Modified by:
// Created:     01/02/97
// RCS-ID:      $Id$
// Copyright:   (c) Julian Smart and Markus Holzem
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#ifdef __GNUG__
    #pragma implementation "scrolwin.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "wx/utils.h"
#include "wx/dcclient.h"

#include "wx/gtk/scrolwin.h"
#include "wx/panel.h"

#include <gtk/gtk.h>
#include "wx/gtk/win_gtk.h"

// ----------------------------------------------------------------------------
// event tables
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(wxScrolledWindow, wxPanel)
    EVT_SCROLLWIN(wxScrolledWindow::OnScroll)
    EVT_SIZE(wxScrolledWindow::OnSize)
    EVT_PAINT(wxScrolledWindow::OnPaint)
    EVT_CHAR(wxScrolledWindow::OnChar)
END_EVENT_TABLE()

IMPLEMENT_DYNAMIC_CLASS(wxScrolledWindow, wxPanel)

// ============================================================================
// implementation
// ============================================================================

//-----------------------------------------------------------------------------
// data
//-----------------------------------------------------------------------------

extern bool       g_blockEventsOnDrag;

//-----------------------------------------------------------------------------
// idle system
//-----------------------------------------------------------------------------

extern void wxapp_install_idle_handler();
extern bool g_isIdle;

//-----------------------------------------------------------------------------
// "value_changed" from m_vAdjust
//-----------------------------------------------------------------------------

static void gtk_scrolled_window_vscroll_callback( GtkAdjustment *adjust, wxScrolledWindow *win )
{
    if (g_isIdle)
        wxapp_install_idle_handler();

    if (g_blockEventsOnDrag) return;

    if (!win->m_hasVMT) return;

    win->GtkVScroll( adjust->value );
}

//-----------------------------------------------------------------------------
// "value_changed" from m_hAdjust
//-----------------------------------------------------------------------------

static void gtk_scrolled_window_hscroll_callback( GtkAdjustment *adjust, wxScrolledWindow *win )
{
    if (g_isIdle)
        wxapp_install_idle_handler();

    if (g_blockEventsOnDrag) return;
    if (!win->m_hasVMT) return;

    win->GtkHScroll( adjust->value );
}

//-----------------------------------------------------------------------------
// InsertChild for wxScrolledWindow
//-----------------------------------------------------------------------------

static void wxInsertChildInScrolledWindow( wxWindow* parent, wxWindow* child )
{
    // The window might have been scrolled already, do we
    // have to adapt the position.
    GtkPizza *pizza = GTK_PIZZA(parent->m_wxwindow);
    child->m_x += pizza->xoffset;
    child->m_y += pizza->yoffset;

    gtk_pizza_put( GTK_PIZZA(parent->m_wxwindow),
                     GTK_WIDGET(child->m_widget),
                     child->m_x,
                     child->m_y,
                     child->m_width,
                     child->m_height );
}

// ----------------------------------------------------------------------------
// wxScrolledWindow creation
// ----------------------------------------------------------------------------

void wxScrolledWindow::Init()
{
    m_xScrollPixelsPerLine = 0;
    m_yScrollPixelsPerLine = 0;
    m_xScrollingEnabled = TRUE;
    m_yScrollingEnabled = TRUE;
    m_xScrollPosition = 0;
    m_yScrollPosition = 0;
    m_xScrollLines = 0;
    m_yScrollLines = 0;
    m_xScrollLinesPerPage = 0;
    m_yScrollLinesPerPage = 0;
    m_targetWindow = (wxWindow*) NULL;
    m_scaleX = 1.0;
    m_scaleY = 1.0;
    m_hasScrolling = TRUE;
}

bool wxScrolledWindow::Create(wxWindow *parent,
                              wxWindowID id,
                              const wxPoint& pos,
                              const wxSize& size,
                              long style,
                              const wxString& name)
{
    Init();

    if (!PreCreation( parent, pos, size ) ||
        !CreateBase( parent, id, pos, size, style, wxDefaultValidator, name ))
    {
        wxFAIL_MSG( wxT("wxWindow creation failed") );
        return FALSE;
    }

    m_insertCallback = wxInsertChildInScrolledWindow;
    
    m_targetWindow = this;

    m_widget = gtk_scrolled_window_new( (GtkAdjustment *) NULL, (GtkAdjustment *) NULL );
    GTK_WIDGET_UNSET_FLAGS( m_widget, GTK_CAN_FOCUS );

    GtkScrolledWindow *scrolledWindow = GTK_SCROLLED_WINDOW(m_widget);

    GtkScrolledWindowClass *scroll_class = GTK_SCROLLED_WINDOW_CLASS( GTK_OBJECT_GET_CLASS(m_widget) );
    scroll_class->scrollbar_spacing = 0;

    gtk_scrolled_window_set_policy( scrolledWindow, GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC );

    m_hAdjust = gtk_range_get_adjustment( GTK_RANGE(scrolledWindow->hscrollbar) );
    m_vAdjust = gtk_range_get_adjustment( GTK_RANGE(scrolledWindow->vscrollbar) );

    m_wxwindow = gtk_pizza_new();

    gtk_container_add( GTK_CONTAINER(m_widget), m_wxwindow );

    GtkPizza *pizza = GTK_PIZZA(m_wxwindow);

    if (HasFlag(wxRAISED_BORDER))
    {
        gtk_pizza_set_shadow_type( pizza, GTK_MYSHADOW_OUT );
    }
    else if (HasFlag(wxSUNKEN_BORDER))
    {
        gtk_pizza_set_shadow_type( pizza, GTK_MYSHADOW_IN );
    }
    else if (HasFlag(wxSIMPLE_BORDER))
    {
        gtk_pizza_set_shadow_type( pizza, GTK_MYSHADOW_THIN );
    }
    else
    {
        gtk_pizza_set_shadow_type( pizza, GTK_MYSHADOW_NONE );
    }

    GTK_WIDGET_SET_FLAGS( m_wxwindow, GTK_CAN_FOCUS );
    m_acceptsFocus = TRUE;

    // I _really_ don't want scrollbars in the beginning
    m_vAdjust->lower = 0.0;
    m_vAdjust->upper = 1.0;
    m_vAdjust->value = 0.0;
    m_vAdjust->step_increment = 1.0;
    m_vAdjust->page_increment = 1.0;
    gtk_signal_emit_by_name( GTK_OBJECT(m_vAdjust), "changed" );
    m_hAdjust->lower = 0.0;
    m_hAdjust->upper = 1.0;
    m_hAdjust->value = 0.0;
    m_hAdjust->step_increment = 1.0;
    m_hAdjust->page_increment = 1.0;
    gtk_signal_emit_by_name( GTK_OBJECT(m_hAdjust), "changed" );

    // Handlers for new scrollbar values
    GtkVConnectEvent();
    GtkHConnectEvent();

    gtk_widget_show( m_wxwindow );

    if (m_parent)
        m_parent->DoAddChild( this );

    PostCreation();

    Show( TRUE );

    return TRUE;
}

// ----------------------------------------------------------------------------
// setting scrolling parameters
// ----------------------------------------------------------------------------

/*
 * pixelsPerUnitX/pixelsPerUnitY: number of pixels per unit (e.g. pixels per text line)
 * noUnitsX/noUnitsY:        : no. units per scrollbar
 */
void wxScrolledWindow::SetScrollbars (int pixelsPerUnitX, int pixelsPerUnitY,
               int noUnitsX, int noUnitsY,
               int xPos, int yPos, bool noRefresh )
{
    m_xScrollPixelsPerLine = pixelsPerUnitX;
    m_yScrollPixelsPerLine = pixelsPerUnitY;
    m_xScrollPosition = xPos;
    m_yScrollPosition = yPos;
    m_xScrollLines = noUnitsX;
    m_yScrollLines = noUnitsY;
    
    m_hAdjust->lower = 0.0;
    m_hAdjust->upper = noUnitsX;
    m_hAdjust->value = xPos;
    m_hAdjust->step_increment = 1.0;
    m_hAdjust->page_increment = 2.0;

    m_vAdjust->lower = 0.0;
    m_vAdjust->upper = noUnitsY;
    m_vAdjust->value = yPos;
    m_vAdjust->step_increment = 1.0;
    m_vAdjust->page_increment = 2.0;
    
    AdjustScrollbars();
}

void wxScrolledWindow::AdjustScrollbars()
{
    int w, h;
    m_targetWindow->GetClientSize( &w, &h );
    
    if (m_xScrollPixelsPerLine == 0)
        m_hAdjust->page_size = 1.0;
    else
        m_hAdjust->page_size = (w / m_xScrollPixelsPerLine);
        
    if (m_yScrollPixelsPerLine == 0)
        m_vAdjust->page_size = 1.0;
    else
        m_vAdjust->page_size = (h / m_yScrollPixelsPerLine);
    
    m_xScrollLinesPerPage = (int)(m_hAdjust->page_size + 0.5);
    m_yScrollLinesPerPage = (int)(m_vAdjust->page_size + 0.5);
    
    gtk_signal_emit_by_name( GTK_OBJECT(m_vAdjust), "changed" );
    gtk_signal_emit_by_name( GTK_OBJECT(m_hAdjust), "changed" );
}

// ----------------------------------------------------------------------------
// target window handling
// ----------------------------------------------------------------------------

void wxScrolledWindow::SetTargetWindow( wxWindow *target )
{
    wxASSERT_MSG( target, wxT("target window must not be NULL") );
    m_targetWindow = target;
}

wxWindow *wxScrolledWindow::GetTargetWindow()
{
    return m_targetWindow;
}

// Override this function if you don't want to have wxScrolledWindow
// automatically change the origin according to the scroll position.
void wxScrolledWindow::PrepareDC(wxDC& dc)
{
    dc.SetDeviceOrigin( -m_xScrollPosition * m_xScrollPixelsPerLine,
                        -m_yScrollPosition * m_yScrollPixelsPerLine );
}

void wxScrolledWindow::GetScrollPixelsPerUnit (int *x_unit, int *y_unit) const
{
    if ( x_unit )
        *x_unit = m_xScrollPixelsPerLine;
    if ( y_unit )
        *y_unit = m_yScrollPixelsPerLine;
}

int wxScrolledWindow::GetScrollPageSize(int orient) const
{
    if ( orient == wxHORIZONTAL )
        return m_xScrollLinesPerPage;
    else
        return m_yScrollLinesPerPage;
}

void wxScrolledWindow::SetScrollPageSize(int orient, int pageSize)
{
    if ( orient == wxHORIZONTAL )
        m_xScrollLinesPerPage = pageSize;
    else
        m_yScrollLinesPerPage = pageSize;
}

void wxScrolledWindow::OnScroll(wxScrollWinEvent& event)
{
    int orient = event.GetOrientation();

    int nScrollInc = CalcScrollInc(event);
    if (nScrollInc == 0) return;

    if (orient == wxHORIZONTAL)
    {
        int newPos = m_xScrollPosition + nScrollInc;
        SetScrollPos(wxHORIZONTAL, newPos, TRUE );
    }
    else
    {
        int newPos = m_yScrollPosition + nScrollInc;
        SetScrollPos(wxVERTICAL, newPos, TRUE );
    }

    if (orient == wxHORIZONTAL)
    {
        m_xScrollPosition += nScrollInc;
    }
    else
    {
        m_yScrollPosition += nScrollInc;
    }

    if (orient == wxHORIZONTAL)
    {
       if (m_xScrollingEnabled)
            m_targetWindow->ScrollWindow(-m_xScrollPixelsPerLine * nScrollInc, 0, (const wxRect *) NULL);
       else
            m_targetWindow->Refresh();
    }
    else
    {
        if (m_yScrollingEnabled)
            m_targetWindow->ScrollWindow(0, -m_yScrollPixelsPerLine * nScrollInc, (const wxRect *) NULL);
        else
            m_targetWindow->Refresh();
    }
}

void wxScrolledWindow::Scroll( int x_pos, int y_pos )
{
    if (!m_targetWindow)
        return;

    if (((x_pos == -1) || (x_pos == m_xScrollPosition)) &&
        ((y_pos == -1) || (y_pos == m_yScrollPosition))) return;

    if ((x_pos != -1) && (m_xScrollPixelsPerLine))
    {
        int max = (int)(m_hAdjust->upper - m_hAdjust->page_size + 0.5);
        if (max < 0) max = 0;
        if (x_pos > max) x_pos = max;
        if (x_pos < 0) x_pos = 0;
            
        int old_x = m_xScrollPosition;
        m_xScrollPosition = x_pos;
        m_hAdjust->value = x_pos;
        
        m_targetWindow->ScrollWindow( (old_x-m_xScrollPosition)*m_xScrollPixelsPerLine, 0 );
        
        // Just update the scrollbar, don't send any wxWindows event
        GtkHDisconnectEvent();
        gtk_signal_emit_by_name( GTK_OBJECT(m_hAdjust), "value_changed" );
        GtkHConnectEvent();
    }
    
    if ((y_pos != -1) && (m_yScrollPixelsPerLine))
    {
        int max = (int)(m_vAdjust->upper - m_vAdjust->page_size + 0.5);
        if (max < 0) max = 0;
        if (y_pos > max) y_pos = max;
        if (y_pos < 0) y_pos = 0;
            
        int old_y = m_yScrollPosition;
        m_yScrollPosition = y_pos;
        m_vAdjust->value = y_pos;
        
        m_targetWindow->ScrollWindow( 0, (old_y-m_yScrollPosition)*m_yScrollPixelsPerLine );
        
        // Just update the scrollbar, don't send any wxWindows event
        GtkVDisconnectEvent();
        gtk_signal_emit_by_name( GTK_OBJECT(m_vAdjust), "value_changed" );
        GtkVConnectEvent();
    }
}

void wxScrolledWindow::GtkVScroll( float value )
{
    if (!m_targetWindow)
        return;

    if (m_yScrollPixelsPerLine == 0)
        return;
    
    int y_pos = (int)(value+0.5);
    
    if (y_pos == m_yScrollPosition)
        return;
    
    GtkScrolledWindow *scrolledWindow = GTK_SCROLLED_WINDOW(m_widget);
    GtkRange *range = GTK_RANGE(scrolledWindow->vscrollbar);
    
    wxEventType command = wxEVT_SCROLLWIN_THUMBTRACK;
    if      (range->scroll_type == GTK_SCROLL_STEP_BACKWARD) command = wxEVT_SCROLLWIN_LINEUP;
    else if (range->scroll_type == GTK_SCROLL_STEP_FORWARD)  command = wxEVT_SCROLLWIN_LINEDOWN;
    else if (range->scroll_type == GTK_SCROLL_PAGE_BACKWARD) command = wxEVT_SCROLLWIN_PAGEUP;
    else if (range->scroll_type == GTK_SCROLL_PAGE_FORWARD)  command = wxEVT_SCROLLWIN_PAGEDOWN;

    wxScrollWinEvent event( command, y_pos, wxVERTICAL );
    event.SetEventObject( this );
    GetEventHandler()->ProcessEvent( event );
}

void wxScrolledWindow::GtkHScroll( float value )
{
    if (!m_targetWindow)
        return;
        
    if (m_xScrollPixelsPerLine == 0)
        return;
    
    int x_pos = (int)(value+0.5);

    if (x_pos == m_xScrollPosition)
        return;

    GtkScrolledWindow *scrolledWindow = GTK_SCROLLED_WINDOW(m_widget);
    GtkRange *range = GTK_RANGE(scrolledWindow->hscrollbar);
    
    wxEventType command = wxEVT_SCROLLWIN_THUMBTRACK;
    if      (range->scroll_type == GTK_SCROLL_STEP_BACKWARD) command = wxEVT_SCROLLWIN_LINEUP;
    else if (range->scroll_type == GTK_SCROLL_STEP_FORWARD)  command = wxEVT_SCROLLWIN_LINEDOWN;
    else if (range->scroll_type == GTK_SCROLL_PAGE_BACKWARD) command = wxEVT_SCROLLWIN_PAGEUP;
    else if (range->scroll_type == GTK_SCROLL_PAGE_FORWARD)  command = wxEVT_SCROLLWIN_PAGEDOWN;

    wxScrollWinEvent event( command, x_pos, wxHORIZONTAL );
    event.SetEventObject( this );
    GetEventHandler()->ProcessEvent( event );
}

void wxScrolledWindow::EnableScrolling (bool x_scroll, bool y_scroll)
{
    m_xScrollingEnabled = x_scroll;
    m_yScrollingEnabled = y_scroll;
}

void wxScrolledWindow::GetVirtualSize (int *x, int *y) const
{
    if ( x )
        *x = m_xScrollPixelsPerLine * m_xScrollLines;
    if ( y )
        *y = m_yScrollPixelsPerLine * m_yScrollLines;
}

// Where the current view starts from
void wxScrolledWindow::GetViewStart (int *x, int *y) const
{
    if ( x )
        *x = m_xScrollPosition;
    if ( y )
        *y = m_yScrollPosition;
}

void wxScrolledWindow::CalcScrolledPosition(int x, int y, int *xx, int *yy) const
{
    if ( xx )
        *xx = x - m_xScrollPosition * m_xScrollPixelsPerLine;
    if ( yy )
        *yy = y - m_yScrollPosition * m_yScrollPixelsPerLine;
}

void wxScrolledWindow::CalcUnscrolledPosition(int x, int y, int *xx, int *yy) const
{
    if ( xx )
        *xx = x + m_xScrollPosition * m_xScrollPixelsPerLine;
    if ( yy )
        *yy = y + m_yScrollPosition * m_yScrollPixelsPerLine;
}

int wxScrolledWindow::CalcScrollInc(wxScrollWinEvent& event)
{
    int pos = event.GetPosition();
    int orient = event.GetOrientation();

    int nScrollInc = 0;
    if (event.GetEventType() == wxEVT_SCROLLWIN_TOP)
    {
            if (orient == wxHORIZONTAL)
                nScrollInc = - m_xScrollPosition;
            else
                nScrollInc = - m_yScrollPosition;
    } else
    if (event.GetEventType() == wxEVT_SCROLLWIN_BOTTOM)
    {
            if (orient == wxHORIZONTAL)
                nScrollInc = m_xScrollLines - m_xScrollPosition;
            else
                nScrollInc = m_yScrollLines - m_yScrollPosition;
    } else
    if (event.GetEventType() == wxEVT_SCROLLWIN_LINEUP)
    {
            nScrollInc = -1;
    } else
    if (event.GetEventType() == wxEVT_SCROLLWIN_LINEDOWN)
    {
            nScrollInc = 1;
    } else
    if (event.GetEventType() == wxEVT_SCROLLWIN_PAGEUP)
    {
            if (orient == wxHORIZONTAL)
                nScrollInc = -GetScrollPageSize(wxHORIZONTAL);
            else
                nScrollInc = -GetScrollPageSize(wxVERTICAL);
    } else
    if (event.GetEventType() == wxEVT_SCROLLWIN_PAGEDOWN)
    {
            if (orient == wxHORIZONTAL)
                nScrollInc = GetScrollPageSize(wxHORIZONTAL);
            else
                nScrollInc = GetScrollPageSize(wxVERTICAL);
    } else
    if ((event.GetEventType() == wxEVT_SCROLLWIN_THUMBTRACK) ||
        (event.GetEventType() == wxEVT_SCROLLWIN_THUMBRELEASE))
    {
            if (orient == wxHORIZONTAL)
                nScrollInc = pos - m_xScrollPosition;
            else
                nScrollInc = pos - m_yScrollPosition;
    }

    if (orient == wxHORIZONTAL)
    {
        if (m_xScrollPixelsPerLine > 0)
        {
            int max = (int)(m_hAdjust->upper - m_hAdjust->page_size + 0.5);
            if (max < 0) max = 0;

            if ( (m_xScrollPosition + nScrollInc) < 0 )
                nScrollInc = -m_xScrollPosition; // As -ve as we can go
            else if ( (m_xScrollPosition + nScrollInc) > max )
                nScrollInc = max - m_xScrollPosition; // As +ve as we can go
        }
        else
            m_targetWindow->Refresh();
    }
    else
    {
        if (m_yScrollPixelsPerLine > 0)
        {
            int max = (int)(m_vAdjust->upper - m_vAdjust->page_size + 0.5);
            if (max < 0) max = 0;

            if ( (m_yScrollPosition + nScrollInc) < 0 )
                nScrollInc = -m_yScrollPosition; // As -ve as we can go
            else if ( (m_yScrollPosition + nScrollInc) > max )
                nScrollInc = max - m_yScrollPosition; // As +ve as we can go
        }
        else
            m_targetWindow->Refresh();
    }

    return nScrollInc;
}

void wxScrolledWindow::SetScrollPos( int orient, int pos, bool WXUNUSED(refresh) )
{
    wxCHECK_RET( m_widget != NULL, wxT("invalid window") );

    wxCHECK_RET( m_wxwindow != NULL, wxT("window needs client area for scrolling") );

    if (orient == wxHORIZONTAL)
    {
        int max = (int)(m_hAdjust->upper - m_hAdjust->page_size + 0.5);
        if (max < 0) max = 0;
        
        if (pos > max) pos = 0;
        if (pos < 0) pos = 0;
        
        if (pos == (int)(m_hAdjust->value+0.5)) return;
        m_hAdjust->value = pos;
    }
    else
    {
        int max = (int)(m_vAdjust->upper - m_vAdjust->page_size + 0.5);
        if (max < 0) max = 0;
        
        if (pos > max) pos = 0;
        if (pos < 0) pos = 0;
        
        if (pos == (int)(m_vAdjust->value+0.5)) return;
        m_vAdjust->value = pos;
    }

    if (m_wxwindow->window)
    {
        if (orient == wxHORIZONTAL)
        {
            // Just update the scrollbar, don't send any wxWindows event
            GtkHDisconnectEvent();
            gtk_signal_emit_by_name( GTK_OBJECT(m_hAdjust), "value_changed" );
            GtkHConnectEvent();
        }
        else
        {
            // Just update the scrollbar, don't send any wxWindows event
            GtkVDisconnectEvent();
            gtk_signal_emit_by_name( GTK_OBJECT(m_vAdjust), "value_changed" );
            GtkVConnectEvent();
        }
    }
}

void wxScrolledWindow::GtkVConnectEvent()
{
    gtk_signal_connect( GTK_OBJECT(m_vAdjust), "value_changed",
          (GtkSignalFunc) gtk_scrolled_window_vscroll_callback, (gpointer) this );
}

void wxScrolledWindow::GtkHConnectEvent()
{
    gtk_signal_connect( GTK_OBJECT(m_hAdjust), "value_changed",
          (GtkSignalFunc) gtk_scrolled_window_hscroll_callback, (gpointer) this );
}

void wxScrolledWindow::GtkHDisconnectEvent()
{
    gtk_signal_disconnect_by_func( GTK_OBJECT(m_hAdjust),
        (GtkSignalFunc) gtk_scrolled_window_hscroll_callback, (gpointer) this );
}

void wxScrolledWindow::GtkVDisconnectEvent()
{
    gtk_signal_disconnect_by_func( GTK_OBJECT(m_vAdjust),
        (GtkSignalFunc) gtk_scrolled_window_vscroll_callback, (gpointer) this );
}

// ----------------------------------------------------------------------------
// event handlers
// ----------------------------------------------------------------------------

// Default OnSize resets scrollbars, if any
void wxScrolledWindow::OnSize(wxSizeEvent& WXUNUSED(event))
{
#if wxUSE_CONSTRAINTS
    if (GetAutoLayout())
        Layout();
#endif

    AdjustScrollbars();
}

// This calls OnDraw, having adjusted the origin according to the current
// scroll position
void wxScrolledWindow::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxPaintDC dc(this);
    PrepareDC(dc);

    OnDraw(dc);
}

// kbd handling: notice that we use OnChar() and not OnKeyDown() for
// compatibility here - if we used OnKeyDown(), the programs which process
// arrows themselves in their OnChar() would never get the message and like
// this they always have the priority
void wxScrolledWindow::OnChar(wxKeyEvent& event)
{
    int stx, sty,       // view origin
        szx, szy,       // view size (total)
        clix, cliy;     // view size (on screen)

    ViewStart(&stx, &sty);
    GetClientSize(&clix, &cliy);
    GetVirtualSize(&szx, &szy);

    if( m_xScrollPixelsPerLine )
    {
        clix /= m_xScrollPixelsPerLine;
        szx /= m_xScrollPixelsPerLine;
    }
    else
    {
        clix = 0;
        szx = -1;
    }
    if( m_yScrollPixelsPerLine )
    {
        cliy /= m_yScrollPixelsPerLine;
        szy /= m_yScrollPixelsPerLine;
    }
    else
    {
        cliy = 0;
        szy = -1;
    }

    int dsty;
    switch ( event.KeyCode() )
    {
        case WXK_PAGEUP:
        case WXK_PRIOR:
            dsty = sty - (5 * cliy / 6);
            Scroll(-1, (dsty == -1) ? 0 : dsty);
            break;

        case WXK_PAGEDOWN:
        case WXK_NEXT:
            Scroll(-1, sty + (5 * cliy / 6));
            break;

        case WXK_HOME:
            Scroll(0, event.ControlDown() ? 0 : -1);
            break;

        case WXK_END:
            Scroll(szx - clix, event.ControlDown() ? szy - cliy : -1);
            break;

        case WXK_UP:
            Scroll(-1, sty - 1);
            break;

        case WXK_DOWN:
            Scroll(-1, sty + 1);
            break;

        case WXK_LEFT:
            Scroll(stx - 1, -1);
            break;

        case WXK_RIGHT:
            Scroll(stx + 1, -1);
            break;

        default:
            // not for us
            event.Skip();
    }
}
