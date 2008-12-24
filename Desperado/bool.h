#ifndef _COM_DIAG_DESPERADO_BOOL_H_
#define _COM_DIAG_DESPERADO_BOOL_H_

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

    $Id: bool.h,v 1.12 2006/01/09 00:24:48 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Defines some symbols and a type that makes it look like C has the
 *  built-in C++ bool type. It is in a seperate header file because
 *  it is such a common thing to do, it is likely to conflict with many
 *  other source code bases.
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.12 $
 *
 *  @date   $Date: 2006/01/09 00:24:48 $
 */


#if !defined(__cplusplus)

#if defined(bool)
#undef bool
#endif

/**
 *  This defines a bool to be an int to conform to the ANSI
 *  C++ definition. 
 */
typedef int bool;

#if defined(true)
#undef true
#endif

/**
 *  This defines true to be whatever the compiler considers
 *  to be true.
 */
static const bool true = (1 == 1);

#if defined(false)
#undef false
#endif

/**
 *  This defines false to be whatever the compiler considers
 *  to be false.
 */
static const bool false = (1 == 0);

#endif


#endif
