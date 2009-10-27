# vim:set ts=4:

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
#	$Id: Makefile,v 1.108 2007/01/31 23:41:10 jsloan Exp $
#
###############################################################################

#
#	@memo	Project Makefile
#
#	@author	coverclock@diag.com (Chip Overclock)
#

#
#	Configuration
#

#
# Leave this stuff as is unless you have a compelling reason not to.
#

DOMAIN		=	diag.com
PRODUCT		=	desperado
PROJECT		=	Desperado
RELEASE		=	refuge
MAJOR		=	2
MINOR		=	10
BUILD		=	0
PRERELEASE	=	syracuse

#
# Indicate the platform and target you are using.
#

#PLATFORM	=	Arroyo
#PLATFORM	=	Diminuto
PLATFORM	=	Linux
#PLATFORM	=	Cygwin

#TARGET		=	ARM920T
TARGET		=	IA32

#
# Define if you want to build using dynamic linking.
# Comment out if you want to build using static linking.
# The Java Native Interface requires dynamic linking.
# Dynamic linking requires that Ficl, if used, also be dynamically linked.
#

DYNAMIC		=	shared

#
# Specify where your public and temporary directories are for make install.
# The public directory will be assumed to have include and lib subdirectories.
#

TMPDIR		=	/tmp
#PUBDIR		=	/usr/local
PUBDIR		=	/opt/diminuto/buildroot/usr/local

#
# Define how and where you get to Subversion.
# This is mostly for my own use.
#

SVNPROTO	=	svn
SVNHOST		=	192.168.1.220
SVNTRUNK	=	${SVNPROTO}://${SVNHOST}/${PRODUCT}/trunk
SVNTAG		=	${SVNPROTO}://${SVNHOST}/${PRODUCT}/tags

# If you are using Ficl, specify where it is.
# Comment out otherwise.

FICLHOME	=	/home/jsloan/src/ficl4.0.31
#FICLHOME	=	/home/jsloan/arroyo/ficl-4.0.31
#FICLHOME	=	/home/jsloan/diminuto/ficl-4.0.31
#FICLHOME	=	/cygdrive/c/Users/jsloan/Desktop/Home/Sources/ficl4.0.31

# If you are using Java, specify where it is.
# Comment out otherwise.

JAVAHOME	=	/opt/jdk1.6.0_07
#JAVAHOME	=	/usr/local/apps/jdk1.6.0_02
#JAVAHOME	=	/cygdrive/c/java/jdk1.6.0_02

#
# If you are using Java, say more about its platform and target.
# These are actually subdirectory names inside the JAVAHOME/jre/lib.
#

JAVAPLAT	=	linux
#JAVAPLAT	=	win32

JAVATARG	=	i386
#JAVATARG	=	arm

#
#	Targets
#

default:
	$(MAKE) -e library
	$(MAKE) -e binaries

all:
	$(MAKE) -e depend
	$(MAKE) -e adjuncts
	$(MAKE) -e library
	$(MAKE) -e binaries

include Desperado.mk
