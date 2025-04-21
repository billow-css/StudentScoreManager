#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 常数模块
#define FILE_MAX 10000
#define STR_MAX 1000
#define DEGITAL 10

// 结构体
// 科目结构体
typedef struct SUBJECT
{
    int i;
    char name[STR_MAX];
    double point; // 新增学分存储
} SUBJECT;

// 学院班级信息结构体
typedef struct COLLEGE_CLASS_INFO
{
    char college_class_info[DEGITAL];
    char college_class_text[STR_MAX];
} COL_INFO;

// 头节点结构体
typedef struct HEAD
{
    char list_name[STR_MAX];
    int student_count;
    COL_INFO *college;
    SUBJECT *subject_list;
    int college_count;  // 记录学院班级信息的数量
    int subject_count;
    struct NODE *next;
} HEAD;

// 节点结构体
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

// 计算 GPA 的函数
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
    // 初始化头节点
    HEAD *head = (HEAD *)malloc(sizeof(HEAD));
    strcpy(head->list_name, "Student List");
    head->student_count = 2;
    head->college_count = 0;
    head->subject_count = 2;

    // 初始化科目列表
    head->subject_list = (SUBJECT *)malloc(head->subject_count * sizeof(SUBJECT));
    strcpy(head->subject_list[0].name, "Math");
    head->subject_list[0].point = 3.0;
    strcpy(head->subject_list[1].name, "English");
    head->subject_list[1].point = 2.0;

    // 初始化学生节点
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

    // 连接节点
    head->next = student1;
    student1->next = student2;

    // 调用 GPA 函数
    GPA(head);

    // 输出每个学生的 GPA
    NODE *current = head->next;
    while (current != NULL) {
        printf("Student: %s, GPA: %.2f\n", current->name, current->GPA);
        current = current->next;
    }

    // 释放内存
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

