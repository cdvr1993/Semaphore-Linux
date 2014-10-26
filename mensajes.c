#include "mensajes.h"

struct message {
   long type;
   char text[1];
};

void queueinit(int *idqueue) {
	*idqueue = msgget(IPC_PRIVATE, IPC_CREAT | 0666);

	if (*idqueue == -1) {
		printf("No fue posible crear la copia\n");
		exit(-1);
	}

	queuesignal(*idqueue);
}

void queuewait(int idqueue) {
	struct message msg;
	if (msgrcv(idqueue, &msg, sizeof(msg.text), 0, 0) == -1) {
		printf("No se pudo recibir el mensaje\n");
		exit(-1);
	}
}

void queuesignal(int idqueue) {
	struct message msg;
	msg.type = 1;
	strcpy(msg.text, "");

	if (msgsnd(idqueue, (void*) &msg, sizeof(msg.text), 0) == -1) {
		printf("No fue posible enviar el mensaje\n");
		exit(-1);
	}
}