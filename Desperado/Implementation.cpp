/* vim: set ts=4 expandtab shiftwidth=4: */

/******************************************************************************

    Copyright 2005-2011 Digital Aggregates Corporation, Colorado, USA.
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

    $Id: Implementation.cpp,v 1.9 2006/08/11 03:37:03 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the Implementation class.
 *
 *  @see    Implementation
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.9 $
 *
 *  @date   $Date: 2006/08/11 03:37:03 $
 */


#include <new>
#include "com/diag/desperado/stdio.h"
#include "com/diag/desperado/Implementation.h"
#include "com/diag/desperado/Platform.h"
#include "com/diag/desperado/Print.h"


#include "com/diag/desperado/Begin.h"


//
// Constructor
//
Implementation::Implementation() :
    Abstract(),
    field(this)
{
#if defined(DESPERADO_HAS_DEBUGGING)
    fprintf(stderr, "Implementation(%p)::Implementation()\n", this);
#endif
}


//
// Constructor
//
Implementation::Implementation(void* f) :
    Abstract(),
    field(f)
{
#if defined(DESPERADO_HAS_DEBUGGING)
    fprintf(stderr, "Implementation(%p)::Implementation(%p)\n", this, f);
#endif
}


//
//  Destructor.
//
Implementation::~Implementation() {
#if defined(DESPERADO_HAS_DEBUGGING)
    fprintf(stderr, "Implementation(%p)::~Implementation()\n", this);
#endif
    if (this->field) {
        this->field = 0;
    }
}


//
//  Copy constructor.
//
Implementation::Implementation(const Implementation& that) :
    Abstract(that)
{
#if defined(DESPERADO_HAS_DEBUGGING)
    fprintf(stderr, "Implementation(%p)::Implementation(%p)\n", this, &that);
#endif
    this->field = that.field;
}


//
//  Assignment operator.
//
Implementation& Implementation::operator=(const Implementation& that) {
#if defined(DESPERADO_HAS_DEBUGGING)
    fprintf(stderr, "Implementation(%p)::operator=(%p)\n", this, &that);
#endif
    if (&that != this) {
        this->Abstract::operator=(that);
        this->field = that.field;
    }
    return *this;
}


//
//  Show this object on the output object.
//
void Implementation::show(int /* level */, Output* display, int indent) const {
    Platform& pl = Platform::instance();
    Print printf(display);
    const char* sp = printf.output().indentation(indent);
    char component[sizeof(__FILE__)];
    printf("%s%s(%p)[%lu]\n",
        sp, pl.component(__FILE__, component, sizeof(component)),
        this, sizeof(*this));
    printf("%s field=%p\n", sp, this->field);
}


#include "com/diag/desperado/End.h"
