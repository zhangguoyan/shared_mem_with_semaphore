#include "common_struct.h"
#include <unistd.h>
#include <errno.h>
#include "stdio.h"
#include "stdlib.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include "string.h"
int main(int argc, char ** argv)
{
    int key, nloop, nusec;
    pid_t pid;
    char mesg[MESGSIZE];
    long offset;

    if(argc != 3)
    {
        printf("usage : client <#loops> <#usec>");
        exit(0);
    }
    nloop = atoi(argv[1]);
    nusec = atoi(argv[2]);

    key = shmget(ftok("eggnzzg",0),sizeof(struct shmstruct), IPC_CREAT);
    shmstruct *const ptr = (shmstruct *)shmat(key, NULL , 0);
    if(ptr == NULL)
    {
        printf("ERROR return\n");
        return 0;
    }

    pid = getpid();

    for(int i =0 ; i < nloop; i++)
    {
        usleep(nusec);
        snprintf(mesg, MESGSIZE, "pid %ld: message %d", (long) pid, i);

        if(sem_trywait(&ptr->nempty) == -1)
        {
            if(errno == EAGAIN)
            {
                sem_wait(&ptr->noverflowmutex);
                ptr->noverflow++;
                sem_post(&ptr->noverflowmutex);
                continue;
            }
            else
            {
                perror("sem_trywait error");
                exit(0);
            }

        }
        sem_wait(&ptr->mutex);
        offset = ptr->msgoff[ptr->nput];
        if(++(ptr->nput) >= NMESG)
        {
            ptr->nput = 0;
        }
        sem_post(&ptr->mutex);
        strcpy(&ptr->msgdata[offset], mesg);
        sem_post(&ptr->nstored);
    }
    exit(0);

}

