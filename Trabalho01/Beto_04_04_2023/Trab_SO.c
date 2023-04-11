#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define PROCESS 5

//[2]
typedef struct PCB {
    int pid;
    int chegada;
    int burst;
    double prioridade;

    struct PCB *prev;
    struct PCB *next;
    struct PCB *dad; // ponteiro desnecessario?
}PCB;

//[5]
typedef struct FCFS {
//criação da estrutura
    PCB *head; // pode ser feito sem a necessidade do struct, pois eles só armazenam o valor de início (cabeça0 e fim (cauda), diferente do PCB. que referenciava a sí mesmo dentro da classe.
    PCB *tail;
    int size;
}FCFS;

void init (FCFS *fila){
    fila->head = NULL;
    fila->tail = NULL;
    fila->size = 0;
}

void push(FCFS *fila, PCB *pcb){
    if (fila->size == 0) {
    fila->head = pcb;
    fila->tail = fila->head;
    } else {
    fila->tail->next = pcb;
    fila->tail = fila->tail->next;
    }
    fila->size += 1;
}

PCB* pop(FCFS *fila){
    if (fila->size == 0){
    return NULL;
    }
    PCB* temp = fila->head;
    fila->head = fila->head->next;
    fila->size -= 1;
return temp;
}

//[11]
typedef struct PRIORIDADE{
    PCB *tree[PROCESS];
    int size;
}PRIORIDADE;

void init_Prioridade(PRIORIDADE *prioridade) {
    for (int i = 0; i < PROCESS; i++){
        prioridade->tree[i] = NULL;
    }
    prioridade->size = 0;
}

void swap(PRIORIDADE *prioridade, int i, int j){
    PCB *temp = prioridade->tree[i];
    prioridade->tree[i] = prioridade->tree[j];
    prioridade->tree[j] = temp;
}

void go_down(PRIORIDADE *prioridade, int i){
    int j = (i + 1) * 2;
    int n = prioridade->size;

    if (j <= n){
        if (j < n){
            if (prioridade->tree[j]->prioridade < prioridade->tree[j - 1]->prioridade){
                j++;
        }
    }
    else if (prioridade->tree[i]->prioridade > prioridade->tree[j - 1]->prioridade){
        swap(prioridade, i, j - 1);
        go_down(prioridade, j - 1);
        }
    }
}


void go_up(PRIORIDADE *prioridade, int i){
    if (i == 0){
    return;
}
int j = (i - 1) / 2;
    if (prioridade->tree[i]->prioridade < prioridade->tree[j]->prioridade){
        swap(prioridade, i, j);
        go_up(prioridade, j);
}
return;
}

void push_Prioridade(PRIORIDADE *prioridade, PCB *pcb) {
    prioridade->tree[prioridade->size] = pcb;
    prioridade->size++;
    if (prioridade->size > 1) {
        go_up(prioridade, prioridade->size - 1);
    }
}

PCB* pop_Prioridade(PRIORIDADE *prioridade) {
    if (prioridade->size > 0) {
        PCB *temp = prioridade->tree[0];
        prioridade->tree[0] = prioridade->tree[prioridade->size - 1];
        prioridade->size--;
        go_down(prioridade, 0);
        return temp;
    }
    return NULL;
}

int main() {
    //int PROCESS = 5;
    PCB lista_PCBS[PROCESS];
    int lista_Burst[PROCESS];

    srand((unsigned long)time(0));

    int chegada;

    for (int i = 0 ; i<PROCESS ; i++) {

        int burst = rand() % 10 + 1;
        int prioridade = rand() % 10 + 1;

        if (i < 2) {
            chegada = rand() % 10 + 1;
        } else {
            chegada = i - 1;
        }

        lista_PCBS[i].pid = i;
        lista_PCBS[i].chegada = chegada;
        lista_PCBS[i].burst = 0;
        lista_PCBS[i].prioridade = prioridade;
        lista_PCBS[i].prev = NULL;
        lista_PCBS[i].next = NULL;
        lista_PCBS[i].dad = NULL;

        lista_Burst[i] = burst;
    }

    int turnaround_FCFS[PROCESS];
    int espera_FCFS[PROCESS];
    FCFS fila = {NULL , NULL  ,0} ;

    for (int i = 0; i < PROCESS ; i++) {

        lista_PCBS[i].burst = lista_Burst[i];
        espera_FCFS[i]= - lista_Burst[i];
        turnaround_FCFS[i]= rand() % 5 + 1;
        push(&fila,&lista_PCBS[i]);
    }

    PCB* node = fila.head;

    while (node != NULL) {
        printf("PID:%d|CHEGADA:%d|BURST:%d\n", node->pid, node->chegada, node->burst);
        sleep(1);
        node = node->next;
    }


    node = pop(&fila);
    int t;
    while(node != NULL) {
        while (node->burst > 0){
                        printf("t:%d, PID:%d|BURST:%d\n", t, node->pid, node->burst);
            t++;
            node->burst -= 1;
            if (node->burst == 0) {
                turnaround_FCFS[node->pid] = t - node->chegada;
                espera_FCFS[node->pid] += turnaround_FCFS[node->pid];
            }
        }
        node=pop(&fila);
    }
    printf("Fim do FCFS \n");
    printf("-------------------------------------\n");

    int turnaround_PRIORIDADE[PROCESS];
    int espera_PRIORIDADE[PROCESS];
    PRIORIDADE fila_prior_1={5,0};

    for (int i=0;i<PROCESS;i++) {

        lista_PCBS[i].burst = lista_Burst[i];
        espera_PRIORIDADE[i]= - lista_Burst[i];
        turnaround_PRIORIDADE[i] = rand() % 5 + 1;
        push_Prioridade(&fila_prior_1 , &lista_PCBS[i]);

    }

    PRIORIDADE fila_prior_2={5,0};

    for (int i=0;i<PROCESS;i++) {
    lista_PCBS[i].burst = lista_Burst[i];
    push_Prioridade(&fila_prior_2 , &lista_PCBS[i]);
    }
    for (int i =0 ; i < PROCESS; i++) {
        printf("PID:%d|CHEGADA:%d|BURST:%d|PRIORIDADE:%f\n", fila_prior_1.tree[i]->pid , fila_prior_1.tree[i]->chegada , fila_prior_1.tree[i]->burst , fila_prior_1.tree[i]->prioridade);
        sleep(1);
    }

    node = pop_Prioridade(&fila_prior_1);
    t=0;
    while (node != NULL) {
        while (node->burst > 0) {
            printf("t:%d, PID:%d|BURST:%d\n", t, node->pid, node->burst);
            t++;
            node->burst -=1;
            if (node->burst ==0) {
                turnaround_PRIORIDADE[node->pid] = t - node->chegada;
                espera_PRIORIDADE[node->pid] += turnaround_PRIORIDADE[node->pid];
            }
        }
        node=pop_Prioridade(&fila_prior_1);
    }
    printf("Fim do PRIORIDADE \n");
    printf("-------------------------------------\n");

    int turnaround_SJF[PROCESS];
    int espera_SJF[PROCESS];
    PRIORIDADE fila_SJF={5,0};

    for (int i = 0; i < PROCESS ; i++) {
        lista_PCBS[i].burst=lista_Burst[i];
        espera_SJF[i]= - lista_Burst[i];
        turnaround_SJF[i] = 0; //rand() % 10 + 1;
        node = &lista_PCBS[i];
        node->prioridade = 1 - 1 / node->burst;
        push_Prioridade(&fila_SJF , &node);
    }

    for (int i = 0 ; i < PROCESS ; i++){
        printf("PID:%d|CHEGADA:%d|BURST:%d|PRIORIDADE:%d\n", fila_SJF.tree[i]->pid , fila_SJF.tree[i]->chegada , fila_SJF.tree[i]->burst , fila_SJF.tree[i]->prioridade);
        sleep(1);
    }

    //problema abaixo;;

    node = pop_Prioridade(&fila_SJF);
    t=0;
    while (node != NULL) {
        while (node->burst > 0) {
            printf("t:%d, PID:%d|BURST:%d\n", t, node->pid, node->burst);
            t++;
            node->burst -=1;
            if (node->burst ==0) {
                turnaround_SJF[node->pid] = t - node->chegada;
                espera_SJF[node->pid] += turnaround_SJF[node->pid];
            }
        }
        node=pop_Prioridade(&fila_SJF);
    }

    printf("Fim do SJF \n");
    printf("-------------------------------------\n");

    FCFS fila_rr = {NULL , NULL  ,0} ;
    for (int i = 0 ; i<PROCESS ; i++) {
        lista_PCBS[i].burst = lista_Burst[i];
        push(&fila_rr , &lista_PCBS[i]);
    }

    int turnaround_RR[PROCESS];
    int espera_RR[PROCESS];
    //FCFS fila_RR = {NULL , NULL  ,0} ;

    for (int i=0;i<PROCESS;i++){
        lista_PCBS[i].burst = lista_Burst[i];
        espera_RR[i]= - lista_Burst[i];
        push(&fila_rr,&lista_PCBS[i]);
    }

    node = fila_rr.head;
    while (node != NULL) {
        printf("PID:%d|CHEGADA:%d|BURST:%d\n", node->pid, node->chegada, node->burst);
        node = node->next;
    }

    node = pop(&fila_rr);
    t=0;
    while(node != NULL) {
        int quantum = 1;
        while (quantum > 0) {
            printf("t:%d, PID:%d|BURST:%d\n", t, node->pid, node->burst);
            t += 1;
            node->burst -= 1;
            if (node->burst == 0 ) {
                turnaround_RR[node->pid] = t - node->chegada;
                espera_RR[node->pid] += turnaround_RR[node->pid];
                break;
            }
            quantum -= 1;
        }
        if (node->burst > 0){
            push(&fila_rr , &node);
        }
        node = pop(&fila_rr);
    }
    printf("Fim do RR \n");
    printf("-------------------------------------\n");


    int mean(int *lista) {
    float s = 0;
    for (int i = 0; i < PROCESS; i++) {
        s += lista[i];
    }
    return s / PROCESS;
}

    printf("Turnaround FCFS:%f \n", mean(turnaround_FCFS));
    printf("Turnaround PRIORIDADE:%f \n", mean(turnaround_PRIORIDADE));
    printf("Turnaround SJF:%f \n", mean(turnaround_SJF));
    printf("Turnaround RR:%f \n", mean(turnaround_RR));

    printf("Espera FCFS:%f \n", mean(espera_FCFS));
    printf("Espera PRIORIDADE:%f \n", mean(espera_PRIORIDADE));
    printf("Espera SJF:%f \n", mean(espera_SJF));
    printf("Espera RR:%f \n", mean(espera_RR));


printf("All good \n");
return 0;
}


