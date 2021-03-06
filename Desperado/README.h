#ifndef _COM_DIAG_DESPERADO_README_H_
#define _COM_DIAG_DESPERADO_README_H_

/* vim: set ts=4 expandtab shiftwidth=4: */

/*******************************************************************************

Copyright 2005-2014 Digital Aggregates Corporation, Colorado, USA.

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

This file is part of the Digital Aggregates Corporation Desperado package.
Desperado is an open source library of object-oriented software components
written in C++. It implements design patterns that the author has found to be
both useful and common in embedded applications. The most useful portions
of Desperado have been forked into another project called Desperadito with a
much simpler build framework. Desperadito also includes a partial fork of the
Hayloft project. All that Desperadito lacks is the Java and FORTH related
interface classes from Desperado. It is likely that that is the project you
really want to use. Never the less, portions of Desperado (mostly prior to the
Desperadito fork) have legitimately found their way into the commercial products
of some of the Corporation's clients, so don't be surprised if you see this
code elsewhere in your travels.

Desperado is licensed under a modified GNU Lesser General Public License to
allow it to be incorporated into proprietary software or firmware without
restriction or viral licensing implication.

Desperado requires

o   ANSI C++ and ANSI C99-compilant compilers,
o   a POSIX-compliant operating system and run-time library, including
o   POSIX threads, and
o   support for 64-bit integral types.

Contact:

	Chip Overclock
	Digital Aggregates Corporation
	3440 Youngfield Street, #209
	Wheat Ridge CO 80033 USA
	http://www.diag.com
	mailto:coverclock@diag.com

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

ACKNOWLEDGEMENTS

This software is an original work of its author(s).

Portions of this software make use of freely available software that may be
copyrighted by the following people and organizations:

    Michael Barr
    Netrino, LLC
    Annapolis MD USA

    John Sadler

    Ross Williams
    Rocksoft Pty. Ltd.
    Adelaide SA AUS

The author(s) would like to thank these people and organizations for
making their software available.

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



*******************************************************************************/

/**
 *  @file
 *
 *  This is the README for this project.
 *
 *  @author Chip Overclock (coverclock@diag.com)
 *
 *
 */

#endif
