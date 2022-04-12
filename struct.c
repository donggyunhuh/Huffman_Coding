#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET 26
#define MAX_LEN 100000
#define MAX_ELEMENT 100000

// heap ���� ��Ʈ

typedef struct
{
    int alpha; // ���ĺ� ������ ���� �迭
    int freq;  // �󵵼� ������ ���� �迭
} AlphaType;   // ����ü �̸� ����

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

    while (i != 1 && item.key < h->heap[i / 2].key) // �θ���� ��
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
    temp = h->heap[(h->heap_size)--]; // ������ ���� size ����

    while (child <= h->heap_size)
    {
        //�ڽ� ��尣 ���� �� ��
        if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
            child++;

        if (temp.key <= h->heap[child].key)
            break;

        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2; // ���� �ڽ� ���� ��
    }

    h->heap[parent] = temp;
    return data;
}

TreeNode *MakeNode(TreeNode *left, TreeNode *right) // ��� ����
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));

    if (node == NULL)
    {
        printf("�޸� �Ҵ� ����\n");
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