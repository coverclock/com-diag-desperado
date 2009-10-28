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

    $Id: FileOutput.cpp,v 1.5 2006/02/07 00:07:03 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the FileOutput class.
 *
 *  @see    FileOutput
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.5 $
 *
 *  @date   $Date: 2006/02/07 00:07:03 $
 */


#include <new>
#include "stdio.h"
#include "errno.h"
#include "target.h"
#include "string.h"
#include "FileOutput.h"
#include "Print.h"
#include "Platform.h"


#include "Begin.h"


//
//  Constructor.
//
FileOutput::FileOutput(FILE* fp) :
    Output(),
    file(fp)
{
}


//
//  Destructor.
//
FileOutput::~FileOutput() {
    (*this)();
}


//
//    Initializer.
//
bool FileOutput::initialize(FILE* fp) {
    bool rc = false;
    try {
        this->FileOutput::~FileOutput();
        new(this) FileOutput(fp);
        rc = true;
    } catch (...) {
        rc = false;
    }
    return rc;
}


//
//  Output a character.
//
int FileOutput::operator() (int c) {
    int rc = EOF;
    if (0 == this->file) {
        errno = EINVAL;
    } else if (std::feof(this->file)) {
        errno = 0;
    } else {
        int fc = std::fputc(c, this->file);
        if (EOF != fc) {
            rc = fc;
        } else if (std::feof(this->file)) {
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
ssize_t FileOutput::operator() (const char* format, va_list ap) {
    ssize_t rc = EOF;
    if (0 == this->file) {
        errno = EINVAL;
    } else if (std::feof(this->file)) {
        errno = 0;
    } else {
        int fc = std::vfprintf(this->file, format, ap);
        if (EOF != fc) {
            rc = fc;
        } else if (std::feof(this->file)) {
            errno = 0;
        } else if (0 == errno) {
            errno = EIO;
        }
    }
    return rc;
}


//
//  Output a string of no more than the specified size.
//
ssize_t FileOutput::operator() (const char* s, size_t size) {
    ssize_t rc = EOF;
    if (0 == this->file) {
        errno = EINVAL;
    } else if (std::feof(this->file)) {
        errno = 0;
    } else if (0 == size) {
        rc = 0;
    } else {
        size_t length = ::strnlen(s, size);
        if (length < size) {
            size = length;
        }
        if (0 == size) {
            rc = 0;
        } else {
            size_t fc = std::fwrite(s, 1, size, this->file);
            if (0 != fc) {
                rc = fc;
            } else if (std::feof(this->file)) {
                errno = 0;
            } else if (0 == errno) {
                errno = EIO;
            }
        }
    }
    return rc;
}


//
//  Output binary data.
//
ssize_t FileOutput::operator() (
    const void* buffer,
    size_t minimum,
    size_t  /* maximum */
) {
    ssize_t rc = EOF;
    if (0 == this->file) {
        errno = EINVAL;
    } else if (std::feof(this->file)) {
        errno = 0;
    } else if (0 == minimum) {
        rc = 0;
    } else {
        size_t fc =
            static_cast<ssize_t>(std::fwrite(buffer, 1, minimum, this->file));
        if (0 != fc) {
            rc = fc;
        } else if (std::feof(this->file)) {
            errno = 0;
        } else if (0 == errno) {
            errno = EIO;
        }
    }
    return rc;
}


//
//  Flush buffered data.
//
int FileOutput::operator() () {
    int rc = EOF;
    if (0 == this->file) {
        errno = EINVAL;
    } else if (std::feof(this->file)) {
        errno = 0;
    } else {
        rc = std::fflush(this->file);
        if (EOF == rc) {
            if (std::feof(this->file)) {
                errno = 0;
            } else if (0 == errno) {
                errno = EIO;
            }
        }
    }
    return rc;
}


//
//  Show this object on the output object.
//
void FileOutput::show(int level, Output* display, int indent) const {
    Platform& pl = Platform::instance();
    Print printf(display);
    const char* sp = printf.output().indentation(indent);
    char component[sizeof(__FILE__)];
    printf("%s%s(%p)[%lu]:\n",
        sp, pl.component(__FILE__, component, sizeof(component)),
        this, sizeof(*this));
    this->Output::show(level, display, indent + 1);
    printf("%s file=%p%s\n", sp, this->file,
        (stdout == this->file) ? "=stdout" :
            (stderr == this->file) ? "=stderr" : "");
    if (this->file) {
        printf("%s  fileno=%d\n", sp, fileno(this->file));
        printf("%s  feof=%d\n", sp, std::feof(this->file));
        printf("%s  ferror=%d\n", sp, std::ferror(this->file));
    }
}


#include "End.h"
