/* vim: set ts=4 expandtab shiftwidth=4: */

/******************************************************************************

    Copyright 2006 Digital Aggregates Corporation, Colorado, USA.
    This file is part of the Digital Aggregates Desperado Library.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

******************************************************************************/

package com.diag.desperado;

/**
 * This class uses JNI to extend the Desperado Platform into the Java world.
 *
 * @author Chip Overclock (coverclock@diag.com)
 */
public class Platform {

    /**
     * Return the platform frequency in units of Hertz or eqivalently
     * platform ticks per second.
     *
     *  @return the number platform ticks per second.
     */
    public static native long frequency();

    /**
     * Return the platform time in units of platform ticks.
     * @return the number platform ticks since the epoch.
     */
    public static native long time();

    /**
     * Return the elapsed time since Platform creation in units of
     * platform ticks.
     * @return the number platform ticks since Platform creation.
     */
    public static native long elapsed();

    /**
     * Return the unique Platform identity.
     * @return the Platform identity.
     */
    public static native long identity();

    /**
     * Return the Platform name.
     * @return the Platform name.
     */
    public static native String platform();

    /**
     * Return the Platform target name.
     * @return the target name.
     */
    public static native String target();

    /**
     * Return the Platform host name.
     * @return the host name.
     */
    public static native String host();

    /**
     * Emit the specified String on the Platform output functor.
     * @param string is the String.
     * @return the number of characters output.
     */
    public static native int print(String string);

    /**
     * Emit the specified String on the Platform error functor.
     * @param string is the String.
     * @return the number of characters output.
     */
    public static native int error(String string);

}
