#ifndef STACK_H
#define STACK_H

#include "icontainer.h"          // Для интерфейса IContainer
#include "doubly_linked_list.h" // Для внутренней реализации списка
#include <stdexcept>            // Для std::logic_error
#include <cstddef>              // Для size_t (используется list.getSize())

template <typename T>
class Stack : public IContainer<T> {
private:
    DoublyLinkedList<T> list; 

public:
    Stack() = default;

    // Реализация интерфейса IContainer
    void addElement(const T& value) override {
        list.push_back(value); 
    }

    T removeElement() override { 
        if (list.isEmpty()) {
            throw std::logic_error("Stack: Невозможно выполнить removeElement (pop) из пустого стека.");
        }
        return list.pop_back();
    }

    bool isEmpty() const noexcept override { 
        return list.isEmpty();
    }

    // Специфичные для стека методы
    const T& top() const { 
        if (list.isEmpty()) {
            throw std::logic_error("Stack: Невозможно получить top из пустого стека.");
        }
        return list.back(); 
    }

    T& top() { 
        if (list.isEmpty()) {
            throw std::logic_error("Stack: Невозможно получить top из пустого стека.");
        }
        return list.back();
    }

    size_t getSize() const noexcept { 
        return list.getSize();
    }
};

#endif // STACK_H