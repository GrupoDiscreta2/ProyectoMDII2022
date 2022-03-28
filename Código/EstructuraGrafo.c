#include <assert.h>
#include <stdio.h>

#include "types.h"

#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "EstructuraGrafo.h"
#include "AVLTree.h"

vertice initVertice(u32 nombre) {
    vertice v = malloc(sizeof(vertice));
    v->nombre = nombre;
    v->grado = 0;
    v->vecinos = NULL;

    return v;
}

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
    int c = '\0';
    do {
        c = getchar();
        if (c == 'c') { // La linea es un comentario y hay que saltearla
            scanf("%*[^\n]");
            int x = getchar();
            assert(x == '\n');
        }
        else if (c != 'p') { // Hay una linea con formato incorrecto
            return NULL;
        }
    } while (c != 'p');

    u32 n = 0;
    u32 m = 0;
    
    int x = scanf(" edge %u %u \n", &n, &m);

    if (x != 2 || n == 0 || m == 0) {
        return NULL;
    }

    Grafo g = initGrafo(n, m);
    AVLTree *T = NULL;


    for(u32 line = 0; line < m; line++) {
        u32 v1;
        u32 v2;
        x = scanf(" e %u %u \n", &v1, &v2);
        if (x != 2 || n == 0 || m == 0) {
            return NULL;
        }
    }

    return NULL;
}


