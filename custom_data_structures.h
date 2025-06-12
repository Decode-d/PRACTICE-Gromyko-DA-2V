#ifndef CUSTOM_DATA_STRUCTURES_H
#define CUSTOM_DATA_STRUCTURES_H

#include <iostream>     // Для DoublyLinkedList::print, print_task_step
#include <stdexcept>    // Для std::out_of_range, std::logic_error
#include <string>       // Для std::string (в print_task_step, areBracketsBalanced, и как тип T)
#include <cstddef>      // Для size_t
void print_task_step(int task_num, const std::string& description);

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
        clear_nodes(); // Release own resources

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
            throw std::out_of_range("Cannot pop_back from an empty list.");
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
            throw std::out_of_range("Cannot pop_front from an empty list.");
        }
        Node* node_to_delete = head;
        T value = node_to_delete->data;

        if (head == tail) { // List has only one element
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
            throw std::out_of_range("Cannot get front from an empty list.");
        }
        return head->data;
    }
     T& front() {
        if (isEmpty()) {
            throw std::out_of_range("Cannot get front from an empty list.");
        }
        return head->data;
    }

    const T& back() const {
        if (isEmpty()) {
            throw std::out_of_range("Cannot get back from an empty list.");
        }
        return tail->data;
    }
    T& back() {
        if (isEmpty()) {
            throw std::out_of_range("Cannot get back from an empty list.");
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
        std::cout << "List (size " << count << "): ";
        if (isEmpty()) {
            std::cout << "empty";
        }
        while (current != nullptr) {
            std::cout << current->data << (current->next ? " <-> " : "");
            current = current->next;
        }
        std::cout << std::endl;
    }
};

template <typename T>
class IContainer {
public:
    virtual ~IContainer() {}
    virtual void addElement(const T& value) = 0;
    virtual T removeElement() = 0;
    virtual bool isEmpty() const noexcept = 0; 
};

template <typename T>
class Stack : public IContainer<T> {
private:
    DoublyLinkedList<T> list;

public:
    Stack() = default;

    void addElement(const T& value) override {
        list.push_back(value); 
    }

    T removeElement() override { 
        if (list.isEmpty()) {
            throw std::logic_error("Stack is empty, cannot pop (removeElement).");
        }
        return list.pop_back();
    }

    bool isEmpty() const noexcept override { 
        return list.isEmpty();
    }

    const T& top() const { 
        if (list.isEmpty()) {
            throw std::logic_error("Stack is empty, cannot peek top.");
        }
        return list.back();
    }
     T& top() { 
        if (list.isEmpty()) {
            throw std::logic_error("Stack is empty, cannot peek top.");
        }
        return list.back();
    }

    size_t getSize() const noexcept { 
        return list.getSize();
    }
};

bool areBracketsBalanced(const std::string& formula);

#endif // CUSTOM_DATA_STRUCTURES_H