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

    $Id: FiclShell.cpp,v 1.3 2006/02/07 00:07:03 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the FiclShell class.
 *
 *  @see    FiclShell
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.3 $
 *
 *  @date   $Date: 2006/02/07 00:07:03 $
 */


#if defined(DESPERADO_HAS_FICL)


#include <new>
#include "desperado/string.h"
#include "desperado/ficlApi.h"
#include "desperado/FiclShell.h"
#include "desperado/BufferInput.h"
#include "desperado/Platform.h"
#include "desperado/Print.h"


#include "desperado/Begin.h"


//
//  Constructor.
//
FiclShell::FiclShell(Output* po, Output* pe) :
    ready(false),
    system(po, pe),
    machine(this->system)
{
}


//
//  Constructor.
//
FiclShell::FiclShell(Output& ro, Output& re) :
    ready(false),
    system(ro, re),
    machine(this->system)
{
}


//
//  Destructor.
//
FiclShell::~FiclShell() {
}


//
//    Initializer.
//
bool FiclShell::initialize(Output* po, Output* pe) {
    bool rc = false;
    try {
        this->FiclShell::~FiclShell();
        new(this) FiclShell(po, pe);
        rc = true;
    } catch (...) {
        rc = false;
    }
    return rc;
}


//
//    Initializer.
//
bool FiclShell::initialize(Output& ro, Output& re) {
    bool rc = false;
    try {
        this->FiclShell::~FiclShell();
        new(this) FiclShell(ro, re);
        rc = true;
    } catch (...) {
        rc = false;
    }
    return rc;
}


//
//  Start the shell using a string.
//
int FiclShell::operator() (char* text) {
    BufferInput input(text);
    return (*this)(input);
}


//
//  Start the shell using an input pointer and a prompt.
//
int FiclShell::operator() (Input* pi, const char* prompt) {
    Input& input = pi ? *pi : Platform::instance().input();
    return (*this)(input, prompt);
}


//
//  Start the shell using an input reference and prompt.
//
int FiclShell::operator() (Input& input, const char* prompt) {

    if (!ready) {

        //  Initialize the underlying Ficl system and machine.

        (this->machine)();

        //  Load the extras into the dictionary.

        this->system.extras();

        //  Load the C symbols into the dictionary.

        desperado_ficl_shell(this->system.getNativeSystem());

        ready = true;
    }

    //  If necessary, generate a prompt based on our host name.

    char hostname[64];
    if (0 == prompt) {
        const char* host = Platform::instance().host();
        strncpy(hostname, host, sizeof(hostname));
        hostname[sizeof(hostname) - sizeof("> ")] = '\0';
        strcat(hostname, "> ");
        prompt = hostname;
    }

    //  Finally, invoke the Ficl machine.

    return (this->machine)(input, prompt);
}


//
//  Show this object on the output object.
//
void FiclShell::show(int level, Output* display, int indent) const {
    Platform& pl = Platform::instance();
    Print printf(display);
    const char* sp = printf.output().indentation(indent);
    char component[sizeof(__FILE__)];
    printf("%s%s(%p)[%lu]:\n",
        sp, pl.component(__FILE__, component, sizeof(component)),
        this, sizeof(*this));
    printf("%s ready=%d\n", sp, this->ready);
    printf("%s system:\n", sp);
    this->system.show(level, display, indent + 2);
    printf("%s machine:\n", sp);
    this->machine.show(level, display, indent + 2);
}


#include "desperado/End.h"


#endif
