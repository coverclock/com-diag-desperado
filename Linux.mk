# vim: set ts=4:

###############################################################################
#
#	Copyright 2005-2008 Digital Aggregates Corp., Arvada CO 80001-0587, USA.
#	This file is part of the Digital Aggregates Desperado library.
#	
#	This library is free software; you can redistribute it and/or
#	modify it under the terms of the GNU Lesser General Public
#	License as published by the Free Software Foundation; either
#	version 2.1 of the License, or (at your option) any later version.
#
#	As a special exception, if other files instantiate templates or
#	use macros or inline functions from this file, or you compile
#	this file and link it with other works to produce a work based on
#	this file, this file does not by itself cause the resulting work
#	to be covered by the GNU Lesser General Public License. However
#	the source code for this file must still be made available in
#	accordance with the GNU Lesser General Public License.
#
#	This exception does not invalidate any other reasons why a work
#	based on this file might be covered by the GNU Lesser General
#	Public License.
#
#	Alternative commercial licensing terms are available from the copyright
#	holder. Contact Digital Aggregates Corporation for more information.
#
#	This library is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU Lesser General Public License for more details.
#
#	You should have received a copy of the GNU Lesser General
#	Public License along with this library; if not, write to the
#	Free Software Foundation, Inc., 59 Temple Place, Suite 330,
#	Boston, MA 02111-1307 USA, or http://www.gnu.org/copyleft/lesser.txt.
#
#	$Name:  $
#
#	$Id: Linux.mk,v 1.42 2007/01/29 15:17:08 jsloan Exp $
#
###############################################################################

#
#	@memo	Desperado Linux Platform Makefile
#
#	@author	coverclock@diag.com (Chip Overclock)
#

AR			=	${CROSS_COMPILE}ar
AS			=	${CROSS_COMPILE}as
CC			=	${CROSS_COMPILE}gcc
CXX			=	${CROSS_COMPILE}g++
GDB			=	${CROSS_COMPILE}gdb
LD			=	${CROSS_COMPILE}g++
NM			=	${CROSS_COMPILE}nm
RANLIB		=	${CROSS_COMPILE}ranlib
SO			=	$(CROSS_COMPILE)g++
STRINGS		=	${CROSS_COMPILE}strings
STRIP		=	${CROSS_COMPILE}strip

BROWSER		=	firefox
CSCOPE		=	cscope -R
CVS			=	cvs
DOXYGEN		=	doxygen
EXEDITOR	=	ex
MAN2PS		=	groff -man -Tps -
NCSL		=	sclc
PS2PDF		=	ps2pdf
READER		=	acroread
SVN			=	svn

CPPONLY		=	-E

ASMONLY		=	-S -dA

ifdef INT64
CDEFINES	=	-DDESPERADO_TARGET_IS_$(TARGET) \
				-DDESPERADO_TARGET_NAME="\"$(TARGET)\"" \
				-DDESPERADO_PLATFORM_IS_$(PLATFORM) \
				-DDESPERADO_PLATFORM_NAME="\"$(PLATFORM)\""  \
				-DDESPERADO_PLATFORM_CLASS=$(PLATFORM) \
				-DDESPERADO_HAS_SYSLOG \
				-D__int64="$(INT64)" \
				$(ADJUNCTDEF) -D_REENTRANT -D_GNU_SOURCE
else
CDEFINES	=	-DDESPERADO_TARGET_IS_$(TARGET) \
				-DDESPERADO_TARGET_NAME="\"$(TARGET)\"" \
				-DDESPERADO_PLATFORM_IS_$(PLATFORM) \
				-DDESPERADO_PLATFORM_NAME="\"$(PLATFORM)\""  \
				-DDESPERADO_PLATFORM_CLASS=$(PLATFORM) \
				-DDESPERADO_HAS_SYSLOG \
				$(ADJUNCTDEF) -D_REENTRANT -D_GNU_SOURCE
endif

ifdef IQUOTE
CINCLUDES	=	-iquote. $(ADJUNCTINCDIR)
else
CINCLUDES	=	-I. $(ADJUNCTINCDIR) -I-
endif

CDEBUG		=	-g -O

# -pedantic may cause problems depending on the compiler version.
# -Werror may cause heartache with certain gcc versions regarding inlines.
GCCOPTIONS	=	-ansi -pedantic -pipe -Wall -W -Wno-long-long -fPIC
COPTIONS	=	-Wmissing-prototypes
# -frepo with gcc 3.3.2 seems to drive the compiler into a loop in some cases.
CXXOPTIONS	=	-fcheck-new -fno-rtti -Wabi -Wold-style-cast -Winline -fno-implicit-templates

CPPFLAGS	=	$(CDEFINES) $(CINCLUDES)

CFLAGS		=	$(CDEBUG) $(GCCOPTIONS) $(COPTIONS)

CXXFLAGS	=	$(CDEBUG) $(GCCOPTIONS) $(CXXOPTIONS)

ARFLAGS		=	rcv

STRIPFLAGS	=	--strip-unneeded --remove-section=.comment

LDLIBDIRS	=	-Wl,-L. $(ADJUNCTLIBDIR) $(PLATFORMLIBDIR) $(TARGETLIBDIR)

ifdef DYNAMIC
LDLIBRARIES	=	-Wl,-Bdynamic -Wl,-l$(LIBRARY) $(ADJUNCTLIBRARY) -Wl,-Bdynamic -Wl,-l$(LIBRARY) -Wl,-Bdynamic -Wl,-lpthread -Wl,-Bdynamic -Wl,-lrt -Wl,-Bdynamic -Wl,-lm
else
LDLIBRARIES	=	-Wl,-Bstatic -Wl,-l$(LIBRARY) $(ADJUNCTLIBRARY) -Wl,-Bstatic -Wl,-l$(LIBRARY) -Wl,-Bstatic -Wl,-lpthread -Wl,-Bstatic -Wl,-lrt -Wl,-Bstatic -Wl,-lm
endif

LDFLAGS		=	$(CDEBUG) $(LDLIBDIRS) $(LDLIBRARIES)

GCCMACHINE	=	$(shell $(CC) -dumpmachine)
GCCVERSION	=	$(shell $(CC) -dumpversion)

# Shared Object (like a DLL under Windows)

SOPREFIX	=	$(CDEBUG) -shared -Wl,-soname,$(SONAME) -Wl,-export-dynamic
SOSUFFIX	=	-Wl,-Bdynamic $(LDDYNAMIC)

LD_LIBRARY_PATH	=	$(ROOT):$(FICLHOME):$(JAVAHOME)/jre/lib/$(JAVATARG)/server
export LD_LIBRARY_PATH

$(SONAME):	$(SOFILE)
	rm -f $(SONAME)
	ln -s $(SOFILE) $(SONAME)

$(SONAME2):	$(SONAME)
	rm -f $(SONAME2)
	ln -s $(SOFILE) $(SONAME2)

$(SHAREDOBJ):	$(SONAME2)
	rm -f $(SHAREDOBJ)
	ln -s $(SOFILE) $(SHAREDOBJ)

so-links:	$(SOFILE) $(SONAME) $(SONAME2) $(SHAREDOBJ)

so-path:
	@echo export LD_LIBRARY_PATH=\"$(LD_LIBRARY_PATH)\"

$(SOFILE):	$(SHARED)
	$(SO) $(SOPREFIX) -o $(SOFILE) $(SHARED) $(SOSUFFIX)

shared:	so

so:	$(SOFILE) so-links so-path

sostripped:	$(STRIPPED)
	$(SO) $(SOPREFIX) -o $(SOFILE) $(STRIPPED) $(SOSUFFIX)
