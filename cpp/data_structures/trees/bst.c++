#include"bst_operations.h"

int main() {
    Node* root = nullptr;
    insertNode(&root, 15);
    insertNode(&root, 10);
    insertNode(&root, 20);
    insertNode(&root, 8);
    insertNode(&root, 12);
    insertNode(&root, 17);
    insertNode(&root, 25);
    insertNode(&root, 6);
    insertNode(&root, 11);
    insertNode(&root, 16);


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

    // ---- Test deletions ----

    // Case 1: Delete a leaf node (e.g., 6)
    cout << "\nDeleting leaf node 6 (by value-copy method):\n";
    root = deleteNodeByValue(root, 6);
    inOrderTraversal(root);
    cout << "\n";

    // Case 2: Delete node with one child (e.g., 17 has child 16)
    cout << "\nDeleting node 17 with one child (by replacement method):\n";
    root = deleteNodeByReplacement(root, 17);
    inOrderTraversal(root);
    cout << "\n";

    // Case 3: Delete node with two children (e.g., 15 root)
    cout << "\nDeleting root 15 with two children (by value-copy method):\n";
    root = deleteNodeByValue(root, 15);
    inOrderTraversal(root);
    cout << "\n";

    cout<<"Min element: "<< minElement(root)<<endl;
    cout<<"Max Element: "<< maxElement(root)<<endl;

    cout<<"Height: " << height(root)<<endl;

    return 0;
}