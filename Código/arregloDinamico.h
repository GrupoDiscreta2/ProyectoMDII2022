#ifndef __ARREGLODINAMICO_H
#define __ARREGLODINAMICO_H

#include "types.h"

typedef struct arregloSt* arreglo;

struct arregloSt {
    u32 capacidad;
    u32 tamanio_actual;
    void **elementos;
};

arreglo nuevo_arreglo_dinamico (u32 cant_elem);

arreglo agregar_elemento(arreglo a,void *nuevo); 

void *indexar_arreglo(arreglo a, u32 i); 

arreglo destuir_arreglo_dinamico (arreglo);

#endif