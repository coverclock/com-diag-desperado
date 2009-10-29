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
 *  Implements the ByteOrder unit test.
 *
 *  @see    ByteOrder
 *
 *  @author $Author: jsloan $
 */


#include "UnitTest.h"
#include "target.h"
#include "target.h"
#include "string.h"
#include "string.h"
#include "ByteOrder.h"
#include "ByteOrder.h"
#include "Print.h"
#include "Print.h"
#include "Dump.h"
#include "Dump.h"
#include "Platform.h"
#include "Platform.h"
#include "Output.h"
#include "Output.h"
#include "Desperado.h"


template <typename _HOST_, typename _NETWORK_>
static int testInteger(const char * file, int line, _HOST_ input) {
    Print errorf(Platform::instance().error());
    Dump dump(Platform::instance().error());
    int errors = 0;
    _NETWORK_ temp = hton(input);
    _HOST_ output = ntoh(temp);
    if (input != output) {
        errorf("%s[%d]: failed!\n", file, line);
        dump.bytes(&input, sizeof(input));
        dump.bytes(&temp, sizeof(temp));
        dump.bytes(&output, sizeof(output));
        ++errors;
    }
    return errors;
}

template <typename _HOST_, typename _NETWORK_>
static int testFloat(const char * file, int line, _HOST_ input) {
    Print errorf(Platform::instance().error());
    Dump dump(Platform::instance().error());
    int errors = 0;
    _NETWORK_ temp = fhton(input);
    _HOST_ output = fntoh(temp);
    if (input != output) {
        errorf("%s[%d]: failed!\n", file, line);
        dump.bytes(&input, sizeof(input));
        dump.bytes(&temp, sizeof(temp));
        dump.bytes(&output, sizeof(output));
        ++errors;
    }
    return errors;
}

template <typename _TYPE_>
static int testSwap(const char * file, int line, _TYPE_ from, _TYPE_ to) {
    Print errorf(Platform::instance().error());
    Dump dump(Platform::instance().error());
    int errors = 0;
    _TYPE_ temp = ByteOrder<_TYPE_, _TYPE_, _TYPE_>::swap(from);
    if (temp != to) {
        errorf("%s[%d]: failed!\n", file, line);
        dump.bytes(&from, sizeof(from));
        dump.bytes(&temp, sizeof(temp));
        dump.bytes(&to, sizeof(to));
        ++errors;
    }
    return errors;
}


CXXCAPI int unittestByteOrder(void) {
    Print printf(Platform::instance().output());
    Print errorf(Platform::instance().error());
    int errors = 0;

    printf("%s[%d]: begin\n", __FILE__, __LINE__);

    errors += testInteger<int64_t, int64_t>
        (__FILE__, __LINE__, 0x0123456789abcdefLL);
    errors += testInteger<int32_t, int32_t>
        (__FILE__, __LINE__, 0x01234567L);
    errors += testInteger<int16_t, int16_t>
        (__FILE__, __LINE__, 0x0123);
    errors += testInteger<int8_t, int8_t>
        (__FILE__, __LINE__, 0x01);

    errors += testInteger<uint64_t, uint64_t>
        (__FILE__, __LINE__, 0x0123456789abcdefULL);
    errors += testInteger<uint32_t, uint32_t>
        (__FILE__, __LINE__, 0x01234567UL);
    errors += testInteger<uint16_t, uint16_t>
        (__FILE__, __LINE__, 0x0123U);
    errors += testInteger<uint8_t, uint8_t>
        (__FILE__, __LINE__, 0x01U);

    errors += testFloat<float64_t, uint64_t>
        (__FILE__, __LINE__, -3.4);
    errors += testFloat<float32_t, uint32_t>
        (__FILE__, __LINE__, 1.2);

    errors += testInteger<signed long long, signed long long>
		(__FILE__, __LINE__, 0x0123456789abcdefLL);
    errors += testInteger<signed long, signed long>
		(__FILE__, __LINE__, 0x01234567L);
    errors += testInteger<signed int, signed int>
		(__FILE__, __LINE__, 0x01234567L);
    errors += testInteger<signed short, signed short>
		(__FILE__, __LINE__, 0x0123);
    errors += testInteger<signed char, signed char>
		(__FILE__, __LINE__, 0x01);

    errors += testInteger<unsigned long long, unsigned long long>
		(__FILE__, __LINE__, 0x0123456789abcdefULL);
    errors += testInteger<unsigned long, unsigned long>
		(__FILE__, __LINE__, 0x01234567UL);
    errors += testInteger<unsigned int, unsigned int>
		(__FILE__, __LINE__, 0x01234567UL);
    errors += testInteger<unsigned short, unsigned short>
		(__FILE__, __LINE__, 0x0123U);
    errors += testInteger<unsigned char, unsigned char>
		(__FILE__, __LINE__, 0x01U);

    errors += testFloat<double, uint64_t>
        (__FILE__, __LINE__, -3.4);
    errors += testFloat<float, uint32_t>
        (__FILE__, __LINE__, 1.2);

    errors += testSwap<uint64_t>
        (__FILE__, __LINE__, 0x0123456789abcdefULL, 0xefcdab8967452301ULL);
    errors += testSwap<uint32_t>
        (__FILE__, __LINE__, 0x01234567UL, 0x67452301UL);
    errors += testSwap<uint16_t>
        (__FILE__, __LINE__, 0x0123U, 0x2301U);
    errors += testSwap<uint8_t>
        (__FILE__, __LINE__, 0x01U, 0x01U);

    errors += testSwap<int64_t>
        (__FILE__, __LINE__, 0x0123456789abcdefLL, 0xefcdab8967452301LL);
    errors += testSwap<int32_t>
        (__FILE__, __LINE__, 0x01234567L, 0x67452301L);
    errors += testSwap<int16_t>
        (__FILE__, __LINE__, 0x0123, 0x2301);
    errors += testSwap<int8_t>
        (__FILE__, __LINE__, 0x01, 0x01);

    printf("%s[%d]: end errors=%d\n", __FILE__, __LINE__,
        errors);

    return errors;
}
