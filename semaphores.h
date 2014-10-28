#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

// Prototipos usados en la implementación de semáforos
void seminit(int *idsem, int val);
void semwait(int idsem);
void semsignal(int idsem);

void proceso(int i);