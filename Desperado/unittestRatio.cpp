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
 *  Implements the Ratio unit test.
 *
 *  @see    Ratio
 *
 *  @author $Author: jsloan $
 */


#include "UnitTest.h"
#include "Ratio.h"
#include "Ratio.h"
#include "Print.h"
#include "Output.h"
#include "Platform.h"
#include "Desperado.h"

static int test(const Ratio & ratio, int numerator, int denominator) {
    Print errorf(Platform::instance().error());
    int errors = 0;
    if (ratio.numerator() != numerator) {
        errorf("%s[%d]: (%d!=%d)!\n",
            ratio.numerator(), numerator);
        ++errors;
    }
    if (ratio.denominator() != denominator) {
        errorf("%s[%d]: (%d!=%d)!\n",
            ratio.denominator(), denominator);
        ++errors;
    }
    return errors;
}

CXXCAPI int unittestRatio(void) {
    Print printf(Platform::instance().output());
    Print errorf(Platform::instance().error());
    int errors = 0;

    printf("%s[%d]: begin\n", __FILE__, __LINE__);

    {
        printf("%s[%d]: test 1\n", __FILE__, __LINE__);
        Ratio ratio;
        test(ratio, 0, 1);
    }

    {
        printf("%s[%d]: test 2\n", __FILE__, __LINE__);
        Ratio ratio(0, 0);
        test(ratio, 0, 0);
    }

    {
        printf("%s[%d]: test 3\n", __FILE__, __LINE__);
        Ratio ratio(24, 8);
        test(ratio, 3, 1);
    }

    {
        printf("%s[%d]: test 4\n", __FILE__, __LINE__);
        Ratio ratio(24, 48);
        test(ratio, 1, 2);
    }

    return errors;

    {
        printf("%s[%d]: test 2\n", __FILE__, __LINE__);
        static const int factor = 2 * 2;
        static const int denominator = 2 * 3 * 3 * 5 * 5 * 5 * 7;
        static const int numerator = denominator * factor;
        Ratio ratio(numerator, denominator);
        if (ratio.numerator() != numerator) {
            errorf("%s[%d]: (%d!=%d)!\n",
                __FILE__, __LINE__, ratio.numerator(), numerator);
            ++errors;
        }
        if (ratio.denominator() != denominator) {
            errorf("%s[%d]: (%d!=%d)!\n",
                __FILE__, __LINE__, ratio.denominator(), denominator);
            ++errors;
        }
        int number1 = ratio;
        if (number1 != factor) {
            errorf("%s[%d]: (%d!=%d)!\n",
                __FILE__, __LINE__, number1, factor);
            ++errors;
        }
        double number2 = ratio;
        if (number2 != factor) {
            errorf("%s[%d]: (%f!=%d)!\n",
                __FILE__, __LINE__, number2, factor);
            ++errors;
        }
        ratio.normalize();
        if (ratio.numerator() != factor) {
            errorf("%s[%d]: (%d!=%d)!\n",
                __FILE__, __LINE__, ratio.numerator(), factor);
            ++errors;
        }
        if (ratio.denominator() != 1) {
            errorf("%s[%d]: (%d!=%d)!\n",
                __FILE__, __LINE__, ratio.denominator(), 1);
            ++errors;
        }
        double number3 = ratio;
        if (number3 != factor) {
            errorf("%s[%d]: (%f!=%d)!\n",
                __FILE__, __LINE__, number3, factor);
            ++errors;
        }
    }

    {
        printf("%s[%d]: test 2\n", __FILE__, __LINE__);

        Ratio ratio0;
        Ratio ratio1(10, 30);
        Ratio ratio2(10, 20);
        ratio0 = ratio1 + ratio2;
        test(ratio0, 5, 6);
    }

    printf("%s[%d]: end errors=%d\n", __FILE__, __LINE__,
        errors);

    return errors;
}
