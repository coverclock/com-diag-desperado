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

#include <vector>
#include "Ratio.h"

#include "Begin.h"

Ratio & Ratio::normalize()
{
    // Estimate the smaller square root.

	typedef int Base;
    Base nup = this->nu < 0 ? -this->nu : this->nu;
    Base dep = this->de < 0 ? -this->de : this->de;
    Base limit = (nup < dep) ? nup : dep;
    Base root = 0;

    while (limit > 0) {
        root = (root << 1) | 0x1;
        limit = limit >> 2;
    }

    // Generate a prime less than the root.

	typedef std::vector<Base> Vector;
	Vector primes;
	Vector::const_iterator here;
	Vector::const_iterator end;

    for (Base factor = 2; factor <= root; ++factor) {

		here = primes.begin();
		end = primes.end();
		while (here != end) {
			if ((factor % (*here)) == 0) {
				break;
			}
			++here;
		}

        // Factor out the prime.

		if (here == end) {
			primes.push_back(factor);
            while (((this->nu % factor) == 0) && ((this->de % factor) == 0)) {
                this->nu /= factor;
                this->de /= factor;
            }
		}

	}

    return *this;	
}

#include "End.h"
