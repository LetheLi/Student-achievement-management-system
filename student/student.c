/*
 * ./1.txt �� ./2.txt����ѧ����Ϣ
 * ./3.txt ��./1.txt �� ./2.txt����Ϣ���кϲ�����������
 * ./4.txt���гɼ��������ѧ������
 *
 * ����Ŀʹ�ýṹ�壬�������ַ������
 * �� 1 �����Ϊ�ṹ�巽��
 * �� 2 �����Ϊ������
 * */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

struct Student {
    char name[10];
    int num;
    int ch;
    int ma;
    int en;
    int all;
} s[100];

struct Node {
    struct Student student;
    struct Node *next;
};

char file[5][30] = {{},
                    {"./1.txt"},
                    {"./2.txt"},
                    {"./3.txt"},
                    {"./4.txt"}};

void menu(int i);

void menu_1();

void StudentIn(int i, int count_1, int count_2);

int Read(int i);

void Write(int i);

void AllWrite();

void Sort();

void Sort_1(int i);

void Sort_2(int begin, int end);

void Fail();

void Select();

void Fail_Output();

void Delete();

void Revamp();

int st_Read(int i, struct Node *head);

void st_StudentIn(struct Node *head, int i);

void st_AllWrite(struct Node *head);

void st_Sort(struct Node *head);

void st_Fail(struct Node *head);

void st_Menu(struct Node *head);

void st_Select(struct Node *head);

void st_Save(struct Node *head, int i);

void st_Fail_Output(struct Node *head);

void st_Delete(struct Node *head);

void st_Revamp(struct Node *head);

int main() {
    int i;
    printf("ʹ�ýṹ�壨1����������2����");
    scanf("%d", &i);
    menu(i);
    getchar();
}

void menu(int i) {
    int n;
    while (1) {
        printf("1.���ļ������ѧ��\n");
        printf("2.��ѯѧ����Ϣ\n");
        printf("3.�鿴������ѧ����Ϣ\n");
        printf("4.ɾ��ѧ����Ϣ\n");
        printf("5.�޸�ѧ����Ϣ\n");
        printf("6.�˳�����\n");
        printf("���������:");
        scanf("%d", &n);
        printf("\n");
        if (n == 6) {
            system("pause");
            return;
        }
        if (i == 1) {
            switch (n) {
                case 1:
                    menu_1();
                    break;
                case 2:
                    Select();
                    break;
                case 3:
                    Fail_Output();
                    break;
                case 4:
                    Delete();
                    break;
                case 5:
                    Revamp();
                    break;
            }
        } else if (i == 2) {
            struct Node *head = (struct Node *) malloc(sizeof(struct Node));
            memset(head, 0, sizeof(struct Student));
            head->next = NULL;
            switch (n) {
                case 1:
                    st_Menu(head);
                    st_AllWrite(head);
                    break;
                case 2:
                    st_Select(head);
                    break;
                case 3:
                    st_Fail(head);
                    st_Fail_Output(head);
                    break;
                case 4:
                    st_Delete(head);
                    break;
                case 5:
                    st_Revamp(head);
            }
        }
    }
}

void menu_1() {
    int count;
    char ch;
    printf("�����ļ�1�����ļ�2��1 or 2):");
    scanf("%d", &count);
    Write(count);
    printf("�Ƿ�༭%s�ļ�(y or n)", file[-count + 3]);
    gets(&ch);
    scanf("%c", &ch);
    if (ch == 'y')
        Write(-count + 3);
    AllWrite();
    Fail();
}

void Write(int i) {
    int count_1, count_2;
    if (access(file[i], F_OK) != 0) {
        //�Ƿ����file[i]
        FILE *fp = fopen(file[i], "w");
        fclose(fp);
    }
    printf("����%s��д�뼸��ѧ����Ϣ��", file[i]);
    scanf("%d", &count_2);
    count_1 = Read(i);
    for (int j = 0; j < count_1; ++j) {
        printf("%s\t%d\t%d\t%d\t%d\n", s[j].name, s[j].num, s[j].ch, s[j].ma, s[j].en);
    }
    StudentIn(i, count_1, count_2);
}

int Read(int i) {
    int j = 0;
    FILE *fp = fopen(file[i], "r+");
    if (fgetc(fp) == EOF) {
        return 0;
    } else {
        fseek(fp, -1, 1);
        fscanf(fp, "name\tnum\tChinese\tMath\tEnglish\n");
        while (fgetc(fp) != EOF) {
            fseek(fp, -1, 1);
            fscanf(fp, "%s\t%d\t%d\t%d\t%d\n", &s[j].name, &s[j].num, &s[j].ch, &s[j].ma, &s[j].en);
            j++;
        }
        fclose(fp);
    }
    return j;
}

void StudentIn(int i, int count_1, int count_2) {
    int j = count_1;
    FILE *fp = fopen(file[i], "a+");
    if (count_1 == 0) {
        fprintf(fp, "name\tnum\tChinese\tMath\tEnglish\n");
    }
    label_1:
    while (j < count_2 + count_1) {
        printf("������ѧ��ѧ��:");
        scanf("%d", &s[j].num);
        for (int k = 0; k < count_1; k++) {
            if (s[k].num == s[j].num) {
                printf("��ѧ���Ѵ��ڣ����������룺");
                goto label_1;
            }
        }
        printf("������ѧ������:");
        scanf("%s", &s[j].name);
        printf("������ѧ������:");
        scanf("%d", &s[j].ch);
        printf("������ѧ����ѧ:");
        scanf("%d", &s[j].ma);
        printf("������ѧ��Ӣ��:");
        scanf("%d", &s[j].en);
        fprintf(fp, "%s\t%d\t%d\t%d\t%d\n", s[j].name, s[j].num, s[j].ch, s[j].ma, s[j].en);
        ++j;
    }
    fclose(fp);
}

void AllWrite() {
    int i;
    i = Read(1);
    FILE *fp = fopen(file[3], "w");
    fprintf(fp, "name\tnum\tChinese\tMath\tEnglish\n");
    for (int j = 0; j < i; ++j) {
        fprintf(fp, "%s\t%d\t%d\t%d\t%d\n", s[j].name, s[j].num, s[j].ch, s[j].ma, s[j].en);
    }
    i = Read(2);
    for (int j = 0; j < i; ++j) {
        fprintf(fp, "%s\t%d\t%d\t%d\t%d\n", s[j].name, s[j].num, s[j].ch, s[j].ma, s[j].en);
    }
    fclose(fp);
}

void Sort() {
    int i;
    i = Read(3);
    for (int j = 0; j < i; ++j) {
        s[j].all = s[j].ch + s[j].ma + s[j].en;
    }
    int a = rand() % 2;
    if (a == 1) {
        Sort_1(i);
    } else {
        Sort_2(0, i);
    }
    FILE *fp = fopen(file[3], "w");
    fprintf(fp, "name\tnum\tChinese\tMath\tEnglish\n");
    for (int j = 0; j < i; ++j) {
        fprintf(fp, "%s\t%d\t%d\t%d\t%d\n", s[j].name, s[j].num, s[j].ch, s[j].ma, s[j].en);
    }
    fclose(fp);
}

void Sort_1(int i) {
    struct Student all;
    for (int j = 0; j < i - 1; ++j) {
        for (int k = j + 1; k < i; ++k) {
            if (s[j].all < s[k].all) {
                all = s[j];
                s[j] = s[k];
                s[k] = all;
            }
        }
    }
}

void Sort_2(int begin, int end) {
    struct Student all;
    if (begin >= end)
        return;
    int left = begin;
    int right = end;
    int keyi = begin;
    while (begin < end) {
        while (s[end].all >= s[keyi].all && begin < end) {
            --end;
        }
        while (s[begin].all <= s[keyi].all && begin < end) {
            ++begin;
        }
        all = s[begin];
        s[begin] = s[end];
        s[end] = all;
    }
    all = s[keyi];
    s[keyi] = s[end];
    s[end] = all;
    keyi = end;
    Sort_2(left, keyi - 1);
    Sort_2(keyi + 1, right);
}

void Fail() {
    int i;
    i = Read(3);
    FILE *fp = fopen(file[4], "w");
    fprintf(fp, "name\tnum\tChinese\tMath\tEnglish\n");
    for (int j = 0; j < i; ++j) {
        if (s[j].ch < 60 || s[j].ma < 60 || s[j].en < 60)
            fprintf(fp, "%s\t%d\t%d\t%d\t%d\n", s[j].name, s[j].num, s[j].ch, s[j].ma, s[j].en);
    }
    fclose(fp);
}

void Select() {
    char name[10];
    int i, flag = 0;
    printf("�������ѯѧ��������:");
    scanf("%s", &name);
    i = Read(3);
    for (int j = 0; j < i; ++j) {
        if (0 == strcmp(name, s[j].name)) {
            printf("%s\t%d\t%d\t%d\t%d\n", s[j].name, s[j].num, s[j].ch, s[j].ma, s[j].en);
            flag = 1;
            return;
        }
    }
    if (flag == 0)
        printf("���޴���\n");
}

void Fail_Output() {
    int i = Read(4);
    for (int j = 0; j < i; ++j) {
        printf("%s\t%d\t%d\t%d\t%d\n", s[j].name, s[j].num, s[j].ch, s[j].ma, s[j].en);
    }
}

void Delete() {
    int num, flag = 0, i = 1;
    getchar();
    printf("��������Ҫɾ����ѧ����ѧ��:");
    scanf("%d", &num);
    while (i <= 2) {
        int a = Read(i);
        for (int j = 0; j < a; ++j) {
            if (s[j].num == num) {
                getchar();
                printf("��Ҫɾ��ѧ�������Ƿ�Ϊ%s(y or n):", s[j].name);
                char c;
                scanf("%c", &c);
                if (c == 'y') {
                    for (int k = j; k < a - 1; ++k) {
                        s[k] = s[k + 1];
                    }
                    FILE *fp = fopen(file[i], "w");
                    fprintf(fp, "name\tnum\tChinese\tMath\tEnglish\n");
                    for (int q = 0; q < a - 1; ++q) {
                        fprintf(fp, "%s\t%d\t%d\t%d\t%d\n", s[q].name, s[q].num, s[q].ch, s[q].ma, s[q].en);
                    }
                    fclose(fp);
                    AllWrite();
                    Fail();
                    return;
                }
            }
        }
        i++;
    }
}

void Revamp() {
    struct Student re;
    int j = 0, q = Read(1);
    printf("��������Ҫ�޸�ѧ��������:");
    scanf("%s", &re.name);
    for (int i = 0; i < q; ++i) {
        if (!strcmp(s[i].name, re.name)) {
            printf("�������޸ĺ�ѧ����Ϣ:\n");
            printf("������ѧ������:");
            scanf("%s", &s[i].name);
            printf("������ѧ��ѧ��:");
            scanf("%d", &s[i].num);
            printf("���������ĳɼ�:");
            scanf("%d", &s[i].ch);
            printf("��������ѧ�ɼ�:");
            scanf("%d", &s[i].ma);
            printf("������Ӣ��ɼ�:");
            scanf("%d", &s[i].en);
            j = 1;
            FILE *fp = fopen(file[1], "w");
            fprintf(fp, "name\tnum\tChinese\tMath\tEnglish\n");
            for (int k = 0; k < q; ++k) {
                fprintf(fp, "%s\t%d\t%d\t%d\t%d\n", s[k].name, s[k].num, s[k].ch, s[k].ma, s[k].en);
            }
            fclose(fp);
            break;
        }
    }

    if (j != 1) {
        q = Read(2);
        for (int i = 0; i < q; ++i) {
            if (!strcmp(s[i].name, re.name)) {
                printf("�������޸ĺ�ѧ����Ϣ:");
                printf("������ѧ������:");
                scanf("%s", &s[i].name);
                printf("������ѧ��ѧ��:");
                scanf("%d", &s[i].num);
                printf("���������ĳɼ�:");
                scanf("%d", &s[i].ch);
                printf("��������ѧ�ɼ�:");
                scanf("%d", &s[i].ma);
                printf("������Ӣ��ɼ�:");
                scanf("%d", &s[i].en);
                j = 1;
                FILE *fp = fopen(file[2], "w");
                fprintf(fp, "name\tnum\tChinese\tMath\tEnglish\n");
                for (int k = 0; k < q; ++k) {
                    fprintf(fp, "%s\t%d\t%d\t%d\t%d\n", s[k].name, s[k].num, s[k].ch, s[k].ma, s[k].en);
                }
                fclose(fp);
                break;
            }
        }
    }
    if (j != 1) {
        printf("���޴��ˣ�\n");
        return;
    }
    printf("%d\n", j);
    AllWrite();
    Fail();
}

void st_Menu(struct Node *head) {
    int count;
    char ch;
    printf("�����ļ�1�����ļ�2��1 or 2):");
    scanf("%d", &count);
    st_Read(count, head);
    st_StudentIn(head, count);
}

int st_Read(int i, struct Node *head) {
    struct Node *end = head;
    int j = 0;
    if (access(file[i], F_OK) == 0) {
        //�Ƿ����file[i]
    } else {
        FILE *fp = fopen(file[i], "w");
        fclose(fp);
    }
    FILE *fp = fopen(file[i], "a+");
    if (fgetc(fp) == EOF) {
        fclose(fp);
        return 0;
    } else {
        fseek(fp, -1, 1);
        fscanf(fp, "name\tnum\tChinese\tMath\tEnglish\n");
        while (fgetc(fp) != EOF) {
            fseek(fp, -1, 1);
            struct Node *new3 = (struct Node *) malloc(sizeof(struct Node));
            fscanf(fp, "%s\t%d\t%d\t%d\t%d\n", new3->student.name, &new3->student.num, &new3->student.ch,
                   &new3->student.ma, &new3->student.en);
            new3->next = NULL;
            end->next = new3;
            end = new3;
            j++;
        }
        fclose(fp);
    }
    return j;
}

void st_StudentIn(struct Node *head, int i) {
    int count_2, flag = 0, j = 0;
    char ch;
    struct Node *temp = head;

    printf("����%s��д�뼸��ѧ����Ϣ:", file[i]);
    scanf("%d", &count_2);
    label:
    while (j < count_2) {
        struct Node *new1 = (struct Node *) malloc(sizeof(struct Node));
        printf("������ѧ��ѧ��:");
        scanf("%d", &new1->student.num);
        struct Node *temp_1 = head;
        while (temp_1 != NULL) {
            if (temp_1->student.num == new1->student.num) {
                printf("��ѧ���Ѵ��ڣ����������롣\n");
                goto label;
            }
            temp_1 = temp_1->next;
        }
        printf("������ѧ������:");
        scanf("%s", new1->student.name);
        printf("������ѧ������:");
        scanf("%d", &new1->student.ch);
        printf("������ѧ����ѧ:");
        scanf("%d", &new1->student.ma);
        printf("����ѧ��Ӣ��:");
        scanf("%d", &new1->student.en);
        new1->next = NULL;
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new1;
        j++;
    }
    st_Save(head, i);
}

void st_AllWrite(struct Node *head) {
    struct Node *end = head;
    int j = 1, count = 0;
    while (j <= 2) {
        FILE *fp = fopen(file[j], "a+");
        fseek(fp, -1, 1);
        fscanf(fp, "name\tnum\tChinese\tMath\tEnglish\n");
        while (fgetc(fp) != EOF) {
            fseek(fp, -1, 1);
            struct Node *new3 = (struct Node *) malloc(sizeof(struct Node));
            fscanf(fp, "%s\t%d\t%d\t%d\t%d\n", new3->student.name, &new3->student.num, &new3->student.ch,
                   &new3->student.ma, &new3->student.en);
            new3->next = NULL;
            end->next = new3;
            end = new3;
            count++;
        }
        fclose(fp);
        j++;
    }
    FILE *fp = fopen(file[3], "w");
    struct Node *end_1 = head->next;
    fprintf(fp, "name\tnum\tChinese\tMath\tEnglish\n");
    for (j = 0; j < count; ++j) {
        fprintf(fp, "%s\t%d\t%d\t%d\t%d\n", end_1->student.name, end_1->student.num, end_1->student.ch,
                end_1->student.ma, end_1->student.en);
        end_1 = end_1->next;
    }

    fclose(fp);
}

void st_Sort(struct Node *head) {
    int i = st_Read(3, head);
    struct Node *temp = head->next;
    struct Node *temp1 = head->next;
    struct Node *temp2;
    struct Student stu;
    for (; temp1->next != NULL; temp1 = temp1->next) {
        for (temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next) {
            temp1->student.all = temp1->student.ch + temp1->student.ma + temp1->student.en;
            temp2->student.all = temp2->student.ch + temp2->student.ma + temp2->student.en;
            if (temp1->student.all < temp2->student.all) {
                stu = temp1->student;
                temp1->student = temp2->student;
                temp2->student = stu;
            }
        }
    }
    FILE *fp = fopen(file[3], "w");
    fprintf(fp, "name\tnum\tChinese\tMath\tEnglish\n");
    while (temp != NULL) {
        fprintf(fp, "%s\t%d\t%d\t%d\t%d\n", temp->student.name, temp->student.num, temp->student.ch, temp->student.ma,
                temp->student.en);
        temp = temp->next;
    }
    fclose(fp);
}

void st_Fail(struct Node *head) {
    st_Read(3, head);
    struct Node *temp = head->next;
    FILE *fp = fopen(file[4], "w");
    fprintf(fp, "name\tnum\tChinese\tMath\tEnglish\n");
    while (temp != NULL) {
        if (temp->student.ch < 60 || temp->student.ma < 60 || temp->student.en < 60) {
            fprintf(fp, "%s\t%d\t%d\t%d\t%d\n", temp->student.name, temp->student.num, temp->student.ch,
                    temp->student.ma, temp->student.en);
        }
        temp = temp->next;
    }
    fclose(fp);
}

void st_Select(struct Node *head) {
    st_Read(3, head);
    struct Node *temp = head->next;
    char name[10] = {0};
    int i, flag = 0;
    printf("�������ѯѧ��������:");
    scanf("%s", name);
    while (temp != NULL) {
        if (0 == strcmp(name, temp->student.name)) {
            printf("%s\t%d\t%d\t%d\t%d\n", temp->student.name, temp->student.num, temp->student.ch, temp->student.ma,
                   temp->student.en);
            flag = 1;
        }
        temp = temp->next;
    }
    if (flag == 0)
        printf("���޴���\n");
}

void st_Save(struct Node *head, int i) {
    FILE *fp = fopen(file[i], "w+");
    fprintf(fp, "name\tnum\tChinese\tMath\tEnglish\n");
    struct Node *temp = head->next;
    while (temp != NULL) {
        fprintf(fp, "%s\t%d\t%d\t%d\t%d\n", temp->student.name, temp->student.num, temp->student.ch, temp->student.ma,
                temp->student.en);
        temp = temp->next;
    }
    fclose(fp);
}

void st_Fail_Output(struct Node *head) {
    st_Read(4, head);
    struct Node *end_1 = head->next;
    for (; end_1 != NULL; end_1 = end_1->next) {
        printf("%s\t%d\t%d\t%d\t%d\n", end_1->student.name, end_1->student.num, end_1->student.ch,
               end_1->student.ma, end_1->student.en);
    }
}

void st_Delete(struct Node *head) {
    int i = 1, num;
    char flag;
    getchar();
    printf("��������Ҫɾ����ѧ����ѧ��:");
    scanf("%d", &num);
    while (i <= 2) {
        st_Read(i, head);
        struct Node *end = head;
        struct Node *end_1 = head->next;
        while (end_1) {
            if (end_1->student.num == num) {
                getchar();
                printf("����ɾ��ѧ�������Ƿ�Ϊ��%s(y or n)", end_1->student.name);
                scanf("%c", &flag);
                //getchar();
                if (flag == 'y') {
                    end->next = end_1->next;
                    st_Save(head, i);
                    st_AllWrite(head);
                    st_Fail(head);
                    return;
                }
            }
            end = end_1;
            end_1 = end_1->next;
        }
        i++;
    }
    printf("���޴���\n");
}

void st_Revamp(struct Node *head) {
    int k = st_Read(1, head), i, flag = 0;
    struct Node *temp = head->next;
    char name[10] = {0};
    printf("��������Ҫ�޸�ѧ��������:");
    scanf("%s", name);
    while (temp != NULL) {
        if (0 == strcmp(name, temp->student.name)) {
            printf("������ѧ������:");
            scanf("%s", temp->student.name);
            printf("������ѧ��ѧ��:");
            scanf("%d", &temp->student.num);
            printf("������ѧ������:");
            scanf("%d", &temp->student.ch);
            printf("������ѧ����ѧ:");
            scanf("%d", &temp->student.ma);
            printf("����ѧ��Ӣ��:");
            scanf("%d", &temp->student.en);
            flag = 1;
            temp = head->next;
            FILE *fp = fopen(file[1], "w");
            fprintf(fp, "name\tnum\tChinese\tMath\tEnglish\n");
            for (int j = 0; j < k; ++j) {
                fprintf(fp, "%s\t%d\t%d\t%d\t%d\n", temp->student.name, temp->student.num, temp->student.ch,
                        temp->student.ma, temp->student.en);
                temp = temp->next;
            }
            fclose(fp);
            break;
        }
        temp = temp->next;
    }
    if (flag != 1) {
        k = st_Read(2, head);
        temp = head->next;
        while (temp != NULL) {
            if (0 == strcmp(name, temp->student.name)) {
                printf("������ѧ������:");
                scanf("%s", temp->student.name);
                printf("������ѧ��ѧ��:");
                scanf("%d", &temp->student.num);
                printf("������ѧ������:");
                scanf("%d", &temp->student.ch);
                printf("������ѧ����ѧ:");
                scanf("%d", &temp->student.ma);
                printf("����ѧ��Ӣ��:");
                scanf("%d", &temp->student.en);
                flag = 1;
                temp = head->next;
                FILE *fp = fopen(file[2], "w");
                fprintf(fp, "name\tnum\tChinese\tMath\tEnglish\n");
                for (int j = 0; j < k; ++j) {
                    fprintf(fp, "%s\t%d\t%d\t%d\t%d\n", temp->student.name, temp->student.num, temp->student.ch,
                            temp->student.ma, temp->student.en);
                    temp = temp->next;
                }
                fclose(fp);
                break;
            }
            temp = temp->next;
        }
    }
    if (flag != 1) {
        printf("���޴���\n");
        return;
    }
    st_AllWrite(head);
    st_Fail(head);
}