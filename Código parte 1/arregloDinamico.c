#include "arregloDinamico.h"

#include <stdlib.h>

typedef struct ArregloDinSt *ArregloDin;

ArregloDin Nuevo_ArregloDin(u32 cant_elem) {
    ArregloDin a = malloc(sizeof(struct ArregloDinSt));
    if (a != NULL) {
        a->capacidad = cant_elem;
        a->elementos = calloc(cant_elem, sizeof(void *));
        a->tamanio_actual = 0;
    }
    return a;
}

ArregloDin AgregarEelemento_ArregloDin(ArregloDin a, void *nuevo) {
    if (a->tamanio_actual >= a->capacidad) {
        a->elementos =
            realloc(a->elementos, sizeof(void *) * (a->tamanio_actual * 2));
        if (a->elementos != NULL) {
            a->capacidad = a->capacidad * 2;
            a->elementos[a->tamanio_actual] = nuevo;
            a->tamanio_actual += 1;
        }
    } else {
        a->elementos[a->tamanio_actual] = nuevo;
        a->tamanio_actual += 1;
    }
    return a;
}

void *Indexar_ArregloDin(ArregloDin a, u32 i) {
    return a->elementos[i];
}

ArregloDin Achicar_ArregloDin(ArregloDin a) {
    a->elementos = realloc(a->elementos, sizeof(void *) * (a->tamanio_actual));
    a->capacidad = a->tamanio_actual;
    return a;
}

ArregloDin Destruir_ArregloDin(ArregloDin a) {
    if (a->elementos != NULL) {
        free(a->elementos);
        a->elementos = NULL;
    }
    free(a);
    a = NULL;
    return NULL;
}