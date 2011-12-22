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


//
//  Constructor.
//
Mutex::Mutex() :
    identity(0),
    level(0),
    uncancellable(false),
    state(PTHREAD_CANCEL_ENABLE)
{
	pthread_spin_init(&(this->spin), 0);
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
    pthread_spin_destroy(&(this->spin));
}


//
//  Lock.
//
bool Mutex::begin(bool block) {
	bool result = false;

	do {

		// We cannot access any of the variables in this object, other than the
		// mutex itself, until we lock the mutex. I'm also assuming the mutex
		// lock does some kind of memory barrier.

		int rc = pthread_mutex_lock(&(this->mutex));
		if (0 != rc) {
			break;
		}

		// If this is the first level of a possibly recursive mutex lock,
		// initialize all the fields in the object. We relying on the
		// fact that cancellation is deferred and there are no cancellation
		// points between the mutex lock and the set cancel state.

		if (0 == this->level) {
			this->identity = pthread_self();
			this->uncancellable = block;
			if (block) {
				int save = PTHREAD_CANCEL_ENABLE;
				pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &save);
				this->state = save;
			}
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

		// We don't know yet whether or not we own this mutex.
		// We can't allow memory to change while we look at the following
		// fields. So we force any other threads on other processors to
		// busy wait until we're done. We must not perform any blocking
		// operations until we release the spin lock. I'm also assuming
		// the spin lock does some kind of memory barrier.

		pthread_spin_lock(&(this->spin));

		bool valid = (0 != pthread_equal(this->identity, pthread_self())) && (0 < this->level);

		pthread_spin_unlock(&(this->spin));

		if (!valid) {
			break;
		}

		// We now know we own this mutex. But once we unlock it, we can't make
		// any assumptions about the state of any variables in this object. So
		// we make local copies of them to use following the unlock.

		--this->level;

		int nesting = this->level;
		bool block = this->uncancellable;
		int restore = this->state;

		int rc = pthread_mutex_unlock(&(this->mutex));
		if (0 != rc) {
			++this->level;
			break;
		}

		// We waited until now to set the cancel state so we didn't have to
		// restore it in case the mutex unlock failed.

		if ((0 == nesting) && block) {
			int dontcare;
			pthread_setcancelstate(restore, &dontcare);
		}

		result = true;

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
    printf("%s identity=0x%08x\n", sp, this->identity);
    printf("%s level=%u%s\n",
        sp, this->level,
        (0 == this->level) ? "=UNLOCKED" : "=LOCKED");
    printf("%s uncancellable=%d%s\n",
        sp, this->uncancellable,
        this->uncancellable ? "=UNCANCELLABLE" : "=CANCELLABLE");
    printf("%s state=%d%s\n",
        sp, this->state,
        (PTHREAD_CANCEL_ENABLE == this->state)
            ? "=PTHREAD_CANCEL_ENABLE"
            : (PTHREAD_CANCEL_DISABLE == this->state)
                ? "=PTHREAD_CANCEL_DISABLE" : "");
}


#include "com/diag/desperado/End.h"
