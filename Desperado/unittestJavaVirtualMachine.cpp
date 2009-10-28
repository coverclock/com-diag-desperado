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

    $Id: unittestJavaVirtualMachine.cpp,v 1.7 2006/09/07 21:38:12 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the JavaVirtualMachine unit test.
 *
 *  @see    JavaVirtualMachine
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.7 $
 *
 *  @date   $Date: 2006/09/07 21:38:12 $
 */

#if defined(DESPERADO_HAS_JAVA)

#include "UnitTest.h"
#include "target.h"
#include "JavaVirtualMachine.h"
#include "JavaVirtualMachine.h"
#include "java.h"
#include "java.h"
#include "cxxjapi.h"
#include "cxxjapi.h"
#include "errno.h"
#include "Print.h"
#include "Platform.h"
#include "Desperado.h"

static JavaVirtualMachine staticJvm;

extern "C" int unittestJavaVirtualMachine(bool debug) {
    Print printf(Platform::instance().output());
    Print errorf(Platform::instance().error());
    int errors = 0;

    printf("%s[%d]: begin\n", __FILE__, __LINE__);

    ::staticJvm.show();

    int rc;

#if 0
    printf("%s[%d]: lifecycle\n", __FILE__, __LINE__);

    {
        JavaVirtualMachine temp1;
        temp1.show();
    }

    {
        JavaVirtualMachine temp2;
        temp2.show();
        rc = temp2.create();
        if (rc != 0) {
            char message[80];
            errorf("%s[%d]: (%d!=%d) (%s)!\n",
                __FILE__, __LINE__, rc, 0,
                Platform::instance().errormessage(errno, message,
                    sizeof(message)));
            ++errors;
        }
        temp2.show();
    }

    {
        JavaVirtualMachine temp3;
        temp3.show();
        rc = temp3.create();
        if (rc != 0) {
            char message[80];
            errorf("%s[%d]: (%d!=%d) (%s)!\n",
                __FILE__, __LINE__, rc, 0,
                Platform::instance().errormessage(errno, message,
                    sizeof(message)));
            ++errors;
        }
        temp3.show();
        rc = temp3.destroy();
        if (rc != 0) {
            char message[80];
            errorf("%s[%d]: (%d!=%d) (%s)!\n",
                __FILE__, __LINE__, rc, 0,
                Platform::instance().errormessage(errno, message,
                    sizeof(message)));
            ++errors;
        }
    }
#endif

    printf("%s[%d]: nodebug\n", __FILE__, __LINE__);

    JavaVirtualMachine jvmnodebug;
    jvmnodebug.show();

    printf("%s[%d]: nodebug\n", __FILE__, __LINE__);

    JavaVirtualMachine jvmdebug(true, &(Platform::instance().error()));
    jvmdebug.show();

    JavaVirtualMachine* jvmp = debug ? &jvmdebug : &jvmnodebug;

    printf("%s[%d]: create\n", __FILE__, __LINE__);

    const char* options[4];
    int noptions = 0;
    if (debug)
    {
        options[noptions++] = "-verbose";
        options[noptions++] = "-verbose:gc";
        options[noptions++] = "-verbose:jni";
    };
    options[noptions++] = "-Djava.class.path=desperado.jar";

    rc = jvmp->create(options, noptions);
    if (rc != 0) {
        char message[80];
        errorf("%s[%d]: (%d!=%d) (%s)!\n",
            __FILE__, __LINE__, rc, 0,
            Platform::instance().errormessage(errno, message, sizeof(message)));
        ++errors;
    }

    jvmp->show();

    do {
        if (rc != 0) {
            break;
        }
        printf("%s[%d]: invoke\n", __FILE__, __LINE__);
        JNIEnv* jenv = jvmp->getJNIEnv();
        if (jenv == 0) {
            errorf("%s[%d]: (0x%x==0)!\n", __FILE__, __LINE__, jenv);
            ++errors;
            break;
        }
        jclass cls = jenv->FindClass("com/diag/desperado/UnitTestJavaVirtualMachine");
        if (cls == 0) {
            errorf("%s[%d]: (0x%x==0)!\n", __FILE__, __LINE__, cls);
            ++errors;
            break;
        }
        // javap -s -p UnitTestJavaVirtualMachine
        jmethodID mid = jenv->GetStaticMethodID(cls, "test", "(J)J");
        if (mid == 0) {
            errorf("%s[%d]: (0x%x==0)!\n", __FILE__, __LINE__, mid);
            ++errors;
            break;
        }
        ticks_t platformticks = Platform::instance().time();
        jlong javaticks = jenv->CallStaticLongMethod(cls, mid, platformticks);
        ticks_t difference = javaticks - platformticks;
        printf("%s[%d]: platformticks=%llu javaticks=%llu difference=%llu\n",
            __FILE__, __LINE__, platformticks, javaticks, difference);
        ticks_t frequency = Platform::instance().frequency();
        ticks_t maximum = frequency / 100; // Somewhat arbitrary choice
        if (difference > maximum) {
            errorf("%s[%d]: (%llu>%llu)!\n",
                __FILE__, __LINE__, difference, maximum);
            ++errors;
            break;
        }
    } while (false);

    printf("%s[%d]: destroy\n", __FILE__, __LINE__);

    rc = jvmp->destroy();
    if (rc != 0) {
        char message[80];
        errorf("%s[%d]: (%d!=%d) (%s)!\n",
            __FILE__, __LINE__, rc, 0,
            Platform::instance().errormessage(errno, message, sizeof(message)));
        ++errors;
    }

    jvmp->show();

    printf("%s[%d]: end errors=%d\n",
        __FILE__, __LINE__, errors);

    return errors;
}

#endif
