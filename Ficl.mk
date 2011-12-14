# vim: set ts=4:

###############################################################################
#
#	Copyright 2005-2011 Digital Aggregates Corporation, Colorado, USA.
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
###############################################################################

#
#	@memo	Desperado Ficl 4.1.0 Customization Makefile
#
#	Requires that FICLHOME be defined upon entry to identify where
#	the FICL source distribution is located.
#
#	@author	coverclock@diag.com (Chip Overclock)
#

FICLDEF			=	-DDESPERADO_HAS_FICL
FICLINCDIR		=	-iquote$(FICLHOME)
FICLLIBDIR		=	-Wl,-L$(FICLHOME)
ifdef DYNAMIC
FICLLIBRARY		=	-Wl,-Bdynamic -Wl,-lficl
else
FICLLIBRARY		=	-Wl,-Bstatic -Wl,-lficl
endif

#
#	Install the ficllocal.h customization file in the Ficl directory.
#

ficl:	ficl-localize ficl-clean ficl-build

HERE=$(shell pwd)

ficl-localize:	Makefile.ficl.desperado include/com/diag/desperado/ficldesperado.h ficldesperado.cc
	ln -s -f $(HERE)/include/com/diag/desperado/ficldesperado.h $(FICLHOME)/ficlplatform/desperado.h
	ln -s -f $(HERE)/ficldesperado.cc $(FICLHOME)/ficlplatform/desperado.c

ficl-build:
ifdef DYNAMIC
	$(MAKE) -e -f $(HERE)/Makefile.ficl.desperado -C $(FICLHOME) libficl.a libficl.so.4.1.0
else
	$(MAKE) -e -f $(HERE)/Makefile.ficl.desperado -C $(FICLHOME) libficl.a
endif

ficl-clean:
	$(MAKE) -e -f $(HERE)/Makefile.ficl.desperado -C $(FICLHOME) clean

ficl-install:	ficl-target
	cp $(FICLHOME)/libficl.a $(INSTALLDIR)

ficl-target:
ifdef DYNAMIC
	( cd $(INSTALLDIR); rm -f libficl.so* )
	cp $(FICLHOME)/libficl.so.4.1.0 $(INSTALLDIR)
	( cd $(INSTALLDIR); rm -f libficl.so.4.1; ln -s libficl.so.4.1.0 libficl.so.4.1 )
	( cd $(INSTALLDIR); rm -f libficl.so.4; ln -s libficl.so.4.1.0 libficl.so.4 )
	( cd $(INSTALLDIR); rm -f libficl.so; ln -s libficl.so.4.1.0 libficl.so )
endif
