#include "ArbolAVL.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
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

static bool ChecOrd_maxMin(ArbolAVL *T, u32 maximo, u32 minimo) {
    return T == NULL || (T->nombre < maximo && T->nombre > minimo &&
                         ChecOrd_maxMin(T->izq, T->nombre, minimo) &&
                         ChecOrd_maxMin(T->der, maximo, T->nombre));
}

static bool ChecOrd_max(ArbolAVL *T, u32 maximo) {
    return T == NULL || (T->nombre < maximo && ChecOrd_max(T->izq, T->nombre) &&
                         ChecOrd_maxMin(T->der, maximo, T->nombre));
}

static bool ChecOrd_min(ArbolAVL *T, u32 minimo) {
    return T == NULL || (T->nombre > minimo && ChecOrd_min(T->der, T->nombre) &&
                         ChecOrd_maxMin(T->izq, T->nombre, minimo));
}

static bool ChecOrd(ArbolAVL *T) {
    return T == NULL ||
           (ChecOrd_max(T->izq, T->nombre) && ChecOrd_min(T->der, T->nombre));
}

static int assertCheckProf(ArbolAVL *T) { // Chequear profundidad
    if (T == NULL) {
        return 0;
    }
    int profIzq = assertCheckProf(T->izq);
    int profDer = assertCheckProf(T->der);
    int prof = max(profIzq, profDer) + 1;
    int FE = profDer - profIzq;

    assert(prof == T->altura);
    assert(-2 < FE && FE < 2);

    return prof;
}

static void assertinvRep_ArbolAVL(ArbolAVL *T) {
    assert(ChecOrd(T));
    assertCheckProf(T);
}

ArbolAVL *Nuevo_ArbolAVL(Vertice v) {
    ArbolAVL *T = (struct ArbolAVLSt *)malloc(sizeof(struct ArbolAVLSt));
    if (T != NULL) {
        T->nombre = v->nombre;
        T->vertice = v;
        T->izq = NULL;
        T->der = NULL;
        T->altura = 1;
    };
    assertinvRep_ArbolAVL(T);
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
    assert(T != NULL && T->izq != NULL);

    ArbolAVL *x = T->izq;
    ArbolAVL *T2 = x->der;

    x->der = T;
    T->izq = T2;

    T->altura = max(Altura_ArbolAVL(T->izq), Altura_ArbolAVL(T->der)) + 1;
    x->altura = max(Altura_ArbolAVL(x->izq), Altura_ArbolAVL(x->der)) + 1;

    //assertinvRep_ArbolAVL(T2);
    return x;
}

// PRE: T != NULL && T->der != NULL
static ArbolAVL *RotarIzq_ArbolAVL(ArbolAVL *T) {
    assert(T != NULL && T->der != NULL);

    ArbolAVL *y = T->der;
    ArbolAVL *T2 = y->izq;

    y->izq = T;
    T->der = T2;

    T->altura = max(Altura_ArbolAVL(T->izq), Altura_ArbolAVL(T->der)) + 1;
    y->altura = max(Altura_ArbolAVL(y->izq), Altura_ArbolAVL(y->der)) + 1;

    //assertinvRep_ArbolAVL(T2);
    return y;
}

int ObtenerBalance_ArbolAVL(ArbolAVL *T) {
    if (T == NULL) {
        return 0;
    }
    return Altura_ArbolAVL(T->izq) - Altura_ArbolAVL(T->der);
}

ArbolAVL *Insertar_ArbolAVL(ArbolAVL *T, u32 nombre, Vertice *res, Grafo G) {
    assert(res != NULL);

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
    assert(((T != NULL) <= (array != NULL)) && i != NULL);

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
