/*
welcome_temp_memory.txt format
sheet_name|adress
for example:
sheet1|C:\\Users\\user\\Desktop\\sheet1.txt
sheet2|C:\\Users\\user\\Desktop\\sheet2.txt
sheet3|C:\\Users\\user\\Desktop\\sheet3.txt
and so on...
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define PAGE_SIZE 5 // 每页显示的文件数量

char* memory()
{
    FILE *fp;
    char sheet_name[100][100];
    char adress[100][100];
    fp = fopen("welcome_temp_memory.txt", "r"); // 修复：改为只读模式
    if(fp == NULL)
    {
        printf("It seems that it is the first time you open this software...\nClick new to create a sheet or import from your Windows!\n");
        return NULL; // 修复：文件不存在时返回 NULL
    }
    else
    {
        int i = 0;
        while (fscanf(fp, "%[^|]|%[^\n]\n", sheet_name[i], adress[i]) != EOF) {
            i++;
            if (i >= 100) { // 修复：防止数组越界
                printf("Error: Too many entries in the file. Maximum supported is 100.\n");
                break;
            }
        }
        fclose(fp); // 修复：关闭文件指针

        int total_files = i;
        int current_page = 0;
        int total_pages = (total_files + PAGE_SIZE - 1) / PAGE_SIZE; // 计算总页数

        while (1) {
            // 显示当前页的内容
            printf("\n|operation code|sheet name|adress|\n");
            int start_index = current_page * PAGE_SIZE;
            int end_index = start_index + PAGE_SIZE;
            if (end_index > total_files) {
                end_index = total_files;
            }

            for (i = start_index; i < end_index; i++) {
                printf("%d|%s|%s\n", i, sheet_name[i], adress[i]);
            }

            // 显示翻页选项
            printf("\nPage %d of %d\n", current_page + 1, total_pages);
            printf("Enter 'n' for next page, 'p' for previous page, or a number to select a file:\n");

            char input[10];
            scanf("%s", input);

            if (strcmp(input, "n") == 0) {
                if (current_page < total_pages - 1) {
                    current_page++;
                } else {
                    printf("Already on the last page.\n");
                }
            } else if (strcmp(input, "p") == 0) {
                if (current_page > 0) {
                    current_page--;
                } else {
                    printf("Already on the first page.\n");
                }
            } else {
                int choice = atoi(input);
                if (choice >= 0 && choice < total_files) {
                    // 修复：动态分配内存以返回地址
                    char* selected_adress = (char*)malloc(strlen(adress[choice]) + 1);
                    if (selected_adress == NULL) {
                        printf("Memory allocation failed.\n");
                        return NULL;
                    }
                    strcpy(selected_adress, adress[choice]);
                    return selected_adress;
                } else {
                    printf("Invalid choice. Try again.\n");
                }
            }
        }
    }
}

int main()
{
    char *address = memory();
    if (address != NULL) {
        printf("The address is: %s\n", address);
        free(address); // 修复：释放动态分配的内存
    } else {
        printf("No address found.\n");
    }
    return 0;
}