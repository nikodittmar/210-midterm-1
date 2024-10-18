#include <iostream>
using namespace std;

// Declare constants, 
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// Doubly Linked List class to encapsulate the data structure.
class DoublyLinkedList {
private:
    // Define each node of the doubly linked list.
    struct Node {
        // The data is the information the node stores.
        int data;
        // Prev is the reference to the previous node, it is null if it is the head.
        Node* prev;
        // Next is the reference to the next node, it is null if it is the tail.
        Node* next;
        // Node constructor.
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            // Set the data to the inputted int.
            data = val; 
            // Set the pointer to prev to the one passed into the constructor.
            prev = p;
            // Set the pointer to next to the one passed into the constructor.
            next = n;
        }
    };

    // Pointer to the head of the linked list.
    Node* head;
    // Pointer to the tail of the linked list.
    Node* tail;

public:
    // Default constructor, set the head and tail pointers to null.
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    // This function adds a new node after a specific index.
    void insert_after(int value, int position) {
        // Ensure that the position is not below 0, an index below 0 is invalid.
        if (position < 0) {
            // Notify the user that the position is invalid.
            cout << "Position must be >= 0." << endl;
            // Exit the function.
            return;
        }

        // Initialize the new node.
        Node* newNode = new Node(value);

        // If the head is null, the list is empty.
        if (!head) {
            // Because the list was previously empty, the new node is both the head and tail of the list.
            // Set the head and tail to point to this new node.
            head = tail = newNode;
            // Exit the function because we have added the node.
            return;
        }

        // Create a pointer variable to point to the current node for our traversal.
        Node* temp = head;
        // Iterate until we reach the index passed into the function.
        for (int i = 0; i < position && temp; ++i)
            // Set our pointer to point to the next node to traverse the list.
            temp = temp->next;

        // If temp is null, we passed the tail node and thus our postion was out of bounds.
        if (!temp) {
            // Notify the user that the postion was invalid and that we were unable to insert the node.
            cout << "Position exceeds list size. Node not inserted.\n";
            // Delete the node to free up space on the heap.
            delete newNode;
            // Exit the function due to error.
            return;
        }

        // If this point is reached, we have found the node at position that we would like to insert another node after.
        // Since we are inserting between temp and the node after temp, the node after temp is the next node for our new node.
        newNode->next = temp->next;
        // Since we are inserting after temp, temp is the previous node. Set the prev pointer to point to temp.
        newNode->prev = temp;
        // If the temp has a next (i.e. it is not the tail node), set the node after it to point to the new node we created.
        if (temp->next)
            // Set the pointer to the next node to point to the newnode as we have inserted the node between temp and the node after it.
            temp->next->prev = newNode;
        else
            // If temp->next is null, we are at the tail so set the tail to point to our new node as it is now the new tail.
            tail = newNode;
        // Since we are inserting after temp, the next node after temp is now newnode.
        temp->next = newNode;
    }

    // This function deletes a node that matches the inputted value, if two nodes have the same value, the first one in the list is deleted.
    void delete_val(int value) {
        // If the head is null, the list is empty and there are no items to delete so return to exit the function.
        if (!head) return;

        // Create pointer to node called temp to store our traversal through the linked list.
        Node* temp = head;
        
        // Traverse through the list until we either reach the end or find the node that matches the inputted value.
        while (temp && temp->data != value)
            // Traverse the list by moving to the next node each iteration of the loop.
            temp = temp->next;

        // If temp is null, the loop above exited due to reaching the end of the list without finding the value.
        // Since the value was not found, we have nothing to delete so exit the list.
        if (!temp) return; 

        // If the value to delete has a prev, (i.e. it is not the head), set the previous node's next to point to the node after the one to delete.
        if (temp->prev)
            // Set the previous node's next to the next node on the node we are deleting.
            temp->prev->next = temp->next;
        else
            // If there is no prev, the node is the head so set the head to point to the new head which is the node after the one we are deleting.
            head = temp->next; 

        // If the value to delete has a next, (i.e. it is not the tail), set the next node's prev to point to the node before the one to delete.
        if (temp->next)
            // Set the next node's prev to point to the node before the one we are deleting.
            temp->next->prev = temp->prev;
        else
            // If there is no next, the node is the tail so set the tail to point ot the new tail which is the node before the one we are deleting.
            tail = temp->prev; 

        // Delete the node to free up space on the heap.
        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}