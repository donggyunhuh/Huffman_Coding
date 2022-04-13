# Huffman_Coding

허프만 압축 알고리즘 with C

## 허프만 코드란?

텍스트에서 문자 빈도수에 따라 다른 길이의 부호를 부여하여 파일을 압축하는 과정이다.
부호를 부여할때 코드가 겹치지 않도록 이진코드를 만드러야만 디코딩이 된다.  
`ex> a가 101일 때 b에는 1, 10, 101은 부여할수 없다.`

## 허프만 코드의 원리

- 허프만 트리를 만들어서 압축한다.

1. 압축할 파일을 스캔하여 각 문자의 빈도수를 계산 한다.
2. 빈도수를 우선순위로 최소힙(heap)을 구성한다.

3. 빈도수가 가장 작은 두 노드를 삭제한다.
4. 삭제한 두 노드 중에 작은 것을 왼쪽 자식노드, 큰것을 오른쪽 자식노드로 삽입한다.

5. 노드가 하나 남을 때까지 반복한다.
6. 마지막에 남은 노드가 루트가 된다.

- 따라서 빈도 수가 높은 문자에는 짧은 이진코드(하프만 코드)를 부여하고, 빈도수가 낮은 문자에는 긴 이진코드(하프만 코드)를 부여하여 한다.

### 허프만 트리 만드는 방법

1. 각 문자가 개별적인 트리인 상태에서 시작한다.
2. 빈도수가 작은 두 트리를 합쳐서 보다 큰 트리를 생성한다.
3. 위의 과정을 반복한다.

- 각 노드는 빈도수를 표시한다.
- 왼쪽 간선은 0, 오른쪽 간선은 1로 쓴다.
- 합쳐지는 두 트리는 자식노드를 갖는 부모노드를 생성한다.
- 부모노드의 빈도수는 두 자식 노드의 빈도수의 합이다.

<center><img src="https://t1.daumcdn.net/cfile/tistory/99D920395AE310302C"></center>

## 하프만 트리를 만드는 시간 + 길이가 m인 텍스트의 실제 인코딩 시간

O(n logn) + O(m) = O(n logn + m)

//_2022-04-13 김재범_

- 먼저, 허프만 함수 전에 함수들에 대해 간략히만 설명해보자면 InsertHeap함수는 히프에 새로운 요소를 삽입하는 삽입 연산이고, 삽입된 노드를 부모 노드와 비교하여 교환하는 식으로 전개된다.
- DeleteHeap은 히프의 삭제 연산이고, 루트 노드 삭제 후 마지막 노드를 가져오고 자식 노드와 비교해 교환하는 방식이다.
- MakeNode는 이진 트리를 생성하는 함수이고, DestroyTree는 이진 트리를 제거하는 함수이다. PrintTree는 1을 저장하고 순환호출하고, 0을 저장하고 순환호출하고, 단말노드이면 코드를 출력한다.
- (허프만 코드 설명)
- **main함수**에 대해 설명해보자면, 처음으로 문자열의 갯수 저장을 위한 변수와 존재하는 문자열의 갯수 저장을 위한 변수를 선언한다. 그리고 문자열을 입력받고 대문자로 변환하는 strupr함수를 사용하여 변환해준다.  
  이제 문자당 빈도수를 체크하기 위해 코드를 생각해보면 알파벳의 아스키 코드 값이 문자열 배열의 어떤 수와 같다면 i값의 알파벳이 존재하는 것이므로 앞에 선언한 flag에 1을 대입. 그리고 알파벳이 존재하므로 count를 증가시켜준다.  
  그런다음 count를 이용해 새로운 동적 메모리를 할당하여 copyData로 선언하고, 존재하는 문자만 복사하도록 가정문을 작성하면 문자당 빈도 수는 복사된배열의 알파벳값과 빈도수 값으로 출력되고, 허프만 압축 결과는 copyData와 count를 인수로 삼는 HuffmanTree함수를 이용하여 출력하면 된다.
