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
 *  Implements the FiclShell unit test 2.
 *
 *  @see    FiclShell
 *
 *  @author Chip Overclock (coverclock@diag.com)
 *
 *
 */

#if defined(DESPERADO_HAS_FICL)

#include "com/diag/desperado/UnitTest.h"
#include "com/diag/desperado/generics.h"
#include "com/diag/desperado/generics.h"
#include "com/diag/desperado/ficlApi.h"
#include "com/diag/desperado/ficlApi.h"
#include "com/diag/desperado/Print.h"
#include "com/diag/desperado/Print.h"
#include "com/diag/desperado/Platform.h"
#include "com/diag/desperado/Platform.h"

extern int unittestFiclShell00(ficlVm*);
extern int unittestFiclShell01(ficlVm*,int);
extern int unittestFiclShell02(ficlVm*,int,int);
extern int unittestFiclShell03(ficlVm*,int,int,int);
extern int unittestFiclShell04(ficlVm*,int,int,int,int);
extern int unittestFiclShell05(ficlVm*,int,int,int,int,int);
extern int unittestFiclShell06(ficlVm*,int,int,int,int,int,int);
extern int unittestFiclShell07(ficlVm*,int,int,int,int,int,int,int);
extern int unittestFiclShell08(ficlVm*,int,int,int,int,int,int,int,int);
extern int unittestFiclShell09(ficlVm*,int,int,int,int,int,int,int,int,int);
extern int unittestFiclShell10(ficlVm*,int,int,int,int,int,int,int,int,int,int);
extern int unittestFiclShell11(ficlVm*,int,int,int,int,int,int,int,int,int,int,int);
extern int unittestFiclShellProxy(void);

int unittestFiclShellValue = -1;
int unittestFiclShellErrors = 0;

ficlVm* unittestFiclShellPointer = 0;

int unittestFiclShell00(
    ficlVm* pVM
) {
    unittestFiclShellPointer = pVM;
    unittestFiclShellValue = 0;
    return unittestFiclShellValue;
}

int unittestFiclShell01(
    ficlVm* pVM,
    int a00
) {
    unittestFiclShellPointer = pVM;
    unittestFiclShellValue = a00;
    return unittestFiclShellValue;
}

int unittestFiclShell02(
    ficlVm* pVM,
    int a00,
    int a01
) {
    unittestFiclShellPointer = pVM;
    unittestFiclShellValue = a00 + a01;
    return unittestFiclShellValue;
}

int unittestFiclShell03(
    ficlVm* pVM,
    int a00,
    int a01,
    int a02
) {
    unittestFiclShellPointer = pVM;
    unittestFiclShellValue = a00 + a01 + a02;
    return unittestFiclShellValue;
}

int unittestFiclShell04(
    ficlVm* pVM,
    int a00,
    int a01,
    int a02,
    int a03
) {
    unittestFiclShellPointer = pVM;
    unittestFiclShellValue = a00 + a01 + a02 + a03;
    return unittestFiclShellValue;
}

int unittestFiclShell05(
    ficlVm* pVM,
    int a00,
    int a01,
    int a02,
    int a03,
    int a04
) {
    unittestFiclShellPointer = pVM;
    unittestFiclShellValue = a00 + a01 + a02 + a03 + a04;
    return unittestFiclShellValue;
}

int unittestFiclShell06(
    ficlVm* pVM,
    int a00,
    int a01,
    int a02,
    int a03,
    int a04,
    int a05
) {
    unittestFiclShellPointer = pVM;
    unittestFiclShellValue = a00 + a01 + a02 + a03 + a04 + a05;
    return unittestFiclShellValue;
}

int unittestFiclShell07(
    ficlVm* pVM,
    int a00,
    int a01,
    int a02,
    int a03,
    int a04,
    int a05,
    int a06
) {
    unittestFiclShellPointer = pVM;
    unittestFiclShellValue = a00 + a01 + a02 + a03 + a04 + a05 + a06;
    return unittestFiclShellValue;
}

int unittestFiclShell08(
    ficlVm* pVM,
    int a00,
    int a01,
    int a02,
    int a03,
    int a04,
    int a05,
    int a06,
    int a07
) {
    unittestFiclShellPointer = pVM;
    unittestFiclShellValue = a00 + a01 + a02 + a03 + a04 + a05 + a06 + a07;
    return unittestFiclShellValue;
}

int unittestFiclShell09(
    ficlVm* pVM,
    int a00,
    int a01,
    int a02,
    int a03,
    int a04,
    int a05,
    int a06,
    int a07,
    int a08
) {
    unittestFiclShellPointer = pVM;
    unittestFiclShellValue = a00 + a01 + a02 + a03 + a04 + a05 + a06 + a07 +
                                a08;
    return unittestFiclShellValue;
}

int unittestFiclShell10(
    ficlVm* pVM,
    int a00,
    int a01,
    int a02,
    int a03,
    int a04,
    int a05,
    int a06,
    int a07,
    int a08,
    int a09
) {
    unittestFiclShellPointer = pVM;
    unittestFiclShellValue = a00 + a01 + a02 + a03 + a04 + a05 + a06 + a07 +
                                a08 + a09;
    return unittestFiclShellValue;
}

int unittestFiclShell11(
    ficlVm* pVM,
    int a00,
    int a01,
    int a02,
    int a03,
    int a04,
    int a05,
    int a06,
    int a07,
    int a08,
    int a09,
    int a10
) {
    unittestFiclShellPointer = pVM;
    unittestFiclShellValue = a00 + a01 + a02 + a03 + a04 + a05 + a06 + a07 +
                                a08 + a09 + a10;
    return unittestFiclShellValue;
}

int unittestFiclShellProxy(void) {
    int errors;
    desperado_ficl_function fps[12];
    int argv[12];
    int rc;
    int expected;
    size_t ii;
    size_t jj;

    errors = 0;

    print_f(platform_error(), "%s[%d]: begin\n", __FILE__, __LINE__);

    fps[0]  = (desperado_ficl_function)unittestFiclShell00;
    fps[1]  = (desperado_ficl_function)unittestFiclShell01;
    fps[2]  = (desperado_ficl_function)unittestFiclShell02;
    fps[3]  = (desperado_ficl_function)unittestFiclShell03;
    fps[4]  = (desperado_ficl_function)unittestFiclShell04;
    fps[5]  = (desperado_ficl_function)unittestFiclShell05;
    fps[6]  = (desperado_ficl_function)unittestFiclShell06;
    fps[7]  = (desperado_ficl_function)unittestFiclShell07;
    fps[8]  = (desperado_ficl_function)unittestFiclShell08;
    fps[9]  = (desperado_ficl_function)unittestFiclShell09;
    fps[10]  = (desperado_ficl_function)unittestFiclShell10;
    fps[11]  = (desperado_ficl_function)unittestFiclShell11;

    for (ii = 0; countof(argv) > ii; ++ii) {
        argv[ii] = ii + 1;
    }

    for (ii = 0; countof(argv) > ii; ++ii) {
        expected = 0;
        for (jj = 0; ii > jj; ++jj) {
            expected += argv[jj];
        }
        rc = desperado_ficl_proxy(0, fps[ii], (int)ii, argv);
        print_f(platform_output(), "%s[%d]: argc=%d rc=%d expected=%d\n",
            __FILE__, __LINE__, (int)ii, rc, expected);
        if ((11 > ii) && (expected != rc)) {
            print_f(platform_error(), "%s[%d]: (%d!=%d)!\n",
                __FILE__, __LINE__, expected, rc);
            ++errors;
        }
    }

    print_f(platform_error(), "%s[%d]: end errors=%d\n",
        __FILE__, __LINE__, errors);

    return errors;
}


#endif
