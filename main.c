int main()
{
    AlphaType data[ALPHABET]; // ���ڿ��� ���� ������ ���� ����
    AlphaType *copyData;      // �����ϴ� ���ڿ��� ���� ������ ���� ����

    Init(data);

    char *str = (char *)malloc(sizeof(char) * MAX_LEN); // �޸� �Ҵ�

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

    copyData = (AlphaType *)malloc(sizeof(AlphaType) * count); // �޸� �Ҵ�

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