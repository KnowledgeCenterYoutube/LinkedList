#include <iostream>
#include <unordered_map>

// structure of Node
struct Node{
    int data;
    Node *next;
    
    Node(int val):data(val), next(nullptr){}
    ~Node(){
        if(next){
            delete next;
            next = nullptr;
        }
    }
};

Node* head = nullptr;

// Insertion at the beginning
void insertNode(int data){
    Node *node = new Node(data);
    node->next = head;
    head = node;
}

// Insert at the End - Not Using Tail -- O(n)
void insertNodeAtEnd(int data) {
    Node *node = new Node(data);
    Node *current = head;
    
    // Empty List
    if(!head){
        head = node;
    }
    else{ // Non-empty list case
        while(current->next){
            current = current->next;
        }
        current->next = node;
    }
}

// Print Elements of the List - O(n)
void printList(Node* head){
    Node *curr = head;
    while(curr){
        std::cout << curr->data << " -> ";
        curr = curr->next;
    }
    std::cout << "NULL" << std::endl;
}

// create loop - make next of last node point to 2nd element of list
void create_loop(Node *head){
    Node *curr = head;
    while(curr->next){
        curr = curr->next;
    }
    curr->next = head->next;
}

void find_loop_beginning(Node *head){
    Node *slow = head;
    Node *fast = head;
    if (!head || !(head->next))
        return;
    while(slow && fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast)
            break;
    }
    
    // No Loop exixts
    if (slow != fast){
        std::cout << "No Loop" << std::endl;
        return;
    }
    
    // When Loop exists
    slow = head;
    while(slow != fast){
        slow = slow->next;
        fast = fast->next;
    }
    std::cout << "First loop element = " << slow->data << std::endl;
}

void remove_loop(Node *head){
    Node *slow = head;
    Node *fast = head;
    if (!head || !(head->next))
        return;
    while(slow && fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast)
            break;
    }
    
    // No Loop exixts
    if (slow != fast){
        std::cout << "No Loop" << std::endl;
        return;
    }
    
    // When Loop exists
    slow = head;
    while(slow->next != fast->next){
        slow = slow->next;
        fast = fast->next;
    }
    fast->next = nullptr;
}

int main(int argc, const char * argv[]) {
    
    insertNodeAtEnd(10);
    insertNodeAtEnd(20);
    insertNodeAtEnd(1); 
    insertNodeAtEnd(2); 
    insertNodeAtEnd(50); 
    insertNodeAtEnd(3); // 10->20->1->2->50->3
    
    create_loop(head);
  
    find_loop_beginning(head);
    
    remove_loop(head);
    
    printList(head);
    
    return 0;
}

