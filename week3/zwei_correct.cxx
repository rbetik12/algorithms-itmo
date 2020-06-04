#include <vector>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

int main() {


    int n, m, k;
    vector<string> a;

    {
        ifstream inn("input.txt");
        inn >> n >> m >> k;
        a.reserve(m);
        for (int i = 0; i < m; ++i) {
            std::string buf;
            inn >> buf;
            a.push_back(buf);
        }
    }
    int *pos = new int[n];
    for (int i = 0; i < n; ++i) {
        pos[i] = i;
    }
    for (int i = 0; i < k; ++i) {
        string arr;
        int idx = m - i - 1;
        for (int j = 0; j < n; ++j) {
            arr += a[idx][pos[j]];
        }
        int c[26] = {0};
        //std::memset(&c[0], 0, sizeof(int) * 26);
        for (int q = 0; q < arr.size(); ++q) {
            char b = arr[q];
            c[b - 97]++;
        }
        for (int q = 1; q < 26; ++q) {
            c[q] = c[q] + c[q - 1];
        }
        int *newPos = new int[n];
        for (int q = n - 1; q >= 0; q--) {
            newPos[c[arr[q] - 97] - 1] = pos[q];
            c[arr[q] - 97]--;
        }
        for (int q = 0; q < n; ++q) {
            pos[q] = newPos[q];
        }
        delete[] newPos;
    }

    {
        ofstream out("output.txt");
        for (int i = 0; i < n; ++i) {
            out << pos[i] + 1 << " ";
        }
    }
    delete[] pos;

    return 0;
}