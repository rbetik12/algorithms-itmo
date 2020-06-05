//
// Created by thomas on 16.02.2020.
//


#include <fstream>
#include <vector>

void quickSort(std::vector<int> &numbers, int left, int right, std::vector<std::pair<int, int>> &target) {
    int pivot; // разрешающий элемент
    int l_hold = left; //левая граница
    int r_hold = right; // правая граница
    pivot = numbers[left];
    while (left < right) // пока границы не сомкнутся
    {
        while ((numbers[right] >= pivot) && (left < right))
            right--; // сдвигаем правую границу пока элемент [right] больше [pivot]
        if (left != right) // если границы не сомкнулись
        {
            numbers[left] = numbers[right]; // перемещаем элемент [right] на место разрешающего
            target.emplace_back(std::min(left, right) + 1, std::max(left, right) + 1);
            left++; // сдвигаем левую границу вправо
        }
        while ((numbers[left] <= pivot) && (left < right))
            left++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
        if (left != right) // если границы не сомкнулись
        {
            numbers[right] = numbers[left]; // перемещаем элемент [left] на место [right]
            target.emplace_back(std::min(left, right) + 1, std::max(left, right) + 1);
            right--; // сдвигаем правую границу вправо
        }
    }
    numbers[left] = pivot; // ставим разрешающий элемент на место
    pivot = left;
    left = l_hold;
    right = r_hold;
    if (left < pivot) // Рекурсивно вызываем сортировку для левой и правой части массива
        quickSort(numbers, left, pivot - 1, target);
    if (right > pivot)
        quickSort(numbers, pivot + 1, right, target);
}

int main() {
    int n;
    std::vector<int> vec_inp = {};
    std::vector<std::pair<int, int>> weirder = {};
    {
        std::ifstream input("input.txt");
        input >> n;

        vec_inp.reserve(n * n);
        weirder.reserve(n);
        for (int i = 0; i < n; i++) {
            int tmp;
            input >> tmp;
            vec_inp.push_back(tmp);
        }
    }


    quickSort(vec_inp, 0, vec_inp.size() - 1, weirder);

    {
        std::ofstream output("output.txt");
        for (auto i : weirder)
            output << "Swap elements at indices " << i.first << " and " << i.second << ".\n";
        output << "No more swaps needed." << std::endl;

        for (auto i : vec_inp)
            output << i << " ";
    }

    return 0;
}