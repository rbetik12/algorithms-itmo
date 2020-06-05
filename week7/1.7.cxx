//
// Created by thomasf on 16.03.2020.
//

#include <vector>
#include <fstream>

struct TreeNode {
    int32_t value = 0;
    uint32_t l_number = 0;
    uint32_t r_number = 0;
    uint32_t unter_size = 0;
};

using DasTree = std::vector<TreeNode>;

uint32_t get_tree_height(DasTree &tree, uint32_t initial = 0) {
    uint32_t lv = 0, rv = 0;
    if (tree[initial].unter_size)
        return tree[initial].unter_size;

    if (tree[initial].l_number)
        lv = get_tree_height(tree, tree[initial].l_number - 1);
    if (tree[initial].r_number)
        rv = get_tree_height(tree, tree[initial].r_number - 1);

    tree[initial].unter_size = std::max(lv, rv) + 1;
    return tree[initial].unter_size;
}

int32_t get_tree_balance(const DasTree &tree, uint32_t initial = 0) {
    uint32_t lv = 0, rv = 0;

    if (tree[initial].l_number)
        lv = tree[tree[initial].l_number - 1].unter_size;
    if (tree[initial].r_number)
        rv = tree[tree[initial].r_number - 1].unter_size;

    return rv - lv;
}

void fill_sizes(DasTree &tree) {
    for (uint32_t i = tree.size() - 1; i > 0; i--)
        tree[i].unter_size = get_tree_height(tree, i);
}

int main() {
    DasTree das_tree;
    uint32_t n;

    {
        std::ifstream inp("input.txt");
        inp >> n;
        das_tree.reserve(n);
        for (uint32_t i = 0; i < n; i++) {
            TreeNode buffer = {};
            inp >> buffer.value >> buffer.l_number >> buffer.r_number;
            das_tree.push_back(buffer);
        }
    }

    fill_sizes(das_tree);

    {
        std::ofstream outp("output.txt");
        for (uint32_t i = 0; i < n; i++)
            outp << get_tree_balance(das_tree, i) << "\n";
    }

    return 0;
}