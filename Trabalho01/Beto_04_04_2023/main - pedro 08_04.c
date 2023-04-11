#include <stdio.h>
#include <stdlib.h>


typedef struct PCB PCB; // declaração avançada da struct PCB

typedef struct FCFS FCFS;

 struct PCB
{
    int pid;
    int chegada;
    int burst;
    int prioridade;
     //o prev e  next sao ponteiros para que eles possam apontar a memoria do seus PCBS
     PCB* prev;
     PCB* next;
};

struct FCFS
{
    int size;
    FCFS* head;
    FCFS* tail;
    FCFS* (*test_push)(PCB pcb);
    FCFS* (*test_pop)();

};

FCFS push(FCFS self , PCB pcb){
    if (self.size ==0 ){
        self.head = pcb;
        self.tail = self.head;
    }else{
    self.tail = pcb;
    }
    self.size += 1;

}






int main() {

    // esse e o contrutor, para eu pegar o ponteiro de qualquer pcb ele tem que que ja te sido criado
    // entao n posso coloacar o netx pcb2 no pcb1 pq ele n foi criado ainda
    // para como o next e o prev sao pointeiros tem que coloacar o "&" antes declarar qual o pcb qual
    //pcb eles sao ligado EX:"&pcb1"

    PCB pcb1 = {1,0,2,1,NULL,NULL};
    PCB pcb2 = {2,0,2,2,&pcb1,NULL};

    int i;
    int PROCESS = 5;
    int lista_burst[PROCESS];
    PCB lista_PCBS[PROCESS];

    int pid;
    int chegada=0;
    int burst;
    int prioridade;


    for (i = 0; i <= PROCESS; i++){

    burst = rand() % 10;
    prioridade = rand() % 10;

    if (i<2){
        chegada=0;
    }else{
        chegada = i - 1;
    }

    PCB pcb;
    pcb.burst = burst;
    pcb.chegada = chegada;
    pcb.pid = i;
    pcb.prioridade = prioridade;

    lista_PCBS[i]=pcb;
    lista_burst[i]=burst;

    //dar appends na lista de PCBS(PCB(i,chegada,0,prioridade))
    //dar appebds na lista de burst(burst)
    }

    //agora que o pcb2 foi criado eu declari ele como next do pcb1

    pcb1.next=&pcb2;


    //
    printf("%p\n", pcb1);// local da memoria do pcb1
    printf("%d\n", pcb1.pid);// pid do pcb1
    printf("%p\n", pcb2.prev);//local da memoria do prev do pcb2(PCB1)
    printf("%d\n", pcb2.pid);//pid do pcb2

    printf("%d\n", pcb2.prev->pid);// pegando o pcb do prev do 2
    printf("ohayo sekai,Good morning world !\n");// apenas um ola mundo
    return 0;

}
