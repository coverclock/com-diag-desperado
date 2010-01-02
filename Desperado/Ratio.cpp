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
 *  Implements the Ratio class.
 */

#include "Root.h"
#include "Primes.h"
#include "Ratio.h"

#include "Begin.h"

/*
 * We take care of all the special cases before the complicated stuff.
 */
Ratio * Ratio::normalize()
{
    if (this->de == 0) {

        // Do nothing: undefined.

    } else if (this->nu == 0) {

        this->de = 1;

    } else if (this->de == 1) {

        // Do nothing.

    } else if (this->nu == 1) {

        // Do nothing.

    } else if (this->de == -1) {

        this->nu = -this->nu;
        this->de = 1;

    } else if (this->nu == this->de) {

        this->nu = 1;
        this->de = 1;

    } else if (this->nu == -(this->de)) {

        this->nu = -1;
        this->de = 1;

    } else if ((absolute(this->nu) % absolute(this->de)) == 0) {

        this->nu /= this->de;
        this->de = 1;

    } else {

        // Estimate the square root of the smaller absolute value.

        Type nup = absolute(this->nu);
        Type dep = absolute(this->de);
        Type limit = root(minimum(nup, dep));

        // Get as least those primes as large as the limit.

        Primes primes(limit);

        // Factor out the primes.

        Primes::Iterator here = primes.begin();
        Primes::Iterator end = primes.end();

	    while ((here != end) && (*here <= limit)) {
            nup = absolute(this->nu);
            dep = absolute(this->de);
            while (((nup % *here) == 0) && ((dep % *here) == 0)) {
                this->nu /= *here;
                this->de /= *here;
                nup = absolute(this->nu);
                dep = absolute(this->de);
		    }
            ++here;
	    }

    }

    return this;	
}

#include "End.h"