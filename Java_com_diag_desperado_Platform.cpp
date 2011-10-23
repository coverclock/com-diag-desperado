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

    $Id: Java_com_diag_desperado_Platform.cpp,v 1.3 2006/09/11 21:38:39 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the Platform Java API (such as it is). Note that the
 *  Java jni.h header file offers very different interfaces to C++
 *  versus C translations units.
 *
 *  @see    Platform
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.3 $
 *
 *  @date   $Date: 2006/09/11 21:38:39 $
 */


#if defined(DESPERADO_HAS_JAVA)


#include "com/diag/desperado/target.h"
#include "com/diag/desperado/Platform.h"
#include "com/diag/desperado/Output.h"
#include "com/diag/desperado/Desperado.h"
#include "com_diag_desperado_Platform.h"
#include "jni.h"


JNIEXPORT jlong JNICALL Java_com_diag_desperado_Platform_frequency(
    JNIEnv*,
    jclass
) {
    return Platform::instance().frequency();
}


JNIEXPORT jlong JNICALL Java_com_diag_desperado_Platform_time(
    JNIEnv*,
    jclass
) {
    return Platform::instance().time();
}


JNIEXPORT jlong JNICALL Java_com_diag_desperado_Platform_elapsed(
    JNIEnv*,
    jclass
) {
    return Platform::instance().elapsed();
}


JNIEXPORT jlong JNICALL Java_com_diag_desperado_Platform_identity(
    JNIEnv*,
    jclass
) {
    return Platform::instance().identity();
}

static jstring enstring(
    JNIEnv* env,
    const char* name
) {
    return env->NewStringUTF(name);
}


JNIEXPORT jstring JNICALL Java_com_diag_desperado_Platform_platform(
    JNIEnv* env,
    jclass
) {
    return enstring(env, Platform::instance().platform());
}


JNIEXPORT jstring JNICALL Java_com_diag_desperado_Platform_target(
    JNIEnv* env,
    jclass
) {
    return enstring(env, Platform::instance().target());
}


JNIEXPORT jstring JNICALL Java_com_diag_desperado_Platform_host(
    JNIEnv* env,
    jclass
) {
    return enstring(env, Platform::instance().host());
}


static jint output(
    JNIEnv* env,
    Output& out,
    jstring string
) {
    char buffer[256];
    int length = env->GetStringLength(string);
    size_t size = (length >= 0) ? length : 0;
    size_t effective = (size >= sizeof(buffer)) ? sizeof(buffer) : size;
    env->GetStringUTFRegion(string, 0, effective, buffer);
    return (out)(buffer, effective);
}


JNIEXPORT jint JNICALL Java_com_diag_desperado_Platform_print(
    JNIEnv* env,
    jclass,
    jstring string
) {
    return output(env, Platform::instance().output(), string);
}


JNIEXPORT jint JNICALL Java_com_diag_desperado_Platform_error(
    JNIEnv* env,
    jclass,
    jstring string
) {
    return output(env, Platform::instance().error(), string);
}


#endif
