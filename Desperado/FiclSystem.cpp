/* vim: set ts=4 expandtab shiftwidth=4: */

/******************************************************************************

    Copyright 2005 Digital Aggregates Corp., Arvada CO 80001-0587, USA.
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

    $Id: FiclSystem.cpp,v 1.10 2006/08/19 21:20:17 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the FiclSystem class.
 *
 *  @see    FiclSystem
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.10 $
 *
 *  @date   $Date: 2006/08/19 21:20:17 $
 */


#if defined(DESPERADO_HAS_FICL)


#include <new>
#include <cstdlib>
#include "ficldesperado.h"
#include "target.h"
#include "cxxcapi.h"
#include "generics.h"
#include "FiclSystem.h"
#include "Platform.h"
#include "Print.h"
#include "Dump.h"


//
//  C-callable adaptor between Ficl and the platform output device.
//
CXXCAPI void desperadoCallbackDefaultTextOut(
    ficlCallback*,
    char* text
) {
    Output& out = Platform::instance().output();
#if defined(DESPERADO_HAS_DEBUGGING)
    out("ficlCallbackDefaultTextOut: ");
#endif
    out(text);
}


//
//  C-callable adaptor between Ficl and the platform output device.
//
CXXCAPI void desperadoCallbackTextOut(
    ficlCallback* callback,
    char* text
) {
    FiclSystem* obj = reinterpret_cast<FiclSystem*>(callback->context);
    Output& out = obj->output();
#if defined(DESPERADO_HAS_DEBUGGING)
    out("ficlCallbackDesperadoTextOut: ");
#endif
    out(text);
}


//
//  C-callable adaptor between Ficl and the platform error device.
//
CXXCAPI void desperadoCallbackErrorOut(
    ficlCallback* callback,
    char* text
) {
    FiclSystem* obj = reinterpret_cast<FiclSystem*>(callback->context);
    Output& err = obj->error();
#if defined(DESPERADO_HAS_DEBUGGING)
    err("ficlCallbackDesperadoErrorOut: ");
#endif
    err(text);
}


//
//  C-callable adaptor between Ficl and heap memory allocate.
//
//  Because Ficl doesn't pass a pointer to a callback, virtual machine,
//  dictionary, context, etc. to this function, there is no way to relate
//  it back to anything.
//
CXXCAPI void* desperadoMalloc(
    size_t size
) {
#if defined(DESPERADO_HAS_DEBUGGING)
    Output& err = Platform::instance().error();
    Print errorf(err);
    errorf("ficlDesperadoMalloc(%lu)\n", size);
#endif
    return FiclSystem::heap().malloc(size);
}


//
//  C-callable adaptor between Ficl and heap memory free.
//
//  Because Ficl doesn't pass a pointer to a callback, virtual machine,
//  dictionary, context, etc. to this function, there is no way to relate
//  it back to anything.
//
CXXCAPI void desperadoFree(
    void* p
) {
#if defined(DESPERADO_HAS_DEBUGGING)
    Output& err = Platform::instance().error();
    Print errorf(err);
    errorf("ficlDesperadoFree(%p)\n", p);
#endif
    FiclSystem::heap().free(p);
}


//
//  C-callable adaptor between Ficl and heap memory reallocate.
//
//  Because Ficl doesn't pass a pointer to a callback, virtual machine,
//  dictionary, context, etc. to this function, there is no way to relate
//  it back to anything.
//
CXXCAPI void* desperadoRealloc(
    void* p,
    size_t size
) {
#if defined(DESPERADO_HAS_DEBUGGING)
    Output& err = Platform::instance().error();
    Print errorf(err);
    errorf("ficlDesperadoRealloc(%p,%lu)\n", p, size);
#endif
    return FiclSystem::heap().realloc(p, size);
}


//
//  C-callable adaptor between Ficl and the mutex.
//
//  Enabling the debug print will quickly suggest that Ficl
//  does not bracket its lock and unlock operations correctly.
//  A glance at the 4.0.31 source code will suggest that perhaps
//  ficlDictionaryLookup() locks the dictionary upon exit when
//  it should probably be unlocking it.
//
CXXCAPI int desperadoDictionaryLock(
    ficlDictionary* dictionary,
    short lockIncrement
) {
    ficlSystem* s = dictionary->system;
    FiclSystem* o = reinterpret_cast<FiclSystem*>(s->callback.context);
#if defined(DESPERADO_HAS_DEBUGGING)
    Print printf;
    printf("ficlDictionaryLock(%p,%d)\n", dictionary, lockIncrement);
#endif
    bool rc = (FICL_FALSE != lockIncrement) ? o->lock() : o->unlock();
    return rc ? 0 : -1;
}


Heap* FiclSystem::ficlheap = 0;


//
//  Return a pointer to the FiclSystem in whose context the Ficl VM
//  is executing.
//
FiclSystem* FiclSystem::findFiclSystem(ficlVm* pVM) {
    FiclSystem* ps = 0;
    if (pVM != 0) {
        ps = reinterpret_cast<FiclSystem*>(pVM->callback.context);
    }
    return ps;
}


//
//  Return a reference to a heap object.
//
Heap& FiclSystem::heap() {
    return FiclSystem::ficlheap ?
        *FiclSystem::ficlheap :
        Platform::instance().heap();
}


//
//  Set the pointer to the heap object.
//
void FiclSystem::heap(Heap* ph) {
    FiclSystem::ficlheap = ph;
}


//
//  Constructor.
//
FiclSystem::FiclSystem(Output* po, Output* pe) :
    Link(this),
    ficlsystem(0),
    ou(po),
    er(pe),
    mutex()
{
    ficlSystemInformationInitialize(&(this->information));
    this->information.context = this;
    this->information.textOut = desperadoCallbackTextOut;
    this->information.errorOut = desperadoCallbackErrorOut;
    setFiclCallbackDefaultTextOutPointer(desperadoCallbackDefaultTextOut);
    setFiclMallocPointer(desperadoMalloc);
    setFiclFreePointer(desperadoFree);
    setFiclReallocPointer(desperadoRealloc);
    setFiclDictionaryLockPointer(desperadoDictionaryLock);
}


//
//  Constructor.
//
FiclSystem::FiclSystem(Output& ro, Output& re) :
    Link(this),
    ficlsystem(0),
    ou(&ro),
    er(&re),
    mutex()
{
    ficlSystemInformationInitialize(&(this->information));
    this->information.context = this;
    this->information.textOut = desperadoCallbackTextOut;
    this->information.errorOut = desperadoCallbackErrorOut;
    setFiclCallbackDefaultTextOutPointer(desperadoCallbackDefaultTextOut);
    setFiclMallocPointer(desperadoMalloc);
    setFiclFreePointer(desperadoFree);
    setFiclReallocPointer(desperadoRealloc);
    setFiclDictionaryLockPointer(desperadoDictionaryLock);
}


//
//  Destructor.
//
FiclSystem::~FiclSystem() {
    if (this->ficlsystem != 0) {
        ficlSystemDestroy(this->ficlsystem);
    }
}


//
//    Initializer.
//
bool FiclSystem::initialize(Output* po, Output* pe) {
    bool rc = false;
    try {
        this->FiclSystem::~FiclSystem();
        new(this) FiclSystem(po, pe);
        rc = true;
    } catch (...) {
        rc = false;
    }
    return rc;
}


//
//    Initializer.
//
bool FiclSystem::initialize(Output& ro, Output& re) {
    bool rc = false;
    try {
        this->FiclSystem::~FiclSystem();
        new(this) FiclSystem(ro, re);
        rc = true;
    } catch (...) {
        rc = false;
    }
    return rc;
}


//
//  Return a reference to an output functor.
//
Output& FiclSystem::output() const {
    return this->ou ? *this->ou : Platform::instance().output();
}


//
//  Change an output functor.
//
void FiclSystem::output(Output* po) {
    this->ou = po;
}


//
//  Change an output functor.
//
void FiclSystem::output(Output& ro) {
    this->ou = &ro;
}


//
//  Return a reference to an error output functor.
//
Output& FiclSystem::error() const {
    return this->er ? *this->er : Platform::instance().error();
}


//
// Change an error output functor.
//
void FiclSystem::error(Output* pe) {
    this->er = pe;
}


//
// Change an error output functor.
//
void FiclSystem::error(Output& re) {
    this->er = &re;
}


//
//  Compile in the extras.
//
void FiclSystem::extras(bool need) {

    if (0 == this->ficlsystem) {
        this->ficlsystem = ficlSystemCreate(&(this->information));
    }

    if (need) {
        ficlSystemCompileExtras(this->ficlsystem);
    }
}


//
//  Ficl VM factory. We defer initializing the Ficl system
//  until the first time we create a Ficl Virtual Machine
//  so that we can create empty static FiclSystem and FiclMachine
//  objects without require a Platform, which provides the Heap
//  used by Ficl.
//
ficlVm* FiclSystem::factory() {

    if (0 == this->ficlsystem) {
        this->ficlsystem = ficlSystemCreate(&(this->information));
    }

    return ficlSystemCreateVm(this->ficlsystem);
}


//
//  Show this object on the output object.
//
void FiclSystem::show(int level, Output* display, int indent) const {
    Platform& pl = Platform::instance();
    Print printf(display);
    Dump dump(display);
    const char* sp = printf.output().indentation(indent);
    char component[sizeof(__FILE__)];
    printf("%s%s(%p)[%lu]:\n",
        sp, pl.component(__FILE__, component, sizeof(component)),
        this, sizeof(*this));
    this->Link::show(level, display, indent + 1);
    printf("%s ficlsystem=%p\n", sp, this->ficlsystem);
    if (this->ficlsystem) {
        dump.words(this->ficlsystem, sizeof(ficlSystem), false, 0, indent + 2);
    }
    printf("%s information:\n", sp);
    dump.words(&(this->information), sizeof(this->information), false, 0,
        indent + 2);
    printf("%s ou=%p\n", sp, this->ou);
    if (this->ou) {
        this->ou->show(level, display, indent + 2);
    }
    printf("%s er=%p\n", sp, this->er);
    if (this->er) {
        this->er->show(level, display, indent + 2);
    }
    printf("%s mutex:\n", sp);
    this->mutex.show(level, display, indent + 2);
}


#endif
