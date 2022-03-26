#ifndef __ESTRUCTURAGRAFO_H
#define __ESTRUCTURAGRAFO_H

#include <stdint.h>

typedef uint32_t u32;
typedef struct verticeSt *vertice;
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
struct verticeSt {
    u32 nombre;
    u32 grado;
    vertice *vecinos;
};

struct GrafoSt {
    u32 n;
    u32 m;
    u32 DELTA;
    vertice *vertices;
};


Grafo initGrafo();

Grafo addVertice(Grafo G, vertice v);

Grafo addArista(Grafo G, vertice V, vertice W);

Grafo sortVertices(Grafo G);

#endif