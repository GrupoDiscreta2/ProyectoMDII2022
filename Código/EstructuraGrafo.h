#ifndef __ESTRUCTURAGRAFO_H
#define __ESTRUCTURAGRAFO_H

#include <stdint.h>

#include "types.h"

#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

typedef struct verticeSt *vertice;

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


Grafo initGrafo(u32 n, u32 m);

vertice initVertice(u32 nombre);

Grafo addVertice(Grafo G, vertice v);

Grafo addArista(Grafo G, vertice V, vertice W);

Grafo sortVertices(Grafo G);

#endif