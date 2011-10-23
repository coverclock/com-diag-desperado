#ifndef _COM_DIAG_DESPERADO_COUNTERSTYPE_H_
#define _COM_DIAG_DESPERADO_COUNTERSTYPE_H_

/* vim: set ts=4 expandtab shiftwidth=4: */

/******************************************************************************

    Copyright 2006 Digital Aggregates Corp., Arvada CO 80001-0587, USA.
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

    $Id: CountersType.h,v 1.5 2006/02/07 00:07:03 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Declares the CountersType class.
 *
 *  @see    CountersType
 *
 *  @see    Counters
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.5 $
 *
 *  @date   $Date: 2006/02/07 00:07:03 $
 */


#include <new>
#include "com/diag/desperado/Counters.h"
#include "com/diag/desperado/Platform.h"
#include "com/diag/desperado/Output.h"
#include "com/diag/desperado/Print.h"


#include "com/diag/desperado/Begin.h"

/**
 *  This is a template that defines a type of the Counters
 *  class in which the counter array of the specified size
 *  is allocated inside the CountersType object.
 *
 *  @author coverclock@diag.com (Chip Overclock)
 */
template <size_t _NCOUNTERS_>
class CountersType : public Counters {

public:

    /**
     *  Constructor.
     *
     *  @param  vlabels             is an array of labels that correspond
     *                              one-to-one to the counters, for when
     *                              the counters are shown. The array may
     *                              be omitted by passing null, in which case
     *                              labels are not used.
     */
    explicit CountersType(const char** vlabels = 0);

    /**
     *  Destructor.
     */
    virtual ~CountersType();

    /**
     *  Initializes this object, returning it to its just constructed state.
     *  This is exactly equivalent to calling the object's destructor
     *  followed by calling its constructor. The use of this method allows
     *  object (re)construction to be virtualized. However, it has the side
     *  effect of also reinitializing the object's virtual pointer. This means
     *  wackiness will ensue when if, for example, a derived class object
     *  deliberately calls its base class initializer. Doing so turns this
     *  object from an instance of the derived class into an instance of its
     *  base class. This implementation requires that every class derived
     *  from a class that implements this method must also implement this
     *  method, otherwise it can never be used against a derived class object.
     *
     *  @param  vlabels             is an array of labels that correspond
     *                              one-to-one to the counters, for when
     *                              the counters are shown. The array may
     *                              be omitted by passing null, in which case
     *                              labels are not used.
     *
     *  @return true if successful, false otherwise.
     */
    virtual bool initialize(const char** vlabels = 0);

    /**
     *  Displays internal information about this object to the specified
     *  output object. Useful for debugging and troubleshooting.
     *
     *  @param  level   sets the verbosity of the output. What this means
     *                  is object dependent. However, the level is passed
     *                  from outer to inner objects this object calls the
     *                  show methods of its inherited or composited objects.
     *
     *  @param display  points to the output object to which output is
     *                  sent. If null (zero), the default platform output
     *                  object is used as the effective output object. The
     *                  effective output object is passed from outer to
     *                  inner objects as this object calls the show methods
     *                  of its inherited and composited objects.
     *
     *  @param  indent  specifies the level of indentation. One more than
     *                  this value is passed from outer to inner objects
     *                  as this object calls the show methods of its
     *                  inherited and composited objects.
     */
    virtual void show(int level = 0, Output* display = 0, int indent = 0) const;

private:

    /**
     *  This is the counter array for this type of Counters.
     */
    Counter vcounters[_NCOUNTERS_];

};


//
//  Constructor.
//
template <size_t _NCOUNTERS_>
inline CountersType<_NCOUNTERS_>::CountersType(const char** vlabels) :
    Counters(_NCOUNTERS_, this->vcounters, vlabels)
{
}


//
//  Destructor.
//
template <size_t _NCOUNTERS_>
CountersType<_NCOUNTERS_>::~CountersType() {
}


//
//    Initializer.
//
template <size_t _NCOUNTERS_>
bool CountersType<_NCOUNTERS_>::initialize(const char** vlabels) {
    bool rc = false;
    try {
        this->CountersType<_NCOUNTERS_>::~CountersType();
        new(this) CountersType<_NCOUNTERS_>(vlabels);
        rc = true;
    } catch (...) {
        rc = false;
    }
    return rc;
}


//
//  Show this object on the output object.
//
template <size_t _NCOUNTERS_>
void CountersType<_NCOUNTERS_>::show(
    int level,
    Output* display,
    int indent
) const {
    Platform& pl = Platform::instance();
    Print printf(display);
    const char* sp = printf.output().indentation(indent);
    char component[sizeof(__FILE__)];
    printf("%s%s(%p)[%lu]\n",
        sp, pl.component(__FILE__, component, sizeof(component)),
        this, sizeof(*this));
    this->Counters::show(level, display, indent + 1);
}

#include "com/diag/desperado/End.h"


#endif
