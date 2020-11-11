#ifndef __AVL_H_
#define __AVL_H_


typedef struct Node{
	void *data;
	int height;

	struct Node *left, *right;
} Node;
typedef struct {
	Node *root;
	int(*compar)(void*, void*);
} Avl_tree;

// Creaza structura avl-ului
Avl_tree* avl_create(int (*cmp)(void*, void*));

void node_free(Node **node);

void avl_free(Avl_tree *tree);

/* Creaza un nod 
 * @param1: Valoarea ce trebuie pusa in nod.
 * @param2: Numarul de octeti pe care scrie valoarea.
 */
Node* node_create(void *value, int data_size);

// Nodurile NULL au inaltimea -1 pentru a respecta regula:
// node->height = 1 + max(node->left->height, nod->right->height)
int height(Node *node);

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
void rotate_right(Node **node);

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
void rotate_left(Node **node);

// Echilibrarea AVL-ului
void avl_fix(Node **node);

/* Inserare in AVL
 * 
 * @param1: Nodul radacina al subarborelui din parcurgerea recursiva.
 * @param2: Valoare de adaugat in AVL.
 * @param3: Numarul de octeti pe care se scrie valoarea.
 * @param4: Functia de comparare pentru datele din AVL.
 */
void avl_insert(Node **node, void *value, int data_size, int (*compar)(void*, void*));

void* get_key(Node *node, void *value, int data_size, int (*compar)(void*, void*));

// Elementul maxim din subarbore
Node *max_element(Node *node);

/* Stergere din AVL
 * 
 * @param1: Nodul radacina al subarborelui din parcurgerea recursiva.
 * @param2: Valoare de adaugat in AVL.
 * @param3: Numarul de octeti pe care se scrie valoarea.
 * @param4: Functia de comparare pentru datele din AVL.
 */
void avl_delete(Node **node, void *value, int data_size, int (*compar)(void*, void*));

void preorder_traversal(Node *node);

#endif
