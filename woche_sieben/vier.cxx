//
// Created by thomasf on 17.03.2020.
//

#include <fstream>
#include <vector>
#include <queue>
#include <iostream>

enum Side {right=0, left=1};

struct Input_Node
{
    int key;
    int children[2];

    Input_Node(int key, int left, int right) : key(key)
    {
        children[0] = left;
        children[1] = right;
    }
};

struct Node
{
    int key;
    int height;
    int inp_num;
    Node* children[2];

    Node(int key, Node * left, Node * right, int num) : key(key), height(1), inp_num(num)
    {
        children[0] = left;
        children[1] = right;
    }

    Node(Input_Node * node, int num) : height(1), key(node->key), inp_num(num)
    {
        children[0] = children[1] = nullptr;
    }
};

struct AVL_Tree
{
    std::vector<Input_Node *> input_tree;
    std::vector<Input_Node *> output_tree;
    Node * root = nullptr;

    void make_tree()
    {
        root = new Node(input_tree[0], 0);
        dfs_make(root);
    }

    void dfs_make(Node * v)
    {
        for (int i = 0; i < 2; i++)
        {
            if (input_tree[v->inp_num]->children[i] == -1)
            {
                v->children[i] = nullptr;
            }
            else
            {
                v->children[i] =
                        new Node(input_tree[input_tree[v->inp_num]->children[i]], input_tree[v->inp_num]->children[i]);
                dfs_make(v->children[i]);
            }
        }
    }

    int count_balance(Node * v)
    {
        return (v->children[1] != nullptr ? v->children[1]->height : 0) -
               (v->children[0] != nullptr ? v->children[0]->height : 0);
    }

    void count_height()
    {
        if (input_tree.empty())
        {
            return ;
        }

        dfs(root);
    }

    void fix_height(Node * v)
    {
        v->height = std::max(height_left(v), height_right(v)) + 1;
    }

    int height_right(Node * v)
    {
        return v->children[1] == nullptr ? 0 : v->children[1]->height;
    }

    int height_left(Node * v)
    {
        return v->children[0] == nullptr ? 0 : v->children[0]->height;
    }

    void dfs(Node * v)
    {
        for (auto child : v->children)
        {
            if (child != nullptr)
            {
                dfs(child);
            }
        }
        fix_height(v);
    }

    Node * rotate(Node * v, int side)
    {
        Node * u = v->children[side == Side::left ? 1 : 0];
        v->children[side == Side::left ? 1 : 0] = u->children[side == Side::left ? 0 : 1];
        u->children[side == Side::left ? 0 : 1] = v;
        fix_height(v);
        fix_height(u);
        return u;
    }

    Node * balance(Node * v)
    {
        fix_height(v);
        if (count_balance(v) > 1)
        {

            if (count_balance(v->children[1]) < 0)
            {
                v->children[1] = rotate(v->children[1], Side::right);
            }
            return rotate(v, Side::left);
        }
        if (count_balance(v) < -1)
        {
            if (count_balance(v->children[0]) > 0)
            {
                v->children[0] = rotate(v->children[0], Side::left);
            }
            return rotate(v, Side::right);
        }
        return v;
    }

    void make_output_tree()
    {
        std::queue<Node *> queue;
        queue.push(root);
        int num = 1;
        while (!queue.empty())
        {
            Node * v = queue.front();
            queue.pop();
            int children_num[2] = {0, 0};
            for (int i = 0; i < 2; i++)
            {
                if (v->children[i] != nullptr)
                {
                    queue.push(v->children[i]);
                    children_num[i] = ++num;
                }
            }
            output_tree.push_back(new Input_Node(v->key, children_num[0], children_num[1]));
        }
    }

    Node * insert(Node * root, int key)
    {
        if (root == nullptr)
        {
            return new Node(key, nullptr, nullptr, static_cast<int>(input_tree.size()+1));
        }
        root->children[key < root->key ? 0 : 1] = insert(root->children[key < root->key ? 0 : 1], key);
        return balance(root);
    }

    Node * find_max(Node * root)
    {
        return root->children[1] == nullptr ? root : find_max(root->children[1]);
    }

    Node * remove(Node * root, int key)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        if (key != root->key)
        {
            root->children[key < root->key ? 0 : 1] = remove(root->children[key < root->key ? 0 : 1], key);
        }
        else
        {
            if (root->children[0] == nullptr && root->children[1] == nullptr)
            {
                return nullptr;
            }
            if (root->children[0] == nullptr)
            {
                root = root->children[1];
                return balance(root);
            }
            Node * r = find_max(root->children[0]);
            root->key = r->key;
            root->children[0] = remove(root->children[0],r->key);
        }
        return balance(root);
    }
};

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    size_t n;
    in >> n;
    auto avl = new AVL_Tree();

    for (int i = 0; i < n; i++)
    {
        int key;
        int left, right;
        in >> key >> left >> right;
        avl->input_tree.push_back(new Input_Node(key, left-1, right-1));
    }

    int key;
    in >> key;

    if (n == 1)
    {
        out << 0 << std::endl;
        return 0;
    }

    avl->make_tree();
    avl->count_height();
    avl->root = avl->remove(avl->root, key);
    avl->make_output_tree();

    out << n - 1 << std::endl;
    for (auto v : avl->output_tree)
    {
        out << v->key << " " << v->children[0] << " " << v->children[1] << std::endl;
    }
}