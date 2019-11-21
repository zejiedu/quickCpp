/**
 * @file Endianness.h
 * @author Zejie Du (duzejie@hotmail.com)
 * @brief "Big-endian" and "Little-endian" 
 * @version 0.1
 * @date 2019-11-01
 * 
 * @copyright Copyright (c) 2019
 * 
 * In computing, endianness refers to the order of bytes (or sometimes bits) within a binary representation of a number. 
 * It can also be used more generally to refer to the internal ordering of any representation, 
 * such as the digits in a numeral system or the sections of a date. 
 * In its most common usage, endianness indicates the ordering of bytes within a multi-byte number. 
 * A big-endian ordering places the most significant byte first and the least significant byte last, 
 * while a little-endian ordering does the opposite. For example, consider the unsigned hexadecimal number 0x1234, 
 * which requires at least two bytes to represent. In a big-endian ordering they would be [ 0x12, 0x34 ], 
 * while in a little-endian ordering, the bytes would be arranged [ 0x34, 0x12 ].
 * 
 * Conversely, little-endianness is the dominant ordering for processor architectures (x86, most ARM implementations) 
 *  and their associated memory. 
 */


#include <stdio.h>
#include <stdint.h>

bool isBigEndian(){
    union {
        int32_t a;
        char    c;
    }tmp;
    tmp.a = 0x12345678;
    if (tmp.c = 0x78)    
        return false;
    else
        return true;       
}

/**
 * @brief "Big-endian" and "Little-endian"  
 * @return 1: represent  "Little-endian", and 0 represent "Big-endian"
 */
int isLittleEndian(){
	int a = 1;	
	return (*(char*)&a);
}
