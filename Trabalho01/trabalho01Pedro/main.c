#include <stdio.h>

typedef struct PCB PCB; // declaração avançada da struct PCB
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





int main() {
    // esse e o contrutor, para eu pegar o ponteiro de qualquer pcb ele tem que que ja te sido criado
    // entao n posso coloacar o netx pcb2 no pcb1 pq ele n foi criado ainda
    // para como o next e o prev sao pointeiros tem que coloacar o "&" antes declarar qual o pcb qual
    //pcb eles sao ligado EX:"&pcb1"
    PCB pcb1 = {1,0,2,1,NULL,NULL};
    PCB pcb2 = {2,0,2,2,&pcb1,NULL};
    //agora que o pcb2 foi criado eu declari ele como next do pcb1
    pcb1.next=&pcb2;


    //toda esse seçao de printes sao para testes  se os pcbs eseatao oks
    // es para printar os dados do pcb tem que sequir esse estrutura no "%d\n", pcb#.(o dado que vc quer)
    // caso queria o local da memoria usar p no lugar do d
    printf("%p\n", pcb1);// local da memoria do pcb1
    printf("%d\n", pcb1.pid);// pid do pcb1
    printf("%p\n", pcb2.prev);//local da memoria do prev do pcb2(PCB1)
    printf("%d\n", pcb2.pid);//pid do pcb2
    printf("%d\n", pcb2.prev->pid);// pegando o pcb do prev do 2
    printf("ohayo sekai,Good morning world !\n");// apenas um ola mundo
    return 0;

}
