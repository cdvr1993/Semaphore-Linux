#include "mensajes.h"

struct message {
   long type;
   char text[1];
};

void queueinit(int *idqueue) {
	// Creamos la cola de mensajes con permisos de lectura y escritura
	*idqueue = msgget(IPC_PRIVATE, IPC_CREAT | 0666);

	// Comprobamos si se pudo crear
	if (*idqueue == -1) {
		printf("No fue posible crear la cola\n");
		exit(-1);
	}

	// Mandamos un mensaje inicial para que no se trabe al comienzo
	queuesignal(*idqueue);
}

void queuewait(int idqueue) {
	// Creamos una variable mensaje y procedemos a traernos el siguiente
	// mensaje de la cola
	struct message msg;
	if (msgrcv(idqueue, &msg, sizeof(msg.text), 0, 0) == -1) {
		printf("No se pudo recibir el mensaje\n");
		exit(-1);
	}
}

void queuesignal(int idqueue) {
	// Creamos un mensaje nuevo y le pasamos un string vacío
	struct message msg;
	msg.type = 1;
	strcpy(msg.text, "");

	// Mandamos el mensaje a la cola
	if (msgsnd(idqueue, (void*) &msg, sizeof(msg.text), 0) == -1) {
		printf("No fue posible enviar el mensaje\n");
		exit(-1);
	}
}