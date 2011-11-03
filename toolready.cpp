/* vim: set ts=4 expandtab shiftwidth=4: */

/******************************************************************************

    Copyright 2011 Digital Aggregates Corporation, Colorado, USA.
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

******************************************************************************/


/**
 *  @file
 *
 *  Implements the ready command line tool.
 *
 *  @see    desperado_descriptor_ready
 */


#include "com/diag/desperado/stdio.h"
#include "com/diag/desperado/stdlib.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "com/diag/desperado/target.h"
#include "com/diag/desperado/string.h"
#include "com/diag/desperado/Platform.h"
#include "com/diag/desperado/DescriptorInput.h"
#include "com/diag/desperado/DescriptorOutput.h"
#include "com/diag/desperado/ready.h"
#include "com/diag/desperado/errno.h"
#include "com/diag/desperado/Desperado.h"

int main(int argc, char ** argv, char **) {
    Print errorf(Platform::instance().error());

    char * cmdname = std::strrchr(argv[0],'/');
    if (0 != cmdname) {
        ++cmdname;
    } else {
        cmdname = argv[0];
    }

    if (argc != 5) {
    	errorf("%s: inputbytes inputfile outputbytes outputfile\n", cmdname);
    	std::exit(1);
    }

    size_t inputbytes = ::strtoul(argv[1], 0, 0);
    const char * inputfile = argv[2];
    size_t outputbytes = ::strtoul(argv[3], 0, 0);
    const char * outputfile = argv[4];

    int in;
    if (std::strcmp(inputfile, "-") == 0) {
    	in = STDIN_FILENO;
    } else if ((in = ::open(inputfile, O_RDONLY)) < 0) {
    	::perror(argv[1]);
    	std::exit(2);
    } else {
    	// Do nothing.
    }

    errorf("input=\"%s\" fd=%d bytes=%zu\n", inputfile, in, inputbytes);

    DescriptorInput input(in);

    int out;
    if (std::strcmp(outputfile, "-") == 0) {
    	out = STDOUT_FILENO;
    } else if ((out = ::open(outputfile, O_WRONLY | O_CREAT, 0644)) < 0) {
    	::perror(argv[2]);
    	std::exit(3);
    } else {
    	// Do nothing.
    }

    errorf("output=\"%s\" fd=%d bytes=%zu\n", outputfile, out, outputbytes);

    DescriptorOutput output(out);

    char buffer[256];
    ssize_t ins;
    ssize_t outs;
    const char * bb;
    int rc;

    bool debug = true;

    while (true) {

    	if (debug || !isatty(in)) {
			rc = desperado_descriptor_ready(in);
			errorf("desperado_descriptor_ready(%d)=%d%s%s%s\n",
				in, rc,
				((rc & DESPERADO_DESCRIPTOR_READY_READ) != 0) ? " READ": "",
				((rc & DESPERADO_DESCRIPTOR_READY_WRITE) != 0) ? " WRITE": "",
				((rc & DESPERADO_DESCRIPTOR_READY_EXCEPTION) != 0) ? " EXCEPTION": ""
			);
    	}

    	ins = input(buffer, (inputbytes < sizeof(buffer)) ? inputbytes : sizeof(buffer), sizeof(buffer));
    	if (debug || !isatty(in)) {
    		errorf("input()=%zd\n", ins);
    	}
    	if (ins < 0) {
    		std::exit(4);
    	} else if (ins == 0) {
			Platform::instance().yield(Platform::instance().frequency(), true);
			continue;
    	}

    	if (debug || !isatty(out)) {
			rc = desperado_descriptor_ready(out);
			errorf("desperado_descriptor_ready(%d)=%d%s%s%s\n",
				out, rc,
				((rc & DESPERADO_DESCRIPTOR_READY_READ) != 0) ? " READ": "",
				((rc & DESPERADO_DESCRIPTOR_READY_WRITE) != 0) ? " WRITE": "",
				((rc & DESPERADO_DESCRIPTOR_READY_EXCEPTION) != 0) ? " EXCEPTION": ""
			);
    	}

    	bb = buffer;
    	while (ins > 0) {
    		outs = output(bb, (outputbytes < static_cast<size_t>(ins)) ? outputbytes : static_cast<size_t>(ins), static_cast<size_t>(ins));
        	if (debug || !isatty(out)) {
        		errorf("output()=%zd\n", outs);
        	}
    		if (outs < 0) {
    			std::exit(5);
    		} else if (outs > 0) {
    			bb += outs;
    			ins -= outs;
    		} else {
    			Platform::instance().yield(Platform::instance().frequency(), true);
    		}
    	}


    }

    std::exit(0);
}
