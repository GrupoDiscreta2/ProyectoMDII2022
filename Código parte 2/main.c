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

    Greedy(G, orden, coloreo);

    u32* res = RecoloreoCardinalidadDecrecienteBC(n, coloreo);
    
    // Imprimir coloreo
    printf("Coloreo: ");
    for (u32 i = 0; i < 20; i++) {
        printf("%d ", coloreo[i]);
    }

    // Imprimir res
    printf("res:");
    for (u32 i = 0; i < 20; i++) {
        printf("%d ", res[i]);
    }

    assert(EsColoreoPropio(G, res));
    DestruccionDelGrafo(G);
    free(coloreo);
    free(orden);
    free(res);

/*     u32 coloreo[] = {0, 1, 2, 2, 0, 3, 4, 3, 2, 4, 2, 3, 3, 4, 3};

    u32* nuevoColoreo = RecoloreoCardinalidadDecrecienteBC(15, coloreo);

    for (u32 i = 0; i < 15; i++) {
        printf("%u, ", nuevoColoreo[i]);
    }

    free(nuevoColoreo); */



    return(0);
}