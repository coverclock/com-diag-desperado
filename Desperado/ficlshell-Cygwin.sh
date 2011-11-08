:
# vi: set ts=4:

###############################################################################
#
#	Copyright 2006 Digital Aggregates Corporation, Colorado, USA.
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
#   $Name:  $
#
#   $Id: ficlshell-Cygwin.sh,v 1.1 2006/01/09 00:24:49 jsloan Exp $
#
###############################################################################

#
#   Extract symbols for functions and variables from each
#   object file spcified on the command line. Emit a stream
#   of tuples, in which the first element is the actual symbol
#   from the object file, and the second element is the name
#   that will be used for the symbol.
#

if [ $# -eq 0 ]; then
    echo "usage: $0 ofile [ ofile ... ]" 1>&2
    exit 1
fi

for FILE in $*; do
    nm ${FILE} | awk '($2~/^[BDT]$/)&&($3!~/^__/) { symbol=substr($3,2,length($3)-1); print symbol, symbol; }'
done

exit 0
