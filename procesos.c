#ifdef SEMAFOROS
	#include "semaphores.h"
#else
	#include "mensajes.h"
#endif

#define CICLOS 10

int idsem = -1;
char *pais[3]={"Peru", "Bolivia", "Colombia"};
int *g;

int main() {
	int pid;
	int status;
	int args[3];
	int i;

	srand(getpid());
	#ifdef SEMAFOROS
		seminit(&idsem, 1);
	#else
		queueinit(&idsem);
	#endif

	for (i=0;i<3;i++) {
		// Crea un nuevo proceso hijo que ejecuta la función proceso()
		pid=fork();
		if (pid==0)
			proceso(i);
	}

	for(i=0;i<3;i++)
		pid = wait(&status);

	return 0;
}

void proceso(int i) {
	int k;
	int l;

	for (k=0;k<CICLOS;k++) {
		// Entrada a la sección crítica
		#ifdef SEMAFOROS
			semwait(idsem);
		#else
			printf("Before Wait\n");
			queuewait(idsem);
		#endif
		printf("Entra %s ", pais[i]);
		fflush(stdout);
		sleep(rand() % 3);
		printf("- %s Sale\n", pais[i]);
		// Salida de la sección crítica
		#ifdef SEMAFOROS
			semsignal(idsem);
		#else
			queuesignal(idsem);
		#endif
		// Espera aleatoria fuera de la sección crítica
		sleep(rand()%3);
	}

	exit(0);
}