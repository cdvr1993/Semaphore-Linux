all: semaforos

semaforos: semaphores.c semaphores.h procesos.c
	gcc -o semaforos procesos.c semaphores.h semaphores.c