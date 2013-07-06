# =========================================================================
#     This makefile was generated by
#     Bakefile 0.2.9 (http://www.bakefile.org)
#     Do not modify, all changes will be overwritten!
# =========================================================================

!include ../../build/msw/config.wat

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
! if $(__VERSION__) >= 1280
!  loaddll wlink    wlinkd
! else
!  loaddll wlink    wlink
! endif
!  loaddll wlib     wlibd
!endif

# We need these variables in some bakefile-made rules:
WATCOM_CWD = $+ $(%cdrive):$(%cwd) $-

### Conditionally set variables: ###

PORTNAME =
!ifeq USE_GUI 0
PORTNAME = base
!endif
!ifeq USE_GUI 1
PORTNAME = msw$(TOOLKIT_VERSION)
!endif
COMPILER_VERSION =
!ifeq OFFICIAL_BUILD 1
COMPILER_VERSION = ERROR-COMPILER-VERSION-MUST-BE-SET-FOR-OFFICIAL-BUILD
!endif
WXDEBUGFLAG =
!ifeq BUILD debug
WXDEBUGFLAG = d
!endif
WXUNICODEFLAG =
!ifeq UNICODE 1
WXUNICODEFLAG = u
!endif
WXUNIVNAME =
!ifeq WXUNIV 1
WXUNIVNAME = univ
!endif
WXDLLFLAG =
!ifeq SHARED 1
WXDLLFLAG = dll
!endif
LIBTYPE_SUFFIX =
!ifeq SHARED 0
LIBTYPE_SUFFIX = lib
!endif
!ifeq SHARED 1
LIBTYPE_SUFFIX = dll
!endif
EXTRALIBS_FOR_BASE =
!ifeq MONOLITHIC 0
EXTRALIBS_FOR_BASE = 
!endif
!ifeq MONOLITHIC 1
EXTRALIBS_FOR_BASE =   
!endif
__WXLIB_NET_p =
!ifeq MONOLITHIC 0
__WXLIB_NET_p = &
	wxbase$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_net.lib
!endif
__LIB_PNG_IF_MONO_p =
!ifeq MONOLITHIC 1
__LIB_PNG_IF_MONO_p = $(__LIB_PNG_p)
!endif
__bench_gui___depname =
!ifeq USE_GUI 1
__bench_gui___depname = $(OBJS)\bench_gui.exe
!endif
__WXLIB_CORE_p =
!ifeq MONOLITHIC 0
__WXLIB_CORE_p = &
	wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_core.lib
!endif
__LIB_SCINTILLA_IF_MONO_p =
!ifeq MONOLITHIC 1
__LIB_SCINTILLA_IF_MONO_p = wxscintilla$(WXDEBUGFLAG).lib
!endif
__LIB_TIFF_p =
!ifeq USE_GUI 1
__LIB_TIFF_p = wxtiff$(WXDEBUGFLAG).lib
!endif
__LIB_JPEG_p =
!ifeq USE_GUI 1
__LIB_JPEG_p = wxjpeg$(WXDEBUGFLAG).lib
!endif
__DEBUGINFO =
!ifeq BUILD debug
!ifeq DEBUG_INFO default
__DEBUGINFO = -d2
!endif
!endif
!ifeq BUILD release
!ifeq DEBUG_INFO default
__DEBUGINFO = -d0
!endif
!endif
!ifeq DEBUG_INFO 0
__DEBUGINFO = -d0
!endif
!ifeq DEBUG_INFO 1
__DEBUGINFO = -d2
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
__OPTIMIZEFLAG =
!ifeq BUILD debug
__OPTIMIZEFLAG = -od
!endif
!ifeq BUILD release
__OPTIMIZEFLAG = -ot -ox
!endif
__THREADSFLAG =
!ifeq USE_THREADS 0
__THREADSFLAG = 
!endif
!ifeq USE_THREADS 1
__THREADSFLAG = -bm
!endif
__RUNTIME_LIBS =
!ifeq RUNTIME_LIBS dynamic
__RUNTIME_LIBS = -br
!endif
!ifeq RUNTIME_LIBS static
__RUNTIME_LIBS = 
!endif
__RTTIFLAG =
!ifeq USE_RTTI 0
__RTTIFLAG = 
!endif
!ifeq USE_RTTI 1
__RTTIFLAG = -xr
!endif
__EXCEPTIONSFLAG =
!ifeq USE_EXCEPTIONS 0
__EXCEPTIONSFLAG = 
!endif
!ifeq USE_EXCEPTIONS 1
__EXCEPTIONSFLAG = -xs
!endif
__WXLIB_BASE_p =
!ifeq MONOLITHIC 0
__WXLIB_BASE_p = &
	wxbase$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR).lib
!endif
__WXLIB_MONO_p =
!ifeq MONOLITHIC 1
__WXLIB_MONO_p = &
	wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR).lib
!endif
__LIB_PNG_p =
!ifeq USE_GUI 1
__LIB_PNG_p = wxpng$(WXDEBUGFLAG).lib
!endif
__CAIRO_LIB_p =
!ifeq USE_CAIRO 1
__CAIRO_LIB_p = cairo.lib
!endif
____CAIRO_LIBDIR_FILENAMES =
!ifeq USE_CAIRO 1
____CAIRO_LIBDIR_FILENAMES = libpath $(CAIRO_ROOT)\lib
!endif
__WXUNIV_DEFINE_p =
!ifeq WXUNIV 1
__WXUNIV_DEFINE_p = -d__WXUNIVERSAL__
!endif
__DEBUG_DEFINE_p =
!ifeq DEBUG_FLAG 0
__DEBUG_DEFINE_p = -dwxDEBUG_LEVEL=0
!endif
__NDEBUG_DEFINE_p =
!ifeq BUILD release
__NDEBUG_DEFINE_p = -dNDEBUG
!endif
__EXCEPTIONS_DEFINE_p =
!ifeq USE_EXCEPTIONS 0
__EXCEPTIONS_DEFINE_p = -dwxNO_EXCEPTIONS
!endif
__RTTI_DEFINE_p =
!ifeq USE_RTTI 0
__RTTI_DEFINE_p = -dwxNO_RTTI
!endif
__THREAD_DEFINE_p =
!ifeq USE_THREADS 0
__THREAD_DEFINE_p = -dwxNO_THREADS
!endif
__UNICODE_DEFINE_p =
!ifeq UNICODE 0
__UNICODE_DEFINE_p = -dwxUSE_UNICODE=0
!endif
!ifeq UNICODE 1
__UNICODE_DEFINE_p = -d_UNICODE
!endif
____CAIRO_INCLUDEDIR_FILENAMES =
!ifeq USE_CAIRO 1
____CAIRO_INCLUDEDIR_FILENAMES = -i=$(CAIRO_ROOT)\include\cairo
!endif
__DLLFLAG_p =
!ifeq SHARED 1
__DLLFLAG_p = -dWXUSINGDLL
!endif

### Variables: ###

WX_RELEASE_NODOT = 29
COMPILER_PREFIX = wat
OBJS = &
	$(COMPILER_PREFIX)$(COMPILER_VERSION)_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WXDLLFLAG)$(CFG)
LIBDIRNAME = &
	.\..\..\lib\$(COMPILER_PREFIX)$(COMPILER_VERSION)_$(LIBTYPE_SUFFIX)$(CFG)
SETUPHDIR = &
	$(LIBDIRNAME)\$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)
BENCH_CXXFLAGS = $(__DEBUGINFO) $(__OPTIMIZEFLAG) $(__THREADSFLAG) &
	$(__RUNTIME_LIBS) -d__WXMSW__ $(__WXUNIV_DEFINE_p) $(__DEBUG_DEFINE_p) &
	$(__NDEBUG_DEFINE_p) $(__EXCEPTIONS_DEFINE_p) $(__RTTI_DEFINE_p) &
	$(__THREAD_DEFINE_p) $(__UNICODE_DEFINE_p) -i=$(SETUPHDIR) &
	-i=.\..\..\include $(____CAIRO_INCLUDEDIR_FILENAMES) -wx -wcd=549 -wcd=656 &
	-wcd=657 -wcd=667 -i=. $(__DLLFLAG_p) -dwxUSE_GUI=0 $(__RTTIFLAG) &
	$(__EXCEPTIONSFLAG) $(CPPFLAGS) $(CXXFLAGS)
BENCH_OBJECTS =  &
	$(OBJS)\bench_bench.obj &
	$(OBJS)\bench_datetime.obj &
	$(OBJS)\bench_htmlpars.obj &
	$(OBJS)\bench_htmltag.obj &
	$(OBJS)\bench_ipcclient.obj &
	$(OBJS)\bench_log.obj &
	$(OBJS)\bench_mbconv.obj &
	$(OBJS)\bench_strings.obj &
	$(OBJS)\bench_tls.obj &
	$(OBJS)\bench_printfbench.obj
BENCH_GUI_CXXFLAGS = $(__DEBUGINFO) $(__OPTIMIZEFLAG) $(__THREADSFLAG) &
	$(__RUNTIME_LIBS) -d__WXMSW__ $(__WXUNIV_DEFINE_p) $(__DEBUG_DEFINE_p) &
	$(__NDEBUG_DEFINE_p) $(__EXCEPTIONS_DEFINE_p) $(__RTTI_DEFINE_p) &
	$(__THREAD_DEFINE_p) $(__UNICODE_DEFINE_p) -i=$(SETUPHDIR) &
	-i=.\..\..\include $(____CAIRO_INCLUDEDIR_FILENAMES) -wx -wcd=549 -wcd=656 &
	-wcd=657 -wcd=667 -i=. $(__DLLFLAG_p) -i=.\..\..\samples -dNOPCH $(__RTTIFLAG) &
	$(__EXCEPTIONSFLAG) $(CPPFLAGS) $(CXXFLAGS)
BENCH_GUI_OBJECTS =  &
	$(OBJS)\bench_gui_bench.obj &
	$(OBJS)\bench_gui_image.obj


all : $(OBJS)
$(OBJS) :
	-if not exist $(OBJS) mkdir $(OBJS)

### Targets: ###

all : .SYMBOLIC $(OBJS)\bench.exe data $(__bench_gui___depname) data-image

clean : .SYMBOLIC 
	-if exist $(OBJS)\*.obj del $(OBJS)\*.obj
	-if exist $(OBJS)\*.res del $(OBJS)\*.res
	-if exist $(OBJS)\*.lbc del $(OBJS)\*.lbc
	-if exist $(OBJS)\*.ilk del $(OBJS)\*.ilk
	-if exist $(OBJS)\*.pch del $(OBJS)\*.pch
	-if exist $(OBJS)\bench.exe del $(OBJS)\bench.exe
	-if exist $(OBJS)\bench_gui.exe del $(OBJS)\bench_gui.exe

$(OBJS)\bench.exe :  $(BENCH_OBJECTS)
	@%create $(OBJS)\bench.lbc
	@%append $(OBJS)\bench.lbc option quiet
	@%append $(OBJS)\bench.lbc name $^@
	@%append $(OBJS)\bench.lbc option caseexact
	@%append $(OBJS)\bench.lbc  $(__DEBUGINFO_1)  libpath $(LIBDIRNAME) system nt ref 'main_' $(____CAIRO_LIBDIR_FILENAMES) $(LDFLAGS)
	@for %i in ($(BENCH_OBJECTS)) do @%append $(OBJS)\bench.lbc file %i
	@for %i in ( $(__WXLIB_NET_p)  $(__WXLIB_BASE_p)  $(__WXLIB_MONO_p) $(__LIB_PNG_IF_MONO_p) wxzlib$(WXDEBUGFLAG).lib wxregex$(WXUNICODEFLAG)$(WXDEBUGFLAG).lib wxexpat$(WXDEBUGFLAG).lib $(EXTRALIBS_FOR_BASE)  $(__CAIRO_LIB_p) kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib wininet.lib) do @%append $(OBJS)\bench.lbc library %i
	@%append $(OBJS)\bench.lbc
	@for %i in () do @%append $(OBJS)\bench.lbc option stack=%i
	wlink @$(OBJS)\bench.lbc

data : .SYMBOLIC 
	if not exist $(OBJS) mkdir $(OBJS)
	for %f in (htmltest.html) do if not exist $(OBJS)\%f copy .\%f $(OBJS)

!ifeq USE_GUI 1
$(OBJS)\bench_gui.exe :  $(BENCH_GUI_OBJECTS) $(OBJS)\bench_gui_sample.res
	@%create $(OBJS)\bench_gui.lbc
	@%append $(OBJS)\bench_gui.lbc option quiet
	@%append $(OBJS)\bench_gui.lbc name $^@
	@%append $(OBJS)\bench_gui.lbc option caseexact
	@%append $(OBJS)\bench_gui.lbc  $(__DEBUGINFO_1)  libpath $(LIBDIRNAME) system nt ref 'main_' $(____CAIRO_LIBDIR_FILENAMES) $(LDFLAGS)
	@for %i in ($(BENCH_GUI_OBJECTS)) do @%append $(OBJS)\bench_gui.lbc file %i
	@for %i in ( $(__WXLIB_CORE_p)  $(__WXLIB_BASE_p)  $(__WXLIB_MONO_p) $(__LIB_SCINTILLA_IF_MONO_p) $(__LIB_TIFF_p) $(__LIB_JPEG_p) $(__LIB_PNG_p)   wxzlib$(WXDEBUGFLAG).lib wxregex$(WXUNICODEFLAG)$(WXDEBUGFLAG).lib wxexpat$(WXDEBUGFLAG).lib $(EXTRALIBS_FOR_BASE)  $(__CAIRO_LIB_p) kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib wininet.lib) do @%append $(OBJS)\bench_gui.lbc library %i
	@%append $(OBJS)\bench_gui.lbc option resource=$(OBJS)\bench_gui_sample.res
	@for %i in () do @%append $(OBJS)\bench_gui.lbc option stack=%i
	wlink @$(OBJS)\bench_gui.lbc
!endif

data-image : .SYMBOLIC 
	if not exist $(OBJS) mkdir $(OBJS)
	for %f in (../../samples/image/horse.bmp ../../samples/image/horse.jpg ../../samples/image/horse.png ../../samples/image/horse.tif) do if not exist $(OBJS)\%f copy .\%f $(OBJS)

$(OBJS)\bench_bench.obj :  .AUTODEPEND .\bench.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(BENCH_CXXFLAGS) $<

$(OBJS)\bench_datetime.obj :  .AUTODEPEND .\datetime.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(BENCH_CXXFLAGS) $<

$(OBJS)\bench_htmlpars.obj :  .AUTODEPEND .\htmlparser\htmlpars.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(BENCH_CXXFLAGS) $<

$(OBJS)\bench_htmltag.obj :  .AUTODEPEND .\htmlparser\htmltag.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(BENCH_CXXFLAGS) $<

$(OBJS)\bench_ipcclient.obj :  .AUTODEPEND .\ipcclient.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(BENCH_CXXFLAGS) $<

$(OBJS)\bench_log.obj :  .AUTODEPEND .\log.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(BENCH_CXXFLAGS) $<

$(OBJS)\bench_mbconv.obj :  .AUTODEPEND .\mbconv.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(BENCH_CXXFLAGS) $<

$(OBJS)\bench_strings.obj :  .AUTODEPEND .\strings.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(BENCH_CXXFLAGS) $<

$(OBJS)\bench_tls.obj :  .AUTODEPEND .\tls.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(BENCH_CXXFLAGS) $<

$(OBJS)\bench_printfbench.obj :  .AUTODEPEND .\printfbench.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(BENCH_CXXFLAGS) $<

$(OBJS)\bench_gui_sample.res :  .AUTODEPEND .\..\..\samples\sample.rc
	wrc -q -ad -bt=nt -r -fo=$^@    -d__WXMSW__ $(__WXUNIV_DEFINE_p) $(__DEBUG_DEFINE_p) $(__NDEBUG_DEFINE_p) $(__EXCEPTIONS_DEFINE_p) $(__RTTI_DEFINE_p) $(__THREAD_DEFINE_p) $(__UNICODE_DEFINE_p)  -i=$(SETUPHDIR) -i=.\..\..\include $(____CAIRO_INCLUDEDIR_FILENAMES) -i=. $(__DLLFLAG_p) -i=.\..\..\samples -dNOPCH $<

$(OBJS)\bench_gui_bench.obj :  .AUTODEPEND .\bench.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(BENCH_GUI_CXXFLAGS) $<

$(OBJS)\bench_gui_image.obj :  .AUTODEPEND .\image.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(BENCH_GUI_CXXFLAGS) $<

