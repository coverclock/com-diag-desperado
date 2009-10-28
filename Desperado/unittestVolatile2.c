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
 *  Implements the Volatile unit test.
 *
 *  @see    Volatile
 *
 *  @author $Author: jsloan $
 */


#include "UnitTest.h"
#include "Volatile.h"
#include "Volatile.h"
#include "Print.h"
#include "Print.h"
#include "Platform.h"
#include "Platform.h"
#include "Output.h"
#include "Output.h"
#include "generics.h"
#include "generics.h"

#define unittestVolatileType(_TYPE_) \
do { \
    volatile _TYPE_ datum = -1; \
    platform_printf("%s[%d]: sizeof=%zu issignedint=%d\n", \
        __FILE__, __LINE__, sizeof(_TYPE_), issignedint(_TYPE_)); \
    if (volatile_value_##_TYPE_(&datum) != datum) { \
        platform_errorf("%s[%d]: (0x%x!=0x%x)!\n", \
            __FILE__, __LINE__, volatile_value_##_TYPE_(&datum), datum); \
        ++errors; \
    } \
    if (volatile_address_##_TYPE_(&datum) != &datum) { \
        platform_errorf("%s[%d]: (%p!=%p)!\n", \
            __FILE__, __LINE__, volatile_address_##_TYPE_(&datum), &datum); \
        ++errors; \
    } \
} while (0)

int unittestVolatile2(void) {
    int errors = 0;

    platform_printf("%s[%d]: begin\n", __FILE__, __LINE__);

    unittestVolatileType(uint8_t);
    unittestVolatileType(uint16_t);
    unittestVolatileType(uint32_t);
    unittestVolatileType(uint64_t);
    unittestVolatileType(int8_t);
    unittestVolatileType(int16_t);
    unittestVolatileType(int32_t);
    unittestVolatileType(int64_t);

    platform_printf("%s[%d]: end errors=%d\n", __FILE__, __LINE__,
        errors);

    return errors;
}
