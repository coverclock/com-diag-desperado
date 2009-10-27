#ifndef _COM_DIAG_DESPERADO_INPUT_H_
#define _COM_DIAG_DESPERADO_INPUT_H_

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

    $Id: Input.h,v 1.26 2006/02/07 00:07:03 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Declares the Input class.
 *
 *  @see    Input
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.26 $
 *
 *  @date   $Date: 2006/02/07 00:07:03 $
 */


#if defined(__cplusplus)


#include "Object.h"
#include "Output.h"


#include "Begin.h"

/**
 *  Defines the interface to an input functor, an object, called
 *  like a function, which returns data from some data source.
 *  This input functor always consumes all data, like /dev/null.
 *
 *  If included from a C translation unit, defines a C-callable API.
 *
 *  @author coverclock@diag.com (Chip Overclock)
 */
class Input : public Object {

public:

    /**
     *  Constructor.
     */
    explicit Input();

    /**
     *  Destructor.
     */
    virtual ~Input();

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
     *  Returns the next character.
     *
     *  @return a character in an integer if successful, EOF otherwise.
     */
    virtual int operator() ();

    /**
     *  Pushes an character in an integer back to the input to be
     *  returned on the next call to the input character functor.
     *  Only one pushed back character is guaranteed to succeed in
     *  between input character operations. The character
     *  pushed back does not have to be the previous character input,
     *  or even any character that was ever input, although at least
     *  one character must have been previously input.
     *
     *  @param  ch      is the character to push back into the input.
     *
     *  @return the pushed back character is successful, EOF otherwise.
     */
    virtual int operator() (int ch);

    /**
     *  Inputs a newline or NUL terminated line into the buffer of
     *  the specified size. If a newline is encountered, it is input
     *  into the buffer. Guarantees that the buffer is NUL terminated
     *  if it is at least one octet in size. Guarantees that no more
     *  than the specified number of octets are returned.
     *
     *  @param  buffer  points to the buffer.
     *
     *  @param  size    is the size of the buffer in octets. Size
     *                  should be no larger than the largest possible
     *                  signed integer.
     *
     *  @return the number of octets input (which may be zero)
     *          including the terminating NUL, if successful, EOF
     *          otherwise.
     */
    virtual ssize_t operator() (char* buffer, size_t size);

    /**
     *  Inputs binary data into a buffer. The intent is that the
     *  operation blocks until the minimum number of requested octets
     *  are input or EOF or an error occurs. If more octets are available
     *  without blocking, up to the maximum number of requested octets
     *  are input. Specific implementations may differ. The interface
     *  only guarantees that no more than the maximum number of octets
     *  a input into the buffer. The functor does not NUL terminate the buffer.
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

};

#include "End.h"


/**
 *  Run the Input/Output Static unit test.
 *  
 *  @return the number of errors detected by the unit test.
 */
extern "C" int unittestInputOutputStatic();


/**
 *  Run the Input/Output unit test.
 *
 *  @param  pVM             points to the Ficl VM in whose context this
 *                          function is being executed if being run from a Ficl
 *                          shell, null otherwise.
 *
 *  @param  mechanism       indicates which input/output mechanism to use.
 *
 *  @param  inputp          points to the input functor to use.
 *
 *  @param  outputp         points to the output functor to use.
 *  
 *  @return the number of errors detected by the unit test.
 */
extern "C" int unittestInputOutput(
    void* pVM,
    char mechanism,
    Input* inputp,
    Output* outputp
);


#else


/**
 *  This is an opaque type used to refer to a C++ input object
 *  in a C program.
 */
typedef struct Input Input;


#endif


#endif
