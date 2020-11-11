#include <stdio.h>

#include "rb_tree.h"

typedef struct team_t team_t;
struct team_t {
	char	*name;
	int		year;
};

static int f(const void *key1, const void *key2)
{
	int a = *(int *)key1;
	int b = *(int *)key2;

	return (a < b ? -1 : (a == b) ? 0 : 1);
}

static void rb_tree_free_data(void *data)
{
	free(((team_t *)data)->name);
}

static void rb_tree_print_inorder(rb_node_t *root)
{
	if (root == NULL)
		return;

	rb_tree_print_inorder(root->left);
	printf("%d %s %d\n", *(int *)root->key, ((team_t *)root->data)->name, ((team_t *)root->data)->year);
	rb_tree_print_inorder(root->right);
}

int main(void)
{
	int N, task;
	int key;
	team_t *data;
	rb_tree_t *rb_tree;

	rb_tree = rb_tree_create(f, sizeof(int), sizeof(team_t));

	scanf("%d\n", &N);
	while (N--) {
		scanf("%d\n", &task);

		if (task == 0) {
			data = malloc(sizeof(team_t));
			if (data == NULL)
				exit(1);
			data->name = calloc(1, BUFSIZ);
			if (data->name == NULL)
				exit(1);

			scanf("%d %s %d\n", &key, data->name, &data->year);
			rb_tree_insert(rb_tree, &key, data);
			free(data);
		} else if (task == 1) {
			scanf("%d\n", &key);
			data = rb_tree_find(rb_tree, &key);
			if (data != NULL)
				printf("%s %d\n", data->name, data->year), printf("%d\n", N);
		}
	}

	rb_tree_print_inorder(rb_tree->root);

	rb_tree_free(rb_tree, NULL, rb_tree_free_data);
	free(rb_tree);

	return 0;
}
