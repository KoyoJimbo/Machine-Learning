/************************
sum2.c
和、二乗和を求める。
標準入力から実数を読み取り、
和と二乗和を逐次出力します
コントロールzとで終了します。
使い方
C:\Users\odaka\dl\ch>sum2
***********************/

#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 256

int main()
{
    char linebuf[BUFSIZE];
    double data;
    double sum = 0.0;
    double sum2 = 0.0;
 
    while (fgets(linebuf, BUFSIZE, stdin) != NULL) {
        if (sscanf(linebuf, "%lf", &data) !=0) {
            sum += data;
            sum2 += data * data;
            printf("%lf\t%lf\n", sum, sum2);
        }
    }
    return 0;
}
 
