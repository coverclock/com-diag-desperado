#ifndef _COM_DIAG_DESPERADO_BYTEORDER_H_
#define _COM_DIAG_DESPERADO_BYTEORDER_H_

/* vim: set ts=4 expandtab shiftwidth=4: */

/******************************************************************************

    Copyright 2009 Digital Aggregates Corp., Arvada CO 80001-0587, USA.
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

******************************************************************************/


/**
 *  @file
 *
 *  Declares the ByteOrder class.
 */


#include "target.h"


#include "Begin.h"

/**
 *  Template defines a generalized method for swapping bytes.
 *
 *  @author coverclock@diag.com (Chip Overclock)
 */
template <typename _INPUT_, typename _OUTPUT_, typename _CONTROL_>
union ByteOrder {

private:

    _CONTROL_ control;

    _INPUT_ input;

    _OUTPUT_ output;

    uint8_t bytes[sizeof(_CONTROL_)];

public:

    /**
     * Ctor.
     * @param cc is the control word.
     */
    ByteOrder(_CONTROL_ cc = 0) : control(cc) {}

    /**
     * Dtor.
     */
    ~ByteOrder() {}

    /**
     * Returns true if network byte order is not the
     * same as host byte order.
     * @return true if network byte order is not the
     * same as host byte order.
     */
    static bool mustswap() {
        static const ByteOrder swappable(1);
        return swappable.bytes[0] != 0;
    }

    /**
     * Unconditionally swap bytes in a word.
     * @param data is the the input word.
     * @return the output word.
     */
    static _OUTPUT_ swap(_INPUT_ data) {
        ByteOrder in;
        ByteOrder out;
        in.input = data;
        for (size_t ii = 0; ii < sizeof(data); ++ii) {
            out.bytes[ii] = in.bytes[sizeof(data) - 1 - ii];
        }
        return out.output;
    }

    /**
     * Convert the input word to the output word
     * without swapping bytes.
     * @param data is the the input word.
     * @return the output word.
     */
    static _OUTPUT_ noswap(_INPUT_ data) {
        ByteOrder convert;
        convert.input = data;
        return convert.output;
    }

    /**
     * Conditionally swap bytes in a word.
     * @param data is the the input word.
     * @return the output word.
     */
    static _OUTPUT_ swapif(_INPUT_ data) {
        return mustswap() ? swap(data) : noswap(data);
    }

};

/*
 * Unsigned Integers
 */

/**
 *  Convert unsigned 64-bit integer from network to host byte order.
 *  @param data is the input word to convert.
 *  @return output word.
 */
inline uint64_t ntoh(uint64_t data) {
    return ByteOrder<uint64_t, uint64_t, uint64_t>::swapif(data);
}

/**
 *  Convert unsigned 64-bit integer from host to network byte order.
 *  @param data is the input word to convert.
 *  @return output word.
 */
inline uint64_t hton(uint64_t data) {
    return ByteOrder<uint64_t, uint64_t, uint64_t>::swapif(data);
}

/**
 *  Convert unsigned 32-bit integer from network to host byte order.
 *  @param data is the input word to convert.
 *  @return output word.
 */
inline uint32_t ntoh(uint32_t data) {
    return ByteOrder<uint32_t, uint32_t, uint32_t>::swapif(data);
}

/**
 *  Convert unsigned 32-bit integer from host to network byte order.
 *  @param data is the input word to convert.
 *  @return output word.
 */
inline uint32_t hton(uint32_t data) {
    return ByteOrder<uint32_t, uint32_t, uint32_t>::swapif(data);
}

/**
 *  Convert unsigned 16-bit integer from network to host byte order.
 *  @param data is the input word to convert.
 *  @return output word.
 */
inline uint16_t ntoh(uint16_t data) {
    return ByteOrder<uint16_t, uint16_t, uint16_t>::swapif(data);
}

/**
 *  Convert unsigned 16-bit integer from host to network byte order.
 *  @param data is the input word to convert.
 *  @return output word.
 */
inline uint16_t hton(uint16_t data) {
    return ByteOrder<uint16_t, uint16_t, uint16_t>::swapif(data);
}

/*
 * Signed Integers
 */

/**
 *  Convert signed 64-bit integer from network to host byte order.
 *  @param data is the input word to convert.
 *  @return output word.
 */
inline int64_t ntoh(int64_t data) {
    return ByteOrder<int64_t, int64_t, int64_t>::swapif(data);
}

/**
 *  Convert signed 64-bit integer from host to network byte order.
 *  @param data is the input word to convert.
 *  @return output word.
 */
inline int64_t hton(int64_t data) {
    return ByteOrder<int64_t, int64_t, int64_t>::swapif(data);
}

/**
 *  Convert signed 32-bit integer from network to host byte order.
 *  @param data is the input word to convert.
 *  @return output word.
 */
inline int32_t ntoh(int32_t data) {
    return ByteOrder<int32_t, int32_t, int32_t>::swapif(data);
}

/**
 *  Convert signed 32-bit integer from host to network byte order.
 *  @param data is the input word to convert.
 *  @return output word.
 */
inline int32_t hton(int32_t data) {
    return ByteOrder<int32_t, int32_t, int32_t>::swapif(data);
}

/**
 *  Convert signed 16-bit integer from network to host byte order.
 *  @param data is the input word to convert.
 *  @return output word.
 */
inline int16_t ntoh(int16_t data) {
    return ByteOrder<int16_t, int16_t, int16_t>::swapif(data);
}

/**
 *  Convert signed 16-bit integer from host to network byte order.
 *  @param data is the input word to convert.
 *  @return output word.
 */
inline int16_t hton(int16_t data) {
    return ByteOrder<int16_t, int16_t, int16_t>::swapif(data);
}

/*
 * Floats
 */

/**
 *  Convert 64-bit float from network to host byte order.
 *  @param data is the input word to convert.
 *  @return output word.
 */
inline float64_t fntoh(uint64_t data) {
    return ByteOrder<uint64_t, float64_t, uint64_t>::swapif(data);
}

/**
 *  Convert 64-bit float from host to network byte order.
 *  @param data is the input word to convert.
 *  @return output word.
 */
inline uint64_t fhton(float64_t data) {
    return ByteOrder<float64_t, uint64_t, uint64_t>::swapif(data);
}

/**
 *  Convert 32-bit float from network to host byte order.
 *  @param data is the input word to convert.
 *  @return output word.
 */
inline float32_t fntoh(uint32_t data) {
    return ByteOrder<uint32_t, float32_t, uint32_t>::swapif(data);
}

/**
 *  Convert 32-bit float from host to network byte order.
 *  @param data is the input word to convert.
 *  @return output word.
 */
inline uint32_t fhton(float32_t data) {
    return ByteOrder<float32_t, uint32_t, uint32_t>::swapif(data);
}

#include "End.h"


#if defined(DESPERADO_HAS_UNITTESTS)
#include "cxxcapi.h"
/**
 *  Run the ByteOrder unit test.
 *  
 *  @return the number of errors detected by the unit test.
 */
CXXCAPI int unittestByteOrder(void);
#endif


#endif
