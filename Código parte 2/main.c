#include "AlduinPaarthurnaxIrileth.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

#include <assert.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

bool EsColoreoPropio(Grafo G, u32* coloreo);

int main(int argc, char** argv) {

    Grafo G = NULL;

    G = ConstruccionDelGrafo();

    u32 n = NumeroDeVertices(G);

    u32* coloreo = calloc(sizeof(u32), n);

    u32* orden = calloc(sizeof(u32), n);

    for(u32 i = 0; i < n; i++){
        orden[i] = i;
    };

    u32 colores = Greedy(G, orden, coloreo);

    printf("Colores 1er greedy: %u\n", colores);

    OrdenFromKey(n, coloreo, orden);

    colores = Greedy(G, orden, coloreo);

    printf("Colores 2do greedy: %u\n", colores);

    OrdenFromKey(n, coloreo, orden);

    colores = Greedy(G, orden, coloreo);

    printf("Colores 3er greedy: %u\n", colores);

    assert(EsColoreoPropio(G, coloreo));
    DestruccionDelGrafo(G);
    free(coloreo);
    free(orden);
/*     u32 coloreo[] = {0, 1, 2, 2, 0, 3, 4, 3, 2, 4, 2, 3, 3, 4, 3};

    u32* nuevoColoreo = RecoloreoCardinalidadDecrecienteBC(15, coloreo);

    for (u32 i = 0; i < 15; i++) {
        printf("%u, ", nuevoColoreo[i]);
    }

    free(nuevoColoreo); */



    return(0);
}