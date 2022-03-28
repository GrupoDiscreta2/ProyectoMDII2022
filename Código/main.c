

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "types.h"

#include "EstructuraGrafo.h"
#include "dump_fancy_plugin.h"
#include "AVLTree.h"

int main() {
    AVLTree *T = NULL;

    bool x = false;

    /* Constructing tree given in the above figure */
    T = insertar_AVLTree(T, 10, &x);
    abb_dump(T);
    T = insertar_AVLTree(T, 20, &x);
    abb_dump(T);
    T = insertar_AVLTree(T, 30, &x);
    abb_dump(T);
    T = insertar_AVLTree(T, 22, &x);
    abb_dump(T);
    T = insertar_AVLTree(T, 50, &x);
    abb_dump(T);
    T = insertar_AVLTree(T, 25, &x);
    
    abb_dump(T);

    /* The constructed AVL Tree would be
              30
             /  \
           20   40
          /  \     \
         10  25    50
    */

//    printf("Preorder traversal of the constructed AVL"
//           " tree is \n");
//    preOrder(T);

    u32 i = 0;

    u32 *array = calloc(6, sizeof(u32));
    T = AVLTree_to_array(T, array, &i);

    for (u32 j = 0; j < 6; j++) {
        printf("%u ", array[j]);
    }

    free(array);

    return 0;
}