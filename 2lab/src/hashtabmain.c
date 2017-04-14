#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include "hashtab.h"

#define HASHTAB_SIZE 600000
#define HASHTAB_MUL  31

double wtime() {
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

int main()
{
	int n, i = 0, j;
	double time, alltime = 0;
	struct listnode *node;
	struct listnode *hashtab[HASHTAB_SIZE];
	char words[51203][60], *w;
	FILE *in = fopen("book.txt", "r");
	for(n = 0; n < 51203; n++) {
		fgets(words[n], 60000, in);
	}
	fclose(in);
	hashtab_init(hashtab);
	for (i = 2; i < 200000; i++) {
		hashtab_add(hashtab, words[i % 51203], i - 1);
		if (i % 10000 == 0) {
			for (j = 0; j < 2; j++) {
				w = words[getrand(0, i - 1)];
				time = wtime();
				hashtab_delete(hashtab, w);
				node = hashtab_lookup(hashtab, w);
				time = wtime() - time;
        	 	alltime = alltime + time;
			}
        alltime = alltime / i;
		printf("n = %d; Elapsed time: %.15f sec.\n", i - 1, alltime);
		}
	}
	
	return 0;
}
