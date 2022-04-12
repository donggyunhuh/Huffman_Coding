void HuffmanTree(AlphaType* pArr, int n){
    TreeNode *node, *temp;
    Element e, e1,e2;
    HeadType heap;
    char binaryCode[100];
    int i;

    heap.heap_size = 0;

    for (i=0; i<n; i++){
        node = MakeNode(NULL,NULL);
        node->weight.alpha = pArr[i].alpha;
        e.key = node->weight.freq = pArr[i].freq;
        e.pTree = node;
        InsertHeap(&heap, e);   // 생성한 노드를 힙에 삽입
    }

    for(i=0; i<n-1; i++){       //n-1까지 반복, 마니막 남은 노드라 루트
        e1 = DeleteHeap(&heap);
        e2 = DeleteHeap(&heap);   //최소값을 가지는 노드 2개를 빼낸다

        temp = MakeNode(e1.pTree, e2.pTree);   // 2개의 노드를 가지는 노드 생성

        e.key = temp->weight.freq = e1.key+e2.key;   // 2개의 노드 값을 더한다
        e.pTree = temp;  // 위에서 만든 노드를 대입

        InsertHeap(&heap.e);   //트리로 구성된 노드를 힙에 삽입
    }

    e = DeleteHeap(&heap); // 꺼낸 데이터는 완성된 트리

    PrintTree(e.pTree, -1, binaryCode);  //하프만 코드 출력

    DestroyTree(e.pTree);  //메모리 변환
}