/**
Дано некоторое двоичное дерево поиска. Также даны запросы на удаление из него вершин, имеющих заданные ключи,
 причем вершины удаляются целиком вместе со своими поддеревьями.

После каждого запроса на удаление выведите число оставшихся вершин в дереве.
*/

#include "edx-io.hpp"

unsigned countCildrenAndPlaceParent(int**, int, int);
unsigned findValue(int**, int, int);
void wipeSubtree(int**, int);
void decreaseNumberOfChildren(int**, int, int);

int main(){
    int length;
    int wipes;
    int numberOfNodes;

    io >> length;
    numberOfNodes = length;

    int **tree = new int* [length + 1];

    for (int i = 1; i <= length; i++){
        tree[i] = new int[3];
        io >> tree[i][0] >> tree[i][1] >> tree[i][2];
        tree[i][3] = 0;
        tree[i][4] = 0;
    }

    countCildrenAndPlaceParent(tree, 1, 0);

    io >> wipes;

    for (int i = 0; i < wipes; i++){
        int index = 1;
        int key;
        io >> key;

        index = findValue(tree, key, 1);

        if (index != 0){
            decreaseNumberOfChildren(tree, index, tree[index][4]);
            wipeSubtree(tree, index);
        }
        io << tree[1][4] << '\n';
    }
}


unsigned countCildrenAndPlaceParent(int** tree, int index, int parent){
    unsigned numberOfChildren = 1;
    int leftChild = tree[index][1];
    int rightChild = tree[index][2];

    tree[index][3] = parent;

    if (leftChild > 0){
        numberOfChildren += countCildrenAndPlaceParent(tree, leftChild, index);
    }
    if (rightChild > 0){
        numberOfChildren += countCildrenAndPlaceParent(tree, rightChild, index);
    }

    tree[index][4] = numberOfChildren;
    return numberOfChildren;
}

unsigned findValue(int** tree, int value, int index){
    int indexValue = tree[index][0];
    if (indexValue == value){
        return index;
    } else if (indexValue > value){
        if (tree[index][1] == 0){
            return 0;
        }
        return findValue(tree, value, tree[index][1]);

    } else {
        if (tree[index][2] == 0){
            return 0;
        }
        return findValue(tree, value, tree[index][2]);
    }
}

void wipeSubtree(int** tree, int index){
    int left = tree[index][1];
    int right = tree[index][2];
    tree[index][3] = 0;
    if (left != 0){
        wipeSubtree(tree, left);
    }
    if (right != 0){
        wipeSubtree(tree, right);
    }
}

void decreaseNumberOfChildren(int** tree, int index, int number){
    tree[index][4] -= number;
    int parent = tree[index][3];
    if (parent != 0){
        decreaseNumberOfChildren(tree, parent, number);
    }
}
