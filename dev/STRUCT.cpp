#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ����ģ��
#define FILE_MAX 10000
#define STR_MAX 1000
#define DEGITAL 10

// �ṹ��
// ��Ŀ�ṹ��
typedef struct SUBJECT
{
    int i;
    char name[STR_MAX];
    double point; // ����ѧ�ִ洢
} SUBJECT;

// ѧԺ�༶��Ϣ�ṹ��
typedef struct COLLEGE_CLASS_INFO
{
    char college_class_info[DEGITAL];
    char college_class_text[STR_MAX];
} COL_INFO;

// ͷ�ڵ�ṹ��
typedef struct HEAD
{
    char list_name[STR_MAX];
    int student_count;
    COL_INFO *college;
    SUBJECT *subject_list;
    int college_count;  // ��¼ѧԺ�༶��Ϣ������
    int subject_count;
    struct NODE *next;
} HEAD;

// �ڵ�ṹ��
typedef struct NODE
{
    int id;
    char name[STR_MAX];
    char student_id[STR_MAX];
    char college_class_info[DEGITAL];
    double score[STR_MAX];
    double GPA;
    double subject_point;
    int level;
    double ave;
    int fails;
    struct NODE *next;
} NODE;

// ��������(�Ժ�Ǩ�Ƶ�ͷ�ļ���)
/*--0.1--��������*/
void Error_report(int error_code);
/*--0.2--���뺯��*/
NODE *input(NODE *new_node, int id, int subject_count);
/*--1--�¼�����-�ֶ�¼��*/
HEAD *newlist(HEAD *header, SUBJECT *subject, COL_INFO *college, int subject_count, int college_count);
NODE *create_node(HEAD *header);
COL_INFO *create_college_array(int college_count);
SUBJECT *create_subject_array(int subject_count);
/*--2--��ʾ����*/
void print(HEAD *header);
/*--3.1--�ͷ�����*/
void free_whole_list(HEAD *header);
/*--3.2--ɾ�����ڵ�*/
void delete_single_node(HEAD *header, int location_code);
/*--4--��ѯ�ڵ���*/
void find_node_with_id(HEAD *header, int target_id); // ����id��ѯ�ڵ�
/*--5--�޸Ľڵ���*/
void change_single_node(HEAD *header, int target_location); // �޸ĵ����ڵ������
/*--6--�ļ��������*/
void output_to_file(HEAD *header, const char *filename);

// ��������
void Error_report(int error_code)
{
    /*
        ��������
        1-�ڴ����ʧ��
        2-�����ʽ����
        3-�ձ�� 
    */
    switch (error_code)
    {
    case 1:
        printf(">[x]>����code==0001���ڴ����ʧ�ܣ�\n");
        break;
    case 2:
        printf(">[x]>����code==0002�����������Ƿ�����\n");
        while (getchar() != '\n');
        break;
    case 3:
        printf(">[x]>����code==0003���ձ��\n");
        break;
    case 4:
        printf(">[x]>����code==0004��������ɳ�������Ϣ�����ڣ�\n");
        break; 
    default:
        break;
    }
}

NODE *input(NODE *new_node, int id, int subject_count)
{
    new_node->id = id;
    printf("������ѧ��������");
    fgets(new_node->name, STR_MAX, stdin);
    new_node->name[strcspn(new_node->name, "\n")] = 0; // ȥ�����з�
    printf("������ѧ��ѧ�ţ�");
    fgets(new_node->student_id, STR_MAX, stdin);
    new_node->student_id[strcspn(new_node->student_id, "\n")] = 0; // ȥ�����з�
    printf("������༶���룺");
    fgets(new_node->college_class_info, DEGITAL, stdin);
    new_node->college_class_info[strcspn(new_node->college_class_info, "\n")] = 0; // ȥ�����з�
    for (int i = 0; i < subject_count; i++) {
        int valid_input = 0;
        while (!valid_input) {
            printf("������� %d �ſεĳɼ���", i + 1);
            if (scanf("%lf", &new_node->score[i]) == 1) {
                valid_input = 1;
            } else {
                Error_report(2);
                while (getchar() != '\n');
            }
        }
        while (getchar() != '\n');
    }

    return new_node;
}

HEAD *newlist(HEAD *header, SUBJECT *subject, COL_INFO *college, int subject_count, int college_count)
{
    printf("��Ϊ�µ�����������\n");
    fgets(header->list_name, STR_MAX, stdin);
    header->list_name[strcspn(header->list_name, "\n")] = 0; // ȥ�����з�

    header->subject_count = subject_count;
    header->college_count = college_count;

    header->college = college;
    header->subject_list = subject;
    return header;
}

NODE *create_node(HEAD *header)
{
    NODE *new_node;
    NODE *temp_point;
    int id = 1;
    int student_count = 0;
    char choice;

    while (1) {
        new_node = (NODE *)malloc(sizeof(NODE));
        if (new_node == NULL) {
            Error_report(1);
            return NULL;
        }
        input(new_node, id, header->subject_count);
        if (student_count == 0) {
            new_node->next = NULL;
            header->next = new_node;
            temp_point = new_node;
        } else {
            new_node->next = NULL;
            temp_point->next = new_node;
            temp_point = new_node;
        }
        student_count++;
        id++;

        printf("�Ƿ����¼��ѧ����Ϣ��(Y/N): ");
        while (scanf(" %c", &choice) != 1 || (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')) {
            Error_report(2);
            printf("�Ƿ����¼��ѧ����Ϣ��(Y/N): ");
        }
        while (getchar() != '\n');

        if (choice == 'N' || choice == 'n') {
            break;
        }
    }

    header->student_count = student_count;
    return header->next;
}

COL_INFO *create_college_array(int college_count)
{
    COL_INFO *college = (COL_INFO *)malloc(college_count * sizeof(COL_INFO));
    if (college == NULL) {
        printf("�ڴ����ʧ�ܣ�\n");
        return NULL;
    }

    for (int i = 0; i < college_count; i++) {
        printf("������� %d ���༶�Ĵ���: ", i + 1);
        fgets(college[i].college_class_info, DEGITAL, stdin);
        college[i].college_class_info[strcspn(college[i].college_class_info, "\n")] = 0;

        printf("������� %d ���༶������: ", i + 1);
        fgets(college[i].college_class_text, STR_MAX, stdin);
        college[i].college_class_text[strcspn(college[i].college_class_text, "\n")] = 0;
    }

    return college;
}

SUBJECT *create_subject_array(int subject_count)
{
    SUBJECT *subject = (SUBJECT *)malloc(subject_count * sizeof(SUBJECT));
    if (subject == NULL) {
        printf("�ڴ����ʧ�ܣ�\n");
        return NULL;
    }

    for (int i = 0; i < subject_count; i++) {
        subject[i].i = i + 1;
        printf("������� %d ����Ŀ�����ƺ�ѧ�֣��ÿո�ָ�����", i + 1);
        while (scanf("%s %lf", subject[i].name, &subject[i].point) != 2) {
            Error_report(2);
            while (getchar() != '\n');
        }
        while (getchar() != '\n');
    }

    return subject;
}
// ... ֮ǰ�Ĵ��뱣�ֲ��� ...

void print(HEAD *header) {
    if (header == NULL) {
        Error_report(1);
        return;
    }
    // ���ͷ�ڵ�����
    printf("��������: %s\n", header->list_name);
    printf("ѧ������: %d\n", header->student_count);
    printf("�༶����: %d\n", header->college_count);
    printf("��Ŀ����: %d\n", header->subject_count);
    printf("��Ŀ�б�: ");
    for (int i = 0; i < header->subject_count; i++) {
        printf("%s(%.1fѧ��) ", header->subject_list[i].name, header->subject_list[i].point);
    }
    printf("\n");

    // ��������Ƿ�ֻ��ͷ���
    if (header->next == NULL) {
        Error_report(3);
        return;
    }

    // �����ͷ
    printf("| ID | ���� | ѧ�� | �༶ |");
    for (int i = 0; i < header->subject_count; i++) {
        printf(" %s |", header->subject_list[i].name);
    }
    printf(" GPA | ��ѧ�� | ���� | ƽ���� | �ҿ��� |\n");

    // ���ÿ���ڵ��������Ϣ
    NODE *current = header->next;
    while (current != NULL) {
        // ���Ұ༶����
        char *class_name = NULL;
        for (int i = 0; i < header->college_count; i++) {
            if (strcmp(current->college_class_info, header->college[i].college_class_info) == 0) {
                class_name = header->college[i].college_class_text;
                break;
            }
        }

        // ����ڵ������Ϣ
        printf("| %d | %s | %s | %s |", current->id, current->name, current->student_id, class_name);

        // ���ÿ����Ŀ�ĳɼ�
        for (int i = 0; i < header->subject_count; i++) {
            printf(" %.2f |", current->score[i]);
        }

        // ��� GPA����ѧ�֡�������ƽ���ֺ͹ҿ���
        printf(" %.2f | %.2f | %d | %.2f | %d |\n", current->GPA, current->subject_point, current->level, current->ave, current->fails);

        current = current->next;
    }
    printf("\n");
}
  
void free_whole_list(HEAD *header) {
    NODE *current = header->next;
    NODE *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    // �ͷŰ༶�Ϳ�Ŀ�����ڴ�
    if (header->college) {
        free(header->college);
    }
    if (header->subject_list) {
        free(header->subject_list);
    }
    free(header);
}

void delete_single_node(HEAD *header, int location_code) {
    NODE *prev_node, *guo_tang;
    int step;
    step = location_code - 1;
    prev_node = header->next;
    if (step > 0) {
        for (int i = 0; i < step; i++) {
            if (prev_node == NULL || prev_node->next == NULL) {
                return;
            }
            prev_node = prev_node->next;
        }
        guo_tang = prev_node->next;
        if (guo_tang != NULL) {
            prev_node->next = guo_tang->next;
            free(guo_tang);
        }
    } else if (step == 0) {
        if (prev_node != NULL) {
            header->next = prev_node->next;
            free(prev_node);
        }
    }
}    

void find_node_with_id(HEAD *header, int target_id) {
    NODE *current = header->next;
    while (current != NULL) {
        if (current->id == target_id) {
            printf("�ҵ��ڵ㣬ID: %d, ����: %s\n", current->id, current->name);
            return;
        }
        current = current->next;
    }
    printf("δ�ҵ� ID Ϊ %d �Ľڵ㡣\n", target_id);
}

void change_single_node(HEAD *header, int target_location) {
    NODE *current = header->next;
    int step = 1;
    while (current != NULL && step < target_location) {
        current = current->next;
        step++;
    }
    if (current == NULL) {
        printf("δ�ҵ�ָ��λ�õĽڵ㡣\n");
        return;
    }
    printf("��ǰ�ڵ���Ϣ��ID: %d, ����: %s, ѧ��: %s, �༶����: %s\n", current->id, current->name, current->student_id, current->college_class_info);
    int choice;
    do {
        printf("\n��ѡ��Ҫ�޸ĵ����ݣ�\n");
        printf("1. ����\n");
        printf("2. ѧ��\n");
        printf("3. �༶����\n");
        for (int i = 0; i < header->subject_count; i++) {
            printf("%d. ", i + 4);
            printf("%s�ɼ�\n", header->subject_list[i].name);
        }
        printf("0. �˳��޸�\n");
        printf("������ѡ�");
        while (scanf("%d", &choice) != 1) {
            Error_report(2);
            printf("������ѡ�");
        }
        while (getchar() != '\n');

        switch (choice) {
        case 1:
            printf("�������µ�ѧ��������");
            fgets(current->name, STR_MAX, stdin);
            current->name[strcspn(current->name, "\n")] = 0;
            break;
        case 2:
            printf("�������µ�ѧ��ѧ�ţ�");
            fgets(current->student_id, STR_MAX, stdin);
            current->student_id[strcspn(current->student_id, "\n")] = 0;
            break;
        case 3:
            printf("�������µİ༶���룺");
            fgets(current->college_class_info, DEGITAL, stdin);
            current->college_class_info[strcspn(current->college_class_info, "\n")] = 0;
            break;
        default:
            if (choice > 3 && choice <= 3 + header->subject_count) {
                int score_index = choice - 4;
                printf("������� %d �ſε��³ɼ���", score_index + 1);
                while (scanf("%lf", &current->score[score_index]) != 1) {
                    Error_report(2);
                    printf("������� %d �ſε��³ɼ���", score_index + 1);
                }
                while (getchar() != '\n');
            } else if (choice != 0) {
                printf("��Ч��ѡ����������롣\n");
            }
            break;
        }
    } while (choice != 0);
    printf("�ڵ���Ϣ�޸���ɡ�\n");
}

//// ���������ļ�
//int main() {
//    HEAD *header = (HEAD *)malloc(sizeof(HEAD));
//    if (header == NULL) {
//        Error_report(1);
//        return 1;
//    }
//
//    int college_count, subject_count;
//    // �����Ŀ����
//    printf("�����Ŀ������");
//    scanf("%d", &subject_count);
//    while (getchar() != '\n'); // ����������Ļ��з�
//
//    // ����༶����
//    printf("����༶������");
//    scanf("%d", &college_count);
//    while (getchar() != '\n'); // ����������Ļ��з�
//
//    SUBJECT *subject = create_subject_array(subject_count);
//    if (subject == NULL) {
//        Error_report(1);
//        free(header);
//        return 1;
//    }
//
//    COL_INFO *college = create_college_array(college_count);
//    if (college == NULL) {
//        Error_report(1);
//        free(subject);
//        free(header);
//        return 1;
//    }
//
//    // ��ʼ������
//    header = newlist(header, subject, college, subject_count, college_count);
//
//    // ����ѧ���ڵ�����
//    create_node(header);
//
//    // ��ʾ����
//    printf("������ɺ������\n");
//    print(header);
//
//    // ʾ�����޸ĵ� 2 ���ڵ������
//    change_single_node(header, 1);
//    printf("�޸ĺ������\n");
//    print(header);
//
//    // ʾ�������� ID Ϊ 3 �Ľڵ�
//    find_node_with_id(header, 3);
//    printf("���ҽڵ�������\n");
//    print(header);  // ������ʾ�������
//
//    // ʾ����ɾ���� 1 ���ڵ�
//    delete_single_node(header, 1);
//    printf("ɾ���ڵ�������\n");
//    print(header);
//
//    // �ͷ�����
//    free_whole_list(header);
//
//    return 0;
//}
