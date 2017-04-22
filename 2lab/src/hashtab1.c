#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include "bstree.h"
#include "hashtab.h"

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
	int n = 0, m = 0, max = 0, i;
	double t, alltime = 0;
	srand(time(NULL));
	struct listnode *hashtab, *node;
	//struct listnode *hashtab[HASHTAB_SIZE];
	FILE *book = fopen("book.txt", "r");
	while (!feof(book)) {	//считает количество слов в книге и ищет самое длинное слово
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
	for(i = 0; i < n; i++) {	//заполняет массив словами из книги
		fscanf(book, "%s", words[i]);
    }
	fclose(book);

	hashtab_init(hashtab);	//создаём основу для таблицы

	for (i = 1; i < n; i++) {	//эксперимент 1 для хэш-таблицы
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
