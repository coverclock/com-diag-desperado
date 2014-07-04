/* vim: set ts=4 expandtab shiftwidth=4: */

/******************************************************************************

    Copyright 2006-2011 Digital Aggregates Corporation, Colorado, USA.
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
 *  Implements the cxxjapi2 unit test.
 *
 *  @see    cxxjapi.h
 *
 *  @author Chip Overclock (coverclock@diag.com)
 *
 *
 */


#include "com/diag/desperado/UnitTest.h"
#include "com/diag/desperado/java.h"
#include "com/diag/desperado/java.h"
#include "com/diag/desperado/cxxjapi.h"
#include "com/diag/desperado/cxxjapi.h"
#include "com/diag/desperado/generics.h"
#include "com/diag/desperado/generics.h"
#include "com/diag/desperado/Platform.h"
#include "com/diag/desperado/Platform.h"
#include "com/diag/desperado/Print.h"
#include "com/diag/desperado/Print.h"
#include "com/diag/desperado/bool.h"
#include "com/diag/desperado/bool.h"


CXXCAPI int unittestcxxjapi2() {
    int errors = 0;
    j_boolean_t jtrue = j_true;
    j_boolean_t jfalse = j_false;

    print_f(platform_output(), "%s[%d]: begin\n",
        __FILE__, __LINE__);

    if (sizeof(j_byte_t) != 1) {
        print_f(platform_error(), "%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, sizeof(j_byte_t), 1);
        ++errors;
    }

    if (intminof(j_byte_t) != -128) {
        print_f(platform_error(), "%s[%d]: (%d!=%d)!\n",
            __FILE__, __LINE__, intminof(j_byte_t), -128);
        ++errors;
    }

    if (intmaxof(j_byte_t) != 127) {
        print_f(platform_error(), "%s[%d]: (%d!=%d)!\n",
            __FILE__, __LINE__, intminof(j_byte_t), -128);
        ++errors;
    }

    if (sizeof(j_char_t) != 2) {
        print_f(platform_error(), "%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, sizeof(j_char_t), 2);
        ++errors;
    }

    if (intminof(j_char_t) != 0) {
        print_f(platform_error(), "%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, intminof(j_char_t), 0);
        ++errors;
    }

    if (intmaxof(j_char_t) != 65535) {
        print_f(platform_error(), "%s[%d]: (%d!=%d)!\n",
            __FILE__, __LINE__, intmaxof(j_char_t), 65535);
        ++errors;
    }

    if (sizeof(j_short_t) != 2) {
        print_f(platform_error(), "%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, sizeof(j_short_t), 2);
        ++errors;
    }

    if (intminof(j_short_t) != (-32767 - 1)) {
        print_f(platform_error(), "%s[%d]: (%d!=%d)!\n",
            __FILE__, __LINE__, intminof(j_short_t), (-32767 - 1));
        ++errors;
    }

    if (intmaxof(j_short_t) != 32767) {
        print_f(platform_error(), "%s[%d]: (%d!=%d)!\n",
            __FILE__, __LINE__, intmaxof(j_short_t), 32767);
        ++errors;
    }

    if (sizeof(j_int_t) != 4) {
        print_f(platform_error(), "%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, sizeof(j_int_t), 4);
        ++errors;
    }

    if (intminof(j_int_t) != (-2147483647L - 1L)) {
        print_f(platform_error(), "%s[%d]: (%ld!=%ld)!\n",
            __FILE__, __LINE__, intminof(j_int_t), (-2147483647L - 1L));
        ++errors;
    }

    if (intmaxof(j_int_t) != 2147483647L) {
        print_f(platform_error(), "%s[%d]: (%ld!=%ld)!\n",
            __FILE__, __LINE__, intmaxof(j_int_t), 2147483647L);
        ++errors;
    }

    if (sizeof(j_size_t) != 4) {
        print_f(platform_error(), "%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, sizeof(j_size_t), 4);
        ++errors;
    }

    if (sizeof(j_long_t) != 8) {
        print_f(platform_error(), "%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, sizeof(j_long_t), 8);
        ++errors;
    }

    if (intminof(j_long_t) != (-9223372036854775807LL - 1LL)) {
        print_f(platform_error(), "%s[%d]: (%lld!=%lld)!\n",
            __FILE__, __LINE__,
            intminof(j_long_t), (-9223372036854775807LL - 1LL));
        ++errors;
    }

    if (intmaxof(j_long_t) != 9223372036854775807LL) {
        print_f(platform_error(), "%s[%d]: (%lld!=%lld)!\n",
            __FILE__, __LINE__,
            intminof(j_long_t), 9223372036854775807LL);
        ++errors;
    }

    if (sizeof(j_boolean_t) != 1) {
        print_f(platform_error(), "%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, sizeof(j_boolean_t), 1);
        ++errors;
    }

    /*
     *  There is no requirement AFAIK that the Java sense of
     *  true and false and the C and C++ senses of true and
     *  false coincide, although I would expect them to do so.
     */

    if (jtrue != j_true) {
        print_f(platform_error(), "%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, jtrue, j_true);
        ++errors;
    }
    if (jtrue != BOOLEAN_C2J(true)) {
        print_f(platform_error(), "%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, jtrue, BOOLEAN_C2J(true));
        ++errors;
    }
    if (BOOLEAN_J2C(jtrue) != true) {
        print_f(platform_error(), "%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, BOOLEAN_J2C(jtrue), true);
        ++errors;
    }

    if (jfalse != j_false) {
        print_f(platform_error(), "%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, jfalse, j_false);
        ++errors;
    }
    if (jfalse != BOOLEAN_C2J(false)) {
        print_f(platform_error(), "%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, jfalse, BOOLEAN_C2J(false));
        ++errors;
    }
    if (BOOLEAN_J2C(jfalse) != false) {
        print_f(platform_error(), "%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, BOOLEAN_J2C(jfalse), false);
        ++errors;
    }

    if (sizeof(j_float_t) != 4) {
        print_f(platform_error(), "%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, sizeof(j_float_t), 4);
        ++errors;
    }

    if (sizeof(j_double_t) != 8) {
        print_f(platform_error(), "%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, sizeof(j_double_t), 8);
        ++errors;
    }

    print_f(platform_output(), "%s[%d]: end errors=%d\n",
        __FILE__, __LINE__, errors);

    return errors;
}
