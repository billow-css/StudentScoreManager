/**
 * @file STRUCT.h
 * @brief 学生信息管理系统头文件
 * @details 包含结构体定义、宏定义及功能函数声明，用于实现学生信息的链表管理
 * @version 1.0
 * @date 2025-04-21
 * @copyright Copyright (c) 2025
 */

#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ====================== 宏定义 ======================
/**
 * @brief 最大文件大小（字节）
 * @note 用于文件操作时的缓冲区大小限制
 */
#define FILE_MAX 10000

/**
 * @brief 最大字符串长度
 * @note 用于字符数组的长度定义
 */
#define STR_MAX 1000

/**
 * @brief 数字类型字段最大长度（如班级代码）
 * @note 限制短数字字符串的输入长度
 */
#define DEGITAL 10

// ====================== 结构体定义 ======================
/**
 * @struct SUBJECT
 * @brief 科目信息结构体
 * @var SUBJECT::i
 * @brief 科目编号（从1开始）
 * @var SUBJECT::name
 * @brief 科目名称（字符串）
 * @var SUBJECT::point
 * @brief 科目学分（浮点数）
 */
typedef struct SUBJECT {
    int i;
    char name[STR_MAX];
    double point;
} SUBJECT;

/**
 * @struct COL_INFO
 * @brief 学院班级信息结构体
 * @var COL_INFO::college_class_info
 * @brief 班级代码（固定长度字符串）
 * @var COL_INFO::college_class_text
 * @brief 班级名称（完整描述）
 */
typedef struct COLLEGE_CLASS_INFO {
    char college_class_info[DEGITAL];
    char college_class_text[STR_MAX];
} COL_INFO;

/**
 * @struct HEAD
 * @brief 链表头节点结构体
 * @var HEAD::list_name
 * @brief 链表名称（用于标识不同数据列表）
 * @var HEAD::student_count
 * @brief 学生节点总数
 * @var HEAD::college
 * @brief 班级信息数组指针（动态分配）
 * @var HEAD::subject_list
 * @brief 科目信息数组指针（动态分配）
 * @var HEAD::college_count
 * @brief 班级信息数量
 * @var HEAD::subject_count
 * @brief 科目信息数量
 * @var HEAD::next
 * @brief 指向下一个头节点的指针（用于多链表管理，当前未实现）
 */
typedef struct HEAD {
    char list_name[STR_MAX];
    int student_count;
    COL_INFO *college;
    SUBJECT *subject_list;
    int college_count;
    int subject_count;
    struct HEAD *next;  // 注意：原代码中误写为struct NODE*，此处修正为头节点指针（根据逻辑）
} HEAD;

/**
 * @struct NODE
 * @brief 学生信息节点结构体
 * @var NODE::id
 * @brief 学生信息编号（自动递增）
 * @var NODE::name
 * @brief 学生姓名
 * @var NODE::student_id
 * @brief 学生学号
 * @var NODE::college_class_info
 * @brief 所属班级代码（对应COL_INFO中的代码）
 * @var NODE::score
 * @brief 科目成绩数组（长度由头节点的subject_count决定）
 * @var NODE::GPA
 * @brief 平均学分绩点（计算值）
 * @var NODE::subject_point
 * @brief 总学分（计算值）
 * @var NODE::level
 * @brief 班级排名（计算值）
 * @var NODE::ave
 * @brief 平均分（计算值）
 * @var NODE::fails
 * @brief 挂科科目数（计算值）
 * @var NODE::next
 * @brief 指向下一个学生节点的指针
 */
typedef struct NODE {
    int id;
    char name[STR_MAX];
    char student_id[STR_MAX];
    char college_class_info[DEGITAL];
    double score[STR_MAX];  // 注意：此处存在潜在问题，STR_MAX过大，建议改用动态数组或头节点传递长度
    double GPA;
    double subject_point;
    int level;
    double ave;
    int fails;
    struct NODE *next;
} NODE;

// ====================== 函数原型声明 ======================
/**
 * @brief 错误报告函数
 * @param error_code 错误代码（1-内存分配失败，2-输入格式错误，3-空表格，4-表信息不存在）
 * @note 打印错误信息并处理输入缓冲区（如清除错误输入）
 */
void Error_report(int error_code);

/**
 * @brief 节点信息输入函数
 * @param new_node 待初始化的节点指针
 * @param id 学生信息编号
 * @param subject_count 科目数量（用于循环输入成绩）
 * @return 初始化后的节点指针
 * @note 包含交互式输入，自动处理换行符
 */
NODE *input(NODE *new_node, int id, int subject_count);

/**
 * @brief 创建新链表头节点
 * @param header 头节点指针（需提前分配内存）
 * @param subject 科目信息数组指针
 * @param college 班级信息数组指针
 * @param subject_count 科目数量
 * @param college_count 班级数量
 * @return 初始化后的头节点指针
 * @note 交互式输入链表名称，关联科目和班级信息
 */
HEAD *newlist(HEAD *header, SUBJECT *subject, COL_INFO *college, int subject_count, int college_count);

/**
 * @brief 创建学生节点链表
 * @param header 头节点指针
 * @return 学生节点链表头指针（即header->next）
 * @note 交互式循环输入多个学生信息，直到用户终止
 */
NODE *create_node(HEAD *header);

/**
 * @brief 创建班级信息数组
 * @param college_count 班级数量
 * @return 动态分配的班级信息数组指针
 * @note 交互式输入每个班级的代码和名称，内存需调用者释放
 */
COL_INFO *create_college_array(int college_count);

/**
 * @brief 创建科目信息数组
 * @param subject_count 科目数量
 * @return 动态分配的科目信息数组指针
 * @note 交互式输入每个科目的名称和学分，内存需调用者释放
 */
SUBJECT *create_subject_array(int subject_count);

/**
 * @brief 打印链表信息
 * @param header 头节点指针
 * @note 输出头节点信息和所有学生节点详情，包含科目成绩和计算值
 */
void print(HEAD *header);

/**
 * @brief 释放整个链表内存
 * @param header 头节点指针
 * @note 递归释放学生节点、班级数组、科目数组及头节点自身内存
 */
void free_whole_list(HEAD *header);

/**
 * @brief 删除指定位置的单个节点
 * @param header 头节点指针
 * @param location_code 节点位置（从1开始计数）
 * @note 位置超出范围时静默处理，需先检查链表有效性
 */
void delete_single_node(HEAD *header, int location_code);

/**
 * @brief 按ID查找节点
 * @param header 头节点指针
 * @param target_id 目标学生编号
 * @note 打印查找结果，未找到时提示信息
 */
void find_node_with_id(HEAD *header, int target_id);

/**
 * @brief 修改指定位置的节点信息
 * @param header 头节点指针
 * @param target_location 目标节点位置（从1开始计数）
 * @note 交互式选择修改内容，支持姓名、学号、班级代码及科目成绩
 */
void change_single_node(HEAD *header, int target_location);

/**
 * @brief 输出链表数据到文件
 * @param header 头节点指针
 * @param filename 目标文件名
 * @note 功能待实现（源文件中声明但未定义），需补充文件操作逻辑
 */
void output_to_file(HEAD *header, const char *filename);

#endif // STRUCT_H_INCLUDED
