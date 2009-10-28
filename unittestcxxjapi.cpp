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

    $Id: unittestcxxjapi.cpp,v 1.3 2006/08/04 20:42:46 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the cxxjapi unit test.
 *
 *  @see    cxxjapi.h
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.3 $
 *
 *  @date   $Date: 2006/08/04 20:42:46 $
 */


#include "UnitTest.h"
#include "java.h"
#include "java.h"
#include "cxxjapi.h"
#include "cxxjapi.h"
#include "generics.h"
#include "generics.h"
#include "Platform.h"
#include "Platform.h"
#include "Print.h"
#include "Print.h"
#include "Desperado.h"


CXXCAPI int unittestcxxjapi() {
    Print printf(Platform::instance().output());
    Print errorf(Platform::instance().error());
    int errors = 0;

    printf("%s[%d]: begin\n", __FILE__, __LINE__);

    if (sizeof(j_byte_t) != 1) {
        errorf("%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, sizeof(j_byte_t), 1);
        ++errors;
    }

    if (intminof(j_byte_t) != -128) {
        errorf("%s[%d]: (%d!=%d)!\n",
            __FILE__, __LINE__, intminof(j_byte_t), -128);
        ++errors;
    }

    if (intmaxof(j_byte_t) != 127) {
        errorf("%s[%d]: (%d!=%d)!\n",
            __FILE__, __LINE__, intminof(j_byte_t), -128);
        ++errors;
    }

    if (sizeof(j_char_t) != 2) {
        errorf("%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, sizeof(j_char_t), 2);
        ++errors;
    }

    if (intminof(j_char_t) != 0) {
        errorf("%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, intminof(j_char_t), 0);
        ++errors;
    }

    if (intmaxof(j_char_t) != 65535) {
        errorf("%s[%d]: (%d!=%d)!\n",
            __FILE__, __LINE__, intmaxof(j_char_t), 65535);
        ++errors;
    }

    if (sizeof(j_short_t) != 2) {
        errorf("%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, sizeof(j_short_t), 2);
        ++errors;
    }

    if (intminof(j_short_t) != (-32767 - 1)) {
        errorf("%s[%d]: (%d!=%d)!\n",
            __FILE__, __LINE__, intminof(j_short_t), (-32767 - 1));
        ++errors;
    }

    if (intmaxof(j_short_t) != 32767) {
        errorf("%s[%d]: (%d!=%d)!\n",
            __FILE__, __LINE__, intmaxof(j_short_t), 32767);
        ++errors;
    }

    if (sizeof(j_int_t) != 4) {
        errorf("%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, sizeof(j_int_t), 4);
        ++errors;
    }

    if (intminof(j_int_t) != (-2147483647L - 1L)) {
        errorf("%s[%d]: (%ld!=%ld)!\n",
            __FILE__, __LINE__, intminof(j_int_t), (-2147483647L - 1L));
        ++errors;
    }

    if (intmaxof(j_int_t) != 2147483647L) {
        errorf("%s[%d]: (%ld!=%ld)!\n",
            __FILE__, __LINE__, intmaxof(j_int_t), 2147483647L);
        ++errors;
    }

    if (sizeof(j_size_t) != 4) {
        errorf("%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, sizeof(j_size_t), 4);
        ++errors;
    }

    if (sizeof(j_long_t) != 8) {
        errorf("%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, sizeof(j_long_t), 8);
        ++errors;
    }

    if (intminof(j_long_t) != (-9223372036854775807LL - 1LL)) {
        errorf("%s[%d]: (%lld!=%lld)!\n",
            __FILE__, __LINE__,
            intminof(j_long_t), (-9223372036854775807LL - 1LL));
        ++errors;
    }

    if (intmaxof(j_long_t) != 9223372036854775807LL) {
        errorf("%s[%d]: (%lld!=%lld)!\n",
            __FILE__, __LINE__,
            intminof(j_long_t), 9223372036854775807LL);
        ++errors;
    }

    if (sizeof(j_boolean_t) != 1) {
        errorf("%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, sizeof(j_boolean_t), 1);
        ++errors;
    }

    /*
     *  There is no requirement AFAIK that the Java sense of
     *  true and false and the C and C++ senses of true and
     *  false coincide, although I would expect them to do so.
     */

    j_boolean_t jtrue = j_true;
    if (jtrue != j_true) {
        errorf("%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, jtrue, j_true);
        ++errors;
    }
    if (jtrue != BOOLEAN_C2J(true)) {
        errorf("%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, jtrue, BOOLEAN_C2J(true));
        ++errors;
    }
    if (BOOLEAN_J2C(jtrue) != true) {
        errorf("%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, BOOLEAN_J2C(jtrue), true);
        ++errors;
    }

    j_boolean_t jfalse = j_false;
    if (jfalse != j_false) {
        errorf("%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, jfalse, j_false);
        ++errors;
    }
    if (jfalse != BOOLEAN_C2J(false)) {
        errorf("%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, jfalse, BOOLEAN_C2J(false));
        ++errors;
    }
    if (BOOLEAN_J2C(jfalse) != false) {
        errorf("%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, BOOLEAN_J2C(jfalse), false);
        ++errors;
    }

    if (sizeof(j_float_t) != 4) {
        errorf("%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, sizeof(j_float_t), 4);
        ++errors;
    }

    if (sizeof(j_double_t) != 8) {
        errorf("%s[%d]: (%u!=%u)!\n",
            __FILE__, __LINE__, sizeof(j_double_t), 8);
        ++errors;
    }

    printf("%s[%d]: end errors=%d\n", __FILE__, __LINE__, errors);

    return errors;
}
