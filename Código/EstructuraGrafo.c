#include <stdio.h>


#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "EstructuraGrafo.h"

Grafo initGrafo(u32 n, u32 m) {
    Grafo G = malloc(sizeof(struct GrafoSt));
    if (G != NULL) {
        G->n = 0;
        G->m = m;
        G->DELTA = 0;
        G->vertices = calloc(n, sizeof(vertice));
        if (G->vertices == NULL) {
            free(G);
            return NULL;
        }
    }
    return G;
}

Grafo ConstruccionDelGrafo() {
    

}

