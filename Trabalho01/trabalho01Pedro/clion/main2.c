//Alunos: Pedro Alexsander, Alberto Huarastaca ,Lucas Cavalcante Fontenele
//
//
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define PROCESS 5

//[2]
typedef struct PCB {
    int pid;
    int chegada;
    int burst;
    float prioridade;

    struct PCB *prev;
    struct PCB *next;
    struct PCB *dad; // ponteiro desnecessario?
}PCB;

//[5]

/*typedef struct FCFS {
//cria��o da estrutura
    PCB *head; // pode ser feito sem a necessidade do struct, pois eles s� armazenam o valor de in�cio (cabe�a0 e fim (cauda), diferente do PCB. que referenciava a s� mesmo dentro da classe.
    PCB *tail;
    int size;
}FCFS;
*/

typedef struct FCFS FCFS;
struct FCFS{
    PCB* head;
    PCB* tail;
    int size;
};

void init (FCFS *fila){
    fila->head = NULL;
    fila->tail = NULL;
    fila->size = 0;
}

void push_FCFS(FCFS *fila, PCB *pcb){
    if (fila->size == 0) {
        fila->head = pcb;
        fila->tail = pcb;
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
typedef struct {
    PCB **tree;
    int size;
}PRIORIDADE;

void swap(PCB **tree, int i, int j){
    PCB *temp = tree[i];
    tree[i] = tree[j];
    tree[j] = temp;
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
        swap(prioridade->tree, i, j - 1);
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
        swap(prioridade->tree, i, j);
        go_up(prioridade, j);
}
}

void push_Prioridade(PRIORIDADE *prioridade, PCB *pcb) {
    prioridade->tree = (PCB **)realloc(prioridade->tree, (prioridade->size + 1) * sizeof(PCB *));
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

float mean(float *lista) {
    float s = 0;
    for (int i = 0; i < PROCESS; i++) {
        s += lista[i];
    }
    return s / PROCESS;
}

int main() {

    srand(time(NULL));

    FCFS fila;
	init(&fila);

    PCB* lista_PCBS[PROCESS];
    float turnaround_FCFS[PROCESS];
    float espera_FCFS[PROCESS];
    int lista_Burst[PROCESS];




    int chegada = 0;

    for (int i = 0 ; i<PROCESS ; i++) {

        int burst = rand() % 10 + 1;
        int prioridade = rand() % 10 + 1;

        if (i < 2) {
            chegada = rand() % 10 + 1;
        } else {
            chegada = i - 1;
        }

        PCB *pcb = (PCB *)malloc(sizeof(PCB));
        pcb->pid = i;
        pcb->chegada = chegada;
        pcb->burst = 0;
        pcb->prioridade = prioridade;
        pcb->prev = NULL;
        pcb->next = NULL;
        pcb->dad = NULL;

        lista_PCBS[i] = pcb;
        lista_Burst[i] = burst;
    }



    for (int i = 0; i < PROCESS ; i++) {

        lista_PCBS[i]->burst = lista_Burst[i];
        espera_FCFS[i]= - lista_Burst[i];
        turnaround_FCFS[i]= 0;
        push_FCFS(&fila,lista_PCBS[i]);
    }


    PCB* node_FCFS = fila.head;
    while (node_FCFS != NULL) {
        printf("PID:%d|CHEGADA:%d|BURST:%d\n", node_FCFS->pid, node_FCFS->chegada, node_FCFS->burst);
        node_FCFS = node_FCFS->next;
    }


    node_FCFS = pop(&fila);
    int t = 0;
    while(node_FCFS != NULL) {
        while (node_FCFS->burst > 0){
                        printf("t:%d, PID:%d|BURST:%d\n", t, node_FCFS->pid, node_FCFS->burst);
            t++;
            node_FCFS->burst -= 1;
            if (node_FCFS->burst == 0) {
                turnaround_FCFS[node_FCFS->pid] = t - node_FCFS->chegada;
                espera_FCFS[node_FCFS->pid] += turnaround_FCFS[node_FCFS->pid];
            }
        }
        node_FCFS=pop(&fila);
    }
    printf("Fim do FCFS \n");
    printf("-------------------------------------\n");

    float turnaround_PRIORIDADE[PROCESS];
    float espera_PRIORIDADE[PROCESS];
    PRIORIDADE fila_prior_1;
    fila_prior_1.tree = NULL;
    fila_prior_1.size = 0;

    chegada = 0;

    for (int i=0;i<PROCESS;i++) {

        lista_PCBS[i]->burst = lista_Burst[i];
        espera_PRIORIDADE[i]= - lista_Burst[i];
        turnaround_PRIORIDADE[i] = 0;
        push_Prioridade(&fila_prior_1 , lista_PCBS[i]);

    }



    for (int i=0;i<PROCESS;i++) {
    lista_PCBS[i]->burst = lista_Burst[i];
    push_Prioridade(&fila_prior_1 , lista_PCBS[i]);
    }
    for (int i =0 ; i < PROCESS; i++) {
        printf("PID:%d|CHEGADA:%d|BURST:%d|PRIORIDADE:%f\n", fila_prior_1.tree[i]->pid , fila_prior_1.tree[i]->chegada , fila_prior_1.tree[i]->burst , fila_prior_1.tree[i]->prioridade);

    }

    PCB *node = pop_Prioridade(&fila_prior_1);
    t = 0;
    while (node != NULL) {
        while (node->burst > 0) {
            printf("t:%d, PID:%d|BURST:%d\n", t, node->pid, node->burst);
            t++;
            node->burst -=1;
            if (node->burst == 0) {
                turnaround_PRIORIDADE[node->pid] = t - node->chegada;
                espera_PRIORIDADE[node->pid] += turnaround_PRIORIDADE[node->pid];
            }
        }
        node = pop_Prioridade(&fila_prior_1);
    }
    printf("Fim do PRIORIDADE \n");
    printf("-------------------------------------\n");

    float turnaround_SJF[PROCESS];
    float espera_SJF[PROCESS];
    PRIORIDADE fila_SJF;
    fila_SJF.tree = NULL;
    fila_SJF.size = 0;

    for (int i = 0; i < PROCESS ; i++) {
        lista_PCBS[i]->burst = lista_Burst[i];
        espera_SJF[i]= - lista_Burst[i];
        turnaround_SJF[i] = 0;
        PCB *node = lista_PCBS[i];
        node->prioridade = 1 - 1 / (float)node->burst;
        push_Prioridade(&fila_SJF , node);
    }

    for (int i = 0 ; i < PROCESS ; i++){
        printf("PID:%d|CHEGADA:%d|BURST:%d|PRIORIDADE:%f\n", fila_SJF.tree[i]->pid , fila_SJF.tree[i]->chegada , fila_SJF.tree[i]->burst , fila_SJF.tree[i]->prioridade);

    }

    //problema abaixo;;

    node = pop_Prioridade(&fila_SJF);
    t=0;
    while (node != NULL) {
        while (node->burst > 0) {
            printf("t:%d, PID:%d|BURST:%d\n", t, node->pid, node->burst);
            t++;
            node->burst -=1;
            if (node->burst == 0) {
                turnaround_SJF[node->pid] = t - node->chegada;
                espera_SJF[node->pid] += turnaround_SJF[node->pid];
            }
        }
        node=pop_Prioridade(&fila_SJF);
    }

    printf("Fim do SJF \n");
    printf("-------------------------------------\n");

    float turnaround_RR[PROCESS];
    float espera_RR[PROCESS];
    FCFS fila_rr;
    init(&fila_rr);

    for (int i=0;i<PROCESS;i++){
        lista_PCBS[i]->burst = lista_Burst[i];
        espera_RR[i]= - lista_Burst[i];
        turnaround_RR[i] = 0;
        push_FCFS(&fila_rr,lista_PCBS[i]);
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
            push_FCFS(&fila_rr , node);
        }
        node = pop(&fila_rr);
    }
    printf("Fim do RR \n");
    printf("-------------------------------------\n");




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


