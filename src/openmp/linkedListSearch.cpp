#include <iostream>
#include <omp.h>

struct Node {
    int data;
    Node* next;
};

bool searchLinkedList(Node* head, int value) {
    Node* current = head;
    #pragma omp parallel
    {
        bool found = false;
        #pragma omp for
        for (; current != nullptr; current = current->next) {
            if (current->data == value) {
                found = true;
                break;
            }
        }
        #pragma omp critical
        {
            if (found) {
                std::cout << "Element " << value << " found!" << std::endl;
            }
        }
    }
    return false;
}

int main() {
    // Create a sample linked list
    Node* head = new Node();
    head->data = 1;
    Node* second = new Node();
    second->data = 2;
    head->next = second;
    Node* third = new Node();
    third->data = 3;
    second->next = third;
    third->next = nullptr;

    // Search for an element in the linked list
    int value = 2;
    searchLinkedList(head, value);

    return 0;
}
