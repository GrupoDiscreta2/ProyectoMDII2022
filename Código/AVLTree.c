#include "AVLTree.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "types.h"

#include "EstructuraGrafo.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

struct AVLTreeSt {
    u32 nombre;
    int altura;
    struct AVLTreeSt *izq;
    struct AVLTreeSt *der;
};


static bool checOrd_maxMin(AVLTree *T, u32 maximo, u32 minimo) {
    return
        T == NULL
        || (T->nombre < maximo
            && T->nombre > minimo
            && checOrd_maxMin(T->izq, T->nombre, minimo)
            && checOrd_maxMin(T->der, maximo, T->nombre)
        )
    ;
}

static bool checOrd_max(AVLTree *T, u32 maximo) {
    return
        T == NULL
        || (T->nombre < maximo
            && checOrd_max(T->izq, T->nombre)
            && checOrd_maxMin(T->der, maximo, T->nombre)
        )
    ;
}

static bool checOrd_min(AVLTree *T, u32 minimo) {
    return
        T == NULL
        || (T->nombre > minimo
            && checOrd_min(T->der, T->nombre)
            && checOrd_maxMin(T->izq, T->nombre, minimo)
        )
    ;
}

static bool checOrd(AVLTree *T) {
    return
        T == NULL
        || (checOrd_max(T->izq, T->nombre) && checOrd_min(T->der, T->nombre))
    ;
}

static int assertCheckProf(AVLTree *T) { // Chequear profundidad
    if (T == NULL) {
        return 0;
    }
    int profIzq = assertCheckProf(T->izq);
    int profDer = assertCheckProf(T->der);
    int prof = max(profIzq, profDer) + 1;
    int FE = profDer - profIzq;
    
//    printf("%d %d %d %d\n", prof, T->altura, profIzq, profDer);
    assert(prof == T->altura); assert(-2 < FE && FE < 2);

    return prof;
}


static void assertinvRep_AVLTree(AVLTree *T) {
    assert(checOrd(T));
    assertCheckProf(T);
}


AVLTree *nuevo_AVLTree(u32 nombre) {
    AVLTree *T = malloc(sizeof(AVLTree));
    if (T != NULL) {
        T->nombre = nombre;
        T->altura = 1;
        T->izq = NULL;
        T->der = NULL;
    };
    assertinvRep_AVLTree(T);
    return T;
}

AVLTree *destruir_AVLTree(AVLTree *T) {
    if (T != NULL) {
        destruir_AVLTree(T->izq);
        destruir_AVLTree(T->der);
        free(T); T = NULL;
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


// PRE: T != NULL && T->der != NULL
static AVLTree *rotarDer_AVLTree(AVLTree *T) {
    assert(T != NULL && T->der != NULL);

    AVLTree *T2 = T->der;
    T->der = T2->izq;
    T2->izq = T;

    T->altura = max(altura_AVLTree(T->izq), altura_AVLTree(T->der)) + 1;
    T2->altura = max(altura_AVLTree(T2->izq), altura_AVLTree(T2->der)) + 1;

    //assertinvRep_AVLTree(T2);
    return T2;
}

// PRE: T != NULL && T->izq != NULL
static AVLTree *rotarIzq_AVLTree(AVLTree *T) {
    assert(T != NULL && T->izq != NULL);

    AVLTree *T2 = T->izq;
    T->izq = T2->der;
    T2->der = T;

    T->altura = max(altura_AVLTree(T->izq), altura_AVLTree(T->der)) + 1;
    T2->altura = max(altura_AVLTree(T2->izq), altura_AVLTree(T2->der)) + 1;

    //assertinvRep_AVLTree(T2);
    return T2;
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


AVLTree *insertar_AVLTree(AVLTree *T, u32 nombre, bool *res) {
    assert(res != NULL);

    *res = false;
    if (T == NULL) {
        T = nuevo_AVLTree(nombre);
    }
    else if (nombre < T->nombre) {
        T->izq = insertar_AVLTree(T->izq, nombre, res);
        if (T->izq == NULL) { // Caso de que hubo un fallo al alocar memoria
            T = destruir_AVLTree(T);
            return T;
        }
        T->altura = max(altura_AVLTree(T->izq), altura_AVLTree(T->der)) + 1;

        int FE = altura_AVLTree(T->izq) - altura_AVLTree(T->der); // Factor de escalado
        int FE_izq = altura_AVLTree(T->izq->izq) - altura_AVLTree(T->izq->der);
        if (FE == 2) {
            if (FE_izq == -1) {
                T = rotarDerIzq_AVLTree(T);
            }
            else {
                T = rotarIzq_AVLTree(T);
            }
        }
    }
    else if (nombre > T->nombre) {
        T->der = insertar_AVLTree(T->der, nombre, res);
        if (T->der == NULL) { // Caso de que hubo un fallo al alocar memoria
            T = destruir_AVLTree(T);
            return T;
        }
        T->altura = max(altura_AVLTree(T->izq), altura_AVLTree(T->der)) + 1;

        int FE = altura_AVLTree(T->izq) - altura_AVLTree(T->der); // Factor de escalado
        int FE_der = altura_AVLTree(T->der->izq) - altura_AVLTree(T->der->der);
        if (FE == -2) {
            if (FE_der == 1) {
                T = rotarIzqDer_AVLTree(T);
            }
            else {
                T = rotarDer_AVLTree(T);
            }
        }
    }
    else {
        *res = true;
    }

    assertinvRep_AVLTree(T);
    return T;
}


void preOrder(AVLTree *T)
{
    if(T != NULL)
    {
        printf("%d ", T->nombre);
        preOrder(T->izq);
        preOrder(T->der);
    }
}

