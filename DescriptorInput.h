#ifndef _COM_DIAG_DESPERADO_DESCRIPTORINPUT_H_
#define _COM_DIAG_DESPERADO_DESCRIPTORINPUT_H_

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

    $Id: DescriptorInput.h,v 1.8 2006/08/04 20:42:46 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Declares the DescriptorInput class.
 *
 *  @see    DescriptorInput
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.8 $
 *
 *  @date   $Date: 2006/08/04 20:42:46 $
 */


#include "Input.h"
#include "Output.h"


/**
 *  Implements an input functor that returns data from a file
 *  descriptor, the default descriptor being 0 for standard input.
 *
 *  @author coverclock@diag.com (Chip Overclock)
 */
class DescriptorInput : public Input {

public:

    /**
     *  Constructor.
     *
     *  @param  fd      is a file descriptor. If no file descriptor is
     *                  specified, the standard input file descriptor
     *                  is used.
     */
    explicit DescriptorInput(int fd = 0);

    /**
     *  Destructor. The file descriptor is not automatically closed upon
     *  destruction.
     */
    virtual ~DescriptorInput();

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
     *  @param  fd      is a file descriptor. If no file descriptor is
     *                  specified, the standard input file descriptor
     *                  is used.
     *
     *  @return true if successful, false otherwise.
     */
    virtual bool initialize(int fd = 0);

    /**
     *  Returns the associated file descriptor.
     *
     *  @return the associated file descriptor.
     */
    int getDescriptor() const;

    /**
     *  Returns the next unsigned character in the file, or EOF if
     *  End Of File has been reached.
     *
     *  @return an unsigned character as an integer if successful,
     *          EOF otherwise.
     */
    virtual int operator() ();

    /**
     *  Pushes an ASCII unsigned character (but not EOF) in an integer
     *  back to the object to be returned on the next call to the
     *  input character functor.
     *
     *  @param  ch      is the character to return to the string.
     *
     *  @return the character if successful, EOF otherwise.
     */
    virtual int operator() (int ch);

    /**
     *  Inputs a newline or NUL terminated line from the file descriptor
     *  into the buffer of the specified size. If a newline is read, it is
     *  input into the buffer. Guarantees that the buffer is NUL terminated
     *  if it is at least one octet in size. Guarantees that no more
     *  than the specified number of octets are returned.
     *
     *  @param  buffer  points to the buffer.
     *
     *  @param  size    is the size of the buffer in octets. Size
     *                  should be no larger than the largest possible
     *                  signed integer.
     *
     *  @return the number of octets output (which may be zero),
     *          including the NUL, if successful, EOF otherwise.
     */
    virtual ssize_t operator() (char* buffer, size_t size);

    /**
     *  Inputs binary data into a buffer from a file descriptor. At least
     *  the minimum number of octets are input unless EOF or error occurs.
     *  Up to the maximum number may be input if it can be done without
     *  further blocking. The functor does not NUL terminate the buffer.
     *
     *  @param  buffer  points to the buffer.
     *
     *  @param  minimum is the minimum number of octets to input.
     *
     *  @param  maximum is the maximum number of octets to input.
     *
     *  @return the number of octets input (which may be any number less
     *          than maximum including zero) if successful, EOF otherwise.
     */
    virtual ssize_t operator() (
        void* buffer,
        size_t minimum,
        size_t maximum
    );

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
     *  This is the file descriptor.
     */
    int descriptor;

    /**
     *  This is the same as the file descriptor until EOF has
     *  been reached.
     */
    int active;

    /**
     *  This is the character pushed back into the descriptor.
     */
    int saved;

};


//
//  Return the associated file descriptor.
//
inline int DescriptorInput::getDescriptor() const {
    return this->descriptor;
}


#endif
