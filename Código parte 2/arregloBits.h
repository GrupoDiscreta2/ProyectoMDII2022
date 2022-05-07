#include <string.h>

#include "types.h"

/* Pone en 1 el bit i de arreglo
 *
 */
inline static void ponerEn1(u8* arreglo, u32 i) {
    arreglo[i / 8] |= 0x80 >> (i % 8);
}

/* Devuelve el índice del primer bit que es un 0 en el arreglo
 * Debe si o si haber algún 0
 */
inline static u32 primer0(u8* arreglo) {
    u32 primeru8no1 = 0;
    while (arreglo[primeru8no1] == 0xFF) {
        primeru8no1++;
    }

    u32 primerbitno1 = 0;
    while ((arreglo[primeru8no1] & (0x80 >> primerbitno1)) != 0) {
        primerbitno1++;
    }

    return primeru8no1 * 8 + primerbitno1;
}
