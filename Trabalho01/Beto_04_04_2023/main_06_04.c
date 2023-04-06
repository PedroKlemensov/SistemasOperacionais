#include <stdio.h>
#include <stdlib.h>


typedef struct
{
    int pid;
    int chegada;
    int burst;
    int prioridade;
    PCB prev = NULL;
    PCB next = NULL;


} PCB;

typedef struct
{

    PCB head = NULL;
    PCB tail = NULL;
    int size;

    PCB push(PCB pcb){

        if (size==0){
            head = pcb;
            tail = head;
        }else{
            tail.next = pcb;
            tail=tail.next;
        }
        size++;
    }


    PCB pop(){

        if (size==0){
            return NULL;
        }
        PCB temp = head;
        head = head.next;
        size--;
        return temp;
    }

} FCFS;



int main()
{
    int i;
    int PROCESS = 5;
    int lista_burst[PROCESS];
    PCB lista_PCBS[PROCESS];

    int pid;
    int chegada=0;
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
    PCB pcb;

    pcb.burst = burst;
    pcb.chegada = chegada;
    pcb.pid = i;
    pcb.prioridade = prioridades;

    lista_PCBS[i]=pcb;
    lista_burst[i]=burst;

    //dar appends na lista de PCBS(PCB(i,chegada,0,prioridade))
    //dar appebds na lista de burst(burst)
    }



    //PARTE [6] PAGINA 2
    int turnaround_FCFS[PROCESS];
    int espera_FCFS[PROCESS];
    FCFS fila;

    for (int i = 0; i < PROCESS ; i++) {
        lista_PCBS[i].burst=lista_burst[i];
        espera_FCFS[i]= -lista_burst[i];
        turnaround_FCFS[i]=0;
        fila.push(lista_PCBS[i])
    }


    //parte [7] pagina 2

    PCB node = fila.head;
    while (node != NULL) {
        while (node.burst > 0) {
            printf(pid, chegada, burst);
            node.next;
        }
    }

    //parte [8] execução pag 2 e 3


    node=fila.pop();
    int t = 0;
        while (node != NULL) {
            while (node.burst > 0) {
                printf(t,pid,burst);
                t++;
                node.burst--;
                if (node.burst == 0) {
                    turnaround_FCFS[node.pid] = t - node.chegada;
                    espera_FCFS[node.pid] += turnaround_FCFS[node.pid];
                }
            }
            node=fila.pop();
        }






    printf("All good");
    return 0;
}





