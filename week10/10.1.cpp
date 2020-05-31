/**
Постройте префикс-функцию для всех непустых префиксов заданной строки .
*/

#include <string>
#include <vector>
#include "edx-io.hpp"

std::vector<int> prefix(std::string &s) {
    std::vector<int> p = {0};
    for (int i = 1; i < s.length(); i++) {
        int k = p[i - 1];
        while (k > 0 && s[i] != s[k])
            k = p[k - 1];
        if (s[i] == s[k])
            k++;
        p.push_back(k);
    }
    return p;
}

int main() {
    std::string s;
    io >> s;
    std::vector<int> p = prefix(s);
    for (auto s: p) {
        io << s << " ";
    }
}