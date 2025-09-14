
using namespace std;

struct Node {
    int data;
    Node* next;
};

void printElements(Node* root) {
    cout<<"Print Elemenmts"<<endl;
    if( root == nullptr) {
        cout<<"No elements  "<<endl;
        return;
    }
    while( root != nullptr){
        cout<<root -> data << " ";
        root = root -> next;
    }
    cout<<endl;

}

void printRec(Node* root) {
    if(root == nullptr) return;
    cout<<root -> data << " ";
    printRec(root -> next);
}

void printRecRev(Node* root) {
    if(root == nullptr) return;
    printRec(root -> next);
    cout<<root -> data << " ";
}


void insertAtBeginning(Node** root,int data){
    Node* newNode = new Node{data,* root};
    *root = newNode;
}

void insertAtEnd(Node** root,int data) {
    if(*root == nullptr) {
        *root = new Node{data,nullptr};
        return;
    }
    Node* temp = *root;

    while( temp -> next != nullptr) {
        temp = temp -> next;
    }
    temp -> next = new Node{data,nullptr};
}

void insertAtEndRec(Node** root, int data) {
    if(*root == nullptr){
        *root = new Node{data,nullptr};
        return;
    }
    insertAtEndRec(&((*root) -> next),data);
}

void insertAt(Node** root, int data, int pos) {
    if(pos == 1) {
        *root = new Node{data,*root};
        return ;
    }
    Node* temp = *root;
    for(int i=1; i<pos-1 && temp -> next != nullptr ; i++ ){
        temp = temp -> next;
    }
    temp-> next = new Node{data, temp -> next}; 
}

void deleteFirstNode(Node** root) {
    if(*root == nullptr) {
        cout<<"No data in list";
        return ;
    }
    Node* temp = *root;
    *root = (*root) -> next;
    delete temp;

}
void deleteLatNodeRec(Node** root){
    if(*root == nullptr) return;
    if( (*root) -> next == nullptr){
        delete *root;
        *root = nullptr;
        return;
    }
    deleteLatNodeRec( &((*root) -> next));
}
void deleteLastNode(Node** root) {
    if(*root == nullptr) {
        cout<<"No data in list";
        return;
    }
    if((*root) -> next == nullptr){
        delete *root;
        *root = nullptr;
        return;
    }
    Node* temp = *root;
    Node * prev = *root;
    while( temp -> next != nullptr) {
        prev = temp;
        temp = temp -> next;
    }
    delete temp;
    prev -> next = nullptr;
}

Node* reverseRec(Node* root) {
    if( root == nullptr || root -> next == nullptr)
    {
        return root;
    }
    Node *newHead = reverseRec(root -> next);
    root -> next -> next = root;
    root -> next = nullptr;
    return newHead;
}


Node* revUtil(Node * root) {
    if( root == nullptr || root -> next == nullptr) {
        return root;
    }

    Node* newHead = revUtil(root -> next);
    root -> next -> next = root;
    root -> next = nullptr;
    return newHead;
}
void reverse(Node** root) {
    if(*root == nullptr || (*root) -> next == nullptr) {
        return;

    }
    Node* newHead = revUtil((*root) );
    *root = newHead;
}

Node* reverseIter(Node* root){
    if(!root && !root-> next) return root;
    Node* curr = root;
    Node* prev = nullptr;
    while(curr){
        Node* next = curr -> next;
        curr -> next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
