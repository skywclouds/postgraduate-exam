/**
 * @file getTreeWidth.c
 * @author He Wang
 * @brief 复习C语言 三个完全平方三位数，1-9中每个数字只出现一次
 * @date 2023-08-02
 */

#include <stdio.h>

int main()
{
    int num[22];
    for(int i = 10;i < 32;i++)//生成所有的三位完全平方数  
        num[i-10] = i * i;
    for(int i = 0;i < 22;i++)//遍历每一种组合
    {
        for(int j = i+1;j < 22;j++)
        {
            for(int k = j+1;k < 22;k++)
            {
                //检验是否每个数字只出现一次
                int p[10] = {1,1,1,1,1,1,1,1,1,1};
                int n_a = num[i];int n_b = num[j];int n_c = num[k];
                while(n_a)
                {
                    p[n_a % 10]--;p[n_b % 10]--;p[n_c % 10]--;
                    n_a = n_a / 10;n_b = n_b / 10;n_c = n_c / 10;
                }
                int m;
                //若每个数字只出现一次，则p数组必然全为0
                for(m = 1;m < 10;m++)
                    if(p[m] != 0)
                        break;
                if(m == 10)
                    printf("%d %d %d\n",num[i],num[j],num[k]);
            }
        }
    }
    return 0;
}