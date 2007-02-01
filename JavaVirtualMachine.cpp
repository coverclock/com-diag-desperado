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

    $Id: JavaVirtualMachine.cpp,v 1.5 2006/09/07 21:38:12 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the JavaVirtualMachine class.
 *
 *  @see    JavaVirtualMachine
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.5 $
 *
 *  @date   $Date: 2006/09/07 21:38:12 $
 */


#if defined(DESPERADO_HAS_JAVA)


#include <new>
#include <cstdlib>
#include "JavaVirtualMachine.h"
#include "Print.h"
#include "Platform.h"
#include "Dump.h"


//
//  Constructor.
//
JavaVirtualMachine::JavaVirtualMachine(bool ign, Output* out) :
    jopts(0),
    jvm(0),
    jenv(0),
    ignore(ign),
    output(out)
{
}


//
//  Destructor.
//
JavaVirtualMachine::~JavaVirtualMachine() {
    this->destroy();
}


//
//    Initializer.
//
bool JavaVirtualMachine::initialize(bool ign, Output* out) {
    bool rc = false;
    try {
        this->JavaVirtualMachine::~JavaVirtualMachine();
        new(this) JavaVirtualMachine(ign, out);
        rc = true;
    } catch (...) {
        rc = false;
    }
    return rc;
}


//
//  Lazy start the machine.
//  
int JavaVirtualMachine::create(const char* options[], size_t noptions) {

    if ((options != 0) && (noptions > 0)) {
        // Yes, shocking that we are dynamically allocating memory.
        // But if you don't want to allocate and free memory on the
        // heap, you really don't want to be using Java.
        this->jopts = new JavaVMOption[noptions];
        for (size_t ii = 0; ii < noptions; ++ii) {
            this->jopts[ii].optionString = const_cast<char*>(options[ii]);
        }
    } else {
        noptions = 0;
    }

    this->jargs.version = 0x00010002;
    JNI_GetDefaultJavaVMInitArgs(&(this->jargs)); 

    this->jargs.nOptions = noptions;
    this->jargs.options = this->jopts;
    this->jargs.ignoreUnrecognized = this->ignore ? JNI_TRUE : JNI_FALSE;

    if (this->output != 0) {
        Print printf(this->output);
        Dump dump(this->output);
        printf("%s[%d]: JavaVMInitArgs:\n", __FILE__, __LINE__);
        dump.words(&(this->jargs), sizeof(JavaVMInitArgs));
        for (int ii = 0; ii < this->jargs.nOptions; ++ii) {
            printf("%s[%d]: JavaVMInitArgs.options[%u].optionString=\"%s\"\n",
                __FILE__, __LINE__, ii, this->jargs.options[ii].optionString);
        }
    }

    jint rc = ::JNI_CreateJavaVM(
        &(this->jvm),
        reinterpret_cast<void**>(&(this->jenv)),
        &(this->jargs)
    );

    if (this->output != 0) {
        Print printf(this->output);
        Dump dump(this->output);
        if (this->jvm != 0) {
            printf("%s[%d]: JavaVM:\n", __FILE__, __LINE__);
            dump.words(this->jvm, sizeof(JavaVM));
        }
        if (this->jenv != 0) {
            printf("%s[%d]: JNIEnv:\n", __FILE__, __LINE__);
            dump.words(this->jenv, sizeof(JNIEnv));
        }
    }

    return static_cast<int>(rc);
}


//
//  Destroy the JVM.
//
int JavaVirtualMachine::destroy() {
    int rc = 0;
    if (this->jvm != 0) {
        rc = jvm->DestroyJavaVM();
    }
    if (jopts != 0) {
        delete[] jopts;
    }
    jopts = 0;
    jargs.nOptions = 0;
    jargs.options = 0;
    jargs.ignoreUnrecognized = 0;
    jvm = 0;
    jenv = 0;
    return rc;
}


//
//  Show this object on the output object.
//
void JavaVirtualMachine::show(int level, Output* display, int indent) const {
    Platform& pl = Platform::instance();
    Print printf(display);
    Dump dump(display);
    const char* sp = printf.output().indentation(indent);
    char component[sizeof(__FILE__)];
    printf("%s%s(%p)[%lu]:\n",
        sp, pl.component(__FILE__, component, sizeof(component)),
        this, sizeof(*this));
    printf("%s jopts=%p\n", sp, this->jopts);
    printf("%s jargs.nOptions=%d\n", sp, this->jargs.nOptions);
    printf("%s jargs.options=%p\n", sp, this->jargs.options);
    printf("%s jargs.ignoreUnrecognized=%d\n", sp, this->jargs.ignoreUnrecognized);
    printf("%s jvm=%p\n", sp, this->jvm);
    printf("%s jenv=%p\n", sp, this->jenv);
    printf("%s ignore=%d\n", sp, this->ignore);
    printf("%s output=%p\n", sp, this->output);
    if (output != 0) {
        output->show(level, display, indent + 2);
    }
}


#endif
