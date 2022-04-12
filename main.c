int main()
{
    AlphaType data[ALPHABET]; // 문자열의 갯수 저장을 위한 변수
    AlphaType *copyData;      // 존재하는 문자열의 갯수 저장을 위한 변수

    Init(data);

    char *str = (char *)malloc(sizeof(char) * MAX_LEN); // 메모리 할당

    int i, j, k = 0;
    int flag, count = 0;

    printf("공백을 제외한 문자열을 입력하세요 : ");
    scanf("%s", str);

    strupr(str); // 모든 문자를 대문자로 변환

    for (i = 'A'; i <= 'Z'; i++)
    {
        flag = 0;
        for (j = 0; j < strlen(str); j++)
        {
            if (i == str[j])
            {
                data[i - 65].freq++;
                flag = 1; // i값의 알파벳이 존재
            }
        }
        if (flag == 1)
            count++; // 알파벳이 존재하므로 카운터 증가
    }

    copyData = (AlphaType *)malloc(sizeof(AlphaType) * count); // 메모리 할당

    for (i = 0; i < ALPHABET; i++)
    {
        if (data[i].freq != '\0') // 존재하는 문자만 복사
        {
            copyData[k].alpha = i + 65;
            copyData[k].freq = data[i].freq;
            k++;
        }
    }

    printf("\n- 문자당 빈도 수 -\n");
    for (i = 0; i < count; i++)
        printf("%3c\t%3d \n", copyData[i].alpha, copyData[i].freq);

    printf("\n- 허프만 압축 결과 -\n");
    HuffmanTree(copyData, count);

    free(str);
    free(copyData);

    return 0;
}