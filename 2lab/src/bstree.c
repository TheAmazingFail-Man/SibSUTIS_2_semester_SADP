#include <stdio.h>
#include <stdlib.h>
#include "bstree.h"

struct bstree *bstree_create(char *key, int value) {
	struct bstree *node;
	node = malloc(sizeof(*node));
	if(node != NULL) {
		node->key = key;
		node->value = value;
		node->left = NULL;
		node->right = NULL;
	}
	return node;
}

void bstree_add(struct bstree *tree, char *key, int value) {
	struct bstree *parent, *node;
	if (tree == NULL) {
	   
		return -1;
	}
	for (parent = tree; tree != NULL;) {
		parent = tree;
		if(key < tree->key) {
			tree = tree->left;
		} else if (key > tree->key) {
			tree = tree->right;
		} else {
			return -1;
		}
	}
	node = bstree_create(key, value);
	if (key < parent->key) {
		parent->left = node;
	} else {
		parent->right = node;
	}
}

struct bstree *bstree_lookup(struct bstree *tree, int value) {
	while(tree != NULL) {
		if(value == tree->value) {
			return tree;
		} else if (value < tree->value) {
			tree = tree->left;
		} else {
			tree = tree->right;
		}
	}
	
	return tree;
}

struct bstree *bstree_min(struct bstree *tree) {
	if (tree == NULL) {
		
		return NULL;
	}
	while (tree->left != NULL) {
		tree = tree->left;
	}
	
	return tree;
}

struct bstree *bstree_max(struct bstree *tree) {
	if (tree == NULL) {
		return NULL;
	}
	while (tree->right != NULL) {
		tree = tree->right;
	}
	
	return tree;
}
