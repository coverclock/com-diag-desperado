# Copyright 2008 Digital Aggregates Corp., Arvada CO 80001-0587, USA.
# Installs Desperado and Ficl libraries and provides unit test binaries.
# Chip Overclock <coverclock@diag.com>
# usage: sh diminuto.sh <serverip> <login> <password>
TARBALL=desperado-diminuto.tar.bz2
LIBDIR=/usr/local/lib
HSTDIR=/tmp
MNTDIR=/mnt
TGTDIR=$MNTDIR/diag.com
BINDIR=$TGTDIR/desperado/diminuto
if [ $# -ne 3 ]; then
    echo "usage: $0 <serverip> <login> <password>" 1>&2
    exit 1
fi
rm -rf $TGTDIR $MNTDIR/$TARBALL
ftpget -u $2 -p $3 $1 $MNTDIR/$TARBALL $HSTDIR/$TARBALL
tar xvjf $TARBALL -C $MNTDIR
rm $LIBDIR/libdesperado.so* $LIBDIR/libficl.so*
cp $BINDIR/libdesperado.so.[0-9]*.[0-9]*.[0-9]* $BINDIR/libficl.so.[0-9]*.[0-9]*.[0-9]* $LIBDIR
ldconfig $LIBDIR
