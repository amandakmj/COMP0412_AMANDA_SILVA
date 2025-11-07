#include <stdio.h>

int partitionQuick(int *A, int low, int high) {
    int pivot = A[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (A[j] <= pivot) {
            i++;
            int temp = A[i]; 
            A[i] = A[j];
            A[j] = temp;
        }
    }

    int temp = A[i + 1];
    A[i + 1] = A[high];
    A[high] = temp;

    return i + 1;
}

void quickRec(int *A, int low, int high) {
    if (low < high) {
        int pi = partitionQuick(A, low, high);
        quickRec(A, low, pi - 1);
        quickRec(A, pi + 1, high);
    }
}

void quicksort(int *A, int n) {
    quickRec(A, 0, n - 1);
}
