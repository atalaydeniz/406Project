#include <iostream>

struct Node {
    int data;
    Node* next;
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() {
        head = nullptr;
    }

    void insert(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        std::cout << "Inserted " << value << " into the linked list." << std::endl;
    }

    void remove(int value) {
        if (head == nullptr) {
            std::cout << "Linked list is empty. Cannot delete." << std::endl;
            return;
        }

        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            std::cout << "Deleted " << value << " from the linked list." << std::endl;
            return;
        }

        Node* current = head;
        while (current->next != nullptr) {
            if (current->next->data == value) {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
                std::cout << "Deleted " << value << " from the linked list." << std::endl;
                return;
            }
            current = current->next;
        }

        std::cout << "Value " << value << " not found in the linked list." << std::endl;
    }

    bool search(int value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                std::cout << "Value " << value << " found in the linked list." << std::endl;
                return true;
            }
            current = current->next;
        }

        std::cout << "Value " << value << " not found in the linked list." << std::endl;
        return false;
    }

    void display() {
        Node* current = head;
        if (current == nullptr) {
            std::cout << "Linked list is empty." << std::endl;
        } else {
            std::cout << "Linked list: ";
            while (current != nullptr) {
                std::cout << current->data << " ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    LinkedList linkedList;

    linkedList.display(); // Linked list is empty.

    for (int i = 0; i < 16777216; i++) {
        linkedList.insert(i);
    }
    int j;
    for (int i = 0; i < 5; i++) {
        j = 16777216/6;
        linkedList.search(j);
        linkedList.search(2*j);
        linkedList.search(3*j);
        linkedList.search(4*j);
        linkedList.search(5*j);
    }

    return 0;
}
