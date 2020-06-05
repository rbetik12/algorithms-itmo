//
// Created by thomasf on 10.04.2020.
//

#include <fstream>
#include <string>
#include <vector>
#include <cstdint>


inline bool check_if_r_matches(const std::string &pattern, const std::string &target, uint32_t pos) {
    if (target.size() < pos + pattern.size() || pattern[pattern.size() - 1] != target[pos + pattern.size() - 1])
        return false;

    for (uint32_t x = 1; x < pattern.size() - 1; x++) {
        if (pattern[x] != target[pos + x])
            return false;
    }
    return true;
}

int main() {
    std::string eins, zwei;
    {
        std::ifstream inp("input.txt");
        inp >> eins >> zwei;
    }

    std::vector<uint32_t> positions;
    positions.reserve(zwei.size());
    for (uint32_t i = 0; i < zwei.size(); i++) {
        if (zwei[i] == eins[0] && check_if_r_matches(eins, zwei, i))
            positions.push_back(i);
    }

    {
        std::ofstream outp("output.txt");
        outp << positions.size() << "\n";
        for (auto x : positions)
            outp << x + 1 << " ";
    }

    return 0;
}
