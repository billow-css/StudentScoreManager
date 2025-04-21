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

// ���� GPA �ĺ���
void GPA(HEAD *head) {
    NODE *current = head->next;
    while (current != NULL) {
        double total_credit_point = 0;
        double total_credits = 0;
        for (int i = 0; i < head->subject_count; i++) {
            double course_gpa = current->score[i] / 10 - 5;
            total_credit_point += course_gpa * head->subject_list[i].point;
            total_credits += head->subject_list[i].point;
        }
        if (total_credits > 0) {
            current->GPA = total_credit_point / total_credits;
        } else {
            current->GPA = 0;
        }
        current = current->next;
    }
}

int main() {
    // ��ʼ��ͷ�ڵ�
    HEAD *head = (HEAD *)malloc(sizeof(HEAD));
    strcpy(head->list_name, "Student List");
    head->student_count = 2;
    head->college_count = 0;
    head->subject_count = 2;

    // ��ʼ����Ŀ�б�
    head->subject_list = (SUBJECT *)malloc(head->subject_count * sizeof(SUBJECT));
    strcpy(head->subject_list[0].name, "Math");
    head->subject_list[0].point = 3.0;
    strcpy(head->subject_list[1].name, "English");
    head->subject_list[1].point = 2.0;

    // ��ʼ��ѧ���ڵ�
    NODE *student1 = (NODE *)malloc(sizeof(NODE));
    student1->id = 1;
    strcpy(student1->name, "Alice");
    strcpy(student1->student_id, "001");
    strcpy(student1->college_class_info, "C01");
    student1->score[0] = 80;
    student1->score[1] = 90;
    student1->next = NULL;

    NODE *student2 = (NODE *)malloc(sizeof(NODE));
    student2->id = 2;
    strcpy(student2->name, "Bob");
    strcpy(student2->student_id, "002");
    strcpy(student2->college_class_info, "C01");
    student2->score[0] = 70;
    student2->score[1] = 80;
    student2->next = NULL;

    // ���ӽڵ�
    head->next = student1;
    student1->next = student2;

    // ���� GPA ����
    GPA(head);

    // ���ÿ��ѧ���� GPA
    NODE *current = head->next;
    while (current != NULL) {
        printf("Student: %s, GPA: %.2f\n", current->name, current->GPA);
        current = current->next;
    }

    // �ͷ��ڴ�
    current = head->next;
    while (current != NULL) {
        NODE *temp = current;
        current = current->next;
        free(temp);
    }
    free(head->subject_list);
    free(head);

    return 0;
}

