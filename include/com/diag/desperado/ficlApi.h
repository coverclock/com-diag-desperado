#ifndef _COM_DIAG_DESPERADO_FICLAPI_H_
#define _COM_DIAG_DESPERADO_FICLAPI_H_

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
 *  Declares the Desperado Ficl API.
 *
 *  This header file can be included from either a C or C++ translation unit.
 *
 *  @see    FiclShell
 *
 *  @see    FiclSystem
 *
 *  @see    FiclMachine
 *
 *  @author Chip Overclock (coverclock@diag.com)
 *
 *
 */


#include "com/diag/desperado/cxxcapi.h"


#if defined(DESPERADO_HAS_FICL)


#include "com/diag/desperado/Ficl.h"


/**
 *  Initialize the Desperado Ficl shell by adding dictionary entries
 *  for functions and variables into the specified Ficl system.
 *
 *  This function is generated as build time by the ficlshell.sh script.
 *
 *  @param  system  points to the Ficl system owning the dictionary.
 */
CXXCAPI void desperado_ficl_shell(ficlSystem* system);


/**
 *  This is a pointer to any function that can be called from the context
 *  of a ficlMacine. The function always has at least one parameter,
 *  a pointer to the Ficl machine in whose context the function is being
 *  executed. It always returns an integer value which is pushed onto the
 *  data stack of its Ficl machine when the function returns. It can have
 *  between zero and ten additional parameters, each of which must be an
 *  integer. The function must always have a C (versus C++) binding.
 *
 *  @param  pVM     points to the Ficl machine in whose context the function
 *                  is being executed. Think of it as the hidden this pointer
 *                  in C++ instance methods.
 *
 *  @return an integer that is pushed onto the data stack of the Ficl machine.
 */
typedef /* CXXCAPI */ int (*desperado_ficl_function)(ficlVm *pVM, ...);


/**
 *  Invoke a Ficl-callable function.
 *
 *  @param  pVM     points to the Ficl machine in whose context the function
 *                  is being executed.
 *
 *  @param  fp      points to the function, which must no more than
 *                  ten integer arguments and return an return an integer.
 *
 *  @param  argc    is the number of arguments.
 *
 *  @param  argv    is an array of integer arguments.
 *
 *  @return the integer return value of the invoked function.
 */
CXXCAPI int desperado_ficl_proxy(
    ficlVm* pVM,
    desperado_ficl_function fp,
    int argc,
    int* argv
);


/**
 *  Implement the Desperado (( Ficl word by remembering the stack depth
 *  before function arguments are pushed onto it by the application.
 *
 *  Return: ( ip -- top ip )
 *  Data:   ( -- )
 *
 *  An example of the use of the (( and the )) words are shown below.
 *
 *  function (( arg1 arg2 ... argN ))
 *
 *  @param  pVM     points to the Ficl machine to execute this word.
 */
CXXCAPI void desperado_ficl_openparens(ficlVm* pVM);


/**
 *  Implement the Desperado )) Ficl word by marshalling the function arguments
 *  from the stack, popping the function pointer, invoking the function, and
 *  pushing its return value back onto the stack. The stack looks like this
 *  when this function before and after this function is invoked.
 *
 *  Return: ( top ip -- ip )
 *  Data:   ( fp arg1 arg2 ... argN -- rc )
 *
 *  An example of the use of the (( and the )) words are shown below.
 *
 *  function (( arg1 arg2 ... argN ))
 *
 *  @param  pVM     points to the Ficl machine to execute this word.
 */
CXXCAPI void desperado_ficl_closeparens(ficlVm* pVM);


/**
 *  Implement the Desperado (()) Ficl word by invoking a function
 *  with no arguments.
 *
 *  Return: ( -- )
 *  Data:   ( fp -- rc )
 *
 *  An example of the use of the (()) word is shown below.
 *
 *  function (())
 *
 *  This is exactly equivalent to the sequence shown below.
 *
 *  function (( ))
 *
 *  @param  pVM     points to the Ficl machine to execute this word.
 */
CXXCAPI void desperado_ficl_null(ficlVm* pVM);


/**
 *  Implement the Desperado ((...)) Ficl word by invoking a function
 *  with a variable number of arguments.
 *
 *  Return: ( -- )
 *  Data:   ( arg1 arg2 ... argN N fp -- rc )
 *
 *  An example of the use of the ((...)) word is shown below.
 *
 *  arg1 arg2 ... argN N function ((...))
 *
 *  @param  pVM     points to the Ficl machine to execute this word.
 */
CXXCAPI void desperado_ficl_parens(ficlVm* pVM);


#else


CXXCAPI void desperado_ficl_shell(void*);


#endif


#endif
