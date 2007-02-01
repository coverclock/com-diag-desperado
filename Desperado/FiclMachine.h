#ifndef _DESPERADO_FICLMACHINE_H_
#define _DESPERADO_FICLMACHINE_H_

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

    $Id: FiclMachine.h,v 1.29 2006/02/07 00:07:03 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Declares the FiclMachine class.
 *
 *  @see    FiclMachine
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.29 $
 *
 *  @date   $Date: 2006/02/07 00:07:03 $
 */


#if defined(DESPERADO_HAS_FICL)


extern "C" {
#   include "ficl.h"
}
#include "target.h"
#include "FiclSystem.h"
#include "Output.h"
#include "Input.h"


/**
 *  Implements an adaptor to a Ficl machine, where Ficl (pronounced "fickle")
 *  is a "FORTH-inspired command language" developed by John Sadler,
 *  a FORTH interpreter written in ANSI C and designed to be embedded
 *  in other applications. Its FORTH dialect is compliant with the ANSI
 *  DPANS94 standard. This class supports Ficl 4.0.31 from
 *  <A HREF="http://ficl.sourceforge.net">http://ficl.sourceforge.net</A>.
 *
 *  When an object of the FiclSystem class instantiates,
 *  a new Ficl system is created. The Ficl system is where the Forth
 *  dictionary resides. When an object of the FiclMachine
 *  class instantiates, a new Ficl virtual machine is created. The Ficl
 *  virtual machine is where the Forth parameter and return stacks reside.
 *  Each Ficl virtual machine must be associated with a single Ficl system.
 *  Each Ficl system may have associated with it one or more Ficl virtual
 *  machines. Each Ficl virtual machine associated with the same Ficl system
 *  shares the same dictionary. Each Ficl virtual machine can be instantiated
 *  in a different thread of execution.
 *
 *  Sadler states that running multiple Ficl virtual machines
 *  in a shared-memory multithreaded environment is "not well
 *  tested". Enable the debug print in the Desperado ficlDictionaryLock()
 *  interface function may suggest to you that Ficl might not bracket
 *  its lock and unlock operations correctly.
 *
 *  It can be useful to know all the FiclMachines that are using a
 *  FiclSystem. All such machines are Linked to their FiclSystem, with
 *  the FiclSystem Link as their root. The FiclMachines are unLinked
 *  upon destruction. The payload of each Link points to its FiclSystem
 *  or FiclMachine.
 *
 *  @see    J. Sadler, "Ficl -- an embeddable extension language
 *          interpreter", <I>Dr. Dobb's Journal</I>,
 *          January 1999
 *
 *  @see    J. Sadler, "Ficl - Object Forth Wraps C Structures",
 *          <I>Proc. of the 20th FORML Conference</I>,
 *          November 1998
 *
 *  @see    E. Conklin, E. Rather, <I>Forth Programmer's
 *          Handbook</I>, Forth Inc., 2000
 *
 *  @see    ANSI, <I>American National Standard for Information
 *          Systems Programming Languages - Forth</I>, ANSI
 *          X3.215:1994, 1994
 *
 *  @see    ISO, <I>Information technology - Programming
 *          languages - Forth</I>, ISO/IEC 15145:1997, 1997
 *          (renaming of ANSI X3.215:1994)
 *
 *  @see    FiclSystem
 *
 *  @see    Link
 *
 *  @author coverclock@diag.com (Chip Overclock)
 */
class FiclMachine : public Link {

public:

    /**
     *  Returns a pointer to the FiclMachine object associated with a native
     *  Ficl virtual machine.
     *
     *  @param  pVM         points to a native Ficl VM structure.
     *
     *  @return a pointer to the FiclMachine or null if in error.
     */
    static FiclMachine* findFiclMachine(ficlVm* pVM);

    /**
     *  Constructor.
     *
     *  @param  s               points to the Ficl system object
     *                          with which this Ficl virtual machine
     *                          object is associated.
     */
    explicit FiclMachine(FiclSystem* s = 0);

    /**
     *  Constructor.
     *
     *  @param  s               refers to the Ficl system object
     *                          with which this Ficl virtual machine
     *                          object is associated.
     */
    explicit FiclMachine(FiclSystem& s);

    /**
     *  Destructor.
     */
    virtual ~FiclMachine();

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
     *  @param  s               points to the Ficl system object
     *                          with which this Ficl virtual machine
     *                          object is associated.
     *
     *  @return true if successful, false otherwise.
     */
    virtual bool initialize(FiclSystem* s = 0);

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
     *  @param  s               refers to the Ficl system object
     *                          with which this Ficl virtual machine
     *                          object is associated.
     *
     *  @return true if successful, false otherwise.
     */
    virtual bool initialize(FiclSystem& s);

    /**
     *  Lines input to the virtual machine from an input functor
     *  can be no longer than this many bytes.
     */
    static const size_t maximum_buffer_size = Output::minimum_buffer_size;

    /**
     *  Return a pointer to the FiclSystem object for this object.
     *
     *  @return a pointer to the FiclSystem object, or null if none.
     */
    FiclSystem* getFiclSystem();

    /**
     *  Return a pointer to the underlying ficlSystem of this object.
     *  This pointer is necessary for many of the native ficl functions.
     *
     *  @return a pointer to the underlying ficlSystem, or null if none.
     */
    ficlSystem* getNativeSystem();

    /**
     *  Return a pointer to the underlying ficlVm of this object.
     *  This pointer is necessary for many of the native ficl functions.
     *
     *  @return a pointer to the underlying ficlVm, or null if none.
     */
    ficlVm* getNativeMachine();

    /**
     *  Performs no evaluation but forces the lazy evaluation of the
     *  underlying Ficl system and machine to be performed.
     *
     *  @return the exit code from the virtual machine.
     */
    virtual int operator() ();

    /**
     *  Evaluates a stream of characters from an input functor until
     *  it emits end of file. Characters are read a line at a time,
     *  each line being terminated by an unescaped NL character.
     *
     *  @param  input       refers to an input functor.
     *
     *  @return the exit code from the virtual machine.
     */
    virtual int operator() (Input& input);

    /**
     *  Evaluates a stream of characters from an input functor until
     *  it emits end of file. Characters are read a line at a time,
     *  each line being terminated by an unescaped NL character.
     *  The prompt string is displayed on the platform output device
     *  before each line is read to facilitate interactive input.
     *
     *  @param  input       refers to an input functor.
     *
     *  @param  prompt      points to the prompt string. ("ok> " is
     *                      a typical prompt on many FORTH systems.)
     *
     *  @return the exit code from the virtual machine.
     */
    virtual int operator() (Input& input, const char* prompt);

    /**
     *  Evaluates a single NUL-terminated string.
     *
     *  @param  text        is a NUL-terminated string to be evaluated.
     *                      Note that this string is not const. This is
     *                      an interface requirement of the underlying
     *                      Ficl 4.0.31 interface.
     *
     *  @return the exit code from the virtual machine.
     */
    virtual int operator() (char* text);

    /**
     *  Pushes a cell onto the data stack of this Ficl machine.
     *  This method can be used to pass parameters on the Ficl
     *  data stack to a subsequent evaluation functor call.
     *
     *  @param  cell    is the cell to push onto the stack.
     */
    virtual void push(ficlCell cell);

    /**
     *  Pops a cell from the data stack of this Ficl machine.
     *  This method can be used to retrieve results on the Ficl
     *  data stack from a prior evaluation functor call.
     *
     *  @return the cell popped off the stack.
     */
    virtual ficlCell pop();

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
     *  Copy constructor.
     *
     *  @param  that    refers to an R-value object of this type.
     */
    FiclMachine(const FiclMachine& that);

    /**
     *  Assignment operator.
     *
     *  @param  that    refers to an R-value object of this type.
     */
    FiclMachine& operator=(const FiclMachine& that);

    /**
     *  This points to the Ficl system object used by this object.
     */
    FiclSystem* system;

    /**
     *  This points to the Ficl virtual machine structure for this object.
     */
    ficlVm* ficlmachine;

};


//
//  Return a pointer to the FiclSystem for this FiclMachine, or null if none.
//
inline FiclSystem* FiclMachine::getFiclSystem() {
    return this->system;
}


//
//  Return a pointer to the ficlSystem, or null if none.
//
inline ficlSystem* FiclMachine::getNativeSystem() {
    return this->system ? this->system->getNativeSystem() : 0;
}


//
//  Return a pointer to the ficlMachine, or null if none.
//
inline ficlVm* FiclMachine::getNativeMachine() {
    return this->ficlmachine;
}


#endif


#endif
