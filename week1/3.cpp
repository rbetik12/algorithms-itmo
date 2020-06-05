//
// Created by thomas on 15.02.2020.
//

#include <fstream>
#include <vector>

void sort(std::vector<int> &to_sorted, std::vector<int> &target) {
    target.push_back(1);
    for (int i = 1; i < to_sorted.size(); i++) {
        int j;
        for (j = i; j > 0 && to_sorted[j - 1] > to_sorted[j]; j--) {
            int tmp = to_sorted[j - 1];
            to_sorted[j - 1] = to_sorted[j];
            to_sorted[j] = tmp;
        }
        target.push_back(j + 1);
    }

}

int main() {
    int n;
    std::vector<int> vec_inp = {};
    std::vector<int> weirder = {};
    {
        std::ifstream input("input.txt");
        input >> n;

        vec_inp.reserve(n);
        weirder.reserve(n);
        for (int i = 0; i < n; i++) {
            int tmp;
            input >> tmp;
            vec_inp.push_back(tmp);
        }
    }


    sort(vec_inp, weirder);

    {
        std::ofstream output("output.txt");
        for (auto i : weirder)
            output << i << " ";
        output << std::endl;

        for (auto i : vec_inp)
            output << i << " ";
    }

    return 0;
}