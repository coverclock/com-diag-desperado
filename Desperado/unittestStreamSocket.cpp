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

    $Id: unittestStreamSocket.cpp,v 1.2 2006/08/14 00:07:14 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the StreamSocket unit test. See also the Service unit test
 *  which tests StreamSockets using real sockets.
 *
 *  @see    StreamSocket
 *
 *  @see    Service
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.2 $
 *
 *  @date   $Date: 2006/08/14 00:07:14 $
 */

#include <unistd.h>
#include "UnitTest.h"
#include "target.h"
#include "StreamSocket.h"
#include "StreamSocket.h"
#include "Print.h"
#include "Platform.h"
#include "Output.h"
#include "Desperado.h"

static StreamSocket staticSocket;

CXXCAPI int unittestStreamSocket(void) {
    Print printf(Platform::instance().output());
    Print errorf(Platform::instance().error());
    int errors = 0;

    printf("%s[%d]: begin\n", __FILE__, __LINE__);

    ::staticSocket.show();

    int fds[2];
    int rc = ::pipe(fds);
    if (0 > rc) {
        errorf("%s[%d]: pipe failed (%d)!\n", __FILE__, __LINE__, rc);
        ++errors;
        return errors;
    }

    StreamSocket socket(fds[0], fds[1]);

    socket.show();

    Input& input = socket.input();
    input.show();

    Output& output = socket.output();
    output.show();

    printf("%s[%d]: end errors=%d\n",
        __FILE__, __LINE__, errors);

    return errors;
}
