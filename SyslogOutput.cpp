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

    $Id: SyslogOutput.cpp,v 1.5 2006/02/07 00:07:03 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the SyslogOutput class.
 *
 *  @see    SyslogOutput
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.5 $
 *
 *  @date   $Date: 2006/02/07 00:07:03 $
 */


#if defined(DESPERADO_PLATFORM_IS_Linux)


#include <new>
#include <cstdarg>
#include "string.h"
#include "generics.h"
#include "SyslogOutput.h"
#include "Platform.h"
#include "Print.h"


int SyslogOutput::priorities[] = {
    LOG_INFO,
    LOG_INFO,
    LOG_INFO,
    LOG_INFO,
    LOG_DEBUG,
    LOG_INFO,
    LOG_NOTICE,
    LOG_NOTICE,
    LOG_WARNING,
    LOG_ERR,
    LOG_CRIT,
    LOG_CRIT,
    LOG_ALERT,
    LOG_EMERG,
    LOG_EMERG,
    LOG_INFO
};


//
//  Constructor.
//
SyslogOutput::SyslogOutput(Logger& rl, const char* id, int opt, int fac) :
    Output(),
    lo(&rl),
    ident(id),
    option(opt),
    facility(fac)
{
    ::openlog(id, opt, fac);
}


//
//  Constructor.
//
SyslogOutput::SyslogOutput(Logger* pl, const char* id, int opt, int fac) :
    Output(),
    lo(pl),
    ident(id),
    option(opt),
    facility(fac)
{
    ::openlog(id, opt, fac);
}


//
//  Destructor.
//
SyslogOutput::~SyslogOutput() {
    ::closelog();
}


//
//    Initializer.
//
bool SyslogOutput::initialize(Logger& rl, const char* id, int opt, int fac) {
    bool rc = false;
    try {
        this->SyslogOutput::~SyslogOutput();
        new(this) SyslogOutput(rl, id, opt, fac);
        rc = true;
    } catch (...) {
        rc = false;
    }
    return rc;
}


//
//    Initializer.
//
bool SyslogOutput::initialize(Logger* pl, const char* id, int opt, int fac) {
    bool rc = false;
    try {
        this->SyslogOutput::~SyslogOutput();
        new(this) SyslogOutput(pl, id, opt, fac);
        rc = true;
    } catch (...) {
        rc = false;
    }
    return rc;
}


//
//  Return a reference to the logger.
//
Logger& SyslogOutput::logger() const {
    return this->lo ? *this->lo : Platform::instance().logger();
}


int SyslogOutput::priority(const char* buffer, size_t size) {
    Logger& log = this->logger();
    size_t level = log.level(buffer, size);
    if (countof(this->priorities) <= level) {
        level = countof(this->priorities) - 1;
    }
    int pri = this->priorities[level];
#if DESPERADO_HAS_DEBUGGING
    Print printf;
    printf("%s[%d]: \"%.*s\" %lu %d %d\n",
        __FILE__, __LINE__, size - 1, buffer, size, level, pri);
#endif
    return pri;
}


//
//  Output a character.
//
int SyslogOutput::operator() (int c) {
    ::syslog(LOG_INFO, "%c", c);
    return c;
}


//
//  Format and output a variable length argument list.
//
ssize_t SyslogOutput::operator() (const char* format, va_list ap) {
    char buffer[minimum_buffer_size];
    ssize_t octets = ::vsnprintf(buffer, minimum_buffer_size, format, ap);
    ::syslog(LOG_INFO, "%s", buffer);
    return octets;
}


//
//  Output a string of no more than the specified size.
//
ssize_t SyslogOutput::operator() (const char* s, size_t size) {
    int priority = this->priority(s, size);
    ::syslog(priority, "%.*s", size, s);
    return ::strnlen(s, size);
}


//
//  Output binary data.
//
ssize_t SyslogOutput::operator() (
    const void* buffer,
    size_t minimum,
    size_t  /* maximum */
) {
    ::syslog(LOG_DEBUG, "%.*s", minimum, reinterpret_cast<const char*>(buffer));
    return minimum;
}


//
//  Flush buffered data.
//
int SyslogOutput::operator() () {
    return 0;
}


//
//  Show this object on the output object.
//
void SyslogOutput::show(int level, Output* display, int indent) const {
    Platform& pl = Platform::instance();
    Print printf(display);
    const char* sp = printf.output().indentation(indent);
    char component[sizeof(__FILE__)];
    printf("%s%s(%p)[%lu]:\n",
        sp, pl.component(__FILE__, component, sizeof(component)),
        this, sizeof(*this));
    this->Output::show(level, display, indent + 1);
    printf("%s lo=%p\n", sp, this->lo);
    // We can't show our logger because he has a pointer to us that he shows.
    printf("%s ident=\"%s\"\n", sp, this->ident);
    printf("%s option=0x%x\n", sp, this->option);
    printf("%s facility=0x%x\n", sp, this->facility);
}


#endif
