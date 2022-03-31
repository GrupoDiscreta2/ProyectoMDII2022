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

    assert(G != NULL);

    printf("%u \n", NumeroDeVertices(G));

    printf("%u \n", Nombre(2, G));

    printf("%u \n", Delta(G));

    DestruccionDelGrafo(G);

    return 0;
}