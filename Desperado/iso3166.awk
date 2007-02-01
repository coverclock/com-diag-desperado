#	:set ts=4
#
#	iso3166.awk: parses lines from RIPE ISO 3166-1 country code list.
#	Copyright 2003 Digital Aggregates Corp., Arvada CO 80001-0587, USA.
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
#	$Id: iso3166.awk,v 1.6 2006/01/09 00:24:49 jsloan Exp $
#
#	coverclock@diag.com (Chip Overclock)
#

BEGIN	{
			line = 0;
			longest = 0;
		}

		{
			Country = substr($0, 1, 48);
			A2 = substr($0, 49, 2);
			A3 = substr($0, 57, 3);
			Number = substr($0, 65, 3);

			Name = Country;
			gsub(" [ ]*$", "", Name);

			Symbol = toupper(Name);
			gsub("[^a-zA-Z0-9]", "_", Symbol);
			gsub("__[_]*", "_", Symbol);
			gsub("_[_]*$", "", Symbol);

			Numeric = Number;
			gsub("^0[0]*", "", Numeric);

			size = length(Name);
			if (size > longest) {
				longest = size;
			}

			Names[line] = Name;
			Symbols[line] = Symbol;
			A2s[line] = A2;
			A3s[line] = A3;
			Numbers[line] = Number;
			Numerics[line] = Numeric;

			line++;
		}

END		{
			print "\tstruct Entry {";
			print "\t\tchar country[" longest " + 1];";
			print "\t\tchar a2[2 + 1];";
			print "\t\tchar a3[3 + 1];";
			print "\t\tint  number;";
			print "\t};";

			print "\tenum Index {";
			for (ii = 0; ii < line; ii++) {
				if ((line - 1) == ii) {
					last = "";
				} else {
					last = ",";
				}
				print "\t\t" Symbols[ii] " = " ii ",";
				print "\t\tA2_" A2s[ii] " = " ii ",";
				print "\t\tA3_" A3s[ii] " = " ii ",";
				print "\t\tN_" Numbers[ii] " = " ii last;
			}
			print "\t};";

			print "const Entry table[" line "] = {";
			for (ii = 0; ii < line; ii++) {
				if ((line - 1) == ii) {
					last = "";
				} else {
					last = ",";
				}
				print "\t{ \"" Names[ii] "\", \"" A2s[ii] "\", \"" A3s[ii] "\", " Numerics[ii] " }" last;
			}
			print "};";
		}
