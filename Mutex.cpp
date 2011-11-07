/* vim: set ts=4 expandtab shiftwidth=4: */

/******************************************************************************

    Copyright 2005-2011 Digital Aggregates Corporation, Colorado, USA.
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
 *  Implements the Mutex class.
 *
 *  @see    Mutex
 *
 *  @author Chip Overclock (coverclock@diag.com)
 *
 *
 */


#include "com/diag/desperado/generics.h"
#include "com/diag/desperado/types.h"
#include "com/diag/desperado/Mutex.h"
#include "com/diag/desperado/Print.h"
#include "com/diag/desperado/Dump.h"
#include "com/diag/desperado/Platform.h"


#include "com/diag/desperado/Begin.h"


//
//  Constructor.
//
Mutex::Mutex() :
    identity(0),
    level(0),
    state(PTHREAD_CANCEL_ENABLE)
{
    pthread_mutexattr_init(&(this->mutexattr));
    pthread_mutexattr_settype(&(this->mutexattr), PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&(this->mutex), &(this->mutexattr));
}


//
//  Destructor.
//
Mutex::~Mutex() {
    pthread_mutex_destroy(&(this->mutex));
    pthread_mutexattr_destroy(&(this->mutexattr));
}


//
//  Lock. This has the unfortunate side effect of making threads
//  waiting on mutexen uncancellable. The alternative would be to
//  allow threads to be cancelled between taking the mutex and
//  becoming uncancellable, leaving the mutex locked. As a rule,
//  threads should not perform blocking operations while holding
//  a mutex, but this is sometimes easier said than done.
//
bool Mutex::begin() {
    Platform& platform = Platform::instance();
    Logger& logger = platform.logger();

    //
    //  Test for cancellation then disable cancellation of
    //  this thread.
    //

    pthread_testcancel();

    int save = PTHREAD_CANCEL_ENABLE;
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &save);

    int rc = pthread_mutex_lock(&(this->mutex));
    if (0 != rc) {
        //
        //  The lock failed. We log an error and return the
        //  cancel state of this thread to its prior state.
        //
        logger.error("%s[%d]: pthread_mutex_lock(%p)=%d\n",
            __FILE__, __LINE__, &(this->mutex), rc);
        pthread_setcancelstate(save, 0);
        return false;
    }

    //
    //  We're inside the mutex now and have exclusive access
    //  to this object.
    //

    if (0 == this->level) {
        this->identity = platform.identity();
        this->state = save;
    }

    if (intmaxof(unsigned int) > this->level) {
        ++this->level;
    } else {
        logger.error("%s[%d]: (%p)->level=0x%x\n",
            __FILE__, __LINE__, this, level);
    }

    return true;
}


//
//  Unlock.
//
bool Mutex::end() {
    Platform& platform = Platform::instance();
    Logger& logger = platform.logger();

    //
    //  We cannot assume we are in the mutex and have exclusive
    //  access to this object. Hence it could be changing as we
    //  look at it. Given a non-sequentially consistent memory
    //  model, the object might lie to us if we do not own it.
    //  But if we do own it, for sure the checks below will pass.
    //

    int before = this->level;
    if (0 == before) {
        logger.error("%s[%d]: level %d==%d\n",
            __FILE__, __LINE__, before, 0);
        return false;
    }

    identity_t owner = this->identity;
    identity_t me = platform.identity();
    if (owner != me) {
        logger.error("%s[%d]: identity 0x%016llx!=0x%016llx\n",
            __FILE__, __LINE__, owner, me);
        return false;
    }

    //
    //  We're pretty sure we are in the mutex and have exclusive
    //  access to this object.
    //

    int restore = this->state;
    --this->level;

    int rc = pthread_mutex_unlock(&(this->mutex));
    if (0 != rc) {
        //
        //  The unlock failed. We return this object to its
        //  prior state since we still presumably have exclusive
        //  access to it.
        //
        logger.error("%s[%d]: pthread_mutex_unlock(%p)=%d\n",
            __FILE__, __LINE__, &(this->mutex), rc);
        this->level = before;
        this->identity = owner;
        this->state = restore;
        return false;
    }

    //
    //  If we are exiting this mutex, restore the cancel state
    //  of this thread to its original state upon entry to the
    //  mutex and test for cancellation.
    //

    if (0 == before) {
        pthread_setcancelstate(restore, 0);
        pthread_testcancel();
    }

    return true;
}


//
//  Show this object on the output object.
//
void Mutex::show(int /* level */, Output* display, int indent) const {
    Platform& pl = Platform::instance();
    Print printf(display);
    Dump dump(display);
    const char* sp = printf.output().indentation(indent);
    char component[sizeof(__FILE__)];
    printf("%s%s(%p)[%lu]:\n",
        sp, pl.component(__FILE__, component, sizeof(component)),
        this, sizeof(*this));
    printf("%s mutex:\n", sp);
    dump.words(&(this->mutex), sizeof(this->mutex), false, 0, indent + 2);
    printf("%s mutexattr:\n", sp);
    dump.words(&(this->mutexattr), sizeof(this->mutexattr), false, 0,
        indent + 2);
    printf("%s identity=0x%016llx\n", sp, this->identity);
    printf("%s level=%u%s\n",
        sp, this->level,
        (0 == this->level) ? "=UNLOCKED" : "=LOCKED");
    printf("%s state=%d%s\n",
        sp, this->state,
        (PTHREAD_CANCEL_ENABLE == this->state)
            ? "=PTHREAD_CANCEL_ENABLE"
            : (PTHREAD_CANCEL_DISABLE == this->state)
                ? "=PTHREAD_CANCEL_DISABLE" : "");
}


#include "com/diag/desperado/End.h"
