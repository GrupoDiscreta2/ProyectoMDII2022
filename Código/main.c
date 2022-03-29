#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "types.h"


#include "EstructuraGrafo.h"
#include "dump_fancy_plugin.h"
#include "AVLTree.h"

int main() {
    Grafo T = NULL;

    T = ConstruccionDelGrafo();

    printf("%u", NumeroDeVertices(T));
    printf("%u", Nombre(1, T));

    return 0;
}