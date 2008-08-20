/* vim: set ts=4 expandtab shiftwidth=4: */

/******************************************************************************

    Copyright 2008 Digital Aggregates Corp., Arvada CO 80001-0587, USA.
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

/*
 * @file
 *
 * This was used to debug the platform initialization issue in Diminuto.
 *
 * arm-linux-g++ -o testdiminuto testdiminuto.cpp -Wl,-Bdynamic -Wl,-L. -Wl,-ldesperado  -DDESPERADO_PLATFORM_IS_Diminuto -Wl,-Bdynamic -Wl,-L/home/jsloan/diminuto/ficl-4.0.31 -Wl,-lficl -Wl,-lpthread -DDESPERADO_PLATFORM_CLASS=Diminuto -g
 *
 * arm-linux-g++ -o testdiminuto testdiminuto.cpp -Wl,-Bdynamic -Wl,-L/opt/diminuto/buildroot/usr/local/lib -Wl,-ldesperado  -DDESPERADO_PLATFORM_IS_Diminuto -Wl,-Bdynamic -Wl,-L/opt/diminuto/buildroot/usr/local/lib -Wl,-lficl -Wl,-lpthread -DDESPERADO_PLATFORM_CLASS=Diminuto -g
 *
 * @author Chip Overclock <coverclock@diag.com>
 */

#include <cstdlib>
#include <cstdio>
#include "Diminuto.h"
#include "Print.h"
#include "CommonEra.h"
#include "main.h"

class Foo {
public: static Platform& factory() { return desperado_platform_factory(); }
};

class Bar : public Platform {
public: static Platform& factory() { return desperado_platform_factory(); }
};

class Moo : public Platform {
public: static Platform& factory() { return Platform::factory(); }
};

class Hoo : public Platform {
};

int main(int, char **, char **) {
#if 0
    Platform * pp = new Diminuto;
    Platform & pp = Platform::factory();
    Platform & pp = desperado_platform_factory();
    { Platform & pp = Platform::factory(); }
    Platform & pp = Bar::factory();
    Platform & pp = Moo::factory();
    Platform & pp = Hoo::factory();
    Platform * dd = new Diminuto; Platform & pp = dd->factory();
    Platform::instance(pp);
    Platform::instance(*pp);
    { Platform * pp = new Diminuto; fprintf(stderr, "%p \"%s\" \"%s\" \"%s\"\n", pp, pp->platform(), pp->target(), pp->host()); Platform::instance(*pp); }
    { Platform * pp = new Diminuto; fprintf(stderr, "%p \"%s\" \"%s\" \"%s\" %p\n", pp, pp->platform(), pp->target(), pp->host(), &(pp->factory())); Platform::instance(*pp); }
    { Platform * pp = new Diminuto; Platform * qq = &(pp->factory()); fprintf(stderr, "%p \"%s\" \"%s\" \"%s\" %p\n", pp, pp->platform(), pp->target(), pp->host(), qq); Platform::instance(*pp); }
    { Platform * pp = new Diminuto; fprintf(stderr, "%p\n", &(pp->factory())); Platform::instance(*pp); }
    { Platform * pp = new Diminuto; fprintf(stderr, "%p \"%s\" \"%s\" \"%s\"\n", pp, pp->platform(), pp->target(), pp->host()); &(pp->factory()); Platform::instance(*pp); }
    { Platform * qq; Platform * pp = new Diminuto; fprintf(stderr, "%p \"%s\" \"%s\" \"%s\" %p\n", pp, pp->platform(), pp->target(), pp->host(), qq = &(pp->factory())); Platform::instance(*qq); }
    { Platform * qq; Platform * pp = new Diminuto; fprintf(stderr, "%p \"%s\" \"%s\" \"%s\" %p\n", pp, pp->platform(), pp->target(), pp->host(), qq = &(pp->factory())); Platform::instance(*qq); }
    { Platform * qq; fprintf(stderr, "%p\n", qq = &(Platform::factory()); Platform::instance(*qq); }
    { Platform & qq = desperado_platform_factory(); Platform & pp = Platform::factory(); Platform::instance(pp); }
    { Platform & qq = desperado_platform_factory(); Platform & pp = Platform::factory(); Platform::instance(qq); }
    { fprintf(stderr, "foo\n"); Platform & pp = Platform::factory(); Platform::instance(pp); }
    { Platform * pp; fprintf(stderr, "%p\n", pp = &(Platform::factory())); Platform::instance(*pp); }
    { desperado_platform_factory(); Platform * pp; fprintf(stderr, "%p\n", pp = &(Platform::factory())); Platform::instance(*pp); }
    { Platform * pp = &(Diminuto::factory()); Platform::instance(*pp); }
    Platform::instance(*(new Diminuto));
    { Platform::instance(desperado_platform_factory()); }
    { Platform::instance(desperado_platform_factory()); Platform & pp = Platform::factory(); fprintf(stderr, "%p", &pp); }
    { Platform::instance(desperado_platform_factory()); Platform::factory(); }
#endif
    Platform::instance(Platform::factory());
    Print printf(Platform::instance().output());

    printf("platform \"%s\"\n", Platform::instance().platform());
    printf("target   \"%s\"\n", Platform::instance().target());
    printf("host     \"%s\"\n", Platform::instance().host());
    printf("file     \"%s\"\n", __FILE__);
    printf("date     \"%s\"\n", __DATE__);
    printf("time     \"%s\"\n", __TIME__);

    // bool was = CommonEra::debug(true);
    // bool now = CommonEra::debug(false);
    // printf("was      %d\n", was);
    // printf("now      %d\n", now);

    std::exit(0);
}
