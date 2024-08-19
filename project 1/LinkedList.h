#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
public:
    class Node {
    public:
        Node* next;
        Node* prev;
        T data;
    };

private:
    unsigned int NodeCounter;
    Node* head;
    Node* tail;

public:
    LinkedList() {
        NodeCounter = 0;
        head = nullptr;
        tail = nullptr;
    }

    // Accessors
    unsigned int NodeCount() const {
        return NodeCounter;
    }

    Node* Head() {
        return head;
    }

    const Node* Head() const {
        return head;
    }

    // Insertions
    void AddHead(const T& data) {
        Node* pro = new Node();
        pro->data = data;
        pro->next = head;
        pro->prev = nullptr;

        if (head != nullptr) {
            head->prev = pro;
        } else {
            tail = pro;
        }

        head = pro;
        NodeCounter++;
    }

    void AddTail(const T& data) {
        Node* pro = new Node();
        pro->data = data;
        pro->next = nullptr;
        pro->prev = tail;

        if (tail != nullptr) {
            tail->next = pro;
        } else {
            head = pro;
        }

        tail = pro;
        NodeCounter++;
    }

    void AddNodesHead(const T* data, unsigned int count) {
        int invert = (int)count - 1;
        for (int i = invert; i >= 0; i--) {
            AddHead(data[i]);
        }
    }

    void AddNodesTail(const T* data, unsigned int count) {
        for (unsigned int i = 0; i < count; i++) {
            AddTail(data[i]);
        }
    }

    // Behaviors
    void PrintForward() const {
        Node* iterator = head;
        while (iterator != nullptr) {
            cout << iterator->data << endl;
            iterator = iterator->next;
        }
    }

    void PrintReverse() const {
        Node* iterator = tail;
        while (iterator != nullptr) {
            cout << iterator->data << endl;
            iterator = iterator->prev;
        }
    }

    // Destructor
    ~LinkedList() {
        Clear();
    }

    // Removals
    void Clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
        NodeCounter = 0;
    }
};
#endif