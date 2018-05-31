#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>

#define SHMSZ 27

void main(){
	int shmid;
	char c;
	key_t key;
	char *shm, *s;

	key = 5678;
	
	if((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0){
		printf("shmget error");
		exit(1);	
	}

	if ((shm = shmat(shmid, NULL, 0)) == (char *) -1){
		printf("Shmget error");
		exit(1);	
	}

	s = shm;

	for (c = 'a'; c <= 'z'; c++){
		*s++ = c;
		*s = '\0';
	}

	while (*shm != '*'){
		sleep(1);
	}
	
	for (s = shm; *s != '\0'; s++){
		putchar(*s);
		putchar('\n');
	}
	exit(0);

}
