:
# vi: set ts=4:

###############################################################################
#
#   Copyright 2006-2011 Digital Aggregates Corporation, Colorado, USA.
#   This file is part of the Digital Aggregates Desperado library.
#   
#   This library is free software; you can redistribute it and/or
#   modify it under the terms of the GNU Lesser General Public
#   License as published by the Free Software Foundation; either
#   version 2.1 of the License, or (at your option) any later version.
#
#   As a special exception, if other files instantiate templates or
#   use macros or inline functions from this file, or you compile
#   this file and link it with other works to produce a work based on
#   this file, this file does not by itself cause the resulting work
#   to be covered by the GNU Lesser General Public License. However
#   the source code for this file must still be made available in
#   accordance with the GNU Lesser General Public License.
#
#   This exception does not invalidate any other reasons why a work
#   based on this file might be covered by the GNU Lesser General
#   Public License.
#
#   Alternative commercial licensing terms are available from the copyright
#   holder. Contact Digital Aggregates Corporation for more information.
#
#   This library is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General
#   Public License along with this library; if not, write to the
#   Free Software Foundation, Inc., 59 Temple Place, Suite 330,
#   Boston, MA 02111-1307 USA, or http://www.gnu.org/copyleft/lesser.txt.
#
###############################################################################

TOTAL=0
NAME="`basename $0`"
PID=$$
COMMANDPATH=.
if [ "$TMPDIR" = "" ]; then
    TMPDIR="/var/tmp"
fi
SCRIPT1=$TMPDIR/$NAME.$PID.1.sh
SCRIPT2=$TMPDIR/$NAME.$PID.2.sh
SCRIPT3=$TMPDIR/$NAME.$PID.3.sh
SCRIPT4=$TMPDIR/$NAME.$PID.4.sh

STATUS0=$TMPDIR/$NAME.$PID.0.txt
STATUS1=$TMPDIR/$NAME.$PID.1.txt
STATUS2=$TMPDIR/$NAME.$PID.2.txt
STATUS3=$TMPDIR/$NAME.$PID.3.txt
STATUS4=$TMPDIR/$NAME.$PID.4.txt

trap "rm -f $SCRIPT1 $SCRIPT2 $SCRIPT3 $SCRIPT4 $STATUS0 $STATUS1 $STATUS2 $STATUS3 $SCRIPT4" 1 2 3 15

TS="`date -u +'%Y-%m-%dT%H:%M:%S.%N%Z'`"
echo "$NAME[$PID]: $TS begin"

# Errors in these commands do not count.
cat << EOF > $SCRIPT1
unittestassert
EOF

# Errors in these commands do count.
cat << EOF > $SCRIPT2
unittestArgument
unittestAscii
unittestAttribute
unittestBandwidthThrottle
unittestByteOrder
unittestCellRateThrottle
unittestChain
unittestCounters
unittestCrc
unittestDump
unittestEncode
unittestEscape
unittestException
unittestFicl
unittestFiclShell
unittestFifo
unittestGeometricThrottle
unittestGrayCode
unittestHeap
unittestImplementation
unittestInputOutputStatic
unittestIso3166
unittestJavaVirtualMachine
unittestLinkType
unittestLogger
unittestMeter
unittestMinimumMaximum
unittestMutex
unittestNumber
unittestPlatform
unittestRam
unittestService
unittestStreamSocket
unittestThrottle
unittestVintage
unittestWord
unittestbarrier
unittestcxxcapi
unittestcxxjapi
unittestgenerics
unittestnamespace
unitteststring
unittesttarget
EOF

# These commands are shell scripts.
cat << EOF > $SCRIPT3
unittestInputOutput.sh
EOF

# These commands take eons to run so we do them last.
cat << EOF > $SCRIPT4
unittestCommonEra
EOF

# Verify that we have everything.

cat $SCRIPT1 $SCRIPT2 $SCRIPT3 $SCRIPT4 | (
	ERRORS=0
    while read COMMAND; do
		echo $COMMAND
        if [ ! -f $COMMAND ]; then
			echo "$COMMAND: no such file!" 1>&2
        	ERRORS=`expr $ERRORS + 1`
		fi
    done
	echo $ERRORS > $STATUS0
)

TS="`date -u +'%Y-%m-%dT%H:%M:%S.%N%Z'`"
ERRORS0=`cat $STATUS0`
TOTAL=`expr $TOTAL + $ERRORS0`
echo "$NAME[$PID]: $TS errors=$TOTAL"
if [ $TOTAL -gt 0 ]; then
	exit $TOTAL
fi

# Run the tests.

(
	ERRORS=0
    while read COMMAND; do
		TS="`date -u +'%Y-%m-%dT%H:%M:%S.%N%Z'`"
        echo "$NAME[$PID]: $TS begin \"$COMMAND $ARGUMENTS\""
        $COMMANDPATH/$COMMAND
        RC=$?
		TS="`date -u +'%Y-%m-%dT%H:%M:%S.%N%Z'`"
        echo "$NAME[$PID]: $TS end \"$COMMAND $ARGUMENTS\" errors=$RC"
        ERRORS=`expr $ERRORS + $RC`
    done
	echo 0 > $STATUS1
) < $SCRIPT1

TS="`date -u +'%Y-%m-%dT%H:%M:%S.%N%Z'`"
ERRORS1=`cat $STATUS1`
TOTAL=`expr $TOTAL + $ERRORS1`
echo "$NAME[$PID]: $TS errors=$TOTAL"

(
	ERRORS=0
    while read COMMAND; do
		TS="`date -u +'%Y-%m-%dT%H:%M:%S.%N%Z'`"
        echo "$NAME[$PID]: $TS begin \"$COMMAND $ARGUMENTS\""
        $COMMANDPATH/$COMMAND
        RC=$?
		TS="`date -u +'%Y-%m-%dT%H:%M:%S.%N%Z'`"
        echo "$NAME[$PID]: $TS end \"$COMMAND $ARGUMENTS\" errors=$RC"
        ERRORS=`expr $ERRORS + $RC`
    done
	echo $ERRORS > $STATUS2
) < $SCRIPT2

TS="`date -u +'%Y-%m-%dT%H:%M:%S.%N%Z'`"
ERRORS2=`cat $STATUS2`
TOTAL=`expr $TOTAL + $ERRORS2`
echo "$NAME[$PID]: $TS errors=$TOTAL"

(
    while read COMMAND; do
		TS="`date -u +'%Y-%m-%dT%H:%M:%S.%N%Z'`"
        echo "$NAME[$PID]: $TS begin \"$COMMAND $ARGUMENTS\""
        sh $COMMANDPATH/$COMMAND
        RC=$?
		TS="`date -u +'%Y-%m-%dT%H:%M:%S.%N%Z'`"
        echo "$NAME[$PID]: $TS end \"$COMMAND $ARGUMENTS\" errors=$RC"
        ERRORS=`expr $ERRORS + $RC`
    done
	echo $ERRORS > $STATUS3
) < $SCRIPT3

TS="`date -u +'%Y-%m-%dT%H:%M:%S.%N%Z'`"
ERRORS3=`cat $STATUS3`
TOTAL=`expr $TOTAL + $ERRORS3`
echo "$NAME[$PID]: $TS errors=$TOTAL"

(
    ERRORS=0
    while read COMMAND; do
        TS="`date -u +'%Y-%m-%dT%H:%M:%S.%N%Z'`"
        echo "$NAME[$PID]: $TS begin \"$COMMAND $ARGUMENTS\""
        $COMMANDPATH/$COMMAND
        RC=$?
        TS="`date -u +'%Y-%m-%dT%H:%M:%S.%N%Z'`"
        echo "$NAME[$PID]: $TS end \"$COMMAND $ARGUMENTS\" errors=$RC"
        ERRORS=`expr $ERRORS + $RC`
    done
    echo $ERRORS > $STATUS4
) < $SCRIPT4

TS="`date -u +'%Y-%m-%dT%H:%M:%S.%N%Z'`"
ERRORS4=`cat $STATUS4`
TOTAL=`expr $TOTAL + $ERRORS4`
echo "$NAME[$PID]: $TS errors=$TOTAL"

rm -f $SCRIPT1 $SCRIPT2 $SCRIPT3 $SCRIPT4 $STATUS0 $STATUS1 $STATUS2 $STATUS3 $STATUS4

exit $TOTAL
