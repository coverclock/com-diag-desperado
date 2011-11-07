#ifndef _COM_DIAG_DESPERADO_FICLLOCAL_H_
#define _COM_DIAG_DESPERADO_FICLLOCAL_H_

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
 *  Contains the basic type and preprocessor definitions necessary
 *  to support the Ficl FORTH interpreter under the FiclSystem and
 *  FiclMachine classes in the Desperado library.
 *  It is used as the ficllocal header file when compiling
 *  the Ficl interpreter itself. You may want or need to modify this
 *  to fit your own application.
 *
 *  @author Chip Overclock (coverclock@diag.com)
 *
 *
 */


#include <stdint.h>


#if defined(FICL_ANSI)
#undef FICL_ANSI
#endif

#if defined(_WIN32)
#undef _WIN32
#endif

#if defined(FREEBSD_ALPHA)
#undef FREEBSD_ALPHA
#endif

#if defined(linux)
#undef linux
#endif

#define FICL_WANT_FILE                  (0)
#define FICL_WANT_MULTITHREADED         (1)
#define FICL_MULTITHREAD                (1)
#define FICL_PLATFORM_ARCHITECTURE      "diag.com/Desperado/target"
#define FICL_PLATFORM_OS                "diag.com/Desperado/Platform"
#define FICL_PLATFORM_HAS_2INTEGER      (1)
#define FICL_PLATFORM_INLINE            inline
#define FICL_PLATFORM_BASIC_TYPES

typedef int8_t ficlInteger8;
typedef uint8_t ficlUnsigned8;
typedef int16_t ficlInteger16;
typedef uint16_t ficlUnsigned16;
typedef int32_t ficlInteger32;
typedef uint32_t ficlUnsigned32;
typedef int64_t ficlInteger64;
typedef uint64_t ficlUnsigned64;

typedef ficlInteger32 ficlInteger;
typedef ficlUnsigned32 ficlUnsigned;
typedef float ficlFloat;

typedef ficlInteger64 ficl2Integer;
typedef ficlUnsigned64 ficl2Unsigned;


#endif
