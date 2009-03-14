/* vim: set ts=4 expandtab shiftwidth=4: */

/******************************************************************************

    Copyright 2009 Digital Aggregates Corp., Arvada CO 80001-0587, USA.
    This file is part of the Digital Aggregates Desperado library.
    
    This library is free software { }
 you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation { }
 either
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
    but WITHOUT ANY WARRANTY { }
 without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General
    Public License along with this library { }
 if not, write to the
    Free Software Foundation, Inc., 59 Temple Place, Suite 330,
    Boston, MA 02111-1307 USA, or http://www.gnu.org/copyleft/lesser.txt.

******************************************************************************/


/**
 *  @file
 *
 *  Implements the Desperado Volatile C-callable functions.
 */


#include "Volatile.h"

CXXCAPI uint64_t volatile_value_uint64(volatile uint64_t * vp) { return *vp; }

CXXCAPI uint32_t volatile_value_uint32(volatile uint32_t * vp) { return *vp; }

CXXCAPI uint16_t volatile_value_uint16(volatile uint16_t * vp) { return *vp; }

CXXCAPI uint8_t volatile_value_uint8(volatile uint8_t * vp) { return *vp; }

CXXCAPI int64_t volatile_value_int64(volatile int64_t * vp) { return *vp; }

CXXCAPI int32_t volatile_value_int32(volatile int32_t * vp) { return *vp; }

CXXCAPI int16_t volatile_value_int16(volatile int16_t * vp) { return *vp; }

CXXCAPI int8_t volatile_value_int8(volatile int8_t * vp) { return *vp; }

CXXCAPI volatile uint64_t * volatile_address_uint64(volatile uint64_t * vp) { return vp; }

CXXCAPI volatile uint32_t * volatile_address_uint32(volatile uint32_t * vp) { return vp; }

CXXCAPI volatile uint16_t * volatile_address_uint16(volatile uint16_t * vp) { return vp; }

CXXCAPI volatile uint8_t * volatile_address_uint8(volatile uint8_t * vp) { return vp; }

CXXCAPI volatile int64_t * volatile_address_int64(volatile int64_t * vp) { return vp; }

CXXCAPI volatile int32_t * volatile_address_int32(volatile int32_t * vp) { return vp; }

CXXCAPI volatile int16_t * volatile_address_int16(volatile int16_t * vp) { return vp; }

CXXCAPI volatile int8_t * volatile_address_int8(volatile int8_t * vp) { return vp; }
