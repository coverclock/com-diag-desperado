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
 *  Implements the Root unit test.
 *
 *  @see    Root
 *
 *  @author $Author: jsloan $
 */


#include "UnitTest.h"
#include "Root.h"
#include "Root.h"
#include "Print.h"
#include "Output.h"
#include "Platform.h"
#include "Desperado.h"

static int testRoot(unsigned int value, unsigned int expected) {
    Print errorf(Platform::instance().error());
    int errors = 0;
    unsigned int actual = root(value);
    if (actual != expected) {
        errorf("%s[%d]: 0x%08x (0x%08x!=0x%08x)!\n",
            __FILE__, __LINE__, value, actual, expected);
        ++errors;
    }
    return errors;
}

CXXCAPI int unittestRoot(void) {
    Print printf(Platform::instance().output());
    Print errorf(Platform::instance().error());
    int errors = 0;

    printf("%s[%d]: begin\n", __FILE__, __LINE__);

    testRoot(0x00000000, 0x00000000);
    testRoot(0x00000001, 0x00000001);
    testRoot(0x00000002, 0x00000001);
    testRoot(0x00000004, 0x00000003);
    testRoot(0x00000008, 0x00000003);
    testRoot(0x00000010, 0x00000007);
    testRoot(0x00000020, 0x00000007);
    testRoot(0x00000040, 0x0000000f);
    testRoot(0x00000080, 0x0000000f);
    testRoot(0xffffffff, 0x0000ffff);
    testRoot(0x7fffffff, 0x0000ffff);
    testRoot(0x3fffffff, 0x00007fff);
    testRoot(0x1fffffff, 0x00007fff);
    testRoot(0x0fffffff, 0x00003fff);
    testRoot(0x07ffffff, 0x00003fff);
    testRoot(0x03ffffff, 0x00001fff);
    testRoot(0x01ffffff, 0x00001fff);
    testRoot(0x00ffffff, 0x00000fff);

    printf("%s[%d]: end errors=%d\n", __FILE__, __LINE__,
        errors);

    return errors;
}

