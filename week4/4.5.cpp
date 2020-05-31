/**
Язык Quack — забавный язык, который фигурирует в одной из задач с Internet Problem Solving Contest. В этой задаче вам
 требуется написать интерпретатор языка Quack.

Виртуальная машина, на которой исполняется программа на языке Quack, имеет внутри себя очередь, содержащую целые числа
 по модулю 65536 (то есть, числа от 0 до 65535, соответствующие беззнаковому 16-битному целому типу). Слово get в описании
 операций означает извлечение из очереди, put — добавление в очередь. Кроме того, у виртуальной машины есть 26 регистров,
 которые обозначаются буквами от 'a' до 'z'. Изначально все регистры хранят нулевое значение. В языке Quack существуют
 следующие команды (далее под  и  подразумеваются некие абстрактные временные переменные):
*/

#include <queue>
#include <iostream>
#include "edx-io.hpp"
#include <cstdlib>
#include <vector>
#include <map>

#define MODULE 65536
#define memory_index_convert 97

int memory_index(char reg) {
    return reg - memory_index_convert;
}

void add_to_queue(std::queue<unsigned short int> &queue, unsigned short int memory[], char &reg) {
    queue.push(memory[memory_index(reg)]);
}

void add_to_memory(std::queue<unsigned short int> &queue, unsigned short int memory[], char &reg) {
    memory[memory_index(reg)] = queue.front();
    queue.pop();
}

void crprint(unsigned short int memory[], char &reg) {
    io << (char) (memory[memory_index(reg)] % 256);
}

void cqprint(std::queue<unsigned short int> &queue) {
    unsigned short int num = queue.front();
    queue.pop();
    io << (char) (num % 256);
}

void rprint(unsigned short int memory[], char &reg) {
    io << memory[memory_index(reg)] << '\n';
}

void qprint(std::queue<unsigned short int> &queue) {
    unsigned short int num = queue.front();
    queue.pop();
    io << num << '\n';
}

void print(std::queue<unsigned short int> queue) {
    std::cout << "Queue: " << std::endl;
    while (!queue.empty()) {
        std::cout << queue.front() << " ";
        queue.pop();
    }
    std::cout << std::endl;
}

void print(unsigned short int memory[]) {
    std::cout << "Memory: " << std::endl;
    for (int i = 0; i < 26; i++) {
        std::cout << (char) (i + memory_index_convert) << ": " << memory[i] << " ";
    }
    std::cout << std::endl;
}

void arithmop(std::queue<unsigned short int> &queue, char &op) {
    unsigned short int a = queue.front();
    queue.pop();
    unsigned short int b = queue.front();
    queue.pop();
    switch (op) {
        case '+':
            queue.push((a + b) % MODULE);
            break;
        case '-':
            queue.push((a - b) % MODULE);
            break;
        case '*':
            queue.push((a * b) % MODULE);
            break;
        case '/':
            if (b == 0) {
                queue.push(0);
            } else {
                queue.push(std::div(a, b).quot);
            }
            break;
        case '%':
            if (b == 0) {
                queue.push(0);
            } else {
                queue.push(std::div(a, b).rem);
            }
            break;
    }
}

int is_numeric(std::string &string) {
    int num;
    try {
        num = std::stoi(string);
    }
    catch (std::invalid_argument &e) {
        return -1;
    }
    return num;
}

bool is_arithmop(std::string &op) {
    return op == "+" || op == "-" || op == "*" || op == "/" || op == "%";
}

void init_memory(unsigned short int memory[]) {
    for (int i = 0; i < 26; i++) {
        memory[i] = 0;
    }
}

char get_register(std::string &str) {
    return str[1];
}

std::string get_label(std::string &str, bool clean) {
    if (clean) {
        return str;
    }
    return str.substr(1, std::string::npos);
}

void exec(std::queue<unsigned short int> &queue, unsigned short int memory[], std::vector<std::string> &program,
          std::map<std::string, int> &labels) {
    for (int i = 0; i < program.size(); i++) {
        if (program[i][0] == 'Q') {
            break;
        }

        int num = is_numeric(program[i]);

        if (num != -1) {
            queue.push(num);
//            print(queue);
        } else {
            if (is_arithmop(program[i])) {
                arithmop(queue, program[i][0]);
//                print(queue);
            } else if (program[i][0] == '>') {
                char reg = program[i][1];
                add_to_memory(queue, memory, reg);
//                print(memory);
            } else if (program[i][0] == '<') {
                char reg = program[i][1];
                add_to_queue(queue, memory, reg);
//                print(queue);
            } else if (program[i][0] == 'P') {
                if (program[i].length() == 2) {
                    rprint(memory, program[i][1]);
                } else {
                    qprint(queue);
                }
            } else if (program[i][0] == 'C') {
                if (program[i].length() == 2) {
                    crprint(memory, program[i][1]);
                } else {
                    cqprint(queue);
                }
            } else if (program[i][0] == 'J') {
                std::string label = get_label(program[i], false);
//                std::cout << labels.find(label)->second << std::endl;
                i = labels.find(label)->second;
            } else if (program[i][0] == 'Z') {
                char reg = program[i][1];
                if (memory[memory_index(reg)] == 0) {
                    std::string label = program[i].substr(2, std::string::npos);
                    i = labels.find(label)->second;
                }
            } else if (program[i][0] == 'E') {
                char reg1 = program[i][1];
                char reg2 = program[i][2];
                if (memory[memory_index(reg1)] == memory[memory_index(reg2)]) {
                    std::string label = program[i].substr(3, std::string::npos);
                    i = labels.find(label)->second;
                }
            } else if (program[i][0] == 'G') {
                char reg1 = program[i][1];
                char reg2 = program[i][2];
//                print(memory);
//                std::cout << memory[memory_index(reg1)] << " " << memory[memory_index(reg2)] << std::endl;
//                std::cout << (memory[memory_index(reg1)] > memory[memory_index(reg2)]) << std::endl;
                if (memory[memory_index(reg1)] > memory[memory_index(reg2)]) {
                    std::string label = program[i].substr(3, std::string::npos);
                    i = labels.find(label)->second;
                }
            }
        }
    }
}

int main() {
    std::queue<unsigned short int> queue;
    std::string input;
    unsigned short int memory[26];
    init_memory(memory);
    std::vector<std::string> program;
    std::map<std::string, int> labels;
    int count = 0;
    while (true) {
        io >> input;
        if (input.empty()) {
            break;
        }
        if (input[0] == ':') {
            labels.insert(make_pair(input.substr(1, std::string::npos), count));
        }
        program.push_back(input);
        count++;
    }
    exec(queue, memory, program, labels);
//    for (auto el: labels) {
//        std::cout << el.first << " " << el.second << std::endl;
//    }
    return 0;
}
