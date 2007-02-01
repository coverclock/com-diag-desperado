(   Copyright 2006 Digital Aggregates Corp., Arvada CO 80001-0587, USA.       )
(   This file is part of the Digital Aggregates Desperado library.            )
(                                                                             )
(   This library is free software; you can redistribute it and/or             )
(   modify it under the terms of the GNU Lesser General Public                )
(   License as published by the Free Software Foundation; either              )
(   version 2.1 of the License, or at your option any later version.          )
(                                                                             )
(   As a special exception, if other files instantiate templates or           )
(   use macros or inline functions from this file, or you compile             )
(   this file, this file does not by itself cause the resulting work          )
(   to be covered by the GNU Lesser General Public License. However           )
(   the source code for this file must still be made available in             )
(   accordance with the GNU Lesser General Public License.                    )
(                                                                             )
(   This exception does not invalidate any other reasons why a work           )
(   based on this file might be covered by the GNU Lesser General             )
(   Public License.                                                           )
(                                                                             )
(   Alternative commercial licensing terms are available from the copyright   )
(   holder. Contact Digital Aggregates Corporation for more information.      )
(                                                                             )
(   This library is distributed in the hope that it will be useful,           )
(   but WITHOUT ANY WARRANTY; without even the implied warranty of            )
(   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             )
(   GNU Lesser General Public License for more details.                       )
(                                                                             )
(   You should have received a copy of the GNU Lesser General                 )
(   Public License along with this library; if not, write to the              )
(   Free Software Foundation, Inc., 59 Temple Place, Suite 330,               )
(   Boston, MA 02111-1307 USA, or http://www.gnu.org/copyleft/lesser.txt.     )
(                                                                             )
(   $Name:  $                                                                    )
(                                                                             )
(   $Id: unittestsuite.4th,v 1.2 2006/01/30 20:35:27 jsloan Exp $                                                                      )

VARIABLE errors

: tally ." incremental errors=" DUP . cr
        errors @ + errors !
       ." total errors=" errors @ . cr ;

: unittestsuitebegin ." begin" cr
                     0 errors ! ;

: unittestsuiteend ." end errors=" errors @ . cr ;

: unittestsuite
    unittestsuitebegin
    unittestArgument (()) tally
    unittestAscii (()) tally
    unittestAttribute (( 0 )) tally
    unittestChain (()) tally
    unittestLinkType (()) tally
    unittestCounters (()) tally
    unittestCrc (()) tally
    unittestDump (()) tally
    unittestEncode (()) tally
    unittestEscape (()) tally
    unittestException (()) tally
    unittestFicl (( 0 )) tally
    unittestFiclShell (( 0 )) tally
    unittestGrayCode (()) tally
    unittestHeap (()) tally
    unittestHeap2 (()) tally
    unittestHeap3 (()) tally
    unittestLogger (()) tally
    unittestLogger2 (()) tally
    unittestImplementation (()) tally
    unittestInputOutputStatic (()) tally
    unittestIso3166 (()) tally
    unittestMeter (()) tally
    unittestMinimumMaximum (()) tally
    unittestMutex (()) tally
    unittestNumber (()) tally
    unittestPlatform (()) tally
    unittestPlatform2 (()) tally
    unittestRam (()) tally
    unittestDelayThrottle (()) tally
    unittestVintage (()) tally
    unittestWord (( 0 )) tally
    unittestbarrier (()) tally
    unittestcxxcapi (()) tally
    unittestgenerics (()) tally
    unittestgenerics2 (()) tally
    unittestnamespace (()) tally
    unitteststring (()) tally
    unittesttarget (()) tally
    unittesttarget2 (()) tally
    unittestThrottle (()) tally
    unittestGeometricThrottle (( 250000000 )) tally
    unittestBandwidthThrottle (( 10240 250000 1024 10 100000 )) tally
    unittestCellRateThrottle (( 200 250 100 5 10000000 )) tally
    unittestFifo (()) tally
    unittestCommonEra (()) tally
    unittestsuiteend
;
