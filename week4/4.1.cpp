/**
Реализуйте работу стека. Для каждой операции изъятия элемента выведите ее результат.

На вход программе подаются строки, содержащие команды. Каждая строка содержит одну команду. Команда — это либо "+ ",
 либо "−". Команда "+ " означает добавление в стек числа , по модулю не превышающего . Команда "−" означает изъятие элемента из стека.
 Гарантируется, что не происходит извлечения из пустого стека.
 Гарантируется, что размер стека в процессе выполнения команд не превысит  элементов.
*/

#include <stack>
#include <fstream>

int main() {
    std::ifstream input("input.txt");
    int n = 0;
    input >> n;
    std::stack<int> stack;
    char sign;
    int num;
    std::ofstream output("output.txt");
    for (int i = 0; i < n; i++) {
        input >> sign;
        if (sign == '+') {
            input >> num;
            stack.push(num);
        }
        else {
            output << stack.top() << std::endl;
            stack.pop();
        }
    }
    output.close();
    input.close();
}
