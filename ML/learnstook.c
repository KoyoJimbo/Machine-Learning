/*
learnstock.c
単純な帰納的学習の例題プログラム
パターン学習器
100個の学習データを読み込み
適合するパターンを返します。
./a.out < ldata.txt
*/
#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define NG 0
#define SETSIZE 100
#define CNO 10
#define GENMAX 10000
#define SEED 32767

int rand012();
int calcscore(int data[SETSIZE][CNO], int teacher[SETSIZE], int answer[CNO]);
void readdata(int data[SETSIZE][CNO], int teacher[SETSIZE]);

int main(void){
    int i, j;
    int score = 0;
    int answer[SETSIZE];
    int data[SETSIZE][CNO];
    int teacher[SETSIZE];
    int bestscore = 0;
    int bestanswer[CNO];

    srand(SEED);
    readdata(data, teacher);
    for(i=0;i<GENMAX;++i){
        for(j=0;j<CNO;++j){
            answer[j] = rand012();
        }
        score=calcscore(data, teacher, answer);
        if(score > bestscore){
            for(j=0;j<CNO;++j){bestanswer[j]=answer[j];}
            bestscore = score;
            for(j=0;j<CNO;++j){printf("%1d",bestanswer[j]);}
            printf(":score=%d\n",bestscore);
        }
    }
    printf("\n最良解\n");
    for(j=0;j<CNO;++j){printf("%d ",bestanswer[j]);}
    printf(":score=%d\n",bestscore);
    return 0;
}

int calcscore(int data[SETSIZE][CNO], int teacher[SETSIZE], int answer[CNO])
{
    int score = 0;
    int point;
    int i,j;
    for(i=0;i<CNO;++i){
        point=0;
        for(j=0;j<CNO;++j){
            if     (answer[j] == 2)         {++point;}
            else if(answer[j] == data[i][j]){++point;}
        }
        if     ((point == CNO) && (teacher[i]==1)){++score;}
        else if((point != CNO) && (teacher[i]==0)){++score;}
    }
    return score;
}

void readdata(int data[SETSIZE][CNO], int teacher[SETSIZE])
{
    int i, j;
    for(i=0;i<SETSIZE;++i){
        for(j=0;j<CNO;++j){
            scanf("%d",&data[i][j]);
        }
        scanf("%d",&teacher[i]);
    }
}

int rand012()
{
    int rnd;
    while((rnd = rand()) == RAND_MAX);
    return (double)rnd / RAND_MAX * 3;
}
