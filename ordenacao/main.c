#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"   
int is_sorted(int *A, int n) {
    for (int i = 1; i < n; ++i)
        if (A[i-1] > A[i]) return 0;
    return 1;
}

double medir_tempo_copia(void (*f)(int*,int), int *orig, int n) {
    int *B = malloc(n * sizeof(int));
    if (!B) { perror("malloc"); exit(1); }
    memcpy(B, orig, n * sizeof(int));
    clock_t inicio = clock();
    f(B, n);
    clock_t fim = clock();
    int sorted = is_sorted(B, n);
    free(B);
    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}

int main() {
    srand((unsigned) time(NULL));

    int tamanhos[] = {1000, 5000, 10000};
    int n_tam = sizeof(tamanhos)/sizeof(tamanhos[0]);

    const char *tipos_nome[] = {"aleatorio","crescente","decrescente"};
    const char *alg_nome[] = {"insertion","mergesort2","quicksort"};

    FILE *out = fopen("tempos.csv", "w");
    if (!out) { perror("fopen"); return 1; }

    fprintf(out, "tamanho,tipo,algoritmo,tempo_s,ordenado\n");

    for (int ti = 0; ti < n_tam; ++ti) {
        int n = tamanhos[ti];
        int *orig = malloc(n * sizeof(int));
        if (!orig) { perror("malloc"); return 1; }

        for (int tipo = 0; tipo < 3; ++tipo) {
            if (tipo == 0) gerarAleatorio(orig, n);
            else if (tipo == 1) gerarCrescente(orig, n);
            else gerarDecrescente(orig, n);

            // insertion
            {
                int *tmp = malloc(n * sizeof(int));
                memcpy(tmp, orig, n * sizeof(int));
                clock_t i0 = clock();
                insertion(tmp, n);
                clock_t i1 = clock();
                int ok = is_sorted(tmp, n);
                double tempo = (double)(i1 - i0) / CLOCKS_PER_SEC;
                fprintf(out, "%d,%s,%s,%.6f,%d\n", n, tipos_nome[tipo], alg_nome[0], tempo, ok);
                free(tmp);
            }

            // mergesort2
            {
                int *tmp = malloc(n * sizeof(int));
                memcpy(tmp, orig, n * sizeof(int));
                clock_t i0 = clock();
                mergesort2(tmp, n);
                clock_t i1 = clock();
                int ok = is_sorted(tmp, n);
                double tempo = (double)(i1 - i0) / CLOCKS_PER_SEC;
                fprintf(out, "%d,%s,%s,%.6f,%d\n", n, tipos_nome[tipo], alg_nome[1], tempo, ok);
                free(tmp);
            }

            // quicksort
            {
                int *tmp = malloc(n * sizeof(int));
                memcpy(tmp, orig, n * sizeof(int));
                clock_t i0 = clock();
                quicksort(tmp, n);
                clock_t i1 = clock();
                int ok = is_sorted(tmp, n);
                double tempo = (double)(i1 - i0) / CLOCKS_PER_SEC;
                fprintf(out, "%d,%s,%s,%.6f,%d\n", n, tipos_nome[tipo], alg_nome[2], tempo, ok);
                free(tmp);
            }
        }

        free(orig);
    }
    
    fclose(out);
    printf("Testes concluídos. Resultados salvos em tempos.csv\n");

    // tempo
    clock_t inicio_total = clock();
    clock_t fim_total = clock();
    double tempo_total = (double)(fim_total - inicio_total) / CLOCKS_PER_SEC;
    printf("Tempo total medido com clock(): %.6f segundos\n", tempo_total);
    printf("Para medir usando o programa 'time', execute:\n");
    printf("time ./ordenacao\n");

    return 0;
}
