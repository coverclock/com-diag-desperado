/* vim: set ts=4 expandtab shiftwidth=4: */

/******************************************************************************

    Copyright 2006 Digital Aggregates Corp., Arvada CO 80001-0587, USA.
    This file is part of the Digital Aggregates Desperado library.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    $Name:  $

    $Id: ficlsh.cpp,v 1.2 2006/01/17 00:25:31 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the ficlsh shell.
 *
 *  @see    FiclConsole
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.2 $
 *
 *  @date   $Date: 2006/01/17 00:25:31 $
 */


#if defined(DESPERADO_HAS_FICL)


#include <cstdlib>
#include "desperado/cxxcapi.h"
#include "desperado/generics.h"
#include "desperado/FiclShell.h"
#include "desperado/Platform.h"
#include "desperado/Desperado.h"


CXXCAPI int hostname(ficlVm* pVM) {
    FiclSystem* system = static_cast<FiclSystem*>(pVM->callback.context);
    return (system->output())(Platform::instance().host());
}


CXXCAPI int platformname(ficlVm* pVM) {
    FiclSystem* system = static_cast<FiclSystem*>(pVM->callback.context);
    return (system->output())(Platform::instance().platform());
}


CXXCAPI int targetname(ficlVm* pVM) {
    FiclSystem* system = static_cast<FiclSystem*>(pVM->callback.context);
    return (system->output())(Platform::instance().target());
}


CXXCAPI int tid(ficlVm* /* pVM */) {
    identity_t identity = Platform::instance().identity();
    return identity;
}


CXXCAPI int pid(ficlVm* /* pVM */) {
    identity_t identity = Platform::instance().identity();
    return identity >> widthof(int);
}


CXXCAPI int frequency(ficlVm* pVM) {
    ticks_t ticks = Platform::instance().frequency();
    ficlCell cell;
    cell.u = ticks >> widthof(int);
    ficlStackPush(pVM->dataStack, cell);
    return ticks;
}


CXXCAPI int dump(ficlVm* pVM, int data, int length) {
    FiclSystem* system = static_cast<FiclSystem*>(pVM->callback.context);
    Dump dump(system->output());
    return dump.words(reinterpret_cast<void*>(data),
                        static_cast<size_t>(length));
}


CXXCAPI int ficlsh(Input& input, Output& output, Output& error) {
    FiclShell shell(output, error);
    shell.getFiclSystem()->extras();
    return shell(input);
}


#endif
