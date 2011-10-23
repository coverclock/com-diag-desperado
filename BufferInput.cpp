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

    $Id: BufferInput.cpp,v 1.6 2006/02/07 00:07:02 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the BufferInput class.
 *
 *  @see    BufferInput
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.6 $
 *
 *  @date   $Date: 2006/02/07 00:07:02 $
 */


#include <new>
#include "com/diag/desperado/errno.h"
#include "com/diag/desperado/target.h"
#include "com/diag/desperado/string.h"
#include "com/diag/desperado/generics.h"
#include "com/diag/desperado/BufferInput.h"
#include "com/diag/desperado/Print.h"
#include "com/diag/desperado/Platform.h"


#include "com/diag/desperado/Begin.h"


//
//  Constructor. The string is assumed to be NUL terminated.
//
BufferInput::BufferInput(char* sp) :
    Input(),
    string(sp),
    size((0 != sp) ? std::strlen(sp) + 1 : 0),
    offset(0)
{
}


//
//  Constructor. The string has a specified size.
//
BufferInput::BufferInput(char* sp, size_t sz) :
    Input(),
    string(sp),
    size((0 != sp) ? sz : 0),
    offset(0)
{
}


//
//  Destructor.
//
BufferInput::~BufferInput() {
}


//
//    Initializer.
//
bool BufferInput::initialize(char* sp) {
    bool rc = false;
    try {
        this->BufferInput::~BufferInput();
        new(this) BufferInput(sp);
        rc = true;
    } catch (...) {
        rc = false;
    }
    return rc;
}


//
//    Initializer.
//
bool BufferInput::initialize(char* sp, size_t sz) {
    bool rc = false;
    try {
        this->BufferInput::~BufferInput();
        new(this) BufferInput(sp, sz);
        rc = true;
    } catch (...) {
        rc = false;
    }
    return rc;
}


//
//  Return the next character in the string.
//
int BufferInput::operator() () {
    int rc = EOF;
    if (0 == this->string) {
        errno = EINVAL;
    } else if (this->offset >= this->size) {
        errno = 0;
    } else if ('\0' == this->string[this->offset]) {
        errno = 0;
    } else {
        rc = this->string[this->offset++];
        rc = rc & unsignedintmaxof(char);
    }
    return rc;
}


//
//  Push a character back into the string up to the limit of the
//  beginning of the string.
//
int BufferInput::operator() (int ch) {
    int rc = EOF;
    if (0 == this->string) {
        errno = EINVAL;
    } else if (0 == this->offset) {
        errno = 0;
    } else {
        rc = this->string[--this->offset] = ch;
    }
    return rc;
}


//
//  Read a line from the string.
//
ssize_t BufferInput::operator() (char* buffer, size_t size) {
    ssize_t rc = EOF;
    if (0 == this->string) {
        errno = EINVAL;
    } else if (0 == size) {
        rc = 0;
    } else if (this->offset >= this->size) {
        errno = 0;
    } else if ('\0' == this->string[this->offset]) {
        errno = 0;
    } else {
        char ch;
        rc = 0;
        while (static_cast<ssize_t>(--size) > rc) {
            ch = this->string[this->offset];
            if ('\0' == ch) {
                break;
            }
            ++this->offset;
            buffer[rc++] = ch;
            if ('\n' == ch) {
                break;
            }
        }
        buffer[rc++] = '\0';
    }
    return rc;
}


//
//  Read binary data from the string.
//
ssize_t BufferInput::operator() (
    void* buffer,
    size_t /* minimum */,
    size_t maximum
) {
    ssize_t rc = EOF;
    if (0 == this->string) {
        errno = EINVAL;
    } else if (this->offset >= this->size) {
        errno = 0;
    } else if (0 == maximum) {
        rc = 0;
    } else {
        size_t have = this->size - this->offset;
        if (have < maximum) {
            maximum = have;
        }
        memcpy(buffer, &(this->string[this->offset]), maximum);
        this->offset += maximum;
        rc = maximum;
    }
    return rc;
}


//
//  Show this object on the output object.
//
void BufferInput::show(int level, Output* display, int indent) const {
    Platform& pl = Platform::instance();
    Print printf(display);
    const char* sp = printf.output().indentation(indent);
    char component[sizeof(__FILE__)];
    printf("%s%s(%p)[%lu]:\n",
        sp, pl.component(__FILE__, component, sizeof(component)),
        this, sizeof(*this));
    this->Input::show(level, display, indent + 1);
    printf("%s string=%p\n", sp, this->string);
    printf("%s size=%lu\n", sp, this->size);
    printf("%s offset=%lu\n", sp, this->offset);
}


#include "com/diag/desperado/End.h"
