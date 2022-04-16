#include "AlduinPaarthurnaxIrileth.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

#include <assert.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

bool EsColoreoPropio(Grafo G, u32* coloreo);

int main(int argc, char** argv) {

    u32 x = (u32)atoi(argv[1]);

    Grafo G = NULL;

    G = ConstruccionDelGrafo();

    u32 n = NumeroDeVertices(G);

    u32* coloreo = calloc(sizeof(u32), n);

    u32* orden = calloc(sizeof(u32), n);

    for(u32 i = 0; i < n; i++){
        orden[i] = i;
    };

    Greedy(G, orden, coloreo);

    u32* res = PermutarColores(n, coloreo, x);
    
    // Imprimir coloreo
    printf("Coloreo: ");
    for (u32 i = (n-10); i < n; i++) {
        printf("%d ", coloreo[i]);
    }

    // Imprimir res
    printf("res:");
    for (u32 i = (n-10); i < n; i++) {
        printf("%d ", res[i]);
    }

    assert(EsColoreoPropio(G, res));
    DestruccionDelGrafo(G);
    free(coloreo);
    free(orden);
    free(res);

    return(0);
}