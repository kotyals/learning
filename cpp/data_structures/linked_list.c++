#include<iostream>
#include"operations.hpp"


// void deleteLastNode(Node** root) {
//     if(*root == nullptr) {
//         cout<<"No data in list";
//         return;
//     }
//     Node* temp = *root;
//     while( temp -> next != nullptr) {
//         temp = temp -> next;
//     }
// }
int main() {
    Node* root = nullptr;
    
    insertAtBeginning(&root,10);
    // printElements(root);
        // deleteFirstNode(&root);
    // printElements(root);

    insertAtEndRec(&root,20);
    insertAtBeginning(&root,1);
    insertAt(&root,3,4);
    insertAt(&root,17,2);
    insertAt(&root,12,1);
    printElements(root);

    // deleteFirstNode(&root);
    // deleteLastNode(&root);


    root = reverseIter(root); 
    // reverse(&root);
    //         // deleteLatNodeRec(&root);
            printElements(root);
            // printRec(root);
            // cout<<endl;
            // printRecRev(root);



    return 0;
}