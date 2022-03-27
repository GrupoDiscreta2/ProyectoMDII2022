#include "cursor.h"

#include <stdio.h>
#include <stdlib.h>

#define assert(_) ;

#include "AVLTree.h"
#define abb AVLTree*
#define left izq
#define right der
#define elem nombre

static unsigned int max(unsigned int x, unsigned int y) {
    return (x > y ? x: y);
}

// Needed for dumping algorithm
static unsigned int abb_height(abb tree) {
    unsigned int height=0;
    if (tree != NULL) {
        unsigned int left_height=abb_height(tree->left);
        unsigned int right_height=abb_height(tree->right);
        height = 1 + max(left_height, right_height);
    }
    return height;
}

// Calculates branch length in the screen (how many dots) for node
static unsigned int branch_length(abb tree) {
    // 2 ^ (height + 1)
    return (1 << (abb_height(tree) + 1));
}

// Draws right branch
static void branch_right(int n) {
    assert(n > 0);
    cursor_down(1);
    if (n == 1) {
            printf(".");
    } else {
        printf(":");
        for (int i=1; i < n; i++)
            printf(".");
    }
}

// Draws left branch
static void branch_left(int n) {
    assert(n > 0);
    cursor_down(1);
    if (n == 1) {
        printf(".");
        cursor_left(2);
    } else {
        printf(":");
        cursor_left(2);
        for (int i=1; i < n; i++) {
            printf(".");
            cursor_left(2);
        }
    }
}

// Scroll down and makes room for n-lines
static void trunk(int n) {
    for (int i=0;i < n; i++)
        printf("\n");
    cursor_up(n);
}


// Calculates left indentation for tree in the screen
static unsigned dump_left_margin(abb tree) {
    unsigned int margin=1;
    if (tree != NULL) {
        unsigned int length = branch_length(tree->left);
        margin = length + dump_left_margin(tree->left);
    }
    return margin;
}

// Show element (leave cursor in original position after printing)
static void dump_elem(abb tree) {
    assert(tree != NULL);
    int moved=0;  // Holds how many chars where printed
    cursor_white();
    printf("%d%n", tree->elem, &moved);
    // Restore cursor position
    cursor_left(moved);
}

// Dump a tree from an internal node
static void dump(abb tree) {
    cursor_down(1);
    if (tree != NULL) {
        unsigned int length_right = branch_length(tree->right);
        unsigned int length_left = branch_length(tree->left);
        // Print current element
        dump_elem(tree);
        //
        // Print branches
        //
        cursor_green();
        // Print branch left
        branch_left(length_left);
        dump(tree->left);
        cursor_right(length_left);
        // Print branch right
        branch_right(length_right);
        dump(tree->right);
        cursor_left(length_right);
    }
    // Move 2 lines up
    cursor_up(2);
}

// Dump entire tree from the root
void abb_dump(abb tree) {
    assert(invrep(tree));
    unsigned int height=abb_height(tree)+1;
    // Make room for tree in the screen
    trunk(height*2);
    // Place cursor in the root position
    cursor_right(dump_left_margin(tree));
    // Print branches
    dump(tree);
    // Leave cursor after tree
    cursor_down(height*2);
    printf("\r");
    // Restore default color
    cursor_no_color();
}

