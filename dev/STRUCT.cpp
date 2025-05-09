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

// 函数申明(稍后迁移到头文件中)
/*--0.1--报错函数组*/
void Error_report(int error_code);
/*--0.2--输入函数*/
NODE *input(NODE *new_node, int id, int subject_count);
/*--1--新键链表-手动录入*/
HEAD *newlist(HEAD *header, SUBJECT *subject, COL_INFO *college, int subject_count, int college_count);
NODE *create_node(HEAD *header);
COL_INFO *create_college_array(int college_count);
SUBJECT *create_subject_array(int subject_count);
/*--2--显示链表*/
void print(HEAD *header);
/*--3.1--释放链表*/
void free_whole_list(HEAD *header);
/*--3.2--删除单节点*/
void delete_single_node(HEAD *header, int location_code);
/*--4--查询节点组*/
void find_node_with_id(HEAD *header, int target_id); // 按照id查询节点
/*--5--修改节点组*/
void change_single_node(HEAD *header, int target_location); // 修改单个节点的数据
/*--6--文件输出函数*/
void output_to_file(HEAD *header, const char *filename);

// 函数定义
void Error_report(int error_code)
{
    /*
        报错代码表：
        1-内存分配失败
        2-输入格式有误
        3-空表格 
    */
    switch (error_code)
    {
    case 1:
        printf(">[x]>报错（code==0001）内存分配失败！\n");
        break;
    case 2:
        printf(">[x]>报错（code==0002）请检查输入是否有误！\n");
        while (getchar() != '\n');
        break;
    case 3:
        printf(">[x]>报错（code==0003）空表格\n");
        break;
    case 4:
        printf(">[x]>报错（code==0004）表格生成出错！表信息不存在！\n");
        break; 
    default:
        break;
    }
}

NODE *input(NODE *new_node, int id, int subject_count)
{
    new_node->id = id;
    printf("请输入学生姓名：");
    fgets(new_node->name, STR_MAX, stdin);
    new_node->name[strcspn(new_node->name, "\n")] = 0; // 去除换行符
    printf("请输入学生学号：");
    fgets(new_node->student_id, STR_MAX, stdin);
    new_node->student_id[strcspn(new_node->student_id, "\n")] = 0; // 去除换行符
    printf("请输入班级代码：");
    fgets(new_node->college_class_info, DEGITAL, stdin);
    new_node->college_class_info[strcspn(new_node->college_class_info, "\n")] = 0; // 去除换行符
    for (int i = 0; i < subject_count; i++) {
        int valid_input = 0;
        while (!valid_input) {
            printf("请输入第 %d 门课的成绩：", i + 1);
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
    printf("请为新的链表命名：\n");
    fgets(header->list_name, STR_MAX, stdin);
    header->list_name[strcspn(header->list_name, "\n")] = 0; // 去除换行符

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

        printf("是否继续录入学生信息？(Y/N): ");
        while (scanf(" %c", &choice) != 1 || (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')) {
            Error_report(2);
            printf("是否继续录入学生信息？(Y/N): ");
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
        printf("内存分配失败！\n");
        return NULL;
    }

    for (int i = 0; i < college_count; i++) {
        printf("请输入第 %d 个班级的代码: ", i + 1);
        fgets(college[i].college_class_info, DEGITAL, stdin);
        college[i].college_class_info[strcspn(college[i].college_class_info, "\n")] = 0;

        printf("请输入第 %d 个班级的名称: ", i + 1);
        fgets(college[i].college_class_text, STR_MAX, stdin);
        college[i].college_class_text[strcspn(college[i].college_class_text, "\n")] = 0;
    }

    return college;
}

SUBJECT *create_subject_array(int subject_count)
{
    SUBJECT *subject = (SUBJECT *)malloc(subject_count * sizeof(SUBJECT));
    if (subject == NULL) {
        printf("内存分配失败！\n");
        return NULL;
    }

    for (int i = 0; i < subject_count; i++) {
        subject[i].i = i + 1;
        printf("请输入第 %d 个科目的名称和学分（用空格分隔）：", i + 1);
        while (scanf("%s %lf", subject[i].name, &subject[i].point) != 2) {
            Error_report(2);
            while (getchar() != '\n');
        }
        while (getchar() != '\n');
    }

    return subject;
}
// ... 之前的代码保持不变 ...

void print(HEAD *header) {
    if (header == NULL) {
        Error_report(1);
        return;
    }
    // 输出头节点内容
    printf("链表名称: %s\n", header->list_name);
    printf("学生数量: %d\n", header->student_count);
    printf("班级数量: %d\n", header->college_count);
    printf("科目数量: %d\n", header->subject_count);
    printf("科目列表: ");
    for (int i = 0; i < header->subject_count; i++) {
        printf("%s(%.1f学分) ", header->subject_list[i].name, header->subject_list[i].point);
    }
    printf("\n");

    // 检查链表是否只有头结点
    if (header->next == NULL) {
        Error_report(3);
        return;
    }

    // 输出表头
    printf("| ID | 姓名 | 学号 | 班级 |");
    for (int i = 0; i < header->subject_count; i++) {
        printf(" %s |", header->subject_list[i].name);
    }
    printf(" GPA | 总学分 | 排名 | 平均分 | 挂科数 |\n");

    // 输出每个节点的完整信息
    NODE *current = header->next;
    while (current != NULL) {
        // 查找班级名称
        char *class_name = NULL;
        for (int i = 0; i < header->college_count; i++) {
            if (strcmp(current->college_class_info, header->college[i].college_class_info) == 0) {
                class_name = header->college[i].college_class_text;
                break;
            }
        }

        // 输出节点基本信息
        printf("| %d | %s | %s | %s |", current->id, current->name, current->student_id, class_name);

        // 输出每个科目的成绩
        for (int i = 0; i < header->subject_count; i++) {
            printf(" %.2f |", current->score[i]);
        }

        // 输出 GPA、总学分、排名、平均分和挂科数
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
    // 释放班级和科目数组内存
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
            printf("找到节点，ID: %d, 名称: %s\n", current->id, current->name);
            return;
        }
        current = current->next;
    }
    printf("未找到 ID 为 %d 的节点。\n", target_id);
}

void change_single_node(HEAD *header, int target_location) {
    NODE *current = header->next;
    int step = 1;
    while (current != NULL && step < target_location) {
        current = current->next;
        step++;
    }
    if (current == NULL) {
        printf("未找到指定位置的节点。\n");
        return;
    }
    printf("当前节点信息：ID: %d, 姓名: %s, 学号: %s, 班级代码: %s\n", current->id, current->name, current->student_id, current->college_class_info);
    int choice;
    do {
        printf("\n请选择要修改的内容：\n");
        printf("1. 姓名\n");
        printf("2. 学号\n");
        printf("3. 班级代码\n");
        for (int i = 0; i < header->subject_count; i++) {
            printf("%d. ", i + 4);
            printf("%s成绩\n", header->subject_list[i].name);
        }
        printf("0. 退出修改\n");
        printf("请输入选项：");
        while (scanf("%d", &choice) != 1) {
            Error_report(2);
            printf("请输入选项：");
        }
        while (getchar() != '\n');

        switch (choice) {
        case 1:
            printf("请输入新的学生姓名：");
            fgets(current->name, STR_MAX, stdin);
            current->name[strcspn(current->name, "\n")] = 0;
            break;
        case 2:
            printf("请输入新的学生学号：");
            fgets(current->student_id, STR_MAX, stdin);
            current->student_id[strcspn(current->student_id, "\n")] = 0;
            break;
        case 3:
            printf("请输入新的班级代码：");
            fgets(current->college_class_info, DEGITAL, stdin);
            current->college_class_info[strcspn(current->college_class_info, "\n")] = 0;
            break;
        default:
            if (choice > 3 && choice <= 3 + header->subject_count) {
                int score_index = choice - 4;
                printf("请输入第 %d 门课的新成绩：", score_index + 1);
                while (scanf("%lf", &current->score[score_index]) != 1) {
                    Error_report(2);
                    printf("请输入第 %d 门课的新成绩：", score_index + 1);
                }
                while (getchar() != '\n');
            } else if (choice != 0) {
                printf("无效的选项，请重新输入。\n");
            }
            break;
        }
    } while (choice != 0);
    printf("节点信息修改完成。\n");
}

//// 测试用主文件
//int main() {
//    HEAD *header = (HEAD *)malloc(sizeof(HEAD));
//    if (header == NULL) {
//        Error_report(1);
//        return 1;
//    }
//
//    int college_count, subject_count;
//    // 输入科目数量
//    printf("输入科目数量：");
//    scanf("%d", &subject_count);
//    while (getchar() != '\n'); // 清除缓冲区的换行符
//
//    // 输入班级数量
//    printf("输入班级数量：");
//    scanf("%d", &college_count);
//    while (getchar() != '\n'); // 清除缓冲区的换行符
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
//    // 初始化链表
//    header = newlist(header, subject, college, subject_count, college_count);
//
//    // 创建学生节点链表
//    create_node(header);
//
//    // 显示链表
//    printf("创建完成后的链表：\n");
//    print(header);
//
//    // 示例：修改第 2 个节点的数据
//    change_single_node(header, 1);
//    printf("修改后的链表：\n");
//    print(header);
//
//    // 示例：查找 ID 为 3 的节点
//    find_node_with_id(header, 3);
//    printf("查找节点后的链表：\n");
//    print(header);  // 新增显示链表操作
//
//    // 示例：删除第 1 个节点
//    delete_single_node(header, 1);
//    printf("删除节点后的链表：\n");
//    print(header);
//
//    // 释放链表
//    free_whole_list(header);
//
//    return 0;
//}
