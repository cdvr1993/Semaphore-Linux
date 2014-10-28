#include "semaphores.h"

void seminit(int *idsem, int val) {
	// Obtenemos un semáforo con permisos de lectura y escritura
	int rc = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);

	// Comprobamos si se creó correctamente
	if (rc == -1) {
		printf("No se pudo obtener el semáforo de parte del sistema\n");
		exit(-1);
	}

	*idsem = rc;

	// Le asignamos el valor inicial al semáforo
	rc = semctl(*idsem, 0, SETVAL, val);

	// Comprobamos si se asigno el valor inicial correctamente
	if (rc == -1) {
		printf("No se pudo asignar el valor inicial al semáforo\n");
		exit(-1);
	}
}

void semwait(int idsem) {
	// Creamos la estructura que nos permitirá realizar operaciones atómicas
	struct sembuf *sops = (struct sembuf *) malloc(sizeof(struct sembuf));
	// Se refiere al índice del arreglo de semáforos que será afectado
	sops[0].sem_num = 0;
	// Se refiere a que le restará uno
	sops[0].sem_op = -1;
	// Se refiere a que debe esperar a que se realice la operación
	sops[0].sem_flg = 0;

	// Comprobamos si se realizaron correctamente las operaciones
	// especificadas por la estructura
	if (semop(idsem, sops, 1) == -1) {
		printf("No se pudo decrementar el semáforo\n");
		exit(-1);
	}
}

void semsignal(int idsem) {
	// Creamos la estructura que nos permitirá realizar operaciones atómicas
	struct sembuf *sops = (struct sembuf *) malloc(sizeof(struct sembuf));
	sops[0].sem_num = 0;
	// Se refiere a que le sumará uno
	sops[0].sem_op = 1;
	sops[0].sem_flg = 0;

	// Comprobamos si se realizaron correctamente las operaciones
	// especificadas por la estructura
	if (semop(idsem, sops, 1) == -1) {
		printf("No se pudo incrementar el semáforo\n");
		exit(-1);
	}
}