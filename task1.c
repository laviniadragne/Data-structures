/* Laborator 11 SD - AVL / Red-Black
 * Autori:
 *
 * Andrei Topala - topala.andrei@gmail.com
 * Dorin Geman  - doringeman@gmail.com
 *
 * Echipa SD, 2020
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

// INT custom comparison function
int compar(void* value1, void* value2) {

    int *a = (int*)value1; 
    int *b = (int*)value2;
    if ((*a) > (*b)) {
        return 1; 
    } else if ((*a) < (*b)) {
        return -1; 
    }
    return 0;
}

int main() {
    Avl_tree *tree = avl_create((int (*)(void*, void*))(compar));

    int task, no_inserts, no_deletes, no_finds;
    int value;

    scanf("%d", &task);
    // ------------- TASK 1 -------------
    if (task == 1) { 
        printf("%s\n", "------------- TASK 1 -------------");
    }
    scanf("%d", &no_inserts);
    for (int i = 0; i < no_inserts; ++i) {
        scanf("%d", &value);
        avl_insert(&tree->root, &value, sizeof(int), tree->compar);
        // Used for checker.
        if (task == 1) {
            printf("%s: ", "Preoder");
            preorder_traversal(tree->root);
            printf("\n");
        }
    }
    if (task >= 2) {
        // ------------- TASK 2 -------------
        if (task == 2) {
            printf("%s\n", "------------- TASK 2 -------------");
        }
        scanf("%d", &no_finds);
        for (int i = 0; i < no_finds; ++i) {
            scanf("%d", &value);
            if (task == 3) {
                continue;   
            }
            if (get_key(tree->root, &value, sizeof(int), tree->compar)) {
                printf("%d %s\n", value, "is in AVL.");
            } else {
                printf("%d %s\n", value, "is NOT in AVL.");
            }
        }
    }
    // ------------- TASK 3 -------------
    if (task == 3) {
        printf("%s\n", "------------- TASK 3 -------------");
        scanf("%d", &no_deletes);
        for (int i = 0; i < no_deletes; ++i) {
            scanf("%d", &value);
            avl_delete(&tree->root, &value, sizeof(int), tree->compar);
            // Used for checker.
            printf("%s: ", "Preoder");
            preorder_traversal(tree->root);
            printf("\n");
        }
    }
    avl_free(tree);
    return 0;
}
