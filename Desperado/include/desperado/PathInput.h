#ifndef _COM_DIAG_DESPERADO_PATHINPUT_H_
#define _COM_DIAG_DESPERADO_PATHINPUT_H_

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

    $Id: PathInput.h,v 1.16 2006/02/07 00:07:03 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Declares the PathInput class.
 *
 *  @see    PathInput
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.16 $
 *
 *  @date   $Date: 2006/02/07 00:07:03 $
 */


#include "desperado/FileInput.h"


#include "desperado/Begin.h"

/**
 *  Implements an input functor that returns data from a C standard
 *  I/O library FILE object opened from a given path, the default path
 *  being a special one, "-", that denotes standard input.
 *
 *  @author coverclock@diag.com (Chip Overclock)
 */
class PathInput : public FileInput {

public:

    /**
     *  Constructor. If the path cannot be open and exceptions are
     *  available, an exception will be thrown to indicate constructor
     *  failure. Otherwise the application must use the method
     *  getFile() and check for a null (0) return.
     *
     *  @param  path    is a path string as defined by the POSIX
     *                  fopen() function. If the path
     *                  is "-", standard input will be used.
     *
     *  @param  mode    is a mode string as defined by the POSIX
     *                  fopen() function. This has no
     *                  meaning if "-" is specified for the path.
     */
    explicit PathInput(const char* path = "-", const char* mode = "r");

    /**
     *  Destructor. If standard input was not specified as the path,
     *  the underlying FILE object is closed upon destruction.
     */
    virtual ~PathInput();

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
     *  @param  path    is a path string as defined by the POSIX
     *                  fopen() function. If the path
     *                  is "-", standard input will be used.
     *
     *  @param  mode    is a mode string as defined by the POSIX
     *                  fopen() function. This has no
     *                  meaning if "-" is specified for the path.
     *
     *  @return true if successful, false otherwise.
     */
    virtual bool initialize(const char* path = "-", const char* mode = "r");

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

#include "desperado/End.h"


#endif