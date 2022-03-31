#include <assert.h>
#include <stdio.h>

#include "types.h"
#include "EstructuraGrafo.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "AVLTree.h"

vertice initVertice(u32 nombre) {
    vertice v = malloc(sizeof(struct verticeSt));
    v->nombre = nombre;
    v->grado = 0;
    v->posicion = 0;
    v->vecinos = NULL;
    return v;
}

vertice addVecino(vertice v1, vertice v2) {
    v1->grado += 1;
    v1->vecinos = realloc(v1->vecinos, sizeof(vertice)*v1->grado);
    v1->vecinos[v1->grado-1] = v2;
    return v1;
}

Grafo addArista(Grafo g, AVLTree **T, u32 nameV1, u32 nameV2) {
    vertice v1 = NULL;
    vertice v2 = NULL;

    *T = insertar_AVLTree(*T, nameV1, &v1);
    *T = insertar_AVLTree(*T, nameV2, &v2);

    v1 = addVecino(v1, v2);
    v2 = addVecino(v2, v1);
    if(max(v1->grado, v2->grado) > g->DELTA) {
        g->DELTA = max(v1->grado, v2->grado);
    };

    return g;
}

Grafo initGrafo(u32 n, u32 m) {
    Grafo G = malloc(sizeof(struct GrafoSt));
    if (G != NULL) {
        G->n = n;
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
            // Falta liberar memoria acá
            return NULL;
        }
        g = addArista(g, &T, v1, v2);
    }

    u32 *i = malloc(sizeof(int));
    *i = 0;
    AVLTree_to_array(T, g->vertices, i);

    free(i);

    return g;
}

u32 NumeroDeVertices(Grafo G) {
    return G->n;
}

u32 Delta(Grafo G) {
    return G->DELTA;
}

u32 Nombre(u32 i, Grafo G) {
    return G->vertices[i]->nombre;
}

u32 Grado(u32 i, Grafo G) {
    return G->vertices[i]->grado;
}

u32 IndiceONVecino(u32 j, u32 k, Grafo G) {
    return G->vertices[k]->vecinos[j]->posicion;
}

void DestruccionDelGrafo(Grafo G){
    assert(G != NULL);

    for(u32 i = 0; i < G->n; i++){
        free(G->vertices[i]->vecinos);
        free(G->vertices[i]);
    };
    free(G->vertices);
    free(G);
    G = NULL;
}


