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

int minElement(Node* root){
    if(root -> left){
        return minElement(root -> left);
    }
    if(!root -> left) return root -> data;
}

Node* minElementNode(Node* root){
    if(root -> left){
        return minElementNode(root -> left);
    }
    if(!root -> left) return root;
}

int maxElement(Node* root){
    if(root -> right){
        return maxElement(root -> right);
    }
    if(!root -> right) return root -> data;
}

Node* maxElementNode(Node* root){
    if(root -> right){
        return maxElementNode(root -> right);
    }
    if(!root -> right) return root;
}

int height(Node* root){
    if(root == nullptr) return 0;
    return 1 + max(height(root -> left), height(root -> right));
}

//delete the node by replacing the inorder successor value
Node* deleteNodeByValue(Node* root,int valToDelete){
    if(root == nullptr) return root;

    if( valToDelete > root -> data ){
        root -> right = deleteNodeByValue(root -> right, valToDelete);
    } else if(valToDelete < root -> data) {
        root -> left = deleteNodeByValue(root -> left, valToDelete);
    } else {
        if(!root -> left) {
            Node* temp = root -> right;
            delete root;
            return temp;
        } else if(!root -> right){
            Node* temp = root -> left;
            delete root;
            return temp;
        }
        Node* minNode = minElementNode(root -> right);
        root -> data = minNode -> data;
        root -> right = deleteNodeByValue(root -> right,minNode -> data);
    }
    return root;
}

//delete the node completely from memory and replace it with inorder successor node
Node* deleteNodeByReplacement(Node* root, int valToDelete){

    if(!root) return root;

    if(valToDelete > root -> data){
        root -> right = deleteNodeByReplacement(root -> right, valToDelete);
    } else if( valToDelete < root -> data){
        root -> left = deleteNodeByReplacement(root -> left, valToDelete);
    }else {
        if(!root -> left){
            Node* temp = root -> right;
            delete root;
            return temp;
        } else if(!root -> right){
            Node* temp = root -> left;
            delete root;
            return temp;
        }
        Node* succ = root -> right;
        Node* succParent = root;

        while(succ -> left){
            succParent = succ;
            succ = succ -> left;
        }
        if(succParent != root){
            succParent -> left = succ -> right;
            succ -> right = root -> right;
        }
        succ -> left = root -> left;

        delete root;
        return succ;

    }
return root;
}