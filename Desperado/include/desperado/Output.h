#ifndef _COM_DIAG_DESPERADO_OUTPUT_H_
#define _COM_DIAG_DESPERADO_OUTPUT_H_

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

    $Id: Output.h,v 1.30 2006/02/07 00:07:03 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Declares the Output class.
 *
 *  @see    Output
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.30 $
 *
 *  @date   $Date: 2006/02/07 00:07:03 $
 */


#include "desperado/target.h"
#include "desperado/cxxcapi.h"
#include "desperado/stdarg.h"


#if defined(__cplusplus)


#include "desperado/Object.h"


#include "desperado/Begin.h"

/**
 *  Defines the interface to an output functor, an object, called
 *  like a function, which writes data to some data sink. This
 *  output functor always consume all data, like /dev/null.
 *
 *  If included from a C translation unit, defines a C-callable API.
 *
 *  @author coverclock@diag.com (Chip Overclock)
 */
class Output : public Object {

public:

    /**
     *  This is the longest NUL terminated string that can be output
     *  by the functor. The type of this constant is size_t, which is
     *  unsigned, but its value is the maximum possible value of
     *  ssize_t, which is signed. This is so that the output functors
     *  can use a negative ssize_t value to indicate failure.
     */
    static const size_t maximum_string_length =
        (~(static_cast<size_t>(1) << ((sizeof(ssize_t) * 8) - 1)));

    /**
     *  Any implementation of the formatted output functor below
     *  must guarantee that is can output a formatted buffer of
     *  at least this many characters.
     */
    static const size_t minimum_buffer_size = 256;

    /**
     *  This is the maximum number of spaces that can be returned
     *  by the indentation method.
     */
    static const size_t maximum_spaces = 64;

    /**
     *  Constructor.
     */
    explicit Output();

    /**
     *  Destructor.
     */
    virtual ~Output();

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
     *  This is an array of spaces plus a terminating NUL.
     */
    static const char spaces[maximum_spaces + 1];

    /**
     *  Returns a pointer to a NUL-terminated character string
     *  containing the specified number of spaces or the maximum
     *  possible number of spaces, which ever is less.
     *
     *  @param  indent      specifies the number of spaces. Zero
     *                      is a valid value.
     *
     *  @return a NUL-terminated character string.
     */
    const char* indentation(int indent) const;

    /**
     *  Outputs a character in integer form.
     *
     *  @param  c           is a character in integer form.
     *
     *  @return the output character if successful, EOF otherwise.
     */
    virtual int operator() (int c);

    /**
     *  Outputs a string of no more than the specified length not
     *  including its terminating NUL.
     *
     *  @param  s           points to a constant NUL-terminated string.
     *
     *  @param  size        is the size of the string in octets.
     *
     *  @return the number of octets output if successful (which
     *          may be zero), EOF otherwise.
     */
    virtual ssize_t operator() (
        const char* s,
        size_t size =  maximum_string_length
    );

    /**
     *  Format a variable length argument list and output the result.
     *
     *  @param  format      is a NUL-terminated string containing a
     *                      printf-style format statement.
     *
     *  @param  ap          is a variable length argument object.
     *
     *  @return a non-negative number if successful, EOF otherwise.
     */
    virtual ssize_t operator() (const char* format, va_list ap);

    /**
     *  Outputs binary data from a buffer. The intent is that the
     *  operation blocks until the minimum number of requested octets
     *  are output or EOF or an error occurs. If more space is available
     *  without blocking, up to the maximum number of requested octets
     *  may be output. Specific implementations may differ. The interface
     *  only guarantees that at least the minimum number of octets are
     *  output from the buffer.
     *
     *  @param  buffer  points to the buffer.
     *
     *  @param  minimum is the minimum number of octets to output.
     *
     *  @param  maximum is the maximum number of octets to output.
     *
     *  @return the number of octets output (which may be any number less
     *          than maximum including zero) if successful, EOF otherwise.
     */
    virtual ssize_t operator() (
        const void* buffer,
        size_t minimum,
        size_t maximum
    );

    /**
     *  Flush any buffered data to the file. Specific implementations
     *  may do nothing if they do not buffer.
     *
     *  @return a non-negative number if successful, EOF otherwise.
     */
    virtual int operator() ();

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


#else


/**
 *  This is an opaque type used to refer to a C++ output object
 *  in a C program.
 */
typedef struct Output Output;


#endif


#include "desperado/Desperado.h"


/**
 *  Outputs a character in integer form.
 *
 *  @param  o           points to an output object, for example,
 *                      the platform output object.
 *
 *  @param  c           is a character in integer form.
 *
 *  @return the output character if successful, EOF otherwise.
 */
CXXCAPI ssize_t output_c(Output* o, int c);


/**
 *  Outputs a character string not including its terminating NUL.
 *
 *  @param  o           points to an output object, for example,
 *                      the platform output object.
 *
 *  @param  s           points to a constant NUL-terminated string.
 *
 *  @return a non-negative number if successful, EOF otherwise.
 */
CXXCAPI ssize_t output_s(Output* o, const char* s);


/**
 *  Outputs a string of no more than the specified length not
 *  including its terminating NUL.
 *
 *  @param  o           points to an output object, for example,
 *                      the platform output object.
 *
 *  @param  s           points to a constant NUL-terminated string.
 *
 *  @param  size        is the size of the string in octets.
 *                      Size should be no larger than the
 *                      largest possible signed integer.
 *
 *  @return the number of octets output if successful (which
 *          may be zero), EOF otherwise.
 */
CXXCAPI ssize_t output_n(Output* o, const char* s, size_t size);


/**
 *  Format a variable length argument list and output the result.
 *
 *  @param  o           points to an output object, for example,
 *                      the platform output object.
 *
 *  @param  format      is a NUL-terminated string containing a
 *                      printf-style format statement.
 *
 *  @param  ap          is a variable length argument object.
 *
 *  @return a non-negative number if successful, EOF otherwise.
 */
CXXCAPI ssize_t output_v(Output* o, const char* format, va_list ap);


/**
 *  Outputs binary data from a buffer. The intent is that the
 *  operation blocks until the minimum number of requested octets
 *  are output or EOF or an error occurs. If more space is available
 *  without blocking, up to the maximum number of requested octets
 *  may be output. Specific implementations may differ. The interface
 *  only guarantees that at least the minimum number of octets are
 *  output from the buffer.
 *
 *  @param  o           points to an output object, for example,
 *                      the platform output object.
 *
 *  @param  buffer  points to the buffer.
 *
 *  @param  minimum is the minimum number of octets to output.
 *
 *  @param  maximum is the maximum number of octets to output.
 *
 *  @return the number of octets output (which may be any number less
 *          than maximum including zero) if successful, EOF otherwise.
 */
CXXCAPI ssize_t output_b(
    Output* o,
    const void* buffer,
    size_t minimum,
    size_t maximum
);


/**
 *  Flush any buffered data to the file. Specific implementations
 *  may do nothing if they do not buffer.
 *
 *  @param  o           points to an output object, for example,
 *                      the platform output object.
 *
 *  @return a non-negative number if successful, EOF otherwise.
 */
CXXCAPI int output_flush(Output* o);


#if !defined(EOF)
/**
 *  @def    EOF
 *
 *  Generates the value returned by the input and output functors (and
 *  by the standard I/O library) to indicate end of file or error.
 */
#define EOF (-1)
#endif


#endif