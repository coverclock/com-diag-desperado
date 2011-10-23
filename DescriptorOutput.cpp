/* vim: set ts=4 expandtab shiftwidth=4: */

/******************************************************************************

    Copyright 2005 Digital Aggregates Corp., Arvada CO 80001-0587, USA.
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

    $Id: DescriptorOutput.cpp,v 1.5 2006/02/07 00:07:03 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the DescriptorOutput class.
 *
 *  @see    DescriptorOutput
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.5 $
 *
 *  @date   $Date: 2006/02/07 00:07:03 $
 */


#include <new>
#include <unistd.h>
#include "com/diag/desperado/stdio.h"
#include "com/diag/desperado/generics.h"
#include "com/diag/desperado/errno.h"
#include "com/diag/desperado/target.h"
#include "com/diag/desperado/string.h"
#include "com/diag/desperado/DescriptorOutput.h"
#include "com/diag/desperado/Print.h"
#include "com/diag/desperado/Platform.h"


#include "com/diag/desperado/Begin.h"


//
//  Constructor.
//
DescriptorOutput::DescriptorOutput(int fd) :
    Output(),
    descriptor(fd),
    active(fd)
{
}


//
//  Destructor.
//
DescriptorOutput::~DescriptorOutput() {
    (*this)();
}


//
//    Initializer.
//
bool DescriptorOutput::initialize(int fd) {
    bool rc = false;
    try {
        this->DescriptorOutput::~DescriptorOutput();
        new(this) DescriptorOutput(fd);
        rc = true;
    } catch (...) {
        rc = false;
    }
    return rc;
}


//
//  Output a character.
//
int DescriptorOutput::operator() (int c) {
    int rc = EOF;
    if (0 > this->active) {
        errno = 0;
    } else {
        unsigned char ch = c;
        ssize_t fc = ::write(this->active, &ch, sizeof(ch));
        if (0 < fc) {
            rc = ch;
            rc = rc & intmaxof(unsigned char);
        } else if (0 == fc) {
            this->active = -1;
            errno = 0;
        } else if (0 == errno) {
            errno = EIO;
        }
    }
    return rc;
}


//
//  Format and output a variable length argument list.
//
ssize_t DescriptorOutput::operator() (const char* format, va_list ap) {
    ssize_t rc = EOF;
    if (0 > this->active) {
        errno = 0;
    } else {
        char buffer[this->minimum_buffer_size + 1];
        ssize_t fc = ::vsnprintf(buffer, sizeof(buffer), format, ap);
        if (0 < fc) {
            const char* s = buffer;
            size_t length = fc;
            rc = 0;
            while (length > 0) {
                fc = ::write(this->active, s, length);
                if (0 < fc) {
                    rc += fc;
                    s += fc;
                    length -= fc;
                } else if (0 == fc) {
                    this->active = -1;
                    if (0 == rc) {
                        rc = EOF;
                        errno = 0;
                    }
                    break;
                } else {
                    if (0 == rc) {
                        rc = EOF;
                        if (0 == errno) {
                            errno = EIO;
                        }
                    }
                    break;
                }
            }
        } else if (0 == fc) {
            rc = fc;
        } else if (0 == errno) {
            errno = EIO;
        }
    }
    return rc;
}


//
//  Output a string of no more than the specified size.
//
ssize_t DescriptorOutput::operator() (const char* s, size_t size) {
    ssize_t rc = EOF;
    if (0 > this->active) {
        errno = 0;
    } else {
        size_t length = ::strnlen(s, size);
        ssize_t fc;
        rc = 0;
        while (length > 0) {
            fc = ::write(this->active, s, length);
            if (0 < fc) {
                rc += fc;
                s += fc;
                length -= fc;
            } else if (0 == fc) {
                this->active = -1;
                if (0 == rc) {
                    rc = EOF;
                    errno = 0;
                }
                break;
            } else {
                if (0 == rc) {
                    rc = EOF;
                    if (0 == errno) {
                        errno = EIO;
                    }
                }
                break;
            }
        }
    }
    return rc;
}


//
//  Write binary data to the file descriptor from a buffer.
//
ssize_t DescriptorOutput::operator() (
    const void* buffer,
    size_t minimum,
    size_t maximum
) {
    ssize_t rc = EOF;
    if (0 > this->active) {
        errno = 0;
    } else if (0 == maximum) {
        rc = 0;
    } else {
        const char* here = reinterpret_cast<const char*>(buffer);
        ssize_t fc;
        rc = 0;
        while (0 < maximum) {
            fc = ::write(this->active, here, maximum);
            if (0 < fc) {
                here += fc;
                maximum -= fc;
                rc += fc;
            } else if (0 == fc) {
                this->active = -1;
                if (0 == rc) {
                    rc = EOF;
                    errno = 0;
                }
                break;
            } else {
                if (0 == rc) {
                    rc = EOF;
                    if (0 == errno) {
                        errno = EIO;
                    }
                }
                break;
            }
            //
            //  Putting this check at the bottom guarantees
            //  at least one write is performed even if
            //  minimum is zero; otherwise a write would never
            //  be performed.
            //
            if (static_cast<ssize_t>(minimum) <= rc) {
                break;
            }
        }
    }
    return rc;
}


//
//  Flush buffered data.
//
int DescriptorOutput::operator() () {
    return 0;
}


//
//  Show this object on the output object.
//
void DescriptorOutput::show(int level, Output* display, int indent) const {
    Platform& pl = Platform::instance();
    Print printf(display);
    const char* sp = printf.output().indentation(indent);
    char component[sizeof(__FILE__)];
    printf("%s%s(%p)[%lu]:\n",
        sp, pl.component(__FILE__, component, sizeof(component)),
        this, sizeof(*this));
    this->Output::show(level, display, indent + 1);
    printf("%s descriptor=%d%s\n",
        sp, this->descriptor,
        (STDOUT_FILENO == this->descriptor) ? "=STDOUT" :
            (STDERR_FILENO == this->descriptor) ? "=STDERR" : "");
    printf("%s active=%d\n", sp, this->active);
}


#include "com/diag/desperado/End.h"
