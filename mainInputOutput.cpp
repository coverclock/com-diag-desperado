/* vim: set ts=4 expandtab shiftwidth=4: */

/******************************************************************************

    Copyright 2006 Digital Aggregates Corp., Arvada CO 80001-0587, USA.
    This file is part of the Digital Aggregates Desperado library.
    
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    As a special exception, if other files instantiate templates or
    use macros or inline functions from this file, or you compile
    this file and link it with other works to produce a work based on
    this file, this file does not by itself cause the resulting work
    to be covered by the GNU Lesser General Public License. However
    the source code for this file must still be made available in
    accordance with the GNU Lesser General Public License.

    This exception does not invalidate any other reasons why a work
    based on this file might be covered by the GNU Lesser General
    Public License.

    Alternative commercial licensing terms are available from the copyright
    holder. Contact Digital Aggregates Corporation for more information.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General
    Public License along with this library; if not, write to the
    Free Software Foundation, Inc., 59 Temple Place, Suite 330,
    Boston, MA 02111-1307 USA, or http://www.gnu.org/copyleft/lesser.txt.

    $Name:  $

    $Id: mainInputOutput.cpp,v 1.6 2006/08/04 20:42:46 jsloan Exp $

******************************************************************************/


/**
 *  @file
 *
 *  Implements the InputOutput unit test main program.
 *
 *  @see    InputOutput
 *
 *  @author $Author: jsloan $
 *
 *  @version    $Revision: 1.6 $
 *
 *  @date   $Date: 2006/08/04 20:42:46 $
 */


#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "desperado/UnitTest.h"
#include "desperado/stdio.h"
#include "desperado/stdio.h"
#include "desperado/errno.h"
#include "desperado/errno.h"
#include "desperado/string.h"
#include "desperado/string.h"
#include "desperado/Platform.h"
#include "desperado/Platform.h"
#include "desperado/DescriptorInput.h"
#include "desperado/DescriptorInput.h"
#include "desperado/DescriptorOutput.h"
#include "desperado/DescriptorOutput.h"
#include "desperado/FileInput.h"
#include "desperado/FileInput.h"
#include "desperado/FileOutput.h"
#include "desperado/FileOutput.h"
#include "desperado/BufferInput.h"
#include "desperado/BufferInput.h"
#include "desperado/BufferOutput.h"
#include "desperado/BufferOutput.h"
#include "desperado/PathInput.h"
#include "desperado/PathInput.h"
#include "desperado/PathOutput.h"
#include "desperado/PathOutput.h"
#include "desperado/DumpInput.h"
#include "desperado/DumpInput.h"
#include "desperado/DumpOutput.h"
#include "desperado/DumpOutput.h"
#include "desperado/Print.h"
#include "desperado/Print.h"
#include "desperado/reads.h"
#include "desperado/reads.h"
#include "desperado/writes.h"
#include "desperado/writes.h"
#include "desperado/Heap.h"
#include "desperado/Heap.h"

#define USAGE   \
    "[ -d(ebug) ]" \
    " [ -c(haracter) | -l(ine) | -b(lock) | -s(tring) | -f(ormatted) ]" \
    " [ -D(escriptor) | -F(ile) | -I(pc) | -N(ull) | -P(ath) | -S(tring) ]" \
    " [ -o(utout) [ outname | - ] ]" \
    " [ [ inname | - ] ... ]"

int main(int argc, char **argv, char **) {
    extern char *optarg;
    extern int optind;
    int opt;
    int inerror;
    int usage;
    int rc;

    int errors = 0;

    bool debug = false;
    bool help = false;

    const char *outname = "-";
    char method = 0;
    char object = 0;
    char* cmdname;

    Platform::instance(Platform::factory());
    Print errorf(Platform::instance().error());

    errorf("%s[%d]: begin\n", __FILE__, __LINE__);

    cmdname = (0 == (cmdname = std::strrchr(argv[0],'/')))
                ? argv[0] : cmdname + 1;

    usage = 0;
    while (0 <= (opt = ::getopt(argc, argv, "?bcdflo:rsDFINPS"))) {
        inerror = 0;
        switch (opt) {
        case '?':
            help = true;
            break;
        case 'd':
            debug = true;
            break;
        case 'b':
        case 'c':
        case 'f':
        case 'l':
        case 's':
            method = opt;
            break;
        case 'D':
        case 'F':
        case 'I':
        case 'N':
        case 'P':
        case 'S':
            object = opt;
            break;
        case 'o':
            outname = optarg;
            break;
        default:
            ++usage;
        }
        if (0 < inerror) {
            errorf("%s: bad value -- -%c %s\n",
                cmdname, opt, optarg);
            ++usage;
        }
    }

    if (help || (0 < usage) || (0 == method) || (0 == object)) {
        errorf("usage: %s %s\n", cmdname, USAGE);
        ::exit(help ? 0 : 1);
    }

    Output* outputp = 0;
    FILE* outfile = 0;
    int outsocket = EOF;
    Dump dump;
    DumpOutput dumpoutput;
    DumpInput dumpinput;

    switch (object) {

    case 'D':
        if (0 == std::strcmp(outname, "-")) {
            outsocket = 1;
        } else {
            outsocket = ::open(outname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        }
        if (0 <= outsocket) {
            outputp = new DescriptorOutput(outsocket);
        } else {
            std::perror(outname);
            ++errors;
        }
        break;

    case 'F':
        if (0 == std::strcmp(outname, "-")) {
            outfile = stdout;
        } else {
            outfile = std::fopen(outname, "w");
        }
        if (0 != outfile) {
            outsocket = fileno(outfile);
            outputp = new FileOutput(outfile);
        } else {
            std::perror(outname);
            ++errors;
        }
        break;

    case 'N':
        outputp = new Output;
        break;

    case 'P':
        try {
            outputp = new PathOutput(outname);
        } catch (...) {
            outputp = 0;
            std::perror(outname);
            ++errors;
        }
        break;

    case 'S':
        if (0 == std::strcmp(outname, "-")) {
            outfile = stdout;
        } else {
            outfile = std::fopen(outname, "w");
        }
        if (0 != outfile) {
            outsocket = fileno(outfile);
        } else {
            std::perror(outname);
            ++errors;
        }
        break;

    }

    const char *inname = "-";
    FILE* infile = 0;
    int insocket = EOF;
    char* instring = 0;
    char* outstring = 0;
    Heap heap;
    struct stat status;
    size_t size = 0;
    ssize_t fc;
    Input* inputp = 0;
    BufferInput* si = 0;
    BufferOutput* so = 0;

    do {

        if (0 == argv[optind]) {
            inname = "-";
        } else {
            inname = argv[optind++];
        }

        switch (object) {

        case 'D':
            if (0 == std::strcmp(inname, "-")) {
                insocket = 0;
            } else {
                insocket = ::open(inname, O_RDONLY);
            }
            if (0 <= insocket) {
                inputp = new DescriptorInput(insocket);
            } else {
                std::perror(inname);
                ++errors;
            }
            break;

        case 'F':
            if (0 == std::strcmp(inname, "-")) {
                infile = stdin;
            } else {
                infile = std::fopen(inname, "r");
            }
            if (0 != infile) {
                insocket = fileno(infile);
                inputp = new FileInput(infile);
            } else {
                std::perror(inname);
                ++errors;
            }
            break;

        case 'N':
            inputp = new Input;
            break;

        case 'P':
            try {
                inputp = new PathInput(inname);
            } catch (...) {
                inputp = 0;
                std::perror(inname);
                ++errors;
            }
            break;

        case 'S':
            do {
                if (0 == std::strcmp(inname, "-")) {
                    infile = stdin;
                } else {
                    infile = std::fopen(inname, "r");
                }
                if (0 == infile) {
                    std::perror(inname);
                    ++errors;
                    break;
                }
                insocket = fileno(infile);
                if (0 != ::fstat(insocket, &status)) {
                    std::perror("fstat");
                    ++errors;
                    break;
                }
                size = status.st_size;
                instring = reinterpret_cast<char*>(heap.malloc(size));
                if (0 == instring) {
                    std::perror("instring=heap.malloc(size)");
                    ++errors;
                    break;
                }
                si = new BufferInput(instring, size);
                inputp = si;
                if (0 == inputp) {
                    std::perror("new BufferInput(instring,size)");
                    ++errors;
                    break;
                }
                fc = ::reads(insocket, si->getString(),
                        si->getSize(), si->getSize());
                if (static_cast<ssize_t>(size) != fc) {
                    heap.free(instring);
                    instring = 0;
                    std::perror("reads(insocket,instring,size,size)");
                    ++errors;
                    break;
                }
                outstring = reinterpret_cast<char*>(heap.malloc(size));
                if (0 == outstring) {
                    std::perror("outstring=heap.malloc(size)");
                    ++errors;
                    break;
                }
                so = new BufferOutput(outstring, size);
                outputp = so;
                if (0 == outputp) {
                    std::perror("new BufferInput(outstring,size)");
                    ++errors;
                    break;
                }
            } while (false);
            break;

        }

        if ((0 == inputp) || (0 == outputp)) {
            ::exit(errors);
        }

        if (debug) {
            dumpinput.initialize(*inputp, dump);
            dumpoutput.initialize(*outputp, dump);
            inputp = &dumpinput;
            outputp = &dumpoutput;
        }

        rc = unittestInputOutput(0, method, inputp, outputp);
        errors += rc;

        if (debug) {
            inputp = &(dumpinput.input());
            outputp = &(dumpoutput.output());
        }

        if (0 != outstring) {
            fc = ::writes(outsocket, so->getString(),
                    so->getOffset(), so->getOffset());
            if (static_cast<ssize_t>(size) != fc) {
                std::perror("writes(outoutsocket,outstring,size)");
                ++errors;
            }
            delete outputp;
            outputp = 0;
            heap.free(outstring);
            outstring = 0;
        }

        if (0 != inputp) {
            delete inputp;
            inputp = 0;
        }

        if (0 != instring) {
            heap.free(instring);
            instring = 0;
        }

        if (0 != infile) {
            std::fclose(infile);
            infile = 0;
            insocket = EOF;
        }

        if (EOF != insocket) {
            ::close(insocket);
            insocket = EOF;
        }

    } while (0 != argv[optind]);

    if (0 != outputp) {
        delete outputp;
        outputp = 0;
    }

    if (0 != outfile) {
        std::fclose(outfile);
        outfile = 0;
        outsocket = EOF;
    }

    if (EOF != outsocket) {
        ::close(outsocket);
        outsocket = EOF;
    }

    errorf("%s[%d]: end errors=%d\n", __FILE__, __LINE__, errors);

    ::exit(errors);
}
