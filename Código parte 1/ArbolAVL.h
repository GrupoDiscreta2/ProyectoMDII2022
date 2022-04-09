#ifndef __AVLTREE_H
#define __AVLTREE_H

/*
TAD de árbol binario autobalanceado
Explicación de wikipedia: https://es.wikipedia.org/wiki/%C3%81rbol_AVL
*/

#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "EstructuraGrafo.h"
#include "types.h"

typedef struct ArbolAVLSt ArbolAVL;

/*
 * Crea un árbol AVL con un solo elemento
 * En caso de error de alocado de memoria devuelve NULL
 */
ArbolAVL *Nuevo_ArbolAVL(Vertice v);

/*
 * Destrulle un árbol AVL liberando toda su memoria y la memoria de los
 * elementos
 */
ArbolAVL *Destruir_ArbolAVL(ArbolAVL *T);

/*
 * Agrega un elemento a un árbol AVL
 * En caso de error de alocado de memoria libera toda la memoria del
 * árbol y devuelve NULL
 *
 * Pone el vertice del elemento en res, tanto si ya estaba como si no
 *
 * PRE: res != NULL
 */
ArbolAVL *Insertar_ArbolAVL(ArbolAVL *T, u32 nombre, Vertice *res, Grafo G);

/*
 * Obtiene el balance de un árbol AVL
 * En caso de T = NULL devuelve 0.
 */
int ObtenerBalance_ArbolAVL(ArbolAVL *T);

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
ArbolAVL *ArbolAVL_a_arreglo(ArbolAVL *T, Vertice *array, u32 *i, u32 n);

#endif