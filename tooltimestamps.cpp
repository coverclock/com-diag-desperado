/* vim: set ts=4 expandtab shiftwidth=4: */

/******************************************************************************

    Copyright 2005-2011 Digital Aggregates Corporation, Colorado, USA.
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

    $Id: tooltimestamps.cpp,v 1.4 2006/01/09 00:24:49 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the timestamps command line tool.
 *
 *  @see    TimeStamp
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.4 $
 *
 *  @date   $Date: 2006/01/09 00:24:49 $
 */


#include <cstdlib>
#include "desperado/Platform.h"
#include "desperado/Print.h"
#include "desperado/LocalTime.h"
#include "desperado/TimeZone.h"
#include "desperado/TimeStamp.h"
#include "desperado/Desperado.h"

int main(int, char **, char **) {
    Print printf(Platform::instance().output());
    CommonEra ce;
    ce.fromNow();
    ce.show();
    LocalTime lt;
    lt.fromCommonEra(ce);
    lt.show();
    TimeStamp ts;
    printf("UTC iso8601:       %s\n", ts.iso8601(ce));
    printf("UTC milspec:       %s\n", ts.milspec(ce));
    printf("UTC civilian:      %s\n", ts.civilian(ce));
    printf("UTC log:           %s\n", ts.log(ce));
    printf("UTC formal:        %s\n", ts.formal(ce));
    printf("UTC highprecision: %s\n", ts.highprecision(ce));
    printf("LCT iso8601:       %s\n", ts.iso8601(lt));
    printf("LCT milspec:       %s\n", ts.milspec(lt));
    printf("LCT civilian:      %s\n", ts.civilian(lt));
    printf("LCT log:           %s\n", ts.log(lt));
    printf("LCT formal:        %s\n", ts.formal(lt));
    printf("LCT highprecision: %s\n", ts.highprecision(lt));

    std::exit(0);
}
