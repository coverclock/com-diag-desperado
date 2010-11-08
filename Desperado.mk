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
#	$Id: Desperado.mk,v 1.44 2007/01/31 18:47:46 jsloan Exp $
#
###############################################################################

#
#	@memo	Desperado Makefile
#
#	@author	coverclock@diag.com (Chip Overclock)
#

#
#	Date and Time Stamps
#

DATESTAMP	=	$(shell date +'%Y%m%d')
TIMESTAMP	=	$(shell date -u +'%Y%m%d%H%M%S%N%Z')
LATEST		=	$(shell date -u +'%Y-%m-%d %H:%M:%S')
ISO8601		=	$(shell date -u +'%Y-%m-%dT%H:%M:%SZ')

#
#	Prefaces
#

LIBRARY		=	$(PRODUCT)

JAVADIR		=	java
JAVASRC		=	src
JAVAPACKAGE	=	com/diag/desperado
JAVAPATH	=	$(JAVADIR)/$(JAVASRC)/$(JAVAPACKAGE)

#
#	Wildcards
#

CSOURCES	=	$(wildcard *.c)
CXXSOURCES	=	$(wildcard *.cpp)
HEADERS		=	$(wildcard *.h)
JAVASOURCES	=	$(wildcard $(JAVAPATH)/*.java)
MKFILES		=	$(wildcard *.mk)
INTERPRETED	=	$(wildcard *.sh) $(wildcard *.ex) $(wildcard *.awk)
CONFIGS		=	$(wildcard *.cf)
TEXTS		=	$(wildcard *.txt)
HTMLS		=	$(wildcard *.html)
FICLSOURCES	=	$(wildcard *.4th)
DOTFILES	=	$(wildcard .??*)
UNITTESTS	=	$(wildcard unittest*.cpp) $(wildcard unittest*.c)
TESTMAINS	=	$(wildcard main*.cpp) $(wildcard main*.c)
TOOLMAINS	=	$(wildcard tool*.cpp) $(wildcard tool*.c)

#
#	Generated
#

FICLTXTGEN	=	desperado_ficl_shell.txt
FICLHGEN	=
FICLCGEN	=	desperado_ficl_shell.c
FICLCXXGEN	=

JAVATXTGEN	=
JAVAHGEN	=	com_diag_desperado_Platform.h
JAVACGEN	=
JAVACXXGEN	=

TXTGEN		=	$(FICLTXTGEN) $(JAVATXTGEN)
CGEN		=	$(FICLCGEN) $(JAVACGEN)
CXXGEN		=	$(FICLCXXGEN) $(JAVACXXGEN)
HGEN		=	$(FICLHGEN) $(JAVAHGEN)
GENERATED	=	$(CGEN) $(CXXGEN) $(HGEN) $(TXTGEN)

#
#	Files
#

CXXCAPI		=	crcmodel.c barrierApi.c ficlApi.c
COMMANDS	=	dates cpdate
SCRIPTS		=	cpdate.sh dates.sh ficlshell-Cygwin.sh ficlshell-Linux.sh ficlshell.sh iso3166.awk prepare.ex prepare.sh toolong.awk unittestInputOutput.sh unittestsuite.sh
MAKESFILES	=	Makefile Makefile.ficl.desperado $(MKFILES)
ANTFILES	=	$(JAVADIR)/build.xml
EXTRAS		=	doxygen.cf footer.html ficldesperadoc.txt
LICENSES	=	lesser.txt gpl.txt fdl.txt LICENSE-2.0.txt
DOCUMENTS	=	doc/pdf/refman.pdf doc/pdf/manpages.pdf doc/pdf/manpages.ps
TEMPORARIES	=	doxygen-local.cf dependencies.mk $(GENERATED)

#
#	Derivatives
#

SOURCES		=	$(HEADERS) $(CSOURCES) $(CXXSOURCES) $(JAVASOURCES)
COMPILABLES	=	$(CSOURCES) $(CXXSOURCES)
DEPENDABLES	=	$(HEADERS) $(COMPILABLES)
OBJECTS		=	$(addsuffix .o,$(basename $(COMPILABLES)))
REPOS		=	$(addsuffix .rpo,$(basename $(CXXSOURCES)))
UNITOBJECTS	=	$(addsuffix .o,$(basename $(UNITTESTS)))
MAINS		=	$(TESTMAINS) $(TOOLMAINS)
CMEMBERS	=	$(filter-out $(MAINS),$(CSOURCES))
CXXMEMBERS	=	$(filter-out $(MAINS),$(CXXSOURCES))
MEMBERS		=	$(sort $(CMEMBERS) $(CXXMEMBERS) $(CGEN))
ARCHIVED	=	$(addsuffix .o,$(basename $(MEMBERS)))
NONSYMBOLS	=	$(filter-out $(CGEN),$(MEMBERS))
EXTRACTED	=	$(addsuffix .o,$(basename $(NONSYMBOLS)))
SHARED		=	$(ARCHIVED)
STRIPPED	=	$(addsuffix .os,$(basename $(SHARED)))
ARCHIVE		=	lib$(LIBRARY).a
SHAREDOBJ	=	lib$(LIBRARY).so
SONAME		=	$(SHAREDOBJ).$(MAJOR)
SONAME2		=	$(SHAREDOBJ).$(MAJOR).$(MINOR)
SOFILE		=	$(SHAREDOBJ).$(MAJOR).$(MINOR).$(BUILD)
SHAREDOBJS	=	$(SHAREDOBJ) $(SONAME) $(SONAME2) $(SOFILE)
UNITMAINS	=	$(subst main,unittest,$(basename $(TESTMAINS)))
TOOLS		=	$(subst tool,,$(basename $(TOOLMAINS)))
WINMAINS	=	$(foreach T,$(UNITMAINS),$(T).exe)
WINTOOLS	=	$(foreach T,$(TOOLS),$(T).exe)
BINARIES	=	$(UNITMAINS) $(TOOLS) $(COMMANDS)
WINBINARIES	=	$(WINMAINS) $(WINTOOLS)

MANIFEST	=	$(sort $(SOURCES) $(MAKESFILES) $(ANTFILES) $(EXTRAS) $(LICENSES) $(INTERPRETED) $(DOTFILES) $(FICLSOURCES) $(SCRIPTS))

BETA		=	$(DOMAIN)/$(PRODUCT)/$(RELEASE)
ALPHA		=	$(DOMAIN)/$(PRODUCT)/$(PRERELEASE)
EMBED		=	$(DOMAIN)/$(PRODUCT)/diminuto

ROOT		=	$(shell pwd)

#
#	Eclipse Targets
#

eclipse-build:
	$(MAKE) -e -k depend
	$(MAKE) -e -k library

eclipse-rebuild:
	$(MAKE) -e -k clean
	$(MAKE) -e -k depend
	$(MAKE) -e -k library
	$(MAKE) -e -k adjuncts
	$(MAKE) -e -k binaries

eclipse-clean:
	$(MAKE) -e -k clean

#
#	Adjuncts
#

ifdef FICLHOME
FICLADJUNCT	=	ficl
FICLCLEAN	=	ficl-clean
include Ficl.mk
endif

ifdef JAVAHOME
JAVAADJUNCT	=	java
JAVACLEAN	=	java-clean
include Java.mk
endif

ADJUNCTDEF		=	$(FICLDEF) $(JAVADEF)
ADJUNCTINCDIR	=	$(FICLINCDIR) $(JAVAINCDIR)
ADJUNCTLIBDIR	=	$(FICLLIBDIR) $(JAVALIBDIR)
ADJUNCTLIBRARY	=	$(FICLLIBRARY) $(JAVALIBRARY)

adjuncts:	$(FICLADJUNCT) $(JAVAADJUNCT)

adjuncts-clean:	$(FICLCLEAN) $(JAVACLEAN)

#
#	Platform
#

include $(PLATFORM).mk

#
#	Dependencies
#
#	Dependencies are made on demand, not whenever anything changes.
#

depend dependencies:
	$(CXX) $(CPPFLAGS) -M -MG $(COMPILABLES) > dependencies.mk

-include dependencies.mk

#
#	Build
#

Vintage.cpp:	$(filter-out Vintage.cpp,$(NONSYMBOLS))
	touch Vintage.cpp

vintage:
	touch Vintage.cpp

ifdef DYNAMIC
library:	static dynamic
else
library:	static
endif

static:		$(ARCHIVE)

dynamic:	$(SHAREDOBJ)

binaries:	$(BINARIES)

unittests:	$(UNITMAINS)

objects:	$(OBJECTS)

repositories:	$(REPOS)

headers:	$(HEADERS)

#
#	Install
#

SHAREDOBJ	=	lib$(LIBRARY).so
SONAME		=	$(SHAREDOBJ).$(MAJOR)
SONAME2		=	$(SHAREDOBJ).$(MAJOR).$(MINOR)
SOFILE		=	$(SHAREDOBJ).$(MAJOR).$(MINOR).$(BUILD)

install:	$(PUBDIR)/include $(PUBDIR)/lib $(PUBDIR)/bin headers library binaries
	cp $(BINARIES) $(PUBDIR)/bin
	cp $(HEADERS) $(PUBDIR)/include
	$(MAKE) -e desperado-install INSTALLDIR=$(PUBDIR)/lib
	$(MAKE) -e ficl-install INSTALLDIR=$(PUBDIR)/lib

#
#	Target
#

target:		$(TMPDIR)/$(PRODUCT)-diminuto.tgz

$(TMPDIR)/$(PRODUCT)-diminuto.tgz:	embeddable
	( cd $(TMPDIR); tar cvzf - $(EMBED) > $(PRODUCT)-diminuto.tgz )

embeddable:		headers library binaries
	rm -rf $(TMPDIR)/$(EMBED)
	mkdir -p $(TMPDIR)/$(EMBED)
	cp $(BINARIES) $(TMPDIR)/$(EMBED)
	$(MAKE) -e desperado-target INSTALLDIR=$(TMPDIR)/$(EMBED)
	$(MAKE) -e ficl-target INSTALLDIR=$(TMPDIR)/$(EMBED)

#
#	Helpers
#

desperado-install:	library desperado-target
	cp $(ARCHIVE) $(INSTALLDIR)

desperado-target:	library
ifdef DYNAMIC
	( cd $(INSTALLDIR); rm -f $(SHAREDOBJ)* )
	cp $(SOFILE) $(INSTALLDIR)
	( cd $(INSTALLDIR); ln -s $(SOFILE) $(SONAME2) )
	( cd $(INSTALLDIR); ln -s $(SOFILE) $(SONAME) )
	( cd $(INSTALLDIR); ln -s $(SOFILE) $(SHAREDOBJ) )
endif

#
#	Test
#
#	e.g.
#
#	make unittest TEST=unittestJavaVirtualMachine
#	make unittest TEST=unittestInputOutput SH=sh
#	make unittest TEST=unittestFicl ARGS=interactive
#

unittestsuite:	unittests unittestsuite.sh
	sh unittestsuite.sh > unittestsuite-$(PRERELEASE)-$(PLATFORM)-$(TARGET)-$(DATESTAMP)-log.txt 2>&1

unittest:	$(TEST)
	$(SH) $(TEST) $(ARGS)

#
#	Clean Up
#

clean:
	-rm -f $(TEMPORARIES) $(OBJECTS) $(STRIPPED) $(REPOS) $(DOCUMENTS) $(BINARIES) $(WINBINARIES) $(ARCHIVE) $(SHAREDOBJS)

mrproper:	pristine

pristine:	clean adjuncts-clean
	-(cd doc/latex; $(MAKE) -e clean)
	-rm -f doc/latex/*.eps doc/latex/*.pdf doc/latex/*.tex
	-rm -f doc/html/*.gif doc/html/*.ttf
	-rm -f doc/html/*.html doc/html/*.png doc/html/*.css
	-rm -f doc/man/cat3/*.3 doc/man/cat3/*.3.gz doc/man/man3/*.3
	-rm -f manpages.ps manpages.pdf refman.pdf

#
#	Distribution
#	
# release (BETA)                most recent tagged version
# prerelease (ALPHA)            most recent checked-in version
#
#	Using CVS:
#
# checkout the next release:    cvs checkout diag.com/desperado
# commit the latest revisions:  cvs commit .
# generate the current relase:  cvs export -r $(RELEASE) diag.com/desperado
# generate the next release:    cvs export -D $(LATEST) diag.com/desperado
# freeze the next release:      cvs tag $(RELEASE) .
#
#	Using SVN:
#
# checkout the next release:    svn checkout svn://localhost/desperado/trunk/Desperado diag.com/desperado
# commit the latest revisions:  svn commit .
# generate the current relase:  svn export svn://localhost/desperado/tags/$(RELEASE)/Desperado diag.com/desperado
# generate the next release:    svn checkout svn://localhost/desperado/trunk/Desperado diag.com/desperado
# freeze the next relase:       svn copy svn://localhost/desperado/trunk svn://localhost/desperado/tags/$(RELEASE)
# add a new element:            svn add [filename]
#
#	Other stuff:
#
# download the latest release:  wget [ -Y on ] ftp://ftp.webcom.com/pub2/jsloan/www/ftp/ desperado-$(RELEASE).tgz
#

freeze:
	${SVN} copy ${SVNTRUNK} ${SVNTAG}/$(RELEASE)

manifest:	manifest.txt
	cat manifest.txt

manifest.txt:	$(MANIFEST)
	ls $(MANIFEST) | sort | uniq > manifest.txt

beta:	release

release:
	rm -rf $(TMPDIR)/$(BETA)
	${SVN} export ${SVNTAG}/$(RELEASE)/${PROJECT} $(TMPDIR)/$(BETA)
	sh prepare.sh $(TMPDIR)/$(BETA)
	(cd $(TMPDIR); tar cvzf - ./$(BETA) > $(PRODUCT)-$(RELEASE).tgz)

alpha:	prerelease

prerelease:
	rm -rf $(TMPDIR)/$(ALPHA)
	${SVN} export ${SVNTRUNK}/${PROJECT} $(TMPDIR)/$(ALPHA)
	sh prepare.sh $(TMPDIR)/$(ALPHA)
	(cd $(TMPDIR); tar cvzf - ./$(ALPHA) > $(PRODUCT)-$(PRERELEASE)-ALPHA.tgz)

dist:	distribution

distribution:	release

#
#	Backup
#

backup:	../$(PRODUCT).bak.tgz
	mv -i ../$(PRODUCT).bak.tgz ../$(PRODUCT).$(TIMESTAMP).tgz

../$(PRODUCT).bak.tgz:
	tar cvzf - . > ../$(PRODUCT).bak.tgz

#
#	Documentation
#
#	When unbundling on the R&D web server, try the following.
#
#		cd ~apache/rnd/desperado
#		rm -rf doc
#		umask 022
#		tarxvpzf desperado-$(RELEASE)-doc.tgz
#

documentation:	doc/pdf
	sed -e "s/\\\$$Name.*\\\$$/$(RELEASE)/" < doxygen.cf > doxygen-local.cf
	$(DOXYGEN) doxygen-local.cf
	(cd doc/latex; $(MAKE) -e refman.pdf; cp refman.pdf ../pdf)
	cat doc/man/man3/*.3 | $(MAN2PS) > doc/pdf/manpages.ps
	$(PS2PDF) doc/pdf/manpages.ps doc/pdf/manpages.pdf

browse:
	$(BROWSER) file:$(ROOT)/doc/html/index.html

read:
	$(READER) file:$(ROOT)/doc/pdf/refman.pdf

man:
	$(READER) file:$(ROOT)/doc/pdf/manpages.pdf

bundle:
	(cd ./doc; tar cvzf - .) > $(TMPDIR)/$(PRODUCT)-$(RELEASE)-doc.tgz

#
#	Patterns
#

$(ARCHIVE):	$(ARCHIVE)($(ARCHIVED))
	$(RANLIB) $(ARCHIVE)

$(ARCHIVE)($%):	$%
	$(AR) $(ARFLAGS) $@ $%

%.o:	%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

%.o:	%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

%.os:	%.o
	cp $< $@
	$(STRIP) $(STRIPFLAGS) $@

#
#	Utilities
#

transmogrify:
	$(EXEDITOR) "+source $(SCRIPT)" $(SOURCES)

archive:	$(ARCHIVE)($(NAME))

preprocess-c:	$(NAME)
	$(CC) $(CPPONLY) $(CPPFLAGS) $(NAME)

preprocess-cxx:	$(NAME)
	$(CXX) $(CPPONLY) $(CPPFLAGS) $(NAME)

preassemble-c:	$(NAME)
	$(CC) $(ASMONLY) $(CPPFLAGS) $(CFLAGS) $(NAME)

preassemble-cxx:	$(NAME)
	$(CXX) $(ASMONLY) $(CPPFLAGS) $(CXXFLAGS) $(NAME)

compile-c:	$(NAME) $(ARCHIVE)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(NAME)

compile-cxx:	$(NAME) $(ARCHIVE)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $(NAME)

simple-c:	$(NAME)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(NAME)
	# $(CC) $(NAME)

simple-cxx:	$(NAME)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(NAME)
	# $(CXX) $(NAME)

#
#	Metrics
#

ncsl-classes:
	$(NCSL) [A-Z]*.h [A-Z]*.cpp

ncsl-unittests:
	$(NCSL) unittest*.cpp unittest*.c main*.cpp main*.c

ncsl-tools:
	$(NCSL) tool*.cpp

ncsl-cxx:
	$(NCSL) *.h *.cpp

ncsl-c:
	$(NCSL) *.c

ncsl-sources:
	$(NCSL) *.h *.cpp *.c

ncsl:	ncsl-classes ncsl-unittests ncsl-tools ncsl-cpp ncsl-c ncsl-sources

metrics:	ncsl

#
#	Unit Tests
#

unittestArgument:	mainArgument.o $(ARCHIVE)
	$(LD) -o unittestArgument mainArgument.o $(LDFLAGS)

unittestAscii:	mainAscii.o $(ARCHIVE)
	$(LD) -o unittestAscii mainAscii.o $(LDFLAGS)

unittestassert:	mainassert.o $(ARCHIVE)
	$(LD) -o unittestassert mainassert.o $(LDFLAGS)

unittestAttribute:	mainAttribute.o $(ARCHIVE)
	$(LD) -o unittestAttribute mainAttribute.o $(LDFLAGS)

unittestBandwidthThrottle:	mainBandwidthThrottle.o $(ARCHIVE)
	$(LD) -o unittestBandwidthThrottle mainBandwidthThrottle.o $(LDFLAGS)

unittestbarrier:	mainbarrier.o $(ARCHIVE)
	$(LD) -o unittestbarrier mainbarrier.o $(LDFLAGS)

unittestByteOrder:	mainByteOrder.o $(ARCHIVE)
	$(LD) -o unittestByteOrder mainByteOrder.o $(LDFLAGS)

unittestcxxcapi:	maincxxcapi.o $(ARCHIVE)
	$(LD) -o unittestcxxcapi maincxxcapi.o $(LDFLAGS)

unittestcxxjapi:	maincxxjapi.o $(ARCHIVE)
	$(LD) -o unittestcxxjapi maincxxjapi.o $(LDFLAGS)

unittestCellRateThrottle:	mainCellRateThrottle.o $(ARCHIVE)
	$(LD) -o unittestCellRateThrottle mainCellRateThrottle.o $(LDFLAGS) 

unittestChain:	mainChain.o $(ARCHIVE)
	$(LD) -o unittestChain mainChain.o $(LDFLAGS)

unittestCommonEra:	mainCommonEra.o $(ARCHIVE)
	$(LD) -o unittestCommonEra mainCommonEra.o $(LDFLAGS)

unittestCounters:	mainCounters.o $(ARCHIVE)
	$(LD) -o unittestCounters mainCounters.o $(LDFLAGS)

unittestCrc:	mainCrc.o $(ARCHIVE)
	$(LD) -o unittestCrc mainCrc.o $(LDFLAGS)

unittestDump:	mainDump.o $(ARCHIVE)
	$(LD) -o unittestDump mainDump.o $(LDFLAGS)

unittestEncode:	mainEncode.o $(ARCHIVE)
	$(LD) -o unittestEncode mainEncode.o $(LDFLAGS)

unittestEscape:	mainEscape.o $(ARCHIVE)
	$(LD) -o unittestEscape mainEscape.o $(LDFLAGS)

unittestException:	mainException.o $(ARCHIVE)
	$(LD) -o unittestException mainException.o $(LDFLAGS)

unittestFifo:	mainFifo.o $(ARCHIVE)
	$(LD) -o unittestFifo mainFifo.o $(LDFLAGS)

unittestgenerics:	maingenerics.o $(ARCHIVE)
	$(LD) -o unittestgenerics maingenerics.o $(LDFLAGS)

unittestGeometricThrottle:	mainGeometricThrottle.o $(ARCHIVE)
	$(LD) -o unittestGeometricThrottle mainGeometricThrottle.o $(LDFLAGS)

unittestGrayCode:	mainGrayCode.o $(ARCHIVE)
	$(LD) -o unittestGrayCode mainGrayCode.o $(LDFLAGS)

unittestHeap:	mainHeap.o $(ARCHIVE)
	$(LD) -o unittestHeap mainHeap.o $(LDFLAGS)

unittestImplementation:	mainImplementation.o $(ARCHIVE)
	$(LD) -o unittestImplementation mainImplementation.o $(LDFLAGS)

unittestIso3166:	mainIso3166.o $(ARCHIVE)
	$(LD) -o unittestIso3166 mainIso3166.o $(LDFLAGS)

unittestJavaVirtualMachine:	mainJavaVirtualMachine.o $(ARCHIVE) $(JARFILE)
	$(LD) -o unittestJavaVirtualMachine mainJavaVirtualMachine.o $(LDFLAGS)

unittestLinkType:	mainLinkType.o $(ARCHIVE)
	$(LD) -o unittestLinkType mainLinkType.o $(LDFLAGS)

unittestLogger:	mainLogger.o $(ARCHIVE)
	$(LD) -o unittestLogger mainLogger.o $(LDFLAGS)

unittestMeter:	mainMeter.o $(ARCHIVE)
	$(LD) -o unittestMeter mainMeter.o $(LDFLAGS)

unittestMinimumMaximum:	mainMinimumMaximum.o $(ARCHIVE)
	$(LD) -o unittestMinimumMaximum mainMinimumMaximum.o $(LDFLAGS)

unittestMutex:	mainMutex.o $(ARCHIVE)
	$(LD) -o unittestMutex mainMutex.o $(LDFLAGS)

unittestnamespace:	mainnamespace.o $(ARCHIVE)
	$(LD) -o unittestnamespace mainnamespace.o $(LDFLAGS)

unittestNumber:	mainNumber.o $(ARCHIVE)
	$(LD) -o unittestNumber mainNumber.o $(LDFLAGS)

unittestPlatform:	mainPlatform.o $(ARCHIVE)
	$(LD) -o unittestPlatform mainPlatform.o $(LDFLAGS)

unittestPrimes:	mainPrimes.o $(ARCHIVE)
	$(LD) -o unittestPrimes mainPrimes.o $(LDFLAGS)

unittestRam:	mainRam.o $(ARCHIVE)
	$(LD) -o unittestRam mainRam.o $(LDFLAGS)

unittestRatio:	mainRatio.o $(ARCHIVE)
	$(LD) -o unittestRatio mainRatio.o $(LDFLAGS)

unittestRoot:	mainRoot.o $(ARCHIVE)
	$(LD) -o unittestRoot mainRoot.o $(LDFLAGS)

unittestService:	mainService.o $(ARCHIVE)
	$(LD) -o unittestService mainService.o $(LDFLAGS)

unittestStreamSocket:	mainStreamSocket.o $(ARCHIVE)
	$(LD) -o unittestStreamSocket mainStreamSocket.o $(LDFLAGS)

unitteststring:	mainstring.o $(ARCHIVE)
	$(LD) -o unitteststring mainstring.o $(LDFLAGS)

unittesttarget:	maintarget.o $(ARCHIVE)
	$(LD) -o unittesttarget maintarget.o $(LDFLAGS)

unittestThrottle:	mainThrottle.o $(ARCHIVE)
	$(LD) -o unittestThrottle mainThrottle.o $(LDFLAGS)

unittestInputOutput:	mainInputOutput.o $(ARCHIVE)
	$(LD) -o unittestInputOutput mainInputOutput.o $(LDFLAGS)

unittestInputOutputStatic:	mainInputOutputStatic.o $(ARCHIVE)
	$(LD) -o unittestInputOutputStatic mainInputOutputStatic.o $(LDFLAGS)

unittestVintage:	mainVintage.o $(ARCHIVE)
	$(LD) -o unittestVintage mainVintage.o $(LDFLAGS)

unittestVolatile:	mainVolatile.o $(ARCHIVE)
	$(LD) -o unittestVolatile mainVolatile.o $(LDFLAGS)

unittestWord:	mainWord.o $(ARCHIVE)
	$(LD) -o unittestWord mainWord.o $(LDFLAGS)

#
#	Tools
#

ascii:	toolascii.o $(ARCHIVE)
	$(LD) -o ascii toolascii.o $(LDFLAGS)

dump:	tooldump.o $(ARCHIVE)
	$(LD) -o dump tooldump.o $(LDFLAGS)

commonera:	toolcommonera.o $(ARCHIVE)
	$(LD) -o commonera toolcommonera.o $(LDFLAGS)

localtime:	toollocaltime.o $(ARCHIVE)
	$(LD) -o localtime toollocaltime.o $(LDFLAGS)

localdate:	toollocaldate.o $(ARCHIVE)
	$(LD) -o localdate toollocaldate.o $(LDFLAGS)

tzset:	tooltzset.o $(ARCHIVE)
	$(LD) -o tzset tooltzset.o $(LDFLAGS)

timestamps:	tooltimestamps.o $(ARCHIVE)
	$(LD) -o timestamps tooltimestamps.o $(LDFLAGS)

coreable:	toolcoreable.o $(ARCHIVE)
	$(LD) -o coreable toolcoreable.o $(LDFLAGS)

dates:	dates.sh
	cp dates.sh dates
	chmod 755 dates

cpdate:	cpdate.sh
	cp cpdate.sh cpdate
	chmod 755 cpdate

#
#	ficlsh and other Ficl related stuff
#

unittestFicl:	mainFicl.o $(ARCHIVE)
	$(LD) -o unittestFicl mainFicl.o $(LDFLAGS)

unittestFiclShell:	mainFiclShell.o $(ARCHIVE)
	$(LD) -o unittestFiclShell mainFiclShell.o $(LDFLAGS)

desperado_ficl_shell.txt:	ficlshell-$(PLATFORM).sh $(EXTRACTED)
	sh ficlshell-$(PLATFORM).sh $(EXTRACTED) | sort | uniq > desperado_ficl_shell.txt

desperado_ficl_shell.c:	ficlshell.sh desperado_ficl_shell.txt
	sh ficlshell.sh desperado_ficl_shell.txt > desperado_ficl_shell.c

ficlsh:	toolficlsh.o $(ARCHIVE)
	$(LD) -o ficlsh toolficlsh.o $(LDFLAGS)

#
#	Directories
#

$(PUBDIR)/include:
	mkdir -p $(PUBDIR)/include

$(PUBDIR)/lib:
	mkdir -p $(PUBDIR)/lib

$(PUBDIR)/bin:
	mkdir -p $(PUBDIR)/bin

doc/pdf:
	mkdir -p doc/pdf
