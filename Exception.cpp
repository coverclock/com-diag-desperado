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

    $Id: Exception.cpp,v 1.5 2006/05/01 19:30:53 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the Exception class.
 *
 *  @see    Exception
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.5 $
 *
 *  @date   $Date: 2006/05/01 19:30:53 $
 */


#include <new>
#include "desperado/errno.h"
#include "desperado/string.h"
#include "desperado/Exception.h"
#include "desperado/Output.h"
#include "desperado/Print.h"
#include "desperado/Platform.h"


#include "desperado/Begin.h"


//
//  Constructor.
//
Exception::Exception(
    const char* eventMessage,
    int errorNumber,
    const char* fileName,
    int lineNumber,
    const char* functionName
) THROWS(()) :
    event(eventMessage),
    error((0 <= errorNumber) ? errorNumber : errno),
    file(fileName),
    line(lineNumber),
    function(functionName)
{
}


//
//  Destructor.
//
Exception::~Exception() THROWS(()) {
}


//
//    Initializer.
//
bool Exception::initialize(
    const char* eventMessage,
    int errorNumber,
    const char* fileName,
    int lineNumber,
    const char* functionName
) THROWS(()) {
    bool rc = false;
    try {
        this->Exception::~Exception();
        new(this) Exception(eventMessage, errorNumber, fileName, lineNumber,
                                functionName);
        rc = true;
    } catch (...) {
        rc = false;
    }
    return rc;
}


//
//  Return the event string.
//
const char* Exception::what() const THROWS(()) {
    return this->event ? this->event : "";
}


//
//  Show this object on the output object.
//
void Exception::show(int /* level */, Output* display, int indent) const {
    Platform& pl = Platform::instance();
    Print printf(display);
    const char* sp = printf.output().indentation(indent);
    char component[sizeof(__FILE__)];
    printf("%s%s(%p)[%lu]:\n",
        sp, pl.component(__FILE__, component, sizeof(component)),
        this, sizeof(*this));
    if (this->event) {
        printf("%s event=\"%s\"\n", sp, this->event);
    }
    if (0 < this->error) {
        const char* string = std::strerror(this->error);
        printf("%s error=%d=\"%s\"\n", sp, this->error, string);
    }
    if (this->file) {
        printf("%s file=\"%s\"\n", sp, this->file);
    }
    if (0  < this->line) {
        printf("%s line=%d\n", sp, this->line);
    }
    if (this->function) {
        printf("%s function=\"%s\"\n", sp, this->function);
    }
}


#include "desperado/End.h"
