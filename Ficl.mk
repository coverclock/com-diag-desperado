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
#	$Id: Ficl.mk,v 1.19 2006/09/12 20:23:54 jsloan Exp $
#
###############################################################################

#
#	@memo	Desperado Ficl 4.0.31 Customization Makefile
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

ficl-localize:	Makefile.ficl.desperado ficllocal.h ficldesperado.h ficldesperadoc.txt
	-mv -i $(FICLHOME)/Makefile.ficl.desperado $(FICLHOME)/Makefile.ficl.desperado-$(TIMESTAMP)
	cp -i Makefile.ficl.desperado $(FICLHOME)
	-mv -i $(FICLHOME)/ficllocal.h $(FICLHOME)/ficllocal.h-$(TIMESTAMP)
	cp -i ficllocal.h $(FICLHOME)
	-mv -i $(FICLHOME)/ficldesperado.h $(FICLHOME)/ficldesperado.h-$(TIMESTAMP)
	cp -i ficldesperado.h $(FICLHOME)
	-mv -i $(FICLHOME)/ficldesperado.c $(FICLHOME)/ficldesperado.c-$(TIMESTAMP)
	cp -i ficldesperadoc.txt $(FICLHOME)/ficldesperado.c

ficl-build:
ifdef DYNAMIC
	( cd $(FICLHOME); $(MAKE) -f Makefile.ficl.desperado libficl.a libficl.so )
else
	( cd $(FICLHOME); $(MAKE) -f Makefile.ficl.desperado libficl.a )
endif

ficl-clean:
	( cd $(FICLHOME); $(MAKE) -f Makefile.ficl.desperado clean )

ficl-install:	ficl-target
	cp $(FICLHOME)/libficl.a $(INSTALLDIR)

ficl-target:
ifdef DYNAMIC
	( cd $(INSTALLDIR); rm -f libficl.so* )
	cp $(FICLHOME)/libficl.so.4.0.31 $(INSTALLDIR)
	( cd $(INSTALLDIR); rm -f libficl.so.4.0; ln -s libficl.so.4.0.31 libficl.so.4.0 )
	( cd $(INSTALLDIR); rm -f libficl.so.4; ln -s libficl.so.4.0.31 libficl.so.4 )
	( cd $(INSTALLDIR); rm -f libficl.so; ln -s libficl.so.4.0.31 libficl.so )
endif
