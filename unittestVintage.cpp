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

    $Id: unittestVintage.cpp,v 1.3 2006/01/09 00:24:49 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the Vintage unit test.
 *
 *  @see    Vintage
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.3 $
 *
 *  @date   $Date: 2006/01/09 00:24:49 $
 */


#include "Vintage.h"
#include "Print.h"
#include "Platform.h"
#include "Desperado.h"

static Vintage staticVintage;

extern "C" int unittestVintage() {
    Print printf(Platform::instance().output());
    int errors = 0;

    printf("%s[%d]: begin\n", __FILE__, __LINE__);

    ::staticVintage.show();

    Vintage vintage;
    vintage.show();

    Vintage vintage2 = vintage;
    vintage2.show();

    Vintage vintage3;
    vintage3 = vintage;
    vintage3.show();

    printf("product=\"%s\"\n", Vintage::product);
    printf("license=\"%s\"\n", Vintage::license);
    printf("copyright=\"%s\"\n", Vintage::copyright);
    printf("contact=\"%s\"\n", Vintage::contact);
    printf("url=\"%s\"\n", Vintage::url);
    printf("uri=\"%s\"\n", Vintage::uri);
    printf("date=\"%s\"\n", Vintage::date);
    printf("release=\"%s\"\n", Vintage::release);
    printf("build=\"%s\"\n", Vintage::build);

    printf("%s[%d]: end errors=%d\n",
        __FILE__, __LINE__, errors);

    return errors;
}
