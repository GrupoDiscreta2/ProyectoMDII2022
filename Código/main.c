#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "types.h"


#include "EstructuraGrafo.h"
#include "dump_fancy_plugin.h"
#include "AVLTree.h"

int main() {
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