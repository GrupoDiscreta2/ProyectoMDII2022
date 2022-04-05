#include "arregloDinamico.h"

#include <assert.h>
#include <stdlib.h>

typedef struct ArregloDinSt *ArregloDin;

ArregloDin Nuevo_ArregloDin(u32 cant_elem) {
    assert(cant_elem != 0);
    ArregloDin a = malloc(sizeof(struct ArregloDinSt));
    if (a != NULL) {
        a->capacidad = cant_elem;
        a->elementos = calloc(cant_elem, sizeof(void *));
        assert(a->elementos != NULL);
        a->tamanio_actual = 0;
    }
    return a;
}

ArregloDin AgregarEelemento_ArregloDin(ArregloDin a, void *nuevo) {
    assert(a != NULL && nuevo != NULL);
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
    assert(a->elementos[a->tamanio_actual - 1] == nuevo);
    return a;
}

void *Indexar_ArregloDin(ArregloDin a, u32 i) {
    assert(a != NULL);
    return a->elementos[i];
}

ArregloDin Achicar_ArregloDin(ArregloDin a) {
    assert(a != NULL);
    a->elementos = realloc(a->elementos, sizeof(void *) * (a->tamanio_actual));
    a->capacidad = a->tamanio_actual;
    return a;
}

ArregloDin Destruir_ArregloDin(ArregloDin a) {
    assert(a != NULL);
    if (a->elementos != NULL) {
        free(a->elementos);
        a->elementos = NULL;
    }
    free(a);
    a = NULL;
    return NULL;
}