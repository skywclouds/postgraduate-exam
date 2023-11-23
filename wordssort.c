/**
 * @file wordssort.c
 * @author He Wang
 * @brief 复习C语言 读取文件中的单词排序后写入文件
 * @date 2023-11-23
 */
#define MAXSIZE 100

#include <stdio.h>
#include <string.h>

int main()
{
    remove("file2.txt");
    FILE *fp1 = fopen("file1.txt","r");
    FILE *fp2 = fopen("file2.txt","w");
    if(fp1&&fp2)
    {
        char arr[MAXSIZE][MAXSIZE];
        int length = 0;
        char str[MAXSIZE];
        while(fscanf(fp1,"%s",str) != EOF)//读取单词
        {
            strcpy(arr[length],str);
            length++;
        }
        for(int i = 1;i < length;i++)//将单词排序
        {
            char t[MAXSIZE];
            strcpy(t,arr[i]);
            if(strcmp(arr[i-1],t) > 0)//插入排序
            {
                int j;
                for(j = i-1;j >= 0;j--)
                {
                    if(strcmp(arr[j],t) > 0)
                        strcpy(arr[j+1],arr[j]);
                    else
                        break;    
                }
                strcpy(arr[j+1],t);
            }   
        }
        for(int i = 0;i < length;i++)//将单词写入文件
            fprintf(fp2,"%s ",arr[i]);
        printf("finished.\n");
    }else
        printf("fail to open file\n");
    return 0;
}