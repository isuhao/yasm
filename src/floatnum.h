/* $IdPath$
 * Floating point number functions header file.
 *
 *  Copyright (C) 2001  Peter Johnson
 *
 *  Based on public-domain x86 assembly code by Randall Hyde (8/28/91).
 *
 *  This file is part of YASM.
 *
 *  YASM is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  YASM is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef YASM_FLOATNUM_H
#define YASM_FLOATNUM_H

/* 88-bit internal floating point format:
 * xxxxxxxs eeeeeeee eeeeeeee m..m m..m m..m m..m m..m m..m m..m m..m
 * Sign          exponent                   mantissa (64 bits)
 *                            | 7  | 6  | 5  | 4  | 3  | 2  | 1  | 0|
 *                            63   55   47   39   31   23   15   7  0
 *
 * Only L.O. bit of Sign byte is significant.  The rest is garbage.
 * Exponent is bias 32767 exponent.
 * Mantissa does NOT have an implied one bit (it's explicit).
 */
typedef struct floatnum_s {
    unsigned int *mantissa;	/* Allocated to 64 bits */
    unsigned short exponent;
    unsigned char sign;
} floatnum;

floatnum *floatnum_new(char *str);

/* The get functions return nonzero if flt can't fit into that size format. */

/* Essentially a convert to single-precision and return as 32-bit value.
 * The 32-bit value is a "standard" C value (eg, of unknown endian).
 */
int floatnum_get_int(unsigned long *ret_val, const floatnum *flt);

/* ptr will point to the Intel-format little-endian byte string after a
 * successful call (eg, [0] should be the first byte output to the file).
 */
int floatnum_get_single(unsigned char *ptr, const floatnum *flt);
int floatnum_get_double(unsigned char *ptr, const floatnum *flt);
int floatnum_get_extended(unsigned char *ptr, const floatnum *flt);

void floatnum_print(const floatnum *flt);

#endif
