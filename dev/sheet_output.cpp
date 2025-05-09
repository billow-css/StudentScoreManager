#include<stdio.h>
#include"STRUCT.h"
#include<stdlib.h>

// 常数模块
#define FILE_MAX 10000
#define STR_MAX 1000
#define DEGITAL 10

void error_report_output(int error_code)
{
    switch (error_code) {
        case 1:
            printf(">[x]>文件打开失败！\n");
            break;
        case 2:
            printf(">[x]>空表格！\n");
            break;
        case 3:
            printf(">[!]>请注意！这不是一个单学科成绩表，无法完成你的操作；\n");
            break;
        default:
            printf("未知错误！\n");
    }
}

void output_single(HEAD *header,char *adress,COL_INFO *college)
{
    FILE *fp;
    NODE *p=header->next;
    if (header == NULL) {
        error_report_output(2);
        return;
    }
    fp = fopen(adress, "w");
    if (fp == NULL) {
        error_report_output(1);
        return; // 不需要 fclose(fp)
    }
    if(header->subject_count!=1)
    {
        error_report_output(3);
        return;
    }
    fprintf(fp,"|%s|\n",header->list_name);
    fprintf(fp,"reference: %d\n",header->student_count);
    fprintf(fp,"point: %.2f\n",header->subject_list[0].point);
    fprintf(fp,"|ID|student_id|name|class|score|level|GPA|");
    while (p!= NULL) {
        char class_text[STR_MAX]="";
        for (int i = 0; i < header->college_count; i++) {
            if (strcmp(p->college_class_info, college[i].college_class_info) == 0) {
            strcpy(class_text, college[i].college_class_text);
            break;
            }
        }
        fprintf(fp,"|%d|%s|%s|%s|%.2f|%d|%.2f|\n", p->id, p->student_id, p->name, class_text, p->score[0], p->level, p->GPA);
        p = p->next;
    }  
    fclose(fp);
}

void output_multi_all(HEAD *header,char *adress,COL_INFO *college,SUBJECT *subject)
{
    FILE *fp;
    NODE *p=header->next;
    if (header == NULL) {
        error_report_output(2);
        return;
    }
    fp = fopen(adress, "w");
    if (fp == NULL) {
        error_report_output(1);
        return; // 不需要 fclose(fp)
    }
    fprintf(fp,"|%s|\n",header->list_name);
    fprintf(fp,"reference: %d\n",header->student_count);
    for(int i=0;i<header->subject_count;i++)
    {
        fprintf(fp,"subject: %s\n",header->subject_list[i].name);
        fprintf(fp,"point: %.2f\n",header->subject_list[i].point);
    }
    fprintf(fp,"|ID|student_id|name|class|");
    for(int i=0;i<header->subject_count;i++)
    {
        fprintf(fp,"%s",subject[i].name);
        if(i<header->subject_count-1)
        {
            fprintf(fp,"|");
        }
    }
    fprintf(fp,"|level|avg|GPA|points|fails|\n");
    while (p!= NULL) {
        char class_text[STR_MAX]="";
        for (int i = 0; i < header->college_count; i++) {
            if (strcmp(p->college_class_info, college[i].college_class_info) == 0) {
            strcpy(class_text, college[i].college_class_text);
            break;
            }
        }
        fprintf(fp,"|%d|%s|%s|%s|", p->id, p->student_id, p->name, class_text);
        for(int i=0;i<header->subject_count;i++)
        {
            fprintf(fp,"%.2f",p->score[i]);
            if(i<header->subject_count-1)
            {
                fprintf(fp,"|");
            }
        }
        fprintf(fp,"|%d|%.2f|%.2f|%.2f|%d|\n",p->level,p->ave,p->GPA,p->subject_point,p->fails);
        p = p->next;
    }
    fclose(fp);
}
//你好，到目前为止我的精神状态良好，我现在只知道我们曦玄小宝宝是唯一一个找果糖含量集邮没有集到邮的，真的太逊了
/*
我宣布个事！
24 计算机类 1班 孙崇礼————是！大！帅！哥！
话密了奥，我继续写代码了
*/
void output_multi_single(HEAD *header,char *adress,COL_INFO *college,SUBJECT *subject,int target)
{
    FILE *fp;
    NODE *p=header->next;
    if (header == NULL) {
        error_report_output(2);
        return;
    }
    fp = fopen(adress, "w");
    if (fp == NULL) {
        error_report_output(1);
        return; 
    }
    fprintf(fp,"|%s|\n",header->list_name);
    fprintf(fp,"reference: %d\n",header->student_count);
    fprintf(fp,"point: %.2f\n",header->subject_list[target].point); 
    fprintf(fp,"|ID|student_id|name|class|score|level|GPA|");
    while (p!= NULL) {
        char class_text[STR_MAX]="";
        for (int i = 0; i < header->college_count; i++) {
            if (strcmp(p->college_class_info, college[i].college_class_info) == 0) {
            strcpy(class_text, college[i].college_class_text);
            break;
            }
        }
        fprintf(fp,"|%d|%s|%s|%s|%.2f|%d|%.2f|\n", p->id, p->student_id, p->name, class_text, p->score[target], p->level, p->GPA);
        p = p->next;
    }  
    fclose(fp);
}

int main() {
    // 创建测试数据
    COL_INFO colleges[] = {
        {"01", "Engineering"},
        {"02", "Science"}
    };

    SUBJECT subjects[] = {
        {1, "Mathematics", 3.0},
        {2, "Physics", 4.0}
    };

    NODE student1 = {1, "Alice", "S001", "01", {85.0, 90.0}, 4.0, 7.0, 1, 87.5, 0, NULL};
    NODE student2 = {2, "Bob", "S002", "02", {78.0, 88.0}, 3.0, 6.5, 2, 83.0, 1, NULL};
    student1.next = &student2;

    HEAD header = {
        "Test List", 2, colleges, subjects, 2, 2, &student1
    };

    // 测试 output_single
    output_single(&header, "single_output.txt", colleges);

    // 测试 output_multi_all
    output_multi_all(&header, "multi_all_output.txt", colleges, subjects);

    // 测试 output_multi_single
    output_multi_single(&header, "multi_single_output.txt", colleges, subjects, 1);

    printf("Test outputs generated.\n");
    return 0;
}
