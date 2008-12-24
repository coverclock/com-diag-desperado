#ifndef _COM_DIAG_DESPERADO_DUMPOUTPUT_H_
#define _COM_DIAG_DESPERADO_DUMPOUTPUT_H_

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

    $Id: DumpOutput.h,v 1.21 2006/02/07 00:07:03 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Declares the DumpOutput class.
 *
 *  @see    DumpOutput
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.21 $
 *
 *  @date   $Date: 2006/02/07 00:07:03 $
 */


#include "Output.h"
#include "Dump.h"


/**
 *  Implements an output functor that uses Dump to display its output stream
 *  before passing it along to another output functor.
 *
 *  @author coverclock@diag.com (Chip Overclock)
 */
class DumpOutput : public Output {

public:

    /**
     *  Constructor. Data is dumped to the system dump object then
     *  sent to the system output object.
     */
    explicit DumpOutput();

    /**
     *  Constructor. Data is dumped to the system dump object then
     *  sent to the specified output functor.
     *
     *  @param  ro      refers to an output functor.
     */
    explicit DumpOutput(Output& ro);

    /**
     *  Constructor. Data is dumped to the specified dump object then
     *  sent to the specified output functor.
     *
     *  @param  ro      refers to an output functor.
     *
     *  @param  rd      refers to a dump object.
     */
    explicit DumpOutput(Output& ro, Dump& rd);

    /**
     *  Destructor.
     */
    virtual ~DumpOutput();

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
     *  @param  ro      refers to an output functor.
     *
     *  @return true if successful, false otherwise.
     */
    virtual bool initialize(Output& ro);

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
     *  @param  ro      refers to an output functor.
     *
     *  @param  rd      refers to a dump object.
     *
     *  @return true if successful, false otherwise.
     */
    virtual bool initialize(Output& ro, Dump& rd);

    /**
     *  Returns a reference to the output object.
     *
     *  @return a reference to the output object.
     */
    virtual Output& output() const;

    /**
     *  Returns a reference to the dump object.
     *
     *  @return a reference to the dump object.
     */
    virtual Dump& dump() const;

    /**
     *  Dumps a character in integer form.
     *
     *  @param  c           is a character in integer form.
     *
     *  @return the output character if successful, EOF otherwise.
     */
    virtual int operator() (int c);

    /**
     *  Dumps a string of no more than the specified length not
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
        size_t size = maximum_string_length
    );

    /**
     *  Format a variable length argument list and dump the result.
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
     *  Dumps binary data from a buffer. The intent is that the
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

private:

    /**
     *  Points to the output functor used to output the data after
     *  dumping it.
     */
    Output* ou;

    /**
     *  Points to the dump object used to dump the output data.
     */
    Dump* du;

};


#endif
