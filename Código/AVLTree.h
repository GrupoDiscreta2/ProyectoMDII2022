#ifndef __AVLTREE_H
#define __AVLTREE_H

/*
TAD de arbol binario autobalanceado
Explicación de wikipedia: https://es.wikipedia.org/wiki/%C3%81rbol_AVL
*/

#include <stdbool.h>

#include "types.h"

#include "EstructuraGrafo.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

typedef struct AVLTreeSt AVLTree;

/*
 * Crea un árbol AVL con un solo elemento
 * En caso de error de alocado de memoria devuelve NULL
 */
AVLTree *nuevo_AVLTree(u32 nombre);

/*
 * Destrulle un árbol AVL liberando toda su memoria
 */
AVLTree *destruir_AVLTree(AVLTree *T);

/*
 * Agrega un elemento a un árbol AVL
 * En caso de error de alocado de memoria libera toda la memoria del
 * árbol y devuelve NULL
 *
 * Pone *res en true si el elemento ya estaba de antes,
 * si lo tubo que agregar lo pone en false
 *
 * PRE: res != NULL
 */
AVLTree *insertar_AVLTree(AVLTree *T, u32 nombre, bool *res);

void preOrder(AVLTree *T);


#endif