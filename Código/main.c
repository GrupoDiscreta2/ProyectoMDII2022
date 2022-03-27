

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "types.h"

#include "EstructuraGrafo.h"
#include "dump_fancy_plugin.h"
#include "AVLTree.h"

int main() {
    AVLTree *root = NULL;

    bool x = false;

    /* Constructing tree given in the above figure */
    root = insertar_AVLTree(root, 10, &x);
    abb_dump(root);
    root = insertar_AVLTree(root, 20, &x);
    abb_dump(root);
    root = insertar_AVLTree(root, 30, &x);
    abb_dump(root);
    root = insertar_AVLTree(root, 22, &x);
    abb_dump(root);
    root = insertar_AVLTree(root, 50, &x);
    abb_dump(root);
    root = insertar_AVLTree(root, 25, &x);
    
    abb_dump(root);

    /* The constructed AVL Tree would be
              30
             /  \
           20   40
          /  \     \
         10  25    50
    */

    printf("Preorder traversal of the constructed AVL"
           " tree is \n");
    preOrder(root);

    root = destruir_AVLTree(root);

    return 0;
}