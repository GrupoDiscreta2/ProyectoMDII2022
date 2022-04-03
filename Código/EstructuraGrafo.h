#ifndef __ESTRUCTURAGRAFO_H
#define __ESTRUCTURAGRAFO_H

#include <stdint.h>

#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "arregloDinamico.h"
#include "types.h"

typedef struct verticeSt *vertice;

struct verticeSt {
    u32 nombre;
    u32 grado;
    u32 posicion;
    arreglo vecinos;
};

struct GrafoSt {
    u32 n;
    u32 m;
    u32 DELTA;
    vertice *vertices;
};

Grafo initGrafo(u32 n, u32 m);

vertice initVertice(u32 nombre, Grafo G);

/* Destrulle un vertice liberando toda su memoria
 *
 * PRE: v != NULL
 */
vertice destruirVertice(vertice v);

vertice addVecino(vertice v1, vertice v2);

#endif