/* vim: set ts=4 expandtab shiftwidth=4: */

/******************************************************************************

    Copyright 2008 Digital Aggregates Corp., Arvada CO 80001-0587, USA.
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
 *  Implements the platform factory.
 *
 *  @see    Platform
 */


#if defined(DESPERADO_PLATFORM_IS_Linux)
#include "desperado/Linux.h"
typedef Linux Host;
#elif defined(DESPERADO_PLATFORM_IS_Cygwin)
#include "desperado/Cygwin.h"
typedef Cygwin Host;
#elif defined(DESPERADO_PLATFORM_IS_Diminuto)
#include "desperado/Diminuto.h"
typedef Diminuto Host;
#elif defined(DESPERADO_PLATFORM_IS_Arroyo)
#include "desperado/Arroyo.h"
typedef Arroyo Host;
#else
#error DESPERADO_PLATFORM_IS_* not defined!
#endif
#include "desperado/cxxcapi.h"


CXXCAPI Platform* platform_factory(void);


/*
 * This must be global, otherwise the compiler will optimize it out.
 * Optimizing it out causes a segmentation fault on the uClibc ARM
 * Linux platform. That's the only reason it's here.
 */
Platform* platform_factory_cache = 0;


/**
 *  Return a Desperado Platform object of the appropriate derived class.
 *
 *  @return a reference to the newly created Platform object.
 */
CXXCAPI Platform* platform_factory() {
    delete platform_factory_cache;
    platform_factory_cache = new Host;
    return platform_factory_cache;
}
