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
 *  Implements the BandwidthThrottle unit test.
 *
 *  @see    BandwidthThrottle
 *
 *  @author Chip Overclock (coverclock@diag.com)
 *
 *
 */

#include <sys/time.h>
#include "com/diag/desperado/UnitTest.h"
#include "com/diag/desperado/generics.h"
#include "com/diag/desperado/BandwidthThrottle.h"
#include "com/diag/desperado/BandwidthThrottle.h"
#include "com/diag/desperado/Meter.h"
#include "com/diag/desperado/Meter.h"
#include "com/diag/desperado/Print.h"
#include "com/diag/desperado/Print.h"
#include "com/diag/desperado/Platform.h"
#include "com/diag/desperado/Platform.h"
#include "com/diag/desperado/Ticks.h"
#include "com/diag/desperado/Ticks.h"
#include "com/diag/desperado/Desperado.h"

static BandwidthThrottle staticBandwidthThrottle;

int bandwidth_exercise(Throttle& throttle, size_t iterations) {
    Print printf(Platform::instance().output());
    Print errorf(Platform::instance().error());
    int errors = 0;
    ticks_t count = 0;
    ticks_t clock = 0;
    ticks_t delay;
    bool ok;
    bool alarmed;
    Ticks ticks;
    uint64_t seconds;
    uint32_t nanoseconds;

    size_t size[] = {
        1,
        10,
        100,
        1000,
        10000,
        100000,
        1000000,
        10000000,
        100000000,
        1000000000
    };
    size_t index = 0;

    throttle.reset(clock);
    throttle.show();
    
    for (size_t ii = 0; ii < iterations; ++ii) {
        delay = throttle.admissible(clock);
        while (0 < delay) {
            if (ii == 0) {
                errorf("%s[%d]: (%llu!=%llu)!\n",
                    __FILE__, __LINE__, delay, 0);
                throttle.show();
                ++errors;
            }
            ok = throttle.rollback();
            if (!ok) {
                errorf("%s[%d]: (%d!=%d)!\n",
                    __FILE__, __LINE__, ok, true);
                throttle.show();
                ++errors;
            }
            clock += delay;
            delay = throttle.admissible(clock);
            if (0 < delay) {
                errorf("%s[%d]: (%llu!=%llu)!\n",
                    __FILE__, __LINE__, delay, 0);
                throttle.show();
                ++errors;
            }
        }
        ok = throttle.commit(size[index]);
        if (!ok) {
            errorf("%s[%d]: (%d!=%d)!\n",
                __FILE__, __LINE__, ok, true);
            throttle.show();
            ++errors;
        }
        count += size[index];
        ++index;
        if (index >= countof(size)) { index = 0; }
        alarmed = throttle.isAlarmed();
        if (alarmed) {
            errorf("%s[%d]: (%d!=%d)!\n",
                __FILE__, __LINE__, alarmed, false);
            throttle.show();
            ++errors;
        }
    }

    delay = throttle.admissible(clock);
    clock += delay;
    ticks.seconds(clock, seconds, nanoseconds);
    ticks_t hz = throttle.frequency();
    ticks_t effective = (hz * count) / clock;
    ticks_t fraction = (((hz * count) % clock) * 1000000000LL) / clock;
    printf("%s[%d]: effective %llu/%llu.%09lu %llu.%09lu\n",
        __FILE__, __LINE__, count, seconds, nanoseconds, effective, fraction);

    delay = throttle.admissible(clock);
    while (0 == delay) {
        ok = throttle.commit();
        if (!ok) {
            errorf("%s[%d]: (%d!=%d)!\n",
                __FILE__, __LINE__, ok, true);
            throttle.show();
            ++errors;
        }
        delay = throttle.admissible(clock);
    }
    throttle.commit();
    alarmed = throttle.isAlarmed();
    if (!alarmed) {
        errorf("%s[%d]: (%d!=%d)!\n",
            __FILE__, __LINE__, alarmed, true);
        throttle.show();
        ++errors;
    }

    throttle.show();

    return errors;
}

CXXCAPI int unittestBandwidthThrottle(
    void*,
    unsigned int pbps,
    unsigned int jt,
    unsigned int sbps,
    unsigned int mbs,
    unsigned int iterations
) {
    Print printf(Platform::instance().output());
    Print errorf(Platform::instance().error());
    int errors = 0;

    BandwidthThrottle constant(pbps, jt);
    BandwidthThrottle variable(pbps, jt, sbps, mbs);
    BandwidthThrottle throttle2;
    BandwidthThrottle throttle3;
    BandwidthThrottle throttle4 = variable;

    printf("%s[%d]: begin\n", __FILE__, __LINE__);

    printf("%d[%d]: pbps=%d jt=%d sbps=%d mbs=%d\n",
        __FILE__, __LINE__, pbps, jt, sbps, mbs);

    ::staticBandwidthThrottle.show();

    printf("%s[%d]: constructors\n", __FILE__, __LINE__);

    constant.show();
    variable.show();
    throttle2.show();
    throttle3 = constant;
    throttle3.show();
    throttle4.show();

    printf("%s[%d]: time\n", __FILE__, __LINE__);

    constant.time();
    ticks_t hz = constant.frequency();
    if (hz == 0) {
        errorf("%s[%d]: (%llu==%llu)!\n",
            __FILE__, __LINE__, hz, 0);
        constant.show();
        ++errors;
    }

    printf("%s[%d]: constant\n", __FILE__, __LINE__);
    errors += bandwidth_exercise(constant, iterations);

    printf("%s[%d]: constant reset\n", __FILE__, __LINE__);
    errors += bandwidth_exercise(constant, iterations);

    printf("%s[%d]: constant initialize\n", __FILE__, __LINE__);
    BandwidthThrottle newconstant(pbps, jt);
    constant = newconstant;
    errors += bandwidth_exercise(constant, iterations);

    printf("%s[%d]: variable\n", __FILE__, __LINE__);
    errors += bandwidth_exercise(variable, iterations);

    printf("%s[%d]: variable reset\n", __FILE__, __LINE__);
    errors += bandwidth_exercise(variable, iterations);

    printf("%s[%d]: variable initialize\n", __FILE__, __LINE__);
    BandwidthThrottle newvariable(pbps, jt, sbps, mbs);
    variable = newvariable;
    errors += bandwidth_exercise(variable, iterations);

    printf("%s[%d]: end errors=%d\n",
        __FILE__, __LINE__, errors);

    return errors;
}
