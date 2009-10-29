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

    $Id: unittestFicl.cpp,v 1.8 2006/09/04 13:50:01 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the Ficl unit test.
 *
 *  @see    Ficl
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.8 $
 *
 *  @date   $Date: 2006/09/04 13:50:01 $
 */


#if defined(DESPERADO_HAS_FICL)


#include "UnitTest.h"
#include "string.h"
#include "string.h"
#include "cxxcapi.h"
#include "cxxcapi.h"
#include "ficlApi.h"
#include "ficlApi.h"
#include "ficllocal.h"
#include "ficllocal.h"
#include "FiclSystem.h"
#include "FiclSystem.h"
#include "FiclMachine.h"
#include "FiclMachine.h"
#include "BufferInput.h"
#include "BufferInput.h"
#include "Print.h"
#include "Print.h"
#include "Platform.h"
#include "Platform.h"
#include "Desperado.h"

static FiclSystem staticFiclSystem;
static FiclMachine staticFiclMachine;

// Some of the following variables are just defined in order
// to see how their names are represented (mangled, unmangled,
// or otherwise) in the symbol table when using the nm utility.
extern "C" {
    int unittestFiclFunction(int x, char y) { return x + y; }
    uint8_t unittestFiclUint8;
    uint16_t unittestFiclUint16;
    uint32_t unittestFiclUint32;
    uint64_t unittestFiclUint64;
    void* unittestFiclPointer;
    int8_t unittestFiclInt8Zero = 0;
    int16_t unittestFiclInt16One = 1;
    int32_t unittestFiclInt32Two= 2;
    int64_t unittestFiclInt64Three = 3;
    FiclSystem unittestFiclSystem;
    void* unittestFiclPointerSystem = &unittestFiclSystem;
    const int unittestFiclIntConst = -1;
}
CXXCAPI int unittestFiclIntC;
CXXCAPI int unittestFiclFunctionC(int x, char y) { return x + y; }
CXXCAPI int unittestFiclIntCXX;
CXXCAPI int unittestFiclFunctionCXX(int x, char y) { return x + y; }
class UnitTestFicl {
public:
    static int unittestFiclMethodCXX(int x, char y) { return x + y; }
};

const char sample[] =
    "2 2 + . cr hello world\n"
    "1 2 unittestFiclFunctionC dup .\n"
    "unittestFiclInt32Two dup @ .\n"
    "!\n"
    "unittestFiclInt32Two @ .\n"
    "*\n"
;

extern "C" {

    static void desperado_ficl_unittestFiclFunctionC(ficlVm* pVM) {
        int x = ficlStackPopInteger(pVM->dataStack);
        int y = ficlStackPopInteger(pVM->dataStack);
        int rc = unittestFiclFunctionC(x, y);
        ficlStackPushInteger(pVM->dataStack, rc);
    }

    static void desperado_ficl_unittestFiclInt32Two(ficlVm* pVM) {
        ficlStackPushPointer(pVM->dataStack, &unittestFiclInt32Two);
    }

}

static int audit(FiclSystem& system, FiclMachine& machine) {
    Print printf(Platform::instance().output());
    Print errorf(Platform::instance().error());
    int errors = 0;

    printf("%s[%d]: begin audit(%p,%p)\n",
        __FILE__, __LINE__, &system, &machine);

    ficlVm* pVM = machine.getNativeMachine();
    if (0 == pVM) {
        errorf("%s[%d]: (%p==%p)!\n",
            __FILE__, __LINE__, 0, pVM);
        ++errors;
    }

    FiclSystem* ps = FiclSystem::findFiclSystem(pVM);
    if (ps != &system) {
        errorf("%s[%d]: (%p!=%p)!\n",
            __FILE__, __LINE__, ps, &system);
        ++errors;
    }

    FiclMachine* pm = FiclMachine::findFiclMachine(pVM);
    if (pm != &machine) {
        errorf("%s[%d]: (%p!=%p)!\n",
            __FILE__, __LINE__, pm, &machine);
        ++errors;
    }

    if ((0 != ps) && (0 != pVM)) {
        ficlSystem* psns = ps->getNativeSystem();
        ficlSystem* pVMs = pVM->callback.system;
        if (psns != pVMs) {
            errorf("%s[%d]: (%p!=%p)!\n",
                __FILE__, __LINE__, psns, pVMs);
            ++errors;
        }
    }

    if (0 != pm) {
        FiclSystem* pms = pm->getFiclSystem();
        if (pms != &system) {
            errorf("%s[%d]: (%p!=%p)!\n",
                __FILE__, __LINE__, pms, &system);
            ++errors;
        }
        ficlVm* pmnm = pm->getNativeMachine();
        if (pmnm != pVM) {
            errorf("%s[%d]: (%p!=%p)!\n",
                __FILE__, __LINE__, pmnm, pVM);
            ++errors;
        }
    }

    ps = FiclSystem::findFiclSystem(0);
    if (0 != ps) {
        errorf("%s[%d]: (%p!=%p)!\n",
            __FILE__, __LINE__, 0, ps);
        ++errors;
    }

    pm = FiclMachine::findFiclMachine(0);
    if (0 != pm) {
        errorf("%s[%d]: (%p!=%p)!\n",
            __FILE__, __LINE__, 0, pm);
        ++errors;
    }

    printf("%s[%d]: end audit(%p,%p) errors=%d\n",
        __FILE__, __LINE__, &system, &machine, errors);

    return errors;
}

CXXCAPI int unittestFicl(void*, int interactive) {
    Print printf(Platform::instance().output());
    Print errorf(Platform::instance().error());
    int errors = 0;

    int rc;

    printf("%s[%d]: begin\n", __FILE__, __LINE__);

    ::staticFiclSystem.show();
    ::staticFiclMachine.show();

    FiclSystem system;
    system.show();

    {

        FiclMachine machine1(system);
        machine1.show();

        printf("%s[%d]: command line\n", __FILE__, __LINE__);

        rc = machine1(".ver .( " __DATE__ " ) cr quit");
        printf("%s[%d]: Ficl returns %d\n",
            __FILE__, __LINE__, rc);

        machine1.show();

        printf("%s[%d]: script\n", __FILE__, __LINE__);

        char script[] = {
            ": hello .\" Hello, \" ;\n"
            ": world .\" world! \" cr ;\n"
            ": Suggestion: .\" for the interactive test try entering: \" cr "
                ".\" 2 2 + . cr hello world\" cr ;\n"
            "Suggestion: "
        };

        BufferInput batch(script);

        rc = machine1(batch);
        printf("%s[%d]: Ficl returns %d\n",
            __FILE__, __LINE__, rc);

        machine1.show();

        printf("%s[%d]: interfaces\n", __FILE__, __LINE__);

        FiclMachine machine2(system);

        ficlSystem* s = machine2.getNativeSystem();
        ficlDictionary* d = ficlSystemGetDictionary(s);

        ficlDictionaryLock(d, ~0);

        ficlDictionaryAppendPrimitive(
            d,
            "unittestFiclFunctionC",
            desperado_ficl_unittestFiclFunctionC,
            0
        );

        ficlDictionaryAppendPrimitive(
            d,
            "unittestFiclInt32Two",
            desperado_ficl_unittestFiclInt32Two,
            0
        );

        ficlDictionaryLock(d, 0);

        printf("%s[%d]: extras\n", __FILE__, __LINE__);

        system.extras();

        printf("%s[%d]: interactive\n", __FILE__, __LINE__);

        Input* input = &Platform::instance().input();
        char buffer[sizeof(script)];
        BufferInput bufferinput;

        if (!interactive) {
            strncpy(buffer, sample, sizeof(buffer));
            bufferinput.initialize(buffer);
            input = &bufferinput;
        }

        unittestFiclInt32Two = 2;

        ficlCell four; four.i = 4;
        ficlCell five; five.i = 5;

        printf("%s[%d]: before unittestFiclInt32Two=%d four.i=%d five.i=%d\n",
            __FILE__, __LINE__, unittestFiclInt32Two, four.i, five.i);

        machine2.push(four);
        machine2.push(five);

        rc = machine2(*input, "ficl> ");
        printf("%s[%d]: Ficl returns %d\n",
            __FILE__, __LINE__, rc);
        machine2.show();

        ficlCell twenty = machine2.pop();

        printf("%s[%d]: after unittestFiclInt32Two=%d twenty.i=%d\n",
            __FILE__, __LINE__, unittestFiclInt32Two, twenty.i);

        if (3 != unittestFiclInt32Two) {
            errorf("%s[%d]: (%d!=%d)!\n",
                __FILE__, __LINE__, 3, unittestFiclInt32Two);
            ++errors;
        }

        if (20 != twenty.i) {
            errorf("%s[%d]: (%d!=%d)!\n",
                __FILE__, __LINE__, 20, twenty.i);
            ++errors;
        }

        printf("%s[%d]: links\n", __FILE__, __LINE__);

        system.show();
        machine1.show();
        machine2.show();

        printf("%s[%d]: audit\n", __FILE__, __LINE__);

        errors += audit(system, machine1);
        errors += audit(system, machine2);
    }

    printf("%s[%d]: destruction\n", __FILE__, __LINE__);

    system.show();

    printf("%s[%d]: end errors=%d\n",
        __FILE__, __LINE__, errors);

    return errors;
}


#endif
