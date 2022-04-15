#include "AlduinPaarthurnaxIrileth.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

#include <assert.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

bool EsColoreoPropio(Grafo G, u32* coloreo);

int main(void) {
    Grafo G = ConstruccionDelGrafo();
    assert(G != NULL);
    u32 n = NumeroDeVertices(G);

    u32* coloreo = calloc(n, sizeof(u32));
    u32* orden = calloc(n, sizeof(u32));
    for (u32 i = 0; i < n; i++) {
        orden[i] = i;
    }

    // medir el tiempo
    clock_t tiempo_inicial = clock();

    u32 x = Greedy(G, orden, coloreo);

    clock_t tiempo_final = clock();

    printf("Tiempo de ejecución: %f segundos\n", (double)(tiempo_final - tiempo_inicial) / CLOCKS_PER_SEC);
    printf("%d\n", x);

    bool e = EsColoreoPropio(G, coloreo);
    printf("%d\n", e);

    free(coloreo);
    free(orden);

    DestruccionDelGrafo(G);

    return(0);
}