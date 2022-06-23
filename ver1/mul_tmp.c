#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int target = 0;

void * addTarget(void * param)
{
    int limit = *(int *) param;
    int i=0;
    for (i=1; i<=limit; i++) {
        printf("[ADD] target : %d\n", ++target);
    }
}

void * subtractTarget(void * param)
{
    int limit = *(int *) param;
    int i=0;
    for (i=1; i<=limit; i++) {
        printf("[SUBTRACT] target : %d\n", --target);
    }
}

int main()
{
    pthread_t add, sub;
    int param = 100;

    int add_id = pthread_create(&add, NULL, addTarget, &param);
    // error handling, 정상적으로 생성되면 0 반환
    if (add_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    }

    int sub_id = pthread_create(&sub, NULL, subtractTarget, &param);
    if (sub_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    }

    sleep(3000);
    printf("target : %d\n", target);

    return 0;
}