/* vim: set ts=4 expandtab shiftwidth=4: */

/******************************************************************************

    Copyright 2005-2008 Digital Aggregates Corp., Arvada CO 80001-0587, USA.
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

    $Id: LeapSeconds.cpp,v 1.6 2006/02/07 00:07:03 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the LeapSeconds class.
 *
 *  @see    LeapSeconds
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.6 $
 *
 *  @date   $Date: 2006/02/07 00:07:03 $
 */


#include <new>
#include "types.h"
#include "generics.h"
#include "LeapSeconds.h"
#include "Platform.h"


//
//  Leap seconds were inserted (or even removed, although it
//  has never happened) by the International Earth Rotation
//  Service (IERS) on these dates and times. ITU-R TF.460
//  specifies that no more than one leap second will be inserted
//  or removed, and that there will be a strong preference to
//  do so on the last day of either December or June.
//
static const CommonEra commoneras[] = {
    CommonEra(1972,  6, 30, 23, 59, 60),
    CommonEra(1972, 12, 31, 23, 59, 60),
    CommonEra(1973, 12, 31, 23, 59, 60),
    CommonEra(1974, 12, 31, 23, 59, 60),
    CommonEra(1975, 12, 31, 23, 59, 60),
    CommonEra(1976, 12, 31, 23, 59, 60),
    CommonEra(1977, 12, 31, 23, 59, 60),
    CommonEra(1978, 12, 31, 23, 59, 60),
    CommonEra(1979, 12, 31, 23, 59, 60),
    CommonEra(1981,  6, 30, 23, 59, 60),
    CommonEra(1982,  6, 30, 23, 59, 60),
    CommonEra(1983,  6, 30, 23, 59, 60),
    CommonEra(1985,  6, 30, 23, 59, 60),
    CommonEra(1987, 12, 31, 23, 59, 60),
    CommonEra(1989, 12, 31, 23, 59, 60),
    CommonEra(1990, 12, 31, 23, 59, 60),
    CommonEra(1992,  6, 30, 23, 59, 60),
    CommonEra(1993,  6, 30, 23, 59, 60),
    CommonEra(1994,  6, 30, 23, 59, 60),
    CommonEra(1995, 12, 31, 23, 59, 60),
    CommonEra(1997,  6, 30, 23, 59, 60),
    CommonEra(1998, 12, 31, 23, 59, 60),
    CommonEra(2005, 12, 31, 23, 59, 60),
    CommonEra(2008, 12, 31, 23, 59, 60)
    //
    //  When another leap second occurs, insert
    //  its Common Era date and time here. It will
    //  likely be at the end of June or December,
    //  and the time should be 23:59:60 for inserted
    //  seconds and 23:59:58 for removed seconds.
    //
};


//
//  Here are the number of leap seconds inserted (or possibly,
//  removed) since the Common Era Epoch for each occurrence.
//  So far, leap seconds have only been inserted due to the
//  Earth's rotation slowing down, but the IERS and ITU-R TF.460
//  admits the possibility that leap seconds could be removed
//  in the future should the Earth's rotation speed up.
//
static const int leapseconds[] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    11,
    12,
    13,
    14,
    15,
    16,
    17,
    18,
    19,
    20,
    21,
    22,
    23
    //
    //  When another leap second occurs, insert the cumulative
    //  number of leap seconds here. If a leap second was inserted,
    //  the value will be one more than the previous value. If
    //  removed, it will be one less.
    //
};


//
//  Here are the number of UTC seconds since the Common Era
//  Epoch for each occurrence. It is the number of atomic (TAI)
//  seconds for each occurrence plus the cumulative number
//  of leap seconds prior to that occurrence.
//
static const seconds_t utcseconds[] = {
    ::commoneras[0].toAtomicSeconds() + ::leapseconds[0],
    ::commoneras[1].toAtomicSeconds() + ::leapseconds[1],
    ::commoneras[2].toAtomicSeconds() + ::leapseconds[2],
    ::commoneras[3].toAtomicSeconds() + ::leapseconds[3],
    ::commoneras[4].toAtomicSeconds() + ::leapseconds[4],
    ::commoneras[5].toAtomicSeconds() + ::leapseconds[5],
    ::commoneras[6].toAtomicSeconds() + ::leapseconds[6],
    ::commoneras[7].toAtomicSeconds() + ::leapseconds[7],
    ::commoneras[8].toAtomicSeconds() + ::leapseconds[8],
    ::commoneras[9].toAtomicSeconds() + ::leapseconds[9],
    ::commoneras[10].toAtomicSeconds() + ::leapseconds[10],
    ::commoneras[11].toAtomicSeconds() + ::leapseconds[11],
    ::commoneras[12].toAtomicSeconds() + ::leapseconds[12],
    ::commoneras[13].toAtomicSeconds() + ::leapseconds[13],
    ::commoneras[14].toAtomicSeconds() + ::leapseconds[14],
    ::commoneras[15].toAtomicSeconds() + ::leapseconds[15],
    ::commoneras[16].toAtomicSeconds() + ::leapseconds[16], 
    ::commoneras[17].toAtomicSeconds() + ::leapseconds[17],
    ::commoneras[18].toAtomicSeconds() + ::leapseconds[18],
    ::commoneras[19].toAtomicSeconds() + ::leapseconds[19],
    ::commoneras[20].toAtomicSeconds() + ::leapseconds[20],
    ::commoneras[21].toAtomicSeconds() + ::leapseconds[21],
    ::commoneras[22].toAtomicSeconds() + ::leapseconds[22],
    ::commoneras[23].toAtomicSeconds() + ::leapseconds[23]
    //
    //  When another leap second occurs, insert a new entry
    //  here using the new values from the previous two tables.
    //
};


//
//  Constructor.
//
//  A derived class can override this constructor to cause the
//  find methods to look somewhere else for the tables, for
//  example, in dynamically allocated arrays populated by
//  data from a file. This can be okay for embedded systems
//  which have a file system; many do not.
//
LeapSeconds::LeapSeconds() :
    count(countof(::commoneras)),
    commoneras(::commoneras),
    leapseconds(::leapseconds),
    utcseconds(::utcseconds)
{
}


//
//  Destructor.
//
LeapSeconds::~LeapSeconds() {
}


//
//    Initializer.
//
bool LeapSeconds::initialize() {
    bool rc = false;
    try {
        this->LeapSeconds::~LeapSeconds();
        new(this) LeapSeconds;
        rc = true;
    } catch (...) {
        rc = false;
    }
    return rc;
}


//
//  Always return true.
//
bool LeapSeconds::isObserved()  const {
    return true;
}


//
//  Look for a matching Common Era entry in the tables.
//
const seconds_t* LeapSeconds::find(const CommonEra& ce, int& ld) const {
    const uint64_t* rc = 0;

    CommonEra myce = ce;
    myce.setNanosecond(0);

    for (size_t ii = 0; ii < this->count; ++ii) {
        ld = this->leapseconds[ii];
        int comparison = this->commoneras[ii].compare(myce);
        if (0 < comparison) {
            break;
        } else if (0 > comparison) {
            continue;
        }
        rc = &(this->utcseconds[ii]);
        ld = this->leapseconds[ii + 1];
        break;
    }

    return rc;
} 


//
//  Look for a matching utcseconds entry in the tables.
//
const CommonEra* LeapSeconds::find(const seconds_t sd, int& ld) const {
    const CommonEra* rc = 0;

    for (size_t ii = 0; ii < this->count; ++ii) {
        ld = this->leapseconds[ii];
        if (this->utcseconds[ii] > sd) {
            break;
        } else if (this->utcseconds[ii] < sd) {
            continue;
        }
        rc = &(this->commoneras[ii]);
        ld = this->leapseconds[ii + 1];
        break;
    }

    return rc;
}


//
//  Show this object on the output object.
//
void LeapSeconds::show(int /* level */, Output* display, int indent) const {
    Platform& pl = Platform::instance();
    Print printf(display);
    const char* sp = printf.output().indentation(indent);
    char component[sizeof(__FILE__)];
    printf("%s%s(%p)[%lu]\n",
        sp, pl.component(__FILE__, component, sizeof(component)),
        this, sizeof(*this));
    printf("%s count=%lu\n", sp, this->count);
    printf("%s commoneras=%p\n", sp, this->commoneras);
    printf("%s leapseconds=%p\n", sp, this->leapseconds);
    printf("%s utcseconds=%p\n", sp, this->utcseconds);
}
