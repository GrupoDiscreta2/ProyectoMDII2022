#include "AVLTree.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "EstructuraGrafo.h"

int main()
{
  AVLTree *root = NULL;
 
  /* Constructing tree given in the above figure */
  root = insertar_AVLTree(root, 10);
  root = insertar_AVLTree(root, 20);
  root = insertar_AVLTree(root, 30);
  root = insertar_AVLTree(root, 40);
  root = insertar_AVLTree(root, 50);
  root = insertar_AVLTree(root, 25);
 
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
 
  return 0;
}