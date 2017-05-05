#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
//#include "bstree.h"
//#include "hashtab.h"

double wtime() {
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

typedef struct {
	char *value;
	int key;
	struct listnode *next;
} listnode;

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

int main()
{
	int n = 0, m = 0, max = 0, i;
	double t, alltime = 0;
	srand(time(NULL));
	struct listnode *hashtab, *node;
	//struct listnode *hashtab[HASHTAB_SIZE];
	FILE *book = fopen("book.txt", "r");
	while (!feof(book)) {
		if (fgetc(book) == '\n') {
			n++;
			max = m;
			m = 0;
		} else {
			m++;
		}
	}
	//words = (char*)malloc(n * max * sizeof(char));
	char words[n][max];
	for(i = 0; i < n; i++) {
		fscanf(book, "%s", words[i]);
    }
	fclose(book);

	hashtab_init(hashtab);

	for (i = 1; i < n; i++) {
  		hashtab_add(hashtab, words[i], i);
		if (i % 4999 == 0) {
			//for (j = 0; j < i; j++) {
				FILE *timehashtab1 = fopen("Experiment1hashtab.txt", "w");
				t = wtime();
				node = hashtab_lookup(hashtab, words[getrand(0, i)]);
				t = wtime() - t;
				alltime += t;
				fprintf(timehashtab1, "n = %d; Elapsed time: %.6f sec.\n", i, alltime);
				fclose(timehashtab1);
  		}
  		//alltime = alltime / i;
  		//printf("n = %d; Elapsed time: %.6f sec.\n", i, alltime);
  		//}
	}
	
	return 0;
}
