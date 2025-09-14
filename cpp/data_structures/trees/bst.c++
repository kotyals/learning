#include"bst_operations.h"

int main() {
    Node* root = nullptr;
    insertNode(&root,10);
    insertNode(&root,20);
    insertNode(&root,18);
    insertNode(&root,9);
    insertNode(&root,5);
    insertNode(&root,1);
    insertNode(&root,7);

    cout<<"Pre-order traversal" << endl;
    preOrderTraversal(root);
    cout<<endl;

    cout<<"Post-order traversal" << endl;
    postOrderTraversal(root);
    cout<<endl;

    cout<<"In-order traversal" << endl;
    inOrderTraversal(root);
    cout<<endl;

    cout<<"Level-order traversal" << endl;
    levelOrderTraversal(root);
    cout<<endl;

    return 0;
}