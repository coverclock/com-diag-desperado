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
#include "Linux.h"
#elif defined(DESPERADO_PLATFORM_IS_Cygwin)
#include "Cygwin.h"
#elif defined(DESPERADO_PLATFORM_IS_Diminuto)
#include "Diminuto.h"
#else
#include "Platform.h"
#endif

Platform* platform_factory_cache = 0;


/**
 *  Return a Desperado Platform object of the appropriate derived class.
 *
 *  On the uClibc-based Diminuto platform, there is either a bug in the
 *  arm-linux-g++ compiler, or a very subtle bug in this code. The store
 *  to the platform_factory_cache is only there to force the compiler to
 *  generate code to implement the reference; without it (or some other
 *  forcing function, like printing the address of the reference to
 *  standard error), this function core dumps with a Segmentation Fault.
 *  Turning off optimization does not fix this.
 * 
 *  @return a reference to the newly created Platform object.
 */
Platform& platform_factory() {
    DESPERADO_PLATFORM_CLASS* derived = new DESPERADO_PLATFORM_CLASS;
    Platform* base = derived;
    Platform& result = *base;
    platform_factory_cache = &result;
    return result;
}
