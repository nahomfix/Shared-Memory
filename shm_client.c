#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>

#define SHMSZ 27

void main(){
	int shmid;
	key_t key;
	char *shm, *s;

	key = 5678;
	
	if((shmid = shmget(key, SHMSZ, 0666)) < 0){
		printf("Shmget error");
		exit(1);	
	}
	
	if ((shm = shmat(shmid, NULL, 0)) == (char *) -1){
		printf("Shmget error");
		exit(1);	
	}

	for (s = shm; *s != 0; s++){
		putchar(*s);
		putchar('\n');
		*shm = '*';
	}
	exit(0);

}
