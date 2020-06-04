//
// Created by thomasf on 11.03.2020.
//

#include <fstream>
#include <set>
#include <vector>

int main() {
    uint32_t n;
    std::multiset<int32_t> target;
    std::vector<int32_t> history;

    std::ifstream inp("input.txt");
    std::ofstream outp("output.txt");
    inp >> n;

    history.reserve(n);

    for (uint32_t i = 0; i < n; i++) {
        char cmd = 0;
        int32_t value = 0;

        inp >> cmd;
        if (cmd == 'A') {
            inp >> value;
            target.insert(value);
        } else if (cmd == 'X') {
            if (target.empty())
                outp << "*\n";
            else {
                outp << *target.begin() << "\n";
                target.erase(target.begin());
            }
        } else if (cmd == 'D') {
            int32_t ind;
            inp >> ind;
            auto buf = history[ind - 1];
            target.erase(target.find(buf));
            inp >> value;
            target.insert(value);
            history[ind - 1] = value;
        }

        history.push_back(value);
    }

    return 0;

}
