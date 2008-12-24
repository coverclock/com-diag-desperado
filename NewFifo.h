#ifndef _COM_DIAG_DESPERADO_NEWFIFO_H_
#define _COM_DIAG_DESPERADO_NEWFIFO_H_

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

    $Id: NewFifo.h,v 1.22 2006/05/01 19:20:36 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Declares the NewFifo class.
 *
 *  @see    NewFifo
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.22 $
 *
 *  @date   $Date: 2006/05/01 19:20:36 $
 */


#include <new>
#include "Fifo.h"
#include "exceptions.h"


/**
 *  Implements a Fifo object in which the queue is dynamically allocated.
 *
 *  @see    Fifo
 *
 *  @author coverclock@diag.com (Chip Overclock)
 */
template <typename _TYPE_>
class NewFifo : public Fifo<_TYPE_> {

public:

    /**
     *  Constructor.
     *
     *  @param  cof         is the countof of the queue to be allocated
     *                      in number of objects of the specified type.
     *                      The actual queue size will be the smallest
     *                      power of two greater than or equal to this
     *                      value.
     */
    explicit NewFifo(size_t cof = 0);

    /**
     *  Destructor.
     */
    virtual ~NewFifo();

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
     *  @param  cof         is the countof of the queue to be allocated
     *                      in number of objects of the specified type.
     *                      The actual queue size will be the smallest
     *                      power of two greater than or equal to this
     *                      value.
     *
     *  @return true if successful, false otherwise.
     */
    virtual bool initialize(size_t cof = 0);

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
     *  Computes the smallest power of two greater than or equal to
     *  its argument.
     *
     *  @param  cof     is the minimum size of of the queue specified
     *                  by the application.
     *
     *  @return the actual size of the queue which is at least as big
     *          as that specified by the application.
     */
    static size_t power(size_t cof);

};


//
//  Compute the actual queue size.
//
template <typename _TYPE_>
size_t NewFifo<_TYPE_>::power(size_t cof) {
    size_t bit = 0;
    if (0 < cof) {
        for (bit = 1; (0 < bit) && (bit < cof); bit<<=1) {
            ;
        }
    }
    return bit;
}


//
// Constructor
//
template <typename _TYPE_>
NewFifo<_TYPE_>::NewFifo(size_t cof) :
    Fifo<_TYPE_>(
        (0 < NewFifo<_TYPE_>::power(cof))
            ? new _TYPE_[NewFifo<_TYPE_>::power(cof)]
            : 0,
        NewFifo<_TYPE_>::power(cof)
    )
{
}


//
//  Destructor.
//
template <typename _TYPE_>
NewFifo<_TYPE_>::~NewFifo() {
    delete [] this->queue;
}


//
//    Initializer.
//
template <typename _TYPE_>
bool NewFifo<_TYPE_>::initialize(size_t cof) {
    bool rc = false;
    try {
        this->NewFifo<_TYPE_>::~NewFifo();
        new(this) NewFifo<_TYPE_>(cof);
        rc = true;
    } catch (...) {
        rc = false;
    }
    return rc;
}


//
//  Show this object on the output object.
//
template <typename _TYPE_>
void NewFifo<_TYPE_>::show(int level, Output* display, int indent) const {
    Platform& pl = Platform::instance();
    Print printf(display);
    const char* sp = printf.output().indentation(indent);
    char component[sizeof(__FILE__)];
    printf("%s%s(%p)[%lu]:\n",
        sp, pl.component(__FILE__, component, sizeof(component)),
        this, sizeof(*this));
    this->Fifo<_TYPE_>::show(level, display, indent + 1);
}


#endif
