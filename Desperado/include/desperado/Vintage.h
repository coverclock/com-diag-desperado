#ifndef _COM_DIAG_DESPERADO_VINTAGE_H_
#define _COM_DIAG_DESPERADO_VINTAGE_H_

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

    $Id: Vintage.h,v 1.25 2006/02/07 00:07:03 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Declares the Vintage class.
 *
 *  @see    Vintage
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.25 $
 *
 *  @date   $Date: 2006/02/07 00:07:03 $
 */


#include "desperado/Object.h"
#include "desperado/Output.h"


#include "desperado/Begin.h"

/**
 *  Contains static variables with control information about
 *  this product. The base class contains information about
 *  the Desperado library itself. A derived class may
 *  contain information about an application using the library.
 *
 *  @author coverclock@diag.com (Chip Overclock)
 */
class Vintage : public Object {

public:

    /**
     *  This NUL-terminated string contains the product name.
     */
    static const char product[];

    /**
     *  This NUL-terminated string contains the license terms.
     */
    static const char license[];

    /**
     *  This NUL-terminated string contains the copyright notice.
     */
    static const char copyright[];

    /**
     *  This NUL-terminated string contains the contact information.
     */
    static const char contact[];

    /**
     *  This NUL-terminated string contains the URL information.
     */
    static const char url[];

    /**
     *  This NUL-terminated string contains the URI information.
     */
    static const char uri[];

    /**
     *  This NUL-terminated string contains the release name.
     */
    static const char release[];

    /**
     *  This NUL-terminated string contains the release date.
     */
    static const char date[];

    /**
     *  This NUL-terminated string contains the build date and time.
     */
    static const char build[];

    /**
     *  Constructor.
     */
    explicit Vintage();

    /**
     *  Destructor.
     */
    virtual ~Vintage();

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
     *  @return true if successful, false otherwise.
     */
    virtual bool initialize();

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

};


//
// Constructor
//
inline Vintage::Vintage() {
}

#include "desperado/End.h"


#if defined(DESPERADO_HAS_UNITTESTS)
#include "desperado/cxxcapi.h"
/**
 *  Run the Vintage unit test.
 *  
 *  @return the number of errors detected by the unit test.
 */
CXXCAPI int unittestVintage(void);
#endif


#endif