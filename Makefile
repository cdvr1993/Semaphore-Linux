all: semaforos mensajes

semaforos: semaphores.c semaphores.h procesos.c
	gcc -o semaforos procesos.c semaphores.h semaphores.c -DSEMAFOROS

mensajes: mensajes.h mensajes.c procesos.c
	gcc -o mensajes mensajes.c mensajes.h procesos.c

clean:
	rm -f semaforos
	rm -f mensajes