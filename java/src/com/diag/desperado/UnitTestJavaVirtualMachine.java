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
 *  This class is part of the Desperado JavaVirtualMachine unit test.
 *
 * @author Chip Overclock (coverclock@diag.com)
 */
public class UnitTestJavaVirtualMachine  {

    /**
     * Ctor.
     */
    public UnitTestJavaVirtualMachine() {
    }

    /**
     *  Run the Java portion of the Desperado JavaVirtualMachine unit test.
     *  @param base is a prior platform time in units of platform ticks.
     *  @return the current platform time in units of platform ticks.
     */
    public static long test(long base) {

        String name = UnitTestJavaVirtualMachine.class.getCanonicalName() + ".java";
        String type = Platform.class.getCanonicalName();

        System.loadLibrary("ficl");
        System.loadLibrary("desperado");
        Platform.error(name + ": java.library.path=\"" + System.getProperty("java.library.path") + "\"\n");

        long frequency = Platform.frequency();
        Platform.print(name + ": " + type + ".frequency=" + frequency + "\n");

        long ticks = Platform.time();
        Platform.print(name + ": "  + type + ".time=" + ticks + "\n");

        long elapsed = Platform.elapsed();
        Platform.print(name + ": " + type + ".elapsed=" + elapsed + "\n");

        long identity = Platform.identity();
        Platform.print(name + ": " + type + ".identity=" + identity + "\n");

        String platform = Platform.platform();
        Platform.print(name + ": " + type + ".platform=\"" + platform + "\"\n");

        String target = Platform.target();
        Platform.print(name + ": " + type + ".target=\"" + target + "\"\n");

        String host = Platform.host();
        Platform.print(name + ": " + type + ".host=\"" + host + "\"\n");

        long difference = ticks - base;
        Platform.print(name + ": difference=" + difference + "\n");

        return ticks;
    }

    /**
     *  Run the test as a main program.
     *  @param args is an array of command line argument strings.
     */
    public static void main(String[] args) {
        int argn = 0;
        for (String arg : args) {
            System.out.println("arg[" + (argn++) + "]=\"" + arg + "\"");
        }
        test(0);
    }
}
