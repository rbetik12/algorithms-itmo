/**
Дано двоичное дерево поиска. В вершинах этого дерева записаны ключи — целые числа, по модулю не превышающие .
 Для каждой вершины дерева  выполняется следующее условие:

все ключи вершин из левого поддерева меньше ключа вершины ;
все ключи вершин из правого поддерева больше ключа вершины .
Найдите высоту данного дерева.
*/

#include <iostream>
#include "edx-io.hpp"

#define LEFT_CHILD 1
#define RIGHT_CHILD 2
#define debugPrint(x) std::cout << x << std::endl;

void print(int **, int);

int countHeight(int **, int, int);

int countLeftSubtree(int **, int, int);

int countRightSubtree(int **, int, int);

int main() {
    int n;
    io >> n;
    if (n == 0) {
        io << 0;
        return 0;
    }
    int **tree;
    tree = new int *[n];
    for (int i = 0; i < n; i++) {
        tree[i] = new int[3];
        for (int j = 0; j < 3; j++) {
            io >> tree[i][j];
            if (j != 0)
                tree[i][j] -= 1;
        }
    }

//    print(tree, n);
//    debugPrint(countHeight(tree, 0, 0));
    io << countHeight(tree, 0, 0);
    for (int i = 0; i < n; i++) {
        delete [] tree[i];
    }
    delete [] tree;
    return 0;
}

void print(int **tree, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << tree[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int countHeight(int **tree, int node, int height) {
    int leftSubtreeHeight = countLeftSubtree(tree, node, height);
    int rightSubtreeHeight = countRightSubtree(tree, node, height);
    return leftSubtreeHeight > rightSubtreeHeight ? leftSubtreeHeight : rightSubtreeHeight;
}

int countLeftSubtree(int **tree, int node, int height) {
    height += 1;
    if (tree[node][LEFT_CHILD] == -1) {
        return height;
    } else {
        return countHeight(tree, tree[node][LEFT_CHILD], height);
    }
}

int countRightSubtree(int **tree, int node, int height) {
    height += 1;
    if (tree[node][RIGHT_CHILD] == -1) {
        return height;
    } else {
        return countHeight(tree, tree[node][RIGHT_CHILD], height);
    }
}