#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <cstddef>   // Для size_t
#include <stdexcept> // Для std::out_of_range
#include <iostream>  // Для std::cout в методе print()
                     // (и std::endl)

// Примечание: Если T - это std::string, пользователь DoublyLinkedList<std::string>
// должен подключить <string> для определения std::string.

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(const T& val, Node* p = nullptr, Node* n = nullptr)
            : data(val), prev(p), next(n) {}
    };

    Node* head;
    Node* tail;
    size_t count;

    void clear_nodes() {
        Node* current = head;
        while (current != nullptr) {
            Node* next_node = current->next;
            delete current;
            current = next_node;
        }
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

    ~DoublyLinkedList() {
        clear_nodes();
    }

    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), count(0) {
        Node* current_other = other.head;
        while (current_other != nullptr) {
            push_back(current_other->data);
            current_other = current_other->next;
        }
    }

    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this == &other) {
            return *this;
        }
        
        clear_nodes();
        Node* current_other = other.head;
        while (current_other != nullptr) {
            push_back(current_other->data); 
            current_other = current_other->next;
        }
        return *this;
    }

    DoublyLinkedList(DoublyLinkedList&& other) noexcept
        : head(other.head), tail(other.tail), count(other.count) {
        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;
    }

    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        clear_nodes(); 

        head = other.head;
        tail = other.tail;
        count = other.count;

        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;
        return *this;
    }

    void push_back(const T& value) {
        Node* new_node = new Node(value);
        if (isEmpty()) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        count++;
    }

    void push_front(const T& value) {
        Node* new_node = new Node(value);
        if (isEmpty()) {
            head = tail = new_node;
        } else {
            head->prev = new_node;
            new_node->next = head;
            head = new_node;
        }
        count++;
    }

    T pop_back() {
        if (isEmpty()) {
            throw std::out_of_range("DoublyLinkedList: Невозможно выполнить pop_back из пустого списка.");
        }
        Node* node_to_delete = tail;
        T value = node_to_delete->data;

        if (head == tail) { 
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete node_to_delete;
        count--;
        return value;
    }

    T pop_front() {
        if (isEmpty()) {
            throw std::out_of_range("DoublyLinkedList: Невозможно выполнить pop_front из пустого списка.");
        }
        Node* node_to_delete = head;
        T value = node_to_delete->data;

        if (head == tail) { 
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete node_to_delete;
        count--;
        return value;
    }

    const T& front() const {
        if (isEmpty()) {
            throw std::out_of_range("DoublyLinkedList: Невозможно получить front из пустого списка.");
        }
        return head->data;
    }
    T& front() {
        if (isEmpty()) {
            throw std::out_of_range("DoublyLinkedList: Невозможно получить front из пустого списка.");
        }
        return head->data;
    }

    const T& back() const {
        if (isEmpty()) {
            throw std::out_of_range("DoublyLinkedList: Невозможно получить back из пустого списка.");
        }
        return tail->data;
    }
    T& back() {
        if (isEmpty()) {
            throw std::out_of_range("DoublyLinkedList: Невозможно получить back из пустого списка.");
        }
        return tail->data;
    }

    bool isEmpty() const noexcept { 
        return count == 0;
    }

    size_t getSize() const noexcept { 
        return count;
    }

    void print() const {
        Node* current = head;
        std::cout << "Список (размер " << getSize() << "): ";
        if (isEmpty()) {
            std::cout << "пусто";
        }
        while (current != nullptr) {
            std::cout << current->data; // Полагается на то, что для T определен operator<<
            if (current->next != nullptr) {
                 std::cout << " <-> ";
            }
            current = current->next;
        }
        std::cout << std::endl;
    }
};

#endif // DOUBLY_LINKED_LIST_H