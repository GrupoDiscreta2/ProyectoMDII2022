#ifndef __ARREGLODINAMICO_H
#define __ARREGLODINAMICO_H

#include "types.h"

/*
 * TAD básico de un Arreglo Dinámico
*/

typedef struct arregloSt *arreglo;

struct arregloSt {
    u32 capacidad;
    u32 tamanio_actual;
    void **elementos;
};

/* 
 * Crea un nuevo arreglo inicializando las datos dentro de la estructura
 * En caso de error de error alocando memoria devuelve NULL  
*/
arreglo nuevo_arreglo_dinamico(u32 cant_elem);

/*
 * Agrega un elemento al final del arreglo
 * 
 * PRE: (a != NULL) && (nuevo != NULL)
*/
arreglo agregar_elemento(arreglo a, void *nuevo);

/*
 * Devuelve el elemento en la posición i del arreglo
*/
void *indexar_arreglo(arreglo a, u32 i);

/* Achica el arreglo para que solo estén alocados los elementos necesarios
 * 
 * PRE: a != NULL
 */
arreglo achicar_arreglo(arreglo a);

/* 
 * Libera toda la memoria utilizada por el arreglo dinámico
*/
arreglo destuir_arreglo_dinamico(arreglo);

#endif