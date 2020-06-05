//
// Created by thomas on 15.02.2020.
//


#include <fstream>
#include <iostream>

using namespace std;

int main() {
    long long a, b;

    {
        ifstream input("input.txt");
        input >> a >> b;
    }

    {
        ofstream output("output.txt");
        output << a + b;
    }

    return 0;
}