//Дан массив целых чисел. Ваша задача — отсортировать его в порядке неубывания с помощью сортировки слиянием.
//
//Чтобы убедиться, что Вы действительно используете сортировку слиянием, мы просим Вас, после каждого осуществленного
//слияния (то есть, когда соответствующий подмассив уже отсортирован!), выводить индексы граничных элементов и их значения.

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

int min(int x, int y) { return (x < y) ? x : y; }

void merge(int *A, int p, int q, int r, std::ofstream& outputFile) {
    int n1, n2, i, j, k;
    bool merging = false;

    n1 = q - p + 1;
    n2 = r - q;

    int *L = new int[n1];
    int *R = new int[n2];

    for (i = 0; i < n1; i++) {
        L[i] = A[p + i];
    }

    for (j = 0; j < n2; j++) {
        R[j] = A[q + j + 1];
    }

    i = 0, j = 0;

    for (k = p; i < n1 && j < n2; k++) {
        if (L[i] < R[j]) {
            A[k] = L[i++];
            merging = true;
        } else {
            A[k] = R[j++];
            merging = true;
        }
    }

    while (i < n1) {
        A[k++] = L[i++];
    }

    while (j < n2) {
        A[k++] = R[j++];
    }

    if (merging) {
        outputFile << p + 1 << " " << r + 1 << " " << A[p] << " " << A[r] << std::endl;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int *arr, int n) {
    int curr_size;
    int left_start;
    std::ofstream outputFile("output.txt", std::ios_base::app);

    for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = min(left_start + curr_size - 1, n - 1);

            int right_end = min(left_start + 2 * curr_size - 1, n - 1);

            merge(arr, left_start, mid, right_end, outputFile);
        }
    }

    outputFile.close();
}

int main() {
    std::ifstream inputFile("input.txt");
    int size;
    inputFile >> size;
    int *array = new int[size];

    for (int i = 0; i < size; i++) {
        inputFile >> array[i];
    }

    inputFile.close();
    mergeSort(array, size);

    std::ofstream outputFile("output.txt", std::ios_base::app);

    for (size_t i = 0; i < size; i++) {
        outputFile << array[i] << " ";
    }

    outputFile.close();
    delete[] array;
    return 0;
}