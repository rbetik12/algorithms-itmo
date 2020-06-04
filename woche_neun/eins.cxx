#include <fstream>
#include <string>
#include <vector>


int main() {
    std::string eins, zwei;
    {
        std::ifstream inp("input.txt");
        inp >> eins >> zwei;
    }

    std::vector<size_t> positions;
    size_t pos = zwei.find(eins, 0);
    while (pos != std::string::npos) {
        positions.push_back(pos);
        pos = zwei.find(eins, pos + 1);
    }

    {
        std::ofstream outp("output.txt");
        outp << positions.size() << "\n";
        for (auto x : positions)
            outp << x + 1 << " ";
    }

    return 0;
}
