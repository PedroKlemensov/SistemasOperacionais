#include <stdio.h>
#include <stdlib.h>
//#define PROCESS = 5
//#define lista_PCBS[PROCESS]
//#define liSta_burstPROCESS]
//#define chegada = 0



struct PCB
{
    int pid;
    int chegada;
    int burst;
    int prioridade;
};

int main()
{
    int i;
    int PROCESS = 5;
    int lista_burst[PROCESS];
    struct PCB lista_PCBS[PROCESS];

    int pid;
    int chegada;
    int burst;
    int prioridades;


    for (i = 0; i <= PROCESS; i++){

    burst = rand() % 10;
    prioridades = rand() % 10;
    if (i<2){
        chegada=0;
    }else{
        chegada = i - 1;
    }
    struct PCB pcb;
    pcb.burst = burst;
    pcb.chegada = chegada;
    pcb.pid = i;
    pcb.prioridade = prioridades;
    lista_PCBS[i]=pcb;
    lista_burst[i]=burst;
    //dar appends na lista de PCBS(PCB(i,chegada,0,prioridade))
    //dar appebds na lista de burst(burst)

}




    return 0;
}





