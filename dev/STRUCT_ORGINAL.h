#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STR_MAX 1000
#define DEGITAL 10

// 学院班级信息结构体
typedef struct COLLEGE_CLASS_INFO {
    char college_class_info[DEGITAL];
    char college_class_text[STR_MAX];
} COL_INFO;

// 头节点结构体
typedef struct HEAD {
    char list_name[STR_MAX];
    int student_count;
    COL_INFO *college;
    int college_count;  // 记录学院班级信息的数量
    struct NODE *next;
} HEAD;

// 节点结构体
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

// 打印班级信息的函数
void print_college_classes(HEAD *head) {
    for (int i = 0; i < head->college_count; i++) {
        printf("%s %s\n", head->college[i].college_class_info, head->college[i].college_class_text);
    }
}

//int main() {
//    HEAD head;
//    strcpy(head.list_name, "班级信息列表");
//    head.student_count = 0;
//    head.college_count = 8;  // 初始化学院班级信息的数量
//
//    // 动态分配内存
//    head.college = (COL_INFO *)malloc(head.college_count * sizeof(COL_INFO));
//    if (head.college == NULL) {
//        fprintf(stderr, "Memory allocation failed\n");
//        return 1;
//    }
//
//    // 初始化部分班级信息
//    strcpy(head.college[0].college_class_info, "10-");
//    strcpy(head.college[0].college_class_text, "计算机类");
//    strcpy(head.college[1].college_class_info, "1001");
//    strcpy(head.college[1].college_class_text, "计算机类1班");
//    strcpy(head.college[2].college_class_info, "1002");
//    strcpy(head.college[2].college_class_text, "计算机类2班");
//    strcpy(head.college[3].college_class_info, "1099");
//    strcpy(head.college[3].college_class_text, "腾讯计算机类联培班");
//    strcpy(head.college[4].college_class_info, "11-");
//    strcpy(head.college[4].college_class_text, "物联网");
//    strcpy(head.college[5].college_class_info, "1101");
//    strcpy(head.college[5].college_class_text, "物联网1班");
//    strcpy(head.college[6].college_class_info, "23-");
//    strcpy(head.college[6].college_class_text, "长望学院人文地理");
//    strcpy(head.college[7].college_class_info, "2301");
//    strcpy(head.college[7].college_class_text, "人文地理1班");
//
//    // 打印班级信息
//    print_college_classes(&head);
//
//    // 释放动态分配的内存
//    free(head.college);
//
//    return 0;
//}
