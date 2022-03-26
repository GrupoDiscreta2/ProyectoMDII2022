#ifndef __AVLTREE_H
#define __AVLTREE_H

/*
TAD de arbol binario autobalanceado
Explicación de wikipedia: https://es.wikipedia.org/wiki/%C3%81rbol_AVL
*/

typedef struct AVLTreeSt AVLTree;

void assertinvRep_AVLTree(AVLTree *T);

AVLTree *nuevo_AVLTree(u32 nombre);

AVLTree *destruir_AVLTree(AVLTree *T);

AVLTree *insertar_AVLTree(AVLTree *T, u32 nombre);


#endif