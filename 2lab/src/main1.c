#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtab.h"
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
    Node *node = NULL;
    double t = 0;
    int i, step = 0, coll = 0;
    FILE *f = fopen("book.txt", "r");

    if (f)
        for (i = 0; i < SIZE; i++) {
            fscanf(f, "%s", words[i]);
        }
    else {
        printf("Error: in_file doesn't exist!\n");
        return -1;
    }

    fclose(f);


    f = fopen("djbex6sort.txt", "w");

    for (i = 0; i < SIZE; i++) {

        hashtab_add(hashtab, words[i], i);

        if ((i + 1) % 2500 == 0) {
            step = i / 2500;
            t = wtime();

            
                node = hashtab_lookup(hashtab, words[i]);
            fprintf(f, "%d\t%lf\n", i+1, wtime() - t);

    }
    }

    fclose(f);

return 0;    
}
