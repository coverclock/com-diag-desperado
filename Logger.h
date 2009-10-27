#ifndef _COM_DIAG_DESPERADO_LOGGER_H_
#define _COM_DIAG_DESPERADO_LOGGER_H_

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

    $Id: Logger.h,v 1.20 2006/05/02 03:58:51 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Declares the Logger class.
 *
 *  @see    Logger
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.20 $
 *
 *  @date   $Date: 2006/05/02 03:58:51 $
 */


#include "target.h"
#include "cxxcapi.h"


#if defined(__cplusplus)


#include "Object.h"
#include "Output.h"


#include "Begin.h"

/**
 *  Defines a simple interface to a multi-level logging mechanism, and
 *  implements a simple logger using it. Is easily overridden to use
 *  other logging mechanisms like cpp4j or syslog(3). The default behavior
 *  is to write output to the platform log functor. Different
 *  logging levels are supported. All levels of logging are enabled
 *  in the base class, although a derived class may implement a
 *  mechanism to limit logging to only certain levels. Levels
 *  representing the transitive closure of tools like log4j/log4cpp,
 *  Linux syslog, JDK Logger, and Apache SimpleLog are defined. A
 *  derived class may choose to map these to a smaller set of levels,
 *  or to extend the class to a larger set of levels. If you are into
 *  log4j or log4cpp, you can think of this class as a log4j logger, and its
 *  output functor as a log4j appender. The purpose of this class is
 *  not to provide an all purpose logging mechanism, but to allow
 *  code to be written that can later be adapted to an existing
 *  logging mechanism, perhaps in a legacy system.
 *
 *  @author coverclock@diag.com (Chip Overclock)
 */
class Logger : public Object {

public:

    /**
     *  Constructor.
     *
     *  @param  po          points to an output object. If 0,
     *                      the platform log object is used.
     */
    explicit Logger(Output* po = 0);

    /**
     *  Constructor.
     *
     *  @param  ro          refers to an output object.
     */
    explicit Logger(Output& ro);

    /**
     *  Destructor.
     */
    virtual ~Logger();

    /**
     *  Initializes this object, returning it to its just constructed state.
     *  This is exactly equivalent to calling the object's destructor
     *  followed by calling its constructor. The use of this method allows
     *  object (re)construction to be virtualized. However, it has the side
     *  effect of also reinitializing the object's virtual pointer. This means
     *  wackiness will ensue when if, for example, a derived class object
     *  deliberately calls its base class initializer. Doing so turns this
     *  object from an instance of the derived class into an instance of its
     *  base class. This implementation requires that every class derived
     *  from a class that implements this method must also implement this
     *  method, otherwise it can never be used against a derived class object.
     *
     *  @param  po          points to an output object. If 0,
     *                      the platform log object is used.
     *
     *  @return true if successful, false otherwise.
     */
    virtual bool initialize(Output* po = 0);

    /**
     *  Initializes this object, returning it to its just constructed state.
     *  This is exactly equivalent to calling the object's destructor
     *  followed by calling its constructor. The use of this method allows
     *  object (re)construction to be virtualized. However, it has the side
     *  effect of also reinitializing the object's virtual pointer. This means
     *  wackiness will ensue when if, for example, a derived class object
     *  deliberately calls its base class initializer. Doing so turns this
     *  object from an instance of the derived class into an instance of its
     *  base class. This implementation requires that every class derived
     *  from a class that implements this method must also implement this
     *  method, otherwise it can never be used against a derived class object.
     *
     *  @param  ro          refers to an output object.
     *
     *  @return true if successful, false otherwise.
     */
    virtual bool initialize(Output& ro);

    /**
     *  Returns a reference to its output object.
     *
     *  @return a reference to its output object.
     */
    virtual Output& output() const;

    /**
     *  These are the levels available for log messages.
     *  They are the transitive closure of the levels
     *  available in syslog(3), log4j, log4cpp, JDK Logger,
     *  Apache SimpleLog, etc.
     */
    enum Level {
        FINEST          =   0,
        FINER           =   1,
        FINE            =   2,
        TRACE           =   3,
        DEBUG           =   4,
        INFORMATION     =   5,
        CONFIGURATION   =   6,
        NOTICE          =   7,
        WARNING         =   8,
        ERROR           =   9,
        SEVERE          =   10,
        CRITICAL        =   11,
        ALERT           =   12,
        FATAL           =   13,
        EMERGENCY       =   14,
        PRINT           =   15
    };

    /**
     *  This nul-terminated array contains labels corresponding to
     *  the levels.
     */
    static const char* labels[PRINT + 2];

    /**
     * These characters delimit the symbolic extended log levels.
     */
    static const char
        LHS_EXTENDED = '[',
        RHS_EXTENDED = ']';

    /**
     * This table maps from the kernel <0>..<7> log levels to the
     * extended log levels.
     */
    static const Level kernel[8];

    /**
     * These characters delimit the numeric kernel log levels,
     * mimicing how the Linux kernel works.
     */
    static const char
        LHS_KERNEL = '<',
        RHS_KERNEL = '>';

    /**
     *  Given a log message in a buffer, determine its level.
     *
     *  @param  buffer      points to the buffer containing
     *                      the message.
     *
     *  @param  size        is the maximum size of the buffer
     *                      in octets.
     */
    virtual Level level(const char* buffer, size_t size);

    /**
     *  Return true if the specified level is enabled, false otherwise.
     *
     *  This method in the base class always returns true. It can be
     *  overridden in a derived class to support other behavior.
     *
     *  @param  level   indicates the level.
     *
     *  @return true if the specified level is enabled, false otherwise.
     */
    virtual bool isEnabled(Level level);

    /**
     *  Format a log message.
     *
     *  @param  buffer  points to the output buffer.
     *
     *  @param  size    is the size of the output buffer in bytes.
     *
     *  @param  level   indicates the level.
     *
     *  @param  format  points to the printf-style format string.
     *
     *  @param  ap      points to the argument list.
     *
     *  @return the number of characters written to its output
     *          object, or a negative number if error.
     */
    virtual ssize_t format(
        char* buffer,
        size_t size,
        Level level,
        const char* format,
        va_list ap
    );

    /**
     *  Unconditionally emit a log message using a buffer.
     *
     *  @param  buffer  points to the buffer to be emitted.
     *
     *  @param  size    is the size of the buffer in bytes.
     *
     *  @return the number of characters written to its output
     *          object, or a negative number if error.
     */
    virtual ssize_t emit(const char* buffer, size_t size);

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

    //
    //  Note that this method is not virtual, and is inline, in
    //  an effort to eliminate some of the overhead of each logging
    //  call. Derived classes wishing to alter the implementation
    //  of this base class shall have to do so by overriding the
    //  Logger::isEnabled(), Logger::format(), Logger::emit() methods,
    //  which are virtual.
    //

    /**
     *  Log a message using an argument list if the specified level
     *  is enabled.
     *
     *  @param  level   indicates the level.
     *
     *  @param  format  points to the printf-style format string.
     *
     *  @param  ap      points to the argument list.
     *
     *  @return the number of characters written to its output
     *          object, or a negative number if error.
     */
    ssize_t log(Level level, const char* format, va_list ap);

    //
    //  Note that the variadic logging methods are not
    //  virtual. This is an attempt to eliminate some of the
    //  overhead of a logging call, while unfortunately limiting
    //  the ability of a derived class to override these methods.
    //  Also note that they are not inline. In my experience, most
    //  C++ compilers cannot inline variadic methods because the
    //  va_list mechanism itself depends on an argument list having
    //  been built on the stack as part of the function call
    //  implementation.
    //

    /**
     *  Log a message using a variadic argument list if the specified
     *  level is enabled.
     *
     *  @param  level   indicates the level.
     *
     *  @param  format  points to the printf-style format string.
     */
    ssize_t log(Level level, const char* format ...);

    /**
     *  Formats a variadic argument list and writes the result
     *  to its output object if FINEST is enabled.
     *
     *  @param  format      is the printf-style format string,
     *                      followed by zero or more arguments.
     *
     *  @return the number of characters written to its output
     *          object, or a negative number if error.
     */
    ssize_t finest(const char* format ...);

    /**
     *  Formats a variadic argument list and writes the result
     *  to its output object if FINER is enabled.
     *
     *  @param  format      is the printf-style format string,
     *                      followed by zero or more arguments.
     *
     *  @return the number of characters written to its output
     *          object, or a negative number if error.
     */
    ssize_t finer(const char* format ...);

    /**
     *  Formats a variadic argument list and writes the result
     *  to its output object if FINE is enabled.
     *
     *  @param  format      is the printf-style format string,
     *                      followed by zero or more arguments.
     *
     *  @return the number of characters written to its output
     *          object, or a negative number if error.
     */
    ssize_t fine(const char* format ...);

    /**
     *  Formats a variadic argument list and writes the result
     *  to its output object if TRACE is enabled.
     *
     *  @param  format      is the printf-style format string,
     *                      followed by zero or more arguments.
     *
     *  @return the number of characters written to its output
     *          object, or a negative number if error.
     */
    ssize_t trace(const char* format ...);

    /**
     *  Formats a variadic argument list and writes the result
     *  to its output object if DEBUG is enabled.
     *
     *  @param  format      is the printf-style format string,
     *                      followed by zero or more arguments.
     *
     *  @return the number of characters written to its output
     *          object, or a negative number if error.
     */
    ssize_t debug(const char* format ...);

    /**
     *  Formats a variadic argument list and writes the result
     *  to its output object if INFORMATION is enabled.
     *
     *  @param  format      is the printf-style format string,
     *                      followed by zero or more arguments.
     *
     *  @return the number of characters written to its output
     *          object, or a negative number if error.
     */
    ssize_t information(const char* format ...);

    /**
     *  Formats a variadic argument list and writes the result
     *  to its output object if CONFIGURATION is enabled.
     *
     *  @param  format      is the printf-style format string,
     *                      followed by zero or more arguments.
     *
     *  @return the number of characters written to its output
     *          object, or a negative number if error.
     */
    ssize_t configuration(const char* format ...);

    /**
     *  Formats a variadic argument list and writes the result
     *  to its output object if NOTICE is enabled.
     *
     *  @param  format      is the printf-style format string,
     *                      followed by zero or more arguments.
     *
     *  @return the number of characters written to its output
     *          object, or a negative number if error.
     */
    ssize_t notice(const char* format ...);

    /**
     *  Formats a variadic argument list and writes the result
     *  to its output object if WARNING is enabled.
     *
     *  @param  format      is the printf-style format string,
     *                      followed by zero or more arguments.
     *
     *  @return the number of characters written to its output
     *          object, or a negative number if error.
     */
    ssize_t warning(const char* format ...);

    /**
     *  Formats a variadic argument list and writes the result
     *  to its output object if ERROR is enabled.
     *
     *  @param  format      is the printf-style format string,
     *                      followed by zero or more arguments.
     *
     *  @return the number of characters written to its output
     *          object, or a negative number if error.
     */
    ssize_t error(const char* format ...);

    /**
     *  Formats a variadic argument list and writes the result
     *  to its output object if SEVERE is enabled.
     *
     *  @param  format      is the printf-style format string,
     *                      followed by zero or more arguments.
     *
     *  @return the number of characters written to its output
     *          object, or a negative number if error.
     */
    ssize_t severe(const char* format ...);

    /**
     *  Formats a variadic argument list and writes the result
     *  to its output object if CRITICAL is enabled.
     *
     *  @param  format      is the printf-style format string,
     *                      followed by zero or more arguments.
     *
     *  @return the number of characters written to its output
     *          object, or a negative number if error.
     */
    ssize_t critical(const char* format ...);

    /**
     *  Formats a variadic argument list and writes the result
     *  to its output object is ALERT is enabled.
     *
     *  @param  format      is the printf-style format string,
     *                      followed by zero or more arguments.
     *
     *  @return the number of characters written to its output
     *          object, or a negative number if error.
     */
    ssize_t alert(const char* format ...);

    /**
     *  Formats a variadic argument list and writes the result
     *  to its output object if FATAL is enabled.
     *
     *  @param  format      is the printf-style format string,
     *                      followed by zero or more arguments.
     *
     *  @return the number of characters written to its output
     *          object, or a negative number if error.
     */
    ssize_t fatal(const char* format ...);

    /**
     *  Formats a variadic argument list and writes the result
     *  to its output object if EMERGENCY is enabled.
     *
     *  @param  format      is the printf-style format string,
     *                      followed by zero or more arguments.
     *
     *  @return the number of characters written to its output
     *          object, or a negative number if error.
     */
    ssize_t emergency(const char* format ...);

    /**
     *  Formats a variadic argument list and writes the result
     *  to its output object unconditionally. The intent of the
     *  PRINT level is that it be used only to direct output to the
     *  log output functor that is the result of a craft demand
     *  (e.g. a command entered by a technician), not for log
     *  output generated spontaneously by the application.
     *
     *  @param  format      is the printf-style format string,
     *                      followed by zero or more arguments.
     *
     *  @return the number of characters written to its output
     *          object, or a negative number if error.
     */
    ssize_t print(const char* format ...);

private:

    /**
     *  Points to the output object to which the logging is directed.
     */
    Output* ou;

};


//
//  Log the argument list. Note that the PRINT level is checked for
//  explicitly, enforcing the fact that the PRINT level is logged
//  unconditionally regardless of the value returned by the isEnabled()
//  method.
//
inline ssize_t Logger::log(Level level, const char* format, va_list ap) {
    ssize_t rc = 0;
    if ((this->PRINT == level) || this->isEnabled(level)) {
        char buffer[Output::minimum_buffer_size + 1];
        this->format(buffer, sizeof(buffer), level, format, ap);
        rc = this->emit(buffer, sizeof(buffer));
    }
    return rc;
}

#include "End.h"


/**
 *  Run the Logger unit test.
 *  
 *  @return the number of errors detected by the unit test.
 */
extern "C" int unittestLogger();


#else


/**
 *  This is an opaque type used to refer to a C++ output object
 *  in a C program.
 */
typedef struct Logger Logger;


#endif


/**
 *  Formats a variadic argument list and writes the result
 *  to the specified log object if FINEST is enabled.
 *
 *  @param  logger      points to a logger object, for
 *                      example the platform logger object.
 *
 *  @param  format      is the printf-style format string,
 *                      followed by zero or more arguments.
 *
 *  @return the number of characters written to its output
 *          object, or a negative number if error.
 */
CXXCAPI ssize_t logger_finest(Logger* logger, const char* format, ...);


/**
 *  Formats a variadic argument list and writes the result
 *  to the specified log object if FINER is enabled.
 *
 *  @param  logger      points to a logger object, for
 *                      example the platform logger object.
 *
 *  @param  format      is the printf-style format string,
 *                      followed by zero or more arguments.
 *
 *  @return the number of characters written to its output
 *          object, or a negative number if error.
 */
CXXCAPI ssize_t logger_finer(Logger* logger, const char* format, ...);


/**
 *  Formats a variadic argument list and writes the result
 *  to the specified log object if FINE is enabled.
 *
 *  @param  logger      points to a logger object, for
 *                      example the platform logger object.
 *
 *  @param  format      is the printf-style format string,
 *                      followed by zero or more arguments.
 *
 *  @return the number of characters written to its output
 *          object, or a negative number if error.
 */
CXXCAPI ssize_t logger_fine(Logger* logger, const char* format, ...);


/**
 *  Formats a variadic argument list and writes the result
 *  to the specified log object if TRACE is enabled.
 *
 *  @param  logger      points to a logger object, for
 *                      example the platform logger object.
 *
 *  @param  format      is the printf-style format string,
 *                      followed by zero or more arguments.
 *
 *  @return the number of characters written to its output
 *          object, or a negative number if error.
 */
CXXCAPI ssize_t logger_trace(Logger* logger, const char* format, ...);


/**
 *  Formats a variadic argument list and writes the result
 *  to the specified log object if DEBUG is enabled.
 *
 *  @param  logger      points to a logger object, for
 *                      example the platform logger object.
 *
 *  @param  format      is the printf-style format string,
 *                      followed by zero or more arguments.
 *
 *  @return the number of characters written to its output
 *          object, or a negative number if error.
 */
CXXCAPI ssize_t logger_debug(Logger* logger, const char* format, ...);


/**
 *  Formats a variadic argument list and writes the result
 *  to the specified log object if INFORMATION is enabled.
 *
 *  @param  logger      points to a logger object, for
 *                      example the platform logger object.
 *
 *  @param  format      is the printf-style format string,
 *                      followed by zero or more arguments.
 *
 *  @return the number of characters written to its output
 *          object, or a negative number if error.
 */
CXXCAPI ssize_t logger_information(Logger* logger, const char* format, ...);


/**
 *  Formats a variadic argument list and writes the result
 *  to the specified log object if CONFIGURATION is enabled.
 *
 *  @param  logger      points to a logger object, for
 *                      example the platform logger object.
 *
 *  @param  format      is the printf-style format string,
 *                      followed by zero or more arguments.
 *
 *  @return the number of characters written to its output
 *          object, or a negative number if error.
 */
CXXCAPI ssize_t logger_configuration(Logger* logger, const char* format, ...);


/**
 *  Formats a variadic argument list and writes the result
 *  to the specified log object if NOTICE is enabled.
 *
 *  @param  logger      points to a logger object, for
 *                      example the platform logger object.
 *
 *  @param  format      is the printf-style format string,
 *                      followed by zero or more arguments.
 *
 *  @return the number of characters written to its output
 *          object, or a negative number if error.
 */
CXXCAPI ssize_t logger_notice(Logger* logger, const char* format, ...);


/**
 *  Formats a variadic argument list and writes the result
 *  to the specified log object if WARNING is enabled.
 *
 *  @param  logger      points to a logger object, for
 *                      example the platform logger object.
 *
 *  @param  format      is the printf-style format string,
 *                      followed by zero or more arguments.
 *
 *  @return the number of characters written to its output
 *          object, or a negative number if error.
 */
CXXCAPI ssize_t logger_warning(Logger* logger, const char* format, ...);


/**
 *  Formats a variadic argument list and writes the result
 *  to the specified log object if ERROR is enabled.
 *
 *  @param  logger      points to a logger object, for
 *                      example the platform logger object.
 *
 *  @param  format      is the printf-style format string,
 *                      followed by zero or more arguments.
 *
 *  @return the number of characters written to its output
 *          object, or a negative number if error.
 */
CXXCAPI ssize_t logger_error(Logger* logger, const char* format, ...);


/**
 *  Formats a variadic argument list and writes the result
 *  to the specified log object if SEVERE is enabled.
 *
 *  @param  logger      points to a logger object, for
 *                      example the platform logger object.
 *
 *  @param  format      is the printf-style format string,
 *                      followed by zero or more arguments.
 *
 *  @return the number of characters written to its output
 *          object, or a negative number if error.
 */
CXXCAPI ssize_t logger_severe(Logger* logger, const char* format, ...);


/**
 *  Formats a variadic argument list and writes the result
 *  to the specified log object if CRITICAL is enabled.
 *
 *  @param  logger      points to a logger object, for
 *                      example the platform logger object.
 *
 *  @param  format      is the printf-style format string,
 *                      followed by zero or more arguments.
 *
 *  @return the number of characters written to its output
 *          object, or a negative number if error.
 */
CXXCAPI ssize_t logger_critical(Logger* logger, const char* format, ...);


/**
 *  Formats a variadic argument list and writes the result
 *  to the specified log object if ALERT is enabled.
 *
 *  @param  logger      points to a logger object, for
 *                      example the platform logger object.
 *
 *  @param  format      is the printf-style format string,
 *                      followed by zero or more arguments.
 *
 *  @return the number of characters written to its output
 *          object, or a negative number if error.
 */
CXXCAPI ssize_t logger_alert(Logger* logger, const char* format, ...);


/**
 *  Formats a variadic argument list and writes the result
 *  to the specified log object if FATAL is enabled.
 *
 *  @param  logger      points to a logger object, for
 *                      example the platform logger object.
 *
 *  @param  format      is the printf-style format string,
 *                      followed by zero or more arguments.
 *
 *  @return the number of characters written to its output
 *          object, or a negative number if error.
 */
CXXCAPI ssize_t logger_fatal(Logger* logger, const char* format, ...);


/**
 *  Formats a variadic argument list and writes the result
 *  to the specified log object if EMERGENCY is enabled.
 *
 *  @param  logger      points to a logger object, for
 *                      example the platform logger object.
 *
 *  @param  format      is the printf-style format string,
 *                      followed by zero or more arguments.
 *
 *  @return the number of characters written to its output
 *          object, or a negative number if error.
 */
CXXCAPI ssize_t logger_emergency(Logger* logger, const char* format, ...);


/**
 *  Formats a variadic argument list and writes the result
 *  to the specified log object if PRINT is enabled.
 *
 *  @param  logger      points to a logger object, for
 *                      example the platform logger object.
 *
 *  @param  format      is the printf-style format string,
 *                      followed by zero or more arguments.
 *
 *  @return the number of characters written to its output
 *          object, or a negative number if error.
 */
CXXCAPI ssize_t logger_print(Logger* logger, const char* format, ...);


/**
 *  Run the Logger CXXCAPI unit test.
 *
 *  @return the number of errors detected.
 */
CXXCAPI int unittestLogger2(void);


#endif
