#!#############################################################################
#! File:    g95.t
#! Purpose: tmake template file from which makefile.g95 is generated by running
#!          tmake -t g95 wxwin.pro -o makefile.g95
#! Author:  Vadim Zeitlin, Robert Roebling, Julian Smart
#! Created: 14.07.99
#! Version: $Id$
#!#############################################################################
#${
    #! include the code which parses filelist.txt file and initializes
    #! %wxCommon, %wxGeneric and %wxMSW hashes.
    IncludeTemplate("filelist.t");

    #! now transform these hashes into $project tags
    foreach $file (sort keys %wxGeneric) {
        #! native wxDirDlg can't be compiled due to GnuWin32/OLE limitations,
        #! so take the generic version
        if ( $wxGeneric{$file} =~ /\b(PS|G|U|16)\b/ ) {
            next #! unless $file =~ /^dirdlgg\./;
        }

        $file =~ s/cp?p?$/\$(OBJSUFF)/;
        $project{"WXGENERICOBJS"} .= '$(GENDIR)/' . $file . " "
    }

    foreach $file (sort keys %wxCommon) {
        next if $wxCommon{$file} =~ /\b(16|U)\b/;

        #! needs extra files (sql*.h) so not compiled by default.
        #! next if $file =~ /^odbc\./;

        if ( $file =~ /^odbc\./ )
        {
          $file =~ s/cp?p?$/\$(OBJSUFF)/;
          $project{"ADVANCEDOBJS"} .= '$(COMMDIR)/' . $file . " "
        }
        else
        {
          $file =~ s/cp?p?$/\$(OBJSUFF)/;
          $project{"WXCOMMONOBJS"} .= '$(COMMDIR)/' . $file . " "
        }
    }

    foreach $file (sort keys %wxMSW) {
        #! native wxDirDlg can't be compiled due to GnuWin32/OLE limitations,
        next if $file =~ /^dirdlg\./;

        next if $wxMSW{$file} =~ /\b(16)\b/;

        #! Mingw32 doesn't have the OLE headers and has some troubles with
        #! socket code, so put in  ADVANCEDOBJS
        if ( $wxMSW{$file} =~ /\b(O)\b/ )
        {
          $file =~ s/cp?p?$/\$(OBJSUFF)/;
          $project{"ADVANCEDOBJS"} .= '$(MSWDIR)/ole/' . $file . " "
        }
        else
        {
          $file =~ s/cp?p?$/\$(OBJSUFF)/;
          $project{"WXMSWOBJS"} .= '$(MSWDIR)/' . $file . " "
        }

    }

    foreach $file (sort keys %wxHTML) {
        $file =~ s/cp?p?$/\$(OBJSUFF)/;
        $project{"WXHTMLOBJS"} .= '$(HTMLDIR)/' . $file . " "
    }

#$}
# This file was automatically generated by tmake at #$ Now()
# DO NOT CHANGE THIS FILE, YOUR CHANGES WILL BE LOST! CHANGE G95.T!

#
# File:     makefile.g95
# Author:   Julian Smart, Robert Roebling, Vadim Zeitlin
# Created:  1993
# Updated:  1999
# Copyright:(c) 1993, AIAI, University of Edinburgh,
# Copyright:(c) 1999, Vadim Zeitlin
# Copyright:(c) 1999, Robert Roebling
#
# Makefile for libwx.a

# Replace this with your own path if necessary
WXDIR = ../..

# All common compiler flags and options are now in
# this central makefile.
include $(WXDIR)/src/makeg95.env

# DLL Name, if building wxWindows as a DLL.
ifdef WXMAKINGDLL
WXDLL = $(WXDIR)/lib/wxmsw$(WXVERSION)$(UNIEXT).dll
WXDEF = wxmsw$(WXVERSION)$(UNIEXT).def
DLL_EXTRA_LIBS = $(WXDIR)/lib/libzlib.a \
                 $(WXDIR)/lib/libpng.a $(WXDIR)/lib/libjpeg.a \
	             $(WXDIR)/lib/libtiff.a $(WXDIR)/lib/libregex.a
DLL_LDFLAGS = -L$(WXDIR)/lib
DLL_LDLIBS = -mwindows -lcomctl32 -lctl3d32 -lole32 -loleaut32 \
             -luuid -lrpcrt4 -lodbc32 -lwinmm -lopengl32 \
             -lwsock32 $(DLL_EXTRA_LIBS) \
	          -lstdc++
endif

# Subordinate library possibilities

EXTRAOBJS=

GENDIR  = $(WXDIR)/src/generic
COMMDIR = $(WXDIR)/src/common
HTMLDIR = $(WXDIR)/src/html
ZLIBDIR = $(WXDIR)/src/zlib
PNGDIR  = $(WXDIR)/src/png
JPEGDIR = $(WXDIR)/src/jpeg
TIFFDIR = $(WXDIR)/src/tiff
OLEDIR  = $(WXDIR)/src/msw/ole
MSWDIR  = $(WXDIR)/src/msw
REGEXDIR= $(WXDIR)/src/regex

ZLIBLIB = $(WXDIR)/lib/libzlib.a
PNGLIB  = $(WXDIR)/lib/libpng.a
JPEGLIB = $(WXDIR)/lib/libjpeg.a
TIFFLIB = $(WXDIR)/lib/libtiff.a
REGEXLIB= $(WXDIR)/lib/libregex.a

DOCDIR = $(WXDIR)/docs

# Only use the WIN32 wxDirDialog if we have a recent
# version of Mingw32
ifeq ($(MINGW32),1)
  ifneq "$(findstring 2.95, $(MINGW32VERSION))" ""
		DIRDLGOBJ = $(MSWDIR)/dirdlg.$(OBJSUFF)
  else
		DIRDLGOBJ = $(GENDIR)/dirdlgg.$(OBJSUFF)
  endif
else
		DIRDLGOBJ = $(GENDIR)/dirdlgg.$(OBJSUFF)
endif

GENERICOBJS = \
                #$ ExpandList("WXGENERICOBJS");

COMMONOBJS  = \
		$(COMMDIR)/y_tab.$(OBJSUFF) \
		#$ ExpandList("WXCOMMONOBJS");

HTMLOBJS = \
                #$ ExpandList("WXHTMLOBJS");

MSWOBJS     = \
		#$ ExpandList("WXMSWOBJS");

ADVANCEDOBJS     = \
		#$ ExpandList("ADVANCEDOBJS");

ZLIBOBJS    = \
		$(ZLIBDIR)/adler32.$(OBJSUFF) \
		$(ZLIBDIR)/compress.$(OBJSUFF) \
		$(ZLIBDIR)/crc32.$(OBJSUFF) \
		$(ZLIBDIR)/gzio.$(OBJSUFF) \
		$(ZLIBDIR)/uncompr.$(OBJSUFF) \
		$(ZLIBDIR)/deflate.$(OBJSUFF) \
		$(ZLIBDIR)/trees.$(OBJSUFF) \
		$(ZLIBDIR)/zutil.$(OBJSUFF) \
		$(ZLIBDIR)/inflate.$(OBJSUFF) \
		$(ZLIBDIR)/infblock.$(OBJSUFF) \
		$(ZLIBDIR)/inftrees.$(OBJSUFF) \
		$(ZLIBDIR)/infcodes.$(OBJSUFF) \
		$(ZLIBDIR)/infutil.$(OBJSUFF) \
		$(ZLIBDIR)/inffast.$(OBJSUFF)

PNGOBJS     = \
		$(PNGDIR)/png.$(OBJSUFF) \
		$(PNGDIR)/pngread.$(OBJSUFF) \
		$(PNGDIR)/pngrtran.$(OBJSUFF) \
		$(PNGDIR)/pngrutil.$(OBJSUFF) \
		$(PNGDIR)/pngpread.$(OBJSUFF) \
		$(PNGDIR)/pngtrans.$(OBJSUFF) \
		$(PNGDIR)/pngwrite.$(OBJSUFF) \
		$(PNGDIR)/pngwtran.$(OBJSUFF) \
		$(PNGDIR)/pngwutil.$(OBJSUFF) \
		$(PNGDIR)/pngerror.$(OBJSUFF) \
		$(PNGDIR)/pngmem.$(OBJSUFF) \
		$(PNGDIR)/pngwio.$(OBJSUFF) \
		$(PNGDIR)/pngrio.$(OBJSUFF) \
		$(PNGDIR)/pngget.$(OBJSUFF) \
		$(PNGDIR)/pngset.$(OBJSUFF)


JPEGOBJS    = \
		$(JPEGDIR)/jcomapi.$(OBJSUFF) \
		$(JPEGDIR)/jutils.$(OBJSUFF) \
		$(JPEGDIR)/jerror.$(OBJSUFF) \
		$(JPEGDIR)/jmemmgr.$(OBJSUFF) \
		$(JPEGDIR)/jmemnobs.$(OBJSUFF) \
		$(JPEGDIR)/jcapimin.$(OBJSUFF) \
		$(JPEGDIR)/jcapistd.$(OBJSUFF) \
		$(JPEGDIR)/jctrans.$(OBJSUFF) \
		$(JPEGDIR)/jcparam.$(OBJSUFF) \
		$(JPEGDIR)/jdatadst.$(OBJSUFF) \
		$(JPEGDIR)/jcinit.$(OBJSUFF) \
		$(JPEGDIR)/jcmaster.$(OBJSUFF) \
		$(JPEGDIR)/jcmarker.$(OBJSUFF) \
		$(JPEGDIR)/jcmainct.$(OBJSUFF) \
		$(JPEGDIR)/jcprepct.$(OBJSUFF) \
		$(JPEGDIR)/jccoefct.$(OBJSUFF) \
		$(JPEGDIR)/jccolor.$(OBJSUFF) \
		$(JPEGDIR)/jcsample.$(OBJSUFF) \
		$(JPEGDIR)/jchuff.$(OBJSUFF) \
		$(JPEGDIR)/jcphuff.$(OBJSUFF) \
		$(JPEGDIR)/jcdctmgr.$(OBJSUFF) \
		$(JPEGDIR)/jfdctfst.$(OBJSUFF) \
		$(JPEGDIR)/jfdctflt.$(OBJSUFF) \
		$(JPEGDIR)/jfdctint.$(OBJSUFF) \
		$(JPEGDIR)/jdapimin.$(OBJSUFF) \
		$(JPEGDIR)/jdapistd.$(OBJSUFF) \
		$(JPEGDIR)/jdtrans.$(OBJSUFF) \
		$(JPEGDIR)/jdatasrc.$(OBJSUFF) \
		$(JPEGDIR)/jdmaster.$(OBJSUFF) \
		$(JPEGDIR)/jdinput.$(OBJSUFF) \
		$(JPEGDIR)/jdmarker.$(OBJSUFF) \
		$(JPEGDIR)/jdhuff.$(OBJSUFF) \
		$(JPEGDIR)/jdphuff.$(OBJSUFF) \
		$(JPEGDIR)/jdmainct.$(OBJSUFF) \
		$(JPEGDIR)/jdcoefct.$(OBJSUFF) \
		$(JPEGDIR)/jdpostct.$(OBJSUFF) \
		$(JPEGDIR)/jddctmgr.$(OBJSUFF) \
		$(JPEGDIR)/jidctfst.$(OBJSUFF) \
		$(JPEGDIR)/jidctflt.$(OBJSUFF) \
		$(JPEGDIR)/jidctint.$(OBJSUFF) \
		$(JPEGDIR)/jidctred.$(OBJSUFF) \
		$(JPEGDIR)/jdsample.$(OBJSUFF) \
		$(JPEGDIR)/jdcolor.$(OBJSUFF) \
		$(JPEGDIR)/jquant1.$(OBJSUFF) \
		$(JPEGDIR)/jquant2.$(OBJSUFF) \
		$(JPEGDIR)/jdmerge.$(OBJSUFF)

TIFFOBJS = $(TIFFDIR)/tif_aux.o \
		$(TIFFDIR)/tif_close.o \
		$(TIFFDIR)/tif_codec.o \
		$(TIFFDIR)/tif_compress.o \
		$(TIFFDIR)/tif_dir.o \
		$(TIFFDIR)/tif_dirinfo.o \
		$(TIFFDIR)/tif_dirread.o \
		$(TIFFDIR)/tif_dirwrite.o \
		$(TIFFDIR)/tif_dumpmode.o \
		$(TIFFDIR)/tif_error.o \
		$(TIFFDIR)/tif_fax3.o \
		$(TIFFDIR)/tif_fax3sm.o \
		$(TIFFDIR)/tif_flush.o \
		$(TIFFDIR)/tif_getimage.o \
		$(TIFFDIR)/tif_jpeg.o \
		$(TIFFDIR)/tif_luv.o \
		$(TIFFDIR)/tif_lzw.o \
		$(TIFFDIR)/tif_next.o \
		$(TIFFDIR)/tif_open.o \
		$(TIFFDIR)/tif_packbits.o \
		$(TIFFDIR)/tif_pixarlog.o \
		$(TIFFDIR)/tif_predict.o \
		$(TIFFDIR)/tif_print.o \
		$(TIFFDIR)/tif_read.o \
		$(TIFFDIR)/tif_strip.o \
		$(TIFFDIR)/tif_swab.o \
		$(TIFFDIR)/tif_thunder.o \
		$(TIFFDIR)/tif_tile.o \
		$(TIFFDIR)/tif_version.o \
		$(TIFFDIR)/tif_warning.o \
		$(TIFFDIR)/tif_win32.o \
		$(TIFFDIR)/tif_write.o \
		$(TIFFDIR)/tif_zip.o

ifeq ($(MINGW32),1)
  ifneq "$(findstring 2.95, $(MINGW32VERSION))" ""
    OBJECTS = $(MSWOBJS) $(COMMONOBJS) $(GENERICOBJS) $(HTMLOBJS) $(DIRDLGOBJ) $(ADVANCEDOBJS)
  else
    OBJECTS = $(MSWOBJS) $(COMMONOBJS) $(GENERICOBJS) $(HTMLOBJS) $(DIRDLGOBJ)
  endif
else
  OBJECTS = $(MSWOBJS) $(COMMONOBJS) $(GENERICOBJS) $(HTMLOBJS) $(DIRDLGOBJ)
endif

# MBN: if anyone has a better solution for this kludge, step
#      forward, *please*
# this tests is we are on cygwin or not ( will _not_ work if you are using
# ZSH on plain Win32, tought ); it uses the presence of "/"
# in the PATH variable

# how do you do "VAR=\" ? BLEAGH!
BACKSLASH=$(subst a,\,a)
ifeq (,$(findstring /,$(PATH)))
  IS_CYGWIN=0
  PATH_SEPARATOR:=$(BACKSLASH)
  PATH_SUBST=/
else
  IS_CYGWIN=1
  PATH_SEPARATOR=/
  PATH_SUBST:=$(BACKSLASH)
endif

#ARCHINCDIR=$(subst $(PATH_SUBST),$(PATH_SEPARATOR),$(WXDIR)/lib/msw$(INCEXT))
ARCHINCDIR=(WXDIR)/lib/msw$(INCEXT)

SETUP_H=$(ARCHINCDIR)/wx/setup.h

ifndef WXMAKINGDLL
all:    $(SETUP_H) $(OBJECTS) $(WXLIB) $(ZLIBLIB) $(PNGLIB) $(JPEGLIB) $(TIFFLIB) $(REGEXLIB)
else
all:    $(SETUP_H) $(OBJECTS) $(ZLIBLIB) $(PNGLIB) $(JPEGLIB) $(TIFFLIB) $(REGEXLIB) $(WXDLL)
endif

$(ARCHINCDIR)/wx:
	mkdir $(subst $(PATH_SUBST),$(PATH_SEPARATOR),$(ARCHINCDIR))
	mkdir $(subst $(PATH_SUBST),$(PATH_SEPARATOR),$(ARCHINCDIR)/wx)

$(SETUP_H): $(ARCHINCDIR)/wx
	$(COPY) $(WXDIR)/include/wx/msw/setup.h $@

#	$(COPY) $(subst $(PATH_SUBST),$(PATH_SEPARATOR),$(WXDIR)/include/wx/msw/setup.h) $(subst $(PATH_SUBST),$(PATH_SEPARATOR),$@)

ifndef WXMAKINGDLL

$(WXLIB): $(OBJECTS) $(EXTRAOBJS)
	ar $(AROPTIONS) $@ $(EXTRAOBJS) $(OBJECTS)
	$(RANLIB) $@

else

# The new linker is a few orders of magnitude faster than the old way
# of creating DLLs.
ifeq "$(strip $(LD_SUPPORTS_SHARED))" "yes"

$(WXDLL): $(OBJECTS) $(EXTRAOBJS)
	$(CC) -shared -o $@ \
	  -Wl,--output-def,$(WXDEF) \
	  -Wl,--out-implib,$(WXLIB) \
	  $(OBJECTS) $(EXTRAOBJS) \
	  $(DLL_LDFLAGS) $(DLL_LDLIBS)
else

ifeq ($(MINGW32),1)
  DLL_ENTRY = _DllMainCRTStartup@12
else
  DLL_ENTRY = __cygwin_dll_entry@12
endif
LD_STUFF = $(OBJECTS) $(EXTRAOBJS) -Wl,-e,$(DLL_ENTRY) \
           $(DLL_LDFLAGS) $(DLL_LDLIBS) #-Wl,--image-base=0x66000000

DLL_STUFF = --as=$(AS) --dllname $(notdir $(WXDLL)) \
            --def $(WXDEF) \
            --base-file wx.base --output-exp wx.exp

$(WXDEF) $(WXLIB): $(OBJECTS) $(EXTRAOBJS)
	$(DLLTOOL) --output-def $@ --output-lib $(WXLIB) \
	  --dllname $(notdir $(WXDLL)) \
	  $(OBJECTS) $(EXTRAOBJS) $(DLL_EXTRA_LIBS)

$(WXDLL): $(OBJECTS) $(EXTRAOBJS) $(WXDEF)
	$(CC) -mdll -Wl,--base-file,wx.base -s -o $@ $(LD_STUFF)
	$(DLLTOOL) $(DLL_STUFF)
	$(CC) -mdll -Wl,--base-file,wx.base wx.exp -s -o $@ $(LD_STUFF)
	$(DLLTOOL) $(DLL_STUFF)
	$(CC) -mdll wx.exp -o $@ $(LD_STUFF)
	-$(RM) wx.base
	-$(RM) wx.exp

endif

endif


$(ZLIBLIB): $(ZLIBOBJS)
	$(AR) $(AROPTIONS) $@ $(ZLIBOBJS)
	$(RANLIB) $@

$(PNGLIB): $(PNGOBJS)
	$(AR) $(AROPTIONS) $@ $(PNGOBJS)
	$(RANLIB) $@

$(JPEGLIB): $(JPEGOBJS)
	$(AR) $(AROPTIONS) $@ $(JPEGOBJS)
	$(RANLIB) $@

$(TIFFLIB): $(TIFFOBJS)
	$(AR) $(AROPTIONS) $@ $(TIFFOBJS)
	$(RANLIB) $@

$(REGEXLIB):
	$(MAKE) -C $(REGEXDIR) -f makefile.g95 WXDIR=$(WXDIR)

$(OBJECTS):	$(WXINC)/wx/defs.h $(WXINC)/wx/object.h $(ARCHINCDIR)/wx/setup.h

$(COMMDIR)/y_tab.$(OBJSUFF):    $(COMMDIR)/y_tab.c $(COMMDIR)/lex_yy.c
	$(CCLEX) -c $(CPPFLAGS) -DUSE_DEFINE -DYY_USE_PROTOS -o $@ $(COMMDIR)/y_tab.c

$(COMMDIR)/y_tab.c:     $(COMMDIR)/dosyacc.c
	$(COPY) ../common/dosyacc.c ../common/y_tab.c

$(COMMDIR)/lex_yy.c:    $(COMMDIR)/doslex.c
	$(COPY) ../common/doslex.c ../common/lex_yy.c

# Replace lex with flex if you run into compilation
# problems with lex_yy.c. See also note about LEX_SCANNER
# above.
# $(COMMDIR)/lex_yy.c:	$(COMMDIR)/lexer.l
#	$(LEX) -L -o$(COMMDIR)/lex_yy.c $(COMMDIR)/lexer.l
#
# Try one of these if the above line doesn't work.
# Alternative syntax (1)
#	$(LEX) -t -L $(COMMDIR)/lexer.l > $(COMMDIR)/lex_yy.c
# Alternative syntax (2)
#	$(LEX) -L -o$(COMMDIR)/lex_yy.c $(COMMDIR)/lexer.l
#
#	sed -e "s/BUFSIZ/5000/g" < lex.yy.c | \
#	sed -e "s/yyoutput(c)/void yyoutput(c)/g" | \
#       sed -e "s/YYLMAX 200/YYLMAX 5000/g" > lex_yy.c
#	rm -f lex.yy.c
#
# Replace yacc with bison if you run into compilation
# problems with y_tab.c.
#
# $(COMMDIR)/y_tab.c:	$(COMMDIR)/parser.y
#	$(YACC) -o $(COMMDIR)/y_tab.c $(COMMDIR)/parser.y
#
# If you use e.g. gcc on Unix, uncomment these lines
# and comment out the above.
#
# $(COMMDIR)/y_tab.c:	$(COMMDIR)/parser.y
#	$(YACC) $(COMMDIR)/parser.y
#	mv y.tab.c $(COMMDIR)/y_tab.c

clean:
	-$(RM) *.o
	-$(RM) ole/*.o
	-$(RM) *.bak
	-$(RM) core
	-$(RM) ../common/y_tab.c
	-$(RM) ../common/lex_yy.c
	-$(RM) ../common/*.o
	-$(RM) ../common/*.bak
	-$(RM) ../generic/*.o
	-$(RM) ../generic/*.bak
	-$(RM) ../html/*.o
	-$(RM) ../zlib/*.o
	-$(RM) ../zlib/*.bak
	-$(RM) ../png/*.o
	-$(RM) ../png/*.bak
	-$(RM) ../jpeg/*.o
	-$(RM) ../jpeg/*.bak
	-$(RM) ../tiff/*.o
	-$(RM) ../tiff/*.bak
	-$(RM) ../regex/*.o
	-$(RM) ../regex/*.bak

cleanall: clean
	-$(RM) $(WXLIB)
	-$(RM) $(ZLIBLIB)
	-$(RM) $(PNGLIB)
	-$(RM) $(JPEGLIB)
	-$(RM) $(TIFFLIB)
	-$(RM) $(REGEXLIB)

ifdef WXMAKINGDLL
	-$(RM) $(WXDLL)
	-$(RM) $(WXDEF)
ifneq "$(strip $(LD_SUPPORTS_SHARED))" "yes"
	-$(RM) wx.base
	-$(RM) wx.exp
endif
endif

