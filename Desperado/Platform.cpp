/* vim: set ts=4 expandtab shiftwidth=4: */

/******************************************************************************

    Copyright 2005 Digital Aggregates Corp., Arvada CO 80001-0587, USA.
    This file is part of the Digital Aggregates Desperado library.
    
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
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General
    Public License along with this library; if not, write to the
    Free Software Foundation, Inc., 59 Temple Place, Suite 330,
    Boston, MA 02111-1307 USA, or http://www.gnu.org/copyleft/lesser.txt.

    $Name:  $

    $Id: Platform.cpp,v 1.6 2006/02/07 00:07:03 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the Platform class.
 *
 *  @see    Platform
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.6 $
 *
 *  @date   $Date: 2006/02/07 00:07:03 $
 */


#include <new>
#include <cstdarg>
#include "littleendian.h"
#include "lowtohigh.h"
#include "Platform.h"
#include "Vintage.h"
#include "Ticks.h"
#include "TimeZone.h"
#include "DstNever.h"
#include "LeapSeconds.h"
#include "Constant.h"


//
//  This forces at least one Vintage object to be linked into any
//  application that uses Platform, allowing the ident(1) command
//  to be used against the resulting application.
//
static Vintage vintage;


//
//  This is the default Daylight Saving Time rule.
//
static DstNever dstnever;


//
//  This is the default Leap Seconds rule.
//
static LeapSeconds leapseconds;


//
//  This points to the system platform object. An application may instantiate
//  many platform objects, but there is only one system platform object.
//  Although it is a singleton, it is not lazily constructed. The
//  establishment is the system platform object is a action of system
//  initialization by the application, since it is up to the application
//  and not this class as to what kind of derived object is the system
//  platform.
//
Platform* Platform::singleton = 0;


//
//  Allocate and construct a suitable Platform object and return a
//  pointer to it.
//
Platform* Platform::factory() {
    return platform_factory();
}


//
//  Set the system platform.
//
void Platform::instance(Platform* that) {
    Platform::singleton = that;
}


//
//  Get the system platform. Calling this method before a system
//  platform is set deliberately dereferences a null pointer. Hopefully
//  on most platforms this causes a segmentation violation or some other
//  machine check. On those platforms for which zero is a valid memory
//  location, wackiness ensues.
//
Platform& Platform::instance() {
    return *Platform::singleton;
}


//
//  Constructor.
//
Platform::Platform() :
    leapseconds(false),
    lsrule(&::leapseconds),
    epoch(),
    offset(0L),
    dstrule(&::dstnever)
{
}


//
//  Destructor.
//
Platform::~Platform() {
}


//
//  Return the platform frequency as a whole number.
//
ticks_t Platform::frequency() {
    ticks_t numerator;
    ticks_t denominator;
    this->frequency(numerator, denominator);
    return numerator / denominator;
}


//
//  Show this object on the output object.
//
void Platform::show(int level, Output* display, int indent) const {
    Print printf(display);
    const char* sp = printf.output().indentation(indent);
    char buffer[sizeof(__FILE__)];
    const char* bp = this->component(__FILE__, buffer, sizeof(buffer));
    printf("%s%s(%p)[%lu]:\n", sp, bp, this, sizeof(*this));
    printf("%s singleton=%p\n", sp, this->singleton);
    printf("%s leapseconds=%d\n", sp, this->leapseconds);
    if (lsrule) {
        printf("%s lsrule:\n", sp);
        this->lsrule->show(level, display, indent + 2);
    } else {
        printf("%s lsrule=%p\n", sp, this->lsrule);
    }
    printf("%s epoch:\n", sp);
    this->epoch.show(level, display, indent + 2);
    printf("%s offset=%ld\n", sp, this->offset);
    if (dstrule) {
        printf("%s dstrule:\n", sp);
        this->dstrule->show(level, display, indent + 2);
    } else {
        printf("%s dstrule=%p\n", sp, this->dstrule);
    }
}
