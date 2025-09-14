#include<iostream>
#include<queue>
using namespace std;

struct Node{
    int data;
    Node* right = nullptr;
    Node* left = nullptr;
};

void insertNode(Node** root,int data){
    if(*root == nullptr) {
        *root = new Node{data,nullptr,nullptr};
        return;
    }
    if((*(root))-> data > data){
        insertNode(&(*root) -> left, data);
    }else {
        insertNode(&(*root) -> right, data);
    }
}

void preOrderTraversal(Node* root){
    if(root == nullptr) return;

    cout<<root -> data << " ";
    preOrderTraversal(root -> left);
    preOrderTraversal(root -> right);
}

void postOrderTraversal(Node* root){
    if(root == nullptr) return;

    postOrderTraversal(root -> left);
    postOrderTraversal(root -> right);
    cout<<root -> data << " ";
}

void inOrderTraversal(Node* root){
    if(root == nullptr) return;
    inOrderTraversal(root -> left);
    cout<<root -> data << " ";
    inOrderTraversal(root -> right);
}

void levelOrderTraversal(Node* root){
    if(root == nullptr) return;

    queue<Node*> q;
    q.push(root);
    while (!q.empty())
    {
       Node* current = q.front();
       q.pop();

       cout<<current -> data << " ";
       if(current -> left) q.push(current -> left);
       if(current -> right) q.push(current -> right);

    }
}