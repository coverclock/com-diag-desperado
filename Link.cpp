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

    $Id: Link.cpp,v 1.7 2007/01/10 22:43:44 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the Link class.
 *
 *  @see    Link
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.7 $
 *
 *  @date   $Date: 2007/01/10 22:43:44 $
 */


#include "com/diag/desperado/Link.h"
#include "com/diag/desperado/Print.h"
#include "com/diag/desperado/Platform.h"


#include "com/diag/desperado/Begin.h"


//
//  Re-root the chain that this link is on so that all links
//  are rooted to this link.
//
Link* Link::reroot() {
    Link* link = this;
    do {
        link->root = this;
        link = link->next;
    } while (link != this);
    return this;
}


//
//  Apply a functor to a chain of links, the functor deciding which
//  link to follow, next or previous.
//
Link* Link::apply(Functor& functor) {
    Link* link = this;
    Link* result;

    while (true) {
        result = functor(link);
        if ((0 == result) || (link == result)) { return result; }
        link = result;
    }
}


//
//  Show this object on the output object.
//
void Link::show(int /* level */, Output* display, int indent) const {
    Platform& pl = Platform::instance();
    Print printf(display);
    const char* sp = printf.output().indentation(indent);
    char component[sizeof(__FILE__)];
    printf("%s%s(%p)[%lu]:\n",
        sp, pl.component(__FILE__, component, sizeof(component)),
        this, sizeof(*this));
    printf("%s next=%p\n", sp, this->next);
    printf("%s previous=%p\n", sp, this->previous);
    printf("%s root=%p\n", sp, this->root);
    printf("%s payload=%p\n", sp, this->payload);
}


//
//  Virtual destructor for Functor.
//
Link::Functor::~Functor() {
}


#include "com/diag/desperado/End.h"
