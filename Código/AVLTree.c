#include "AVLTree.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "EstructuraGrafo.h"
#include "types.h"

struct AVLTreeSt {
    u32 nombre;
    vertice vertice;
    int altura;
    struct AVLTreeSt *izq;
    struct AVLTreeSt *der;
};

static bool checOrd_maxMin(AVLTree *T, u32 maximo, u32 minimo) {
    return T == NULL || (T->nombre < maximo && T->nombre > minimo &&
                         checOrd_maxMin(T->izq, T->nombre, minimo) &&
                         checOrd_maxMin(T->der, maximo, T->nombre));
}

static bool checOrd_max(AVLTree *T, u32 maximo) {
    return T == NULL || (T->nombre < maximo && checOrd_max(T->izq, T->nombre) &&
                         checOrd_maxMin(T->der, maximo, T->nombre));
}

static bool checOrd_min(AVLTree *T, u32 minimo) {
    return T == NULL || (T->nombre > minimo && checOrd_min(T->der, T->nombre) &&
                         checOrd_maxMin(T->izq, T->nombre, minimo));
}

static bool checOrd(AVLTree *T) {
    return T == NULL ||
           (checOrd_max(T->izq, T->nombre) && checOrd_min(T->der, T->nombre));
}

static int assertCheckProf(AVLTree *T) { // Chequear profundidad
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

static void assertinvRep_AVLTree(AVLTree *T) {
    assert(checOrd(T));
    assertCheckProf(T);
}

AVLTree *nuevo_AVLTree(vertice v) {
    AVLTree *T = (struct AVLTreeSt *)malloc(sizeof(struct AVLTreeSt));
    if (T != NULL) {
        T->nombre = v->nombre;
        T->vertice = v;
        T->izq = NULL;
        T->der = NULL;
        T->altura = 1;
    };
    assertinvRep_AVLTree(T);
    return T;
}

AVLTree *destruir_AVLTree(AVLTree *T) {
    if (T != NULL) {
        T->vertice = destruirVertice(T->vertice);
        T->izq = destruir_AVLTree(T->izq);
        T->der = destruir_AVLTree(T->der);
        free(T);
        T = NULL;
    }
    return NULL;
}

static int altura_AVLTree(AVLTree *T) {
    int res = 0;
    if (T != NULL) {
        res = T->altura;
    }

    return res;
}

// PRE: T != NULL && T->izq != NULL
static AVLTree *rotarDer_AVLTree(AVLTree *T) {
    assert(T != NULL && T->izq != NULL);

    AVLTree *x = T->izq;
    AVLTree *T2 = x->der;

    x->der = T;
    T->izq = T2;

    T->altura = max(altura_AVLTree(T->izq), altura_AVLTree(T->der)) + 1;
    x->altura = max(altura_AVLTree(x->izq), altura_AVLTree(x->der)) + 1;

    //assertinvRep_AVLTree(T2);
    return x;
}

// PRE: T != NULL && T->der != NULL
static AVLTree *rotarIzq_AVLTree(AVLTree *T) {
    assert(T != NULL && T->der != NULL);

    AVLTree *y = T->der;
    AVLTree *T2 = y->izq;

    y->izq = T;
    T->der = T2;

    T->altura = max(altura_AVLTree(T->izq), altura_AVLTree(T->der)) + 1;
    y->altura = max(altura_AVLTree(y->izq), altura_AVLTree(y->der)) + 1;

    //assertinvRep_AVLTree(T2);
    return y;
}

// PRE: T != NULL && T->der != NULL && T->der->izq != NULL
static AVLTree *rotarIzqDer_AVLTree(AVLTree *T) {
    assert(T != NULL && T->der != NULL && T->der->izq != NULL);

    T->der = rotarIzq_AVLTree(T->der);
    T = rotarDer_AVLTree(T);

    //assertinvRep_AVLTree(T);
    return T;
}

// PRE: T != NULL && T->izq != NULL && T->izq->der != NULL
static AVLTree *rotarDerIzq_AVLTree(AVLTree *T) {
    assert(T != NULL && T->izq != NULL && T->izq->der != NULL);

    T->izq = rotarDer_AVLTree(T->izq);
    T = rotarIzq_AVLTree(T);

    //assertinvRep_AVLTree(T);
    return T;
}

int obtenerBalance(AVLTree *T) {
    if (T == NULL) {
        return 0;
    }
    return altura_AVLTree(T->izq) - altura_AVLTree(T->der);
}

AVLTree *insertar_AVLTree(AVLTree *T, u32 nombre, vertice *res, Grafo G) {
    assert(res != NULL);

    if (T == NULL) {
        *res = initVertice(nombre, G);
        T = nuevo_AVLTree(*res);
    } else if (nombre < T->nombre) {
        T->izq = insertar_AVLTree(T->izq, nombre, res, G);
        if (T->izq == NULL) { // Caso de que hubo un fallo al alocar memoria
            T = destruir_AVLTree(T);
            return T;
        }
    } else if (nombre > T->nombre) {
        T->der = insertar_AVLTree(T->der, nombre, res, G);
        if (T->der == NULL) { // Caso de que hubo un fallo al alocar memoria
            T = destruir_AVLTree(T);
            return T;
        }
    } else {
        *res = T->vertice;
    }

    T->altura = 1 + max(altura_AVLTree(T->izq), altura_AVLTree(T->der));

    int balance = obtenerBalance(T);
    if (balance > 1 && nombre < T->izq->nombre)
        return rotarDer_AVLTree(T);
    if (balance < -1 && nombre > T->der->nombre)
        return rotarIzq_AVLTree(T);
    if (balance > 1 && nombre > T->izq->nombre) {
        T->izq = rotarIzq_AVLTree(T->izq);
        return rotarDer_AVLTree(T);
    }
    if (balance < -1 && nombre < T->der->nombre) {
        T->der = rotarDer_AVLTree(T->der);
        return rotarIzq_AVLTree(T);
    }

    return T;
}

AVLTree *AVLTree_to_array(AVLTree *T, vertice *array, u32 *i, u32 n) {
    assert(((T != NULL) <= (array != NULL)) && i != NULL);

    if (T != NULL) {
        AVLTree_to_array(T->izq, array, i, n);
        if (*i < n) {
            array[*i] = T->vertice;
            T->vertice->posicion = *i;
        } else {
            T->vertice = destruirVertice(T->vertice);
        }
        (*i)++;
        AVLTree_to_array(T->der, array, i, n);

        free(T);
        T = NULL;
    }

    return T;
}

void preOrder(AVLTree *T) {
    if (T != NULL) {
        printf("%d ", T->nombre);
        preOrder(T->izq);
        preOrder(T->der);
    }
}