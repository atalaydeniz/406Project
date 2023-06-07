/*

Classified as "Memory Management" --> "Memory Leak"

*/

#include <iostream>

struct Node {
    int data;
    Node* next;
};

void insertLinkedList(Node** head, int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;

    if (*head == nullptr) {
        // If the list is empty, make the new node the head
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

int main() {
    // Create an empty linked list
    Node* head = nullptr;

    // Insert elements into the linked list
    insertLinkedList(&head, 1);
    insertLinkedList(&head, 2);
    insertLinkedList(&head, 3);

    // Print the linked list
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;

    return 0;
}
