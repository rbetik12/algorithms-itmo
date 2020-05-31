/**
Структуру данных «куча», или, более конкретно, «неубывающая пирамида», можно реализовать на основе массива.

Для этого должно выполнятся основное свойство неубывающей пирамиды, которое заключается в том, что для каждого  выполняются условия:

если , то ;
если , то .
Дан массив целых чисел. Определите, является ли он неубывающей пирамидой.
*/

#include <iostream>
#include "edx-io.hpp"

int main() {
    int num;
    io >> num;
    int *array = new int[num];
    for (int i = 0; i < num; i++) {
        io >> array[i];
//        std::cout << array[i] << " ";
    }
//    bool correct = isHeap(array, 0, num);
    bool correct = true;
    for (int i = 0; i < (num / 2) - 1; i++) {
        if (2 * i + 1 <= num && array[i] <= array[2 * i + 1]) {
        } else {
            correct = false;
            break;
        }
        if (2 * i + 2 <= num && array[i] <= array[2 * i + 2]) {

        } else {
            correct = false;
            break;
        }
    }
    if (correct) {
        io << "YES";
    } else {
        io << "NO";
    }
    delete[] array;
    return 0;
}
