#ifndef _COM_DIAG_DESPERADO_CXXJAPI_H_
#define _COM_DIAG_DESPERADO_CXXJAPI_H_

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

    $Id: cxxjapi.h,v 1.2 2006/07/24 16:26:21 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Defines the symbols and macros necessary for the Desperado
 *  C++/Java-language Application Programming Interface (CXXJAPI).
 *  The CXXCAPI provides tools to make it easier for Java and C++
 *  applications to interoperate.
 *
 *  This header file can included from both C++ and C translation units.
 *
 *  @see    J. Gosling, et al., <I>The Java Language Specification
 *          Second Edition</I>, Addison-Wesley, 2000
 *
 *  @see    K. Arnold, et al., <I>The Java Programming Language
 *          Third Edition</I>, Addison-Wesley, 2000
 *
 *  @see    S. Liang, <I>The Java Native Interface Programmer's Guide
 *          and Specification</I>, Addison-Wesley, 1999
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.2 $
 *
 *  @date   $Date: 2006/07/24 16:26:21 $
 */


#include "com/diag/desperado/cxxcapi.h"


#define CXXJAPI CXXCAPI


#if defined(DESPERADO_HAS_UNITTESTS)
/**
 *  Run the C++ CXXJAPI unit test.
 *
 *  @return the number of errors detected.
 */
CXXCAPI int unittestcxxjapi();
/**
 *  Run the C CXXJAPI unit test.
 *
 *  @return the number of errors detected.
 */
CXXCAPI int unittestcxxjapi2(void);
#endif


#endif
