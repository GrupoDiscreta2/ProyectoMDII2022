#ifndef __ARREGLODINAMICO_H
#define __ARREGLODINAMICO_H

#include "types.h"

/*
 * TAD básico de un Arreglo Dinámico
*/

typedef struct ArregloDinSt *ArregloDin;

struct ArregloDinSt {
    u32 capacidad;
    u32 tamanio_actual;
    void **elementos;
};

/* 
 * Crea un nuevo arreglo inicializando las datos dentro de la estructura
 * En caso de error de error alocando memoria devuelve NULL  
*/
ArregloDin Nuevo_ArregloDin(u32 cant_elem);

/*
 * Agrega un elemento al final del ArregloDin
 * 
 * PRE: (a != NULL) && (nuevo != NULL)
*/
ArregloDin AgregarEelemento_ArregloDin(ArregloDin a, void *nuevo);

/*
 * Devuelve el elemento en la posición i del arreglo
*/
void *Indexar_ArregloDin(ArregloDin a, u32 i);

/* Achica el arreglo para que solo estén alocados los elementos necesarios
 * 
 * PRE: a != NULL
 */
ArregloDin Achicar_ArregloDin(ArregloDin a);

/* 
 * Libera toda la memoria utilizada por el arreglo dinámico
*/
ArregloDin Destruir_ArregloDin(ArregloDin);

#endif