#include "semaphores.h"

void seminit(int *idsem, int val) {
	int rc = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
	if (rc == -1) {
		printf("No se pudo obtener el semáaforo de parte del sistema\n");
		exit(-1);
	}

	*idsem = rc;

	rc = semctl(*idsem, 0, SETVAL, val);
	if (rc == -1) {
		printf("No se pudo asignar el valor inicial al semáforo\n");
		exit(-1);
	}
}

void semwait(int idsem) {
	struct sembuf *sops = (struct sembuf *) malloc(sizeof(struct sembuf));
	sops[0].sem_num = 0;
	sops[0].sem_op = -1;
	sops[0].sem_flg = 0;

	if (semop(idsem, sops, 1) == -1) {
		printf("No se pudo decrementar el semáforo\n");
		exit(-1);
	}
}

void semsignal(int idsem) {
	struct sembuf *sops = (struct sembuf *) malloc(sizeof(struct sembuf));
	sops[0].sem_num = 0;
	sops[0].sem_op = 1;
	sops[0].sem_flg = 0;

	if (semop(idsem, sops, 1) == -1) {
		printf("No se pudo incrementar el semáforo\n");
		exit(-1);
	}
}