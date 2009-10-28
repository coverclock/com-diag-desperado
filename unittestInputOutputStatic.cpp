/* vim: set ts=4 expandtab shiftwidth=4: */

/******************************************************************************

    Copyright 2006 Digital Aggregates Corp., Arvada CO 80001-0587, USA.
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

    $Name:  $

    $Id: unittestInputOutputStatic.cpp,v 1.4 2006/08/04 20:42:46 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the InputOutput Static unit test.
 *
 *  @see    Input
 *  @see    Output
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.4 $
 *
 *  @date   $Date: 2006/08/04 20:42:46 $
 */


#include <cstdarg>
#include "errno.h"
#include "string.h"
#include "BufferInput.h"
#include "BufferInput.h"
#include "BufferOutput.h"
#include "BufferOutput.h"
#include "DescriptorInput.h"
#include "DescriptorInput.h"
#include "DescriptorOutput.h"
#include "DescriptorOutput.h"
#include "DumpInput.h"
#include "DumpInput.h"
#include "DumpOutput.h"
#include "DumpOutput.h"
#include "FileInput.h"
#include "FileInput.h"
#include "FileOutput.h"
#include "FileOutput.h"
#include "Input.h"
#include "Input.h"
#include "Output.h"
#include "Output.h"
#include "PathInput.h"
#include "PathInput.h"
#include "PathOutput.h"
#include "PathOutput.h"
#include "SyslogOutput.h"
#include "SyslogOutput.h"
#include "Print.h"
#include "Platform.h"
#include "Desperado.h"

static BufferInput staticBufferInput;
static BufferOutput staticBufferOutput;
static DescriptorInput staticDescriptorInput;
static DescriptorOutput staticDescriptorOutput;
static DumpInput staticDumpInput;
static DumpOutput staticDumpOutput;
static FileInput staticFileInput;
static FileOutput staticFileOutput;
static Input staticInput;
static Output staticOutput;
static PathInput staticPathInput;
static PathOutput staticPathOutput;
#if defined(DESPERADO_HAS_SYSLOG)
static SyslogOutput staticSyslogOutput;
#endif

extern "C" int unittestInputOutputStatic() {
    Print printf(Platform::instance().output());
    int errors = 0;

    printf("%s[%d]: begin\n", __FILE__, __LINE__);

    ::staticBufferInput.show();
    ::staticBufferOutput.show();
    ::staticDescriptorInput.show();
    ::staticDescriptorOutput.show();
    ::staticDumpInput.show();
    ::staticDumpOutput.show();
    ::staticFileInput.show();
    ::staticFileOutput.show();
    ::staticInput.show();
    ::staticOutput.show();
    ::staticPathInput.show();
    ::staticPathOutput.show();
#if defined(DESPERADO_HAS_SYSLOG)
    ::staticSyslogOutput.show();
#endif

    printf("%s[%d]: end errors=%d\n",
        __FILE__, __LINE__, errors);

    return errors;
}
