/* qlearning.c
強化学習(Q学習)の例題ブログラム
迷路の探索を学習します。
*/
#include<stdio.h>
#include<stdlib.h>

#define GENMAX  1000
#define NODENO  15
#define ALPHA   0.1
#define GAMMA   0.9
#define EPSILON 0.3
#define SEED    32767

int rand100();
int rand01();
double rand1();
void printqvalue(int qvalue[NODENO]);
int selecta(int s, int qvalue[NODENO]);
int updateq(int s, int qvalue[NODENO]);

int main(void){
    int i;
    int s;
    int t;
    int qvalue[NODENO];

    srand(SEED);

    for(i = 0; i < GENMAX; ++i){
        s = 0;
        for(t = 0; t < 3; ++t){
            s= selecta(s, qvalue);
            qvalue[s] = updateq(s, qvalue);
        }
        printqvalue(qvalue);
    }
    return 0;
}


int updateq(int s, int qvalue[NODENO])
{
    int qv;
    int qmax;

    if(s > 6){
        if     (s == 14){qv = qvalue[s] + ALPHA * (1000 - qvalue[s]);}
        /*報酬を与えるノードを増やす*/
        /*他のノードを追加する場合は*/
        /*下記1行のコメントを外す*/
//        else if(s == 11){qv = qvalue[s] + ALPHA * (500  - qvalue[s]);}
        else            {qv = qvalue[s];}
    }
    else{
        if((qvalue[2 * s + 1]) > (qvalue[2 * s + 2])){
            qmax = qvalue[2 * s + 1];
        }
        else{
            qmax = qvalue[2 * s + 2];
        }
        qv = qvalue[s] + ALPHA * (GAMMA * qmax - qvalue[s]);
    }
    return qv;
}

int selecta(int olds, int qvalue[NODENO])
{
    int s;
    if(rand1() < EPSILON){
        if(rand01() == 0){s = 2 * olds + 1;}
        else             {s = 2 * olds + 2;}
    }
    else{
        if((qvalue[2 * olds + 1]) > (qvalue[2 * olds + 2])){
            s = 2 * olds + 1;
        }
        else{
            s = 2 * olds + 2;
        }
    }
    return s;
}

void printqvalue(int qvalue[NODENO])
{
    int i;
    for(i = 1; i < NODENO; ++i){printf("%d\t",qvalue[i]);}
    printf("\n");
}

double rand1()
{
    return (double)rand() / RAND_MAX;
}

int rand01()
{
    int rnd;
    while((rnd = rand()) == RAND_MAX);
    return (int)((double)rnd / RAND_MAX * 2);
}

int rand100()
{
    int rnd;
    while((rnd = rand()) == RAND_MAX);
    return (int)((double)rnd / RAND_MAX * 101);
}
