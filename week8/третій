//
//  main.cpp
//  pads
//
//  Created by Alexey Ageev.
//  Copyright © 2020 Alexey Ageev. All rights reserved.
//
//MARK: Debug
//#include <ctime>
//unsigned long startTime = clock();
//#include <iostream>
//#include <fstream>

//MARK: Code
#include "edx-io.hpp"
#include <vector>

long long contains (std::vector<long long>, long long);

unsigned hashFunction(long long value);

int main() {
    long long N;
    long long X;
    long long A;
    long long B;
    long long Ac;
    long long Bc;
    long long Ad;
    long long Bd;
    io >> N >> X >> A >> B >> Ac >> Bc >> Ad >> Bd;
    std::vector<long long> vectors[131071];
    for (unsigned long i = 0; i < N; i++){
        long long hash = hashFunction(X);
        if (contains(vectors[hash], X) == -1){
            vectors[hash].push_back(X);
            A = (A + Ad) % 1000;
            B = (B + Bd) % 1000000000000000;
        } else {
            A = (A + Ac) % 1000;
            B = (B + Bc) % 1000000000000000;
        }
        X = (X * A + B) % 1000000000000000;
        
    }
    io << X << " " << A << " " << B;
//    std::cout << std::endl << "!!!COMMENT DEBUG LINES BEFORE TESTING!!!" << std::endl << "Work time: " << 1000 * (clock() - startTime) / CLOCKS_PER_SEC << std::endl;
}

long long contains(std::vector<long long> vec, long long value){
    for (unsigned i = 0; i < vec.size(); i++){
        if (value == vec[i]){
            return i;
        }
    }
    return -1;
}

unsigned hashFunction(long long value){
    return abs(int((value / 4294967296) % 65536 + value % 65536) / 2);
}
