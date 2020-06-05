//
// Created by thomas on 15.02.2020.
//

#include <fstream>

int main() {
    long long a, b;

    {
        std::ifstream input("input.txt");
        input >> a >> b;
    }

    {
        std::ofstream output("output.txt");
        output << a + b * b;
    }

    return 0;
}