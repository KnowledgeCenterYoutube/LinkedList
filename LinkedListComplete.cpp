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

Node *tail = nullptr;
// Insert at the End -Using Tail -- O(1)
void insertNodeAtEnd_T(int data) {
    Node *node = new Node(data);
    
    // Empty List
    if(!head){
        head = node;
    }
    else{ // Non-empty list case
        tail->next = node;
    }
    tail = node;
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

void insertNodeAtPositionK(int data, int K){
    
    // Insert the beginning, head node changes
    if(K == 1){
        Node *n = new Node(data);
        n->next = head;
        head = n;
        return;
    }
    
    int count = K;
    Node *prevNode = head;
    Node *nextNode = head;
    while(count > 1){
        if(nextNode){
            prevNode = nextNode;
            nextNode = nextNode->next;
            count--;
        }
        else{ // count > 1, but we have reached the last node
            return;
        }
    }
    
    if(count == 1){
        Node *n = new Node(data);
        n->next = nextNode;
        prevNode->next = n;
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

// Reverse a Linked List -- Iterative
void reverse_LL_iterative(Node **head){
    if(head == nullptr || *head == nullptr || (*head)->next == nullptr)
        return;
    
    Node *prev = nullptr;
    Node *curr = *head;
    Node *next = curr->next;
    
    while(curr){
        curr->next = prev;
        prev = curr;
        curr = next;
        if(next)
            next = curr->next;
    }
    *head = prev;
}

// Reverse a Linked List -- Recursive
void reverse_LL_recursive(Node **head){
    if(head == nullptr || *head == nullptr || (*head)->next == nullptr)
        return;
    
    Node *curr = *head;
    Node *next = curr->next;
    *head = next;
    reverse_LL_recursive(head);
    next->next = curr;
    curr->next = nullptr;
}

bool detect_loop_map(Node *head){
    std::unordered_map<Node*, bool> visited;
    Node *curr = head;
    while(curr){
        if(visited[curr]){
            return true;
        }
        visited[curr] = true;
        curr = curr->next;
    }
    return false;
}

int count_loop_length(Node *node){
    int count = 1;
    Node *curr = node;
    while(curr->next != node){
        curr = curr->next;
        ++count;
    }
    return count;
}

bool detect_loop_floyd(Node *head){
    Node *slow = head;
    Node *fast = head;
    while(slow && fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast){
            std::cout << count_loop_length(slow) << std::endl;
            return true;
        }
    }
    return false;
}

void create_loop(Node *head){
    Node *curr = head;
    while(curr->next){
        curr = curr->next;
    }
    curr->next = head->next;
}

void print_middle(Node *head){
    Node *fast = head;
    Node *slow = head;
    while(fast && fast->next){
        fast = fast->next->next;
        slow = slow->next;
    }
    std::cout << slow->data << std::endl;
}

void print_kth_from_end(Node *head, int k){
    Node *lead = head;
    Node *lag = head;
    while(k > 0){
        if(lead){
            k--;
            lead = lead->next;
        }
        else{
            std::cout << "K is larger than length of Linked List" << std::endl;
            return;
        }
    }
    while(lead){
        lead = lead->next;
        lag = lag->next;
    }
    std::cout << "kth node from end = " << lag->data << std::endl;
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

void swap_nodes(Node **headPtr, int a, int b){
    if(a == b || !headPtr || !(*headPtr))
        return;
    
    Node *curr = *headPtr;
    Node *prev = nullptr;
    Node *nodeA = nullptr;
    Node *nodeB = nullptr;
    Node *prevA = nullptr;
    Node *prevB = nullptr;
    
    while (curr) {
        if(curr->data == a){
            nodeA = curr;
            prevA = prev;
        } else if(curr->data == b){
            nodeB = curr;
            prevB = prev;
        }
        prev = curr;
        curr = curr->next;
    }
    
    if(!nodeA || !nodeB)
        return;
    
    if(prevA){
        prevA->next = nodeB;
    } else { // nodeA is head
        *headPtr = nodeB;
    }
    
    if(prevB){
        prevB->next = nodeA;
    } else { // nodeB is head
        *headPtr = nodeA;
    }
    
    Node *tmp = nodeA->next;
    nodeA->next = nodeB->next;
    nodeB->next = tmp;
}

int main(int argc, const char * argv[]) {
    //insertNode(1);
    //insertNode(2);
    //insertNode(3);
    // head --> 3 -> 2 -> 1 -> NULL
    
    //    insertNodeAtEnd_T(1);
    //    insertNodeAtEnd_T(2);
    //    insertNodeAtEnd_T(3);
    // head --> 1 -> 2 -> 3 -> NULL
    
    insertNodeAtEnd(1);
    insertNodeAtEnd(2);
    insertNodeAtEnd(3);  // 1->2->3
    
    insertNodeAtPositionK(10, 1); // 10->1->2->3
    insertNodeAtPositionK(20, 2); // 10->20->1->2->3
    insertNodeAtPositionK(50, 5); // 10->20->1->2->50->3
    insertNodeAtPositionK(70, 8); // 10->20->1->2->50->3
    
    
    //std::cout << head->data << " -> " << head->next->data << " -> " << head->next->next->data << std::endl;
    
    printList(head);
    
    //reverse_LL_iterative(&head);
    //reverse_LL_recursive(&head);
    //printList(head);
    
    //bool hasloop = detect_loop_map(head);
    //std::cout << std::boolalpha << hasloop << std::endl;
    //bool hasloop = detect_loop_floyd(head);
    //std::cout << std::boolalpha << hasloop << std::endl;
    
    //std::cout << "-------------" << std::endl;
    
    //create_loop(head);
    
    //hasloop = detect_loop_map(head);
    //std::cout << hasloop << std::endl;
    //hasloop = detect_loop_floyd(head);
    //std::cout << hasloop << std::endl;
    
    //print_middle(head);
    //print_kth_from_end(head, 3);
    
    //find_loop_beginning(head);
    
    //remove_loop(head);
    
    swap_nodes(&head, 10, 20);
    printList(head);
    
    return 0;
}

