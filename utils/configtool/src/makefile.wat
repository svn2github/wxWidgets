# =========================================================================
#     This makefile was generated by
#     Bakefile 0.1.1 (http://bakefile.sourceforge.net)
#     Do not modify, all changes will be overwritten!
# =========================================================================

!include ../../../build/msw/config.wat

# -------------------------------------------------------------------------
# Do not modify the rest of this file!
# -------------------------------------------------------------------------

# Speed up compilation a bit:
!ifdef __LOADDLL__
!  loaddll wcc      wccd
!  loaddll wccaxp   wccdaxp
!  loaddll wcc386   wccd386
!  loaddll wpp      wppdi86
!  loaddll wppaxp   wppdaxp
!  loaddll wpp386   wppd386
!  loaddll wlink    wlink
!  loaddll wlib     wlibd
!endif

# We need these variables in some bakefile-made rules:
WATCOM_CWD = $+ $(%cdrive):$(%cwd) $-

### Conditionally set variables: ###

LIBDIRNAME =
!ifeq SHARED 0
LIBDIRNAME = .\..\..\..\lib\wat_lib$(CFG)
!endif
!ifeq SHARED 1
LIBDIRNAME = .\..\..\..\lib\wat_dll$(CFG)
!endif
PORTNAME =
!ifeq USE_GUI 0
PORTNAME = base
!endif
!ifeq USE_GUI 1
PORTNAME = msw
!endif
WXDEBUGFLAG =
!ifeq BUILD debug
!ifeq DEBUG_FLAG default
WXDEBUGFLAG = d
!endif
!endif
!ifeq DEBUG_FLAG 1
WXDEBUGFLAG = d
!endif
WXDLLFLAG =
!ifeq SHARED 1
WXDLLFLAG = dll
!endif
WXUNICODEFLAG =
!ifeq UNICODE 1
WXUNICODEFLAG = u
!endif
WXUNIVNAME =
!ifeq WXUNIV 1
WXUNIVNAME = univ
!endif
__DEBUGINFO_0 =
!ifeq BUILD debug
!ifeq DEBUG_INFO default
__DEBUGINFO_0 = -d2
!endif
!endif
!ifeq BUILD release
!ifeq DEBUG_INFO default
__DEBUGINFO_0 = -d0
!endif
!endif
!ifeq DEBUG_INFO 0
__DEBUGINFO_0 = -d0
!endif
!ifeq DEBUG_INFO 1
__DEBUGINFO_0 = -d2
!endif
__DEBUGINFO_1 =
!ifeq BUILD debug
!ifeq DEBUG_INFO default
__DEBUGINFO_1 = debug all
!endif
!endif
!ifeq BUILD release
!ifeq DEBUG_INFO default
__DEBUGINFO_1 = 
!endif
!endif
!ifeq DEBUG_INFO 0
__DEBUGINFO_1 = 
!endif
!ifeq DEBUG_INFO 1
__DEBUGINFO_1 = debug all
!endif
__DEBUG_DEFINE_p =
!ifeq BUILD debug
!ifeq DEBUG_FLAG default
__DEBUG_DEFINE_p = -d__WXDEBUG__
!endif
!endif
!ifeq DEBUG_FLAG 1
__DEBUG_DEFINE_p = -d__WXDEBUG__
!endif
__DLLFLAG_p =
!ifeq SHARED 1
__DLLFLAG_p = -dWXUSINGDLL
!endif
__LIB_JPEG_p =
!ifeq USE_GUI 1
__LIB_JPEG_p = wxjpeg$(WXDEBUGFLAG).lib
!endif
__LIB_PNG_p =
!ifeq USE_GUI 1
__LIB_PNG_p = wxpng$(WXDEBUGFLAG).lib
!endif
__LIB_TIFF_p =
!ifeq USE_GUI 1
__LIB_TIFF_p = wxtiff$(WXDEBUGFLAG).lib
!endif
__OPTIMIZEFLAG_2 =
!ifeq BUILD debug
__OPTIMIZEFLAG_2 = -od
!endif
!ifeq BUILD release
__OPTIMIZEFLAG_2 = -ot -ox
!endif
__RUNTIME_LIBS_5 =
!ifeq RUNTIME_LIBS dynamic
__RUNTIME_LIBS_5 = -br
!endif
!ifeq RUNTIME_LIBS static
__RUNTIME_LIBS_5 = 
!endif
__UNICODE_DEFINE_p =
!ifeq UNICODE 1
__UNICODE_DEFINE_p = -dwxUSE_UNICODE=1
!endif
__WXLIB_ADV_p =
!ifeq MONOLITHIC 0
__WXLIB_ADV_p = &
	wx$(PORTNAME)$(WXUNIVNAME)25$(WXUNICODEFLAG)$(WXDEBUGFLAG)_adv.lib
!endif
__WXLIB_BASE_p =
!ifeq MONOLITHIC 0
__WXLIB_BASE_p = wxbase25$(WXUNICODEFLAG)$(WXDEBUGFLAG).lib
!endif
__WXLIB_CORE_p =
!ifeq MONOLITHIC 0
__WXLIB_CORE_p = &
	wx$(PORTNAME)$(WXUNIVNAME)25$(WXUNICODEFLAG)$(WXDEBUGFLAG)_core.lib
!endif
__WXLIB_HTML_p =
!ifeq MONOLITHIC 0
__WXLIB_HTML_p = &
	wx$(PORTNAME)$(WXUNIVNAME)25$(WXUNICODEFLAG)$(WXDEBUGFLAG)_html.lib
!endif
__WXLIB_MONO_p =
!ifeq MONOLITHIC 1
__WXLIB_MONO_p = &
	wx$(PORTNAME)$(WXUNIVNAME)25$(WXUNICODEFLAG)$(WXDEBUGFLAG).lib
!endif
__WXLIB_XML_p =
!ifeq MONOLITHIC 0
__WXLIB_XML_p = wxbase25$(WXUNICODEFLAG)$(WXDEBUGFLAG)_xml.lib
!endif
__WXUNIV_DEFINE_p =
!ifeq WXUNIV 1
__WXUNIV_DEFINE_p = -d__WXUNIVERSAL__
!endif

### Variables: ###

OBJS = &
	wat_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WXDLLFLAG)$(CFG)
SETUPHDIR = &
	$(LIBDIRNAME)\$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)
WXCONFIGTOOL_CXXFLAGS = $(CPPFLAGS) $(__DEBUGINFO_0) $(__OPTIMIZEFLAG_2) -bm &
	$(__RUNTIME_LIBS_5) -d__WXMSW__ $(__WXUNIV_DEFINE_p) $(__DEBUG_DEFINE_p) &
	$(__UNICODE_DEFINE_p) -i=.\..\..\..\include -i=$(SETUPHDIR) -i=. &
	$(__DLLFLAG_p) -i=.\..\..\..\samples $(CXXFLAGS)
WXCONFIGTOOL_OBJECTS =  &
	$(OBJS)\wxconfigtool_wxconfigtool.obj &
	$(OBJS)\wxconfigtool_appsettings.obj &
	$(OBJS)\wxconfigtool_configitem.obj &
	$(OBJS)\wxconfigtool_configitemselector.obj &
	$(OBJS)\wxconfigtool_configtooldoc.obj &
	$(OBJS)\wxconfigtool_configtoolview.obj &
	$(OBJS)\wxconfigtool_configtree.obj &
	$(OBJS)\wxconfigtool_custompropertydialog.obj &
	$(OBJS)\wxconfigtool_htmlparser.obj &
	$(OBJS)\wxconfigtool_mainframe.obj &
	$(OBJS)\wxconfigtool_propeditor.obj &
	$(OBJS)\wxconfigtool_property.obj &
	$(OBJS)\wxconfigtool_settingsdialog.obj &
	$(OBJS)\wxconfigtool_utils.obj


all : $(OBJS)
$(OBJS) :
	-if not exist $(OBJS) mkdir $(OBJS)

### Targets: ###

all : .SYMBOLIC $(OBJS)\wxconfigtool.exe data

$(OBJS)\wxconfigtool_appsettings.obj :  .AUTODEPEND .\appsettings.cpp
	$(CXX) -zq -fo=$^@ $(WXCONFIGTOOL_CXXFLAGS) $<

$(OBJS)\wxconfigtool_configitem.obj :  .AUTODEPEND .\configitem.cpp
	$(CXX) -zq -fo=$^@ $(WXCONFIGTOOL_CXXFLAGS) $<

$(OBJS)\wxconfigtool_configitemselector.obj :  .AUTODEPEND .\configitemselector.cpp
	$(CXX) -zq -fo=$^@ $(WXCONFIGTOOL_CXXFLAGS) $<

$(OBJS)\wxconfigtool_configtooldoc.obj :  .AUTODEPEND .\configtooldoc.cpp
	$(CXX) -zq -fo=$^@ $(WXCONFIGTOOL_CXXFLAGS) $<

$(OBJS)\wxconfigtool_configtoolview.obj :  .AUTODEPEND .\configtoolview.cpp
	$(CXX) -zq -fo=$^@ $(WXCONFIGTOOL_CXXFLAGS) $<

$(OBJS)\wxconfigtool_configtree.obj :  .AUTODEPEND .\configtree.cpp
	$(CXX) -zq -fo=$^@ $(WXCONFIGTOOL_CXXFLAGS) $<

$(OBJS)\wxconfigtool_custompropertydialog.obj :  .AUTODEPEND .\custompropertydialog.cpp
	$(CXX) -zq -fo=$^@ $(WXCONFIGTOOL_CXXFLAGS) $<

$(OBJS)\wxconfigtool_htmlparser.obj :  .AUTODEPEND .\htmlparser.cpp
	$(CXX) -zq -fo=$^@ $(WXCONFIGTOOL_CXXFLAGS) $<

$(OBJS)\wxconfigtool_mainframe.obj :  .AUTODEPEND .\mainframe.cpp
	$(CXX) -zq -fo=$^@ $(WXCONFIGTOOL_CXXFLAGS) $<

$(OBJS)\wxconfigtool_propeditor.obj :  .AUTODEPEND .\propeditor.cpp
	$(CXX) -zq -fo=$^@ $(WXCONFIGTOOL_CXXFLAGS) $<

$(OBJS)\wxconfigtool_property.obj :  .AUTODEPEND .\property.cpp
	$(CXX) -zq -fo=$^@ $(WXCONFIGTOOL_CXXFLAGS) $<

$(OBJS)\wxconfigtool_sample.res :  .AUTODEPEND .\..\..\..\samples\sample.rc
	wrc -q -ad -bt=nt -r -fo=$^@ -d__WXMSW__ $(__WXUNIV_DEFINE_p) $(__DEBUG_DEFINE_p) $(__UNICODE_DEFINE_p) -i=.\..\..\..\include -i=$(SETUPHDIR) -i=. $(__DLLFLAG_p) -i=.\..\..\..\samples $<

$(OBJS)\wxconfigtool_settingsdialog.obj :  .AUTODEPEND .\settingsdialog.cpp
	$(CXX) -zq -fo=$^@ $(WXCONFIGTOOL_CXXFLAGS) $<

$(OBJS)\wxconfigtool_utils.obj :  .AUTODEPEND .\utils.cpp
	$(CXX) -zq -fo=$^@ $(WXCONFIGTOOL_CXXFLAGS) $<

$(OBJS)\wxconfigtool_wxconfigtool.obj :  .AUTODEPEND .\wxconfigtool.cpp
	$(CXX) -zq -fo=$^@ $(WXCONFIGTOOL_CXXFLAGS) $<

clean : .SYMBOLIC 
	-if exist $(OBJS)\*.obj del $(OBJS)\*.obj
	-if exist $(OBJS)\*.res del $(OBJS)\*.res
	-if exist $(OBJS)\*.lbc del $(OBJS)\*.lbc
	-if exist $(OBJS)\*.ilk del $(OBJS)\*.ilk
	-if exist $(OBJS)\wxconfigtool.exe del $(OBJS)\wxconfigtool.exe

data : .SYMBOLIC 
	if not exist $(OBJS) mkdir $(OBJS)
	for %f in (wxconfigtool.pjd ../configs/wxwin250.wxs) do if not exist $(OBJS)\%f copy .\%f $(OBJS)

$(OBJS)\wxconfigtool.exe :  $(WXCONFIGTOOL_OBJECTS) $(OBJS)\wxconfigtool_sample.res
	@%create $(OBJS)\wxconfigtool.lbc
	@%append $(OBJS)\wxconfigtool.lbc option quiet
	@%append $(OBJS)\wxconfigtool.lbc name $^@
	@%append $(OBJS)\wxconfigtool.lbc option caseexact
	@%append $(OBJS)\wxconfigtool.lbc $(LDFLAGS) $(__DEBUGINFO_1)  libpath $(LIBDIRNAME) system nt_win ref '_WinMain@16'
	@for %i in ($(WXCONFIGTOOL_OBJECTS)) do @%append $(OBJS)\wxconfigtool.lbc file %i
	@for %i in ( $(__WXLIB_ADV_p) $(__WXLIB_HTML_p) $(__WXLIB_CORE_p) $(__WXLIB_XML_p) $(__WXLIB_BASE_p) $(__WXLIB_MONO_p) $(__LIB_TIFF_p) $(__LIB_JPEG_p) $(__LIB_PNG_p) wxzlib$(WXDEBUGFLAG).lib  wxregex$(WXDEBUGFLAG).lib wxexpat$(WXDEBUGFLAG).lib   kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib odbc32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib ) do @%append $(OBJS)\wxconfigtool.lbc library %i
	@%append $(OBJS)\wxconfigtool.lbc option resource=$(OBJS)\wxconfigtool_sample.res
	wlink @$(OBJS)\wxconfigtool.lbc
