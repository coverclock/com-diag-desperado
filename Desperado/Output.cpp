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



******************************************************************************/


/**
 *  @file
 *
 *  Implements the Output class.
 *
 *  @see    Output
 *
 *  @author Chip Overclock (coverclock@diag.com)
 *
 *
 */


#include "com/diag/desperado/stdio.h"
#include "com/diag/desperado/Output.h"
#include "com/diag/desperado/string.h"
#include "com/diag/desperado/Platform.h"
#include "com/diag/desperado/Print.h"


#include "com/diag/desperado/Begin.h"


const char Output::spaces[65] = "                                "
                                "                                ";


//
//  Constructor.
//
Output::Output() {
}


//
//  Destructor.
//
Output::~Output() {
}


//
//  Return a NUL-terminated character string of blanks.
//
const char* Output::indentation(int indent) const {
    const int maximum = sizeof(spaces) - 1;
    int effective = indent < maximum ? indent : maximum;
    return &spaces[sizeof(spaces) - 1 - effective];
}


//
//  Return character.
//
int Output::operator() (int c) {
    return c;
}


//
//  Format a variable length argument list and return success.
//  Why do all the overhead of the formatting just to toss the
//  output away? Because the caller may be using this class to
//  unit test prior to using a derived output functor, and it
//  is this class' responsibility to insure that the output
//  formatting works correctly (for example, no null pointers
//  are used as character strings) even if the result is discarded.
//
ssize_t Output::operator() (const char* format, va_list ap) {
    char buffer[this->minimum_buffer_size + 1];
    ssize_t fc = ::vsnprintf(buffer, sizeof(buffer), format, ap);
    return fc;
}


//
//  Return success.
//
ssize_t Output::operator() (const char* s, size_t size) {
    return ::strnlen(s, size);
}


//
//  Return success.
//
ssize_t Output::operator() (
    const void* /* buffer */,
    size_t minimum,
    size_t /* maximum */
) {
    return minimum;
}


//
//  Return success.
//
int Output::operator() () {
    return 0;
}


//
//  Show this object on the output object.
//
void Output::show(int /* level */, Output* display, int indent) const {
    Platform& pl = Platform::instance();
    Print printf(display);
    const char* sp = printf.output().indentation(indent);
    char component[sizeof(__FILE__)];
    printf("%s%s(%p)[%lu]\n",
        sp, pl.component(__FILE__, component, sizeof(component)),
        this, sizeof(*this));
}


#include "com/diag/desperado/End.h"
