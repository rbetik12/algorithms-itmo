/**
«Сортировка пугалом» — это давно забытая народная потешка, которую восстановили по летописям
специалисты платформы «Открытое образование» специально для этого курса.

Участнику под верхнюю одежду продевают деревянную палку, так что у него оказываются растопырены руки, как у огородного пугала.
 Перед ним ставятся  матрёшек в ряд. Из-за палки единственное, что он может сделать — это взять в руки две матрешки
 на расстоянии  друг от друга (то есть -ую и -ую), развернуться и поставить их обратно в ряд, таким образом поменяв их местами.

Задача участника — расположить матрёшки по неубыванию размера. Может ли он это сделать?
*/

#include <fstream>
#include <iostream>

void quickSort(int *, int, int, int);

void swap(int &, int &);

bool check(const int *array, int size);

#include <chrono>
using namespace std::chrono;

int main() {
    auto start = high_resolution_clock::now();
    std::ifstream inputFile("input.txt");
    int size = 0;
    int k = 0;
    int *array = new int[size];
    inputFile >> size >> k;
    for (int i = 0; i < size; i++) {
        inputFile >> array[i];
    }
    inputFile.close();

    quickSort(array, 0, size - 1, k);

    std::ofstream output("output.txt");
    output << (check(array, size) ? "YES" : "NO");
    output.close();
    delete[] array;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << duration.count() / 1e+6 << std::endl;
    return 0;
}

void quickSort(int *arr, int left, int right, int k) {
    int i = left;
    int j = right;
    int key = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i] < key) {
            i += 1;
        }
        while (arr[j] > key) {
            j -= 1;
        }
        if (i <= j) {
            if (abs(i - j) == k) {
                swap(arr[i], arr[j]);
            }
            i += 1;
            j -= 1;
        }
    }

    if (left < j)
        quickSort(arr, left, j, k);
    if (right > i)
        quickSort(arr, i, right, k);
}

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

bool check(const int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (array[i] > array[i + 1]) return false;
    }
    return true;
}
