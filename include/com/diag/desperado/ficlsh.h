#ifndef _COM_DIAG_DESPERADO_FICLSH_H_
#define _COM_DIAG_DESPERADO_FICLSH_H_

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
 *  Declares the ficlsh functions.
 *
 *  @author Chip Overclock (coverclock@diag.com)
 *
 *
 */


#if defined(DESPERADO_HAS_FICL)


#include "com/diag/desperado/target.h"
#include "com/diag/desperado/cxxcapi.h"
#include "com/diag/desperado/Input.h"
#include "com/diag/desperado/Output.h"
#include "com/diag/desperado/Platform.h"
#include "com/diag/desperado/Ficl.h"


/**
 *  Display the host name.
 *
 *  @param  pVM     points to the Ficl virtual machine in which this function
 *                  is executed.
 *
 *  @return the number of characters displayed.
 */
CXXCAPI int hostname(ficlVm* pVM);


/**
 *  Display the platform name.
 *
 *  @param  pVM     points to the Ficl virtual machine in which this function
 *                  is executed.
 *
 *  @return the number of characters displayed.
 */
CXXCAPI int platformname(ficlVm* pVM);


/**
 *  Display the target hostname.
 *
 *  @param  pVM     points to the Ficl virtual machine in which this function
 *                  is executed.
 *
 *  @return the number of characters displayed.
 */
CXXCAPI int targetname(ficlVm* pVM);


/**
 *  Return the current process identifier.
 *
 *  @param  pVM     points to the Ficl virtual machine in which this function
 *                  is executed.
 *
 *  @return the current process identifier.
 */
CXXCAPI int tid(ficlVm* pVM);


/**
 *  Return the current thread identifier.
 *
 *  @param  pVM     points to the Ficl virtual machine in which this function
 *                  is executed.
 *
 *  @return the current thread identifier.
 */
CXXCAPI int pid(ficlVm* pVM);


/**
 *  Return the low order word of the platform frequency and push the high
 *  order word of the platform frequency on the stack. The stack transform
 *  is ( -- highorder loworder ).
 *
 *  @param  pVM     points to the Ficl virtual machine in which this function
 *                  is executed.
 *
 *  @return the low order word of the platform frequency.
 */
CXXCAPI int frequency(ficlVm* pVM);


/**
 *  Dump length bytes starting at address data.
 *
 *  @param  pVM     points to the Ficl virtual machine in which this function
 *                  is executed.
 *
 *  @param  data    is an integer cast of a pointer to the data area to be
 *                  dumped.
 *
 *  @param  length  is an integer cast of the size_t in octets of the data
 *                  area to be dumped.
 *
 *  @return the number of characters dumped.
 */
CXXCAPI int dump(ficlVm* pVM, int data, int length);


/**
 *  Starts a Ficl shell. By default, the shell uses the platform input,
 *  output, and error output functors. The function returns when the shell
 *  exits. The Ficl shell, Ficl system, and Ficl machine are all deallocated
 *  when this function returns.
 *
 *  @param  input   refers to the input functor used by the Ficl machine.
 *
 *  @param  output  refers to the output functor used by the Ficl system.
 *
 *  @param  error   refers to the error output functor used by the Ficl system.
 * 
 *  @return the exit status of the Ficl shell.
 */
CXXCAPI int ficlsh(
    CXXCTYPE(::com::diag::desperado::, Input)& input = *platform_input(),
    CXXCTYPE(::com::diag::desperado::, Output)& output = *platform_output(),
    CXXCTYPE(::com::diag::desperado::, Output)& error = *platform_error()
);


#endif


#endif
