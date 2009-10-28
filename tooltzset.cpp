/* vim: set ts=4 expandtab shiftwidth=4: */

/******************************************************************************

    Copyright 2005 Digital Aggregates Corp., Arvada CO 80001-0587, USA.
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

    $Id: tooltzset.cpp,v 1.3 2006/01/09 00:24:49 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the tzset command line tool.
 *
 *  @see    tzset
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.3 $
 *
 *  @date   $Date: 2006/01/09 00:24:49 $
 */


#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <sys/time.h>
#include "Platform.h"
#include "Desperado.h"

int main(int, char **, char **) {
    Platform::instance(Platform::factory());
    Print printf(Platform::instance().output());
    extern long timezone;
    extern int daylight;
    tzset();
    printf("timezone=%ld=0x%lx\n", timezone, timezone);
    printf("daylight=%d=0x%x\n", daylight, daylight);
    std::exit(0);
}
