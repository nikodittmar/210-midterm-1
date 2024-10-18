// COMSC 210 | Midterm 1 | Niko Dittmar
#include <iostream>
using namespace std;

// Declare constants:
// MIN_NR, minimum value for random node value.
// MAX_NR, maximum value for random node value.
// MIM_LS, minimum size for random list size.
// MAX_LS, maximum size for random list size.
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

    // This function will delete the node at the specified index.
    void delete_pos(int pos) {
        // If the head is null, the list is empty and there are no items to delete.
        if (!head) {
            // Notify the user that the list is empty and that we cannot delete any items.
            cout << "List is empty." << endl;
            // Exit the function.
            return;
        }
    
        // If the position is 1, we are removing the first item in the list so call pop_front() which deletes the first item in the list.
        if (pos == 1) {
            // Call pop front to delete the first item in the list.
            pop_front();
            // Exit the function as we have deleted the node.
            return;
        }
    
        // Create a pointer variable to point to the head, this will be our traveral variable to iterate over the list.
        Node* temp = head;
    
        // Iterate over the list until we have reached the inputted position.
        for (int i = 1; i < pos; i++){
            // If temp is null, we passed the end of the list and thus the positon was out of bounds.
            if (!temp) {
                // Notify the user that the positon was out of bounds.
                cout << "Position doesn't exist." << endl;
                // Exit the function because of the error.
                return;
            }
            else
                // If temp is not null, we can continue iterating through the list by setting our traversal to the next node.
                temp = temp->next;
        }
        // If temp is null, we again passed the end of the list and thus the position was out of bounds.
        if (!temp) {
            // Again notify the user that the positon is out of bounds.
            cout << "Position doesn't exist." << endl;
            // Exit the function because of the error.
            return;
        }
    
        // If temp does not have next node, it is the tail so we can simply call pop_back to remove the last item from the list.
        if (!temp->next) {
            // Call pop back to remvoe the last item from the list.
            pop_back();
            // Exit the function as we have successfully deleted the node.
            return;
        }
    
        // Create a pointer variable to temporarily hold the previous node of the one to delete.
        Node* tempPrev = temp->prev;
        // Set the next node of the previous node to point to the node after the one we are deleting.
        tempPrev->next = temp->next;
        // Set the prev of the node after the one we are deleting to point to the previous node to the one we are deleting.
        temp->next->prev = tempPrev;
        // Delete the node we are deleting to free space on the heap.
        delete temp;
    }

    // This function will add a node to the end of the doubly linked list.
    void push_back(int v) {
        // Create the new node with the inputted value.
        Node* newNode = new Node(v);
        // If there is no tail, the list is empty.
        if (!tail)
            // If the list is empty, set both the head and tail to point to our new one and only node. (since it is the only node it is both the head and tail of our list.)
            head = tail = newNode;
        else {
            // If the list already has nodes, set the old tail's next to point to our new node.
            tail->next = newNode;
            // Set our new node's prev to point to the old tail of the list.
            newNode->prev = tail;
            // Set the tail pointer to point to the new tail (the node we added to the back of the list)
            tail = newNode;
        }
    }
    
    // This function will add a node to the front of the doubly linked list.
    void push_front(int v) {
        // Create the new node with the inputted value.
        Node* newNode = new Node(v);
        // If there is no head, the list is empty.
        if (!head)
            // If the list is empty, set both the head and tail to point to our new one and only node. (since it is the only node, it is both the head and tail of our list.)
            head = tail = newNode;
        else {
            // If the list already had nodes, set the new node's next pointer to point to the current head.
            newNode->next = head;
            // Set the old head's prev to point to our new head.
            head->prev = newNode;
            // Set the head to point to our new head, newnode.
            head = newNode;
        }
    }
    
    // This function will remove the first item from the doubly linked list.
    void pop_front() {

        // If there is no head, the list is empty and there is nothing to delete.
        if (!head) {
            // Notify the user that there is nothing to delete as the list is empty.
            cout << "List is empty." << endl;
            // Exit the function due the the error.
            return;
        }

        // Store the pointer to the head in temp.
        Node * temp = head;

        // If there is a node after head, it is not the only item in the list.
        if (head->next) {
            // Set the new head to the node after the one we will delete.
            head = head->next;
            // Set the new head's prev to a null pointer as there is no node before it.
            head->prev = nullptr;
        }
        else
            // If the head is the only item in the list, set both the head and tail to a null pointer.
            head = tail = nullptr;
        // Delete the front node to free space on the heap.
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