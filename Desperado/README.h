#ifndef _COM_DIAG_DESPERADO_README_H_
#define _COM_DIAG_DESPERADO_README_H_

/* vim: set ts=4 expandtab shiftwidth=4: */

/*******************************************************************************

Copyright 2005-2009 by the Digital Aggregates Corp., Arvada CO 80001-0587 USA.

----------------------------------------------------------------------

LICENSES

-----

The C and C++ portions of this library are licensed under a modified
version of the GNU Lesser General Public License that allows for
static linking without any viral licensing implications:

--

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

As a special exception, if other files instantiate templates or
use macros or inline functions from this file, or you compile
this file and link it with other works to produce a work based on
this file, this file does not by itself cause the resulting work
to be covered by the GNU Lesser General Public License. However
the source code for this file must still be made available in
accordance with the GNU Lesser General Public License.

This exception does not invalidate any other reasons why a work
based on this file might be covered by the GNU Lesser General
Public License.

Alternative commercial licensing terms are available from the copyright
holder. Contact Digital Aggregates Corporation for more information.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, contact

    Free Software Foundation, Inc.
    59 Temple Place, Suite 330
    Boston MA 02111-1307 USA
    http://www.gnu.org/copyleft/lesser.txt

-----

The Java portions of this library are licensed under the Apache
License:

--

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

----------------------------------------------------------------------

ABSTRACT

This file is part of the Digital Aggregates Corporation Desperado
library. Desperado is an open source library of object-oriented
software components written in C++. It implements design patterns
that the authors have found to be both useful and common in embedded
applications. It was developed as mechanism for the authors to both
learn and teach.

It is licensed under a modified GNU Lesser General Public License
to allow it to be incorporated into proprietary software or
firmware without restriction or viral licensing implication.

Desperado requires

o   ANSI C++ and ANSI C99-compilant compilers,
o   a POSIX-compliant operating system and run-time library, including
o   POSIX threads, and
o   support for 64-bit integral types.

Contact:

    Chip Overclock
    mailto:coverclock@diag.com
    Digital Aggregates Corporation
    Arvada CO 80001-0587 USA

----------------------------------------------------------------------

INSTALLATION

This version of Desperado as distributed can be built to run under
Linux. However, all of the operating system dependencies are
isolated in a single class derived from the base class Platform.
It should be pretty easy replace the Linux class with a new derived
class, for example VxWorks.h and VxWorks.C, and add a new makefile
specific to the new platform, for example VxWorks.mk. There is an
example alternative platform, Cygwin, the Cygnus UNIX emulation that
runs under Windows.

Here is the sequence of commands to build Desperado:

vi Makefile                 # establish your configuration
make clean                  # make clean
make depend                 # establish dependencies
make adjuncts               # builds adjuncts if you want Ficl and/or Java
make library                # builds the archive or shared object
make binaries               # builds unit tests and tools

To run the unit tests when using dynamic linking, you will need to
set the LD_LIBRARY_PATH environment variable appropriately, or else
run the tests from make which sets the variable for itself.

make unittestsuite          # to run all unit tests which runs for hours
make test TEST=unittestCrc  # for example to run a specific unit test
make so-path                # displays the command to set LD_LIBRARY_PATH

Warnings about "old-style casts" (which are typically inside system
header files), "overflow in implicit constant conversion" (which
are typically in the Ficl sources), "can never be inlined" (which are
typically in the JDK jni.h header file), and "inline failed in call"
(which are typically in Desperado and occur depending on what version of
gcc you are using) can be (must be) ignored.

The binaries are main programs and hence might not be applicable
for embedded systems. The adjuncts are optional components such as
the Ficl FORTH interpreter (available from www.sourceforge.net)
using a interface to the Desperado Platform, and a Java JNI interface
to the Desperado Platform.

----------------------------------------------------------------------

HISTORY

Here is a list of Desperado releases.

    acme            1.1.0    2005-02-14
    bachelor        1.2.0    2005-06-27
    cascade         1.3.0    2005-07-05
    dexter          1.4.0    2005-09-03
    empire          1.5.0    2005-09-19
    fortune         1.6.0    2005-09-19
    glacier         1.7.0    2005-09-19
    horseshoe       1.8.0    2005-10-03
    ironside        1.9.0    2005-10-10
    jackpot         1.10.0   2005-10-16
    klondike        1.11.0   2005-10-23
    liberty         1.12.0   2005-10-28
    maverick        1.13.0   2005-10-31
    nugget          1.14.0   2005-11-07
    opportunity     1.15.0   2005-11-22
    paradox         1.16.0   2005-12-28
    quadrilateral   1.17.0   2006-01-09
    rattlesnake     1.18.0   2006-01-09
    shadow          1.19.0   2006-01-09
    tempest         1.20.0   2006-01-14
    union           1.21.0   2006-02-08
    vermillion      1.22.0   2006-05-01
    wildcat         1.23.0   2006-09-14
    xray            1.24.0   2007-01-01
    yukon           1.25.0   2007-01-05
    zephyr          1.26.0   2007-01-10
    alpine          1.27.0   2007-01-12
    bonanza         1.28.0   2007-01-12
    climax          1.29.0   2007-01-12
    dexter          1.30.0   2007-01-12 (oops)
    eureka          1.31.0   2007-01-12
    firefly         1.32.0   2007-01-29
    grizzly         1.33.0   2007-01-29
    hurricane       2.1.0    2007-01-31
    imperial        2.2.0    2007-02-01
    jupiter         2.3.0    2007-08-15
    keystone        2.4.0    2008-08-21
    lucky           2.5.0    2008-09-02
    mercantile      2.6.0    2008-09-02
    neptune         2.7.0
    olympus         2.8.0
    porcupine       2.9.0
    quinto          2.10.0
    refuge          2.11.0
    syracuse        3.1.0   2009-10-28
    triumph         3.2.0   2010-01-04
    uranium         3.3.0   TBD

Information regarding Desperado can be found here:

    http://www.diag.com/navigation/downloads/Desperado.html

----------------------------------------------------------------------

ACKNOWLEDGEMENTS

This software is an original work of its authors.

Portions of this library were inspired by, but do not incorporate,
in any way make use of, are not based upon, and are probably
completely incompatible with, software that may be the intellectual
property of the following people and organizations:

    Avaya Inc.
    1300 West 120th Avenue
    Westminster CO 80234 USA

    Nachum Dershowitz
    Department of Computer Science
    Tel Aviv University
    Tel Aviv ISR

    Digital Aggregates Corporation
    Arvada CO 80001-0587 USA

    Keil Software, Inc.
    1501 10th Street, Suite 110
    Plano TX 75074 USA

    Lance Latham
    Resource Management Systems
    Fredericksburg TX USA

    Lucent Technologies Inc.
    11900 North Pecos Street
    Westminster CO 80234 USA

    Monta Vista Software Inc.
    1237 East Arques Avenue
    Sunnyvale CA 94085 USA

    Edward M. Reingold
    Department of Computer Science
    Illinois Institute of Technology
    Chicago IL USA

    University Corporation for Atmospheric Research
    1850 Table Mesa Drive
    Boulder CO 80303 USA

    Wright State University
    3640 Colonel Glenn Highway
    Dayton OH 45435-0001 USA

The authors would like to acknowledge these people and organizations
for their work in the problem domains addressed by this library.

Portions of this software make use of freely available and unrestricted
software that may be copyrighted by the following people and
organizations:

    Michael Barr
    Netrino, LLC
    Annapolis MD USA

    Jack Ganssle
    The Ganssle Group
    Baltimore MD USA

    John Sadler

    Ross Williams
    Rocksoft Pty. Ltd.
    Adelaide SA AUS

The authors would like to thank these people and organizations for
making their software available.

The design patterns implemented by this software benefitted from
the wisdom and experience of the following cast of thousands:

    Ted Apke
    Bill Bahr
    Michael Barr
    Randy Billinger
    Todd Blachowiak
    Allan Clarke
    Cindy Clay
    Marshall Cline
    Dale Courte
    Jill Courte
    Michael Dierks
    Bob Dixon
    Tom Doeppner
    Issac Eyeson
    Joel Ezell
    Doug Gibbons
    Gene Harano
    Les Hatton
    David Hemmendinger
    Dan Higgins
    Ken Howard
    Won Huh
    Basil Irwin
    Pete Isensee
    Ken Jensen
    Alan Jones
    Chad Komer
    Don Leuenberger
    Sam Linzell
    Joe McTee
    John Meiners
    Paul Moorman
    Demian Neidetcher
    Tamarra Noirot
    Phil Ouellette
    Norm Petty
    Ron Phillips
    Edward Reingold
    Gary Robertson
    Craig Ruff
    John Sadler
    Al Sanders
    Michael Tamny
    Steve Tarr
    Erich Thanhardt
    Scott Thomas
    Mark Uris
    Ross Williams
    Eric Wanowsky
    Chris Wood
    Wayne Zakowski

The authors are grateful for their sometimes unwitting suggestions,
criticisms, insights, reviews, mentoring, and strictly intellectual
contributions.

----------------------------------------------------------------------

QUESTIONS

Why is this README a header file?

    Sometimes it is useful to have whatever source code search
    tools you are using, whether it be cscope or eclipse or
    what not, to find strings even if they are in the README.
    Having it be part of the source base facilitates that.

What is your build target?

    Various releases of Desperado have been built for and tested on
    the following targets (most recent to least recent):

        Linux 2.6.25.10 for the Atmel AT91RM9200-EK (ARM9)
        gcc 4.2.4
        GNU Make 3.81
        uClibc 0.9.29
        ficl4.0.31

        Linux 2.6.22-14 for the i486
        gcc 4.1.3
        GNU Make 3.81
        glibc 2.6.1
        ficl4.0.31

        Linux 2.6.15-1.2054_FC5 for the i486
        gcc 4.1.0
        GNU Make 3.80
        ficl4.0.31
        jdk1.5.0_08
        apache-ant-1.6.5

        Cygwin CYGWIN_NT-5.1 1.5.24 (0.156/4/2) for the i486
        gcc 3.4.4
        GNU Make 3.81
        ficl4.0.31

        Linux 2.4.22-1.2115.nptlsmp for the i386
        gcc 3.3.2
        GNU Make 3.79.1

    One of my goals is to learn about the portability issues of
    porting embedded C++ and C code from target to target. While
    every attempt has been made to make the code in this library
    portable, my experience has been that porting across Linux,
    gcc and stdlib versions is not always trivial undertaking.
    Somewhat remarkably, it seems more labor intensive than it
    was in the pre-Linux era using POSIX-compliant UNIXen and
    ANSI-compliant C compilers across a wide variety of hardware
    targets. Open source definitely presents a fast moving target.
    There is no guarantee that this code is backward compatible
    to prior versions of Linux, gcc, or anything else.

Why didn't you use cppunit for your unit testing?

    You will notice that the unit tests are functions, not main
    programs. I want it to be possible, although perhaps not easy,
    to download the unit tests themselves into an embedded system
    and execute them on the target hardware. (I was specifically
    thinking of the VxWorks shell.) I was not sure that there
    would be sufficient environment in the target hardware to
    support cppunit, which is after all not built around the portable
    Platform layer.  Also, I wanted the unit tests to serve as use
    cases which would be examples of how to use the library. Having
    said that, I love junit and cannot imagine not using it when
    I write Java applications. I've had some experience recently
    with Google Test (gtest), Google's framework for C++ unit testing.
    I recommend it, and will probably start using it for other
    C++ work in the near future.

Is Chip Overclock a real person?

    He is as real as Betty Crocker, Captain Morgan, Aunt Jemima,
    Cap'n Crunch, Uncle Ben, Cracker Jack, and any number of
    folks who proudly put their names on the stuff that they make.
    Chip Overclock is the pen name and alter ego of John Sloan and
    represents an experiment in both product branding and process
    improvement. This is the same Chip Overclock who occasionally
    blogs at http://www.chipoverclock.com and frequently comments
    at http://io9.com .

Why didn't you implement design pattern Foo?

    Maybe I will. Maybe I am not familiar with it. Maybe I never
    found it that useful in my own embedded work. Maybe it's already
    been implemented in some of the common packages like ACE, STL,
    or Boost, whose functionality I try not to overlap. (I've used the
    STL a lot, ACE a little, and haven't yet done much with Boost.)

What does it mean to have inline virtual destructors?

    This bothers me a little bit too. Obviously, the destructors
    have to be virtual if the intent is to allow the class to be
    overridden, and for objects of the derived class to be pointed to
    by base class pointers. But if the destructors are truly empty,
    then it might be possible for a very smart compiler to eliminate
    some of the code involved. Probably not. But I let the compiler
    know that anyway by putting the empty destructors inline. (In
    later versions of this library, I moved all virtual destructors
    outline.)

Shouldn't every class with a virtual destructor have all of the Big Three?

    Where the Big Three are virtual destructor, copy constructor, and
    assignment operator. Maybe. For those classes where I specifically
    want to prohibit copying, I make the copy constructor and assignment
    operator private and leave them unimplemented. I'm nervous about
    either prohibiting all copying, or providing a deep copy for every
    object when in embedded applications that may not be what the developer
    really wants. This is a complicated issue, and it really depends on
    how the application wants to use the component, something I have
    difficulty anticipating except for the use cases I execute in my
    unit tests. For now I'm punting.

Why don't you use configure, autoconf, automake, libtool, etc.?

    That's a good idea. It's on my todo list. Of course, it
    will only help with UNIX-like systems, not with embedded OSes
    like VxWorks, PSOS, C/Executive, uC/COS-II etc. I haven't quite
    figured out how this would work with cross-compilation in
    which the platform on which you run configure is not the
    platform on which you run Desperado, which is a pretty typical
    situation for embedded applications.

Why do I get a lot of warnings about failures to inline when I build?

    It depends on what compiler you are using. For example, gcc
    3.3.4 does a much better job inlining than does gcc 3.3.2,
    or at least if it doesn't, it complains a lot less. You may
    also see warnings about using the wrong printf format. My
    experience in porting this code to various platforms, both
    Linux and non-Linux, has been that it is impossible to get
    this consistently and portably correct.

Aren't the reinitializeobject.h macros really a bad idea?

    Yes. It's the one experiment that I consider a failure.
    I've replaced their use with the initialize() methods,
    but those have the drawback that they absolutely must be
    implemented in every derived class if they are to be used
    at all. Alternatives like placing the constructor code in a
    separate virtual function, or having an initializer whose code
    is completely distinct from that of the constructor, have their
    own drawbacks.

The EC++ specification doesn't allow templates, why do you?

    I think that templates, properly used, are a safer
    alternative to using new/delete to implement type-safe
    variable length objects. At least with the GNU C++
    compiler, templates to not inevitably lead to code bloat.
    Besides, much of what EC++, a C++ subset for embedded
    applications, disallows, it does so because the features
    were considered too new. EC++ reflects that state of C++
    compilers in Japan when the specification was written
    circa 1999. On the other hand, I also prefer not to use
    real-time type identification (RTTI), or at least find it
    usually unnecessary, so I agree with EC++ on that one.
    Templates are in fact necessary when using the STL, and
    although in some embedded applications I avoid the STL
    for good reasons, in others a good STL implementation is
    the greatest thing since sliced bread.

C++ exceptions can be enabled or disabled in Desperado, why?

    C++ exception handling has proven to be problematic in my
    experience for lots of reasons. Tom Cargill cogently
    argues that it is not well understood how to write reliable
    code using exceptions, and I agree. I think that it is
    very hard to predict how long exception handlers will take
    to execute. In C++, particularly in embedded applications,
    I prefer not to use them, but recognize that they may have
    their place, particularly to indicate constructor failure.
    And when I write Java, I cannot avoid using exceptions.

What's the deal with the licenses?

    The licensing of this library is based mostly on my
    experience dealing with corporate intellectual property
    lawyers. It is my goal to not place undue restrictions on
    how Desperado may be used while at the same time protecting
    everyone's (including my own) intellectual property rights.
    I find that companies frequently "pre-approve" the LGPL for
    C and C++ code, and the Apache License for Java code. Not
    conforming to one of these two models makes life painful for
    all involved. I used a modified version of the LGPL at some
    risk because the dynamic versus static linking licensing issues
    are real ones for embedded systems developers.

----------------------------------------------------------------------

PHILOSOPHY

"Elegance is not optional." -- Richard O'Keefe

"When I am working on a problem I never think about beauty. I only
think about how to solve the problem. But when I have finished,
if the solution is not beautiful, I know it is wrong."
-- Buckminster Fuller

"Good design is clear thinking made visible." -- Edward Tufte

"A couple of months in the laboratory can save you a couple of
hours in the library" -- Westheimer's Discovery

----------------------------------------------------------------------

$Name:  $

$Id: README.h,v 1.44 2007/01/29 15:48:22 jsloan Exp $

*******************************************************************************/

/**
 *  @file
 *
 *  This is the README for this project.
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.44 $
 *
 *  @date   $Date: 2007/01/29 15:48:22 $
 */

#endif
