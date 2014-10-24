#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

void seminit(int *idsem, int val);
void semwait(int idsem);
void semsignal(int idsem);

void proceso(int i);