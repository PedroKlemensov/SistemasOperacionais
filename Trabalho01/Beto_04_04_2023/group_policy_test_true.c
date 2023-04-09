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



typedef struct Prioridade {
    PCB* tree[10];
}Prioridade;

Prioridade* swap(Prioridade self, int i , int j) {
    Prioridade* temp = self.tree[i];
    self.tree[i] = self.tree[j];
    self.tree[j]=temp;
}

Prioridade* go_down(Prioridade self, int i){
    int j = (i + 1) * 2;
    int n = sizeof(self.tree);
    if (j <= n) {
            if( j < n) {
                if (self.tree[j]->prioridade < self.tree[j - 1]->prioridade) {
                    j++;
                }
            }
            if (self.tree[i]->prioridade > self.tree[j-1]->prioridade) {
                swap(self , i , j-1);
                go_down(self, j-1);
            }
    }
}

Prioridade* go_up (Prioridade self, int i) {
    if (i == 0) {
        return 0;
    }
    int j = (i - 1) / 2;   // era um comentario de dois ou dividido por 2 ou multiplizar por 2?
    if (self.tree[i]->prioridade < self.tree[j]->prioridade) {
        swap(self, i, j);
        go_up(self, j);
    }
    return 0;

}

Prioridade* push_prioridade(Prioridade self, PCB node) {
    self.tree[0]= &node;
    if (sizeof(self.tree) == 1) {
        return 0;
    }else{
        go_up(self, sizeof(self.tree) - 1);
        return 0;
    }
}



Prioridade* pop_prioridade(Prioridade self) {
    if (sizeof(self.tree) > 0) {
        Prioridade* temp = self.tree[0];
        self.tree[0] = self.tree[-1];
        pop_prioridade(self);
        go_down(self , 0);
        return temp;
    }
    return NULL;
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


    int turnaround_PRIORIDADE[5];
    int espera_PRIORIDADE[5];
    struct Prioridade fila_prio;
    //fila.size=0;


    for (int i = 0; i < PROCESS ; i++) {
        lista_de_PCBS[i].burst = lista_de_burst[i];
        espera_PRIORIDADE[i]= - lista_de_burst[i];
        turnaround_PRIORIDADE[i]=0;
        push_prioridade(fila_prio,lista_de_PCBS[i]);
    }

    for (int i = 0 ; i < PROCESS ; i++) {
        lista_de_PCBS[i].burst = lista_de_burst[i];
        push_prioridade(fila_prio , lista_de_PCBS[i]);
    }

    int i;
    for(i = 0; i < sizeof(fila_prio.tree) ; i++){
    printf("PID:%d|CHEGADA:%d|BURST:%d|PRIORIDADE:%d\n", fila_prio.tree[i]->pid, fila_prio.tree[i]->chegada, fila_prio.tree[i]->burst,fila_prio.tree[i]->prioridade);
    }


    node = pop_prioridade(fila_prio);
    int tt;
    while (node != NULL) {
        while (node->burst >0) {
            printf("t:%d, PID:%d|BURST: %d", t, node->pid, node->burst);
            tt ++;
            node->burst -=1;
            if (node->burst == 0) {
                turnaround_PRIORIDADE[node->pid] = t - node->chegada;
                espera_PRIORIDADE[node->pid] += turnaround_PRIORIDADE[node->pid];
            }
        }
        node = pop_prioridade(fila_prio);
    }













    return 0;
}
