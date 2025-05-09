#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STR_MAX 1000
#define DEGITAL 10

// ѧԺ�༶��Ϣ�ṹ��
typedef struct COLLEGE_CLASS_INFO {
    char college_class_info[DEGITAL];
    char college_class_text[STR_MAX];
} COL_INFO;

// ͷ�ڵ�ṹ��
typedef struct HEAD {
    char list_name[STR_MAX];
    int student_count;
    COL_INFO *college;
    int college_count;  // ��¼ѧԺ�༶��Ϣ������
    struct NODE *next;
} HEAD;

// �ڵ�ṹ��
typedef struct NODE {
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
} NODE;

// ��ӡ�༶��Ϣ�ĺ���
void print_college_classes(HEAD *head) {
    for (int i = 0; i < head->college_count; i++) {
        printf("%s %s\n", head->college[i].college_class_info, head->college[i].college_class_text);
    }
}

//int main() {
//    HEAD head;
//    strcpy(head.list_name, "�༶��Ϣ�б�");
//    head.student_count = 0;
//    head.college_count = 8;  // ��ʼ��ѧԺ�༶��Ϣ������
//
//    // ��̬�����ڴ�
//    head.college = (COL_INFO *)malloc(head.college_count * sizeof(COL_INFO));
//    if (head.college == NULL) {
//        fprintf(stderr, "Memory allocation failed\n");
//        return 1;
//    }
//
//    // ��ʼ�����ְ༶��Ϣ
//    strcpy(head.college[0].college_class_info, "10-");
//    strcpy(head.college[0].college_class_text, "�������");
//    strcpy(head.college[1].college_class_info, "1001");
//    strcpy(head.college[1].college_class_text, "�������1��");
//    strcpy(head.college[2].college_class_info, "1002");
//    strcpy(head.college[2].college_class_text, "�������2��");
//    strcpy(head.college[3].college_class_info, "1099");
//    strcpy(head.college[3].college_class_text, "��Ѷ������������");
//    strcpy(head.college[4].college_class_info, "11-");
//    strcpy(head.college[4].college_class_text, "������");
//    strcpy(head.college[5].college_class_info, "1101");
//    strcpy(head.college[5].college_class_text, "������1��");
//    strcpy(head.college[6].college_class_info, "23-");
//    strcpy(head.college[6].college_class_text, "����ѧԺ���ĵ���");
//    strcpy(head.college[7].college_class_info, "2301");
//    strcpy(head.college[7].college_class_text, "���ĵ���1��");
//
//    // ��ӡ�༶��Ϣ
//    print_college_classes(&head);
//
//    // �ͷŶ�̬������ڴ�
//    free(head.college);
//
//    return 0;
//}
