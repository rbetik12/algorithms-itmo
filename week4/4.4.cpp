/**
Реализуйте работу очереди. В дополнение к стандартным операциям очереди, необходимо также отвечать на запрос
 о минимальном элементе из тех, которые сейчас находится в очереди. Для каждой операции запроса минимального элемента
 выведите ее результат.

На вход программе подаются строки, содержащие команды. Каждая строка содержит одну команду. Команда — это либо «+ »,
 либо «−», либо «?». Команда «+ » означает добавление в очередь числа , по модулю не превышающего . Команда «−» означает
 изъятие элемента из очереди.
 Команда «?» означает запрос на поиск минимального элемента в очереди.
*/
#include <deque>
#include <algorithm>
#include <climits>
#include "edx-io.hpp"
#include <stack>

class Stack {
private:
    class Element {
    public:
        int number;
        int opResult;

        Element(int el, int opRes) {
            number = el;
            opResult = opRes;
        }
    };

    std::stack<Element> stack;
public:
    void push(int el) {
        if (!stack.empty()) {
            stack.push(Element(el, std::min(el, stack.top().opResult)));
        } else {
            stack.push(Element(el, el));
        }
    }

    int pop() {
        int num = stack.top().number;
        stack.pop();
        return num;
    }

    int getMin() {
        if (stack.empty()) {
            return INT_MAX;
        } else {
            return stack.top().opResult;
        }
    }

    bool empty() {
        return stack.empty();
    }
};

class Queue {
private:
    Stack s1;
    Stack s2;
public:
    void push(int el) {
        s1.push(el);
    }
    int pop() {
        if (s2.empty()) {
            while(!s1.empty()) {
                s2.push(s1.pop());
            }
        }
        return s2.pop();
    }

    int getMin() {
        return std::min(s1.getMin(), s2.getMin());
    }
};

int main() {
    int n = 0;
    io >> n;
    Queue deque;
    char sign;
    int num;
    for (int i = 0; i < n; i++) {
        io >> sign;
        if (sign == '+') {
            io >> num;
            deque.push(num);
        } else if (sign == '-') {
            deque.pop();
        } else if (sign == '?') {
            io << deque.getMin() << '\n';
        }
    }
}


