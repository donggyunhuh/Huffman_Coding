#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET 26
#define MAX_LEN 100000
#define MAX_ELEMENT 100000

// heap 구현 파트

typedef struct
{
    int alpha; // 알파벳 저장을 위한 배열
    int freq;  // 빈도수 저장을 위한 배열
} AlphaType;   // 구조체 이름 저장

typedef struct TreeNode
{
    AlphaType weight;
    struct TreeNode *left_child;
    struct TreeNode *right_child;
} TreeNode;

typedef struct
{
    TreeNode *pTree;
    int key;
} Element;

typedef struct
{
    Element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

void InsertHeap(HeapType *h, Element item)
{
    int i;
    i = ++(h->heap_size);

    while (i != 1 && item.key < h->heap[i / 2].key) // 부모노드와 비교
    {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }

    h->heap[i] = item;
}

Element DeleteHeap(HeapType *h)
{
    int parent = 1, child = 2;
    Element data, temp;

    data = h->heap[parent];
    temp = h->heap[(h->heap_size)--]; // 삭제에 의한 size 감소

    while (child <= h->heap_size)
    {
        //자식 노드간 작은 수 비교
        if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
            child++;

        if (temp.key <= h->heap[child].key)
            break;

        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2; // 다음 자식 노드와 비교
    }

    h->heap[parent] = temp;
    return data;
}

TreeNode *MakeNode(TreeNode *left, TreeNode *right) // 노드 생성
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));

    if (node == NULL)
    {
        printf("메모리 할당 에러\n");
        exit(-1);
    }

    node->left_child = left;
    node->right_child = right;

    return node;
}

void PrintTree(TreeNode *p, int i, char *pCode)
{
    if (p)
    {
        i++;
        pCode[i] = '1';
        PrintTree(p->left_child, i, pCode);
        pCode[i] = '0';
        PrintTree(p->right_child, i, pCode);
        pCode[i] = '\0';

        if (p->left_child == NULL && p->right_child == NULL)
        {
            printf("%3c\t%3d\t%s\n", p->weight.alpha, p->weight.freq, pCode);
        }
    }
}

int DestroyTree(TreeNode *p)
{
    if (p == NULL)
        return -1;

    DestroyTree(p->left_child);
    DestroyTree(p->right_child);

    free(p);

    return 1;
}