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
 *  Implements the Ficl API functions.
 *
 *  @see    FiclSystem
 *
 *  @see    FiclMachine
 *
 *  @author Chip Overclock (coverclock@diag.com)
 *
 *
 */


#if defined(DESPERADO_HAS_FICL)


#include "com/diag/desperado/target.h"
#include "com/diag/desperado/generics.h"
#include "com/diag/desperado/ficlApi.h"
#include "com/diag/desperado/Platform.h"
#include "com/diag/desperado/Print.h"


/*
 *  Invoke a Ficl-callable function.
 */
int desperado_ficl_proxy(
    ficlVm* pVM,
    desperado_ficl_function fp,
    int argc,
    int* argv
) {
    int rc;

    switch (argc) {
    case 0:
        rc = (*fp)(
            pVM
        );
        break;
    case 1:
        rc = (*fp)(
            pVM,
            argv[0]
        );
        break;
    case 2:
        rc = (*fp)(
            pVM,
            argv[0],
            argv[1]
        );
        break;
    case 3:
        rc = (*fp)(
            pVM,
            argv[0],
            argv[1],
            argv[2]
        );
        break;
    case 4:
        rc = (*fp)(
            pVM,
            argv[0],
            argv[1],
            argv[2],
            argv[3]
        );
        break;
    case 5:
        rc = (*fp)(
            pVM,
            argv[0],
            argv[1],
            argv[2],
            argv[3],
            argv[4]
        );
        break;
    case 6:
        rc = (*fp)(
            pVM,
            argv[0],
            argv[1],
            argv[2],
            argv[3],
            argv[4],
            argv[5]
        );
        break;
    case 7:
        rc = (*fp)(
            pVM,
            argv[0],
            argv[1],
            argv[2],
            argv[3],
            argv[4],
            argv[5],
            argv[6]
        );
        break;
    case 8:
        rc = (*fp)(
            pVM,
            argv[0],
            argv[1],
            argv[2],
            argv[3],
            argv[4],
            argv[5],
            argv[6],
            argv[7]
        );
        break;
    case 9:
        rc = (*fp)(
            pVM,
            argv[0],
            argv[1],
            argv[2],
            argv[3],
            argv[4],
            argv[5],
            argv[6],
            argv[7],
            argv[8]
        );
        break;
    case 10:
        rc = (*fp)(
            pVM,
            argv[0],
            argv[1],
            argv[2],
            argv[3],
            argv[4],
            argv[5],
            argv[6],
            argv[7],
            argv[8],
            argv[9]
        );
        break;
    default:
    	rc = -1;
    	break;
   }

    return rc;
}


/*
 *  Implement the Desperado (( Ficl word.
 */
void desperado_ficl_openparens(ficlVm* pVM) {
    ficlIp ip;

    ip = (ficlIp)ficlStackPopPointer(pVM->returnStack);
    ficlStackPushPointer(pVM->returnStack, pVM->dataStack->top);
    ficlStackPushPointer(pVM->returnStack, ip);
}


/*
 *  Implement the Desperado )) Ficl word.
 */
void desperado_ficl_closeparens(ficlVm* pVM) {
    ficlIp ip;
    ficlCell* bottom;
    int argc;
    int argv[10];
    int extras;
    int ii;
    void* vp;
    uintptr_t up;
    desperado_ficl_function fp;
    int rc;

    /*
     *  Determine the argument count by determining the differences
     *  in the stack size before and after pushing the arguments.
     */

    ip = (ficlIp)ficlStackPopPointer(pVM->returnStack);
    bottom = (ficlCell*)ficlStackPopPointer(pVM->returnStack);
    ficlStackPushPointer(pVM->returnStack, ip);

    argc = pVM->dataStack->top - bottom; 
    if (0 > argc) {
        argc = 0;
    } 

    extras = 0;
    if ((int)countof(argv) < argc) {
        extras = argc - (int)countof(argv);
        argc = (int)countof(argv);
    }

    /*
     *  Marshall the arguments by popping them off the stack.
     */

    for (ii = 0; argc > ii; ++ii) {
        argv[argc - ii - 1] = ficlStackPopInteger(pVM->dataStack);
    }

    for (ii = 0; extras > ii; ++ii ) {
        ficlStackPopInteger(pVM->dataStack);
    }

    /*
     *  Pop the function pointer off the stack.
     */

    vp = ficlStackPopPointer(pVM->dataStack);
    up = (uintptr_t)vp;
    fp = (desperado_ficl_function)up;

    /*
     *  Call the function with the appropriate number of parameters.
     */

    rc = desperado_ficl_proxy(pVM, fp, argc, argv); 

    /*
     *  Push the function return result onto the stack.
     */

    ficlStackPushInteger(pVM->dataStack, rc);
}


/*
 *  Implement the Desperado (()) Ficl word.
 */
void desperado_ficl_null(ficlVm* pVM) {
    void* vp;
    uintptr_t up;
    desperado_ficl_function fp;
    int rc;

    /*
     *  Pop the function pointer off the stack.
     */

    vp = ficlStackPopPointer(pVM->dataStack);
    up = (uintptr_t)vp;
    fp = (desperado_ficl_function)up;

    /*
     *  Call the function with no parameters.
     */

    rc = desperado_ficl_proxy(pVM, fp, 0, 0); 

    /*
     *  Push the function return result onto the stack.
     */

    ficlStackPushInteger(pVM->dataStack, rc);
} 


/*
 *  Implement the Desperado ((..)) Ficl word.
 */
void desperado_ficl_parens(ficlVm* pVM) {
    void* vp;
    uintptr_t up;
    desperado_ficl_function fp;
    int argc;
    int argv[10];
    int extras;
    int ii;
    int rc;

    /*
     *  Pop the function pointer off the stack.
     */

    vp = ficlStackPopPointer(pVM->dataStack);
    up = (uintptr_t)vp;
    fp = (desperado_ficl_function)up;

    /*
     *  Pop the argc off the stack.
     */

    argc = ficlStackPopInteger(pVM->dataStack);
    if (0 > argc) {
        argc = 0;
    } 

    extras = 0;
    if ((int)countof(argv) < argc) {
        extras = argc - (int)countof(argv);
        argc = (int)countof(argv);
    }

    /*
     *  Marshall the arguments by popping them off the stack.
     */

    for (ii = 0; argc > ii; ++ii) {
        argv[argc - ii - 1] = ficlStackPopInteger(pVM->dataStack);
    }

    for (ii = 0; extras > ii; ++ii ) {
        ficlStackPopInteger(pVM->dataStack);
    }

    /*
     *  Call the function with the appropriate number of parameters.
     */

    rc = desperado_ficl_proxy(pVM, fp, argc, argv); 

    /*
     *  Push the function return result onto the stack.
     */

    ficlStackPushInteger(pVM->dataStack, rc);
} 


#endif
