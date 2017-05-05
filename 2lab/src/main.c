#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstree.h"
#include <time.h>
#include <sys/time.h>
#define SIZE 51203
static char words[SIZE][25];

double wtime()
{
    struct timeval t;
    gettimeofday(&t,NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max-min) + min;
}




int main()
{
    int coll=0;
    bstree *tree = NULL, *node = NULL;
    double t = 0;
    int i, step = 0;
    FILE *f = fopen("book.txt", "r");

    if (f)
        for (i = 0; i < SIZE; i++) {
            fscanf(f, "%s", words[i]);
        }
    else {
        printf("Error: file doesn't exists!\n");
        return -1;
    }

    fclose(f);

    f = fopen("out.txt", "w");

    for (i = 0; i < SIZE; i++) {
        tree = bstree_add(tree, words[i], i,&coll);

        if ((i+1) % 2500 == 0) {
            step = i / 2500;
            t = wtime();
                node = bstree_lookup(tree, words[getrand(0, i+1)]);
            fprintf(f, "%d\t%lf collision: %d\n", i+1, wtime() - t,coll);
        }

    }

    fclose(f);

return 0;
}
