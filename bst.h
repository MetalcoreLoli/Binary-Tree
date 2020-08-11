#include <stdlib.h>

typedef const void * GetKeyFunc_t   (const void * pData);
typedef const int    CmpFunc_t      (const void * key1, const void * key2); 

typedef struct BSTNode {
    struct BSTNode * left;
    struct BSTNode * right;
    size_t size;
    const void * data;
} BSTNode_t;

typedef struct BSTree {
    BSTNode_t * root;
    CmpFunc_t * cmp;
    GetKeyFunc_t * getKey;
} BSTree_t;


BSTree_t * newBST(CmpFunc_t * cmp, GetKeyFunc_t* getKey);

bool BST_insert(BSTree_t * pBST, const void * pData, size_t size);
bool BST_delete(BSTree_t * pBST, const void * pData);
const void *BST_search(BSTree_t * pBST, const void * pKey);

void BST_clear          (BSTree_t * pBST);

int BST_inorder         (BSTree_t *pBST, bool (*action)(const void * pData));
int BST_preorder       (BSTree_t *pBST, bool (*action)(const void * pData));
int BST_postorder      (BSTree_t *pBST, bool (*action)(const void * pData));


