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
 *  Implements the FiclShell unit test.
 *
 *  @see    FiclShell
 *
 *  @author Chip Overclock (coverclock@diag.com)
 *
 *
 */

#if defined(DESPERADO_HAS_FICL)

#include "com/diag/desperado/UnitTest.h"
#include "com/diag/desperado/cxxcapi.h"
#include "com/diag/desperado/cxxcapi.h"
#include "com/diag/desperado/generics.h"
#include "com/diag/desperado/generics.h"
#include "com/diag/desperado/string.h"
#include "com/diag/desperado/string.h"
#include "com/diag/desperado/ficlApi.h"
#include "com/diag/desperado/ficlApi.h"
#include "com/diag/desperado/FiclShell.h"
#include "com/diag/desperado/FiclShell.h"
#include "com/diag/desperado/DataInput.h"
#include "com/diag/desperado/DataInput.h"
#include "com/diag/desperado/Print.h"
#include "com/diag/desperado/Print.h"
#include "com/diag/desperado/Platform.h"
#include "com/diag/desperado/Platform.h"
#include "com/diag/desperado/Desperado.h"


CXXCAPI int unittestFiclShellProxy(void);
CXXCAPI int unittestFiclShellValue;
CXXCAPI int unittestFiclShellErrors;

static FiclShell staticficlshell;

const char script[] =
    ": ++errors ( -- ) unittestFiclShellErrors DUP @ 1 + SWAP ! ;\n"
    ": expected ( N -- E ) 1 + 0 SWAP 0 ?DO I + LOOP ;\n"
    ": expecting ( RC N -- ) expected DUP ROT DUP ROT "
    "            <> IF   .\" (\" . .\" !=\" . .\" )!\" CR ++errors "
    "            ELSE . . CR THEN ;\n"
    ": f00 ( -- RC ) unittestFiclShell00 (( )) ;\n"
    ": f01 ( -- RC ) unittestFiclShell01 (( 1 )) ;\n"
    ": f02 ( -- RC ) unittestFiclShell02 (( 1 2 )) ;\n"
    ": f03 ( -- RC ) unittestFiclShell03 (( 1 2 3 )) ;\n"
    ": f04 ( -- RC ) unittestFiclShell04 (( 1 2 3 4 )) ;\n"
    ": f05 ( -- RC ) unittestFiclShell05 (( 1 2 3 4 5 )) ;\n"
    ": f06 ( -- RC ) unittestFiclShell06 (( 1 2 3 4 5 6 )) ;\n"
    ": f07 ( -- RC ) unittestFiclShell07 (( 1 2 3 4 5 6 7 )) ;\n"
    ": f08 ( -- RC ) unittestFiclShell08 (( 1 2 3 4 5 6 7 8 )) ;\n"
    ": f09 ( -- RC ) unittestFiclShell09 (( 1 2 3 4 5 6 7 8 9 )) ;\n"
    ": f10 ( -- RC ) unittestFiclShell10 (( 1 2 3 4 5 6 7 8 9 10 )) ;\n"
    ": v00 ( -- RC ) 0 unittestFiclShell00 ((...)) ;\n"
    ": v01 ( -- RC ) 1 1 unittestFiclShell01 ((...)) ;\n"
    ": v02 ( -- RC ) 1 2 2 unittestFiclShell02 ((...)) ;\n"
    ": v03 ( -- RC ) 1 2 3 3 unittestFiclShell03 ((...)) ;\n"
    ": v04 ( -- RC ) 1 2 3 4 4 unittestFiclShell04 ((...)) ;\n"
    ": v05 ( -- RC ) 1 2 3 4 5 5 unittestFiclShell05 ((...)) ;\n"
    ": v06 ( -- RC ) 1 2 3 4 5 6 6 unittestFiclShell06 ((...)) ;\n"
    ": v07 ( -- RC ) 1 2 3 4 5 6 7 7 unittestFiclShell07 ((...)) ;\n"
    ": v08 ( -- RC ) 1 2 3 4 5 6 7 8 8 unittestFiclShell08 ((...)) ;\n"
    ": v09 ( -- RC ) 1 2 3 4 5 6 7 8 9 9 unittestFiclShell09 ((...)) ;\n"
    ": v10 ( -- RC ) 1 2 3 4 5 6 7 8 9 10 10 unittestFiclShell10 ((...)) ;\n"
    ": t00 ( -- ) f00 0  expecting v00 0  expecting ;\n"
    ": t01 ( -- ) f01 1  expecting v01 1  expecting ;\n"
    ": t02 ( -- ) f02 2  expecting v02 2  expecting ;\n"
    ": t03 ( -- ) f03 3  expecting v03 3  expecting ;\n"
    ": t04 ( -- ) f04 4  expecting v04 4  expecting ;\n"
    ": t05 ( -- ) f05 5  expecting v05 5  expecting ;\n"
    ": t06 ( -- ) f06 6  expecting v06 6  expecting ;\n"
    ": t07 ( -- ) f07 7  expecting v07 7  expecting ;\n"
    ": t08 ( -- ) f08 8  expecting v08 8  expecting ;\n"
    ": t09 ( -- ) f09 9  expecting v09 9  expecting ;\n"
    ": t10 ( -- ) f10 10 expecting v10 10 expecting ;\n"
    ": unittest 0 unittestFiclShellErrors !"
    "           CR .\" begin\" CR"
    "           t00 t01 t02 t03 t04 t05 t06 t07 t08 t09 t10"
    "           .\" end errors=\" unittestFiclShellErrors @ . CR ;\n"
    "unittest\n"
;

CXXCAPI int unittestFiclShell(void*, int interactive) {
    Print printf(Platform::instance().output());
    Print errorf(Platform::instance().error());
    int errors = 0;

    printf("%s[%d]: begin\n", __FILE__, __LINE__);

    ::unittestFiclShellErrors = 0;

    ::staticficlshell.show();

    printf("%s[%d]: proxy\n", __FILE__, __LINE__);

    errors += unittestFiclShellProxy();

    if (!interactive) {

        char buffer[sizeof(script)];

        printf("%s[%d]: shell with pointer\n", __FILE__, __LINE__);

        strncpy(buffer, script, sizeof(buffer));
        DataInput datainput;
        DataInput datainput2(buffer);
        datainput = datainput2;

        Input* input = 0;
        if (!interactive) {
            input = &datainput;
        }

        unittestFiclShellValue = -1;

        {
            FiclShell ficlshell;
            
            int rc = ficlshell(input);
            errors += ::unittestFiclShellErrors;

            if (0 > unittestFiclShellValue) {
                errorf("%s[%d]: (0>%d)!\n",
                    __FILE__, __LINE__, unittestFiclShellValue);
                ++errors;
            }

            ficlshell.show();

            printf("\n%s[%d]: rc=%d errors=%d\n",
                __FILE__, __LINE__, rc, errors);
        }

        printf("%s[%d]: shell with pointer and prompt\n",
            __FILE__, __LINE__);

        strncpy(buffer, script, sizeof(buffer));
        DataInput datainput3(buffer);
        datainput = datainput3;

        unittestFiclShellValue = -1;

        {
            FiclShell ficlshell;

            int rc = ficlshell(&datainput, "ok> ");
            errors += ::unittestFiclShellErrors;

            if (0 > unittestFiclShellValue) {
                errorf("%s[%d]: (0>%d)!\n",
                    __FILE__, __LINE__, unittestFiclShellValue);
                ++errors;
            }

            ficlshell.show();

            printf("\n%s[%d]: rc=%d errors=%d\n",
                __FILE__, __LINE__, rc, errors);
        }

        printf("%s[%d]: shell with reference\n",
            __FILE__, __LINE__);

        strncpy(buffer, script, sizeof(buffer));
        DataInput datainput4(buffer);
        datainput = datainput4;

        unittestFiclShellValue = -1;

        {
            FiclShell ficlshell;

            int rc = ficlshell(datainput);
            errors += ::unittestFiclShellErrors;

            if (0 > unittestFiclShellValue) {
                errorf("%s[%d]: (0>%d)!\n",
                    __FILE__, __LINE__, unittestFiclShellValue);
                ++errors;
            }

            ficlshell.show();

            printf("\n%s[%d]: rc=%d errors=%d\n",
                __FILE__, __LINE__, rc, errors);
        }

        printf("%s[%d]: shell with reference and prompt\n",
            __FILE__, __LINE__);

        strncpy(buffer, script, sizeof(buffer));
        DataInput datainput5(buffer);
        datainput = datainput5;

        unittestFiclShellValue = -1;

        {
            FiclShell ficlshell;

            int rc = ficlshell(datainput, "ok> ");
            errors += ::unittestFiclShellErrors;

            if (0 > unittestFiclShellValue) {
                errorf("%s[%d]: (0>%d)!\n",
                    __FILE__, __LINE__, unittestFiclShellValue);
                ++errors;
            }

            ficlshell.show();

            printf("\n%s[%d]: rc=%d errors=%d\n",
                __FILE__, __LINE__, rc, errors);
        }

        printf("%s[%d]: shell with string\n",
            __FILE__, __LINE__);

        strncpy(buffer, script, sizeof(buffer));

        unittestFiclShellValue = -1;

        {
            FiclShell ficlshell;
 
            int rc = ficlshell(buffer);
            errors += ::unittestFiclShellErrors;

            if (0 > unittestFiclShellValue) {
                errorf("%s[%d]: (0>%d)!\n",
                    __FILE__, __LINE__, unittestFiclShellValue);
                ++errors;
            }

            ficlshell.show();

            printf("\n%s[%d]: rc=%d errors=%d\n",
                __FILE__, __LINE__, rc, errors);
        }

    } else {

        FiclShell ficlshell;

        ficlshell();

    }

    printf("%s[%d]: end errors=%d\n",
        __FILE__, __LINE__, errors);

    return errors;
}

#endif
