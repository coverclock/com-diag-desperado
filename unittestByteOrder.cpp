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


template <typename _INPUT_, typename _OUTPUT_>
static int testInteger(const char * file, int line, _INPUT_ input) {
    Print errorf(Platform::instance().error());
    Dump dump(Platform::instance().error());
    int errors = 0;
    _OUTPUT_ temp = hton(input);
    _INPUT_ output = ntoh(temp);
    if (input != output) {
        errorf("%s[%d]: failed!\n", file, line);
        dump.bytes(&input, sizeof(input));
        dump.bytes(&temp, sizeof(temp));
        dump.bytes(&output, sizeof(output));
        ++errors;
    }
    return errors;
}

template <typename _INPUT_, typename _OUTPUT_>
static int testFloat(const char * file, int line, _INPUT_ input) {
    Print errorf(Platform::instance().error());
    Dump dump(Platform::instance().error());
    int errors = 0;
    _OUTPUT_ temp = fhton(input);
    _INPUT_ output = fntoh(temp);
    if (input != output) {
        errorf("%s[%d]: failed!\n", file, line);
        dump.bytes(&input, sizeof(input));
        dump.bytes(&temp, sizeof(temp));
        dump.bytes(&output, sizeof(output));
        ++errors;
    }
    return errors;
}


CXXCAPI int unittestByteOrder(void) {
    Print printf(Platform::instance().output());
    Print errorf(Platform::instance().error());
    int errors = 0;

    printf("%s[%d]: begin\n", __FILE__, __LINE__);

    errors += testInteger<int16_t, int16_t>(__FILE__, __LINE__, 0x0123);
    errors += testInteger<int32_t, int32_t>(__FILE__, __LINE__, 0x01234567L);
    errors += testInteger<int64_t, int64_t>(__FILE__, __LINE__, 0x0123456789abcdefLL);

    errors += testInteger<uint16_t, uint16_t>(__FILE__, __LINE__, 0x0123U);
    errors += testInteger<uint32_t, uint32_t>(__FILE__, __LINE__, 0x01234567UL);
    errors += testInteger<uint64_t, uint64_t>(__FILE__, __LINE__, 0x0123456789abcdefULL);

    errors += testFloat<float32_t, uint32_t>(__FILE__, __LINE__, 1.2);
    errors += testFloat<float64_t, uint64_t>(__FILE__, __LINE__, -3.4);

    printf("%s[%d]: end errors=%d\n", __FILE__, __LINE__,
        errors);

    return errors;
}
