# vim: set ts=4:

###############################################################################
#
#	Copyright 2006 Digital Aggregates Corp., Arvada CO 80001-0587, USA.
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
#	$Id: Java.mk,v 1.10 2006/09/12 16:49:22 jsloan Exp $
#
###############################################################################

#
#	@memo	Desperado Java Customization Makefile
#
#	Requires that JAVAHOME be defined upon entry to identify where
#	the Java Development Kit distribution is located.
#
#	@author	coverclock@diag.com (Chip Overclock)
#

JAVAINCPATH		=	$(JAVAHOME)/include
JAVAINCPLATPATH	=	$(JAVAHOME)/include/$(JAVAPLAT)
JAVADEF			=	-DDESPERADO_HAS_JAVA
JAVAINCDIR		=	-I$(JAVAINCPATH) -I$(JAVAINCPLATPATH)
JAVALIBDIR		=	-L$(JAVAHOME)/jre/lib/i386/server
JAVALIBRARY		=	-Wl,-Bdynamic -Wl,-ljvm

JARFILE			=	$(PRODUCT).jar
PLATFORMJNIH	=	com_diag_desperado_Platform.h
PLATFORMJNIO	=	Java_com_diag_desperado_Platform.o

JAVAH			=	javah  -classpath $(JARFILE) -jni
JAVAP			=	javap  -classpath $(JARFILE) -s -p
ANT				=	ant -v
JAR				=	jar

ifdef JAVAHOME

java:	java-clean java-install java-disassemble $(PLATFORMJNIH)

java-install:	$(JARFILE)

java-disassemble: $(JARFILE)
	$(JAVAP) com.diag.desperado.Platform
	$(JAVAP) com.diag.desperado.UnitTestJavaVirtualMachine
	
java-clean:
	(cd $(JAVADIR); $(ANT) clean)
	rm -f $(JARFILE) $(PLATFORMJNIH)

$(PLATFORMJNIH):	$(JARFILE)
	$(JAVAH) com.diag.desperado.Platform

$(JARFILE):
	(cd $(JAVADIR); $(ANT) install)


$(PLATFORMJNIO):	$(PLATFORMJNIH)

endif
