#ifndef _COM_DIAG_DESPERADO_FICLSHELL_H_
#define _COM_DIAG_DESPERADO_FICLSHELL_H_

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

    $Id: FiclShell.h,v 1.5 2006/02/07 00:07:03 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Declares the FiclShell class.
 *
 *  @see    FiclShell
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.5 $
 *
 *  @date   $Date: 2006/02/07 00:07:03 $
 */


#if defined(DESPERADO_HAS_FICL)


#include "com/diag/desperado/Object.h"
#include "com/diag/desperado/FiclSystem.h"
#include "com/diag/desperado/FiclMachine.h"
#include "com/diag/desperado/Output.h"


#include "com/diag/desperado/Begin.h"

/**
 *  Creates a Ficl-based command line shell which can manipulate
 *  C-accessible integer variables and invoke C-callable functions
 *  which take zero to ten integer arguments and return an integer
 *  value. An integral Ficl machine is created and started. The machine
 *  runs in the thread from which it is called. An integral Ficl system
 *  is used to support the shell. This means shells do not share
 *  dictionaries.
 *
 *  @author coverclock@diag.com (Chip Overclock)
 */
class FiclShell : public Object {

public:

    /**
     *  Constructor.
     *
     *  @param  po          points to the output functor used by
     *                      Ficl machines that are part of this system.
     *                      If null, the Platform output functor is used.
     *
     *
     *  @param  pe          points to the error output functor used by
     *                      Ficl machines that are part of this system.
     *                      If null, the Platform error output functor is used.
     */
    explicit FiclShell(Output* po = 0, Output* pe = 0);

    /**
     *  Constructor.
     *
     *  @param  ro          refers to the output functor used by
     *                      Ficl machines that are part of this system.
     *
     *
     *  @param  re          refers to the error output functor used by
     *                      Ficl machines that are part of this system.
     */
    explicit FiclShell(Output& ro, Output& re);

    /**
     *  Destructor. Destroying an object of this type does not
     *  automatically destroy any virtual machine objects associated
     *  with it.
     */
    virtual ~FiclShell();

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
     *  @param  po          points to the output functor used by
     *                      Ficl machines that are part of this system.
     *                      If null, the Platform output functor is used.
     *
     *
     *  @param  pe          points to the error output functor used by
     *                      Ficl machines that are part of this system.
     *                      If null, the Platform error output functor is used.
     *
     *  @return true if successful, false otherwise.
     */
    virtual bool initialize(Output* po = 0, Output* pe = 0);

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
     *  @param  ro          refers to the output functor used by
     *                      Ficl machines that are part of this system.
     *
     *
     *  @param  re          refers to the error output functor used by
     *                      Ficl machines that are part of this system.
     *
     *  @return true if successful, false otherwise.
     */
    virtual bool initialize(Output& ro, Output& re);

    /**
     *  Return a pointer to the FiclSystem object for this object.
     *  This is not a pointer to a constant object. Hence the FiclSystem
     *  can be modified before the shell is started.
     *
     *  @return a pointer to the FiclSystem object, or null if none.
     */
    FiclSystem* getFiclSystem();

    /**
     *  Return a pointer to the FiclMachine object for this object.
     *  This is not a pointer to a constant object. Hence the FiclMachine
     *  can be modified before the shell is started.
     *
     *  @return a pointer to the FiclMachine object, or null if none.
     */
    FiclMachine* getFiclMachine();

    /**
     *  Start the Ficl shell. If this is the first time the shell
     *  has been started, the Ficl system is initialized with the
     *  default dictionary size, stack sizes, and environment size.
     *  This method returns when the Ficl machine exits.
     *
     *  @param  pi      points to the input functor from which the
     *                  shell will take its input. If null, the
     *                  Platform input functor is used.
     *
     *  @param  prompt  points to the prompt string. ("ok> " is
     *                  a typical prompt on many FORTH systems.)
     *                  This replaces the default prompt, which
     *                  uses the hostname of the underlying platform.
     *
     *  @return the exit code from the Ficl machine.
     */
    virtual int operator() (Input* pi = 0, const char* prompt = 0);

    /**
     *  Start the Ficl shell. If this is the first time the shell
     *  has been started, the Ficl system is initialized with the
     *  default dictionary size, stack sizes, and environment size.
     *  This method returns when the Ficl machine exits.
     *
     *  @param  ri      refers to the input functor from which the
     *                  shell will take its input.
     *
     *  @param  prompt  points to the prompt string. ("ok> " is
     *                  a typical prompt on many FORTH systems.)
     *                  This replaces the default prompt, which
     *                  uses the hostname of the underlying platform.
     *
     *  @return the exit code from the Ficl machine.
     */
    virtual int operator() (Input& ri, const char* prompt = 0);

    /**
     *  Evaluates a single NUL-terminated string.
     *
     *  @param  text        is a NUL-terminated string to be evaluated.
     *                      Note that this string is not const. This is
     *                      an interface requirement of the underlying
     *                      Ficl 4.0.31 interface.
     *
     *  @return the exit code from the Ficl machine.
     */
    virtual int operator() (char* text);

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
    FiclShell(const FiclShell& that);

    /**
     *  Assignment operator.
     *
     *  @param  that    refers to an R-value object of this type.
     */
    FiclShell& operator=(const FiclShell& that);

    /**
     *  This class performs lazy initialization, performing it just before
     *  the object is first used. This is so that static objects of this
     *  type can be allocated before the underlying platform has initialized.
     *  This field indicates whether the initialization has been performed
     *  (true) or not (false).
     */
    bool ready;

    /**
     *  This is the FiclSystem that supports the shell. Although
     *  it is declared private, it can be accessed via the accessor
     *  method. Multiple shells do not share systems, hence they do
     *  not share dictionaries.
     */
    FiclSystem system;

    /**
     *  This is the FiclMachine that supports the shell. Although
     *  it is declared private, it can be accessed via the accessor
     *  method. Multiple shells do not share machines, hence they do
     *  not share stacks.
     */
    FiclMachine machine;

};


//
//  Return a pointer to the FiclSystem for this shell.
//
inline FiclSystem* FiclShell::getFiclSystem() {
    return &(this->system);
}


//
//  Return a pointer to the FiclMachine for this shell.
//
inline FiclMachine* FiclShell::getFiclMachine() {
    return &(this->machine);
}

#include "com/diag/desperado/End.h"


#if defined(DESPERADO_HAS_UNITTESTS)
#include "com/diag/desperado/cxxcapi.h"
/**
 *  Run the FiclShell unit test.
 *
 *  @param  pVM             points to the Ficl VM in whose context this
 *                          function is being executed if being run from a Ficl
 *                          shell, null otherwise.
 *
 *  @param  interactive     if non-zero causes the test to run interactively,
 *                          taking input from the platform input functor.
 *  
 *  @return the number of errors detected by the unit test.
 */
CXXCAPI int unittestFiclShell(void* pVM, int interactive);
#endif


#endif


#endif
