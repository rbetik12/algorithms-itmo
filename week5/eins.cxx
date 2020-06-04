#include <fstream>
#include <vector>


int main() {
    uint32_t n;
    std::vector<int32_t> target;
    {
        std::ifstream inp("input.txt");
        inp >> n;
        target.resize(n, 0);
        for (uint32_t i = 0; i < n; i++)
            inp >> target[i];
    }

    std::string answer = "YES";

    for (uint32_t i = 1; i <= n / 2 + 1; i++) {
        if (2 * i <= n) {
            if (target[i - 1] > target[(2 * i) - 1]) {
                answer = "NO";
                break;
            }
        }
        if (2 * i + 1 <= n) {
            if (target[i - 1] > target[2 * i]) {
                answer = "NO";
                break;
            }
        }
    }


    {
        std::ofstream outp("output.txt");
        outp << answer;
    }

    return 0;

}
