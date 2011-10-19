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

    $Id: NewCounters.cpp,v 1.6 2006/02/07 00:07:03 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the NewCounters class.
 *
 *  @see    NewCounters
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.6 $
 *
 *  @date   $Date: 2006/02/07 00:07:03 $
 */


#include <new>
#include "desperado/target.h"
#include "desperado/NewCounters.h"
#include "desperado/Print.h"
#include "desperado/Platform.h"


#include "desperado/Begin.h"


//
//  Constructor.
//
NewCounters::NewCounters(
    size_t ncounters,
    const char** vlabels
) :
    Counters(
        ncounters,
        (0 == ncounters) ? 0 : new Counter [ncounters],
        vlabels
    )
{
}


//
//  Destructor.
//
NewCounters::~NewCounters() {
    delete [] this->countersv;
}


//
//    Initializer.
//
bool NewCounters::initialize(
    size_t ncounters,
    const char** vlabels
) {
    bool rc = false;
    try {
        this->NewCounters::~NewCounters();
        new(this) NewCounters(ncounters, vlabels);
        rc = true;
    } catch (...) {
        rc = false;
    }
    return rc;
}


//
//  Show this object on the output object.
//
void NewCounters::show(int level, Output* display, int indent) const {
    Platform& pl = Platform::instance();
    Print printf(display);
    const char* sp = printf.output().indentation(indent);

    if (0 == level) {
        char component[sizeof(__FILE__)];
        printf("%s%s(%p)[%lu]:\n",
            sp, pl.component(__FILE__, component, sizeof(component)),
            this, sizeof(*this));
        this->Counters::show(level, display, indent + 1);
        return;
    }

    this->Counters::show(level, display, indent);
}


#include "desperado/End.h"
