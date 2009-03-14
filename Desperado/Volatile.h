#ifndef _COM_DIAG_DESPERADO_VOLATILE_H_
#define _COM_DIAG_DESPERADO_VOLATILE_H_

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
 *  Defines the Desperado Volatile class that provides helper
 *  functions for volatile accesses.
 *
 *  @see    E. Eide, J. Regehr, "Volatiles Are Miscompiled, and
 *          What to Do about It", <I>Proceedings of the Eighth
 *          ACM and IEEE International Conference on Embedded
 *          Software</i>, Atlanta GA, Oct 2008
 *
 *  This can be included from either a C or a C++ translation unit.
 * 
 *  @author $Author: jsloan $
 */


#include "target.h"
#include "cxxcapi.h"


/**
 *  Return the value of the specified volatile unsigned 64-bit
 *  integer variable. Must not be inlined.
 *
 *  @param vp points to the volatile variable.
 *
 *  @return the value of the volatile variable.
 */
CXXCAPI uint64_t volatile_value_uint64(volatile uint64_t * vp);


/**
 *  Return the value of the specified volatile unsigned 32-bit
 *  integer variable. Must not be inlined.
 *
 *  @param vp points to the volatile variable.
 *
 *  @return the value of the volatile variable.
 */
CXXCAPI uint32_t volatile_value_uint32(volatile uint32_t * vp);


/**
 *  Return the value of the specified volatile unsigned 16-bit
 *  integer variable. Must not be inlined.
 *
 *  @param vp points to the volatile variable.
 *
 *  @return the value of the volatile variable.
 */
CXXCAPI uint16_t volatile_value_uint16(volatile uint16_t * vp);


/**
 *  Return the value of the specified volatile unsigned 8-bit
 *  integer variable. Must not be inlined.
 *
 *  @param vp points to the volatile variable.
 *
 *  @return the value of the volatile variable.
 */
CXXCAPI uint8_t volatile_value_uint8(volatile uint8_t * vp);


/**
 *  Return the value of the specified volatile signed 64-bit
 *  integer variable. Must not be inlined.
 *
 *  @param vp points to the volatile variable.
 *
 *  @return the value of the volatile variable.
 */
CXXCAPI int64_t volatile_value_int64(volatile int64_t * vp);


/**
 *  Return the value of the specified volatile signed 32-bit
 *  integer variable. Must not be inlined.
 *
 *  @param vp points to the volatile variable.
 *
 *  @return the value of the volatile variable.
 */
CXXCAPI int32_t volatile_value_int32(volatile int32_t * vp);


/**
 *  Return the value of the specified volatile signed 16-bit
 *  integer variable. Must not be inlined.
 *
 *  @param vp points to the volatile variable.
 *
 *  @return the value of the volatile variable.
 */
CXXCAPI int16_t volatile_value_int16(volatile int16_t * vp);


/**
 *  Return the value of the specified volatile signed 8-bit
 *  integer variable. Must not be inlined.
 *
 *  @param vp points to the volatile variable.
 *
 *  @return the value of the volatile variable.
 */
CXXCAPI int8_t volatile_value_int8(volatile int8_t * vp);


/**
 *  Return a pointer to of the specified volatile unsigned 64-bit
 *  integer variable. Must not be inlined.
 *
 *  @param vp points to the volatile variable.
 *
 *  @return a pointer to the volatile variable.
 */
CXXCAPI volatile uint64_t * volatile_address_uint64(volatile uint64_t * vp);


/**
 *  Return a pointer to of the specified volatile unsigned 32-bit
 *  integer variable. Must not be inlined.
 *
 *  @param vp points to the volatile variable.
 *
 *  @return a pointer to the volatile variable.
 */
CXXCAPI volatile uint32_t * volatile_address_uint32(volatile uint32_t * vp);


/**
 *  Return a pointer to of the specified volatile unsigned 16-bit
 *  integer variable. Must not be inlined.
 *
 *  @param vp points to the volatile variable.
 *
 *  @return a pointer to the volatile variable.
 */
CXXCAPI volatile uint16_t * volatile_address_uint16(volatile uint16_t * vp);


/**
 *  Return a pointer to of the specified volatile unsigned 8-bit
 *  integer variable. Must not be inlined.
 *
 *  @param vp points to the volatile variable.
 *
 *  @return a pointer to the volatile variable.
 */
CXXCAPI volatile uint8_t * volatile_address_uint8(volatile uint8_t * vp);


/**
 *  Return a pointer to of the specified volatile signed 64-bit
 *  integer variable. Must not be inlined.
 *
 *  @param vp points to the volatile variable.
 *
 *  @return a pointer to the volatile variable.
 */
CXXCAPI volatile int64_t * volatile_address_int64(volatile int64_t * vp);


/**
 *  Return a pointer to of the specified volatile signed 32-bit
 *  integer variable. Must not be inlined.
 *
 *  @param vp points to the volatile variable.
 *
 *  @return a pointer to the volatile variable.
 */
CXXCAPI volatile int32_t * volatile_address_int32(volatile int32_t * vp);


/**
 *  Return a pointer to of the specified volatile signed 16-bit
 *  integer variable. Must not be inlined.
 *
 *  @param vp points to the volatile variable.
 *
 *  @return a pointer to the volatile variable.
 */
CXXCAPI volatile int16_t * volatile_address_int16(volatile int16_t * vp);


/**
 *  Return a pointer to of the specified volatile signed 8-bit
 *  integer variable. Must not be inlined.
 *
 *  @param vp points to the volatile variable.
 *
 *  @return a pointer to the volatile variable.
 */
CXXCAPI volatile int8_t * volatile_address_int8(volatile int8_t * vp);


#if defined(__cplusplus)

/**
 * The Volatile class defines polymorphic inline static C++ class methods
 * to the C-callable value and address helper functions. Note that although
 * these methods are inlined, the C-callable functions are not. This is
 * crucial to implement Eide and Regher's volatile helper functions.
 */
class Volatile {

    static inline uint64_t value(volatile uint64_t * vp) {
		return volatile_value_uint64(vp);
	}

    static inline uint32_t value(volatile uint32_t * vp) {
		return volatile_value_uint32(vp);
	}

    static inline uint16_t value(volatile uint16_t * vp) {
		return volatile_value_uint16(vp);
	}

    static inline uint8_t value(volatile uint8_t * vp) {
		return volatile_value_uint8(vp);
	}

    static inline int64_t value(volatile int64_t * vp) {
		return volatile_value_int64(vp);
	}

    static inline int32_t value(volatile int32_t * vp) {
		return volatile_value_int32(vp);
	}

    static inline int16_t value(volatile int16_t * vp) {
		return volatile_value_int16(vp);
	}

    static inline int8_t value(volatile int8_t * vp) {
		return volatile_value_int8(vp);
	}

    static inline uint64_t value(volatile uint64_t & vr) {
		return volatile_value_uint64(&vr);
	}

    static inline uint32_t value(volatile uint32_t & vr) {
		return volatile_value_uint32(&vr);
	}

    static inline uint16_t value(volatile uint16_t & vr) {
		return volatile_value_uint16(&vr);
	}

    static inline uint8_t value(volatile uint8_t & vr) {
		return volatile_value_uint8(&vr);
	}

    static inline int64_t value(volatile int64_t & vr) {
		return volatile_value_int64(&vr);
	}

    static inline int32_t value(volatile int32_t & vr) {
		return volatile_value_int32(&vr);
	}

    static inline int16_t value(volatile int16_t & vr) {
		return volatile_value_int16(&vr);
	}

    static inline int8_t value(volatile int8_t & vr) {
		return volatile_value_int8(&vr);
	}

    static inline volatile uint64_t * address(volatile uint64_t * vp) {
		return volatile_address_uint64(vp);
	}

    static inline volatile uint32_t * address(volatile uint32_t * vp) {
		return volatile_address_uint32(vp);
	}

    static inline volatile uint16_t * address(volatile uint16_t * vp) {
		return volatile_address_uint16(vp);
	}

    static inline volatile uint8_t * address(volatile uint8_t * vp) {
		return volatile_address_uint8(vp);
	}

    static inline volatile int64_t * address(volatile int64_t * vp) {
		return volatile_address_int64(vp);
	}

    static inline volatile int32_t * address(volatile int32_t * vp) {
		return volatile_address_int32(vp);
	}

    static inline volatile int16_t * address(volatile int16_t * vp) {
		return volatile_address_int16(vp);
	}

    static inline volatile int8_t * address(volatile int8_t * vp) {
		return volatile_address_int8(vp);
	}

    static inline volatile uint64_t & address(volatile uint64_t & vr) {
		return *volatile_address_uint64(&vr);
	}

    static inline volatile uint32_t & address(volatile uint32_t & vr) {
		return *volatile_address_uint32(&vr);
	}

    static inline volatile uint16_t & address(volatile uint16_t & vr) {
		return *volatile_address_uint16(&vr);
	}

    static inline volatile uint8_t & address(volatile uint8_t & vr) {
		return *volatile_address_uint8(&vr);
	}

    static inline volatile int64_t & address(volatile int64_t & vr) {
		return *volatile_address_int64(&vr);
	}

    static inline volatile int32_t & address(volatile int32_t & vr) {
		return *volatile_address_int32(&vr);
	}

    static inline volatile int16_t & address(volatile int16_t & vr) {
		return *volatile_address_int16(&vr);
	}

    static inline volatile int8_t & address(volatile int8_t & vr) {
		return *volatile_address_int8(&vr);
	}

};

#endif

#if defined(__cplusplus)

/**
 *  Run the Volatile unit test.
 *  
 *  @return the number of errors detected by the unit test.
 */
extern "C" int unittestVolatile();

/**
 *  Run the Volatile2 unit test.
 *  
 *  @return the number of errors detected by the unit test.
 */
extern "C" int unittestVolatile2();

#endif


#endif
