/////////////////////////////////////////////////////////////////////////////
// Name:        app.cpp
// Purpose:     wxApp
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id$
// Copyright:   (c) Julian Smart and Markus Holzem
// Licence:   	wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
#pragma implementation "app.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#define IN_WX_MAIN_CPP
#include "wx/wxprec.h"

#if defined(__BORLANDC__)
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/frame.h"
#include "wx/app.h"
#include "wx/utils.h"
#include "wx/gdicmn.h"
#include "wx/pen.h"
#include "wx/brush.h"
#include "wx/cursor.h"
#include "wx/icon.h"
#include "wx/palette.h"
#include "wx/dc.h"
#include "wx/dialog.h"
#include "wx/msgdlg.h"
#endif

#include "wx/msw/private.h"
#include "wx/postscrp.h"
#include "wx/log.h"
#include "wx/module.h"

#if USE_WX_RESOURCES
#include "wx/resource.h"
#endif


#include <string.h>

#if defined(__WIN95__) && !defined(__GNUWIN32__)
#include <commctrl.h>
#endif

extern char *wxBuffer;
extern char *wxOsVersion;
extern wxList *wxWinHandleList;
extern wxList wxPendingDelete;
extern void wxSetKeyboardHook(bool doIt);
extern wxCursor *g_globalCursor;

HANDLE wxhInstance = 0;
static MSG s_currentMsg;
wxApp *wxTheApp = NULL;

char wxFrameClassName[]         = "wxFrameClass";
char wxMDIFrameClassName[]      = "wxMDIFrameClass";
char wxMDIChildFrameClassName[] = "wxMDIChildFrameClass";
char wxPanelClassName[]         = "wxPanelClass";
char wxCanvasClassName[]        = "wxCanvasClass";

HICON wxSTD_FRAME_ICON = NULL;
HICON wxSTD_MDICHILDFRAME_ICON = NULL;
HICON wxSTD_MDIPARENTFRAME_ICON = NULL;

HICON wxDEFAULT_FRAME_ICON = NULL;
HICON wxDEFAULT_MDICHILDFRAME_ICON = NULL;
HICON wxDEFAULT_MDIPARENTFRAME_ICON = NULL;

HBRUSH wxDisableButtonBrush = 0;

LRESULT APIENTRY wxWndProc(HWND, UINT, WPARAM, LPARAM);

#if !USE_SHARED_LIBRARY
IMPLEMENT_DYNAMIC_CLASS(wxApp, wxEvtHandler)
BEGIN_EVENT_TABLE(wxApp, wxEvtHandler)
    EVT_IDLE(wxApp::OnIdle)
END_EVENT_TABLE()
#endif

long wxApp::sm_lastMessageTime = 0;

#ifdef __WIN95__
static HINSTANCE gs_hRichEdit = NULL;
#endif

bool wxApp::Initialize(WXHANDLE instance)
{
  HANDLE hInstance = (HANDLE)instance;

  CommonInit();

#if defined(__WIN95__)
  InitCommonControls();
  gs_hRichEdit = LoadLibrary("RICHED32.DLL");

  if (gs_hRichEdit == NULL)
  {
    wxMessageBox("Could not initialise Rich Edit DLL");
  }
#endif

#if     defined(WX_DRAG_DROP)
  // we need to initialize OLE library
  if ( FAILED(::OleInitialize(NULL)) )
    wxFatalError(_("Cannot initialize OLE"));
#endif

#if CTL3D
  if (!Ctl3dRegister(hInstance))
    wxFatalError("Cannot register CTL3D");

  Ctl3dAutoSubclass(hInstance);
#endif

  wxSTD_FRAME_ICON = LoadIcon(hInstance, "wxSTD_FRAME");
  wxSTD_MDIPARENTFRAME_ICON = LoadIcon(hInstance, "wxSTD_MDIPARENTFRAME");
  wxSTD_MDICHILDFRAME_ICON = LoadIcon(hInstance, "wxSTD_MDICHILDFRAME");

  wxDEFAULT_FRAME_ICON = LoadIcon(hInstance, "wxDEFAULT_FRAME");
  wxDEFAULT_MDIPARENTFRAME_ICON = LoadIcon(hInstance, "wxDEFAULT_MDIPARENTFRAME");
  wxDEFAULT_MDICHILDFRAME_ICON = LoadIcon(hInstance, "wxDEFAULT_MDICHILDFRAME");

  RegisterWindowClasses();

  // Create the brush for disabling bitmap buttons

  LOGBRUSH lb ;
  lb.lbStyle = BS_PATTERN;
  lb.lbHatch = (int)LoadBitmap( hInstance, "wxDISABLE_BUTTON_BITMAP" ) ;
  wxDisableButtonBrush = ::CreateBrushIndirect( & lb ) ;
  ::DeleteObject( (HGDIOBJ)lb.lbHatch ) ;

#if USE_PENWINDOWS
  wxRegisterPenWin();
#endif

  wxWinHandleList = new wxList(wxKEY_INTEGER);

  // This is to foil optimizations in Visual C++ that
  // throw out dummy.obj.
#if (_MSC_VER >= 800) && !defined(WXMAKINGDLL)
  extern char wxDummyChar;
  if (wxDummyChar) wxDummyChar++;
#endif
  wxSetKeyboardHook(TRUE);

  wxModule::RegisterModules();
  if (!wxModule::InitializeModules())
    return FALSE;
  return TRUE;
}

bool wxApp::RegisterWindowClasses(void)
{
///////////////////////////////////////////////////////////////////////
// Register the frame window class.
  WNDCLASS wndclass;   // Structure used to register Windows class.

  wndclass.style         = CS_HREDRAW | CS_VREDRAW;
  wndclass.lpfnWndProc   = (WNDPROC)wxWndProc;
  wndclass.cbClsExtra    = 0;
  wndclass.cbWndExtra    = sizeof( DWORD ); // was 4
  wndclass.hInstance     = wxhInstance;
  wndclass.hIcon         = NULL;        // wxSTD_FRAME_ICON;
  wndclass.hCursor       = LoadCursor( NULL, IDC_ARROW );
  wndclass.hbrBackground =  (HBRUSH)(COLOR_APPWORKSPACE+1) ;
//  wndclass.hbrBackground = GetStockObject( WHITE_BRUSH );
  wndclass.lpszMenuName  = NULL;
#ifdef _MULTIPLE_INSTANCES
  sprintf( wxFrameClassName,"wxFrameClass%d", hInstance );
#endif
  wndclass.lpszClassName = wxFrameClassName;

  if (!RegisterClass( &wndclass ))
  {
    // wxFatalError("Can't register Frame Window class");
  }

///////////////////////////////////////////////////////////////////////
// Register the MDI frame window class.
  WNDCLASS wndclass1;   // Structure used to register Windows class.

  wndclass1.style         = CS_HREDRAW | CS_VREDRAW;
  wndclass1.lpfnWndProc   = (WNDPROC)wxWndProc;
  wndclass1.cbClsExtra    = 0;
  wndclass1.cbWndExtra    = sizeof( DWORD ); // was 4
  wndclass1.hInstance     = wxhInstance;
  wndclass1.hIcon         = NULL; // wxSTD_MDIPARENTFRAME_ICON;
  wndclass1.hCursor       = LoadCursor( NULL, IDC_ARROW );
//  wndclass1.hbrBackground =  (HBRUSH)(COLOR_APPWORKSPACE+1) ;
  wndclass1.hbrBackground = NULL;
  wndclass1.lpszMenuName  = NULL;

  wndclass1.lpszClassName = wxMDIFrameClassName;
  if (!RegisterClass( &wndclass1 ))
  {
//    wxFatalError("Can't register MDI Frame window class");
//	return FALSE;
  }

///////////////////////////////////////////////////////////////////////
// Register the MDI child frame window class.
  WNDCLASS wndclass4;   // Structure used to register Windows class.

  wndclass4.style         = CS_HREDRAW | CS_VREDRAW;
  wndclass4.lpfnWndProc   = (WNDPROC)wxWndProc;
  wndclass4.cbClsExtra    = 0;
  wndclass4.cbWndExtra    = sizeof( DWORD ); // was 4
  wndclass4.hInstance     = wxhInstance;
  wndclass4.hIcon         = NULL;       // wxSTD_MDICHILDFRAME_ICON;
  wndclass4.hCursor       = LoadCursor( NULL, IDC_ARROW );
  // TODO: perhaps this should be NULL so that Windows doesn't
  // paint the background itself (would OnEraseBackground duplicate
  // this?)
  wndclass4.hbrBackground =  (HBRUSH)(COLOR_WINDOW+1) ;
//  wndclass4.hbrBackground = NULL;
  wndclass4.lpszMenuName  = NULL;
  wndclass4.lpszClassName = wxMDIChildFrameClassName;

  if (!RegisterClass( &wndclass4 ))
  {
//   wxFatalError("Can't register MDI child frame window class");
//   return FALSE;
  }

///////////////////////////////////////////////////////////////////////
// Register the panel window class.
  WNDCLASS wndclass2;   // Structure used to register Windows class.
  memset(&wndclass2, 0, sizeof(WNDCLASS));   // start with NULL defaults
  // Use CS_OWNDC to avoid messing about restoring the context
  // for every graphic operation.
  wndclass2.style         = CS_HREDRAW | CS_VREDRAW;
  wndclass2.lpfnWndProc   = (WNDPROC)wxWndProc;
  wndclass2.cbClsExtra    = 0;
  wndclass2.cbWndExtra    = sizeof( DWORD ); // was 4
  wndclass2.hInstance     = wxhInstance;
  wndclass2.hIcon         = NULL;
  wndclass2.hCursor       = NULL;
//  wndclass2.hbrBackground = (HBRUSH)(COLOR_BTNFACE+1) ;
  wndclass2.hbrBackground = GetStockObject( LTGRAY_BRUSH );
  wndclass2.lpszMenuName  = NULL;
  wndclass2.lpszClassName = wxPanelClassName;
  if (!RegisterClass( &wndclass2 ))
  {
//   wxFatalError("Can't register Panel Window class");
//   return FALSE;
  }

///////////////////////////////////////////////////////////////////////
// Register the canvas and textsubwindow class name
  WNDCLASS wndclass3;   // Structure used to register Windows class.
  memset(&wndclass3, 0, sizeof(WNDCLASS));   // start with NULL defaults
  // Use CS_OWNDC to avoid messing about restoring the context
  // for every graphic operation.
//  wndclass3.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS ; 
  // wxWin 2.0
  wndclass3.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS ; 
  wndclass3.lpfnWndProc   = (WNDPROC)wxWndProc;
  wndclass3.cbClsExtra    = 0;
  wndclass3.cbWndExtra    = sizeof( DWORD ); // was 4
  wndclass3.hInstance     = wxhInstance;
  wndclass3.hIcon         = NULL;
  wndclass3.hCursor       = NULL;
//  wndclass3.hbrBackground = (HBRUSH)(COLOR_WINDOW+1) ;
  wndclass3.hbrBackground = NULL;
  wndclass3.lpszMenuName  = NULL;
  wndclass3.lpszClassName = wxCanvasClassName;
  if (!RegisterClass( &wndclass3))
  {
//   wxFatalError("Can't register Canvas class");
//   return FALSE;
  }

  return TRUE;
}

// Cleans up any wxWindows internal structures left lying around
void wxApp::CleanUp(void)
{
  wxModule::CleanUpModules();

  CommonCleanUp();

  wxSetKeyboardHook(FALSE);

#ifdef __WIN95__
  if (gs_hRichEdit != NULL)
    FreeLibrary(gs_hRichEdit);
#endif

#if USE_PENWINDOWS
  wxCleanUpPenWin();
#endif

  if (wxSTD_FRAME_ICON)
    DestroyIcon(wxSTD_FRAME_ICON);
  if (wxSTD_MDICHILDFRAME_ICON)
    DestroyIcon(wxSTD_MDICHILDFRAME_ICON);
  if (wxSTD_MDIPARENTFRAME_ICON)
    DestroyIcon(wxSTD_MDIPARENTFRAME_ICON);

  if (wxDEFAULT_FRAME_ICON)
    DestroyIcon(wxDEFAULT_FRAME_ICON);
  if (wxDEFAULT_MDICHILDFRAME_ICON)
    DestroyIcon(wxDEFAULT_MDICHILDFRAME_ICON);
  if (wxDEFAULT_MDIPARENTFRAME_ICON)
    DestroyIcon(wxDEFAULT_MDIPARENTFRAME_ICON);

  if ( wxDisableButtonBrush )
    ::DeleteObject( wxDisableButtonBrush ) ;

#if     defined(WX_DRAG_DROP)
  ::OleUninitialize();
#endif

#if CTL3D
  Ctl3dUnregister(wxhInstance);
#endif

  if (wxWinHandleList)
    delete wxWinHandleList ;
    
  // do it as the very last thing because everything else can log messages
  delete wxLog::SetActiveTarget(NULL);
}

void wxApp::CommonInit(void)
{
#ifdef __WINDOWS__
  wxBuffer = new char[1500];
#else
  wxBuffer = new char[BUFSIZ + 512];
#endif

  wxClassInfo::InitializeClasses();

#ifdef __X__
  wxTheFontNameDirectory.Initialize();
#endif

#if defined(__X__) && USE_RESOURCES
  // Read standard font names from .Xdefaults

  extern char *wxDecorativeFontName;
  extern char *wxRomanFontName;
  extern char *wxModernFontName;
  extern char *wxSwissFontName;
  extern char *wxScriptFontName;
  extern char *wxTeletypeFontName;
  extern char *wxDefaultFontName;

  (void) wxGetResource("wxWindows", "defaultFamily", &wxDefaultFontName);
  (void) wxGetResource("wxWindows", "decorativeFamily", &wxDecorativeFontName);
  (void) wxGetResource("wxWindows", "romanFamily", &wxRomanFontName);
  (void) wxGetResource("wxWindows", "modernFamily", &wxModernFontName);
  (void) wxGetResource("wxWindows", "swissFamily", &wxSwissFontName);
  (void) wxGetResource("wxWindows", "scriptFamily", &wxScriptFontName);
  (void) wxGetResource("wxWindows", "teletypeFamily", &wxTeletypeFontName);
#endif

#if USE_RESOURCES
  (void) wxGetResource("wxWindows", "OsVersion", &wxOsVersion);
#endif

  wxTheColourDatabase = new wxColourDatabase(wxKEY_STRING);
  wxTheColourDatabase->Initialize();
  wxInitializeStockObjects();

#if USE_WX_RESOURCES
  wxInitializeResourceSystem();
#endif

  // For PostScript printing
#if USE_POSTSCRIPT
  wxInitializePrintSetupData();
  wxThePrintPaperDatabase = new wxPrintPaperDatabase;
  wxThePrintPaperDatabase->CreateDatabase();
#endif

  wxBitmap::InitStandardHandlers();

  g_globalCursor = new wxCursor;
}

void wxApp::CommonCleanUp(void)
{
#if USE_WX_RESOURCES
  wxCleanUpResourceSystem();

//  wxDefaultResourceTable->ClearTable();
#endif
  // Indicate that the cursor can be freed,
  // so that cursor won't be deleted by deleting
  // the bitmap list before g_globalCursor goes out
  // of scope (double deletion of the cursor).
  wxSetCursor(wxNullCursor);
  delete g_globalCursor;

  wxDeleteStockObjects() ;

  // Destroy all GDI lists, etc.
  delete wxTheBrushList;
  wxTheBrushList = NULL;

  delete wxThePenList;
  wxThePenList = NULL;

  delete wxTheFontList;
  wxTheFontList = NULL;

  delete wxTheBitmapList;
  wxTheBitmapList = NULL;

  delete wxTheColourDatabase;
  wxTheColourDatabase = NULL;

#if USE_POSTSCRIPT
  wxInitializePrintSetupData(FALSE);
  delete wxThePrintPaperDatabase;
  wxThePrintPaperDatabase = NULL;
#endif

  wxBitmap::CleanUpHandlers();

  delete[] wxBuffer;
  wxBuffer = NULL;
}

#if !defined(_WINDLL) || (defined(_WINDLL) && defined(WXMAKINGDLL))

// Main wxWindows entry point

int wxEntry(WXHINSTANCE hInstance, WXHINSTANCE WXUNUSED(hPrevInstance), char *m_lpCmdLine,
                    int nCmdShow, bool enterLoop)
{
  wxhInstance = (HINSTANCE) hInstance;

#if (DEBUG && USE_MEMORY_TRACING) || USE_DEBUG_CONTEXT

#if !defined(_WINDLL)
  streambuf* sBuf = new wxDebugStreamBuf;
#else
  streambuf* sBuf = NULL;
#endif
  ostream* oStr = new ostream(sBuf) ;
  wxDebugContext::SetStream(oStr, sBuf);

#endif

  if (!wxApp::Initialize((WXHINSTANCE) wxhInstance))
    return 0;

  // The app may have declared a global application object, but we recommend
  // the IMPLEMENT_APP macro is used instead, which sets an initializer function
  // for delayed, dynamic app object construction.
  if (!wxTheApp)
  {
  	if (!wxApp::GetInitializerFunction())
  	{
    	MessageBox(NULL, "No initializer - use IMPLEMENT_APP macro.", "wxWindows Error", MB_APPLMODAL | MB_ICONSTOP | MB_OK);
		return 0;
  	}

  	wxTheApp = (* wxApp::GetInitializerFunction()) ();
  }

  if (!wxTheApp) {
    MessageBox(NULL, "You have to define an instance of wxApp!", "wxWindows Error", MB_APPLMODAL | MB_ICONSTOP | MB_OK);
    return 0;
  }

  // Split command line into tokens, as in usual main(argc, argv)
  char **command = new char*[50];
  
  int count = 0;
  char *buf = new char[strlen(m_lpCmdLine) + 1];
  
  // Hangs around until end of app. in case
  // user carries pointers to the tokens

  /* Model independent strcpy */
  int i;
  for (i = 0; (buf[i] = m_lpCmdLine[i]) != 0; i++)
  {
    /* loop */;
  }

  // Get application name
  char name[200];
  ::GetModuleFileName(wxhInstance, name, 199);

  // Is it only 16-bit Borland that already copies the program name
  // to the first argv index?
#if !defined(__GNUWIN32__)
// #if ! (defined(__BORLANDC__) && !defined(__WIN32__))
  command[count++] = copystring(name);
// #endif
#endif

  strcpy(name, wxFileNameFromPath(name));
  wxStripExtension(name);
  wxTheApp->SetAppName(name);

  /* Break up string */
  // Treat strings enclosed in double-quotes as single arguments
    char* str = buf;
	while (*str)
	{
		while (*str && *str <= ' ') str++;	// skip whitespace
		if (*str == '"')
		{
			str++;
			command[count++] = str;
			while (*str && *str != '"') str++;
		}
		else if (*str)
		{
			command[count++] = str;
			while (*str && *str > ' ') str++;
		}
		if (*str) *str++ = '\0';
	}
  command[count] = NULL; /* argv[] is NULL terminated list! */

  wxTheApp->argc = count;
  wxTheApp->argv = command;
  wxTheApp->m_nCmdShow = nCmdShow;

  // GUI-specific initialisation. In fact on Windows we don't have any,
  // but this call is provided for compatibility across platforms.
  wxTheApp->OnInitGui() ;

  if (!wxTheApp->OnInit())
  {
    	wxTheApp->DeletePendingObjects();
        wxTheApp->OnExit();
        wxApp::CleanUp();

        delete wxTheApp;
        wxTheApp = NULL;

        delete [] buf ;

        // TODO: This should really be cleaned up in ~wxApp
        delete [] command[0] ;
        delete [] command ;
   	    return 0;
  }

  if (!enterLoop)
	return 0;

  int retValue = 1;

/* New behaviour - leave it to the app to show the top window
  if (wxTheApp->GetTopWindow()) {
    // show the toplevel frame, only if we are not iconized (from MS-Windows)
    if(wxTheApp->GetShowFrameOnInit() && (nCmdShow!=SW_HIDE)) wxTheApp->GetTopWindow()->Show(TRUE);
  }
*/

  retValue = wxTheApp->OnRun();

  if (wxTheApp->GetTopWindow())
  {
    // Forcibly delete the window.
	if (wxTheApp->GetTopWindow()->IsKindOf(CLASSINFO(wxFrame)) ||
	    wxTheApp->GetTopWindow()->IsKindOf(CLASSINFO(wxDialog)))
	{
    	wxTheApp->GetTopWindow()->Close(TRUE);
    	wxTheApp->DeletePendingObjects();
	}
	else
	{
		delete wxTheApp->GetTopWindow();
		wxTheApp->SetTopWindow(NULL);
	}
  }
  
  wxTheApp->OnExit();
  wxApp::CleanUp();

  delete wxTheApp;
  wxTheApp = NULL;

  delete [] buf ;
  delete [] command[0] ;
  delete [] command ;

#if (DEBUG && USE_MEMORY_TRACING) || USE_DEBUG_CONTEXT
  // At this point we want to check if there are any memory
  // blocks that aren't part of the wxDebugContext itself,
  // as a special case. Then when dumping we need to ignore
  // wxDebugContext, too.
  if (wxDebugContext::CountObjectsLeft() > 0)
  {
    wxTrace("There were memory leaks.\n");
    wxDebugContext::Dump();
    wxDebugContext::PrintStatistics();
  }
  wxDebugContext::SetStream(NULL, NULL);
#endif

  return retValue;
}

#else /*  _WINDLL  */

int wxEntry(WXHINSTANCE hInstance)
{
  wxhInstance = (HINSTANCE) hInstance;
  wxApp::Initialize((WXHINSTANCE) wxhInstance);

  // The app may have declared a global application object, but we recommend
  // the IMPLEMENT_APP macro is used instead, which sets an initializer function
  // for delayed, dynamic app object construction.

  if (!wxTheApp)
  {
  	if (!wxApp::GetInitializerFunction())
  	{
    	MessageBox(NULL, "No initializer - use IMPLEMENT_APP macro.", "wxWindows Error", MB_APPLMODAL | MB_ICONSTOP | MB_OK);
		return 0;
  	}

  	wxTheApp = (* wxApp::GetInitializerFunction()) ();
  }

  if (!wxTheApp) {
    MessageBox(NULL, "You have to define an instance of wxApp!", "wxWindows Error", MB_APPLMODAL | MB_ICONSTOP | MB_OK);
    return 0;
  }

  wxTheApp->argc = 0;
  wxTheApp->argv = NULL;

  wxTheApp->OnInitGui();

  wxTheApp->OnInit();

  if (wxTheApp->GetTopWindow() && wxTheApp->GetTopWindow()->GetHWND()) {
    wxTheApp->GetTopWindow()->Show(TRUE);
  }

  return 1;
}
#endif // _WINDLL

// Static member initialization
wxAppInitializerFunction wxApp::m_appInitFn = (wxAppInitializerFunction) NULL;

wxApp::wxApp(void)
{
  m_topWindow = NULL;
  wxTheApp = this;
//  work_proc = NULL ;
  m_className = "";
//  m_resourceCollection = TRUE;
//  m_pendingCleanup = FALSE;
  m_wantDebugOutput = TRUE ;
  m_appName = "";
  argc = 0;
  argv = NULL;
#ifdef __WINDOWS__
  m_printMode = wxPRINT_WINDOWS;
#else
  m_printMode = wxPRINT_POSTSCRIPT;
#endif
//  work_proc = NULL;
  m_exitOnFrameDelete = TRUE;
//  m_showOnInit = TRUE;
  m_auto3D = TRUE;
}

bool wxApp::Initialized(void)
{
#ifndef _WINDLL
  if (GetTopWindow())
    return TRUE;
  else
    return FALSE;
#endif
#ifdef _WINDLL // Assume initialized if DLL (no way of telling)
  return TRUE;
#endif
}

/*
 * Get and process a message, returning FALSE if WM_QUIT
 * received.
 *
 */
bool wxApp::DoMessage(void)
{
  if (!::GetMessage(&s_currentMsg, (HWND) NULL, 0, 0))
  {
    return FALSE;
  }
    
  // Process the message
  if (!ProcessMessage((WXMSG *)&s_currentMsg))
  {
    ::TranslateMessage(&s_currentMsg);
    wxApp::sm_lastMessageTime = s_currentMsg.time; /* MATTHEW: timeStamp impl. */
    ::DispatchMessage(&s_currentMsg);
  }
  return TRUE;
}

/*
 * Keep trying to process messages until WM_QUIT
 * received.
 *
 * If there are messages to be processed, they will all be
 * processed and OnIdle will not be called.
 * When there are no more messages, OnIdle is called.
 * If OnIdle requests more time,
 * it will be repeatedly called so long as there are no pending messages.
 * A 'feature' of this is that once OnIdle has decided that no more processing
 * is required, then it won't get processing time until further messages
 * are processed (it'll sit in DoMessage).
 */

int wxApp::MainLoop(void)
{
  m_keepGoing = TRUE;
  while (m_keepGoing)
  {
    while (!::PeekMessage(&s_currentMsg, 0, 0, 0, PM_NOREMOVE) &&
           ProcessIdle()) {}
    if (!DoMessage())
      m_keepGoing = FALSE;
  }

  return s_currentMsg.wParam;
}

// Returns TRUE if more time is needed.
bool wxApp::ProcessIdle(void)
{
    wxIdleEvent event;
    event.SetEventObject(this);
    ProcessEvent(event);

    return event.MoreRequested();
}

void wxApp::ExitMainLoop(void)
{
  m_keepGoing = FALSE;
}

bool wxApp::Pending(void)
{
  return (::PeekMessage(&s_currentMsg, 0, 0, 0, PM_NOREMOVE) != 0) ;
}

void wxApp::Dispatch(void)
{
    if (!DoMessage())
      m_keepGoing = FALSE;
}

/*
 * Give all windows a chance to preprocess
 * the message. Some may have accelerator tables, or have
 * MDI complications.
 */
bool wxApp::ProcessMessage(WXMSG *Msg)
{
  MSG *msg = (MSG *)Msg;

  HWND hWnd;

  // Anyone for a message? Try youngest descendants first.
  for (hWnd = msg->hwnd; hWnd != NULL; hWnd = ::GetParent(hWnd))
  {
    wxWindow *wnd = wxFindWinFromHandle((WXHWND) hWnd);
    if (wnd)
    {
       if (wnd->MSWProcessMessage(Msg))
         return TRUE;

       // STOP if we've reached the top of the hierarchy!
//       if (m_topWindow && (wnd == m_topWindow))
//          return FALSE;
    }
  }

  // TODO: Is this now obsolete, given that m_topWindow may not be defined?
  // Does it do anything useful anyway?
//  if (m_topWindow && m_topWindow->MSWProcessMessage(Msg))
//     return TRUE;
    return FALSE;
}

void wxApp::OnIdle(wxIdleEvent& event)
{
  static bool inOnIdle = FALSE;

  // Avoid recursion (via ProcessEvent default case)
  if (inOnIdle)
    return;

  inOnIdle = TRUE;

  // 'Garbage' collection of windows deleted with Close().
  DeletePendingObjects();

  // flush the logged messages if any
  wxLog *pLog = wxLog::GetActiveTarget();
  if ( pLog != NULL && pLog->HasPendingMessages() )
    pLog->Flush();

  // Send OnIdle events to all windows
  bool needMore = SendIdleEvents();
//  bool needMore = FALSE;

  if (needMore)
    event.RequestMore(TRUE);

  inOnIdle = FALSE;
}

// Send idle event to all top-level windows
bool wxApp::SendIdleEvents(void)
{
    bool needMore = FALSE;
	wxNode* node = wxTopLevelWindows.First();
	while (node)
	{
		wxWindow* win = (wxWindow*) node->Data();
		if (SendIdleEvents(win))
            needMore = TRUE;

		node = node->Next();
	}
    return needMore;
}

// Send idle event to window and all subwindows
bool wxApp::SendIdleEvents(wxWindow* win)
{
    bool needMore = FALSE;

	wxIdleEvent event;
	event.SetEventObject(win);
	win->ProcessEvent(event);

    if (event.MoreRequested())
        needMore = TRUE;

	wxNode* node = win->GetChildren()->First();
	while (node)
	{
		wxWindow* win = (wxWindow*) node->Data();
		if (SendIdleEvents(win))
            needMore = TRUE;

		node = node->Next();
	}
    return needMore ;
}

// Windows specific. Intercept keyboard input: by default,
// route it to the active frame or dialog box.
#if WXWIN_COMPATIBILITY == 2
bool wxApp::OldOnCharHook(wxKeyEvent& event)
{
  wxWindow *win = wxGetActiveWindow();
  if (win)
    return win->GetEventHandler()->OldOnCharHook(event);
  else
    return FALSE;
}
#endif

void wxApp::DeletePendingObjects(void)
{
  wxNode *node = wxPendingDelete.First();
  while (node)
  {
    wxObject *obj = (wxObject *)node->Data();
    
    delete obj;

    if (wxPendingDelete.Member(obj))
      delete node;

    // Deleting one object may have deleted other pending
    // objects, so start from beginning of list again.
    node = wxPendingDelete.First();
  }
}

/*
// Free up font objects that are not being used at present.
bool wxApp::DoResourceCleanup(void)
{
//  wxDebugMsg("ResourceCleanup\n");

  if (wxTheFontList)
  {
    wxNode *node = wxTheFontList->First();
    while (node)
    {
      wxGDIObject *obj = (wxGDIObject *)node->Data();
      if ((obj->GetResourceHandle() != 0) && (obj->GetResourceUsage() == 0))
      {
//        wxDebugMsg("Freeing font %ld (GDI object %d)\n", (long)obj, (int)obj->GetResourceHandle());
        obj->FreeResource();
      }
      node = node->Next();
    }
  }
  if (wxThePenList)
  {
    wxNode *node = wxThePenList->First();
    while (node)
    {
      wxGDIObject *obj = (wxGDIObject *)node->Data();
      if ((obj->GetResourceHandle() != 0) && (obj->GetResourceUsage() == 0))
      {
//        wxDebugMsg("Freeing pen %ld (GDI object %d)\n", (long)obj, (int)obj->GetResourceHandle());
        obj->FreeResource();
      }
      node = node->Next();
    }
  }
  if (wxTheBrushList)
  {
    wxNode *node = wxTheBrushList->First();
    while (node)
    {
      wxGDIObject *obj = (wxGDIObject *)node->Data();
      if ((obj->GetResourceHandle() != 0) && (obj->GetResourceUsage() == 0))
      {
//        wxDebugMsg("Freeing brush %ld (GDI object %d)\n", (long)obj, (int)obj->GetResourceHandle());
        obj->FreeResource();
      }
      node = node->Next();
    }
  }

  SetPendingCleanup(FALSE);
  return FALSE;
}
*/

wxLog* wxApp::CreateLogTarget(void)
{
    return new wxLogGui;
}

wxWindow* wxApp::GetTopWindow(void) const
{
    if (m_topWindow)
        return m_topWindow;
    else if (wxTopLevelWindows.Number() > 0)
        return (wxWindow*) wxTopLevelWindows.First()->Data();
    else
        return NULL;
}

void wxExit(void)
{
  wxApp::CleanUp();
  FatalAppExit(0, "Fatal error: exiting");
}

// Yield to incoming messages
bool wxYield(void)
{
  MSG msg;
  // We want to go back to the main message loop
  // if we see a WM_QUIT. (?)
  while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) && msg.message != WM_QUIT)
  {
    if (!wxTheApp->DoMessage())
      break;
  }

  return TRUE;
}

HINSTANCE wxGetInstance()
{
	return wxhInstance;
}

// For some reason, with MSVC++ 1.5, WinMain isn't linked in properly
// if in a separate file. So include it here to ensure it's linked.
#if (defined(_MSC_VER) && !defined(__WIN32__)) || defined(__GNUWIN32__)
#include "main.cpp"
#endif

#undef IN_WX_MAIN_CPP

