#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "hashtab.h"

#define HASHTAB_SIZE 600000
#define HASHTAB_MUL  10

unsigned int hashtab_hash(char *key) {
	unsigned int h = 0;
	char *p;
	for (p = key; *p != '\0'; p++) {
	   h = h * HASHTAB_MUL + (unsigned int) * p;
	}
	
	return h % HASHTAB_SIZE;
}

void hashtab_init(struct listnode **hashtab) {
	int i;
	for (i = 0; i < HASHTAB_SIZE; i++) {
		hashtab[i] = NULL;
	}
}

unsigned int hashtab_hash_xor(char *key)
{
    unsigned char *p = key;
    unsigned h = 0;
    int i;
    
    for (i=0; i < 25 ; i++) {
    	h^=p[i];
    }

    return h;
}

void hashtab_add(struct listnode **hashtab, char *key, int value) {
	struct listnode *node;
	int index = hashtab_hash(key);
	node = malloc(sizeof(*node));
	if (node != NULL) {
		node->key = key;
		node->value = value;
		node->next = hashtab[index];
		hashtab[index] = node;
	}
}

struct listnode *hashtab_lookup(struct listnode **hashtab, char *key){
	int index;
	struct listnode *node;
	index = hashtab_hash(key);
	node = hashtab[index];
        while (node != NULL){
			if (strcmp(node->key, key) == 0) {
			
				return node;
			}
			node = node->next;
	}
	
	return NULL;
}

void hashtab_delete(struct listnode **hashtab, char *key) {
	int index;
	struct listnode *p, *prev = NULL;
	index = hashtab_hash(key);
	for (p = hashtab[index]; p != NULL; p = p->next) {
		if (strcmp(p->key,key) == 0) {
			if (prev == NULL) {
				hashtab[index] = p->next;
			} else {
				prev->next = p->next;
			}
			free(p);
			
			return;
		}
		prev = p;
	}
}