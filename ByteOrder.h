#ifndef _COM_DIAG_DESPERADO_BYTEORDER_H_
#define _COM_DIAG_DESPERADO_BYTEORDER_H_

/* vim: set ts=4 expandtab shiftwidth=4: */

/******************************************************************************

    Copyright 2009 Digital Aggregates Corp., Arvada CO 80001-0587, USA.
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
 *  Declares the ByteOrder class.
 */


#if defined(__cplusplus)


#include <stdint.h>
#include <sys/types.h>


/**
 *  @author coverclock@diag.com (Chip Overclock)
 */
template <typename _TYPE_>
union ByteOrder {

    _TYPE_ word;

    uint8_t bytes[sizeof(_TYPE_)];

    static bool mustswap() {
        static const ByteOrder swappable = { 1 };
        return swappable.bytes[0] != 0;
    }

    static _TYPE_ swap(_TYPE_ data) {
        ByteOrder in;
        ByteOrder out;
        in.word = data;
        for (size_t ii = 0; ii < sizeof(data); ++ii) {
            out.bytes[ii] = in.bytes[sizeof(data) - 1 - ii];
        }
        return out.word;
    }

    static _TYPE_ swapif(_TYPE_ data) {
        return mustswap() ? swap(data) : data;
    }

};


inline uint64_t desperado_swap64(uint64_t data) {
    return ByteOrder<uint64_t>::swapif(data);
}

inline uint32_t desperado_swap32(uint32_t data) {
    return ByteOrder<uint32_t>::swapif(data);
}

inline uint64_t desperado_swap16(uint16_t data) {
    return ByteOrder<uint16_t>::swapif(data);
}


/**
 *  Run the ByteOrder unit test.
 *  
 *  @return the number of errors detected by the unit test.
 */
extern "C" int unittestByteOrder();


#endif
