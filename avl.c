#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "avl.h"


// Creaza structura avl-ului
Avl_tree* avl_create(int (*cmp)(void*, void*)) {
	Avl_tree *tree = malloc(sizeof(Avl_tree));
	tree->compar = cmp;
	if (tree == NULL) {
		return NULL;
	}
	tree->root = NULL;
	return tree;
}
void node_free(Node **node) {
	if ((*node)->left != NULL) {
		node_free(&(*node)->left);
	}
	if ((*node)->right != NULL) {
		node_free(&(*node)->right);
	}
	Node *temp = (*node);
	if ((*node)->left == NULL && (*node)->right == NULL) {
		free(temp->data);
		(*node) = NULL;
		free(temp);
		return;
	}
}
void avl_free(Avl_tree *tree) {
	if (tree->root != NULL) {
		node_free(&tree->root);
	}
	free(tree);
}
int max(int a, int b) {
	if (a > b) {
		return a;
	}
	return b;
}
/* Creaza un nod 
 * @param1: Valoarea ce trebuie pusa in nod.
 * @param2: Numarul de octeti pe care scrie valoarea.
 */
Node* node_create(void *value, int data_size) {
	Node *node = malloc(sizeof(Node));
	if (node == NULL) {
		return NULL;
	}
	node->data = malloc(data_size);

	// Copiere octet cu octet din value, in nodul curent.
    // OBS: char are 1 octet.  
    for (int i = 0; i < data_size; ++i) {
        *(char *)(node->data + i) = *(char *)(value + i);
    }

    // Nodurile frunze au inaltimea 0.
	node->height = 0;
	node->left = NULL;
	node->right = NULL;

	return node;
}
// Nodurile NULL au inaltimea -1 pentru a respecta regula:
// node->height = 1 + max(node->left->height, nod->right->height)
int height(Node *node) {
	if (node == NULL) {
		return -1;
	}
	return node->height;
}
/* Rotire dreapta
 * Pentru a nu fi nevoie sa mentinem pointer catre nodul parinte,
 * se vor folosi pointeri la noduri
 *
 *      node  			    lson
 *     /    \			   /    \ 
 *   lson    y    --->    x    node
 *   /  \     		           /   \ 
 *  x   lrson                lrson  y
 */
void rotate_right(Node **node) {
	// TODO: Completati rotire dreapta

	Node *lson = (*node)->left;
	Node *lrson = lson->right;
	Node *rson = (*node);

	(*node) = lson;
	(*node)->right = rson;
	(*node)->right->left = lrson;

	// Restabilire intaltimi
	(*node)->right->height = 1 + max(height((*node)->right->left), height((*node)->right->right));
	(*node)->height = 1 + max(height((*node)->left), height((*node)->right));

}
/* Rotire stanga
 * Pentru a nu fi nevoie sa mentinem pointer catre nodul parinte,
 * se vor folosi pointeri la noduri
 *
 *     node  			    rson
 *    /    \			   /    \ 
 *   x     rson    --->  node    y
 *         /   \		 /   \
 *       rlson  y       x   rlson
 */	
void rotate_left(Node **node) {
	// TODO: Completati rotire stanga.

	Node *rson = (*node)->right;
	Node *rlson = rson->left;
	Node *lson = (*node);
	
	(*node) = rson;
	(*node)->left = lson;
	(*node)->left->right = rlson;

	// Restabilire inaltimi
	(*node)->left->height = 1 + max(height((*node)->left->left), height((*node)->left->right));
	(*node)->height = 1 + max(height((*node)->left), height((*node)->right));

}


// Echilibrarea AVL-ului
void avl_fix(Node **node) {
	// TODO: Completati rotatiile corespunzatoare
	if (height((*node)->left) > height((*node)->right) + 1 
		&& height((*node)->left->left) >= height((*node)->left->right)) {
		/* Rotatie RR
		 *
		 *     node                  a
		 *     /                    / \
		 *    a          --->      b   node
		 *   /
		 *  b
		 *
		 */
		// TODO

		rotate_right(node);
		return;


	} else if (height((*node)->right) > height((*node)->left) + 1 
				&& height((*node)->right->right) >= height((*node)->right->left)) {
		/* Rotatie LL
		 *
		 *     node                a
		 *        \               / \
		 *         a     --->  node  b
		 *          \ 
		 *           b
		 *
		 */
		// TODO

		rotate_left(node);
		return;


	} else if (height((*node)->left) > height((*node)->right) + 1 
				&& height((*node)->left->left) < height((*node)->left->right)) {
		/* Rotatie LR
		 *
		 *     node                node               b
		 *     /        left       /      right      / \
		 *    a         --->      b        --->     a   node
		 *     \                 /
		 *      b               a
		 *
		 */
		// TODO

		rotate_left(&(*node)->left);
		rotate_right(node); 
		return;


	} else if (height((*node)->right) > height((*node)->left) + 1 
				&& height((*node)->right->right) < height((*node)->right->left)) {

		/* Rotatie RL
		 *
		 *     node                node                  b
		 *        \      right        \       left      / \
		 *         a      --->         b       --->   node a
		 *        /                     \
		 *       b                       a
		 *
		 */
		// TODO

		rotate_right(&(*node)->right);
		rotate_left(node);
		return;
	}
}
/* Inserare in AVL
 * 
 * @param1: Nodul radacina al subarborelui din parcurgerea recursiva.
 * @param2: Valoare de adaugat in AVL.
 * @param3: Numarul de octeti pe care se scrie valoarea.
 * @param4: Functia de comparare pentru datele din AVL.
 */
void avl_insert(Node **node, void *value, int data_size, int (*compar)(void*, void*)) {
	// TODO: Inserati recursiv in arbore

	if((*node) == NULL) {
		(*node) = node_create(value, data_size);
		return ;
	} 
	// insert ca la bfs
	else if (compar((*node)->data, value) > 0) {
		avl_insert(&(*node)->left, value, data_size, compar);
	}
	else {
		avl_insert(&(*node)->right, value, data_size, compar);
	}

	// update la height
	(*node)->height = 1 + max(height((*node)->left), height((*node)->right));

	// reechilibrare arbore
	avl_fix(node);
	return;
	

}
void* get_key(Node *node, void *value, int data_size, int (*compar)(void*, void*)) {
	// TODO: Cautarea unei valori in arbore
	// nu se gaseste valoarea in treap
	if (node == NULL || node->data == NULL) return NULL;

	// compar valoarea nodului cautat cu valoarea din nodul curent
    int rc = compar(value, node->data);

    // l-am gasit
    if(rc == 0) return value;
    else {
    	if (rc < 0) 
    		return get_key(node->left, value, data_size, compar);
    	else {
    	return get_key(node->right, value, data_size, compar);
    	}	
	}
}
// Elementul maxim din subarbore
Node *max_element(Node *node) {
	if (node->right == NULL) {
		return node;
	}
	return max_element(node->right);
}
/* Stergere din AVL
 * 
 * @param1: Nodul radacina al subarborelui din parcurgerea recursiva.
 * @param2: Valoare de adaugat in AVL.
 * @param3: Numarul de octeti pe care se scrie valoarea.
 * @param4: Functia de comparare pentru datele din AVL.
 */
void avl_delete(Node **node, void *value, int data_size, int (*compar)(void*, void*)) {
	// TODO: Stergeti recursiv din arbore

	if((*node) == NULL) {
		return;
	}
	if(compar((*node)->data, value) > 0) {
		avl_delete(&(*node)->left, value, data_size, compar);
	} 
	else if (compar((*node)->data, value) < 0) {
		avl_delete(&(*node)->right, value, data_size, compar);
	}
	else {

		// are 0 copii
		if(((*node)->left == NULL) && ((*node)->right == NULL)) {

            free((*node)->data);
            free(*node);
            *node = NULL;
            return;
		}
		// are un succesor
		else if (((*node)->left == NULL) || ((*node)->right == NULL)) {

			if ((*node)->left == NULL){
				Node *tmp = (*node)->right;
				free((*node)->data);
				free(*node);
				*node = tmp;
			}
			else if ((*node)->right == NULL){
					Node *tmp = (*node)->left;
					free((*node)->data);
					free(*node);
					*node = tmp;
			}
			
		}
		else {
			Node *max_node = max_element((*node)->left);

			// Copiere octet cu octet din max_node, in nodul curent.
    		// OBS: char are 1 octet.  
    		for (int i = 0; i < data_size; ++i) {
        		*(char *)((*node)->data + i) = *(char *)(max_node->data + i);
    		}

			avl_delete(&(*node)->left, max_node->data, data_size, compar);
		}
	}

	// noua inaltime
	(*node)->height = 1 + max(height((*node)->left), height((*node)->right));
	
	// reechilibrare arbore
	avl_fix(node);
	return;

	
}

void preorder_traversal(Node *node) {
	if (node == NULL) {
		return;
	}
	printf("%d ", *(int*)node->data);
	preorder_traversal(node->left);
	preorder_traversal(node->right);
}
