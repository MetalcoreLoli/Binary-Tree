#include <iostream>
#include <cstring>
#include "bst.h"

bool printNodeData(const void * data) { std::cout << (const char *)data <<"\n"; return 1; }

bool contains(BSTree_t * pBST, const char * str) {
    return (BST_search(pBST, str) != NULL) ? true : false;
}


void showTree(BSTree_t *pBST) {
    std::cout << "inorder: \n";
    BST_inorder(pBST, printNodeData);

    std::cout << "\npreorder: \n";
    BST_preorder(pBST, printNodeData);

    std::cout << "\npostoreder: \n";
    BST_postorder(pBST, printNodeData);
}

int main (void) {
    const char * strs[] = {
       "123",
       "1",
       "1234569"
    };
    
    BSTree_t *pBST = newBST((CmpFunc_t *)strcmp, NULL);
    
    for (auto str : strs) {
        BST_insert(pBST, str, strlen(str));
    }
    showTree(pBST);
    
    if (contains(pBST, "simple_text")) 
        std::cout << "\"simple_text\" was found\n";

    if (contains(pBST, "1")) 
        std::cout << "\"1\" was found\n";

    BST_delete(pBST, "1");    

    std::cout << "\nafter deleting \"1\"\n";
    showTree(pBST);
    return 0;
}
