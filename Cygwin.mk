# vim: set ts=4:

###############################################################################
#
#	Copyright 2005 Digital Aggregates Corp., Arvada CO 80001-0587, USA.
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
#	$Id: Cygwin.mk,v 1.5 2006/09/12 20:23:54 jsloan Exp $
#
###############################################################################

#
#	@memo	Desperado Cygwin Platform Makefile
#
#	@author	coverclock@diag.com (Chip Overclock)
#

CXX			=	g++
CC			=	gcc
LD			=	g++
AR			=	ar
RANLIB		=	ranlib
NCSL		=	sclc
DOXYGEN		=	doxygen
PS2PDF		=	ps2pdf
CSCOPE		=	cscope -R
EXEDITOR	=	ex
MAN2PS		=	groff -man -Tps -
BROWSER		=	mozilla
READER		=	acroread

CPPONLY		=	-E

CDEFINES	=	-DDESPERADO_TARGET_IS_$(TARGET) \
				-DDESPERADO_TARGET_NAME="\"$(TARGET)\"" \
				-DDESPERADO_PLATFORM_IS_$(PLATFORM) \
				-DDESPERADO_PLATFORM_NAME="\"$(PLATFORM)\""  \
				-DDESPERADO_PLATFORM_CLASS=$(PLATFORM) \
				$(ADJUNCTDEF) -D_REENTRANT -D_GNU_SOURCE

ifdef IQUOTE
CINCLUDES	=	-iquote. $(ADJUNCTINCDIR)
else
CINCLUDES	=	-I. $(ADJUNCTINCDIR) -I-
endif

CDEBUG		=	-g3 -O3 -pg

COPTIONS	=	-pipe -Wall -W -Wno-long-long -Wmissing-prototypes

CXXOPTIONS	=	-pipe -fcheck-new -fno-rtti -fno-implicit-templates -Wall -W -Wno-long-long -Wabi -Wold-style-cast -Winline

LDLIBDIRS	=	-L. $(ADJUNCTLIBDIR) $(PLATFORMLIBDIR) $(TARGETLIBDIR)

LDLIBRARIES	=	-l$(LIBRARY) $(ADJUNCTLIBRARY) -lpthread -lm -l$(LIBRARY) $(ADJUNCTLIBRARY)

CPPFLAGS	=	$(CDEFINES) $(CINCLUDES)

CFLAGS		=	$(CDEBUG) $(COPTIONS)

CXXFLAGS	=	$(CDEBUG) $(CXXOPTIONS)

ARFLAGS		=	rcv

LDFLAGS		=	$(CDEBUG) $(LDLIBDIRS) $(LDLIBRARIES)

GCCMACHINE	=	$(shell $(CC) -dumpmachine)
GCCVERSION	=	$(shell $(CC) -dumpversion)
CINCPATH	=	/usr/lib/gcc/$(GCCMACHINE)/$(GCCVERSION)/include
CXXINCPATH	=	/usr/include/boost-1_33_1/boost/compatibility/cpp_c_headers
