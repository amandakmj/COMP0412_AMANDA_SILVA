#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

int main() {

    srand(time(NULL));

    int tamanhos[] = {500, 1000};
    int qtd = 3;

    FILE *arq = fopen("tempos.txt", "w");

    for (int t = 0; t < qtd; t++) {
        int n = tamanhos[t];
        int *A = malloc(n * sizeof(int));

        fprintf(arq, "\nTamanho: %d\n", n);

        // Insertion
        gerarAleatorio(A, n);
        fprintf(arq, "Insertion: %f\n", medirTempo(insertion, A, n));

        // MergeSort
        gerarAleatorio(A, n);
        fprintf(arq, "MergeSort2: %f\n", medirTempo(mergesort2, A, n));

        // QuickSort
        gerarAleatorio(A, n);
        fprintf(arq, "QuickSort: %f\n", medirTempo(quicksort, A, n));

        free(A);
    }

    fclose(arq);

    return 0;
}
