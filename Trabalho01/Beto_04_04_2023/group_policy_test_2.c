#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct PCB {
    int pid;
    int chegada;
    int burst;
    int prioridade;
    struct PCB* prev;
    struct PCB* next;
    struct PCB* dad;
} PCB;

int PROCESS = 5;
PCB lista_de_PCBS[5];
int lista_de_burst[5];

typedef struct FCFS {
    PCB* head;
    PCB* tail;
    int size;
} FCFS;

void push(FCFS* fila, PCB* pcb) {
    if (fila->size == 0) {
        fila->head = pcb;
        fila->tail = fila->head;
    } else {
        fila->tail->next = pcb;
        fila->tail = fila->tail->next;
    }
    fila->size++;
}

PCB* pop(FCFS* fila) {
    if (fila->size == 0) {
        return NULL;
    }
    PCB* temp = fila->head;
    fila->head = fila->head->next;
    fila->size--;
    return temp;
}

int main() {
    srand((unsigned long)time(0));

    int chegada = 0;
    for (int i = 0; i < PROCESS; i++) {
        int burst = rand() % 10;
        int prioridade = rand() % 10;
        if (i < 2) {
            chegada = 0;
        } else {
            chegada = i - 1;
        }
        lista_de_PCBS[i].pid = i;
        lista_de_PCBS[i].chegada = chegada;
        lista_de_PCBS[i].burst = 0;
        lista_de_PCBS[i].prioridade = prioridade;
        lista_de_PCBS[i].prev = NULL;
        lista_de_PCBS[i].next = NULL;
        lista_de_PCBS[i].dad = NULL;
        lista_de_burst[i] = burst;
    }

    FCFS fila;
    fila.head = NULL;
    fila.tail = NULL;
    fila.size = 0;

    int turnaround_FCFS[5];
    int espera_FCFS[5];
    for (int i = 0; i < PROCESS; i++) {
        lista_de_PCBS[i].burst = lista_de_burst[i];
        espera_FCFS[i] = -lista_de_burst[i];
        turnaround_FCFS[i] = 0;
        push(&fila, &lista_de_PCBS[i]);
    }

    PCB* node = fila.head;
    while (node != NULL) {
        printf("PID:%d|CHEGADA:%d|BURST:%d\n", node->pid, node->chegada, node->burst);
        node = node->next;
    }

    node = pop(&fila);
    int t = 0;
    while (node != NULL) {
        while (node->burst > 0) {
            printf("t:%d, PID:%d|BURST:%d\n", t, node->pid, node->burst);
            t++;
            node->burst--;
            if (node->burst == 0) {
                turnaround_FCFS[node->pid] = t - node->chegada;
                espera_FCFS[node->pid] += turnaround_FCFS[node->pid];
            }
        }
        node = pop(&fila);
    }

    return 0;
}
