#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NOA     10
#define ILIMIT  50
#define Q       3
#define RHO     0.8
#define STEP    10
#define EPSILON 0.10
#define SEED    24478

void printp(double pheromone[2][STEP]);
void printmstep(int mstep[NOA][STEP]);
void walk  (int cost[2][STEP],
            double pheromone[2][STEP],
            int mstep[NOA][STEP]);
void update(int cost[2][STEP],
            double pheromone[2][STEP],
            int mstep[NOA][STEP]);
double rand1();
int rand01();

int main()
{
    int cost[2][STEP] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, },
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, }
    };
    double pheromone[2][STEP];
    int mstep[NOA][STEP];
    int i;
    int m;

    for (m=0;m<NOA;++m){
        for(i=0;i<STEP;++i){
           mstep[m][i] = 0;
        }
    }

    srand(SEED);

    for(i=0;i<ILIMIT;++i){
        printf("%d:\n",i);
        printp(pheromone);
        walk(cost, pheromone, mstep);
        update(cost, pheromone, mstep);
    }
    printf("%d:\n",i);
    printp(pheromone);
    return 0;
}

void update(int cost[2][STEP],
            double pheromone[2][STEP],
            int mstep[NOA][STEP])
{
    int m;
    int lm;
    int i,j;
    double sum_lm = 0;
    int tmpstep;

    for(i=0;i<2;++i){
        for(j=0;j<STEP;++j){
            pheromone[i][j] *= RHO;
        }
    }
    for (m=0;m<NOA;++m){
        lm = 0;
        for(i=0;i<STEP;++i){
            tmpstep = mstep[m][i];
            lm += cost[tmpstep][i];
        }
        for(i=0;i<STEP;++i){
            tmpstep = mstep[m][i];
            pheromone[tmpstep][i] += Q * (1.0 / lm);
        }
        sum_lm += lm;
    }
    printf("%lf\n", sum_lm/NOA);
}

void walk(int cost[2][STEP],
          double pheromone[2][STEP],
          int mstep[NOA][STEP])
{
    int m;
    int s;
    double diff;
    for(m=0;m<NOA;++m){
        for(s=0;s<STEP;++s){
            diff = pheromone[0][s] - pheromone[1][s];
            if((rand1() < EPSILON) || (fabs(diff) < 1e-10)){
                mstep[m][s] = rand01();
            }
            else{
                if(pheromone[0][s] > pheromone[1][s]){
                    mstep[m][s] = 0;
                }
                else{
                    mstep[m][s] = 1;
                }
            }
        }
    }
    printmstep(mstep);
}

void printmstep(int mstep[NOA][STEP])
{
    int i, j;
    printf("*mstep\n");
    for(i=0;i<NOA;++i){
        for(j=0;j<STEP;++j){
            printf("%d ", mstep[i][j]);
        }
        printf("\n");
    }
}
void printp(double pheromone[2][STEP])
{
    int i, j;
    for(i=0;i<2;++i){
        for(j=0;j<STEP;++j){
            printf("%4.2f  ", pheromone[i][j]);
        }
        printf("\n");
    }

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
