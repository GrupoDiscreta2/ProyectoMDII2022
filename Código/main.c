#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "ArbolAVL.h"
#include "EstructuraGrafo.h"
#include "types.h"

int main(void) {
    Grafo G = NULL;

    G = ConstruccionDelGrafo();

    if (G == NULL) {
        printf("G == NULL\n");
        return 0;
    }

    printf("n: %u \n", NumeroDeVertices(G));

    printf("nombre0: %u \n", Nombre(0, G));

    printf("Δ: %u \n", Delta(G));

    printf("0[0]: %u \n", IndiceONVecino(0, 0, G));

    DestruccionDelGrafo(G);

    return 0;
}