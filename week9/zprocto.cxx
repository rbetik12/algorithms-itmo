#include <fstream>
#include <vector>


void prefix_function(std::string const & text, std::vector<int> & prefix)
{
    prefix.push_back(0);

    for (size_t i = 1; i < text.size(); ++i)
    {
        int border = prefix[i - 1];

        while (border > 0 && text[i] != text[border])
        {
            border = prefix[border - 1];
        }

        prefix.push_back(border + (text[border] == text[i] ? 1 : 0));
    }
}


void kmp(std::string const & text, std::string const & pattern, std::vector<int64_t> & pos)
{
    std::vector<int> prefix;
    std::string super_string;

    super_string = pattern + '$' + text;

    prefix_function(super_string, prefix);

    for (int i = 0; i < static_cast<int>(text.length() - pattern.length() + 1); ++i)
    {
        if (prefix[i + 2*pattern.size()] == pattern.size())
        {
            pos.push_back(i + 1);
        }
    }
}


int main()
{
    std::ifstream inp_file("input.txt");
    std::ofstream out_file("output.txt");

    std::string text, pattern;
    inp_file >> pattern >> text;

    std::vector<int64_t> pattern_positions;
    kmp(text, pattern, pattern_positions);

    out_file << pattern_positions.size() << std::endl;
    for (auto x : pattern_positions)
    {
        out_file << x << ' ';
    }

    return 0;
}