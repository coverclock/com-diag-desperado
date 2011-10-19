:
# vi: set ts=4:

###############################################################################
#
#   Copyright 2006-2008 Digital Aggregates Corp., Arvada CO 80001-0587, USA.
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
#   $Id: ficlshell.sh,v 1.4 2006/09/12 14:52:25 jsloan Exp $
#
###############################################################################

#
#   Generate the Ficl API symbol .c file to standard output given an
#   input file of symbol and name tuples. We have to make several passes
#   on the input file to do this.
#

if [ $# -eq 0 ]; then
    echo "usage: $0 sfile [ sfile ... ]" 1>&2
    exit 1
fi

TIMESTAMP="`date`"

echo "/*"
echo " * Copyright 2006-2008 Digital Aggregates Corp.,"
echo " * Arvada CO 80001-0587, USA. Licensed under"
echo " * the same terms as the Desperado library."
echo " * This file was generated automatically"
echo " * by the Desperado $0 script"
echo " * on ${TIMESTAMP}."
echo " */"
echo "#include \"desperado/target.h\""
echo "#include \"desperado/ficlApi.h\""
echo "#if defined(DESPERADO_HAS_FICL)"

for FILE in $*; do
    (
        while read SYMBOL NAME; do
			case "${SYMBOL}" in
			ficl[A-Z]*) continue;;
			desperado_ficl_*) continue;;
			esac
            echo "extern int ${SYMBOL}(void);"
            echo "static void desperado_ficl_symbol_${SYMBOL}(ficlVm* pVM) {"
			echo "    uintptr_t _integer = (uintptr_t)(&${NAME});"
			echo "    void* _pointer = (void*)_integer;"
            echo "    ficlStackPushPointer(pVM->dataStack, _pointer);"
            echo "}"
        done
    ) < $FILE
done

echo "void desperado_ficl_shell(ficlSystem* s) {"
echo "    ficlDictionary* d = ficlSystemGetDictionary(s);"
echo "    ficlDictionaryLock(d, ~0);"
echo "    ficlDictionaryAppendPrimitive(d, \"((\", &desperado_ficl_openparens, 0);"
echo "    ficlDictionaryAppendPrimitive(d, \"))\", &desperado_ficl_closeparens, 0);"
echo "    ficlDictionaryAppendPrimitive(d, \"(())\", &desperado_ficl_null, 0);"
echo "    ficlDictionaryAppendPrimitive(d, \"((...))\", &desperado_ficl_parens, 0);"

for FILE in $*; do
    (
        while read SYMBOL NAME; do
			case "${SYMBOL}" in
			ficl[A-Z]*) continue;;
			desperado_ficl_*) continue;;
			esac
            echo "    ficlDictionaryAppendPrimitive(d, \"${NAME}\", &desperado_ficl_symbol_${SYMBOL}, 0);"
        done
    ) < ${FILE}
done

echo "    ficlDictionaryLock(d, 0);"
echo "}"
echo "#else"
echo "void desperado_ficl_shell(void* unused) {"
echo "}"
echo "#endif"

exit 0
