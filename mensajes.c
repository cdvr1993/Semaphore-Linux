#include "mensajes.h"

void queueinit(int *idqueue) {
	*idqueue = msgget(IPC_PRIVATE, IPC_CREAT | 0666);

	if (*idqueue == -1) {
		printf("No fue posible crear la copia\n");
		exit(-1);
	}

	queuesignal(*idqueue);
}

void queuewait(int idqueue) {
	if (msgrcv(idqueue, NULL, 0, 0, 0) == -1) {
		printf("No se pudo recibir el mensaje\n");
		exit(-1);
	}
}

void queuesignal(int idqueue) {
	if (msgsnd(idqueue, NULL, 0, 0) == -1) {
		printf("No fue posible enviar el mensaje\n");
		exit(-1);
	}
}