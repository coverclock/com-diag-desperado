/* vim: set ts=4 expandtab shiftwidth=4: */

/******************************************************************************

    Copyright 2005-2011 Digital Aggregates Corporation, Colorado, USA.
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

    $Id: FiclMachine.cpp,v 1.8 2006/08/07 20:44:29 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the FiclMachine class.
 *
 *  @see    FiclMachine
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.8 $
 *
 *  @date   $Date: 2006/08/07 20:44:29 $
 */


#if defined(DESPERADO_HAS_FICL)


#include <new>
#include <cstdlib>
#include "com/diag/desperado/target.h"
#include "com/diag/desperado/FiclMachine.h"
#include "com/diag/desperado/Print.h"
#include "com/diag/desperado/Platform.h"
#include "com/diag/desperado/Dump.h"


#include "com/diag/desperado/Begin.h"


//
//  Return a pointer to the FiclMachine in whose context the Ficl VM
//  is executing. To do this, we have get the FiclSystem object, then
//  step through all of its FiclMachines looking for the one associated
//  with the VM. This is somewhat complicated by the fact that while
//  Link is a base class to both FiclSystem and FiclMachine, it is not
//  virtual, while the two derived classes are.
//
FiclMachine* FiclMachine::findFiclMachine(ficlVm* pVM) {
    FiclMachine* pm = 0;
    if (pVM != 0) {
        FiclSystem* ps = FiclSystem::findFiclSystem(pVM);
        if (ps != 0) {
            Link* psl = ps;
            Link* pml = psl->getNext();
            while (pml != psl) {
                void* pp = pml->getPayload();
                if (pp != 0) {
                    FiclMachine* pmt = reinterpret_cast<FiclMachine*>(pp);
                    ficlVm* pnm = pmt->getNativeMachine();
                    if (pnm == pVM) {
                        pm = pmt;
                        break;
                    }
                }
                pml = pml->getNext();
            }
        }
    }
    return pm;
}


//
//  Constructor.
//
FiclMachine::FiclMachine(FiclSystem* s) :
    Link(this),
    system(s),
    ficlmachine(0)
{
    if (0 != this->system) {
        this->insert(this->system);
    }
}


//
//  Constructor.
//
FiclMachine::FiclMachine(FiclSystem& s) :
    Link(this),
    system(&s),
    ficlmachine(0)
{
    this->insert(this->system);
}


//
//  Destructor.
//
FiclMachine::~FiclMachine() {
    if (this->ficlmachine != 0) {
        ficlSystemDestroyVm(this->ficlmachine);
    }
}


//
//    Initializer.
//
bool FiclMachine::initialize(FiclSystem* s) {
    bool rc = false;
    try {
        this->FiclMachine::~FiclMachine();
        new(this) FiclMachine(s);
        rc = true;
    } catch (...) {
        rc = false;
    }
    return rc;
}


//
//    Initializer.
//
bool FiclMachine::initialize(FiclSystem& s) {
    bool rc = false;
    try {
        this->FiclMachine::~FiclMachine();
        new(this) FiclMachine(s);
        rc = true;
    } catch (...) {
        rc = false;
    }
    return rc;
}


//
//  Push a cell onto the stack.
//
void FiclMachine::push(ficlCell cell) {
    (*this)();
    ficlStackPush(this->ficlmachine->dataStack, cell);
}


//
//  Pop a cell from the stack.
//
ficlCell FiclMachine::pop() {
    (*this)();
    return ficlStackPop(this->ficlmachine->dataStack);
}


//
//  Force lazy intitialization to complete.
//
int FiclMachine::operator() () {

    if (0 == this->ficlmachine) {
        this->ficlmachine = this->system->factory();
    }

    return 0;
}


//
//  Do a batch interpretation.
//
int FiclMachine::operator() (Input& input) {
    char buffer[this->maximum_buffer_size + 1];
    size_t ii;
    int rc;
    int ch;

    (*this)();

    do {
        ii = 0;
        ch = input();
        while ((EOF != ch) && (sizeof(buffer) > ii)) {
            buffer[ii++] = ch;
            if ('\n' == ch) {
                break;
            }
            ch = input();
        }
        buffer[ii++] = '\0';
        (Platform::instance().output())(buffer);
        rc = ficlVmEvaluate(this->ficlmachine, buffer);
    } while ((FICL_VM_STATUS_USER_EXIT != rc) && (EOF != ch));

    return rc;
}


//
//  Do an interactive interpretation.
//
int FiclMachine::operator() (Input& input, const char* prompt) {
    char buffer[this->maximum_buffer_size + 1];
    size_t ii;
    int rc;
    int ch;

    (*this)();

    do {
        (Platform::instance().output())(prompt);
        ii = 0;
        ch = input();
        while ((EOF != ch) && (sizeof(buffer) > ii)) {
            buffer[ii++] = ch;
            if ('\n' == ch) {
                break;
            }
            ch = input();
        }
        buffer[ii++] = '\0';
        rc = ficlVmEvaluate(this->ficlmachine, buffer);
    } while ((FICL_VM_STATUS_USER_EXIT != rc) && (EOF != ch));

    return rc;
}


//
//  Do a command line interface interpretation.
//
int FiclMachine::operator() (char* text) {

    (*this)();

    return ficlVmEvaluate(this->ficlmachine, text);
}


//
//  Show this object on the output object.
//
void FiclMachine::show(int level, Output* display, int indent) const {
    Platform& pl = Platform::instance();
    Print printf(display);
    Dump dump(display);
    const char* sp = printf.output().indentation(indent);
    char component[sizeof(__FILE__)];
    printf("%s%s(%p)[%lu]:\n",
        sp, pl.component(__FILE__, component, sizeof(component)),
        this, sizeof(*this));
    this->Link::show(level, display, indent + 1);
    printf("%s system=%p\n", sp, this->system);
    if (this->system) {
        this->system->show(level, display, indent + 2);
    }
    printf("%s ficlmachine=%p\n", sp, this->ficlmachine);
    if (this->ficlmachine) {
        dump.words(this->ficlmachine, sizeof(ficlVm), false, 0, indent + 2);
    }
}


#include "com/diag/desperado/End.h"


#endif
