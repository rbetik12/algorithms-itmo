/**
Дан массив из  элементов, упорядоченный в порядке неубывания, и  запросов: найти первое и последнее вхождение некоторого числа в массив.
 Требуется ответить на эти запросы.
*/

#include <iostream>
#include "edx-io.hpp"

const int *bin_search(int const *array, int size, int key) {
    int left = 0;
    int right = size - 1;
    int firstIndex = -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (array[mid] > key) {
            right = mid - 1;
        } else if (array[mid] < key) {
            left = mid + 1;
        } else if (array[mid] == key) {
            firstIndex = mid;
            break;
        }
    }
    int *const answer = new int[2];
    answer[0] = -1;
    answer[1] = -1;
    if (firstIndex == -1)
        return answer;
    else {
        int i = firstIndex;
        while (array[i] == array[firstIndex]) {
            i += 1;
        }
        answer[1] = i;
        i = firstIndex;
        while (array[i] == array[firstIndex]) {
            i -= 1;
        }
        answer[0] = i + 2;
//        std::cout << i << std::endl;
        return answer;
    }
}

int main() {
    int arraySize, requestsCount;
    io >> arraySize;
    int *array = new int[arraySize];
    for (int i = 0; i < arraySize; i++) {
        io >> array[i];
    }
    io >> requestsCount;
    int *requests = new int[requestsCount];
    for (int i = 0; i < requestsCount; i++) {
        io >> requests[i];
    }
    for (int i = 0; i < requestsCount; i++) {
        int const *answer = bin_search(array, arraySize, requests[i]);
        io << answer[0] << " " << answer[1] << '\n';
        delete[] answer;
    }
    delete[] requests;
    delete[] array;
    return 0;
}
