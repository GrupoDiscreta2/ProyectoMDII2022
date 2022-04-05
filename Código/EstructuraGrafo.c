#include "EstructuraGrafo.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "AVLTree.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "types.h"

vertice initVertice(u32 nombre, Grafo G) {
    vertice v = malloc(sizeof(struct verticeSt));
    if (v != NULL) {
        v->nombre = nombre;
        v->grado = 0;
        v->posicion = 0;
        v->vecinos = nuevo_arreglo_dinamico(2 * (G->m) / G->n);
    }
    return v;
}

vertice addVecino(vertice v1, vertice v2) {
    assert(v1 != NULL);
    v1->grado += 1;
    v1->vecinos = agregar_elemento(v1->vecinos, v2);
    return v1;
}

vertice destruirVertice(vertice v) {
    assert(v != NULL);
    destuir_arreglo_dinamico(v->vecinos);
    free(v);
    v = NULL;
    return NULL;
}

static Grafo addArista(Grafo G, AVLTree **T, u32 nameV1, u32 nameV2) {
    vertice v1 = NULL;
    vertice v2 = NULL;

    *T = insertar_AVLTree(*T, nameV1, &v1, G);
    *T = insertar_AVLTree(*T, nameV2, &v2, G);

    v1 = addVecino(v1, v2);
    v2 = addVecino(v2, v1);
    if (max(v1->grado, v2->grado) > G->DELTA) {
        G->DELTA = max(v1->grado, v2->grado);
    };

    return G;
}

Grafo initGrafo(u32 n, u32 m) {
    Grafo G = malloc(sizeof(struct GrafoSt));
    if (G != NULL) {
        G->n = n;
        G->m = m;
        G->DELTA = 0;
        G->vertices = NULL;
    }
    return G;
}

Grafo ConstruccionDelGrafo(void) {
    int c = '\0'; // getchar devuelve int, por eso esto es un int
    do {
        c = getchar();
        if (c == 'c') { // La linea es un comentario y hay que saltearla
            int b = scanf("%*[^\n]");
            assert(b == 0);
            int x = getchar();
            assert(x == '\n');
        } else if (c != 'p') { // Hay una linea con formato incorrecto
            return NULL;
        }
    } while (c != 'p');

    u32 n = 0;
    u32 m = 0;

    int x = scanf(" edge %u %u \n", &n, &m);

    if (x != 2 || n == 0 || m == 0) {
        return NULL;
    }

    Grafo G = initGrafo(n, m);
    AVLTree *T = NULL;

    for (u32 line = 0; line < m; line++) {
        u32 v1 = 0;
        u32 v2 = 0;
        x = scanf("e %u %u \n", &v1, &v2);
        if (x != 2) { // Los datos no están en el formato correcto
            DestruccionDelGrafo(G);
            G = NULL;
            T = destruir_AVLTree(T);
            return NULL;
        }
        G = addArista(G, &T, v1, v2);
    }

    u32 i = 0;
    G->vertices = calloc(n, sizeof(vertice));
    if (G->vertices == NULL) {
        DestruccionDelGrafo(G);
        G = NULL;
        T = destruir_AVLTree(T);
        return NULL;
    }
    T = AVLTree_to_array(T, G->vertices, &i, n);
    if (i != n) {
        // La cantidad de vertices no coincide con n
        DestruccionDelGrafo(G);
        G = NULL;
        T = destruir_AVLTree(T);
        return NULL;
    }

    // Liberar memoria extra pedida por los arreglos de vecinos
    for (u32 i = 0; i < n; i++) {
        G->vertices[i]->vecinos = achicar_arreglo(G->vertices[i]->vecinos);
    }

    return G;
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
    u32 result;
    if (k >= NumeroDeVertices(G) || j >= Grado(k, G)) {
        result = MAX_U32;
    } else {
        vertice elem = indexar_arreglo(G->vertices[k]->vecinos, j);
        result = elem->posicion;
    }
    return result;
}

void DestruccionDelGrafo(Grafo G) {
    assert(G != NULL);

    if (G->vertices != NULL) {
        for (u32 i = 0; i < G->n; i++) {
            if (G->vertices[i] != NULL) {
                // Algunos podrían ser NULL si el grafo no se construyó bien
                // (Si no había n vertices)
                G->vertices[i] = destruirVertice(G->vertices[i]);
            }
        };
    }
    free(G->vertices);
    G->vertices = NULL;
    free(G);
    G = NULL;
}
