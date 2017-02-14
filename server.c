#include "common_struct.h"
#include "stdio.h"
#include "stdlib.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include "string.h"
int main(int argc, char ** argv)
{
    int key, index, lastnoverflow, temp;
    long offset;

    key = shmget(ftok("eggnzzg",0),sizeof(struct shmstruct), IPC_CREAT);
    shmstruct *const ptr = (shmstruct *)shmat(key, NULL , 0);
    if(ptr == NULL)
    {
        printf("ERROR return\n");
        return 0;
    }
    for(index = 0; index < NMESG; index++)
    {
        ptr->msgoff[index] = index * MESGSIZE;;
    }

    sem_init(&ptr->mutex, 1 , 1);
    sem_init(&ptr->nempty, 1,NMESG);
    sem_init(&ptr->nstored, 1, 0);
    sem_init(&ptr->noverflowmutex, 1, 1);

    index = 0;
    lastnoverflow = 0;
    for(;;)
    {
        sem_wait(&ptr->nstored);
        sem_wait(&ptr->mutex);
        offset = ptr->msgoff[index];
        printf("index = %d: %s\n", index, &ptr->msgdata[offset]);
        if(++index >= NMESG)
        {
            index = 0;
        }
        sem_post(&ptr->mutex);
        sem_post(&ptr->nempty);

        sem_wait(&ptr->noverflowmutex);
        temp = ptr->noverflow;
        sem_post(&ptr->noverflowmutex);
        if(temp != lastnoverflow)
        {
            printf("noverflow = %d\n", temp);
            lastnoverflow = temp;
        }

    }
      exit(0);
}

