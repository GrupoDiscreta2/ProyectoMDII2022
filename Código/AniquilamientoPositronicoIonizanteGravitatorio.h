#ifndef __APIG_H
#define __APIG_H

#include "types.h"

// Funciones referidas a la estructura del GRAFO solamente (vertices y lados, básicamente)
// y no a sus colores o el orden en que se correra Greedy.
// Es decir, solo referidas a la ESTRUCTURA del grafo.
// Todos estos datos son fijos una vez cargado el grafo.

// Grafo es un puntero a una estructura, la cual esta definida en el .h siguiente.

typedef struct GrafoSt *Grafo;

#include "EstructuraGrafo.h"

// Construcción/destrucción del grafo.

Grafo ConstruccionDelGrafo(void);

void DestruccionDelGrafo(Grafo G);

// Funciones para extraer datos del grafo. u32 esta definida en el .h de arriba.

u32 NumeroDeVertices(Grafo G);
u32 NumeroDeLados(Grafo G);
u32 Delta(Grafo G); // Δ (delta mayuscula)

// Funciones de infoextract de vertices.

// Valor de retorno (2^32)-1 para reportar errores.
// Nombre no tienen forma de reportar errores.
// Las otras no hay problema pues es imposible que (2^32)-1 sea un indice o un grado.
// El indice i es el indice en el orden natural.
u32 Nombre(u32 i, Grafo G);
u32 Grado(u32 i, Grafo G);
// Vecinos info
u32 IndiceONVecino(u32 j, u32 k, Grafo G);

#endif
