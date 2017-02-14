#include <semaphore.h>
const int MESGSIZE = 256;
const int NMESG = 16;

struct shmstruct
{
    sem_t mutex;
    sem_t nempty;
    sem_t nstored;
    int nput;
    long noverflow;
    sem_t noverflowmutex;
    long msgoff[NMESG];
    char msgdata[NMESG * MESGSIZE];
};

