//author 软1803 徐志

#include <stdio.h>
#include <time.h>
#include<stdlib.h>
#include<cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

const int NP = 40; // 蜂群的规模=采蜜蜂+观察蜂
const int FoodNumber = NP / 2; // 食物的数量，为采蜜蜂的数量
const int limit = 20;  //限度，超过这个限度没有更新，采蜜蜂变成观察蜂
const int maxCycle = 10000;  //停止条件

/*****************/
const int D = 2;  //函数的参数个数
const double lb = -100; //函数的下界
const double ub = 100; //函数的上界

double result[maxCycle] = {0};

/****种群的定义********/
struct BeeGroup {
    double code[D];  //函数的维数
    double trueFit; //记录真实的最小值
    double fitness;//适应值
    double rfitness; // 相对适应值比例
    int trail; //表示实验的次数
} Bee[FoodNumber];

BeeGroup NectarSource[FoodNumber]; //蜜源，一切的修改都是针对蜜源而言
BeeGroup EmployedBee[FoodNumber]; //采蜜蜂
BeeGroup OnLooker[FoodNumber]; //观察蜂
BeeGroup BestSource;//记录最好的蜜源

double random(double, double);

void initilize();

double calculationTruefit(BeeGroup);  //计算真实的函数值
double calculationFitness(double);   //计算适应值
void CalculateProbabilities();    //计算轮盘赌的概率
void evalueSource();        //评价蜜源
void sendEmployedBees();

void sendOnlookerBees();

void sendScoutBees();

void MemorizeBestSource();

/****主函数******/
int main() {
    ofstream output;
    output.open("dataABC.txt");
    srand((unsigned) time(NULL));
    initilize();
    MemorizeBestSource();

    //主要循环
    int gen = 0;
    while (gen < maxCycle) {
        sendEmployedBees();

        CalculateProbabilities();

        sendOnlookerBees();

        MemorizeBestSource();

        sendScoutBees();

        MemorizeBestSource();

        output << setprecision(30) << BestSource.trueFit << endl;

        gen++;
    }

    output.close();
    std::cout << "ending" << endl;

    return 0;
}

double random(double start, double end) {
    return start + (end - start) * rand() / (RAND_MAX + 1.0);
}

void initilize() {
    int i,j;
    for(i=0;i<D;i++) {
        for (j=0;j<D;j++) {
            NectarSource[i].code[j]=random(lb,ub);
            EmployedBee[i].code[j]=NectarSource[i].code[j];
            OnLooker[i].code[j]=NectarSource[i].code[j];
            BestSource.code[j]=NectarSource[0].code[j];
        }

        /***蜜源的初始化****/
        NectarSource[i].trueFit=calculationTruefit(NectarSource[i]);
        NectarSource[i].fitness=calculationFitness(NectarSource[i].trueFit);
        NectarSource[i].rfitness=0;
        NectarSource[i].trail=0;
        /*****采蜜蜂的初始化*******/
        EmployedBee[i].trueFit=NectarSource[i].trueFit;
        EmployedBee[i].fitness=NectarSource[i].fitness;
        EmployedBee[i].rfitness=NectarSource[i].rfitness;
        EmployedBee[i].trail = NectarSource[i].trail;
        /****观察蜂的初始化******/
        OnLooker[i].trueFit=NectarSource[i].trueFit;
        OnLooker[i].fitness=NectarSource[i].fitness;
        OnLooker[i].rfitness=NectarSource[i].rfitness;
        OnLooker[i].trail = NectarSource[i].trail;
    }
    /****最优化蜜源的初始化**********/
    BestSource.trueFit=NectarSource[i].trueFit;
    BestSource.fitness=NectarSource[i].fitness;
    BestSource.rfitness=NectarSource[i].rfitness;
    BestSource.trail = NectarSource[i].trail;
}

double calculationTruefit(BeeGroup bee) {
    double truefit=0;
    truefit=(-20)*exp((-0.2)*sqrt((bee.code[0]*bee.code[0]+bee.code[1]*bee.code[1])/2))-exp(
            (cos(2*3.14*bee.code[0]+cos(2*3.14*bee.code[1]))/2))+20+2.718;
    return truefit;
}

double calculationFitness(double truefit) {
    double fitnessResult=0;
    if (truefit>0) {
        fitnessResult=1/(truefit+1);
    }else {
        fitnessResult=1+abs(truefit);
    }
    return fitnessResult;
}

void sendEmployedBees() {
    int i,j,k;
    int param2change; //需要改变的维数
    double Rij; //[-1,1]之间的随机数
    for(i=0;i<FoodNumber;i++) {    //每一个密封都要去采蜜
        param2change=(int)random(0,D);   //任意方向偏移

        /*****选取不等于i的k*********/
        while(1) {
            k = (int)random(0,FoodNumber);
            if(k!=i) {
                break;
            }
        }

        for (j = 0; j < D; ++j) {
            EmployedBee[i].code[j]=NectarSource[i].code[j];
        }

        /***采蜂去更新信息****/
        Rij=random(-1,1);
        EmployedBee[i].code[param2change]=NectarSource[i].code[param2change]+Rij*(NectarSource[i].code[param2change]-NectarSource[k].code[param2change]);
        /*****判断是否越界******/
        if (EmployedBee[i].code[param2change]>ub) {
            EmployedBee[i].code[param2change]=ub;
        }

        if (EmployedBee[i].code[param2change]<lb) {
            EmployedBee[i].code[param2change]=lb;
        }
        EmployedBee[i].trueFit=calculationTruefit(EmployedBee[i]);
        EmployedBee[i].fitness=calculationFitness(EmployedBee[i].trueFit);

        /****贪婪选择策略*******/
        if (EmployedBee[i].trueFit<NectarSource[i].trueFit) {
            for(j=0;j<D;j++) {
                NectarSource[i].code[j]=EmployedBee[i].code[j];
            }
            NectarSource[i].trail=0;
            NectarSource[i].trueFit=EmployedBee[i].trueFit;
            NectarSource[i].fitness=EmployedBee[i].fitness;
        }else {
            NectarSource[i].trail++;
        }
    }
}

void CalculateProbabilities() { //计算轮盘赌的选择概率
    int i;
    double maxfit;
    maxfit=NectarSource[0].fitness;
    for(i=1;i<FoodNumber;i++) {
        if(NectarSource[i].fitness>maxfit) {
            maxfit=NectarSource[i].fitness;
        }
    }

    for (int i = 0; i < FoodNumber; ++i) {
        NectarSource[i].rfitness=(0.9*(NectarSource[i].fitness/maxfit))+0.1;
    }
}

void sendOnlookerBees() { //采蜜蜂与观察蜂交流，观察蜂更改信息
    int i,j,t,k;
    double R_choosed; //被选中的概率
    int param2change;
    double Rij;//[-1,1]之间的随机数
    i=0;
    t= 0;
    while(t<FoodNumber){
        R_choosed=random(0,1);
        if(R_choosed<NectarSource[i].rfitness) {  //根据被选择的概率选择
            t++;
            param2change=(int)random(0,D);

            /*****选取不等于i的k*********/
            while(1) {
                k = (int)random(0,FoodNumber);
                if(k!=i) {
                    break;
                }
            }

            for (j = 0; j < D; ++j) {
                OnLooker[i].code[j]=NectarSource[i].code[j];
            }

            /***更新信息****/
            Rij=random(-1,1);
            OnLooker[i].code[param2change]=NectarSource[i].code[param2change]+Rij*(NectarSource[i].code[param2change]-NectarSource[k].code[param2change]);

            /*****判断是否越界******/
            if (OnLooker[i].code[param2change]>ub) {
                OnLooker[i].code[param2change]=ub;
            }

            if (OnLooker[i].code[param2change]<lb) {
                OnLooker[i].code[param2change]=lb;
            }
            OnLooker[i].trueFit=calculationTruefit(OnLooker[i]);
            OnLooker[i].fitness=calculationFitness(OnLooker[i].trueFit);

            /****贪婪选择策略*******/
            if (OnLooker[i].trueFit<NectarSource[i].trueFit) {
                for(j=0;j<D;j++) {
                    NectarSource[i].code[j]=OnLooker[i].code[j];
                }
                NectarSource[i].trail=0;
                NectarSource[i].trueFit=EmployedBee[i].trueFit;
                NectarSource[i].fitness=EmployedBee[i].fitness;
            }else {
                NectarSource[i].trail++;
            }
        }
        i++;
        if(i==FoodNumber) {
            i=0;
        }
    }
}

void sendScoutBees() {
    int maxtrialindex,i,j;
    double R;
    maxtrialindex=0;
    for ( i = 0; i < FoodNumber; ++i) {
        if(NectarSource[i].trail>NectarSource[maxtrialindex].trail) {
            maxtrialindex=i;
        }
    }
    if(NectarSource[maxtrialindex].trail>=limit) {
        /*****重新初始化***********/
        for (j = 0; j < D; ++j) {
            R=random(0,1);
            NectarSource[maxtrialindex].code[j]=lb+R*(ub-lb);
        }
        NectarSource[maxtrialindex].trail =0;
        NectarSource[maxtrialindex].trueFit=calculationTruefit(NectarSource[maxtrialindex]);
        NectarSource[maxtrialindex].fitness=calculationFitness(NectarSource[maxtrialindex].trueFit);
    }
}

void MemorizeBestSource()//保存最优的蜜源
{
    int i,j;
    for(i=1;i<FoodNumber;i++) {
        if(NectarSource[i].trueFit<BestSource.trueFit) {
            for (int j = 0; j< D; ++j) {
                BestSource.code[j]=NectarSource[i].code[j];
            }
            BestSource.trueFit=NectarSource[i].trueFit;
        }
    }
}