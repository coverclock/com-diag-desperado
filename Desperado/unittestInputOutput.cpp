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

    $Id: unittestInputOutput.cpp,v 1.3 2006/01/09 00:24:49 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the InputOutput unit test.
 *
 *  @see    InputOutput
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.3 $
 *
 *  @date   $Date: 2006/01/09 00:24:49 $
 */


#include <cstdarg>
#include "UnitTest.h"
#include "errno.h"
#include "errno.h"
#include "string.h"
#include "string.h"
#include "stdio.h"
#include "stdio.h"
#include "Input.h"
#include "Input.h"
#include "Output.h"
#include "Output.h"
#include "Print.h"
#include "Print.h"
#include "Platform.h"
#include "Platform.h"
#include "Desperado.h"

CXXCAPI int unittestInputOutput(
    void *,
    char mechanism,
    Input* inputp,
    Output* outputp
) {
    Input& input = *inputp;
    Output& output = *outputp;
    Print errorf(Platform::instance().error());
    Print outputf(output);
    int errors = 0;

    errorf("%s[%d]: begin\n", __FILE__, __LINE__);

    errorf("mechanism='%c'\n", mechanism);

    errorf("%s[%d]: before\n", __FILE__, __LINE__);
    errorf(" input:\n");
    input.show(0, &(Platform::instance().error()), 2);
    errorf(" output:\n");
    output.show(0, &(Platform::instance().error()), 2);

    ssize_t octets = 0;

    switch (mechanism) {

    //
    // Character.
    //
    case 'c':
        {
            int ch;
            int ch2;
            while (true) {
                ch = input();
                if (EOF == ch) {
                    if (0 != errno) {
                        errorf("%s[%d]: [%lu] input()!\n",
                            __FILE__, __LINE__, octets);
                        std::perror("input()");
                        ++errors;
                    }
                    break;
                }
                ++octets;
                ch2 = input(ch);
                if (EOF == ch2) {
                    errorf("%s[%d]: [%lu] input(ch)!\n",
                        __FILE__, __LINE__, octets);
                    std::perror("input(ch)");
                    ++errors;
                    break;
                }
                if (ch != ch2) {
                    errorf("%s[%d]: [%lu] (0x%hhx!=0x%hhx)!\n",
                        __FILE__, __LINE__, octets, ch, ch2);
                    std::perror("input(ch)");
                    ++errors;
                    break;
                }
                ch = input();
                if (EOF == ch) {
                    errorf("%s[%d]: [%lu] input()!\n",
                        __FILE__, __LINE__, octets);
                    std::perror("input()");
                    ++errors;
                    break;
                }
                if (ch2 != ch) {
                    errorf("%s[%d]: [%lu] (0x%hhx!=0x%hhx)!\n",
                        __FILE__, __LINE__, octets, ch2, ch);
                    std::perror("input()");
                    ++errors;
                    break;
                }
                ch2 = output(ch);
                if (EOF == ch2) {
                    errorf("%s[%d]: [%lu] output(ch)!\n",
                        __FILE__, __LINE__, octets);
                    std::perror("output(ch)");
                    ++errors;
                    break;
                }
                if (ch2 != ch) {
                    errorf("%s[%d]: [%lu] (0x%hhx!=0x%hhx)!\n",
                        __FILE__, __LINE__, octets, ch2, ch);
                    std::perror("output(ch)");
                    ++errors;
                    break;
                }
            }
        }
        break;

    //
    // Line.
    //
    case 'l':
        {
            char buffer[257];
            ssize_t rc;
            ssize_t rc2;
            while (true) {
                rc = input(buffer, sizeof(buffer));
                if (EOF == rc) {
                    if (0 != errno) {
                        errorf(
                            "%s[%d]: [%lu] input(buffer, size)!\n",
                            __FILE__, __LINE__, octets);
                        std::perror("input(buffer, size)");
                        ++errors;
                    }
                    break;
                }
                if (0 == rc) {
                    errorf("%s[%d]: [%lu] (0==%zd)!\n",
                        __FILE__, __LINE__, octets, rc);
                    ++errors;
                    continue;
                }
                if (static_cast<int>(sizeof(buffer)) < rc) {
                    errorf("%s[%d]: [%lu] (%lu<%zd)!\n",
                        __FILE__, __LINE__, octets, sizeof(buffer), rc);
                    ++errors;
                    break;
                }
                if ('\0' != buffer[rc - 1]) {
                    errorf("%s[%d]: [%lu] (NUL!=0x%hhx[%zd])!\n",
                        __FILE__, __LINE__, octets, buffer[rc - 1], rc - 1);
                    ++errors;
                    break;
                }
                octets += rc;
                rc2 = output(buffer);
                if (EOF == rc2) {
                    errorf("%s[%d]: [%lu] output(buffer)!\n",
                        __FILE__, __LINE__, octets);
                    std::perror("output(buffer)");
                    ++errors;
                    break;
                }
                if ((rc - 1) != rc2) {
                    errorf("%s[%d]: [%lu] (%zd!=%zd)\n",
                        __FILE__, __LINE__, octets, rc - 1, rc2);
                    ++errors;
                    break;
                }
            }
        }
        break;

    //
    // String.
    //
    case 's':
        {
            char buffer[16 + 1];
            ssize_t rc;
            ssize_t rc2;
            while (true) {
                rc = input(buffer, sizeof(buffer) - 1);
                if (EOF == rc) {
                    if (0 != errno) {
                        errorf(
                            "%s[%d]: [%lu] input(buffer, size)!\n",
                            __FILE__, __LINE__, octets);
                        std::perror("input(buffer, size)");
                        ++errors;
                    }
                    break;
                }
                if (0 == rc) {
                    errorf("%s[%d]: [%lu] (0==%zd)!\n",
                        __FILE__, __LINE__, octets, rc);
                    ++errors;
                    continue;
                }
                if (static_cast<int>(sizeof(buffer)) <= rc) {
                    errorf("%s[%d]: [%lu] (%lu<%zd)!\n",
                        __FILE__, __LINE__, octets, sizeof(buffer), rc);
                    ++errors;
                    break;
                }
                if ('\0' != buffer[rc - 1]) {
                    errorf("%s[%d]: [%lu] (NUL!=0x%hhx[%zd])!\n",
                        __FILE__, __LINE__, octets, buffer[rc - 1], rc - 1);
                    ++errors;
                    break;
                }
                octets += rc;
                buffer[rc - 1] = '!';
                buffer[rc] = '\0';
                rc2 = output(buffer, rc - 1);
                if (EOF == rc2) {
                    errorf(
                        "%s[%d]: [%lu] output(buffer, size)!\n",
                        __FILE__, __LINE__, octets);
                    std::perror("output(buffer, size)");
                    ++errors;
                    break;
                }
                if ((rc - 1) != rc2) {
                    errorf("%s[%d]: [%lu] (%zd!=%zd)\n",
                        __FILE__, __LINE__, octets, rc - 1, rc2);
                    ++errors;
                    break;
                }
            }
        }
        break;

    //
    // Formatted.
    //
    case 'f':
        {
            char buffer[257];
            ssize_t rc;
            ssize_t rc2;
            Print outputf(output);
            while (true) {
                rc = input(buffer, sizeof(buffer));
                if (EOF == rc) {
                    if (0 != errno) {
                        errorf(
                            "%s[%d]: [%lu] input(buffer, size)!\n",
                            __FILE__, __LINE__, octets);
                        std::perror("input(buffer, size)");
                        ++errors;
                    }
                    break;
                }
                if (0 == rc) {
                    errorf("%s[%d]: [%lu] (0==%zd)!\n",
                        __FILE__, __LINE__, octets, rc);
                    ++errors;
                    continue;
                }
                if (static_cast<int>(sizeof(buffer)) < rc) {
                    errorf("%s[%d]: [%lu] (%lu<%zd)!\n",
                        __FILE__, __LINE__, octets, sizeof(buffer), rc);
                    ++errors;
                    break;
                }
                if ('\0' != buffer[rc - 1]) {
                    errorf("%s[%d]: [%lu] (NUL!=0x%hhx[%zd])!\n",
                        __FILE__, __LINE__, octets, buffer[rc - 1], rc - 1);
                    ++errors;
                    break;
                }
                octets += rc;
                rc2 = outputf("%s", buffer);
                if (EOF == rc2) {
                    errorf("%s[%d]: [%lu] outputf(buffer)!\n",
                        __FILE__, __LINE__, octets);
                    std::perror("outputf(buffer)");
                    ++errors;
                    break;
                }
                if ((rc - 1) != rc2) {
                    errorf("%s[%d]: [%lu] (%zd!=%zd)\n",
                        __FILE__, __LINE__, octets, rc - 1, rc2);
                    ++errors;
                    break;
                }
            }
        }
        break;

    //
    // Binary (or maybe Block).
    //
    case 'b':
        {
            char buffer[output.minimum_buffer_size];
            ssize_t rc;
            ssize_t rc2;
            while (true) {
                rc = input(buffer, 1, sizeof(buffer));
                if (EOF == rc) {
                    if (0 != errno) {
                        errorf(
                            "%s[%d]: [%lu] input(buffer, minimum, maximum)!\n",
                            __FILE__, __LINE__, octets);
                        std::perror("input(buffer, minimum, maximum)");
                        ++errors;
                    }
                    break;
                }
                if (0 == rc) {
                    errorf("%s[%d]: [%lu] (0==%zd)!\n",
                        __FILE__, __LINE__, octets, rc);
                    ++errors;
                    continue;
                }
                if (static_cast<ssize_t>(sizeof(buffer)) < rc) {
                    errorf("%s[%d]: [%lu] (%lu<%zd)!\n",
                        __FILE__, __LINE__, octets, sizeof(buffer), rc);
                    ++errors;
                    break;
                }
                octets += rc;
                rc2 = output(buffer, rc, rc);
                if (EOF == rc2) {
                    errorf(
                        "%s[%d]: [%lu] output(buffer, size, count)!\n",
                        __FILE__, __LINE__, octets);
                    std::perror("output(buffer, size, count)");
                    ++errors;
                    break;
                }
                if (rc != rc2) {
                    errorf("%s[%d]: [%lu] (%zd!=%zd)\n",
                        __FILE__, __LINE__, octets, rc, rc2);
                    ++errors;
                    break;
                }
            }
        }
        break;

    default:
        errorf("%s[%d]: (0x%x)!\n",
            __FILE__, __LINE__, mechanism);
        ++errors;
        break;

    }

    errorf("%s[%d]: after\n", __FILE__, __LINE__);
    errorf(" input:\n");
    input.show(0, &(Platform::instance().error()), 2);
    errorf(" output:\n");
    output.show(0, &(Platform::instance().error()), 2);

    errorf("%s[%d]: end octets=%u errors=%d\n",
        __FILE__, __LINE__, octets, errors);

    return errors;
}
