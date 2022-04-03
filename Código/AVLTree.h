#ifndef __AVLTREE_H
#define __AVLTREE_H

/*
TAD de arbol binario autobalanceado
Explicación de wikipedia: https://es.wikipedia.org/wiki/%C3%81rbol_AVL
*/

#include <stdbool.h>

#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "EstructuraGrafo.h"
#include "types.h"

typedef struct AVLTreeSt AVLTree;

/*
 * Crea un árbol AVL con un solo elemento
 * En caso de error de alocado de memoria devuelve NULL
 */
AVLTree *nuevo_AVLTree(vertice v);

/*
 * Destrulle un árbol AVL liberando toda su memoria y la memoria de los
 * elementos
 */
AVLTree *destruir_AVLTree(AVLTree *T);

/*
 * Agrega un elemento a un árbol AVL
 * En caso de error de alocado de memoria libera toda la memoria del
 * árbol y devuelve NULL
 *
 * Pone el vertice del elemento en res, tanto si ya estaba como si no
 *
 * PRE: res != NULL
 */
AVLTree *insertar_AVLTree(AVLTree *T, u32 nombre, vertice *res, Grafo G);

/*
 * Obtiene el balance de un árbol AVL
 * En caso de T = NULL devuelve 0.
*/
int obtenerBalance(AVLTree *T);

/* 
 * Pone en orden los elementos (vértices) de un árbol en un array empezando desde la
 * posición i hasta a lo sumo la posición n - 1 y destruye el árbol
 * Modifica i para indicar la posición del siguiente elemento libre
 * Si no entran hasta en menos de n, inserta hasta n pero igualmente aumenta i
 * como si los hubieran insertado a todos
 * Los elementos que no pueden entrar se destrullen
 * 
 * PRE: ((T != NULL) <= (array != NULL)) && i != NULL
 */
AVLTree *AVLTree_to_array(AVLTree *T, vertice *array, u32 *i, u32 n);

void preOrder(AVLTree *T);

#endif