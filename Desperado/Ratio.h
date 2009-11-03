#ifndef _COM_DIAG_DESPERADO_RATIO_H_
#define _COM_DIAG_DESPERADO_RATIO_H_

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
 *  Declares the Ratio class.
 */


#include "Begin.h"

/**
 *  @author coverclock@diag.com (Chip Overclock)
 */
class Ratio {

public:

    Ratio(int nn = 0, int dd = 1)
    : nu(nn)
    , de(dd)
    {}

    ~Ratio() {}

    int numerator() {
        return nu;
    }

    int denominator() {
        return de;
    }

    void numerator(int nn) {
        nu = nn;
    }

    void denominator(int dd) {
        de = dd;
    }

    void normalize() {
    }

    Ratio(const Ratio & that) {
        this->nu = that.nu;
        this->de = that.de;
    }

    Ratio & operator =(const Ratio & that) {
        if (this != &that) {
            this->nu = that.nu;
            this->de = that.de;
        }
        return *this;
    }

    Ratio & operator +=(const Ratio & that) {
        this->nu = (this->nu * that.de) + (that.nu * this->de);
        this->de = (this->de * that.de) + (that.de * this->de);
        return *this;
    }

    Ratio & operator -=(const Ratio & that) {
        this->nu = (this->nu * that.de) - (that.nu * this->de);
        this->de = (this->de * that.de) - (that.de * this->de);
        return *this;
    }

    Ratio & operator *=(const Ratio & that) {
        this->nu *= that.nu;
        this->de *= that.de;
        return *this;
    }

    Ratio & operator /=(const Ratio & that) {
        this->nu *= that.de;
        this->de *= that.nu;
        return *this;
    }

    Ratio operator +(const Ratio &that) {
        Ratio temp = *this;
        temp += that;
        return that;
    }

    Ratio operator -(const Ratio &that) {
        Ratio temp = *this;
        temp -= that;
        return that;
    }

    Ratio operator *(const Ratio &that) {
        Ratio temp = *this;
        temp *= that;
        return that;
    }

    Ratio operator /(const Ratio &that) {
        Ratio temp = *this;
        temp /= that;
        return that;
    }

    bool operator ==(const Ratio &that) {
        int nu1 = (this->nu * that.de);
        int nu2 = (that.nu * this->de);
        return nu1 == nu2;
    }

    bool operator !=(const Ratio &that) {
        return !(*this == that);
    }

private:

	int nu;

    int de;

};


#include "End.h"


#if defined(DESPERADO_HAS_UNITTESTS)
#include "cxxcapi.h"
/**
 *  Run the Ratio unit test.
 *  
 *  @return the number of errors detected by the unit test.
 */
CXXCAPI int unittestRatio(void);
#endif


#endif

