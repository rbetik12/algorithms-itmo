/**
Реализуйте работу очереди. Для каждой операции изъятия элемента выведите ее результат.

На вход программе подаются строки, содержащие команды. Каждая строка содержит одну команду. Команда — это либо «+ »,
 либо «−». Команда «+ » означает добавление в очередь числа , по модулю не превышающего .
 Команда «−» означает изъятие элемента из очереди. Гарантируется, что размер очереди в процессе выполнения команд не превысит  элементов.
*/

#include <queue>
#include <fstream>

int main() {
    std::ifstream input("input.txt");
    int n = 0;
    input >> n;
    std::queue<int> stack;
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
            output << stack.front() << std::endl;
            stack.pop();
        }
    }
    output.close();
    input.close();
}
