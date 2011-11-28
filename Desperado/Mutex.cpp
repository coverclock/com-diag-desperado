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
 *  Implements the Mutex class. This class can't make use of the Platform class
 *  during construction, begin(), or end(), because architecturally it sits
 *  below the Platform class.
 *
 *  @see    Mutex
 *
 *  @author Chip Overclock (coverclock@diag.com)
 */


#include <unistd.h>
#include "com/diag/desperado/generics.h"
#include "com/diag/desperado/Mutex.h"
#include "com/diag/desperado/Print.h"
#include "com/diag/desperado/Dump.h"
#include "com/diag/desperado/Platform.h"


#include "com/diag/desperado/Begin.h"


static uint64_t self() {
    pid_t pid = ::getpid();
    pthread_t self = pthread_self();
    uint64_t identity = pid;
    return (identity << widthof(self)) | self;
}


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
	bool result = false;

	do {

		if (intmaxof(uint64_t) <= this->level) {
			break;
		}

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
			//  The lock failed. We return the cancel state of this thread
			//	to its prior state.
			//
			pthread_setcancelstate(save, 0);
			break;
		}

		//
		//  We're inside the mutex now and have exclusive access
		//  to this object.
		//

		if (0 == this->level) {
			this->identity = self();
			this->state = save;
		}

		++this->level;

		result = true;

	} while (false);

    return result;
}


//
//  Unlock.
//
bool Mutex::end() {
	bool result = false;

	do {

		//
		//  We cannot assume we are in the mutex and have exclusive
		//  access to this object. Hence it could be changing as we
		//  look at it. Given a non-sequentially consistent memory
		//  model, the object might lie to us if we do not own it.
		//  But if we do own it, for sure the checks below will pass.
		//

		int before = this->level;
		if (0 == before) {
			break;
		}

		uint64_t owner = this->identity;
		uint64_t me = self();
		if (owner != me) {
			break;
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
			this->level = before;
			this->identity = owner;
			this->state = restore;
			break;
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

	} while (false);

    return result;
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
    printf("%s level=%llu%s\n",
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
