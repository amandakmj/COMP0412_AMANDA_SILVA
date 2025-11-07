#include <stdio.h>
#include <stdlib.h>

void merge(int *A, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = A[l + i];
    for (int j = 0; j < n2; j++) R[j] = A[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
        A[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];

    while (i < n1) A[k++] = L[i++];
    while (j < n2) A[k++] = R[j++];

    free(L);
    free(R);
}

void mergeRec(int *A, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeRec(A, l, m);
        mergeRec(A, m + 1, r);
        merge(A, l, m, r);
    }
}

void mergesort2(int *A, int n) {
    mergeRec(A, 0, n - 1);
}
