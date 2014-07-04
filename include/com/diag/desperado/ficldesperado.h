#ifndef _COM_DIAG_DESPERADO_FICLDESPERADO_H_
#define _COM_DIAG_DESPERADO_FICLDESPERADO_H_

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
 *  This module eliminates a dependancy on the Desperado (or any other)
 *  library by dependency injection: the dependencies on the platform
 *  (Desperado, in this case) are established at run-time by inserting
 *  the appropriate addresses into the pointer variables. If no dependencies
 *  are required, the defaults are used.
 *
 *  @author Chip Overclock (coverclock@diag.com)
 *
 *
 */


#include "ficl.h"


#if defined(__cplusplus)
extern "C" {
#endif

typedef void (*FiclCallbackDefaultTextOutFuncPtr)(ficlCallback*, char* text);
typedef void* (*FiclMallocFuncPtr)(size_t size);
typedef void (*FiclFreeFuncPtr)(void* p);
typedef void* (*FiclReallocFuncPtr)(void* p, size_t size);
typedef int (*FiclDictionaryLockFuncPtr)(ficlDictionary* dict, short inc);

extern void setFiclCallbackDefaultTextOutPointer(FiclCallbackDefaultTextOutFuncPtr p);
extern void setFiclMallocPointer(FiclMallocFuncPtr p);
extern void setFiclFreePointer(FiclFreeFuncPtr p);
extern void setFiclReallocPointer(FiclReallocFuncPtr p);
extern void setFiclDictionaryLockPointer(FiclDictionaryLockFuncPtr p);

#if defined(__cplusplus)
}
#endif

#endif
