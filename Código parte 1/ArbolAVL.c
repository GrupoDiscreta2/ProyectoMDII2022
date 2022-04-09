#include "ArbolAVL.h"

#include <stdbool.h>
#include <stdlib.h>

#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "EstructuraGrafo.h"
#include "types.h"

struct ArbolAVLSt {
    u32 nombre;
    Vertice vertice;
    int altura;
    struct ArbolAVLSt *izq;
    struct ArbolAVLSt *der;
};

ArbolAVL *Nuevo_ArbolAVL(Vertice v) {
    ArbolAVL *T = (struct ArbolAVLSt *)malloc(sizeof(struct ArbolAVLSt));
    if (T != NULL) {
        T->nombre = v->nombre;
        T->vertice = v;
        T->izq = NULL;
        T->der = NULL;
        T->altura = 1;
    };
    return T;
}

ArbolAVL *Destruir_ArbolAVL(ArbolAVL *T) {
    if (T != NULL) {
        T->vertice = DestruirVertice(T->vertice);
        T->izq = Destruir_ArbolAVL(T->izq);
        T->der = Destruir_ArbolAVL(T->der);
        free(T);
        T = NULL;
    }
    return NULL;
}

static int Altura_ArbolAVL(ArbolAVL *T) {
    int res = 0;
    if (T != NULL) {
        res = T->altura;
    }

    return res;
}

// PRE: T != NULL && T->izq != NULL
static ArbolAVL *RotarDer_ArbolAVL(ArbolAVL *T) {

    ArbolAVL *x = T->izq;
    ArbolAVL *T2 = x->der;

    x->der = T;
    T->izq = T2;

    T->altura = max(Altura_ArbolAVL(T->izq), Altura_ArbolAVL(T->der)) + 1;
    x->altura = max(Altura_ArbolAVL(x->izq), Altura_ArbolAVL(x->der)) + 1;

    return x;
}

// PRE: T != NULL && T->der != NULL
static ArbolAVL *RotarIzq_ArbolAVL(ArbolAVL *T) {

    ArbolAVL *y = T->der;
    ArbolAVL *T2 = y->izq;

    y->izq = T;
    T->der = T2;

    T->altura = max(Altura_ArbolAVL(T->izq), Altura_ArbolAVL(T->der)) + 1;
    y->altura = max(Altura_ArbolAVL(y->izq), Altura_ArbolAVL(y->der)) + 1;

    return y;
}

int ObtenerBalance_ArbolAVL(ArbolAVL *T) {
    if (T == NULL) {
        return 0;
    }
    return Altura_ArbolAVL(T->izq) - Altura_ArbolAVL(T->der);
}

ArbolAVL *Insertar_ArbolAVL(ArbolAVL *T, u32 nombre, Vertice *res, Grafo G) {
    if (T == NULL) {
        *res = InicializarVertice(nombre, G);
        T = Nuevo_ArbolAVL(*res);
    } else if (nombre < T->nombre) {
        T->izq = Insertar_ArbolAVL(T->izq, nombre, res, G);
        if (T->izq == NULL) { // Caso de que hubo un fallo al alocar memoria
            T = Destruir_ArbolAVL(T);
            return T;
        }
    } else if (nombre > T->nombre) {
        T->der = Insertar_ArbolAVL(T->der, nombre, res, G);
        if (T->der == NULL) { // Caso de que hubo un fallo al alocar memoria
            T = Destruir_ArbolAVL(T);
            return T;
        }
    } else {
        *res = T->vertice;
    }

    T->altura = 1 + max(Altura_ArbolAVL(T->izq), Altura_ArbolAVL(T->der));

    int balance = ObtenerBalance_ArbolAVL(T);
    if (balance > 1 && nombre < T->izq->nombre)
        return RotarDer_ArbolAVL(T);
    if (balance < -1 && nombre > T->der->nombre)
        return RotarIzq_ArbolAVL(T);
    if (balance > 1 && nombre > T->izq->nombre) {
        T->izq = RotarIzq_ArbolAVL(T->izq);
        return RotarDer_ArbolAVL(T);
    }
    if (balance < -1 && nombre < T->der->nombre) {
        T->der = RotarDer_ArbolAVL(T->der);
        return RotarIzq_ArbolAVL(T);
    }

    return T;
}

ArbolAVL *ArbolAVL_a_arreglo(ArbolAVL *T, Vertice *array, u32 *i, u32 n) {
    if (T != NULL) {
        ArbolAVL_a_arreglo(T->izq, array, i, n);
        if (*i < n) {
            array[*i] = T->vertice;
            T->vertice->posicion = *i;
        } else {
            T->vertice = DestruirVertice(T->vertice);
        }
        (*i)++;
        ArbolAVL_a_arreglo(T->der, array, i, n);

        free(T);
        T = NULL;
    }

    return T;
}
