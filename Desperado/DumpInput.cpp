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

    $Id: DumpInput.cpp,v 1.5 2006/02/07 00:07:03 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the DumpInput class.
 *
 *  @see    DumpInput
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.5 $
 *
 *  @date   $Date: 2006/02/07 00:07:03 $
 */


#include <new>
#include "desperado/errno.h"
#include "desperado/DumpInput.h"
#include "desperado/Output.h"
#include "desperado/Platform.h"
#include "desperado/Print.h"


#include "desperado/Begin.h"


//
//  Constructor.
//
DumpInput::DumpInput() :
    in(0),
    du(0)
{
}


//
//  Constructor.
//
DumpInput::DumpInput(Input& ri) :
    in(&ri),
    du(0)
{
}


//
//  Constructor.
//
DumpInput::DumpInput(Input& ri, Dump& rd) :
    in(&ri),
    du(&rd)
{
}


//
//  Destructor.
//
DumpInput::~DumpInput() {
}


//
//    Initializer.
//
bool DumpInput::initialize() {
    bool rc = false;
    try {
        this->DumpInput::~DumpInput();
        new(this) DumpInput;
        rc = true;
    } catch (...) {
        rc = false;
    }
    return rc;
}


//
//    Initializer.
//
bool DumpInput::initialize(Input& ri) {
    bool rc = false;
    try {
        this->DumpInput::~DumpInput();
        new(this) DumpInput(ri);
        rc = true;
    } catch (...) {
        rc = false;
    }
    return rc;
}


//
//    Initializer.
//
bool DumpInput::initialize(Input& ri, Dump& rd) {
    bool rc = false;
    try {
        this->DumpInput::~DumpInput();
        new(this) DumpInput(ri, rd);
        rc = true;
    } catch (...) {
        rc = false;
    }
    return rc;
}


//
//  Returns input object.
//
Input& DumpInput::input() const {
    return this->in ? *this->in : Platform::instance().input();
}


//
//  Returns dump object.
//
Dump& DumpInput::dump() const {
    return this->du ? *this->du : Platform::instance().dump();
}


//
//  Dump a character.
//
int DumpInput::operator() () {
    Input& inp = this->input();
    Dump& dmp = this->dump();
    int rc = inp();
    dmp.words(&rc, sizeof(rc));
    return rc;
}


//
//  Push back a character and dump it.
//
int DumpInput::operator() (int ch) {
    Input& inp = this->input();
    Dump& dmp = this->dump();
    int rc = inp(ch);
    dmp.words(&rc, sizeof(rc));
    return rc;
}


//
//  Dump a line of a maximum length.
//
ssize_t DumpInput::operator() (char* buffer, size_t size) {
    Input& inp = this->input();
    Dump& dmp = this->dump();
    ssize_t rc = inp(buffer, size);
    if (0 < rc) {
        dmp.bytes(buffer, rc);
    }
    return rc;
}


//
//  Dump binary data.
//
ssize_t DumpInput::operator() (
    void* buffer,
    size_t minimum,
    size_t maximum
) {
    Input& inp = this->input();
    Dump& dmp = this->dump();
    ssize_t rc = inp(buffer, minimum, maximum);
    if (0 < rc) {
        dmp.words(buffer, rc);
    }
    return rc;
}


//
//  Show this object on the output object.
//
void DumpInput::show(int level, Output* display, int indent) const {
    Platform& pl = Platform::instance();
    Print printf(display);
    const char* sp = printf.output().indentation(indent);
    char component[sizeof(__FILE__)];
    printf("%s%s(%p)[%lu]:\n",
        sp, pl.component(__FILE__, component, sizeof(component)),
        this, sizeof(*this));
    this->Input::show(level, display, indent + 1);
    printf("%s in=%p\n", sp, this->in);
    if (this->in) {
        this->in->show(level, display, indent + 2);
    }
    printf("%s du=%p\n", sp, this->du);
    if (this->du) {
        this->du->show(level, display, indent + 2);
    }
}


#include "desperado/End.h"
