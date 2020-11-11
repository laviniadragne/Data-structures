/**
 * SD, 2020
 * 
 * Lab #9, BST & Heap
 * 
 * Task #1 - Binary Search Tree implementation
 */

#include "bst.h"
#include "utils.h"

static bst_node_t *__bst_node_create(char *data)
{
    char *rc;
    bst_node_t *bst_node;

    bst_node = malloc(sizeof(bst_node_t));
    DIE(bst_node == NULL, "bst_node malloc");

    bst_node->left = bst_node->right = NULL;

    bst_node->data = calloc(BST_DATA_LEN, sizeof(char));
    DIE(bst_node->data == NULL, "bst_node->data malloc");

    rc = strncpy(bst_node->data, data, BST_DATA_LEN - 1);
    DIE(rc != bst_node->data, "bst_node->data strncpy");

    return bst_node;
}

bst_tree_t *bst_tree_create(int (*cmp_f) (const char *, const char *))
{
    bst_tree_t *bst_tree;

    bst_tree = malloc(sizeof(bst_tree_t));
    DIE(bst_tree == NULL, "bst_tree malloc");

    bst_tree->root  = NULL;
    bst_tree->cmp   = cmp_f;

    return bst_tree;
}

void bst_tree_insert(bst_tree_t *bst_tree, char *data)
{
    int rc;
    bst_node_t *root    = bst_tree->root;
    bst_node_t *parent  = NULL;
    bst_node_t *node    = __bst_node_create(data);

    /* TODO */

    // cat timp nu am dat de o frunza
    while(root != NULL) {

        // retin parintele
        parent = root;

        // compar datele ce trebuie introduse cu cele
        // de pe nodul actual
        rc = bst_tree->cmp(data, root->data);
        // daca e mai mic continui pe subarborele stang
        if(rc <= 0)
            root = root->left;
        // daca e mai mare continui pe subarborele drept
        else root = root->right;
    }

    // arborele este gol, adaug nodul ca si radacina
    if(parent == NULL) 
        bst_tree->root = node;

    else 
        // daca este mai mic, il adaug ca fiu stanga
        if(rc <= 0) 
            parent->left = node;
        else 
            // altfel, il adaug ca fiu dreapta
            parent->right = node;

}

// functia gaseste minimul dintr-un arbore
struct bst_node_t * findmin (bst_node_t *node) 
{ 
    bst_node_t* current = node; 
  
    // caut nodul cu valoarea cea mai mica, el se va gasi
    // mereu in subarborele stang
    while (current && current->left != NULL) 
        current = current->left; 
  
    return current; 
} 

static bst_node_t *__bst_tree_remove(bst_node_t *bst_node,
                                    char *data,
                                    int (*f) (const char *, const char *))
{
    int rc;
    bst_node_t *tmp;

    // arborele e gol
    if (!bst_node)
        return NULL;

    rc = f(data, bst_node->data);

    if (rc < 0) {
        /* TODO */
        // caut in subarborele stang
        bst_node->left = __bst_tree_remove(bst_node->left, data, f);
    } else if (rc > 0) {
        /* TODO */
        // caut in subarborele drept
        bst_node->right = __bst_tree_remove(bst_node->right, data, f);
    } else {
        /* TODO */
        // daca am gasit nodul ce trebuie sters
        // daca e frunza
        if(bst_node->left == NULL && bst_node->right == NULL){
            free(bst_node->data);
            free(bst_node);
            bst_node = NULL;
        }
        // are un copil
        else
            // legatura parinte nod cautat - copil nod cautat
            // are subarbore dreapta
            if(bst_node->left == NULL) {
                tmp = bst_node;
                bst_node = bst_node->right;
                free(tmp->data);
                free(tmp);
            }
            else 
                // are subarbore stanga
                if(bst_node->right == NULL) {
                    tmp = bst_node;
                    bst_node = bst_node->left;
                    free(tmp->data);
                    free(tmp);
                }
                // are 2 copii
                else {
                    // gasesc minimul din subarborele stang
                    tmp = findmin(bst_node->right);
                    // schimb nodurile intre ele
                    bst_node->data = tmp->data;
                    // elimin duplicatul, adica minimul cu care tocmai am inlocuit nodul
                    // ce trebuia sters
                    bst_node->right = __bst_tree_remove(bst_node->right, tmp->data, f);
                }
    }

    return bst_node;
}

void bst_tree_remove(bst_tree_t *bst_tree, char *data)
{
    bst_tree->root = __bst_tree_remove(bst_tree->root, data, bst_tree->cmp);
}

static void __bst_tree_free(bst_node_t *bst_node)
{
    if (!bst_node)
        return;

    /* TODO */
    // sterg subarborele stang
    __bst_tree_free(bst_node->left);
    // sterg subarborele drept
    __bst_tree_free(bst_node->right);
    free(bst_node->data);
    free(bst_node);
}

void bst_tree_free(bst_tree_t *bst_tree)
{
    __bst_tree_free(bst_tree->root);
    free(bst_tree);
}
