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
 *  are required, the defaults are used. (Yes, this is like the v-table in
 *  C++.)
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "ficl.h"
#include "desperado.h"

/******************************************************************************/

static void defOut(ficlCallback* callback, char* message) {
    FICL_IGNORE(callback);
    if (message != 0)
        fputs(message, stdout);
    else
        fflush(stdout);
    return;
}

static void* defMalloc(size_t size) {
    return malloc(size);
}

static void defFree(void* p) {
    free(p);
}

static void* defRealloc(void* p, size_t size) {
    return realloc(p, size);
}

static int defLock(ficlDictionary* dict, short inc) {
	return 0;
}

/******************************************************************************/

static FiclCallbackDefaultTextOutFuncPtr ficlCallbackDefaultTextOutPointer = defOut;
static FiclMallocFuncPtr ficlMallocPointer = defMalloc;
static FiclFreeFuncPtr ficlFreePointer = defFree;
static FiclReallocFuncPtr ficlReallocPointer = defRealloc;
static FiclDictionaryLockFuncPtr ficlDictionaryLockPointer = defLock;

/******************************************************************************/

void setFiclCallbackDefaultTextOutPointer(FiclCallbackDefaultTextOutFuncPtr p) {
    ficlCallbackDefaultTextOutPointer = p;
}

void setFiclMallocPointer(FiclMallocFuncPtr p) {
    ficlMallocPointer = p;
}

void setFiclFreePointer(FiclFreeFuncPtr p) {
    ficlFreePointer = p;
}

void setFiclReallocPointer(FiclReallocFuncPtr p) {
    ficlReallocPointer = p;
}

void setFiclDictionaryLockPointer(FiclDictionaryLockFuncPtr p) {
    ficlDictionaryLockPointer = p;
}

/******************************************************************************/

void ficlCallbackDefaultTextOut(ficlCallback* cback, char* text) {
	(*ficlCallbackDefaultTextOutPointer)(cback, text);
}

void* ficlMalloc(size_t size) {
	return (*ficlMallocPointer)(size);
}

void ficlFree(void* p) {
	(*ficlFreePointer)(p);
}

void* ficlRealloc(void* p, size_t size) {
	return (*ficlReallocPointer)(p, size);
}

#if defined(FICL_MULTITHREAD)
int ficlDictionaryLock(ficlDictionary* dict, short inc) {
	return (*ficlDictionaryLockPointer)(dict, inc);
}
#endif

/******************************************************************************/

/*
 * These functions in Ficl 4.1.0 were not in Ficl 4.0.31. There is no equivalent
 * to them in Platform so for now we just implement them directly.
 */

int ficlFileTruncate(ficlFile *ff, ficlUnsigned size)
{
    return ftruncate(fileno(ff->f), size);
}

int ficlFileStatus(char *filename, int *status)
{
    struct stat statbuf;
    if (stat(filename, &statbuf) == 0)
    {
        *status = statbuf.st_mode;
        return 0;
    }
    *status = ENOENT;
    return -1;
}

long ficlFileSize(ficlFile *ff)
{
    struct stat statbuf;
    if (ff == NULL)
        return -1;

    statbuf.st_size = -1;
    if (fstat(fileno(ff->f), &statbuf) != 0)
        return -1;

    return statbuf.st_size;
}

/******************************************************************************/

void ficlSystemCompilePlatform(ficlSystem *system)
{
    return;
}
