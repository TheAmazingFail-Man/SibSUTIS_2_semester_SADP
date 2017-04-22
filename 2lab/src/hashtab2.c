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
	int word;
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

	for (i = 1; i < n; i++) {	//эксперимент 2 для хэш-таблицы
		if (i % 5000 == 0) {
			//for (j = 0; j < i; j++) {
				FILE *timehashtab2 = fopen("Experiment2hashtab.txt", "w");
				hashtab_add(hashtab, words[i], i);
				time = wtime() - time;
				alltime += time;
				fprintf("n = %d; Elapsed time: %.6f sec.\n", i, alltime);
				fclose(timehashtab2);
  		} else {
  			time = wtime();
  			hashtab_add(hashtab, words[i], i);
  		}
  		//alltime = alltime / i;
  		//printf("n = %d; Elapsed time: %.6f sec.\n", i, alltime);
  		//}
	}
	
	return 0;
}
