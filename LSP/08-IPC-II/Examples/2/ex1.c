#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  /* make it a 1K shared memory segment */

int main(int argc, char *argv[])
    {
        key_t key;
        int shmid;
        char *data;
        int mode;
		
		int c;

        if (argc > 2) {
            fprintf(stderr, "usage: shmdemo [data_to_write]\n");
            exit(1);
        }

        /* make the key: */
        if ((key = ftok("Wednesday", 'R')) == -1) {
            perror("ftok");
            exit(1);
        }

				fprintf(stderr, "arg1=%s, arg2=%c key=%#x\n","Wednesday",'R',key);

        if ((key = ftok("Wednesday", 'Z')) == -1) {
            perror("ftok");
            exit(1);
        }

				fprintf(stderr, "arg1=%s, arg2=%c key=%#x\n","Wednesday",'Z',key);

	return 0;
}
