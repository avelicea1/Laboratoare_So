#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NR_THREADS 7
#define AMOUNT_WITHDRAW 7
#define AMOUNT_DEPOSIT 11

typedef struct
{
    int id;
    pthread_mutex_t *lock;
    pthread_cond_t *cond;
    pthread_cond_t *cond_turn;
} TH_STRUCT;

int balance = 0;
int turn = 0;
void *thread_withdraw(void *args)
{
    TH_STRUCT *s = (TH_STRUCT *)args;
    usleep(10000 * s->id);

    pthread_mutex_lock(s->lock);
    
    while(turn != s->id){
        pthread_cond_wait(s->cond_turn, s->lock);
    }
    printf("%d a inceput \n",s->id);
    turn = (turn +1)%NR_THREADS;
    pthread_cond_broadcast(s->cond_turn);
    while (balance < AMOUNT_WITHDRAW)
    {
        printf("[TH%d] Not enough money (%d). Will wait..\n", s->id, balance);
        pthread_cond_wait(s->cond, s->lock);
    }
    balance -= AMOUNT_WITHDRAW;
    printf("[TH%d] Withdraw %d. Current balance is %d. \n", s->id, AMOUNT_WITHDRAW, balance);
    pthread_mutex_unlock(s->lock);
    return NULL;
}

void *thread_deposit(void *args)
{
    TH_STRUCT *s = (TH_STRUCT *)args;
    usleep(10000 * s->id);

    pthread_mutex_lock(s->lock);
    balance += AMOUNT_DEPOSIT;
    printf("[Th%d] Deposited %d. Current balance is %d.\n", s->id, AMOUNT_DEPOSIT, balance);
    while (turn != s->id)
    {
        pthread_cond_wait(s->cond_turn, s->lock);
    }
    printf("%d a inceput \n",s->id);
    turn = (turn +1)%NR_THREADS;
    pthread_cond_broadcast(s->cond_turn);
    if (balance >= 2 * AMOUNT_WITHDRAW)
    {
        pthread_cond_broadcast(s->cond);
    }
    else if (balance >= AMOUNT_WITHDRAW)
    {
        pthread_cond_signal(s->cond);
    }
    pthread_mutex_unlock(s->lock);
    return NULL;
}

int main()
{
    int i;
    TH_STRUCT params[NR_THREADS];
    pthread_t tids[NR_THREADS];
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    pthread_cond_t cond_turn = PTHREAD_COND_INITIALIZER;

    for (i = 0; i < NR_THREADS; i++)
    {
        params[i].id = i;
        params[i].lock = &lock;
        params[i].cond = &cond;
        params[i].cond_turn = &cond_turn;
        if (i == 0 || i == 2 || i == 3 || i == 4)
        {
            pthread_create(&tids[i], NULL, thread_withdraw, &params[i]);
        }
        else
        {
            pthread_create(&tids[i], NULL, thread_deposit, &params[i]);
        }
    }
    for (i = 0; i < NR_THREADS; i++)
    {
        pthread_join(tids[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    pthread_cond_destroy(&cond_turn);
    return 0;
}