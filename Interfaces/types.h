#ifndef __TYPES_H
#define __TYPES_H

/*
 * Algunos typedef y defines útiles
 */

#include <stdint.h>

typedef uint8_t u8;
typedef uint32_t u32;

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#define MAX_U32 4294967295

#endif