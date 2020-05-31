/**
Последовательность , состоящую из символов из множества «(», «)», «[» и «]», назовем правильной скобочной
 последовательностью, если выполняется одно из следующих утверждений:

 — пустая последовательность;
первый символ последовательности  — это «(», и в этой последовательности существует такой символ «)»,
 что последовательность можно представить как , где  и  — правильные скобочные последовательности;
первый символ последовательности  — это «[», и в этой последовательности существует такой символ «]»,
 что последовательность можно представить как , где  и  — правильные скобочные последовательности.
Так, например, последовательности «(())» и «()[]» являются правильными скобочными последовательностями,
а последовательности «[)» и «((» таковыми не являются.

Входной файл содержит несколько строк, каждая из которых содержит последовательность символов «(», «)», «[» и «]».
 Для каждой из этих строк выясните, является ли она правильной скобочной последовательностью.
*/

#include <stack>
#include "edx-io.hpp"

void clearStack(std::stack<char> &stack) {
    while (!stack.empty()) {
        stack.pop();
    }
}

bool checkOnStack(std::stack<char> &stack, char strEl) {
    if (stack.empty()) return false;
    char okBracket;

    if (strEl == ')') {
        okBracket = '(';
    } else {
        okBracket = '[';
    }

    bool correct = false;
    if (stack.top() == okBracket) {
        correct = true;
    }
    stack.pop();
    return correct;
}

int main() {
    int n;
    io >> n;
    std::string sequence;
    std::stack<char> stack;
    bool correct;
    for (int i = 0; i < n; i++) {
        io >> sequence;
        correct = true;
        for (int j = 0; j < sequence.size(); j++) {
            if (sequence[j] == '(' || sequence[j] == '[') {
                stack.push(sequence[j]);
            } else {
                correct = checkOnStack(stack, sequence[j]);
                if (!correct) {
                    break;
                }
            }
        }
        if (!stack.empty()) {
            correct = false;
        }
        clearStack(stack);
        if (correct) {
            io << "YES" << '\n';
        } else {
            io << "NO" << '\n';
        }
    }
    return 0;
}