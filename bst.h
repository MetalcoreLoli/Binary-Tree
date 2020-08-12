#include <stdlib.h>

// объявления типа указателя на функция получения ключа
// const void * pData - указатель на данные
typedef const void * GetKeyFunc_t   (const void * pData);

// объявления типа указателя на функцию сравнения двух ключей
// const void * key1 - указатель на первый ключ 
// const void * key2 - указатель на второй ключ 
typedef const int    CmpFunc_t      (const void * key1, const void * key2); 

// объявления типа узла двоичного древа поиска
typedef struct BSTNode {
    // указатель на левый узел
    struct BSTNode * left;
    
    // указатель на правый узел
    struct BSTNode * right;

    // размер узла
    size_t size;

    // указатель на данные 
    const void * data;
} BSTNode_t;

// объявления типа двоичного древа поиска
typedef struct BSTree {
    // корень древа
    BSTNode_t * root;

    // указатель на функцию сравнения
    CmpFunc_t * cmp;

    // указатель на функицю получения ключа
    GetKeyFunc_t * getKey;
} BSTree_t;

// функция созднания пустого древа поиска
// CmpFunc_t* cmp - указатель на функцию сравнения данных в дереве
// GetKeyFunc_t * - указатель на функцию получения ключа
BSTree_t * newBST(CmpFunc_t * cmp, GetKeyFunc_t* getKey);

// функция вставки в древо. вернет false если вставка не удастся
// BSTree_t *pBST - указалатель на бинарное дерево
// const void * pData - указатель на данные
// size_t size - размер данных
bool BST_insert(BSTree_t * pBST, const void * pData, size_t size);

// функция удаления данных из древа. вернет false, если удаление не удастся 
// BSTree_t *pBST - указалатель на бинарное дерево
// const void * pData - указатель на данные
bool BST_delete(BSTree_t * pBST, const void * pData);

// функция поиска данных по ключи в дереве
// BSTree_t *pBST - указалатель на бинарное дерево
// const void * pKey - указатель на ключ 
const void *BST_search(BSTree_t * pBST, const void * pKey);

// функция очитски дерева
// BSTree_t *pBST - указалатель на бинарное дерево
void BST_clear         (BSTree_t * pBST);

// функции выполнения действий над данными в дереве в определенном порядке 
// BSTree_t *pBST - указалатель на бинарное дерево
// bool (*action)(const void * pData) - указатель на функцию, которая будет применяться к данным
int BST_inorder        (BSTree_t *pBST, bool (*action)(const void * pData));
int BST_preorder       (BSTree_t *pBST, bool (*action)(const void * pData));
int BST_postorder      (BSTree_t *pBST, bool (*action)(const void * pData));


