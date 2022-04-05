#ifndef __ESTRUCTURAGRAFO_H
#define __ESTRUCTURAGRAFO_H

#include <stdint.h>

#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "arregloDinamico.h"
#include "types.h"

typedef struct VerticeSt *Vertice;

struct VerticeSt {
    u32 nombre;
    u32 grado;
    u32 posicion;
    ArregloDin vecinos;
};

struct GrafoSt {
    u32 n;
    u32 m;
    u32 DELTA;
    Vertice *vertices;
};

Grafo InicializarGrafo(u32 n, u32 m);

/* Iniciliza un vértice
 * Toma un Grafo para saber el n y el m por cuestiones de eficiencia
 * 
 * PRE: G != NULL
 */
Vertice InicializarVertice(u32 nombre, Grafo G);

/* Destrulle un vertice liberando toda su memoria
 *
 * PRE: v != NULL
 */
Vertice DestruirVertice(Vertice v);

/* Agrega un vecino al vertice v1
 *
 * PRE: v1 != NULL
 */
Vertice AgregarVecino(Vertice v1, Vertice v2);

#endif