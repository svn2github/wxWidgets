# Microsoft Developer Studio Project File - Name="mmedia" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=mmedia - Win32 DLL Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mmedia.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mmedia.mak" CFG="mmedia - Win32 DLL Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mmedia - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "mmedia - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "mmedia - Win32 Unicode Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "mmedia - Win32 Unicode Release" (based on "Win32 (x86) Static Library")
!MESSAGE "mmedia - Win32 Universal Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "mmedia - Win32 Universal Release" (based on "Win32 (x86) Static Library")
!MESSAGE "mmedia - Win32 Universal Unicode Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "mmedia - Win32 Universal Unicode Release" (based on "Win32 (x86) Static Library")
!MESSAGE "mmedia - Win32 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "mmedia - Win32 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "mmedia - Win32 DLL Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "mmedia - Win32 DLL Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "mmedia - Win32 DLL Universal Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "mmedia - Win32 DLL Universal Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "mmedia - Win32 DLL Universal Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "mmedia - Win32 DLL Universal Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mmedia - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswd\mmedia"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswd\mmedia"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /W4 /GR /GX /MDd /Od /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_lib\mswd" /Zi /Gm /GZ /Fd..\..\src\mmedia\..\..\..\lib\vc_lib\wxmsw25d_mmedia.pdb /Yu"wx/wxprec.h" /Fp"vc_mswd\wxprec_mmedialib.pch" /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /c
# ADD CPP /nologo /FD /W4 /GR /GX /MDd /Od /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_lib\mswd" /Zi /Gm /GZ /Fd..\..\src\mmedia\..\..\..\lib\vc_lib\wxmsw25d_mmedia.pdb /Yu"wx/wxprec.h" /Fp"vc_mswd\wxprec_mmedialib.pch" /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /c
# ADD BASE RSC /l 0x405
# ADD RSC /l 0x405
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\src\mmedia\..\..\..\lib\vc_lib\wxmsw25d_mmedia.lib"
# ADD LIB32 /nologo /out:"..\..\src\mmedia\..\..\..\lib\vc_lib\wxmsw25d_mmedia.lib"

!ELSEIF  "$(CFG)" == "mmedia - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_msw\mmedia"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_msw\mmedia"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /W4 /GR /GX /MD /O1 /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_lib\msw" /Fd..\..\src\mmedia\..\..\..\lib\vc_lib\wxmsw25_mmedia.pdb /Yu"wx/wxprec.h" /Fp"vc_msw\wxprec_mmedialib.pch" /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_LIB" /D "__WXMSW__" /c
# ADD CPP /nologo /FD /W4 /GR /GX /MD /O1 /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_lib\msw" /Fd..\..\src\mmedia\..\..\..\lib\vc_lib\wxmsw25_mmedia.pdb /Yu"wx/wxprec.h" /Fp"vc_msw\wxprec_mmedialib.pch" /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_LIB" /D "__WXMSW__" /c
# ADD BASE RSC /l 0x405
# ADD RSC /l 0x405
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\src\mmedia\..\..\..\lib\vc_lib\wxmsw25_mmedia.lib"
# ADD LIB32 /nologo /out:"..\..\src\mmedia\..\..\..\lib\vc_lib\wxmsw25_mmedia.lib"

!ELSEIF  "$(CFG)" == "mmedia - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswud\mmedia"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswud\mmedia"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /W4 /GR /GX /MDd /Od /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_lib\mswud" /Zi /Gm /GZ /Fd..\..\src\mmedia\..\..\..\lib\vc_lib\wxmsw25ud_mmedia.pdb /Yu"wx/wxprec.h" /Fp"vc_mswud\wxprec_mmedialib.pch" /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D wxUSE_UNICODE=1 /c
# ADD CPP /nologo /FD /W4 /GR /GX /MDd /Od /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_lib\mswud" /Zi /Gm /GZ /Fd..\..\src\mmedia\..\..\..\lib\vc_lib\wxmsw25ud_mmedia.pdb /Yu"wx/wxprec.h" /Fp"vc_mswud\wxprec_mmedialib.pch" /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D wxUSE_UNICODE=1 /c
# ADD BASE RSC /l 0x405
# ADD RSC /l 0x405
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\src\mmedia\..\..\..\lib\vc_lib\wxmsw25ud_mmedia.lib"
# ADD LIB32 /nologo /out:"..\..\src\mmedia\..\..\..\lib\vc_lib\wxmsw25ud_mmedia.lib"

!ELSEIF  "$(CFG)" == "mmedia - Win32 Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswu\mmedia"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswu\mmedia"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /W4 /GR /GX /MD /O1 /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_lib\mswu" /Fd..\..\src\mmedia\..\..\..\lib\vc_lib\wxmsw25u_mmedia.pdb /Yu"wx/wxprec.h" /Fp"vc_mswu\wxprec_mmedialib.pch" /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D wxUSE_UNICODE=1 /c
# ADD CPP /nologo /FD /W4 /GR /GX /MD /O1 /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_lib\mswu" /Fd..\..\src\mmedia\..\..\..\lib\vc_lib\wxmsw25u_mmedia.pdb /Yu"wx/wxprec.h" /Fp"vc_mswu\wxprec_mmedialib.pch" /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D wxUSE_UNICODE=1 /c
# ADD BASE RSC /l 0x405
# ADD RSC /l 0x405
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\src\mmedia\..\..\..\lib\vc_lib\wxmsw25u_mmedia.lib"
# ADD LIB32 /nologo /out:"..\..\src\mmedia\..\..\..\lib\vc_lib\wxmsw25u_mmedia.lib"

!ELSEIF  "$(CFG)" == "mmedia - Win32 Universal Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswunivd\mmedia"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswunivd\mmedia"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /W4 /GR /GX /MDd /Od /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_lib\mswunivd" /Zi /Gm /GZ /Fd..\..\src\mmedia\..\..\..\lib\vc_lib\wxmswuniv25d_mmedia.pdb /Yu"wx/wxprec.h" /Fp"vc_mswunivd\wxprec_mmedialib.pch" /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /c
# ADD CPP /nologo /FD /W4 /GR /GX /MDd /Od /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_lib\mswunivd" /Zi /Gm /GZ /Fd..\..\src\mmedia\..\..\..\lib\vc_lib\wxmswuniv25d_mmedia.pdb /Yu"wx/wxprec.h" /Fp"vc_mswunivd\wxprec_mmedialib.pch" /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /c
# ADD BASE RSC /l 0x405
# ADD RSC /l 0x405
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\src\mmedia\..\..\..\lib\vc_lib\wxmswuniv25d_mmedia.lib"
# ADD LIB32 /nologo /out:"..\..\src\mmedia\..\..\..\lib\vc_lib\wxmswuniv25d_mmedia.lib"

!ELSEIF  "$(CFG)" == "mmedia - Win32 Universal Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswuniv\mmedia"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswuniv\mmedia"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /W4 /GR /GX /MD /O1 /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_lib\mswuniv" /Fd..\..\src\mmedia\..\..\..\lib\vc_lib\wxmswuniv25_mmedia.pdb /Yu"wx/wxprec.h" /Fp"vc_mswuniv\wxprec_mmedialib.pch" /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "__WXUNIVERSAL__" /c
# ADD CPP /nologo /FD /W4 /GR /GX /MD /O1 /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_lib\mswuniv" /Fd..\..\src\mmedia\..\..\..\lib\vc_lib\wxmswuniv25_mmedia.pdb /Yu"wx/wxprec.h" /Fp"vc_mswuniv\wxprec_mmedialib.pch" /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "__WXUNIVERSAL__" /c
# ADD BASE RSC /l 0x405
# ADD RSC /l 0x405
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\src\mmedia\..\..\..\lib\vc_lib\wxmswuniv25_mmedia.lib"
# ADD LIB32 /nologo /out:"..\..\src\mmedia\..\..\..\lib\vc_lib\wxmswuniv25_mmedia.lib"

!ELSEIF  "$(CFG)" == "mmedia - Win32 Universal Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswunivud\mmedia"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswunivud\mmedia"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /W4 /GR /GX /MDd /Od /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_lib\mswunivud" /Zi /Gm /GZ /Fd..\..\src\mmedia\..\..\..\lib\vc_lib\wxmswuniv25ud_mmedia.pdb /Yu"wx/wxprec.h" /Fp"vc_mswunivud\wxprec_mmedialib.pch" /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D wxUSE_UNICODE=1 /c
# ADD CPP /nologo /FD /W4 /GR /GX /MDd /Od /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_lib\mswunivud" /Zi /Gm /GZ /Fd..\..\src\mmedia\..\..\..\lib\vc_lib\wxmswuniv25ud_mmedia.pdb /Yu"wx/wxprec.h" /Fp"vc_mswunivud\wxprec_mmedialib.pch" /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D wxUSE_UNICODE=1 /c
# ADD BASE RSC /l 0x405
# ADD RSC /l 0x405
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\src\mmedia\..\..\..\lib\vc_lib\wxmswuniv25ud_mmedia.lib"
# ADD LIB32 /nologo /out:"..\..\src\mmedia\..\..\..\lib\vc_lib\wxmswuniv25ud_mmedia.lib"

!ELSEIF  "$(CFG)" == "mmedia - Win32 Universal Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswunivu\mmedia"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswunivu\mmedia"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /W4 /GR /GX /MD /O1 /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_lib\mswunivu" /Fd..\..\src\mmedia\..\..\..\lib\vc_lib\wxmswuniv25u_mmedia.pdb /Yu"wx/wxprec.h" /Fp"vc_mswunivu\wxprec_mmedialib.pch" /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D wxUSE_UNICODE=1 /c
# ADD CPP /nologo /FD /W4 /GR /GX /MD /O1 /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_lib\mswunivu" /Fd..\..\src\mmedia\..\..\..\lib\vc_lib\wxmswuniv25u_mmedia.pdb /Yu"wx/wxprec.h" /Fp"vc_mswunivu\wxprec_mmedialib.pch" /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D wxUSE_UNICODE=1 /c
# ADD BASE RSC /l 0x405
# ADD RSC /l 0x405
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\src\mmedia\..\..\..\lib\vc_lib\wxmswuniv25u_mmedia.lib"
# ADD LIB32 /nologo /out:"..\..\src\mmedia\..\..\..\lib\vc_lib\wxmswuniv25u_mmedia.lib"

!ELSEIF  "$(CFG)" == "mmedia - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswddll\mmedia"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswddll\mmedia"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /W4 /GR /GX /MDd /Od /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_dll\mswd" /Yu"wx/wxprec.h" /Fp"vc_mswddll\wxprec_mmediadll.pch" /Zi /Gm /GZ /Fd..\..\src\mmedia\..\..\..\lib\vc_dll\wxmsw250d_mmedia_vc_custom.pdb /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /c
# ADD CPP /nologo /FD /W4 /GR /GX /MDd /Od /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_dll\mswd" /Yu"wx/wxprec.h" /Fp"vc_mswddll\wxprec_mmediadll.pch" /Zi /Gm /GZ /Fd..\..\src\mmedia\..\..\..\lib\vc_dll\wxmsw250d_mmedia_vc_custom.pdb /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /mktyplib203 /win32
# ADD BASE RSC /l 0x405 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /i "..\..\src\mmedia\..\..\..\include" /i "..\..\src\mmedia\..\..\..\lib\vc_dll\mswd" /i "..\..\src\mmedia\..\..\include" /d "WXUSINGDLL" /d WXMAKINGDLL_MMEDIA
# ADD RSC /l 0x405 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /i "..\..\src\mmedia\..\..\..\include" /i "..\..\src\mmedia\..\..\..\lib\vc_dll\mswd" /i "..\..\src\mmedia\..\..\include" /d "WXUSINGDLL" /d WXMAKINGDLL_MMEDIA
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib odbc32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib wxmsw25d_core.lib wxbase25d.lib /nologo /dll /machine:i386 /out:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmsw250d_mmedia_vc_custom.dll" /libpath:"..\..\src\mmedia\..\..\..\lib\vc_dll" /implib:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmsw25d_mmedia.lib" /debug
# ADD LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib odbc32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib wxmsw25d_core.lib wxbase25d.lib /nologo /dll /machine:i386 /out:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmsw250d_mmedia_vc_custom.dll" /libpath:"..\..\src\mmedia\..\..\..\lib\vc_dll" /implib:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmsw25d_mmedia.lib" /debug

!ELSEIF  "$(CFG)" == "mmedia - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswdll\mmedia"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswdll\mmedia"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /W4 /GR /GX /MD /O1 /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_dll\msw" /Yu"wx/wxprec.h" /Fp"vc_mswdll\wxprec_mmediadll.pch" /Fd..\..\src\mmedia\..\..\..\lib\vc_dll\wxmsw250_mmedia_vc_custom.pdb /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /c
# ADD CPP /nologo /FD /W4 /GR /GX /MD /O1 /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_dll\msw" /Yu"wx/wxprec.h" /Fp"vc_mswdll\wxprec_mmediadll.pch" /Fd..\..\src\mmedia\..\..\..\lib\vc_dll\wxmsw250_mmedia_vc_custom.pdb /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /mktyplib203 /win32
# ADD BASE RSC /l 0x405 /d "__WXMSW__" /i "..\..\src\mmedia\..\..\..\include" /i "..\..\src\mmedia\..\..\..\lib\vc_dll\msw" /i "..\..\src\mmedia\..\..\include" /d "WXUSINGDLL" /d WXMAKINGDLL_MMEDIA
# ADD RSC /l 0x405 /d "__WXMSW__" /i "..\..\src\mmedia\..\..\..\include" /i "..\..\src\mmedia\..\..\..\lib\vc_dll\msw" /i "..\..\src\mmedia\..\..\include" /d "WXUSINGDLL" /d WXMAKINGDLL_MMEDIA
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib odbc32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib wxmsw25_core.lib wxbase25.lib /nologo /dll /machine:i386 /out:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmsw250_mmedia_vc_custom.dll" /libpath:"..\..\src\mmedia\..\..\..\lib\vc_dll" /implib:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmsw25_mmedia.lib"
# ADD LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib odbc32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib wxmsw25_core.lib wxbase25.lib /nologo /dll /machine:i386 /out:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmsw250_mmedia_vc_custom.dll" /libpath:"..\..\src\mmedia\..\..\..\lib\vc_dll" /implib:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmsw25_mmedia.lib"

!ELSEIF  "$(CFG)" == "mmedia - Win32 DLL Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswuddll\mmedia"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswuddll\mmedia"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /W4 /GR /GX /MDd /Od /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_dll\mswud" /Yu"wx/wxprec.h" /Fp"vc_mswuddll\wxprec_mmediadll.pch" /Zi /Gm /GZ /Fd..\..\src\mmedia\..\..\..\lib\vc_dll\wxmsw250ud_mmedia_vc_custom.pdb /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D wxUSE_UNICODE=1 /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /c
# ADD CPP /nologo /FD /W4 /GR /GX /MDd /Od /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_dll\mswud" /Yu"wx/wxprec.h" /Fp"vc_mswuddll\wxprec_mmediadll.pch" /Zi /Gm /GZ /Fd..\..\src\mmedia\..\..\..\lib\vc_dll\wxmsw250ud_mmedia_vc_custom.pdb /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D wxUSE_UNICODE=1 /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D wxUSE_UNICODE=1 /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D wxUSE_UNICODE=1 /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /mktyplib203 /win32
# ADD BASE RSC /l 0x405 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /d wxUSE_UNICODE=1 /i "..\..\src\mmedia\..\..\..\include" /i "..\..\src\mmedia\..\..\..\lib\vc_dll\mswud" /i "..\..\src\mmedia\..\..\include" /d "WXUSINGDLL" /d WXMAKINGDLL_MMEDIA
# ADD RSC /l 0x405 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /d wxUSE_UNICODE=1 /i "..\..\src\mmedia\..\..\..\include" /i "..\..\src\mmedia\..\..\..\lib\vc_dll\mswud" /i "..\..\src\mmedia\..\..\include" /d "WXUSINGDLL" /d WXMAKINGDLL_MMEDIA
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib odbc32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib wxmsw25ud_core.lib wxbase25ud.lib /nologo /dll /machine:i386 /out:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmsw250ud_mmedia_vc_custom.dll" /libpath:"..\..\src\mmedia\..\..\..\lib\vc_dll" /implib:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmsw25ud_mmedia.lib" /debug
# ADD LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib odbc32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib wxmsw25ud_core.lib wxbase25ud.lib /nologo /dll /machine:i386 /out:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmsw250ud_mmedia_vc_custom.dll" /libpath:"..\..\src\mmedia\..\..\..\lib\vc_dll" /implib:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmsw25ud_mmedia.lib" /debug

!ELSEIF  "$(CFG)" == "mmedia - Win32 DLL Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswudll\mmedia"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswudll\mmedia"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /W4 /GR /GX /MD /O1 /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_dll\mswu" /Yu"wx/wxprec.h" /Fp"vc_mswudll\wxprec_mmediadll.pch" /Fd..\..\src\mmedia\..\..\..\lib\vc_dll\wxmsw250u_mmedia_vc_custom.pdb /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D wxUSE_UNICODE=1 /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /c
# ADD CPP /nologo /FD /W4 /GR /GX /MD /O1 /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_dll\mswu" /Yu"wx/wxprec.h" /Fp"vc_mswudll\wxprec_mmediadll.pch" /Fd..\..\src\mmedia\..\..\..\lib\vc_dll\wxmsw250u_mmedia_vc_custom.pdb /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D wxUSE_UNICODE=1 /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D wxUSE_UNICODE=1 /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D wxUSE_UNICODE=1 /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /mktyplib203 /win32
# ADD BASE RSC /l 0x405 /d "__WXMSW__" /d wxUSE_UNICODE=1 /i "..\..\src\mmedia\..\..\..\include" /i "..\..\src\mmedia\..\..\..\lib\vc_dll\mswu" /i "..\..\src\mmedia\..\..\include" /d "WXUSINGDLL" /d WXMAKINGDLL_MMEDIA
# ADD RSC /l 0x405 /d "__WXMSW__" /d wxUSE_UNICODE=1 /i "..\..\src\mmedia\..\..\..\include" /i "..\..\src\mmedia\..\..\..\lib\vc_dll\mswu" /i "..\..\src\mmedia\..\..\include" /d "WXUSINGDLL" /d WXMAKINGDLL_MMEDIA
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib odbc32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib wxmsw25u_core.lib wxbase25u.lib /nologo /dll /machine:i386 /out:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmsw250u_mmedia_vc_custom.dll" /libpath:"..\..\src\mmedia\..\..\..\lib\vc_dll" /implib:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmsw25u_mmedia.lib"
# ADD LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib odbc32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib wxmsw25u_core.lib wxbase25u.lib /nologo /dll /machine:i386 /out:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmsw250u_mmedia_vc_custom.dll" /libpath:"..\..\src\mmedia\..\..\..\lib\vc_dll" /implib:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmsw25u_mmedia.lib"

!ELSEIF  "$(CFG)" == "mmedia - Win32 DLL Universal Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswunivddll\mmedia"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswunivddll\mmedia"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /W4 /GR /GX /MDd /Od /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_dll\mswunivd" /Yu"wx/wxprec.h" /Fp"vc_mswunivddll\wxprec_mmediadll.pch" /Zi /Gm /GZ /Fd..\..\src\mmedia\..\..\..\lib\vc_dll\wxmswuniv250d_mmedia_vc_custom.pdb /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /c
# ADD CPP /nologo /FD /W4 /GR /GX /MDd /Od /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_dll\mswunivd" /Yu"wx/wxprec.h" /Fp"vc_mswunivddll\wxprec_mmediadll.pch" /Zi /Gm /GZ /Fd..\..\src\mmedia\..\..\..\lib\vc_dll\wxmswuniv250d_mmedia_vc_custom.pdb /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /mktyplib203 /win32
# ADD BASE RSC /l 0x405 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /i "..\..\src\mmedia\..\..\..\include" /i "..\..\src\mmedia\..\..\..\lib\vc_dll\mswunivd" /i "..\..\src\mmedia\..\..\include" /d "WXUSINGDLL" /d WXMAKINGDLL_MMEDIA
# ADD RSC /l 0x405 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /i "..\..\src\mmedia\..\..\..\include" /i "..\..\src\mmedia\..\..\..\lib\vc_dll\mswunivd" /i "..\..\src\mmedia\..\..\include" /d "WXUSINGDLL" /d WXMAKINGDLL_MMEDIA
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib odbc32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib wxmswuniv25d_core.lib wxbase25d.lib /nologo /dll /machine:i386 /out:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmswuniv250d_mmedia_vc_custom.dll" /libpath:"..\..\src\mmedia\..\..\..\lib\vc_dll" /implib:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmswuniv25d_mmedia.lib" /debug
# ADD LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib odbc32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib wxmswuniv25d_core.lib wxbase25d.lib /nologo /dll /machine:i386 /out:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmswuniv250d_mmedia_vc_custom.dll" /libpath:"..\..\src\mmedia\..\..\..\lib\vc_dll" /implib:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmswuniv25d_mmedia.lib" /debug

!ELSEIF  "$(CFG)" == "mmedia - Win32 DLL Universal Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswunivdll\mmedia"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswunivdll\mmedia"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /W4 /GR /GX /MD /O1 /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_dll\mswuniv" /Yu"wx/wxprec.h" /Fp"vc_mswunivdll\wxprec_mmediadll.pch" /Fd..\..\src\mmedia\..\..\..\lib\vc_dll\wxmswuniv250_mmedia_vc_custom.pdb /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /c
# ADD CPP /nologo /FD /W4 /GR /GX /MD /O1 /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_dll\mswuniv" /Yu"wx/wxprec.h" /Fp"vc_mswunivdll\wxprec_mmediadll.pch" /Fd..\..\src\mmedia\..\..\..\lib\vc_dll\wxmswuniv250_mmedia_vc_custom.pdb /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /mktyplib203 /win32
# ADD BASE RSC /l 0x405 /d "__WXMSW__" /d "__WXUNIVERSAL__" /i "..\..\src\mmedia\..\..\..\include" /i "..\..\src\mmedia\..\..\..\lib\vc_dll\mswuniv" /i "..\..\src\mmedia\..\..\include" /d "WXUSINGDLL" /d WXMAKINGDLL_MMEDIA
# ADD RSC /l 0x405 /d "__WXMSW__" /d "__WXUNIVERSAL__" /i "..\..\src\mmedia\..\..\..\include" /i "..\..\src\mmedia\..\..\..\lib\vc_dll\mswuniv" /i "..\..\src\mmedia\..\..\include" /d "WXUSINGDLL" /d WXMAKINGDLL_MMEDIA
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib odbc32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib wxmswuniv25_core.lib wxbase25.lib /nologo /dll /machine:i386 /out:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmswuniv250_mmedia_vc_custom.dll" /libpath:"..\..\src\mmedia\..\..\..\lib\vc_dll" /implib:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmswuniv25_mmedia.lib"
# ADD LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib odbc32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib wxmswuniv25_core.lib wxbase25.lib /nologo /dll /machine:i386 /out:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmswuniv250_mmedia_vc_custom.dll" /libpath:"..\..\src\mmedia\..\..\..\lib\vc_dll" /implib:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmswuniv25_mmedia.lib"

!ELSEIF  "$(CFG)" == "mmedia - Win32 DLL Universal Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswunivuddll\mmedia"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswunivuddll\mmedia"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /W4 /GR /GX /MDd /Od /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_dll\mswunivud" /Yu"wx/wxprec.h" /Fp"vc_mswunivuddll\wxprec_mmediadll.pch" /Zi /Gm /GZ /Fd..\..\src\mmedia\..\..\..\lib\vc_dll\wxmswuniv250ud_mmedia_vc_custom.pdb /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D wxUSE_UNICODE=1 /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /c
# ADD CPP /nologo /FD /W4 /GR /GX /MDd /Od /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_dll\mswunivud" /Yu"wx/wxprec.h" /Fp"vc_mswunivuddll\wxprec_mmediadll.pch" /Zi /Gm /GZ /Fd..\..\src\mmedia\..\..\..\lib\vc_dll\wxmswuniv250ud_mmedia_vc_custom.pdb /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D wxUSE_UNICODE=1 /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D wxUSE_UNICODE=1 /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D wxUSE_UNICODE=1 /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /mktyplib203 /win32
# ADD BASE RSC /l 0x405 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /d wxUSE_UNICODE=1 /i "..\..\src\mmedia\..\..\..\include" /i "..\..\src\mmedia\..\..\..\lib\vc_dll\mswunivud" /i "..\..\src\mmedia\..\..\include" /d "WXUSINGDLL" /d WXMAKINGDLL_MMEDIA
# ADD RSC /l 0x405 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /d wxUSE_UNICODE=1 /i "..\..\src\mmedia\..\..\..\include" /i "..\..\src\mmedia\..\..\..\lib\vc_dll\mswunivud" /i "..\..\src\mmedia\..\..\include" /d "WXUSINGDLL" /d WXMAKINGDLL_MMEDIA
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib odbc32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib wxmswuniv25ud_core.lib wxbase25ud.lib /nologo /dll /machine:i386 /out:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmswuniv250ud_mmedia_vc_custom.dll" /libpath:"..\..\src\mmedia\..\..\..\lib\vc_dll" /implib:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmswuniv25ud_mmedia.lib" /debug
# ADD LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib odbc32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib wxmswuniv25ud_core.lib wxbase25ud.lib /nologo /dll /machine:i386 /out:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmswuniv250ud_mmedia_vc_custom.dll" /libpath:"..\..\src\mmedia\..\..\..\lib\vc_dll" /implib:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmswuniv25ud_mmedia.lib" /debug

!ELSEIF  "$(CFG)" == "mmedia - Win32 DLL Universal Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswunivudll\mmedia"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\src\mmedia\..\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswunivudll\mmedia"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /W4 /GR /GX /MD /O1 /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_dll\mswunivu" /Yu"wx/wxprec.h" /Fp"vc_mswunivudll\wxprec_mmediadll.pch" /Fd..\..\src\mmedia\..\..\..\lib\vc_dll\wxmswuniv250u_mmedia_vc_custom.pdb /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D wxUSE_UNICODE=1 /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /c
# ADD CPP /nologo /FD /W4 /GR /GX /MD /O1 /I "..\..\src\mmedia\..\..\..\include" /I "..\..\src\mmedia\..\..\..\lib\vc_dll\mswunivu" /Yu"wx/wxprec.h" /Fp"vc_mswunivudll\wxprec_mmediadll.pch" /Fd..\..\src\mmedia\..\..\..\lib\vc_dll\wxmswuniv250u_mmedia_vc_custom.pdb /I "..\..\src\mmedia\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D wxUSE_UNICODE=1 /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D wxUSE_UNICODE=1 /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D wxUSE_UNICODE=1 /D "WXUSINGDLL" /D "WXMAKINGDLL_MMEDIA" /mktyplib203 /win32
# ADD BASE RSC /l 0x405 /d "__WXMSW__" /d "__WXUNIVERSAL__" /d wxUSE_UNICODE=1 /i "..\..\src\mmedia\..\..\..\include" /i "..\..\src\mmedia\..\..\..\lib\vc_dll\mswunivu" /i "..\..\src\mmedia\..\..\include" /d "WXUSINGDLL" /d WXMAKINGDLL_MMEDIA
# ADD RSC /l 0x405 /d "__WXMSW__" /d "__WXUNIVERSAL__" /d wxUSE_UNICODE=1 /i "..\..\src\mmedia\..\..\..\include" /i "..\..\src\mmedia\..\..\..\lib\vc_dll\mswunivu" /i "..\..\src\mmedia\..\..\include" /d "WXUSINGDLL" /d WXMAKINGDLL_MMEDIA
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib odbc32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib wxmswuniv25u_core.lib wxbase25u.lib /nologo /dll /machine:i386 /out:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmswuniv250u_mmedia_vc_custom.dll" /libpath:"..\..\src\mmedia\..\..\..\lib\vc_dll" /implib:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmswuniv25u_mmedia.lib"
# ADD LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib odbc32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib wxmswuniv25u_core.lib wxbase25u.lib /nologo /dll /machine:i386 /out:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmswuniv250u_mmedia_vc_custom.dll" /libpath:"..\..\src\mmedia\..\..\..\lib\vc_dll" /implib:"..\..\src\mmedia\..\..\..\lib\vc_dll\wxmswuniv25u_mmedia.lib"

!ENDIF

# Begin Target

# Name "mmedia - Win32 Debug"
# Name "mmedia - Win32 Release"
# Name "mmedia - Win32 Unicode Debug"
# Name "mmedia - Win32 Unicode Release"
# Name "mmedia - Win32 Universal Debug"
# Name "mmedia - Win32 Universal Release"
# Name "mmedia - Win32 Universal Unicode Debug"
# Name "mmedia - Win32 Universal Unicode Release"
# Name "mmedia - Win32 DLL Debug"
# Name "mmedia - Win32 DLL Release"
# Name "mmedia - Win32 DLL Unicode Debug"
# Name "mmedia - Win32 DLL Unicode Release"
# Name "mmedia - Win32 DLL Universal Debug"
# Name "mmedia - Win32 DLL Universal Release"
# Name "mmedia - Win32 DLL Universal Unicode Debug"
# Name "mmedia - Win32 DLL Universal Unicode Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=../../src/mmedia\cdbase.cpp
# End Source File
# Begin Source File

SOURCE=../../src/mmedia\cdwin.cpp
# End Source File
# Begin Source File

SOURCE=../../src/mmedia\..\..\..\src\msw\dummy.cpp
# ADD BASE CPP /Yc"wx/wxprec.h"
# ADD CPP /Yc"wx/wxprec.h"
# End Source File
# Begin Source File

SOURCE=../../src/mmedia\g711.cpp
# End Source File
# Begin Source File

SOURCE=../../src/mmedia\g721.cpp
# End Source File
# Begin Source File

SOURCE=../../src/mmedia\g723_24.cpp
# End Source File
# Begin Source File

SOURCE=../../src/mmedia\g723_40.cpp
# End Source File
# Begin Source File

SOURCE=../../src/mmedia\g72x.cpp
# End Source File
# Begin Source File

SOURCE=../../src/mmedia\sndaiff.cpp
# End Source File
# Begin Source File

SOURCE=../../src/mmedia\sndbase.cpp
# End Source File
# Begin Source File

SOURCE=../../src/mmedia\sndcodec.cpp
# End Source File
# Begin Source File

SOURCE=../../src/mmedia\sndcpcm.cpp
# End Source File
# Begin Source File

SOURCE=../../src/mmedia\sndfile.cpp
# End Source File
# Begin Source File

SOURCE=../../src/mmedia\sndg72x.cpp
# End Source File
# Begin Source File

SOURCE=../../src/mmedia\sndmsad.cpp
# End Source File
# Begin Source File

SOURCE=../../src/mmedia\sndpcm.cpp
# End Source File
# Begin Source File

SOURCE=../../src/mmedia\sndulaw.cpp
# End Source File
# Begin Source File

SOURCE=../../src/mmedia\sndwav.cpp
# End Source File
# Begin Source File

SOURCE=../../src/mmedia\sndwin.cpp
# End Source File
# Begin Source File

SOURCE=../../src/mmedia\vidbase.cpp
# End Source File
# Begin Source File

SOURCE=../../src/mmedia\vidwin.cpp
# End Source File
# End Group
# End Target
# End Project

