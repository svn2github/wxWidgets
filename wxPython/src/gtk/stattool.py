# This file was created automatically by SWIG.
import stattoolc

from misc import *

from windows import *

from gdi import *

from clip_dnd import *

from controls import *

from events import *
import wx
class wxStatusBarPtr(wxWindowPtr):
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def Create(self, *_args, **_kwargs):
        val = apply(stattoolc.wxStatusBar_Create,(self,) + _args, _kwargs)
        return val
    def GetFieldRect(self, *_args, **_kwargs):
        val = apply(stattoolc.wxStatusBar_GetFieldRect,(self,) + _args, _kwargs)
        if val: val = wxRectPtr(val) ; val.thisown = 1
        return val
    def GetFieldsCount(self, *_args, **_kwargs):
        val = apply(stattoolc.wxStatusBar_GetFieldsCount,(self,) + _args, _kwargs)
        return val
    def GetStatusText(self, *_args, **_kwargs):
        val = apply(stattoolc.wxStatusBar_GetStatusText,(self,) + _args, _kwargs)
        return val
    def GetBorderX(self, *_args, **_kwargs):
        val = apply(stattoolc.wxStatusBar_GetBorderX,(self,) + _args, _kwargs)
        return val
    def GetBorderY(self, *_args, **_kwargs):
        val = apply(stattoolc.wxStatusBar_GetBorderY,(self,) + _args, _kwargs)
        return val
    def SetFieldsCount(self, *_args, **_kwargs):
        val = apply(stattoolc.wxStatusBar_SetFieldsCount,(self,) + _args, _kwargs)
        return val
    def SetStatusText(self, *_args, **_kwargs):
        val = apply(stattoolc.wxStatusBar_SetStatusText,(self,) + _args, _kwargs)
        return val
    def SetStatusWidths(self, *_args, **_kwargs):
        val = apply(stattoolc.wxStatusBar_SetStatusWidths,(self,) + _args, _kwargs)
        return val
    def SetMinHeight(self, *_args, **_kwargs):
        val = apply(stattoolc.wxStatusBar_SetMinHeight,(self,) + _args, _kwargs)
        return val
    def __repr__(self):
        return "<C wxStatusBar instance at %s>" % (self.this,)
class wxStatusBar(wxStatusBarPtr):
    def __init__(self,*_args,**_kwargs):
        self.this = apply(stattoolc.new_wxStatusBar,_args,_kwargs)
        self.thisown = 1
        self._setOORInfo(self)



def wxPreStatusBar(*_args,**_kwargs):
    val = wxStatusBarPtr(apply(stattoolc.new_wxPreStatusBar,_args,_kwargs))
    val.thisown = 1
    val._setOORInfo(val)
    return val


class wxToolBarToolBasePtr(wxObjectPtr):
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def Destroy(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_Destroy,(self,) + _args, _kwargs)
        return val
    def GetId(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_GetId,(self,) + _args, _kwargs)
        return val
    def GetControl(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_GetControl,(self,) + _args, _kwargs)
        return val
    def GetToolBar(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_GetToolBar,(self,) + _args, _kwargs)
        return val
    def IsButton(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_IsButton,(self,) + _args, _kwargs)
        return val
    def IsControl(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_IsControl,(self,) + _args, _kwargs)
        return val
    def IsSeparator(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_IsSeparator,(self,) + _args, _kwargs)
        return val
    def GetStyle(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_GetStyle,(self,) + _args, _kwargs)
        return val
    def GetKind(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_GetKind,(self,) + _args, _kwargs)
        return val
    def IsEnabled(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_IsEnabled,(self,) + _args, _kwargs)
        return val
    def IsToggled(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_IsToggled,(self,) + _args, _kwargs)
        return val
    def CanBeToggled(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_CanBeToggled,(self,) + _args, _kwargs)
        return val
    def GetNormalBitmap(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_GetNormalBitmap,(self,) + _args, _kwargs)
        if val: val = wxBitmapPtr(val) 
        return val
    def GetDisabledBitmap(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_GetDisabledBitmap,(self,) + _args, _kwargs)
        if val: val = wxBitmapPtr(val) 
        return val
    def GetBitmap(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_GetBitmap,(self,) + _args, _kwargs)
        if val: val = wxBitmapPtr(val) ; val.thisown = 1
        return val
    def GetLabel(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_GetLabel,(self,) + _args, _kwargs)
        return val
    def GetShortHelp(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_GetShortHelp,(self,) + _args, _kwargs)
        return val
    def GetLongHelp(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_GetLongHelp,(self,) + _args, _kwargs)
        return val
    def Enable(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_Enable,(self,) + _args, _kwargs)
        return val
    def Toggle(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_Toggle,(self,) + _args, _kwargs)
        return val
    def SetToggle(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_SetToggle,(self,) + _args, _kwargs)
        return val
    def SetShortHelp(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_SetShortHelp,(self,) + _args, _kwargs)
        return val
    def SetLongHelp(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_SetLongHelp,(self,) + _args, _kwargs)
        return val
    def SetNormalBitmap(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_SetNormalBitmap,(self,) + _args, _kwargs)
        return val
    def SetDisabledBitmap(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_SetDisabledBitmap,(self,) + _args, _kwargs)
        return val
    def SetLabel(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_SetLabel,(self,) + _args, _kwargs)
        return val
    def Detach(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_Detach,(self,) + _args, _kwargs)
        return val
    def Attach(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_Attach,(self,) + _args, _kwargs)
        return val
    def GetClientData(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_GetClientData,(self,) + _args, _kwargs)
        return val
    def SetClientData(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarToolBase_SetClientData,(self,) + _args, _kwargs)
        return val
    def __repr__(self):
        return "<C wxToolBarToolBase instance at %s>" % (self.this,)
    
    GetBitmap1 = GetNormalBitmap
    GetBitmap2 = GetDisabledBitmap
    SetBitmap1 = SetNormalBitmap
    SetBitmap2 = SetDisabledBitmap
    
class wxToolBarToolBase(wxToolBarToolBasePtr):
    def __init__(self,this):
        self.this = this




class wxToolBarBasePtr(wxControlPtr):
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def AddTool(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_AddTool,(self,) + _args, _kwargs)
        return val
    def AddSimpleTool(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_AddSimpleTool,(self,) + _args, _kwargs)
        return val
    def AddCheckTool(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_AddCheckTool,(self,) + _args, _kwargs)
        return val
    def AddRadioTool(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_AddRadioTool,(self,) + _args, _kwargs)
        return val
    def InsertTool(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_InsertTool,(self,) + _args, _kwargs)
        return val
    def InsertSimpleTool(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_InsertSimpleTool,(self,) + _args, _kwargs)
        return val
    def AddControl(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_AddControl,(self,) + _args, _kwargs)
        return val
    def InsertControl(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_InsertControl,(self,) + _args, _kwargs)
        return val
    def AddSeparator(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_AddSeparator,(self,) + _args, _kwargs)
        return val
    def InsertSeparator(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_InsertSeparator,(self,) + _args, _kwargs)
        return val
    def RemoveTool(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_RemoveTool,(self,) + _args, _kwargs)
        return val
    def DeleteToolByPos(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_DeleteToolByPos,(self,) + _args, _kwargs)
        return val
    def DeleteTool(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_DeleteTool,(self,) + _args, _kwargs)
        return val
    def ClearTools(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_ClearTools,(self,) + _args, _kwargs)
        return val
    def Realize(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_Realize,(self,) + _args, _kwargs)
        return val
    def EnableTool(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_EnableTool,(self,) + _args, _kwargs)
        return val
    def ToggleTool(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_ToggleTool,(self,) + _args, _kwargs)
        return val
    def SetToggle(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_SetToggle,(self,) + _args, _kwargs)
        return val
    def GetToolClientData(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_GetToolClientData,(self,) + _args, _kwargs)
        return val
    def SetToolClientData(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_SetToolClientData,(self,) + _args, _kwargs)
        return val
    def GetToolState(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_GetToolState,(self,) + _args, _kwargs)
        return val
    def GetToolEnabled(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_GetToolEnabled,(self,) + _args, _kwargs)
        return val
    def SetToolShortHelp(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_SetToolShortHelp,(self,) + _args, _kwargs)
        return val
    def GetToolShortHelp(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_GetToolShortHelp,(self,) + _args, _kwargs)
        return val
    def SetToolLongHelp(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_SetToolLongHelp,(self,) + _args, _kwargs)
        return val
    def GetToolLongHelp(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_GetToolLongHelp,(self,) + _args, _kwargs)
        return val
    def SetMarginsXY(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_SetMarginsXY,(self,) + _args, _kwargs)
        return val
    def SetMargins(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_SetMargins,(self,) + _args, _kwargs)
        return val
    def SetToolPacking(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_SetToolPacking,(self,) + _args, _kwargs)
        return val
    def SetToolSeparation(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_SetToolSeparation,(self,) + _args, _kwargs)
        return val
    def GetToolMargins(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_GetToolMargins,(self,) + _args, _kwargs)
        if val: val = wxSizePtr(val) ; val.thisown = 1
        return val
    def GetMargins(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_GetMargins,(self,) + _args, _kwargs)
        if val: val = wxSizePtr(val) ; val.thisown = 1
        return val
    def GetToolPacking(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_GetToolPacking,(self,) + _args, _kwargs)
        return val
    def GetToolSeparation(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_GetToolSeparation,(self,) + _args, _kwargs)
        return val
    def SetRows(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_SetRows,(self,) + _args, _kwargs)
        return val
    def SetMaxRowsCols(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_SetMaxRowsCols,(self,) + _args, _kwargs)
        return val
    def GetMaxRows(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_GetMaxRows,(self,) + _args, _kwargs)
        return val
    def GetMaxCols(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_GetMaxCols,(self,) + _args, _kwargs)
        return val
    def SetToolBitmapSize(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_SetToolBitmapSize,(self,) + _args, _kwargs)
        return val
    def GetToolBitmapSize(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_GetToolBitmapSize,(self,) + _args, _kwargs)
        if val: val = wxSizePtr(val) ; val.thisown = 1
        return val
    def GetToolSize(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_GetToolSize,(self,) + _args, _kwargs)
        if val: val = wxSizePtr(val) ; val.thisown = 1
        return val
    def FindToolForPosition(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_FindToolForPosition,(self,) + _args, _kwargs)
        return val
    def IsVertical(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarBase_IsVertical,(self,) + _args, _kwargs)
        return val
    def __repr__(self):
        return "<C wxToolBarBase instance at %s>" % (self.this,)
class wxToolBarBase(wxToolBarBasePtr):
    def __init__(self,this):
        self.this = this




class wxToolBarPtr(wxToolBarBasePtr):
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def Create(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBar_Create,(self,) + _args, _kwargs)
        return val
    def FindToolForPosition(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBar_FindToolForPosition,(self,) + _args, _kwargs)
        return val
    def __repr__(self):
        return "<C wxToolBar instance at %s>" % (self.this,)
class wxToolBar(wxToolBarPtr):
    def __init__(self,*_args,**_kwargs):
        self.this = apply(stattoolc.new_wxToolBar,_args,_kwargs)
        self.thisown = 1
        self._setOORInfo(self)



def wxPreToolBar(*_args,**_kwargs):
    val = wxToolBarPtr(apply(stattoolc.new_wxPreToolBar,_args,_kwargs))
    val.thisown = 1
    val._setOORInfo(val)
    return val


class wxToolBarSimplePtr(wxToolBarBasePtr):
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def Create(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarSimple_Create,(self,) + _args, _kwargs)
        return val
    def FindToolForPosition(self, *_args, **_kwargs):
        val = apply(stattoolc.wxToolBarSimple_FindToolForPosition,(self,) + _args, _kwargs)
        return val
    def __repr__(self):
        return "<C wxToolBarSimple instance at %s>" % (self.this,)
class wxToolBarSimple(wxToolBarSimplePtr):
    def __init__(self,*_args,**_kwargs):
        self.this = apply(stattoolc.new_wxToolBarSimple,_args,_kwargs)
        self.thisown = 1
        self._setOORInfo(self)



def wxPreToolBarSimple(*_args,**_kwargs):
    val = wxToolBarSimplePtr(apply(stattoolc.new_wxPreToolBarSimple,_args,_kwargs))
    val.thisown = 1
    val._setOORInfo(val)
    return val




#-------------- FUNCTION WRAPPERS ------------------



#-------------- VARIABLE WRAPPERS ------------------

wxTOOL_STYLE_BUTTON = stattoolc.wxTOOL_STYLE_BUTTON
wxTOOL_STYLE_SEPARATOR = stattoolc.wxTOOL_STYLE_SEPARATOR
wxTOOL_STYLE_CONTROL = stattoolc.wxTOOL_STYLE_CONTROL
