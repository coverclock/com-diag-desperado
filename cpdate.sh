:
# vi: set ts=4:

###############################################################################
#
#   Copyright 2006 Digital Aggregates Corporation, Colorado, USA.
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

#       
#   cpdate.sh: make a timestamped backup copy of a file.
#
#   usage:  cpdate file [ dir ]
#

USAGE="`basename $0` file [ dir ]"
TS="`date -u +%Y%m%d%H%M%S%N%Z`"
if [ 1 -le $# -a $# -le 2 ]; then
    if [ -f $1 ]; then
        if [ $# -eq 1 ]; then
            TO="$1-$TS"
        elif [ -d $2 ]; then
            BN="`basename $1`"
            TO="$2/$BN-$TS"
        fi
        cp -i $1 $TO && chmod u-wx,g-wx,o-wx $TO
        exit $?
    fi
fi
echo "$USAGE" 1>&2
exit 1
