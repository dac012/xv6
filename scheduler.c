#include <stdio.h>
#include <stdlib.h>

#define MAXPROC 10
#define DEFAULT_PRIORITY 5
#define NPRIORITIES 10

typedef enum {RUNNABLE, RUNNING, SLEEPING} estado;

struct procTablaPrioridad {
    int primero;
    int ultimo;
};

struct procTablaPrioridad** tablaPrioridad;

struct proc {
    int pid;
    int priority;
    int status;
    int sig;
};
struct proc procesos[MAXPROC];

void creaProceso(int pid) {
    procesos[pid].pid = pid;
    procesos[pid].priority = DEFAULT_PRIORITY;
    procesos[pid].sig = -1;
    procesos[pid].status = RUNNABLE;
    if(tablaPrioridad[DEFAULT_PRIORITY] == NULL) {
        tablaPrioridad[DEFAULT_PRIORITY] = malloc(sizeof(struct procTablaPrioridad));
        tablaPrioridad[DEFAULT_PRIORITY]->primero = pid;
    } else {
        procesos[tablaPrioridad[DEFAULT_PRIORITY]->ultimo].sig = pid;
    }
    tablaPrioridad[DEFAULT_PRIORITY]->ultimo = pid;
}

void setPriority(int newPriority, int pid) {
    int primeroAntiguo = tablaPrioridad[procesos[pid].priority]->primero;
    if(procesos[pid].sig == -1) {
        tablaPrioridad[procesos[pid].priority]->ultimo = -1;
        if(primeroAntiguo == pid) {
            free(tablaPrioridad[procesos[pid].priority]);
        } else {
            while(procesos[primeroAntiguo].sig != -1) {
                primeroAntiguo = procesos[primeroAntiguo].sig;
            }
            tablaPrioridad[procesos[pid].priority]->ultimo = primeroAntiguo;
        }
    } else {
        if(primeroAntiguo == pid) {
            tablaPrioridad[procesos[pid].priority]->primero = procesos[pid].sig;
        } else {
            int buscador = 0;
            while(procesos[buscador].sig != pid) {
                buscador = buscador + 1;
            }
            procesos[buscador].sig = procesos[buscador+1].sig;
        }
    }
    procesos[pid].priority = newPriority;
    if(tablaPrioridad[newPriority] == NULL) {
        tablaPrioridad[newPriority] = malloc(sizeof(struct procTablaPrioridad));
        tablaPrioridad[newPriority]->primero = pid;
    } else {
        procesos[tablaPrioridad[newPriority]->ultimo].sig = pid;
    }
    tablaPrioridad[newPriority]->ultimo = pid;
    procesos[pid].sig = -1;
}

void ejecutar() {
    int pEjecutable = -1;
    for(int i=0; i<NPRIORITIES; i=i+1) {
        if(tablaPrioridad[i] != NULL) {
            pEjecutable = tablaPrioridad[i]->primero;
            while(pEjecutable != -1) {
                if(procesos[pEjecutable].status == RUNNABLE) {
                    procesos[pEjecutable].status = RUNNING;
                    printf("EJECUTANDO: %d\n", pEjecutable);
                    procesos[pEjecutable].status = SLEEPING;
                }
                pEjecutable = procesos[pEjecutable].sig;
            }
        }
    }
}

int main(void) {
    tablaPrioridad = malloc(NPRIORITIES*sizeof(struct procTablaPrioridad*));

    for(int i=0; i<MAXPROC; i=i+1) {
        creaProceso(i);
    }

    setPriority(0, 0);
    setPriority(0, 1);
    setPriority(0, 0);

    ejecutar();

    int sig = tablaPrioridad[5]->primero;
    while(procesos[sig].sig != -1) {
        printf("Prioridad: %d, proceso: %d\n", procesos[sig].priority, procesos[sig].pid);
        sig = procesos[sig].sig;
    }
    printf("Prioridad: %d, proceso: %d\n", procesos[sig].priority, procesos[sig].pid);
    printf("Primero P5: %d\nÚltimo P5: %d\n", tablaPrioridad[5]->primero, tablaPrioridad[5]->ultimo);

    sig = tablaPrioridad[0]->primero;
    while(procesos[sig].sig != -1) {
        printf("Prioridad: %d, proceso: %d\n", procesos[sig].priority, procesos[sig].pid);
        sig = procesos[sig].sig;
    }
    printf("Prioridad: %d, proceso: %d\n", procesos[sig].priority, procesos[sig].pid);
    printf("Primero P5: %d\nÚltimo P5: %d\n", tablaPrioridad[0]->primero, tablaPrioridad[0]->ultimo);
}