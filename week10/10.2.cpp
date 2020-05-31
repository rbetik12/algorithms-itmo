/**
Постройте Z-функцию для заданной строки .
*/

#include "edx-io.hpp"
#include <algorithm>
#include <vector>

std::vector<int> zFunction(std::string& s) {
    std::vector<int> z(s.length(), 0);

    //начальные значения l и r непринципиальны
    for (int i = 1, l = 0, r = 0; i < s.length(); i++) {
        if (i <= r) {                            //если i входит в уже обработанный отрезок
            z[i] = std::min(z[i - l], r - i + 1);     //используем предыдущие вычисления
        }

        //иначе начальным значением z[i] остаётся 0

        //пытаемся увеличить z[i] наивным алгоритмом
        while (i + z[i] < s.length()) {
            if (s[i + z[i]] == s[z[i]]) {
                z[i]++;
            } else {
                break;
            }
        }

        //если мы можем увеличить r, делаем это
        if (z[i] > 0 && i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    return z;
}

int main() {
    std::string s;
    io >> s;
    std::vector<int> zf = zFunction(s);
    for (int i = 1; i < s.size(); i++) {
        io << zf[i] << " ";
    }
    return 0;
}
