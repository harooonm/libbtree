#ifndef _LIBBTREE_H_
#define _LIBBTREE_H_

typedef struct tree_node{
	void *data;
	struct tree_node *left;
	struct tree_node *right;
}btree_t;

typedef void (*for_each)(btree_t *n);
typedef int (*comparator)(void *old, void *new);
typedef void (*free_data)(void *data);

extern btree_t *add_get_tree_node(btree_t **root, void *data,
	comparator comp, int *added);
extern void add_tree_node(btree_t **root, void *data, comparator comp);
extern void del_tree_node(btree_t **root, void *data, comparator comp, free_data free_data_func);
extern void itr_tree(btree_t *root, for_each foreach);
extern void free_tree(btree_t **root, free_data free_data_func);
extern btree_t *find_tree_node(btree_t **root, void *data, comparator comp);

#endif
