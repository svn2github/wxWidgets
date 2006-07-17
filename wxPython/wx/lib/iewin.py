#----------------------------------------------------------------------
# Name:        wx.lib.iewin
# Purpose:     A class that allows the use of the IE web browser
#              ActiveX control
#
# Author:      Robin Dunn
#
# Created:     22-March-2004
# RCS-ID:      $Id$
# Copyright:   (c) 2004 by Total Control Software
# Licence:     wxWindows license
#----------------------------------------------------------------------

# This module was originally generated by the
# wx.activex.GernerateAXModule class but has been tweaked somewhat as
# indicated below.

import wx
import wx.activex

clsID = '{8856F961-340A-11D0-A96B-00C04FD705A2}'
progID = 'Shell.Explorer.2'


# Flags to be used with the RefreshPage method
REFRESH_NORMAL = 0
REFRESH_IFEXPIRED = 1
REFRESH_CONTINUE = 2
REFRESH_COMPLETELY = 3

# Flags to be used with LoadUrl, Navigate, Navigate2 methods
NAV_OpenInNewWindow = 0x1
NAV_NoHistory = 0x2
NAV_NoReadFromCache = 0x4
NAV_NoWriteToCache = 0x8
NAV_AllowAutosearch = 0x10
NAV_BrowserBar = 0x20
NAV_Hyperlink = 0x40



# Create eventTypes and event binders
wxEVT_StatusTextChange = wx.activex.RegisterActiveXEvent('StatusTextChange')
wxEVT_ProgressChange = wx.activex.RegisterActiveXEvent('ProgressChange')
wxEVT_CommandStateChange = wx.activex.RegisterActiveXEvent('CommandStateChange')
wxEVT_DownloadBegin = wx.activex.RegisterActiveXEvent('DownloadBegin')
wxEVT_DownloadComplete = wx.activex.RegisterActiveXEvent('DownloadComplete')
wxEVT_TitleChange = wx.activex.RegisterActiveXEvent('TitleChange')
wxEVT_PropertyChange = wx.activex.RegisterActiveXEvent('PropertyChange')
wxEVT_BeforeNavigate2 = wx.activex.RegisterActiveXEvent('BeforeNavigate2')
wxEVT_NewWindow2 = wx.activex.RegisterActiveXEvent('NewWindow2')
wxEVT_NavigateComplete2 = wx.activex.RegisterActiveXEvent('NavigateComplete2')
wxEVT_DocumentComplete = wx.activex.RegisterActiveXEvent('DocumentComplete')
wxEVT_Quit = wx.activex.RegisterActiveXEvent('OnQuit')
wxEVT_Visible = wx.activex.RegisterActiveXEvent('OnVisible')
wxEVT_ToolBar = wx.activex.RegisterActiveXEvent('OnToolBar')
wxEVT_MenuBar = wx.activex.RegisterActiveXEvent('OnMenuBar')
wxEVT_StatusBar = wx.activex.RegisterActiveXEvent('OnStatusBar')
wxEVT_FullScreen = wx.activex.RegisterActiveXEvent('OnFullScreen')
wxEVT_TheaterMode = wx.activex.RegisterActiveXEvent('OnTheaterMode')
wxEVT_WindowSetResizable = wx.activex.RegisterActiveXEvent('WindowSetResizable')
wxEVT_WindowSetLeft = wx.activex.RegisterActiveXEvent('WindowSetLeft')
wxEVT_WindowSetTop = wx.activex.RegisterActiveXEvent('WindowSetTop')
wxEVT_WindowSetWidth = wx.activex.RegisterActiveXEvent('WindowSetWidth')
wxEVT_WindowSetHeight = wx.activex.RegisterActiveXEvent('WindowSetHeight')
wxEVT_WindowClosing = wx.activex.RegisterActiveXEvent('WindowClosing')
wxEVT_ClientToHostWindow = wx.activex.RegisterActiveXEvent('ClientToHostWindow')
wxEVT_SetSecureLockIcon = wx.activex.RegisterActiveXEvent('SetSecureLockIcon')
wxEVT_FileDownload = wx.activex.RegisterActiveXEvent('FileDownload')
wxEVT_NavigateError = wx.activex.RegisterActiveXEvent('NavigateError')
wxEVT_PrintTemplateInstantiation = wx.activex.RegisterActiveXEvent('PrintTemplateInstantiation')
wxEVT_PrintTemplateTeardown = wx.activex.RegisterActiveXEvent('PrintTemplateTeardown')
wxEVT_UpdatePageStatus = wx.activex.RegisterActiveXEvent('UpdatePageStatus')
wxEVT_PrivacyImpactedStateChange = wx.activex.RegisterActiveXEvent('PrivacyImpactedStateChange')

EVT_StatusTextChange = wx.PyEventBinder(wxEVT_StatusTextChange, 1)
EVT_ProgressChange = wx.PyEventBinder(wxEVT_ProgressChange, 1)
EVT_CommandStateChange = wx.PyEventBinder(wxEVT_CommandStateChange, 1)
EVT_DownloadBegin = wx.PyEventBinder(wxEVT_DownloadBegin, 1)
EVT_DownloadComplete = wx.PyEventBinder(wxEVT_DownloadComplete, 1)
EVT_TitleChange = wx.PyEventBinder(wxEVT_TitleChange, 1)
EVT_PropertyChange = wx.PyEventBinder(wxEVT_PropertyChange, 1)
EVT_BeforeNavigate2 = wx.PyEventBinder(wxEVT_BeforeNavigate2, 1)
EVT_NewWindow2 = wx.PyEventBinder(wxEVT_NewWindow2, 1)
EVT_NavigateComplete2 = wx.PyEventBinder(wxEVT_NavigateComplete2, 1)
EVT_DocumentComplete = wx.PyEventBinder(wxEVT_DocumentComplete, 1)
EVT_Quit = wx.PyEventBinder(wxEVT_Quit, 1)
EVT_Visible = wx.PyEventBinder(wxEVT_Visible, 1)
EVT_ToolBar = wx.PyEventBinder(wxEVT_ToolBar, 1)
EVT_MenuBar = wx.PyEventBinder(wxEVT_MenuBar, 1)
EVT_StatusBar = wx.PyEventBinder(wxEVT_StatusBar, 1)
EVT_FullScreen = wx.PyEventBinder(wxEVT_FullScreen, 1)
EVT_TheaterMode = wx.PyEventBinder(wxEVT_TheaterMode, 1)
EVT_WindowSetResizable = wx.PyEventBinder(wxEVT_WindowSetResizable, 1)
EVT_WindowSetLeft = wx.PyEventBinder(wxEVT_WindowSetLeft, 1)
EVT_WindowSetTop = wx.PyEventBinder(wxEVT_WindowSetTop, 1)
EVT_WindowSetWidth = wx.PyEventBinder(wxEVT_WindowSetWidth, 1)
EVT_WindowSetHeight = wx.PyEventBinder(wxEVT_WindowSetHeight, 1)
EVT_WindowClosing = wx.PyEventBinder(wxEVT_WindowClosing, 1)
EVT_ClientToHostWindow = wx.PyEventBinder(wxEVT_ClientToHostWindow, 1)
EVT_SetSecureLockIcon = wx.PyEventBinder(wxEVT_SetSecureLockIcon, 1)
EVT_FileDownload = wx.PyEventBinder(wxEVT_FileDownload, 1)
EVT_NavigateError = wx.PyEventBinder(wxEVT_NavigateError, 1)
EVT_PrintTemplateInstantiation = wx.PyEventBinder(wxEVT_PrintTemplateInstantiation, 1)
EVT_PrintTemplateTeardown = wx.PyEventBinder(wxEVT_PrintTemplateTeardown, 1)
EVT_UpdatePageStatus = wx.PyEventBinder(wxEVT_UpdatePageStatus, 1)
EVT_PrivacyImpactedStateChange = wx.PyEventBinder(wxEVT_PrivacyImpactedStateChange, 1)


# For this there are a few special methods implemented in C++ in the
# IEHtmlWindowBase class, so derive from it instead of ActiveXWindow.
class IEHtmlWindow(wx.activex.IEHtmlWindowBase):
    def __init__(self, parent, ID=-1, pos=wx.DefaultPosition,
                 size=wx.DefaultSize, style=0, name='IEHtmlWindow'):
        wx.activex.IEHtmlWindowBase.__init__(self, parent,
            wx.activex.CLSID('{8856F961-340A-11D0-A96B-00C04FD705A2}'),
            ID, pos, size, style, name)

    # Methods from IEHtmlWindowBase.  Redirected from here just for
    # the sake of completeness...
    def LoadString(self, html):
        """Load the html document from a string"""
        return wx.activex.IEHtmlWindowBase.LoadString(self, html)


    def LoadStream(self, stream):
        """
        Load the html document from a wx.InputStream or a Python
        file-like object.
        """
        return wx.activex.IEHtmlWindowBase.LoadStream(self, stream)


    def LoadUrl(self, URL, Flags=0):
        """Load the document from url."""
        return self.Navigate2(URL, Flags)


    def GetStringSelection(self, asHTML=True):
        """
        Returns the contents of the selected portion of the document as
        either html or plain text.
        """
        return wx.activex.IEHtmlWindowBase.GetStringSelection(self, asHTML)


    def GetText(self, asHTML=True):
        """
        Returns the contents of the the html document as either html or plain text.
        """
        return wx.activex.IEHtmlWindowBase.GetText(self, asHTML)
        
   
    def SetCharset(self, charset):
        """"""
        return wx.activex.IEHtmlWindowBase.SetCharset(self, charset)

        
    # Methods exported by the ActiveX object
    def QueryInterface(self, riid):
        return self.CallAXMethod('QueryInterface', riid)

    def AddRef(self):
        return self.CallAXMethod('AddRef')

    def Release(self):
        return self.CallAXMethod('Release')

    def GetTypeInfoCount(self):
        return self.CallAXMethod('GetTypeInfoCount')

    def GetTypeInfo(self, itinfo, lcid):
        return self.CallAXMethod('GetTypeInfo', itinfo, lcid)

    def GetIDsOfNames(self, riid, rgszNames, cNames, lcid):
        return self.CallAXMethod('GetIDsOfNames', riid, rgszNames, cNames, lcid)

    def Invoke(self, dispidMember, riid, lcid, wFlags, pdispparams):
        return self.CallAXMethod('Invoke', dispidMember, riid, lcid, wFlags, pdispparams)

    def GoBack(self):
        return self.CallAXMethod('GoBack')

    def GoForward(self):
        return self.CallAXMethod('GoForward')

    def GoHome(self):
        return self.CallAXMethod('GoHome')

    def GoSearch(self):
        return self.CallAXMethod('GoSearch')

    # added default for Flags
    def Navigate(self, URL, Flags=0, TargetFrameName=None, PostData=None, Headers=None):
        return self.CallAXMethod('Navigate', URL, Flags, TargetFrameName, PostData, Headers)

    # Removed to prevent conflict with wx.Window.Refresh
    #def Refresh(self):
    #    return self.CallAXMethod('Refresh')

    # renamed
    def RefreshPage(self, Level=REFRESH_NORMAL):
        return self.CallAXMethod('Refresh2', Level)

    def Stop(self):
        return self.CallAXMethod('Stop')

    def Quit(self):
        return self.CallAXMethod('Quit')

    def ClientToWindow(self, pcx, pcy):
        return self.CallAXMethod('ClientToWindow', pcx, pcy)

    def PutProperty(self, Property, vtValue):
        return self.CallAXMethod('PutProperty', Property, vtValue)

    def GetProperty(self, Property):
        return self.CallAXMethod('GetProperty', Property)

    # added default for flags
    def Navigate2(self, URL, Flags=0, TargetFrameName=None, PostData=None, Headers=None):
        return self.CallAXMethod('Navigate2', URL, Flags, TargetFrameName, PostData, Headers)

    def QueryStatusWB(self, cmdID):
        return self.CallAXMethod('QueryStatusWB', cmdID)

    def ExecWB(self, cmdID, cmdexecopt, pvaIn, pvaOut=None):
        return self.CallAXMethod('ExecWB', cmdID, cmdexecopt, pvaIn, pvaOut)

    def ShowBrowserBar(self, pvaClsid, pvarShow, pvarSize=None):
        return self.CallAXMethod('ShowBrowserBar', pvaClsid, pvarShow, pvarSize)

    # Getters, Setters and properties
    def _get_Application(self):
        return self.GetAXProp('Application')
    application = property(_get_Application, None)

    def _get_Parent(self):
        return self.GetAXProp('Parent')
    parent = property(_get_Parent, None)

    def _get_Container(self):
        return self.GetAXProp('Container')
    container = property(_get_Container, None)

    def _get_Document(self):
        return self.GetAXProp('Document')
    document = property(_get_Document, None)

    def _get_TopLevelContainer(self):
        return self.GetAXProp('TopLevelContainer')
    toplevelcontainer = property(_get_TopLevelContainer, None)

    def _get_Type(self):
        return self.GetAXProp('Type')
    type = property(_get_Type, None)

    def _get_Left(self):
        return self.GetAXProp('Left')
    def _set_Left(self, Left):
        self.SetAXProp('Left', Left)
    left = property(_get_Left, _set_Left)

    def _get_Top(self):
        return self.GetAXProp('Top')
    def _set_Top(self, Top):
        self.SetAXProp('Top', Top)
    top = property(_get_Top, _set_Top)

    def _get_Width(self):
        return self.GetAXProp('Width')
    def _set_Width(self, Width):
        self.SetAXProp('Width', Width)
    width = property(_get_Width, _set_Width)

    def _get_Height(self):
        return self.GetAXProp('Height')
    def _set_Height(self, Height):
        self.SetAXProp('Height', Height)
    height = property(_get_Height, _set_Height)

    def _get_LocationName(self):
        return self.GetAXProp('LocationName')
    locationname = property(_get_LocationName, None)

    def _get_LocationURL(self):
        return self.GetAXProp('LocationURL')
    locationurl = property(_get_LocationURL, None)

    def _get_Busy(self):
        return self.GetAXProp('Busy')
    busy = property(_get_Busy, None)

    def _get_Name(self):
        return self.GetAXProp('Name')
    name = property(_get_Name, None)

    def _get_HWND(self):
        return self.GetAXProp('HWND')
    hwnd = property(_get_HWND, None)

    def _get_FullName(self):
        return self.GetAXProp('FullName')
    fullname = property(_get_FullName, None)

    def _get_Path(self):
        return self.GetAXProp('Path')
    path = property(_get_Path, None)

    def _get_Visible(self):
        return self.GetAXProp('Visible')
    def _set_Visible(self, Visible):
        self.SetAXProp('Visible', Visible)
    visible = property(_get_Visible, _set_Visible)

    def _get_StatusBar(self):
        return self.GetAXProp('StatusBar')
    def _set_StatusBar(self, StatusBar):
        self.SetAXProp('StatusBar', StatusBar)
    statusbar = property(_get_StatusBar, _set_StatusBar)

    def _get_StatusText(self):
        return self.GetAXProp('StatusText')
    def _set_StatusText(self, StatusText):
        self.SetAXProp('StatusText', StatusText)
    statustext = property(_get_StatusText, _set_StatusText)

    def _get_ToolBar(self):
        return self.GetAXProp('ToolBar')
    def _set_ToolBar(self, ToolBar):
        self.SetAXProp('ToolBar', ToolBar)
    toolbar = property(_get_ToolBar, _set_ToolBar)

    def _get_MenuBar(self):
        return self.GetAXProp('MenuBar')
    def _set_MenuBar(self, MenuBar):
        self.SetAXProp('MenuBar', MenuBar)
    menubar = property(_get_MenuBar, _set_MenuBar)

    def _get_FullScreen(self):
        return self.GetAXProp('FullScreen')
    def _set_FullScreen(self, FullScreen):
        self.SetAXProp('FullScreen', FullScreen)
    fullscreen = property(_get_FullScreen, _set_FullScreen)

    def _get_ReadyState(self):
        return self.GetAXProp('ReadyState')
    readystate = property(_get_ReadyState, None)

    def _get_Offline(self):
        return self.GetAXProp('Offline')
    def _set_Offline(self, Offline):
        self.SetAXProp('Offline', Offline)
    offline = property(_get_Offline, _set_Offline)

    def _get_Silent(self):
        return self.GetAXProp('Silent')
    def _set_Silent(self, Silent):
        self.SetAXProp('Silent', Silent)
    silent = property(_get_Silent, _set_Silent)

    def _get_RegisterAsBrowser(self):
        return self.GetAXProp('RegisterAsBrowser')
    def _set_RegisterAsBrowser(self, RegisterAsBrowser):
        self.SetAXProp('RegisterAsBrowser', RegisterAsBrowser)
    registerasbrowser = property(_get_RegisterAsBrowser, _set_RegisterAsBrowser)

    def _get_RegisterAsDropTarget(self):
        return self.GetAXProp('RegisterAsDropTarget')
    def _set_RegisterAsDropTarget(self, RegisterAsDropTarget):
        self.SetAXProp('RegisterAsDropTarget', RegisterAsDropTarget)
    registerasdroptarget = property(_get_RegisterAsDropTarget, _set_RegisterAsDropTarget)

    def _get_TheaterMode(self):
        return self.GetAXProp('TheaterMode')
    def _set_TheaterMode(self, TheaterMode):
        self.SetAXProp('TheaterMode', TheaterMode)
    theatermode = property(_get_TheaterMode, _set_TheaterMode)

    def _get_AddressBar(self):
        return self.GetAXProp('AddressBar')
    def _set_AddressBar(self, AddressBar):
        self.SetAXProp('AddressBar', AddressBar)
    addressbar = property(_get_AddressBar, _set_AddressBar)

    def _get_Resizable(self):
        return self.GetAXProp('Resizable')
    def _set_Resizable(self, Resizable):
        self.SetAXProp('Resizable', Resizable)
    resizable = property(_get_Resizable, _set_Resizable)


#  PROPERTIES
#  --------------------
#  application
#      type:VT_DISPATCH  arg:VT_EMPTY  canGet:True  canSet:False
#  
#  parent
#      type:VT_DISPATCH  arg:VT_EMPTY  canGet:True  canSet:False
#  
#  container
#      type:VT_DISPATCH  arg:VT_EMPTY  canGet:True  canSet:False
#  
#  document
#      type:VT_DISPATCH  arg:VT_EMPTY  canGet:True  canSet:False
#  
#  toplevelcontainer
#      type:bool  arg:VT_EMPTY  canGet:True  canSet:False
#  
#  type
#      type:string  arg:VT_EMPTY  canGet:True  canSet:False
#  
#  left
#      type:int  arg:int  canGet:True  canSet:True
#  
#  top
#      type:int  arg:int  canGet:True  canSet:True
#  
#  width
#      type:int  arg:int  canGet:True  canSet:True
#  
#  height
#      type:int  arg:int  canGet:True  canSet:True
#  
#  locationname
#      type:string  arg:VT_EMPTY  canGet:True  canSet:False
#  
#  locationurl
#      type:string  arg:VT_EMPTY  canGet:True  canSet:False
#  
#  busy
#      type:bool  arg:VT_EMPTY  canGet:True  canSet:False
#  
#  name
#      type:string  arg:VT_EMPTY  canGet:True  canSet:False
#  
#  hwnd
#      type:int  arg:VT_EMPTY  canGet:True  canSet:False
#  
#  fullname
#      type:string  arg:VT_EMPTY  canGet:True  canSet:False
#  
#  path
#      type:string  arg:VT_EMPTY  canGet:True  canSet:False
#  
#  visible
#      type:bool  arg:bool  canGet:True  canSet:True
#  
#  statusbar
#      type:bool  arg:bool  canGet:True  canSet:True
#  
#  statustext
#      type:string  arg:string  canGet:True  canSet:True
#  
#  toolbar
#      type:int  arg:int  canGet:True  canSet:True
#  
#  menubar
#      type:bool  arg:bool  canGet:True  canSet:True
#  
#  fullscreen
#      type:bool  arg:bool  canGet:True  canSet:True
#  
#  readystate
#      type:unsupported type 29  arg:VT_EMPTY  canGet:True  canSet:False
#  
#  offline
#      type:bool  arg:bool  canGet:True  canSet:True
#  
#  silent
#      type:bool  arg:bool  canGet:True  canSet:True
#  
#  registerasbrowser
#      type:bool  arg:bool  canGet:True  canSet:True
#  
#  registerasdroptarget
#      type:bool  arg:bool  canGet:True  canSet:True
#  
#  theatermode
#      type:bool  arg:bool  canGet:True  canSet:True
#  
#  addressbar
#      type:bool  arg:bool  canGet:True  canSet:True
#  
#  resizable
#      type:bool  arg:bool  canGet:True  canSet:True
#  
#  
#  
#  
#  METHODS
#  --------------------
#  QueryInterface
#      retType:  VT_VOID
#      params:
#          riid
#              in:True  out:False  optional:False  type:unsupported type 29
#          ppvObj
#              in:False  out:True  optional:False  type:unsupported type 26
#  
#  AddRef
#      retType:  int
#  
#  Release
#      retType:  int
#  
#  GetTypeInfoCount
#      retType:  VT_VOID
#      params:
#          pctinfo
#              in:False  out:True  optional:False  type:int
#  
#  GetTypeInfo
#      retType:  VT_VOID
#      params:
#          itinfo
#              in:True  out:False  optional:False  type:int
#          lcid
#              in:True  out:False  optional:False  type:int
#          pptinfo
#              in:False  out:True  optional:False  type:unsupported type 26
#  
#  GetIDsOfNames
#      retType:  VT_VOID
#      params:
#          riid
#              in:True  out:False  optional:False  type:unsupported type 29
#          rgszNames
#              in:True  out:False  optional:False  type:unsupported type 26
#          cNames
#              in:True  out:False  optional:False  type:int
#          lcid
#              in:True  out:False  optional:False  type:int
#          rgdispid
#              in:False  out:True  optional:False  type:int
#  
#  Invoke
#      retType:  VT_VOID
#      params:
#          dispidMember
#              in:True  out:False  optional:False  type:int
#          riid
#              in:True  out:False  optional:False  type:unsupported type 29
#          lcid
#              in:True  out:False  optional:False  type:int
#          wFlags
#              in:True  out:False  optional:False  type:int
#          pdispparams
#              in:True  out:False  optional:False  type:unsupported type 29
#          pvarResult
#              in:False  out:True  optional:False  type:VT_VARIANT
#          pexcepinfo
#              in:False  out:True  optional:False  type:unsupported type 29
#          puArgErr
#              in:False  out:True  optional:False  type:int
#  
#  GoBack
#      retType:  VT_VOID
#  
#  GoForward
#      retType:  VT_VOID
#  
#  GoHome
#      retType:  VT_VOID
#  
#  GoSearch
#      retType:  VT_VOID
#  
#  Navigate
#      retType:  VT_VOID
#      params:
#          URL
#              in:True  out:False  optional:False  type:string
#          Flags
#              in:True  out:False  optional:False  type:VT_VARIANT
#          TargetFrameName
#              in:True  out:False  optional:True  type:VT_VARIANT
#          PostData
#              in:True  out:False  optional:True  type:VT_VARIANT
#          Headers
#              in:True  out:False  optional:True  type:VT_VARIANT
#  
#  Refresh
#      retType:  VT_VOID
#  
#  Refresh2
#      retType:  VT_VOID
#      params:
#          Level
#              in:True  out:False  optional:False  type:VT_VARIANT
#  
#  Stop
#      retType:  VT_VOID
#  
#  Quit
#      retType:  VT_VOID
#  
#  ClientToWindow
#      retType:  VT_VOID
#      params:
#          pcx
#              in:True  out:True  optional:False  type:int
#          pcy
#              in:True  out:True  optional:False  type:int
#  
#  PutProperty
#      retType:  VT_VOID
#      params:
#          Property
#              in:True  out:False  optional:False  type:string
#          vtValue
#              in:True  out:False  optional:False  type:VT_VARIANT
#  
#  GetProperty
#      retType:  VT_VARIANT
#      params:
#          Property
#              in:True  out:False  optional:False  type:string
#  
#  Navigate2
#      retType:  VT_VOID
#      params:
#          URL
#              in:True  out:False  optional:False  type:VT_VARIANT
#          Flags
#              in:True  out:False  optional:False  type:VT_VARIANT
#          TargetFrameName
#              in:True  out:False  optional:True  type:VT_VARIANT
#          PostData
#              in:True  out:False  optional:True  type:VT_VARIANT
#          Headers
#              in:True  out:False  optional:True  type:VT_VARIANT
#  
#  QueryStatusWB
#      retType:  unsupported type 29
#      params:
#          cmdID
#              in:True  out:False  optional:False  type:unsupported type 29
#  
#  ExecWB
#      retType:  VT_VOID
#      params:
#          cmdID
#              in:True  out:False  optional:False  type:unsupported type 29
#          cmdexecopt
#              in:True  out:False  optional:False  type:unsupported type 29
#          pvaIn
#              in:True  out:False  optional:False  type:VT_VARIANT
#          pvaOut
#              in:True  out:True  optional:True  type:VT_VARIANT
#  
#  ShowBrowserBar
#      retType:  VT_VOID
#      params:
#          pvaClsid
#              in:True  out:False  optional:False  type:VT_VARIANT
#          pvarShow
#              in:True  out:False  optional:False  type:VT_VARIANT
#          pvarSize
#              in:True  out:False  optional:True  type:VT_VARIANT
#  
#  
#  
#  
#  EVENTS
#  --------------------
#  StatusTextChange
#      retType:  VT_VOID
#      params:
#          Text
#              in:True  out:False  optional:False  type:string
#  
#  ProgressChange
#      retType:  VT_VOID
#      params:
#          Progress
#              in:True  out:False  optional:False  type:int
#          ProgressMax
#              in:True  out:False  optional:False  type:int
#  
#  CommandStateChange
#      retType:  VT_VOID
#      params:
#          Command
#              in:True  out:False  optional:False  type:int
#          Enable
#              in:True  out:False  optional:False  type:bool
#  
#  DownloadBegin
#      retType:  VT_VOID
#  
#  DownloadComplete
#      retType:  VT_VOID
#  
#  TitleChange
#      retType:  VT_VOID
#      params:
#          Text
#              in:True  out:False  optional:False  type:string
#  
#  PropertyChange
#      retType:  VT_VOID
#      params:
#          szProperty
#              in:True  out:False  optional:False  type:string
#  
#  BeforeNavigate2
#      retType:  VT_VOID
#      params:
#          pDisp
#              in:True  out:False  optional:False  type:VT_DISPATCH
#          URL
#              in:True  out:False  optional:False  type:VT_VARIANT
#          Flags
#              in:True  out:False  optional:False  type:VT_VARIANT
#          TargetFrameName
#              in:True  out:False  optional:False  type:VT_VARIANT
#          PostData
#              in:True  out:False  optional:False  type:VT_VARIANT
#          Headers
#              in:True  out:False  optional:False  type:VT_VARIANT
#          Cancel
#              in:True  out:True  optional:False  type:bool
#  
#  NewWindow2
#      retType:  VT_VOID
#      params:
#          ppDisp
#              in:True  out:True  optional:False  type:VT_DISPATCH
#          Cancel
#              in:True  out:True  optional:False  type:bool
#  
#  NavigateComplete2
#      retType:  VT_VOID
#      params:
#          pDisp
#              in:True  out:False  optional:False  type:VT_DISPATCH
#          URL
#              in:True  out:False  optional:False  type:VT_VARIANT
#  
#  DocumentComplete
#      retType:  VT_VOID
#      params:
#          pDisp
#              in:True  out:False  optional:False  type:VT_DISPATCH
#          URL
#              in:True  out:False  optional:False  type:VT_VARIANT
#  
#  Quit
#      retType:  VT_VOID
#  
#  Visible
#      retType:  VT_VOID
#      params:
#          Visible
#              in:True  out:False  optional:False  type:bool
#  
#  ToolBar
#      retType:  VT_VOID
#      params:
#          ToolBar
#              in:True  out:False  optional:False  type:bool
#  
#  MenuBar
#      retType:  VT_VOID
#      params:
#          MenuBar
#              in:True  out:False  optional:False  type:bool
#  
#  StatusBar
#      retType:  VT_VOID
#      params:
#          StatusBar
#              in:True  out:False  optional:False  type:bool
#  
#  FullScreen
#      retType:  VT_VOID
#      params:
#          FullScreen
#              in:True  out:False  optional:False  type:bool
#  
#  TheaterMode
#      retType:  VT_VOID
#      params:
#          TheaterMode
#              in:True  out:False  optional:False  type:bool
#  
#  WindowSetResizable
#      retType:  VT_VOID
#      params:
#          Resizable
#              in:True  out:False  optional:False  type:bool
#  
#  WindowSetLeft
#      retType:  VT_VOID
#      params:
#          Left
#              in:True  out:False  optional:False  type:int
#  
#  WindowSetTop
#      retType:  VT_VOID
#      params:
#          Top
#              in:True  out:False  optional:False  type:int
#  
#  WindowSetWidth
#      retType:  VT_VOID
#      params:
#          Width
#              in:True  out:False  optional:False  type:int
#  
#  WindowSetHeight
#      retType:  VT_VOID
#      params:
#          Height
#              in:True  out:False  optional:False  type:int
#  
#  WindowClosing
#      retType:  VT_VOID
#      params:
#          IsChildWindow
#              in:True  out:False  optional:False  type:bool
#          Cancel
#              in:True  out:True  optional:False  type:bool
#  
#  ClientToHostWindow
#      retType:  VT_VOID
#      params:
#          CX
#              in:True  out:True  optional:False  type:int
#          CY
#              in:True  out:True  optional:False  type:int
#  
#  SetSecureLockIcon
#      retType:  VT_VOID
#      params:
#          SecureLockIcon
#              in:True  out:False  optional:False  type:int
#  
#  FileDownload
#      retType:  VT_VOID
#      params:
#          Cancel
#              in:True  out:True  optional:False  type:bool
#  
#  NavigateError
#      retType:  VT_VOID
#      params:
#          pDisp
#              in:True  out:False  optional:False  type:VT_DISPATCH
#          URL
#              in:True  out:False  optional:False  type:VT_VARIANT
#          Frame
#              in:True  out:False  optional:False  type:VT_VARIANT
#          StatusCode
#              in:True  out:False  optional:False  type:VT_VARIANT
#          Cancel
#              in:True  out:True  optional:False  type:bool
#  
#  PrintTemplateInstantiation
#      retType:  VT_VOID
#      params:
#          pDisp
#              in:True  out:False  optional:False  type:VT_DISPATCH
#  
#  PrintTemplateTeardown
#      retType:  VT_VOID
#      params:
#          pDisp
#              in:True  out:False  optional:False  type:VT_DISPATCH
#  
#  UpdatePageStatus
#      retType:  VT_VOID
#      params:
#          pDisp
#              in:True  out:False  optional:False  type:VT_DISPATCH
#          nPage
#              in:True  out:False  optional:False  type:VT_VARIANT
#          fDone
#              in:True  out:False  optional:False  type:VT_VARIANT
#  
#  PrivacyImpactedStateChange
#      retType:  VT_VOID
#      params:
#          bImpacted
#              in:True  out:False  optional:False  type:bool
#  
#  
#  
#  
