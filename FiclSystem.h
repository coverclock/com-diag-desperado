#ifndef _COM_DIAG_DESPERADO_FICLSYSTEM_H_
#define _COM_DIAG_DESPERADO_FICLSYSTEM_H_

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

    $Id: FiclSystem.h,v 1.30 2006/08/09 03:26:05 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Declares the FiclSystem class.
 *
 *  @see    FiclSystem
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.30 $
 *
 *  @date   $Date: 2006/08/09 03:26:05 $
 */


#if defined(DESPERADO_HAS_FICL)


extern "C" {
#   include "ficl.h"
}
#include "cxxcapi.h"
#include "Platform.h"
#include "Link.h"
#include "Heap.h"
#include "Mutex.h"
#include "Output.h"


#include "Begin.h"

/**
 *  Implements an adaptor to a Ficl system, where Ficl (pronounced "fickle")
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
 *  @see    FiclMachine
 *
 *  @see    Link
 *
 *  @author coverclock@diag.com (Chip Overclock)
 */
class FiclSystem : public Link {

public:

    /**
     *  Returns a pointer to the FiclSystem object associated with a native
     *  Ficl virtual machine.
     *
     *  @param  pVM         points to a native Ficl VM structure.
     *
     *  @return a pointer to the FiclSystem or null if in error.
     */
    static FiclSystem* findFiclSystem(ficlVm* pVM);

    /**
     *  Returns a reference to a heap object. It is static because
     *  the Ficl memory functions are not passed a context from which
     *  their system or machine can be inferred. Hence, all Ficl systems
     *  and machines use the same heap object.
     *
     *  @return a reference to a heap object.
     */
    static Heap& heap();

    /**
     *  Sets the heap used by all Ficl systems and machines. If no
     *  heap is set, the default Platform heap is used.
     *
     *  @param  ph          points to the heap to use. A null pointer
     *                      causes subsequent applications to use the
     *                      default platform heap object.
     */
    static void heap(Heap* ph);

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
    explicit FiclSystem(Output* po = 0, Output* pe = 0);

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
    explicit FiclSystem(Output& ro, Output& re);

    /**
     *  Destructor. Destroying an object of this type does not
     *  automatically destroy any virtual machine objects associated
     *  with it.
     */
    virtual ~FiclSystem();

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
     *  Causes the so-called "extra" Ficl words to be compiled into
     *  the dictionary. These optional primitive words are distributed
     *  with Ficl and add capabilities like loading a Ficl program from
     *  a file into the current dictionary using standard ANSI stdio system
     *  calls.
     *
     *  @param  need        if true cause the extras to be compiled in.
     *                      If false, the extras are not compiled in but
     *                      as a side effect the underlying Ficl system
     *                      is initialized using the current
     *                      ficlSystemInformation structure instead of
     *                      waiting for the first Ficl machine evaluation
     *                      to lazily occur.
     */
    virtual void extras(bool need = true);

    /**
     *  Returns a pointer to the underlying ficlSystem of this object.
     *  This pointer is necessary for many of the native ficl functions.
     *
     *  @return a pointer to the underlying ficlSystem, or null of none.
     */
    ficlSystem* getNativeSystem() const;

    /**
     *  Returns a reference to the ficlSystemInformation structure currently
     *  in use. This structure contains pointers to the I/O routines
     *  used by each Ficl machine supported by this system, and
     *  memory parameters used to allocate dictionaries and stacks when
     *  the Ficl system initializes. The returned reference is not
     *  constant, and can be altered by the application. All Ficl system
     *  and Ficl machine initialization is lazy: the Ficl system is not
     *  initialized until its first Ficl machine is created, and the Ficl
     *  machine is not created until the first FiclMachine evaluation
     *  functor is called. Hence, the system information structure can
     *  be modified after an object of this type is constructed but before
     *  it is used.
     *
     *  @return a reference to the ficlSystemInformation structure in use.
     */
    ficlSystemInformation& getNativeInformation();

    /**
     *  Returns a reference to an output functor.
     *
     *  @return a reference to an output functor.
     */
    virtual Output& output() const;

    /**
     *  Changes the output functor used by this Ficl system. If a
     *  null pointer is used, the Ficl system will use the default
     *  Platform output functor.
     *
     *  @param  po      points to an output functor or null.
     */
    virtual void output(Output* po);

    /**
     *  Changes the output functor used by this Ficl system.
     *
     *  @param  ro      refers to an output functor.
     */
    virtual void output(Output& ro);

    /**
     *  Returns a reference to an error output functor.
     *
     *  @return a reference to an error output functor.
     */
    virtual Output& error() const;

    /**
     *  Changes the error output functor used by this Ficl system. If a
     *  null pointer is used, the Ficl system will use the default
     *  Platform error output functor.
     *
     *  @param  pe      points to an output functor or null.
     */
    virtual void error(Output* pe);

    /**
     *  Changes the error output functor used by this Ficl system.
     *
     *  @param  re      refers to an output functor or null.
     */
    virtual void error(Output& re);

    /**
     *  Creates a new Ficl virtual machine. If this is the first
     *  machine created for this system, this system is initialized
     *  with the current ficlSystemInformation structure.
     *
     *  @return a pointer to the new Ficl virtual machine.
     */
    virtual ficlVm* factory();

    /**
     *  Locks the mutex associated with this object.
     *
     *  @return true if successful, false otherwise.
     */
    bool lock();

    /**
     *  Unlocks the mutex associated with this object.
     *
     *  @return true if successful, false otherwise.
     */
    bool unlock();

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
    FiclSystem(const FiclSystem& that);

    /**
     *  Assignment operator.
     *
     *  @param  that    refers to an R-value object of this type.
     */
    FiclSystem& operator=(const FiclSystem& that);

    /**
     *  This points to the heap used by all Ficl systems and machines.
     */
    static Heap* ficlheap;

    /**
     *  This points to the Ficl system structure for this object.
     */
    ficlSystem* ficlsystem;

    /**
     *  This structure determines the parameters used by the native
     *  Ficl system when it initializes.
     */
    ficlSystemInformation information;

    /**
     *  Points to an output functor.
     */
    Output* ou;

    /**
     *  Points to an error output functor.
     */
    Output* er;

    /**
     *  This is the mutex used to lock the dictionary for this object.
     */
    Mutex mutex;

};


//
//  Return a pointer to the ficlSystem, or null if none.
//
inline ficlSystem* FiclSystem::getNativeSystem() const {
    return this->ficlsystem;
}


//
//  Get the current ficlSystemInformation structure.
//
inline ficlSystemInformation& FiclSystem::getNativeInformation() {
    return this->information;
}


//
//  Lock the mutex associated with this object.
//
inline bool FiclSystem::lock() {
    return this->mutex.begin();
}


//
//  Unlock the mutex associated with this object.
//
inline bool FiclSystem::unlock() {
    return this->mutex.end();
}

#include "End.h"


/**
 *  Run the Ficl unit test.
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
extern "C" int unittestFicl(void* pVM, int interactive);


#endif


#endif
