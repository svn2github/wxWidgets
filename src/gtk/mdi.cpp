/////////////////////////////////////////////////////////////////////////////
// Name:        src/gtk/mdi.cpp
// Purpose:
// Author:      Robert Roebling
// Id:          $Id$
// Copyright:   (c) 1998 Robert Roebling
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#if wxUSE_MDI

#include "wx/mdi.h"

#ifndef WX_PRECOMP
    #include "wx/intl.h"
    #include "wx/menu.h"
#endif

#include "wx/gtk/private.h"

//-----------------------------------------------------------------------------
// "switch_page"
//-----------------------------------------------------------------------------

extern "C" {
static void
gtk_mdi_page_change_callback( GtkNotebook *WXUNUSED(widget),
                              GtkNotebookPage *page,
                              gint WXUNUSED(page_num),
                              wxMDIParentFrame *parent )
{
    // send deactivate event to old child

    wxMDIChildFrame *child = parent->GetActiveChild();
    if (child)
    {
        wxActivateEvent event1( wxEVT_ACTIVATE, false, child->GetId() );
        event1.SetEventObject( child);
        child->HandleWindowEvent( event1 );
    }

    // send activate event to new child

    wxMDIClientWindow *client_window = parent->GetClientWindow();
    if (!client_window)
        return;

    child = (wxMDIChildFrame*) NULL;

    wxWindowList::compatibility_iterator node = client_window->GetChildren().GetFirst();
    while ( node )
    {
        wxMDIChildFrame *child_frame = wxDynamicCast( node->GetData(), wxMDIChildFrame );

        // child_frame can be NULL when this is called from dtor, probably
        // because g_signal_connect (m_widget, "switch_page", (see below)
        // isn't deleted early enough
        if ( child_frame && child_frame->m_page == page )
        {
            child = child_frame;
            break;
        }
        node = node->GetNext();
    }

    if (!child)
         return;

    wxActivateEvent event2( wxEVT_ACTIVATE, true, child->GetId() );
    event2.SetEventObject( child);
    child->HandleWindowEvent( event2 );
}
}

//-----------------------------------------------------------------------------
// wxMDIParentFrame
//-----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC_CLASS(wxMDIParentFrame,wxFrame)

void wxMDIParentFrame::Init()
{
    m_justInserted = false;
    m_clientWindow = (wxMDIClientWindow *) NULL;
}

wxMDIParentFrame::~wxMDIParentFrame()
{
}

bool wxMDIParentFrame::Create(wxWindow *parent,
                              wxWindowID id,
                              const wxString& title,
                              const wxPoint& pos,
                              const wxSize& size,
                              long style,
                              const wxString& name )
{
    if ( !wxFrame::Create( parent, id, title, pos, size, style, name ) )
        return false;

    m_clientWindow = OnCreateClient();

    return m_clientWindow != NULL;
}

void wxMDIParentFrame::OnInternalIdle()
{
    /* if a an MDI child window has just been inserted
       it has to be brought to the top in idle time. we
       simply set the last notebook page active as new
       pages can only be appended at the end */

    if (m_justInserted)
    {
        GtkNotebook *notebook = GTK_NOTEBOOK(m_clientWindow->m_widget);
        gtk_notebook_set_current_page( notebook, g_list_length( notebook->children ) - 1 );

        /* need to set the menubar of the child */
        wxMDIChildFrame *active_child_frame = GetActiveChild();
        if (active_child_frame != NULL)
        {
            wxMenuBar *menu_bar = active_child_frame->m_menuBar;
            if (menu_bar)
            {
                menu_bar->SetInvokingWindow(active_child_frame);
            }
        }
        m_justInserted = false;
        return;
    }

    wxFrame::OnInternalIdle();

    wxMDIChildFrame *active_child_frame = GetActiveChild();
    bool visible_child_menu = false;

    wxWindowList::compatibility_iterator node = m_clientWindow->GetChildren().GetFirst();
    while (node)
    {
        wxMDIChildFrame *child_frame = wxDynamicCast( node->GetData(), wxMDIChildFrame );

        if ( child_frame )
        {
            wxMenuBar *menu_bar = child_frame->m_menuBar;
            if ( menu_bar )
            {
                if (child_frame == active_child_frame)
                {
                    if (menu_bar->Show(true))
                    {
                        menu_bar->SetInvokingWindow( child_frame );
                    }
                    visible_child_menu = true;
                }
                else
                {
                    if (menu_bar->Show(false))
                    {
                        menu_bar->UnsetInvokingWindow( child_frame );
                    }
                }
            }
        }

        node = node->GetNext();
    }

    /* show/hide parent menu bar as required */
    if ((m_frameMenuBar) &&
        (m_frameMenuBar->IsShown() == visible_child_menu))
    {
        if (visible_child_menu)
        {
            m_frameMenuBar->Show( false );
            m_frameMenuBar->UnsetInvokingWindow( this );
        }
        else
        {
            m_frameMenuBar->Show( true );
            m_frameMenuBar->SetInvokingWindow( this );
        }
    }
}

void wxMDIParentFrame::DoGetClientSize(int* width, int* height) const
{
    wxFrame::DoGetClientSize(width, height);

    if (height)
    {
        wxMDIChildFrame* active_child_frame = GetActiveChild();
        if (active_child_frame)
        {
            wxMenuBar* menubar = active_child_frame->m_menuBar;
            if (menubar && menubar->IsShown())
            {
                GtkRequisition req;
                gtk_widget_size_request(menubar->m_widget, &req);
                *height -= req.height;
                if (*height < 0) *height = 0;
            }
        }
    }
}

wxMDIChildFrame *wxMDIParentFrame::GetActiveChild() const
{
    if (!m_clientWindow) return (wxMDIChildFrame*) NULL;

    GtkNotebook *notebook = GTK_NOTEBOOK(m_clientWindow->m_widget);
    if (!notebook) return (wxMDIChildFrame*) NULL;

    gint i = gtk_notebook_get_current_page( notebook );
    if (i < 0) return (wxMDIChildFrame*) NULL;

    GtkNotebookPage* page = (GtkNotebookPage*) (g_list_nth(notebook->children,i)->data);
    if (!page) return (wxMDIChildFrame*) NULL;

    wxWindowList::compatibility_iterator node = m_clientWindow->GetChildren().GetFirst();
    while (node)
    {
        if ( wxPendingDelete.Member(node->GetData()) )
            return (wxMDIChildFrame*) NULL;

        wxMDIChildFrame *child_frame = wxDynamicCast( node->GetData(), wxMDIChildFrame );

        if (!child_frame)
            return (wxMDIChildFrame*) NULL;

        if (child_frame->m_page == page)
            return child_frame;

        node = node->GetNext();
    }

    return (wxMDIChildFrame*) NULL;
}

wxMDIClientWindow *wxMDIParentFrame::GetClientWindow() const
{
    return m_clientWindow;
}

wxMDIClientWindow *wxMDIParentFrame::OnCreateClient()
{
    return new wxMDIClientWindow( this );
}

void wxMDIParentFrame::ActivateNext()
{
    if (m_clientWindow)
      gtk_notebook_next_page( GTK_NOTEBOOK(m_clientWindow->m_widget) );
}

void wxMDIParentFrame::ActivatePrevious()
{
    if (m_clientWindow)
      gtk_notebook_prev_page( GTK_NOTEBOOK(m_clientWindow->m_widget) );
}

//-----------------------------------------------------------------------------
// wxMDIChildFrame
//-----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC_CLASS(wxMDIChildFrame,wxFrame)

BEGIN_EVENT_TABLE(wxMDIChildFrame, wxFrame)
    EVT_ACTIVATE(wxMDIChildFrame::OnActivate)
    EVT_MENU_HIGHLIGHT_ALL(wxMDIChildFrame::OnMenuHighlight)
END_EVENT_TABLE()

wxMDIChildFrame::wxMDIChildFrame()
{
    m_menuBar = (wxMenuBar *) NULL;
    m_page = (GtkNotebookPage *) NULL;
}

wxMDIChildFrame::wxMDIChildFrame( wxMDIParentFrame *parent,
      wxWindowID id, const wxString& title,
      const wxPoint& WXUNUSED(pos), const wxSize& size,
      long style, const wxString& name )
{
    m_menuBar = (wxMenuBar *) NULL;
    m_page = (GtkNotebookPage *) NULL;
    Create( parent, id, title, wxDefaultPosition, size, style, name );
}

wxMDIChildFrame::~wxMDIChildFrame()
{
    if (m_menuBar)
        delete m_menuBar;

    // wxMDIClientWindow does not get redrawn properly after last child is removed
    if (m_parent && m_parent->GetChildren().size() <= 1)
        gtk_widget_queue_draw(m_parent->m_widget);
}

bool wxMDIChildFrame::Create( wxMDIParentFrame *parent,
      wxWindowID id, const wxString& title,
      const wxPoint& WXUNUSED(pos), const wxSize& size,
      long style, const wxString& name )
{
    m_title = title;

    return wxWindow::Create( parent->GetClientWindow(), id, wxDefaultPosition, size, style, name );
}

bool wxMDIChildFrame::Destroy()
{
    // delayed destruction: the frame will be deleted during
    // the next idle loop iteration.
    // I'm not sure if delayed destruction really makes so
    // much sense for MDI child frames, actually, but hiding
    // it doesn't make any sense.
    if ( !wxPendingDelete.Member(this) )
        wxPendingDelete.Append(this);

    return true;
}

void wxMDIChildFrame::DoSetSize( int x, int y, int width, int height, int sizeFlags )
{
    wxWindow::DoSetSize( x, y, width, height, sizeFlags );
}

void wxMDIChildFrame::AddChild( wxWindowBase *child )
{
    wxWindow::AddChild(child);
}

void wxMDIChildFrame::SetMenuBar( wxMenuBar *menu_bar )
{
    wxASSERT_MSG( m_menuBar == NULL, wxT("Only one menubar allowed") );

    m_menuBar = menu_bar;

    if (m_menuBar)
    {
        wxMDIParentFrame *mdi_frame = (wxMDIParentFrame*)m_parent->GetParent();

        m_menuBar->SetParent( mdi_frame );

        /* insert the invisible menu bar into the _parent_ mdi frame */
        m_menuBar->Show(false);
        gtk_box_pack_start(GTK_BOX(mdi_frame->m_mainWidget), m_menuBar->m_widget, false, false, 0);
        gtk_box_reorder_child(GTK_BOX(mdi_frame->m_mainWidget), m_menuBar->m_widget, 0);

        gulong handler_id = g_signal_handler_find(
            m_menuBar->m_widget,
            GSignalMatchType(G_SIGNAL_MATCH_ID | G_SIGNAL_MATCH_DATA),
            g_signal_lookup("size_request", GTK_TYPE_WIDGET),
            0, NULL, NULL, m_menuBar);
        if (handler_id != 0)
            g_signal_handler_disconnect(m_menuBar->m_widget, handler_id);
        gtk_widget_set_size_request(m_menuBar->m_widget, -1, -1);
    }
}

wxMenuBar *wxMDIChildFrame::GetMenuBar() const
{
    return m_menuBar;
}

void wxMDIChildFrame::Activate()
{
    wxMDIParentFrame* parent = (wxMDIParentFrame*) GetParent();
    GtkNotebook* notebook = GTK_NOTEBOOK(parent->m_widget);
    gint pageno = gtk_notebook_page_num( notebook, m_widget );
    gtk_notebook_set_current_page( notebook, pageno );
}

void wxMDIChildFrame::OnActivate( wxActivateEvent& WXUNUSED(event) )
{
}

void wxMDIChildFrame::OnMenuHighlight( wxMenuEvent& event )
{
#if wxUSE_STATUSBAR
    wxMDIParentFrame *mdi_frame = (wxMDIParentFrame*)m_parent->GetParent();
    if ( !ShowMenuHelp(event.GetMenuId()) )
    {
        // we don't have any help text for this item, but may be the MDI frame
        // does?
        mdi_frame->OnMenuHighlight(event);
    }
#endif // wxUSE_STATUSBAR
}

void wxMDIChildFrame::SetTitle( const wxString &title )
{
    if ( title == m_title )
        return;

    m_title = title;

    wxMDIParentFrame* parent = (wxMDIParentFrame*) GetParent();
    GtkNotebook* notebook = GTK_NOTEBOOK(parent->m_widget);
    gtk_notebook_set_tab_label_text(notebook, m_widget, wxGTK_CONV( title ) );
}

void wxMDIClientWindow::AddChildGTK(wxWindowGTK* child)
{
    wxMDIChildFrame* child_frame = static_cast<wxMDIChildFrame*>(child);
    wxString s = child_frame->GetTitle();
    if (s.IsNull()) s = _("MDI child");

    GtkWidget *label_widget = gtk_label_new( s.mbc_str() );
    gtk_misc_set_alignment( GTK_MISC(label_widget), 0.0, 0.5 );

    GtkNotebook* notebook = GTK_NOTEBOOK(m_widget);

    gtk_notebook_append_page( notebook, child->m_widget, label_widget );

    child_frame->m_page = (GtkNotebookPage*) (g_list_last(notebook->children)->data);

    wxMDIParentFrame* parent_frame = static_cast<wxMDIParentFrame*>(GetParent());
    parent_frame->m_justInserted = true;
}

//-----------------------------------------------------------------------------
// wxMDIClientWindow
//-----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC_CLASS(wxMDIClientWindow,wxWindow)

wxMDIClientWindow::wxMDIClientWindow()
{
}

wxMDIClientWindow::wxMDIClientWindow( wxMDIParentFrame *parent, long style )
{
    CreateClient( parent, style );
}

wxMDIClientWindow::~wxMDIClientWindow()
{

}

bool wxMDIClientWindow::CreateClient( wxMDIParentFrame *parent, long style )
{
    if (!PreCreation( parent, wxDefaultPosition, wxDefaultSize ) ||
        !CreateBase( parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, style, wxDefaultValidator, wxT("wxMDIClientWindow") ))
    {
        wxFAIL_MSG( wxT("wxMDIClientWindow creation failed") );
        return false;
    }

    m_widget = gtk_notebook_new();
    g_object_ref(m_widget);

    g_signal_connect (m_widget, "switch_page",
                      G_CALLBACK (gtk_mdi_page_change_callback), parent);

    gtk_notebook_set_scrollable( GTK_NOTEBOOK(m_widget), 1 );

    m_parent->DoAddChild( this );

    PostCreation();

    Show( true );

    return true;
}

#endif // wxUSE_MDI
