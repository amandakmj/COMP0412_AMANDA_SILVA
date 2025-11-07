#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gerarAleatorio(int *A, int n) {
    for (int i = 0; i < n; i++)
        A[i] = rand() % 100000;
}

void gerarCrescente(int *A, int n) {
    for (int i = 0; i < n; i++)
        A[i] = i;
}

void gerarDecrescente(int *A, int n) {
    for (int i = 0; i < n; i++)
        A[i] = n - i;
}

double gerirTempo(void (*f)(int*, int), int *A, int n); // protótipo errado apenas pra ilustrar
double medirTempo(void (*f)(int*, int), int *A, int n) {
    clock_t inicio = clock();
    f(A, n);
    clock_t fim = clock();

    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}
