/*
 * Program: wxLayout
 * 
 * Author: Karsten Ball�der
 *
 * Copyright: (C) 1998, Karsten Ball�der <Ballueder@usa.net>
 *
 */

#ifdef __GNUG__
#pragma implementation "wxLayout.h"
#endif

#include "wxLayout.h"
#include "wx/textfile.h"


#include   "Micon.xpm"

// for testing only:
#include   <stdio.h>

//-----------------------------------------------------------------------------
// main program
//-----------------------------------------------------------------------------

IMPLEMENT_APP(MyApp)

//-----------------------------------------------------------------------------
// MyFrame
//-----------------------------------------------------------------------------

   enum ids{ ID_ADD_SAMPLE = 1, ID_CLEAR, ID_PRINT,
             ID_PRINT_SETUP, ID_PAGE_SETUP, ID_PREVIEW, ID_PRINT_PS,
             ID_PRINT_SETUP_PS, ID_PAGE_SETUP_PS,ID_PREVIEW_PS,
             ID_WRAP, ID_NOWRAP,
             ID_WXLAYOUT_DEBUG, ID_QUIT, ID_CLICK, ID_HTML, ID_TEXT, ID_TEST };


IMPLEMENT_DYNAMIC_CLASS( MyFrame, wxFrame )

   BEGIN_EVENT_TABLE(MyFrame,wxFrame)
   EVT_MENU(ID_PRINT, MyFrame::OnPrint)
   EVT_MENU(ID_PREVIEW, MyFrame::OnPrintPreview)
   EVT_MENU(ID_PRINT_SETUP, MyFrame::OnPrintSetup)
   EVT_MENU(ID_PAGE_SETUP, MyFrame::OnPageSetup)
   EVT_MENU(ID_PRINT_PS, MyFrame::OnPrintPS)
   EVT_MENU(ID_PREVIEW_PS, MyFrame::OnPrintPreviewPS)
   EVT_MENU(ID_PRINT_SETUP_PS, MyFrame::OnPrintSetupPS)
   EVT_MENU(ID_PAGE_SETUP_PS, MyFrame::OnPageSetupPS)
   EVT_MENU    (-1,       MyFrame::OnCommand)
   EVT_COMMAND (-1,-1,    MyFrame::OnCommand)
   EVT_CHAR    (  wxLayoutWindow::OnChar  )
   END_EVENT_TABLE()


   int orientation = wxPORTRAIT;

MyFrame::MyFrame(void) :
   wxFrame( (wxFrame *) NULL, -1, (char *) "wxLayout", wxPoint(20,20), wxSize(600,360) )
{
   CreateStatusBar( 1 );
  
   SetStatusText( "wxLayout by Karsten Ball�der." );

   wxMenu *file_menu = new wxMenu;
   file_menu->Append( ID_CLEAR, "Clear");
   file_menu->Append( ID_ADD_SAMPLE, "Example");

   file_menu->Append(ID_PRINT, "&Print...", "Print");
   file_menu->Append(ID_PRINT_SETUP, "Print &Setup...","Setup printer properties");
   file_menu->Append(ID_PAGE_SETUP, "Page Set&up...", "Page setup");
   file_menu->Append(ID_PREVIEW, "Print Pre&view", "Preview");
#ifdef __WXMSW__
   file_menu->AppendSeparator();
   file_menu->Append(ID_PRINT_PS, "Print PostScript...", "Print (PostScript)");
   file_menu->Append(ID_PRINT_SETUP_PS, "Print Setup PostScript...", "Setup printer properties (PostScript)");
   file_menu->Append(ID_PAGE_SETUP_PS, "Page Setup PostScript...", "Page setup (PostScript)");
   file_menu->Append(ID_PREVIEW_PS, "Print Preview PostScript", "Preview (PostScript)");
#endif
   file_menu->AppendSeparator();
   file_menu->Append(ID_WRAP, "Wrap mode", "Activate wrapping at pixel 200.");
   file_menu->Append(ID_NOWRAP, "No-wrap mode", "Deactivate wrapping.");

   file_menu->AppendSeparator();
   file_menu->Append( ID_TEXT, "Export Text");
   file_menu->Append( ID_HTML, "Export HTML");
   file_menu->Append( ID_QUIT, "Exit");
  
   wxMenuBar *menu_bar = new wxMenuBar();
   menu_bar->Append(file_menu, "File" );

#ifndef __WXMSW__
   menu_bar->Show( TRUE );
#endif // MSW
  
   SetMenuBar( menu_bar );

   m_lwin = new wxLayoutWindow(this);
   m_lwin->SetMouseTracking(true);
   m_lwin->SetEditable(true);
   m_lwin->Clear(wxROMAN,16,wxNORMAL,wxNORMAL, false);
   m_lwin->SetFocus();
};

void
MyFrame::AddSampleText(wxLayoutList *llist)
{
   llist->SetFont(wxROMAN,16,wxNORMAL,wxNORMAL, false);
   llist->Insert("--");
   llist->LineBreak();

   llist->SetFont(wxROMAN);
   llist->Insert("The quick brown fox jumps over the lazy dog.");
   llist->LineBreak();
   llist->Insert("Hello ");
   llist->Insert(new wxLayoutObjectIcon(new wxICON(Micon)));
   llist->SetFontWeight(wxBOLD);
   llist->Insert("World! ");
   llist->SetFontWeight(wxNORMAL);
   llist->Insert("The quick brown fox jumps...");
   llist->LineBreak();

   llist->Insert("over the lazy dog.");
   llist->SetFont(-1,-1,-1,-1,true);
   llist->Insert("underlined");
   llist->SetFont(-1,-1,-1,-1,false);
   llist->SetFont(wxROMAN);
   llist->Insert("This is ");
   llist->SetFont(-1,-1,-1,wxBOLD);  llist->Insert("BOLD ");  llist->SetFont(-1,-1,-1,wxNORMAL);
   llist->Insert("and ");
   llist->SetFont(-1,-1,wxITALIC);
   llist->Insert("italics ");
   llist->SetFont(-1,-1,wxNORMAL);
   llist->LineBreak();
  
   llist->Insert("and ");
   llist->SetFont(-1,-1,wxSLANT);
   llist->Insert("slanted");
   llist->SetFont(-1,-1,wxNORMAL);
   llist->Insert(" text.");
   llist->LineBreak();

   llist->Insert("and ");
   llist->SetFont(-1,-1,-1,-1,-1,"blue");
   llist->Insert("blue");
   llist->SetFont(-1,-1,-1,-1,-1,"black");
   llist->Insert(" and ");
   llist->SetFont(-1,-1,-1,-1,-1,"green","black");
   llist->Insert("green on black");
   llist->SetFont(-1,-1,-1,-1,-1,"black","white");
   llist->Insert(" text.");
   llist->LineBreak();

   llist->SetFont(-1,-1,wxSLANT);
   llist->Insert("Slanted");
   llist->SetFont(-1,-1,wxNORMAL);
   llist->Insert(" and normal text and ");
   llist->SetFont(-1,-1,wxSLANT);
   llist->Insert("slanted");
   llist->SetFont(-1,-1,wxNORMAL);
   llist->Insert(" again.");
   llist->LineBreak();

   // add some more text for testing:
   llist->Insert("And here the source for the test program:");
   llist->LineBreak();
   llist->SetFont(wxTELETYPE,16);
   char buffer[1024];
   FILE *in = fopen("wxLayout.cpp","r");
   if(in)
   {
      for(;;)
      {
         fgets(buffer,1024,in);
         if(feof(in))
            break;
         llist->Insert(buffer);
         llist->LineBreak();
      }
   }
   llist->MoveCursorTo(wxPoint(0,0));
   m_lwin->SetDirty();
   m_lwin->Refresh();
}

void
MyFrame::Clear(void)
{
   m_lwin->Clear(wxROMAN,16,wxNORMAL,wxNORMAL, false);
}


void MyFrame::OnCommand( wxCommandEvent &event )
{
   switch (event.GetId())
   {
   case ID_QUIT:
      Close( TRUE );
      break;
   case ID_PRINT:
   {
      wxPrinter printer;
      wxLayoutPrintout printout(m_lwin->GetLayoutList(),_("M: Printout"));
      if (! printer.Print(this, &printout, TRUE))
         wxMessageBox(                           
            _("There was a problem with printing the message:\n"
              "perhaps your current printer is not set up correctly?"),
            _("Printing"), wxOK);
   }
   break;
   case ID_NOWRAP:
   case ID_WRAP:
////      m_lwin->GetLayoutList()->SetWrapMargin(
////         event.GetId() == ID_NOWRAP ? -1 : 40);
      break;
   case ID_ADD_SAMPLE:
      AddSampleText(m_lwin->GetLayoutList());
      break;
   case ID_CLEAR:
      Clear();
      break;
   case ID_CLICK:
      cerr << "Received click event." << endl;
      break;
   case ID_HTML:
   {
      wxLayoutExportObject *export;
      wxLayoutExportStatus status(m_lwin->GetLayoutList());

      while((export = wxLayoutExport( &status, WXLO_EXPORT_AS_HTML)) != NULL)
      {
         if(export->type == WXLO_EXPORT_HTML)
            cout << *(export->content.text);
         else
            cout << "<!--UNKNOWN OBJECT>";
         delete export;
      }
   }
   break;
   case ID_TEXT:
   {
      wxLayoutExportObject *export;
      wxLayoutExportStatus status(m_lwin->GetLayoutList());

      while((export = wxLayoutExport( &status, WXLO_EXPORT_AS_TEXT)) != NULL)
      {
         if(export->type == WXLO_EXPORT_TEXT)
            cout << *(export->content.text);
         else
            cout << "<!--UNKNOWN OBJECT>";
         delete export;
      }
   }
   break;
   }
};

void MyFrame::OnPrint(wxCommandEvent& WXUNUSED(event))
{
#ifdef __WXMSW__
   wxGetApp().SetPrintMode(wxPRINT_WINDOWS);
#else
   wxGetApp().SetPrintMode(wxPRINT_POSTSCRIPT);
#endif
   wxPrinter printer;
   wxLayoutPrintout printout( m_lwin->GetLayoutList(),"Printout from wxLayout");
   if (! printer.Print(this, &printout, TRUE))
      wxMessageBox(
         "There was a problem printing.\nPerhaps your current printer is not set correctly?",
         "Printing", wxOK);  
}

void MyFrame::OnPrintPS(wxCommandEvent& WXUNUSED(event))
{
   wxGetApp().SetPrintMode(wxPRINT_POSTSCRIPT);

   wxPostScriptPrinter printer;
   wxLayoutPrintout printout( m_lwin->GetLayoutList(),"My printout");
   printer.Print(this, &printout, TRUE);
}

void MyFrame::OnPrintPreview(wxCommandEvent& WXUNUSED(event))
{
#ifdef __WXMSW__
   wxGetApp().SetPrintMode(wxPRINT_WINDOWS);
#else
   wxGetApp().SetPrintMode(wxPRINT_POSTSCRIPT);
#endif
   wxPrintData printData;
   printData.SetOrientation(orientation);

   // Pass two printout objects: for preview, and possible printing.
   wxPrintPreview *preview = new wxPrintPreview(new
                                                wxLayoutPrintout(
                                                   m_lwin->GetLayoutList()), new wxLayoutPrintout( m_lwin->GetLayoutList()), & printData);  
   if (!preview->Ok())
   {
      delete preview;
      wxMessageBox("There was a problem previewing.\nPerhaps your current printer is not set correctly?", "Previewing", wxOK);
      return;
   }
      
   wxPreviewFrame *frame = new wxPreviewFrame(preview, this, "Demo Print Preview", wxPoint(100, 100), wxSize(600, 650));
   frame->Centre(wxBOTH);
   frame->Initialize();
   frame->Show(TRUE);
}

void MyFrame::OnPrintPreviewPS(wxCommandEvent& WXUNUSED(event))
{
   wxGetApp().SetPrintMode(wxPRINT_POSTSCRIPT);

   wxPrintData printData;
   printData.SetOrientation(orientation);

   // Pass two printout objects: for preview, and possible printing.
   wxPrintPreview *preview = new wxPrintPreview(new wxLayoutPrintout( m_lwin->GetLayoutList()), new wxLayoutPrintout( m_lwin->GetLayoutList()), & printData);
   wxPreviewFrame *frame = new wxPreviewFrame(preview, this, "Demo Print Preview", wxPoint(100, 100), wxSize(600, 650));
   frame->Centre(wxBOTH);
   frame->Initialize();
   frame->Show(TRUE);
}

void MyFrame::OnPrintSetup(wxCommandEvent& WXUNUSED(event))
{
#ifdef __WXMSW__
   wxGetApp().SetPrintMode(wxPRINT_WINDOWS);
#else
   wxGetApp().SetPrintMode(wxPRINT_POSTSCRIPT);
#endif
   wxPrintData data;
   data.SetOrientation(orientation);

#ifdef __WXMSW__
   wxPrintDialog printerDialog(this, & data);
#else
   wxGenericPrintDialog printerDialog(this, & data);
#endif
   printerDialog.GetPrintData().SetSetupDialog(TRUE);
   printerDialog.ShowModal();

   orientation = printerDialog.GetPrintData().GetOrientation();
}

void MyFrame::OnPageSetup(wxCommandEvent& WXUNUSED(event))
{
#ifdef __WXMSW__
   wxGetApp().SetPrintMode(wxPRINT_WINDOWS);
#else
   wxGetApp().SetPrintMode(wxPRINT_POSTSCRIPT);
#endif
   wxPageSetupData data;
   data.SetOrientation(orientation);

#ifdef __WXMSW__
   wxPageSetupDialog pageSetupDialog(this, & data);
#else
   wxGenericPageSetupDialog pageSetupDialog(this, & data);
#endif
   pageSetupDialog.ShowModal();

   data = pageSetupDialog.GetPageSetupData();
   orientation = data.GetOrientation();
}

void MyFrame::OnPrintSetupPS(wxCommandEvent& WXUNUSED(event))
{
   wxGetApp().SetPrintMode(wxPRINT_POSTSCRIPT);

   wxPrintData data;
   data.SetOrientation(orientation);

   wxGenericPrintDialog printerDialog(this, & data);
   printerDialog.GetPrintData().SetSetupDialog(TRUE);
   printerDialog.ShowModal();

   orientation = printerDialog.GetPrintData().GetOrientation();
}

void MyFrame::OnPageSetupPS(wxCommandEvent& WXUNUSED(event))
{
   wxGetApp().SetPrintMode(wxPRINT_POSTSCRIPT);

   wxPageSetupData data;
   data.SetOrientation(orientation);

   wxGenericPageSetupDialog pageSetupDialog(this, & data);
   pageSetupDialog.ShowModal();

   orientation = pageSetupDialog.GetPageSetupData().GetOrientation();
}


//-----------------------------------------------------------------------------
// MyApp
//-----------------------------------------------------------------------------

MyApp::MyApp(void) : 
   wxApp( )
{
};

bool MyApp::OnInit(void)
{
   wxFrame *frame = new MyFrame();
   frame->Show( TRUE );
//   wxSetAFMPath("/usr/local/src/wxWindows/misc/afm/");
   return TRUE;
};





