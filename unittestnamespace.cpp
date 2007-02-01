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

    $Id: unittestnamespace.cpp,v 1.6 2007/01/31 18:47:47 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the namespace unit test.
 *
 *  This is a work in progress. I'm trying to understand how
 *  namespaces work in C++.
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.6 $
 *
 *  @date   $Date: 2007/01/31 18:47:47 $
 */


#include <stdint.h>
#include <sys/types.h>
#include <cstddef>
#include <cstring>
#include "stdio.h"
#include <new>

#if 0
namespace Desperado {
#endif

#include "assert.h"
#include "barrier.h"
#include "bool.h"
#include "cxxcapi.h"
#include "cxxjapi.h"
#include "debug.h"
#include "errno.h"
#include "exceptions.h"
#include "generics.h"
#include "java.h"
#include "littleendian.h"
#include "lowtohigh.h"
#include "reads.h"
#include "string.h"
#include "target.h"
#include "types.h"
#include "writes.h"
#include "Argument.h"
#include "Ascii.h"
#include "AtomicSeconds.h"
#include "Attribute.h"
#include "BufferInput.h"
#include "BufferOutput.h"
#include "CompoundThrottle.h"
#include "CellRateThrottle.h"
#include "Chain.h"
#include "CommonEra.h"
#include "Constant.h"
#include "Counters.h"
#include "Crc.h"
#include "CriticalSection.h"
#include "Date.h"
#include "DateTime.h"
#include "DaylightSavingTime.h"
#include "DescriptorInput.h"
#include "DescriptorOutput.h"
#include "DstAlways.h"
#include "DstEu.h"
#include "DstGeneric.h"
#include "DstNever.h"
#include "DstUs.h"
#include "DstUs1966.h"
#include "DstUs1986.h"
#include "DstUs2007.h"
#include "Dump.h"
#include "DumpInput.h"
#include "DumpOutput.h"
#include "Encode.h"
#include "Epoch.h"
#include "Escape.h"
#include "GeometricThrottle.h"
#include "FiclMachine.h"
#include "FiclSystem.h"
#include "Fifo.h"
#include "FileInput.h"
#include "FileOutput.h"
#include "GrayCode.h"
#include "Heap.h"
#include "Input.h"
#include "Iso3166.h"
#include "LeapSeconds.h"
#include "Link.h"
#include "Linux.h"
#include "LocalTime.h"
#include "Logger.h"
#include "Maximum.h"
#include "MemoryBarrier.h"
#include "Meter.h"
#include "Minimum.h"
#include "Mutex.h"
#include "NewCounters.h"
#include "NewFifo.h"
#include "Number.h"
#include "Output.h"
#include "PathInput.h"
#include "PathOutput.h"
#include "Platform.h"
#include "Print.h"
#include "README.h"
#include "Ram.h"
#include "SyslogOutput.h"
#include "Throttle.h"
#include "Ticks.h"
#include "Time.h"
#include "TimeStamp.h"
#include "TimeZone.h"
#include "Transliterator.h"
#include "Vintage.h"
#include "Word.h"

#if 0
}

namespace {
    int function1() {
        Desperado::Print printf;
        printf("%s[%d]: explicit\n", __FILE__, __LINE__);
        return 0;
    }
}

namespace {
    int function2() {
        using Desperado::Print;
        Print printf;
        printf("%s[%d]: explicit\n", __FILE__, __LINE__);
        return 0;
    }
}

namespace ComDiagDesperado = Desperado;

namespace {
    int function3() {
        ComDiagDesperado::Print printf;
        printf("%s[%d]: explicit\n", __FILE__, __LINE__);
        return 0;
    }
}

using namespace Desperado;

#endif

extern "C" int unittestnamespace() {
    Print printf;
    int errors = 0;

    printf("%s[%d]: begin\n", __FILE__, __LINE__);

#if 0
    errors += ::function1();
    errors += ::function2();
    errors += ::function2();
#endif

    printf("%s[%d]: end errors=%d\n", __FILE__, __LINE__, errors);

    return errors;
}
