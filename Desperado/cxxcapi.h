#ifndef _COM_DIAG_DESPERADO_CXXCAPI_H_
#define _COM_DIAG_DESPERADO_CXXCAPI_H_

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

    $Id: cxxcapi.h,v 1.9 2006/07/24 16:01:46 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Defines the symbols and macros necessary for the Desperado
 *  C++/C-language Application Programming Interface (CXXCAPI).
 *  The CXXCAPI provides tools to make it easier for C and C++
 *  applications to interoperate, and for inline functions and
 *  macros to be included in either C or C++ translations units.
 *
 *  This header file can included from both C++ and C translation units.
 *
 *  @see    M. Cline et al., <I>C++ FAQs</I>, 2nd edition,
 *          Addision-Wessley, 1999, pp. 538, "FAQ 36.05 How
 *          can an object of a C++ class be passed to or from
 *          a C function?"
 *
 *  @see    M. Cline, "C++ FAQ Lite", 2001-08-15, 29.8
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.9 $
 *
 *  @date   $Date: 2006/07/24 16:01:46 $
 */


#if !defined(NULL)
#   if defined(__cplusplus)
        /**
         *  @def NULL
         *
         *  NULL is the value of the null pointer. The use of this manifest
         *  constant should be avoided in C++, but may be necessary when
         *  writing header files that may be included in either C or C++
         *  translation units.
         */
#       define NULL (0)
#   else
        /**
         *  @def NULL
         *
         *  NULL is the value of the null pointer. The use of this manifest
         *  constant should be avoided in C++, but may be necessary when
         *  writing header files that may be included in either C or C++
         *  translation units.
         */
#       define NULL ((void*)0)
#   endif
#endif


#if defined(__cplusplus)
    /**
     *  @def CXXCAPI
     *
     *  This symbol is used in both declarations and definitions of
     *  functions in C++ translation units that are callable from C
     *  translation units. Pronounced "sex-cappy".
     */
#   define CXXCAPI extern "C"
#else
    /**
     *  @def CXXCAPI
     *
     *  This symbol is used in declarations of functions in C translation
     *  units that are defined in C++ translation units. Pronounced
     *  "sex-cappy".
     */
#   define CXXCAPI extern
#endif


#if defined(__cplusplus)
    /*
     *  C++ allows inline keyword.
     */
#elif (defined(__STDC_VERSION__)&&((__STDC_VERSION__) > 199901L))
    /*
     *  ANSI C beyond 1999-01 allows inline keyword.
     */
#elif (defined(__GNUC__)&&defined(__GNUC_MINOR__)&&((((__GNUC__)*1000)+(__GNUC_MINOR__))>=2007))
#   undef inline
    /**
     *  @def inline
     *
     *  This symbol allows applications to include system header
     *  files that define inline functions into a C translation
     *  units being compiled for strict ISO C compliance.
     */
#   define inline __inline__
#else
#   undef inline
    /**
     *  @def inline
     *
     *  This symbol allows applications to include system header
     *  files that define inline functions into a C translation
     *  units being compiled for strict ISO C compliance.
     */
#   define inline
#endif


/**
 *  @def CXXCINLINE
 *
 *  This symbol is used in both declarations and definitions of
 *  standalone functions in header files included in both C
 *  and C++ translation units to suggest that the compiler inline
 *  the function. Pronounced "sexy-inline".
 *
 *  Note that the use of the static keyword in this context has
 *  been deprecated by the later ANSI C++ standard.
 */
#define CXXCINLINE static inline


/**
 *  Run the cxxcapi unit test.
 *
 *  @return the number of errors detected.
 */
CXXCAPI int unittestcxxcapi(void);


/**
 *  Run the cxxcapi CXXCAPI unit test.
 *
 *  @return the number of errors detected.
 */
CXXCAPI int unittestcxxcapi2(void);


#endif
