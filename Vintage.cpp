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

    $Id: Vintage.cpp,v 1.6 2006/02/07 00:07:03 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the Vintage class.
 *
 *  @see    Vintage
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.6 $
 *
 *  @date   $Date: 2006/02/07 00:07:03 $
 */



#include <new>
#include "Vintage.h"
#include "Platform.h"
#include "Print.h"


const char Vintage::product[] =     "$Product: Desperado $";

const char Vintage::license[] =     "$License: Modified GNU Lesser Public License $";

const char Vintage::copyright[] =   "$Copyright: Copyright 2007 Digital Aggregates Corp., Arvada CO 80001-0587, USA $";

const char Vintage::contact[] =     "$Contact: coverclock@diag.com (Chip Overclock) $";

const char Vintage::url[] =         "$Url: http://www.diag.com $";

const char Vintage::uri[] =         "$Uri: sip:600@sip.diag.dnsalias.com $";

const char Vintage::date[] =        "$Date: 2007-08-15T23:00:00+00 $";

const char Vintage::release[] =     "$Name: jupiter $";

const char Vintage::build[] =       "$Build: " __DATE__ " " __TIME__ " $";


//
//  Destructor.
//
Vintage::~Vintage() {
}


//
//    Initializer.
//
bool Vintage::initialize() {
    bool rc = false;
    try {
        this->Vintage::~Vintage();
        new(this) Vintage;
        rc = true;
    } catch (...) {
        rc = false;
    }
    return rc;
}


//
//  Show this object on the output object.
//
void Vintage::show(int /* level */, Output* display, int indent) const {
    Platform& pl = Platform::instance();
    Print printf(display);
    const char* sp = printf.output().indentation(indent);
    char component[sizeof(__FILE__)];
    printf("%s%s(%p)[%lu]:\n",
        sp, pl.component(__FILE__, component, sizeof(component)),
        this, sizeof(*this));
    printf("%s product[%lu]=\"%s\"\n",
        sp, sizeof(this->product), this->product);
    printf("%s license[%lu]=\"%s\"\n",
        sp, sizeof(this->license), this->license);
    printf("%s copyright[%lu]=\"%s\"\n",
        sp, sizeof(this->copyright), this->copyright);
    printf("%s contact[%lu]=\"%s\"\n",
        sp, sizeof(this->contact),  this->contact);
    printf("%s url[%lu]=\"%s\"\n",
        sp, sizeof(this->url),  this->url);
    printf("%s date[%lu]=\"%s\"\n",
        sp, sizeof(this->date),  this->date);
    printf("%s release[%lu]=\"%s\"\n",
        sp, sizeof(this->release), this->release);
    printf("%s build[%lu]=\"%s\"\n",
        sp, sizeof(this->build), this->build);
}
