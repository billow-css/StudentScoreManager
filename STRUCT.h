/**
 * @file STRUCT.h
 * @brief ѧ����Ϣ����ϵͳͷ�ļ�
 * @details �����ṹ�嶨�塢�궨�弰���ܺ�������������ʵ��ѧ����Ϣ���������
 * @version 1.0
 * @date 2025-04-21
 * @copyright Copyright (c) 2025
 */

#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ====================== �궨�� ======================
/**
 * @brief ����ļ���С���ֽڣ�
 * @note �����ļ�����ʱ�Ļ�������С����
 */
#define FILE_MAX 10000

/**
 * @brief ����ַ�������
 * @note �����ַ�����ĳ��ȶ���
 */
#define STR_MAX 1000

/**
 * @brief ���������ֶ���󳤶ȣ���༶���룩
 * @note ���ƶ������ַ��������볤��
 */
#define DEGITAL 10

// ====================== �ṹ�嶨�� ======================
/**
 * @struct SUBJECT
 * @brief ��Ŀ��Ϣ�ṹ��
 * @var SUBJECT::i
 * @brief ��Ŀ��ţ���1��ʼ��
 * @var SUBJECT::name
 * @brief ��Ŀ���ƣ��ַ�����
 * @var SUBJECT::point
 * @brief ��Ŀѧ�֣���������
 */
typedef struct SUBJECT {
    int i;
    char name[STR_MAX];
    double point;
} SUBJECT;

/**
 * @struct COL_INFO
 * @brief ѧԺ�༶��Ϣ�ṹ��
 * @var COL_INFO::college_class_info
 * @brief �༶���루�̶������ַ�����
 * @var COL_INFO::college_class_text
 * @brief �༶���ƣ�����������
 */
typedef struct COLLEGE_CLASS_INFO {
    char college_class_info[DEGITAL];
    char college_class_text[STR_MAX];
} COL_INFO;

/**
 * @struct HEAD
 * @brief ����ͷ�ڵ�ṹ��
 * @var HEAD::list_name
 * @brief �������ƣ����ڱ�ʶ��ͬ�����б�
 * @var HEAD::student_count
 * @brief ѧ���ڵ�����
 * @var HEAD::college
 * @brief �༶��Ϣ����ָ�루��̬���䣩
 * @var HEAD::subject_list
 * @brief ��Ŀ��Ϣ����ָ�루��̬���䣩
 * @var HEAD::college_count
 * @brief �༶��Ϣ����
 * @var HEAD::subject_count
 * @brief ��Ŀ��Ϣ����
 * @var HEAD::next
 * @brief ָ����һ��ͷ�ڵ��ָ�루���ڶ����������ǰδʵ�֣�
 */
typedef struct HEAD {
    char list_name[STR_MAX];
    int student_count;
    COL_INFO *college;
    SUBJECT *subject_list;
    int college_count;
    int subject_count;
    struct HEAD *next;  // ע�⣺ԭ��������дΪstruct NODE*���˴�����Ϊͷ�ڵ�ָ�루�����߼���
} HEAD;

/**
 * @struct NODE
 * @brief ѧ����Ϣ�ڵ�ṹ��
 * @var NODE::id
 * @brief ѧ����Ϣ��ţ��Զ�������
 * @var NODE::name
 * @brief ѧ������
 * @var NODE::student_id
 * @brief ѧ��ѧ��
 * @var NODE::college_class_info
 * @brief �����༶���루��ӦCOL_INFO�еĴ��룩
 * @var NODE::score
 * @brief ��Ŀ�ɼ����飨������ͷ�ڵ��subject_count������
 * @var NODE::GPA
 * @brief ƽ��ѧ�ּ��㣨����ֵ��
 * @var NODE::subject_point
 * @brief ��ѧ�֣�����ֵ��
 * @var NODE::level
 * @brief �༶����������ֵ��
 * @var NODE::ave
 * @brief ƽ���֣�����ֵ��
 * @var NODE::fails
 * @brief �ҿƿ�Ŀ��������ֵ��
 * @var NODE::next
 * @brief ָ����һ��ѧ���ڵ��ָ��
 */
typedef struct NODE {
    int id;
    char name[STR_MAX];
    char student_id[STR_MAX];
    char college_class_info[DEGITAL];
    double score[STR_MAX];  // ע�⣺�˴�����Ǳ�����⣬STR_MAX���󣬽�����ö�̬�����ͷ�ڵ㴫�ݳ���
    double GPA;
    double subject_point;
    int level;
    double ave;
    int fails;
    struct NODE *next;
} NODE;

// ====================== ����ԭ������ ======================
/**
 * @brief ���󱨸溯��
 * @param error_code ������루1-�ڴ����ʧ�ܣ�2-�����ʽ����3-�ձ��4-����Ϣ�����ڣ�
 * @note ��ӡ������Ϣ���������뻺������������������룩
 */
void Error_report(int error_code);

/**
 * @brief �ڵ���Ϣ���뺯��
 * @param new_node ����ʼ���Ľڵ�ָ��
 * @param id ѧ����Ϣ���
 * @param subject_count ��Ŀ����������ѭ������ɼ���
 * @return ��ʼ����Ľڵ�ָ��
 * @note ��������ʽ���룬�Զ������з�
 */
NODE *input(NODE *new_node, int id, int subject_count);

/**
 * @brief ����������ͷ�ڵ�
 * @param header ͷ�ڵ�ָ�루����ǰ�����ڴ棩
 * @param subject ��Ŀ��Ϣ����ָ��
 * @param college �༶��Ϣ����ָ��
 * @param subject_count ��Ŀ����
 * @param college_count �༶����
 * @return ��ʼ�����ͷ�ڵ�ָ��
 * @note ����ʽ�����������ƣ�������Ŀ�Ͱ༶��Ϣ
 */
HEAD *newlist(HEAD *header, SUBJECT *subject, COL_INFO *college, int subject_count, int college_count);

/**
 * @brief ����ѧ���ڵ�����
 * @param header ͷ�ڵ�ָ��
 * @return ѧ���ڵ�����ͷָ�루��header->next��
 * @note ����ʽѭ��������ѧ����Ϣ��ֱ���û���ֹ
 */
NODE *create_node(HEAD *header);

/**
 * @brief �����༶��Ϣ����
 * @param college_count �༶����
 * @return ��̬����İ༶��Ϣ����ָ��
 * @note ����ʽ����ÿ���༶�Ĵ�������ƣ��ڴ���������ͷ�
 */
COL_INFO *create_college_array(int college_count);

/**
 * @brief ������Ŀ��Ϣ����
 * @param subject_count ��Ŀ����
 * @return ��̬����Ŀ�Ŀ��Ϣ����ָ��
 * @note ����ʽ����ÿ����Ŀ�����ƺ�ѧ�֣��ڴ���������ͷ�
 */
SUBJECT *create_subject_array(int subject_count);

/**
 * @brief ��ӡ������Ϣ
 * @param header ͷ�ڵ�ָ��
 * @note ���ͷ�ڵ���Ϣ������ѧ���ڵ����飬������Ŀ�ɼ��ͼ���ֵ
 */
void print(HEAD *header);

/**
 * @brief �ͷ����������ڴ�
 * @param header ͷ�ڵ�ָ��
 * @note �ݹ��ͷ�ѧ���ڵ㡢�༶���顢��Ŀ���鼰ͷ�ڵ������ڴ�
 */
void free_whole_list(HEAD *header);

/**
 * @brief ɾ��ָ��λ�õĵ����ڵ�
 * @param header ͷ�ڵ�ָ��
 * @param location_code �ڵ�λ�ã���1��ʼ������
 * @note λ�ó�����Χʱ��Ĭ�������ȼ��������Ч��
 */
void delete_single_node(HEAD *header, int location_code);

/**
 * @brief ��ID���ҽڵ�
 * @param header ͷ�ڵ�ָ��
 * @param target_id Ŀ��ѧ�����
 * @note ��ӡ���ҽ����δ�ҵ�ʱ��ʾ��Ϣ
 */
void find_node_with_id(HEAD *header, int target_id);

/**
 * @brief �޸�ָ��λ�õĽڵ���Ϣ
 * @param header ͷ�ڵ�ָ��
 * @param target_location Ŀ��ڵ�λ�ã���1��ʼ������
 * @note ����ʽѡ���޸����ݣ�֧��������ѧ�š��༶���뼰��Ŀ�ɼ�
 */
void change_single_node(HEAD *header, int target_location);

/**
 * @brief ����������ݵ��ļ�
 * @param header ͷ�ڵ�ָ��
 * @param filename Ŀ���ļ���
 * @note ���ܴ�ʵ�֣�Դ�ļ���������δ���壩���貹���ļ������߼�
 */
void output_to_file(HEAD *header, const char *filename);

#endif // STRUCT_H_INCLUDED
