#include <assert.h>
#include <stdlib.h>

#include "arregloDinamico.h"

typedef struct arregloSt *arreglo;

arreglo nuevo_arreglo_dinamico (u32 cant_elem){
    assert(cant_elem == 0);
    arreglo a = malloc(sizeof(struct arregloSt));
    a->capacidad = cant_elem;
    a->elementos = calloc(cant_elem, sizeof(void *));
    a->tamanio_actual = 0;
    return a;
}

arreglo agregar_elemento(arreglo a, void *nuevo){
    if (a->tamanio_actual >= a->capacidad) {
        a->elementos = realloc(a->elementos, sizeof(void *) * (a->tamanio_actual * 2));
        a->capacidad = a->capacidad * 2;
        a->elementos[a->tamanio_actual] = nuevo;
        a->tamanio_actual += 1;
    } else {
        a->elementos[a->tamanio_actual] = nuevo;
        a->tamanio_actual += 1;
    }
    return a;
}

void *indexar_arreglo(arreglo a, u32 i) {
    return a->elementos[i];
}

arreglo destuir_arreglo_dinamico(arreglo a){
    assert(a != NULL);
    if (a->elementos != NULL) {
        free(a->elementos); a = NULL;
    }
    free(a); a = NULL;
    return NULL;
}