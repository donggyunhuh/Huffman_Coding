#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET 26
#define MAX_LEN 100000
#define MAX_ELEMENT 100000

typedef struct
{
    int alpha; // ���ĺ� ������ ���� �迭
    int freq;  // �󵵼� ������ ���� �迭
} AlphaType;

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

void HuffmanTree(AlphaType *pArr, int n)
{
    TreeNode *node, *temp;
    Element e, e1, e2;
    HeapType heap;
    char binaryCode[100];
    int i;

    heap.heap_size = 0;

    for (i = 0; i < n; i++)
    {
        node = MakeNode(NULL, NULL);
        node->weight.alpha = pArr[i].alpha;
        e.key = node->weight.freq = pArr[i].freq;
        e.pTree = node;
        InsertHeap(&heap, e); // ������ ��带 ���� ����
    }

    for (i = 0; i < n - 1; i++) // n-1���� �ݺ�, ������ ���� ��尡 ��Ʈ
    {
        e1 = DeleteHeap(&heap); // �ּҰ��� ������ ��� 2���� ������
        e2 = DeleteHeap(&heap);

        temp = MakeNode(e1.pTree, e2.pTree); // 2���� ��带 ������ ��� ����

        e.key = temp->weight.freq = e1.key + e2.key; // 2���� ��� ���� ���Ѵ�
        e.pTree = temp;                              // ������ ���� ��带 ����

        InsertHeap(&heap, e); // Ʈ���� ������ ��带 ���� ����
    }
    e = DeleteHeap(&heap); // ���⼭ ���� �����ʹ� �ϼ��� Ʈ��

    PrintTree(e.pTree, -1, binaryCode); // ������ �ڵ� ���

    DestroyTree(e.pTree); // �޸� ��ȯ
}

void Init(AlphaType *p)
{
    for (int i = 0; i < ALPHABET; i++)
    {
        p[i].alpha = i + 65;
        p[i].freq = 0;
    }
}

int main()
{
    AlphaType data[ALPHABET]; // ���ڿ��� ���� ������ ���� ����
    AlphaType *copyData;      // �����ϴ� ���ڿ��� ���� ������ ���� ����

    Init(data);

    char *str = (char *)malloc(sizeof(char) * MAX_LEN);

    int i, j, k = 0;
    int flag, count = 0;

    printf("������ ������ ���ڿ��� �Է��ϼ��� : ");
    scanf("%s", str);

    strupr(str); // ��� ���ڸ� �빮�ڷ� ��ȯ

    for (i = 'A'; i <= 'Z'; i++)
    {
        flag = 0;
        for (j = 0; j < strlen(str); j++)
        {
            if (i == str[j])
            {
                data[i - 65].freq++;
                flag = 1; // i���� ���ĺ��� ����
            }
        }
        if (flag == 1)
            count++; // ���ĺ��� �����ϹǷ� ī���� ����
    }

    copyData = (AlphaType *)malloc(sizeof(AlphaType) * count);

    for (i = 0; i < ALPHABET; i++)
    {
        if (data[i].freq != '\0') // �����ϴ� ���ڸ� ����
        {
            copyData[k].alpha = i + 65;
            copyData[k].freq = data[i].freq;
            k++;
        }
    }

    printf("\n- ���ڴ� �� �� -\n");
    for (i = 0; i < count; i++)
        printf("%3c\t%3d \n", copyData[i].alpha, copyData[i].freq);

    printf("\n- ������ ���� ��� -\n");
    HuffmanTree(copyData, count);

    free(str);
    free(copyData);

    return 0;
}