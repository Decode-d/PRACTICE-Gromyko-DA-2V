#include "doubly_linked_list.h" // Для прямой демонстрации DoublyLinkedList
#include "stack.h"              // Для Stack и IContainer usage
                                // IContainer.h подключается через stack.h

#include <iostream>             // Для std::cout, std::endl
#include <string>               // Для std::string (формулы, элементы списка)
// <vector> и <utility> (для std::move) не используются согласно строгой интерпретации запрета STL

// --- Объявления функций для main.cpp ---
void print_task_step(int task_num, const std::string& description);
bool areBracketsBalanced(const std::string& formula); // Использует Stack<char>

// --- Определения функций ---

void print_task_step(int task_num, const std::string& description) {
    std::cout << "\n// --- Задание " << task_num << ": " << description << " --- //\n";
}

// Определение areBracketsBalanced с использованием пользовательского Stack
// и исправленным стилем (ОДНА СТРОКА = ОДНО ВЫРАЖЕНИЕ)
bool areBracketsBalanced(const std::string& formula) {
    Stack<char> s; // ИСПОЛЬЗУЕМ СВОЙ Stack<char> (ответ на Замечание 1)
    for (char ch : formula) { 
        if (ch == '(' || ch == '{' || ch == '[' || ch == '<') {
            s.addElement(ch);
        } else if (ch == ')') {
            if (s.isEmpty()) {          // Стиль исправлен (ответ на Замечание 3)
                return false; 
            }
            char topChar = s.removeElement(); 
            if (topChar != '(') {       // Стиль исправлен (ответ на Замечание 3)
                return false; 
            }
        } else if (ch == '}') {
            if (s.isEmpty()) { 
                return false; 
            }
            char topChar = s.removeElement();
            if (topChar != '{') { 
                return false; 
            }
        } else if (ch == ']') {
            if (s.isEmpty()) { 
                return false; 
            }
            char topChar = s.removeElement();
            if (topChar != '[') { 
                return false; 
            }
        } else if (ch == '>') {
            if (s.isEmpty()) { 
                return false; 
            }
            char topChar = s.removeElement();
            if (topChar != '<') { 
                return false; 
            }
        }
        // Другие символы игнорируются
    }
    return s.isEmpty(); // В конце стек должен быть пуст
}

int main() {
    // Блок 1: Демонстрация пользовательских структур данных (ответ на Замечание 2 - это не тесты, а демонстрация)
    print_task_step(1, "Демонстрация DoublyLinkedList и Custom Stack");
    
    std::cout << "\n// --- Демонстрация DoublyLinkedList --- //\n";
    DoublyLinkedList<int> myList;
    myList.push_back(10);
    myList.push_back(20);
    myList.push_front(5);
    myList.print(); 

    std::cout << "Извлечено из начала: " << myList.pop_front() << std::endl; 
    myList.print(); 
    std::cout << "Извлечено с конца: " << myList.pop_back() << std::endl; 
    myList.print(); 
    std::cout << "Список пуст? " << (myList.isEmpty() ? "Да" : "Нет") << std::endl; 
    std::cout << "Извлечено с конца: " << myList.pop_back() << std::endl; 
    std::cout << "Список пуст после последнего извлечения? " << (myList.isEmpty() ? "Да" : "Нет") << std::endl; 

    DoublyLinkedList<std::string> list1_str; // Изменено имя, чтобы не конфликтовать с list1 из скриншота
    list1_str.push_back("альфа");
    list1_str.push_back("бета");
    std::cout << "List1_str: "; list1_str.print();

    DoublyLinkedList<std::string> list2_str = list1_str; 
    std::cout << "List2_str (скопирован из list1_str): "; list2_str.print(); 
    
    DoublyLinkedList<std::string> list3_str;
    list3_str.push_back("дельта");
    std::cout << "List3_str (до присваивания): "; list3_str.print();
    list3_str = list1_str; 
    std::cout << "List3_str (присвоен из list1_str): "; list3_str.print(); 

    std::cout << "\n// --- Демонстрация Custom Stack (через IContainer) --- //\n";
    IContainer<std::string>* container = new Stack<std::string>(); // Используем свой Stack
    container->addElement("Привет");
    container->addElement("Мир");
    std::cout << "Контейнер (Стек) пуст? " << (container->isEmpty() ? "Да" : "Нет") << std::endl; 
    std::cout << "Удалено из контейнера: " << container->removeElement() << std::endl; 
    std::cout << "Удалено из контейнера: " << container->removeElement() << std::endl; 
    std::cout << "Контейнер (Стек) пуст после удалений? " << (container->isEmpty() ? "Да" : "Нет") << std::endl;
    delete container;

    // Блок 2: РЕШЕНИЕ ПОСТАВЛЕННОЙ ЗАДАЧИ (ответ на Замечание 2)
    print_task_step(2, "Задача: Проверка корректности расстановки скобок"); 
    std::cout << "Для решения этой задачи используется собственная реализация стека (Stack<char>)." << std::endl;
    
    const int NUM_FORMULAS = 13; 
    std::string formulas_to_test[NUM_FORMULAS] = {
        "({<[]>})", "([)]", "{()", "())({}{()})", "{<O{}>}",
        "()({<O{}>})", "()({(O{})})", "()({(O{)} })", "([{}])", 
        "", ")", "(", "abc(def{valid}ghi)"
    };

    std::cout << "\nПримеры работы решения для различных формул:" << std::endl;
    for (int i = 0; i < NUM_FORMULAS; ++i) {
        const std::string& f = formulas_to_test[i];
        std::cout << "Формула: \"" << (f.empty() ? "<пустая строка>" : f) << "\" - Корректно: "
                  << (areBracketsBalanced(f) ? "Да" : "Нет") << std::endl;
    }

    std::cout << "\n// --- Обоснование выбора структуры данных для задачи --- //\n";
    std::cout << "Для решения задачи проверки скобок был использован собственный класс Stack, "
              << "определенный в 'stack.h' и использующий 'doubly_linked_list.h' для внутреннего хранения." << std::endl;
    std::cout << "Стек идеально подходит для этой задачи благодаря своей LIFO (Last-In, First-Out) природе:" << std::endl;
    std::cout << "   - При обнаружении открывающей скобки она помещается в стек." << std::endl;
    std::cout << "   - При обнаружении закрывающей скобки, она сравнивается с той, что на вершине стека." << std::endl;
    std::cout << "   - Если они образуют пару, скобка с вершины стека удаляется. В противном случае - ошибка." << std::endl;
    std::cout << "   - В конце проверки стек должен быть пуст для корректной последовательности." << std::endl;
    std::cout << "Использование собственной реализации Stack соответствует требованию использовать разработанные структуры данных в задании." << std::endl;

    return 0;
}