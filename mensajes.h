#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Prototipos usados en la implementación de cola de mensajes
void queueinit(int *idqueue);
void queuewait(int idqueue);
void queuesignal(int idqueue);

void proceso(int i);