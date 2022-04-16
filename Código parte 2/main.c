#include "AlduinPaarthurnaxIrileth.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

#include <assert.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

bool EsColoreoPropio(Grafo G, u32* coloreo);

int main(void) {
    u32 arreglo[] = {4, 2, 2, 3, 4,2,1,1};
    u32 orden[8];
    OrdenFromKey(8, arreglo, orden);

    for (u32 i = 0; i < 8; i++) {
        printf("orden[%u] = %u\n", i, orden[i]);
    }
    
    return(0);
}