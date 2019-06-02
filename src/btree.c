#include <stdlib.h>
#include "libbtree.h"

static btree_t **_find_tree_node(btree_t **root, void *data, comparator comp)
{
	btree_t **cur = root;
	while(*cur){
		int cmp_res = comp((*cur)->data, data);
		if (cmp_res > 0)
			cur = &((*cur)->right);
		else if (cmp_res < 0)
			cur = &((*cur)->left);
		else
			return cur;
	}
	return cur;
}

btree_t *add_get_tree_node(btree_t **root, void *data,
	comparator comp, int *added)
{
	btree_t **next = _find_tree_node(root, data, comp);
	if (!*next) {
		(*next) = calloc(1, sizeof(btree_t));
		(*next)->data = data;
		*added = 1;
	}
	return *next;
}

void add_tree_node(btree_t **root, void *data, comparator comp)
{
	int added = 0;
	btree_t __attribute__((unused)) *node = add_get_tree_node(root,
		data, comp, &added);
}


void del_tree_node(btree_t **root, void *data, comparator comp, free_data free_data)
{
	btree_t **node = _find_tree_node(root, data, comp);

	if (!*node)
		return;

	if ((*node)->left && (*node)->right) {
		btree_t **follow = &(*node)->right;
		while(1) {
			if (!(*follow)->left)
				break;
			follow = &(*follow)->left;
		}
		(*node)->data = (*follow)->data;
		if (free_data)
			free_data((*follow)->data);
		free(*follow);
		(*follow) = NULL;
	} else {
		btree_t *next = NULL;
		if (!(next = (*node)->left))
			next = (*node)->right;
		if (free_data)
			free_data((*node)->data);
		free(*node);
		(*node) = next;
	}
}

void itr_tree(btree_t *root, for_each foreach)
{
	if (!root)
		return;
	itr_tree(root->left, foreach);
	foreach(root);
	itr_tree(root->right, foreach);
}

void free_tree(btree_t **root, free_data free_data_func)
{
	if (!*root)
		return;

	free_tree(&(*root)->left, free_data_func);

	if (free_data_func)
		free_data_func((*root)->data);

	free_tree(&(*root)->right, free_data_func);
	free(*root);
	(*root) = NULL;
}

inline btree_t *find_tree_node(btree_t **root, void *data, comparator comp)
{
	return *(_find_tree_node(root, data, comp));
}
