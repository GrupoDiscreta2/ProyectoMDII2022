#include "EstructuraGrafo.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "ArbolAVL.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "types.h"

Vertice InicializarVertice(u32 nombre, Grafo G) {
    assert(G != NULL);

    Vertice v = malloc(sizeof(struct VerticeSt));
    if (v != NULL) {
        v->nombre = nombre;
        v->grado = 0;
        v->posicion = 0;
        v->vecinos = Nuevo_ArregloDin(2 * (G->m) / G->n);
    }
    return v;
}

Vertice AgregarVecino(Vertice v1, Vertice v2) {
    assert(v1 != NULL);
    v1->grado += 1;
    v1->vecinos = AgregarEelemento_ArregloDin(v1->vecinos, v2);
    return v1;
}

Vertice DestruirVertice(Vertice v) {
    assert(v != NULL);
    Destruir_ArregloDin(v->vecinos);
    free(v);
    v = NULL;
    return NULL;
}

static Grafo addArista(Grafo G, ArbolAVL **T, u32 nameV1, u32 nameV2) {
    Vertice v1 = NULL;
    Vertice v2 = NULL;

    *T = Insertar_ArbolAVL(*T, nameV1, &v1, G);
    *T = Insertar_ArbolAVL(*T, nameV2, &v2, G);

    v1 = AgregarVecino(v1, v2);
    v2 = AgregarVecino(v2, v1);
    if (max(v1->grado, v2->grado) > G->DELTA) {
        G->DELTA = max(v1->grado, v2->grado);
    };

    return G;
}

Grafo InicializarGrafo(u32 n, u32 m) {
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

    Grafo G = InicializarGrafo(n, m);
    ArbolAVL *T = NULL;

    for (u32 line = 0; line < m; line++) {
        u32 v1 = 0;
        u32 v2 = 0;
        x = scanf("e %u %u \n", &v1, &v2);
        if (x != 2) { // Los datos no están en el formato correcto
            DestruccionDelGrafo(G);
            G = NULL;
            T = Destruir_ArbolAVL(T);
            return NULL;
        }
        G = addArista(G, &T, v1, v2);
    }

    u32 i = 0;
    G->vertices = calloc(n, sizeof(Vertice));
    if (G->vertices == NULL) {
        DestruccionDelGrafo(G);
        G = NULL;
        T = Destruir_ArbolAVL(T);
        return NULL;
    }
    T = ArbolAVL_a_arreglo(T, G->vertices, &i, n);
    if (i != n) {
        // La cantidad de vertices no coincide con n
        DestruccionDelGrafo(G);
        G = NULL;
        T = Destruir_ArbolAVL(T);
        return NULL;
    }

    // Liberar memoria extra pedida por los arreglos de vecinos
    for (u32 i = 0; i < n; i++) {
        G->vertices[i]->vecinos = Achicar_ArregloDin(G->vertices[i]->vecinos);
    }

    return G;
}

u32 NumeroDeVertices(Grafo G) {
    return G->n;
}

u32 NumeroDeLados(Grafo G) {
    return G->m;
}

u32 Delta(Grafo G) {
    return G->DELTA;
}

u32 Nombre(u32 i, Grafo G) {
    return G->vertices[i]->nombre;
}

u32 Grado(u32 i, Grafo G) {
    u32 result = MAX_U32;
    if (i < G->n) {
        result = G->vertices[i]->grado;
    }
    return result;
}

u32 IndiceONVecino(u32 j, u32 k, Grafo G) {
    u32 result = MAX_U32;
    if (k < NumeroDeVertices(G) && j < Grado(k, G)) {
        Vertice elem = Indexar_ArregloDin(G->vertices[k]->vecinos, j);
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
                G->vertices[i] = DestruirVertice(G->vertices[i]);
            }
        };
    }
    free(G->vertices);
    G->vertices = NULL;
    free(G);
    G = NULL;
}
