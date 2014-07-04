#ifndef _COM_DIAG_DESPERADO_JAVAVIRTUALMACHINE_H_
#define _COM_DIAG_DESPERADO_JAVAVIRTUALMACHINE_H_

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
 *  Declares the JavaVirtualMachine class.
 *
 *  @see    JavaVirtualMachine
 *
 *  @author Chip Overclock (coverclock@diag.com)
 *
 *
 */


#if defined(DESPERADO_HAS_JAVA)


extern "C" {
#   include "jni.h"
}
#include "com/diag/desperado/target.h"
#include "com/diag/desperado/Object.h"
#include "com/diag/desperado/Output.h"


#include "com/diag/desperado/Begin.h"

/**
 *  Creates, strarts and destroys a Java Virtual Machine.
 *
 *  N.B. Because of a limitation in the Sun implementation
 *  (see SDN bugs 4479303 and 4525299), it does not
 *  appear that you can actually create more than one
 *  JVM per Linux process, neither in parallel or
 *  sequentially, and destroying an existing JVM is
 *  also problematic. The API would certainly lead you
 *  to believe that multiple JVMs can exist concurrently,
 *  or at least sequentially. This issue exists at least
 *  through J2SE 1.5.
 *
 *  @author coverclock@diag.com (Chip Overclock)
 */
class JavaVirtualMachine : public Object {

public:

    /**
     *  Constructor. N.B. See the note above regarding a limitation in
     *  the Sun implementation.
     *
     *  @param  ign         if true causes the JVM to ignore invalid options.
     *
     *  @param  out         if non-null causes debug output to be printed.
     */
    explicit JavaVirtualMachine(bool ign = false, Output* out = 0);

    /**
     *  Destructor.
     */
    virtual ~JavaVirtualMachine();

    /**
     *  Creates the Java Virtual Machine.
     *
     *  @param  options     is a list of option strings passed to the
     *                      JNI_CreateJavaVM() call as if they were
     *                      passed on the command line of the java command.
     *
     *  @param  noptions    is the size of the options array.
     *
     *  @return the return code from the JNI_CreateJavaVM() call.
     */
    virtual int create(const char* options[] = 0, size_t noptions = 0);

    /**
     *  Destroys the Java Virtual Machine. Can only be called from the
     *  thread that started the JVM. Waits until all resources in the
     *  JVM have been cleaned up. N.B. see the note above regarding a
     *  limitation in the Sun implementation.
     */
    virtual int destroy();

    /**
     *  Return a pointer to the underlying Java Virtual Machine structure
     *  for this object. This pointer is necessary for some of the
     *  JNI functions.
     *
     *  @return a pointer to the underlying JavaVM, or null if none.
     */
    JavaVM* getJavaVM();

    /**
     *  Return a pointer to the underlying Java Native Interface Environment
     *  structure for this object. This pointer is necessary for many of
     *  the JNI functions.
     *
     *  @return a pointer to the underlying JNIEnv, or null if none.
     */
    JNIEnv* getJNIEnv();

    /**
     *  Displays internal information about this object to the specified
     *  output object. Useful for debugging and troubleshooting.
     *
     *  @param  level   sets the verbosity of the output. What this means
     *                  is object dependent. However, the level is passed
     *                  from outer to inner objects this object calls the
     *                  show methods of its inherited or composited objects.
     *
     *  @param display  points to the output object to which output is
     *                  sent. If null (zero), the default platform output
     *                  object is used as the effective output object. The
     *                  effective output object is passed from outer to
     *                  inner objects as this object calls the show methods
     *                  of its inherited and composited objects.
     *
     *  @param  indent  specifies the level of indentation. One more than
     *                  this value is passed from outer to inner objects
     *                  as this object calls the show methods of its
     *                  inherited and composited objects.
     */
    virtual void show(int level = 0, Output* display = 0, int indent = 0) const;

private:

    /**
     *  Copy constructor.
     *
     *  @param  that    refers to an R-value object of this type.
     */
    JavaVirtualMachine(const JavaVirtualMachine& that);

    /**
     *  Assignment operator.
     *
     *  @param  that    refers to an R-value object of this type.
     */
    JavaVirtualMachine& operator=(const JavaVirtualMachine& that);

    /**
     *  This points to the Java VM Option array for this object.
     */
    JavaVMOption* jopts;

    /**
     *  This is the Java VM Init Arguments for this object.
     */
    JavaVMInitArgs jargs;

    /**
     *  This points to the Java VM structure for this object.
     */
    JavaVM* jvm;

    /**
     *  This points to the JNI Environment structure for this object.
     */
    JNIEnv* jenv;

    /**
     *  If true, cause the JVM to ignore parameters it does not understand.
     */
    bool ignore;

    /**
     *  If non-null, print debugging information to this output object.
     */
    Output* output;
};


//
//  Return a pointer to the JVM for this JavaVirtualMachine, or null if none.
//
inline JavaVM* JavaVirtualMachine::getJavaVM() {
    return this->jvm;
}


//
//  Return a pointer to the JNI Environment, or null if none.
//
inline JNIEnv* JavaVirtualMachine::getJNIEnv() {
    return this->jenv;
}

#include "com/diag/desperado/End.h"


#if defined(DESPERADO_HAS_UNITTESTS)
#include "com/diag/desperado/cxxcapi.h"
/**
 *  Run the JavaVirtualMachine unit test.
 *
 *  @param  debug       if true enables debugging output.
 *  
 *  @return the number of errors detected by the unit test.
 */
CXXCAPI int unittestJavaVirtualMachine(bool debug);
#endif


#endif


#endif
