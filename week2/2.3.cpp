//Хотя QuickSort является очень быстрой сортировкой в среднем, существуют тесты, на которых она работает очень долго.
//Оценивать время работы алгоритма будем числом сравнений
//с элементами массива (то есть, суммарным числом сравнений в первом и втором while).
//Требуется написать программу, генерирующую тест, на котором быстрая сортировка сделает наибольшее число таких сравнений.

#include <fstream>

void swap (int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    std::ifstream inputFile("input.txt");
    int size = 0;
    inputFile >> size;
    inputFile.close();

    std::ofstream output("output.txt");
    int *array = new int[size];

    for (int i = 0; i < size; i++) {
        array[i] = i + 1;
    }
    for (int i = 2; i < size; i++) {
        swap(array[i], array[i/2]);
    }
    for (int i = 0; i < size; i++) {
        output << array[i] << " ";
    }
    output.close();
    delete[] array;
    return 0;
}
