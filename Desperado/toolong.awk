#	:set ts=4
#
#	toolong.awk: display source lines that are too long.
#	Copyright 2005 Digital Aggregates Corp., Arvada CO 80001-0587, USA.
#
#	This program is free software; you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation; either version 2 of the License, or
#	(at your option) any later version.
#
#	This program is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with this program; if not, write to the Free Software
#	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
#	$Name:  $
#
#	$Id: toolong.awk,v 1.5 2006/01/09 00:24:49 jsloan Exp $
#
#	coverclock@diag.com (Chip Overclock)
#

(length($0) > 80) {
	print FILENAME "[" NR "](" length($0) "): " $0;
}
