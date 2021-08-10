#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct id{
    int flag;
};
int turn=0;
int number;
pthread_mutex_t mutexinc;

void *increment(void *args)
{
    struct id *info = (struct id*) args;
    int flag = info->flag;
    while(number < 100){
        if(turn == flag){
        pthread_mutex_lock(&mutexinc);
        number = number+1;
        turn=(flag + 1) % 2;
        printf("%d\t thread_id=%lu\n", number, pthread_self());
        pthread_mutex_unlock(&mutexinc);
        }
    }

    pthread_exit(NULL);
    
}

int main(){
    FILE *fp;
    fp = fopen("number.txt", "r");
    if(fp==NULL){
        fp = fopen("number.txt","w");
        fprintf(fp,"%d",20);
        number = 20;
    }else{
        fscanf(fp,"%d", &number);
    }
    
    //printf("Reading from file = %d\n",number);
    pthread_mutex_init(&mutexinc, NULL);
    pthread_t thread1;
    pthread_t thread2;

    struct id *firstID = (struct id*) malloc(sizeof(struct id));
    struct id *secondID = (struct id*) malloc(sizeof(struct id));

    firstID->flag=0;
    secondID->flag=1;



    pthread_create(&thread1, NULL, increment, firstID);
    pthread_create(&thread2, NULL, increment, secondID);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    fclose(fp);
    pthread_mutex_destroy(&mutexinc);
    pthread_exit(NULL);
}