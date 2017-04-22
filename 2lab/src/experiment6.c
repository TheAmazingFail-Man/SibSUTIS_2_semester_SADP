#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
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
	char *words;
	double time, alltime = 0;
	int word;
	struct bstree *tree, *node;
	struct listnode *node;
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
		fgets(words[n], n, book);
    }
	fclose(book);
	
	tree = bstree_create(words[0], 0);	//создает корень дерева

	hashtab_init(hashtab);	//создаём основу для таблицы

	for (i = 1; i < n; i++) {	//эксперимент 1 для бинарного дерева
  		bstree_add(tree, words[i], i);
		if (i % 5000 == 0) {
			//for (j = 0; j < i; j++) {
				word = getrand(0, i);
				FILE *timebstree1 = fopen("Experiment1bstree.txt", "w");
				time = wtime();
				node = bstree_lookup(tree, word);
				time = wtime() - time;
				alltime += time;
				fprintf("n = %d; Elapsed time: %.6f sec.\n", i, alltime);
				fclose(timebstree1);
  		}
  		//alltime = alltime / i;
  		//printf("n = %d; Elapsed time: %.6f sec.\n", i, alltime);
  		//}
	}

	for (i = 1; i < n; i++) {	//эксперимент 1 для хэш-таблицы
  		hashtab_add(hashtab, words[i], i);
		if (i % 5000 == 0) {
			//for (j = 0; j < i; j++) {
				word = getrand(0, i);
				FILE *timehashtab1 = fopen("Experiment1hashtab.txt", "w");
				time = wtime();
				node = hashtab_lookup(hashtab, word);
				time = wtime() - time;
				alltime += time;
				fprintf("n = %d; Elapsed time: %.6f sec.\n", i, alltime);
				fclose(timehashtab1);
  		}
  		//alltime = alltime / i;
  		//printf("n = %d; Elapsed time: %.6f sec.\n", i, alltime);
  		//}
	}
	
	return 0;
}