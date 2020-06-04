//
// Created by thomasf on 16.03.2020.
//

#include <vector>
#include <fstream>

struct node // структура для представления узлов дерева
{
    int key;
    uint32_t height;
    node *left;
    node *right;

    explicit node(int k) {
        key = k;
        left = right = nullptr;
        height = 1;
    }
};

unsigned char height(node *p) {
    return p ? p->height : 0;
}

int bfactor(node *p) {
    return height(p->right) - height(p->left);
}

void fixheight(node *p) {
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

uint32_t fixheight_recursive(node *p) {
    uint32_t hl = 0, hr = 0;
    if (p->left)
        hl = fixheight_recursive(p->left);
    if (p->right)
        hr = fixheight_recursive(p->right);

    p->height = (hl > hr ? hl : hr) + 1;
    return p->height;
}

node *rotateright(node *p) // правый поворот вокруг p
{
    node *q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

node *rotateleft(node *q) // левый поворот вокруг q
{
    node *p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

node *auto_rotate_left(node *p) {
    node * q;
    if (p->right && bfactor(p->right) == -1) {
        p->right = rotateright(p->right);
        q = rotateleft(p);
    } else {
        q = rotateleft(p);
    }
    return q;
}


node *balance(node *p) // балансировка узла p
{
    fixheight(p);
    if (bfactor(p) == 2) {
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (bfactor(p) == -2) {
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не нужна
}


node *insert(node *p, int k) // вставка ключа k в дерево с корнем p
{
    if (!p) return new node(k);
    if (k < p->key)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    return balance(p);
}

node *findmin(node *p) // поиск узла с минимальным ключом в дереве p
{
    return p->left ? findmin(p->left) : p;
}

node *removemin(node *p) // удаление узла с минимальным ключом из дерева p
{
    if (p->left == nullptr)
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

node *remove(node *p, int k) // удаление ключа k из дерева p
{
    if (!p) return nullptr;
    if (k < p->key)
        p->left = remove(p->left, k);
    else if (k > p->key)
        p->right = remove(p->right, k);
    else //  k == p->key
    {
        node *q = p->left;
        node *r = p->right;
        delete p;
        if (!r) return q;
        node *min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

struct TreeNode {
    int32_t value = 0;
    uint32_t l_number = 0;
    uint32_t r_number = 0;
};

using DasTree = std::vector<TreeNode>;


node *create_avl_tree(const DasTree &tree, uint32_t initial = 0) {
    auto proot = new node(tree[initial].value);

    if (tree[initial].l_number)
        proot->left = create_avl_tree(tree, tree[initial].l_number - 1);
    if (tree[initial].r_number)
        proot->right = create_avl_tree(tree, tree[initial].r_number - 1);

    return proot;
}


uint32_t push_to_das_tree(DasTree &tree, node *p_root) {
    tree.push_back({p_root->key, 0, 0});
    auto ind = tree.size();
    if (p_root->right)
        tree[ind - 1].r_number = push_to_das_tree(tree, p_root->right);
    if (p_root->left)
        tree[ind - 1].l_number = push_to_das_tree(tree, p_root->left);

    return ind;
}

void create_das_tree(node *p_root, DasTree &target) {
    push_to_das_tree(target, p_root);
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

    auto avl_tree_root = create_avl_tree(das_tree);
    fixheight_recursive(avl_tree_root);
    avl_tree_root = auto_rotate_left(avl_tree_root);
    DasTree das_rotated;
    das_rotated.reserve(n);
    create_das_tree(avl_tree_root, das_rotated);

    {
        std::ofstream outp("output.txt");
        outp << das_rotated.size() << "\n";
        for (auto x : das_rotated)
            outp << x.value << " " << x.l_number << " " << x.r_number << "\n";
    }

    return 0;
}