#include "bst.h"


const void * defaultKey(const void *pData) { return pData; }

BSTree_t * newBST(CmpFunc_t* cmp, GetKeyFunc_t * getKey) {
    BSTree_t * pBST = new BSTree_t;
    
    if (cmp != NULL) {
        pBST->root = NULL; 
        pBST->cmp = cmp;
        pBST->getKey = (getKey == NULL) ? defaultKey : getKey;
    }
    return pBST;
}

static void clear(BSTNode_t* pNode) {
    if (pNode == NULL) return;
    clear(pNode->left);
    clear(pNode->right);
    delete pNode;
}

void BST_clear(BSTree_t * pBST) {
    if (pBST == NULL) return;
    clear(pBST->root);    
}

static BSTNode_t * detachMin(BSTNode_t **ppNode) {
    BSTNode_t * pNode = *ppNode;
    if (pNode == NULL) return NULL;
    else if (pNode->left != NULL) {
        return detachMin(&(pNode->left));
    } else {
        *ppNode = pNode->right;
        return pNode;
    }
}

static bool delete_data(BSTree_t * pBST,BSTNode_t **ppNode, const void * pData) {
    BSTNode_t *pNode = *ppNode;
    if (pNode == NULL) return false;
    int cmp_res = pBST->cmp(pData, pBST->getKey(pNode->data));
    if (cmp_res < 0) {
        return delete_data(pBST, &(pNode->left), pData);
    } else if (cmp_res > 0) {
        return delete_data(pBST, &(pNode->right), pData);
    } else {
        if (pNode->left == NULL) {
            *ppNode = pNode->right;
        } else if (pNode->right == NULL) {
            *ppNode= pNode->left;
        } else {
            BSTNode_t *pMin = detachMin(&(pNode->right));
            *ppNode = pMin;
            pMin->left  = pNode->left;
            pMin->right = pNode->right; 
        }
        delete pNode;
        return true;
    }
}

bool BST_delete(BSTree_t * pBST, const void * pData) {
    if (pBST == NULL || pData == NULL)
        return false;
    else 
        return delete_data(pBST, &(pBST->root), pData);
}

static const void* search (BSTree_t * pBST, BSTNode_t *pNode, const void * pKey) {
   if (pNode == NULL) {
        return NULL;
   } else {
        int cmp_res = pBST->cmp(pKey, pBST->getKey(pNode->data));

        if (cmp_res == 0) {
            return pNode->data;
        } else if (cmp_res < 0) {
            return search(pBST, pNode->left, pKey);
        } else {
            return search(pBST, pNode->right, pKey);
        }
   }
}

const void * BST_search(BSTree_t * pBST, const void * pKey) {
     if (pBST == NULL || pKey == NULL) {
        return NULL;
     } else {
        return search(pBST, pBST->root, pKey);
     } 
}

static bool insert(BSTree_t *pBST, BSTNode_t** ppNode, const void * pData, size_t size) {
    BSTNode_t * pNode = *ppNode;

    if (pNode == NULL) {
        pNode = new BSTNode_t;
        if (pNode != NULL) {
            pNode->data = pData;
            pNode->size = size;
            *ppNode = pNode; //insert data into node ;
            return true; 
        } else {
            return false;
        }
    } else {
        const void * key1 = pBST->getKey(pData);
        const void * key2 = pBST->getKey(pNode->data);
        if (pBST->cmp(key1, key2) < 0) {
            return insert(pBST, &(pNode->left), pData, size);
        } else {
            return insert(pBST, &(pNode->right), pData, size);
        }

    }
}

bool BST_insert(BSTree_t * pBST, const void * pData, size_t size) {
    if (pBST == NULL || pData == NULL || size == NULL) {
        return false;
    } else {
        return insert(pBST, &(pBST->root), pData, size);
    }
}

static int inorder(BSTNode_t * pNode, bool (* action)(const void *pData)) {
    if (pNode == NULL) return 0; 
    int count  = 0;
    count = inorder(pNode->left, action);
    if (action(pNode->data)) count++;
    count += inorder(pNode->right, action);
    return count;
}

int BST_inorder(BSTree_t *pBST, bool (*action)(const void * pData)) {
   if (pBST == NULL || action == NULL) { 
       return 0;
   }
   else {
    return inorder(pBST->root, action);
   } 
}

static int preorder (BSTNode_t * pNode, bool (*action)(const void *pData)) {
    if (pNode == NULL) return 0; 
    int count  = 0;

    if (action(pNode->data)) count++;
    count = preorder(pNode->left, action);
    count += preorder(pNode->right, action);

    return count;
}

int BST_preorder (BSTree_t *pBST, bool (*action)(const void * pData)) {
   if (pBST == NULL || action == NULL) { 
        return 0;
   }
   else {
        return preorder(pBST->root, action);
   }
}
static int postorder (BSTNode_t * pNode, bool (*action)(const void *pData)) {
    if (pNode == NULL) return 0; 
    int count  = 0;

    count = postorder(pNode->left, action);
    count += postorder(pNode->right, action);
    if (action(pNode->data)) count++;

    return count;
}

int BST_postorder(BSTree_t *pBST, bool (*action)(const void * pData)) {
   if (pBST == NULL || action == NULL) { 
        return 0;
   }
   else {
        return postorder(pBST->root, action);
   }
}
