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
 *  Implements the Mutex unit test.
 *
 *  @see    Mutex
 *
 *  @author Chip Overclock (coverclock@diag.com)
 *
 *
 */


#if !defined(DESPERADO_HAS_DEBUGGING)
#define DESPERADO_HAS_DEBUGGING (1)
#endif
#include "com/diag/desperado/UnitTest.h"
#include "com/diag/desperado/debug.h"
#include "com/diag/desperado/debug.h"
#include "com/diag/desperado/Mutex.h"
#include "com/diag/desperado/Mutex.h"
#include "com/diag/desperado/CriticalSection.h"
#include "com/diag/desperado/CriticalSection.h"
#include "com/diag/desperado/Platform.h"
#include "com/diag/desperado/Desperado.h"

static Mutex staticMutex;

CXXCAPI int unittestMutex(void) {
    Print printf(Platform::instance().output());
    Print errorf(Platform::instance().error());
    int errors = 0;

    printf("%s[%d]: begin\n", __FILE__, __LINE__);

    ::staticMutex.show();

    Mutex mutex;

    printf("%s[%d]: mutex begin\n", __FILE__, __LINE__);

    bool locked = mutex.isLocked();
    if (locked) {
        errorf("%s[%d]: (%d!=%d)!\n", __FILE__, __LINE__, locked, false);
        ++errors;
    }

    mutex.show();
    DEBUG_TRACE(mutex.begin());
    mutex.show();

    locked = mutex.isLocked();
    if (!locked) {
        errorf("%s[%d]: (%d!=%d)!\n", __FILE__, __LINE__, locked, true);
        ++errors;
    }

    bool uncancellable = mutex.isUncancellable();
    if (!uncancellable) {
        errorf("%s[%d]: (%d!=%d)!\n", __FILE__, __LINE__, uncancellable, true);
        ++errors;
    }

    printf("%s[%d]: mutex end\n", __FILE__, __LINE__);

    mutex.show();
    DEBUG_TRACE(mutex.end());
    mutex.show();

    locked = mutex.isLocked();
    if (locked) {
        errorf("%s[%d]: (%d!=%d)!\n", __FILE__, __LINE__, locked, false);
        ++errors;
    }

    printf("%s[%d]: mutex recursion\n", __FILE__, __LINE__);

    mutex.show();
    DEBUG_TRACE(mutex.begin());

    locked = mutex.isLocked();
    if (!locked) {
        errorf("%s[%d]: (%d!=%d)!\n", __FILE__, __LINE__, locked, true);
        ++errors;
    }

    uncancellable = mutex.isUncancellable();
    if (!uncancellable) {
        errorf("%s[%d]: (%d!=%d)!\n", __FILE__, __LINE__, uncancellable, true);
        ++errors;
    }

    identity_t id = mutex.getIdentity();

    mutex.show();
    DEBUG_TRACE(mutex.begin());

    locked = mutex.isLocked();
    if (!locked) {
        errorf("%s[%d]: (%d!=%d)!\n", __FILE__, __LINE__, locked, true);
        ++errors;
    }

    uncancellable = mutex.isUncancellable();
    if (!uncancellable) {
        errorf("%s[%d]: (%d!=%d)!\n", __FILE__, __LINE__, uncancellable, true);
        ++errors;
    }

    identity_t id2 = mutex.getIdentity();
    if (id != id2) {
        errorf("%s[%d]: (0x%016llx!=0x%016llx)!\n",
            __FILE__, __LINE__, id, id2);
        ++errors;
    }

    mutex.show();
    DEBUG_TRACE(mutex.begin());

    locked = mutex.isLocked();
    if (!locked) {
        errorf("%s[%d]: (%d!=%d)!\n", __FILE__, __LINE__, locked, true);
        ++errors;
    }

    uncancellable = mutex.isUncancellable();
    if (!uncancellable) {
        errorf("%s[%d]: (%d!=%d)!\n", __FILE__, __LINE__, uncancellable, true);
        ++errors;
    }

    id2 = mutex.getIdentity();
    if (id != id2) {
        errorf("%s[%d]: (0x%016llx!=0x%016llx)!\n",
            __FILE__, __LINE__, id, id2);
        ++errors;
    }

    mutex.show();
    DEBUG_TRACE(mutex.end());

    locked = mutex.isLocked();
    if (!locked) {
        errorf("%s[%d]: (%d!=%d)!\n", __FILE__, __LINE__, locked, true);
        ++errors;
    }

    id2 = mutex.getIdentity();
    if (id != id2) {
        errorf("%s[%d]: (0x%016llx!=0x%016llx)!\n",
            __FILE__, __LINE__, id, id2);
        ++errors;
    }

    mutex.show();
    DEBUG_TRACE(mutex.end());

    locked = mutex.isLocked();
    if (!locked) {
        errorf("%s[%d]: (%d!=%d)!\n", __FILE__, __LINE__, locked, true);
        ++errors;
    }

    id2 = mutex.getIdentity();
    if (id != id2) {
        errorf("%s[%d]: (0x%016llx!=0x%016llx)!\n",
            __FILE__, __LINE__, id, id2);
        ++errors;
    }

    mutex.show();
    DEBUG_TRACE(mutex.end());
    mutex.show();

    locked = mutex.isLocked();
    if (locked) {
        errorf("%s[%d]: (%d!=%d)!\n", __FILE__, __LINE__, locked, false);
        ++errors;
    }

    printf("%s[%d]: critical section\n", __FILE__, __LINE__);

    DEBUG_TRACE(((void)0));
    mutex.show();
    {
        DEBUG_TRACE(CriticalSection one(mutex));
        mutex.show();
        {
            locked = mutex.isLocked();
            if (!locked) {
                errorf("%s[%d]: (%d!=%d)!\n", __FILE__, __LINE__, locked, true);
                ++errors;
            }

            uncancellable = mutex.isUncancellable();
            if (!uncancellable) {
                errorf("%s[%d]: (%d!=%d)!\n", __FILE__, __LINE__, uncancellable, true);
                ++errors;
            }

            id = mutex.getIdentity();

            DEBUG_TRACE(CriticalSection two(mutex));
            mutex.show();
            DEBUG_TRACE(((void)0));

            locked = mutex.isLocked();
            if (!locked) {
                errorf("%s[%d]: (%d!=%d)!\n", __FILE__, __LINE__, locked, true);
                ++errors;
            }

            id2 = mutex.getIdentity();
            if (id != id2) {
                errorf("%s[%d]: (0x%016llx!=0x%016llx)!\n",
                    __FILE__, __LINE__, id, id2);
                ++errors;
            }
        }   
        DEBUG_TRACE(((void)0));
        mutex.show();

        locked = mutex.isLocked();
        if (!locked) {
            errorf("%s[%d]: (%d!=%d)!\n", __FILE__, __LINE__, locked, true);
            ++errors;
        }

        id2 = mutex.getIdentity();
        if (id != id2) {
            errorf("%s[%d]: (0x%016llx!=0x%016llx)!\n",
                __FILE__, __LINE__, id, id2);
            ++errors;
        }
    }
    DEBUG_TRACE(((void)0));
    mutex.show();

    locked = mutex.isLocked();
    if (locked) {
        errorf("%s[%d]: (%d!=%d)!\n", __FILE__, __LINE__, locked, false);
        ++errors;
    }

    printf("%s[%d]: mutex begin cancellable\n", __FILE__, __LINE__);

    locked = mutex.isLocked();
    if (locked) {
        errorf("%s[%d]: (%d!=%d)!\n", __FILE__, __LINE__, locked, false);
        ++errors;
    }

    mutex.show();
    DEBUG_TRACE(mutex.begin(false));
    mutex.show();

    locked = mutex.isLocked();
    if (!locked) {
        errorf("%s[%d]: (%d!=%d)!\n", __FILE__, __LINE__, locked, true);
        ++errors;
    }

    uncancellable = mutex.isUncancellable();
    if (uncancellable) {
        errorf("%s[%d]: (%d!=%d)!\n", __FILE__, __LINE__, uncancellable, false);
        ++errors;
    }

    printf("%s[%d]: mutex end cancellable\n", __FILE__, __LINE__);

    mutex.show();
    DEBUG_TRACE(mutex.end());
    mutex.show();

    locked = mutex.isLocked();
    if (locked) {
        errorf("%s[%d]: (%d!=%d)!\n", __FILE__, __LINE__, locked, false);
        ++errors;
    }

    printf("%s[%d]: end errors=%d\n",
        __FILE__, __LINE__, errors);

    return errors;
}

