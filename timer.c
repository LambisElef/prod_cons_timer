/*
 *	File	: timer.c
 *
 *	Author	: Eleftheriadis Charalampos
 *
 *	Date	: 23 July 2020
 */

#include "timer.h"

void startFcn(Timer *timer, int period, int tasksToExecute, int startDelay, void *(*timerFcn)(void *arg),
              void *(*errorFcn)(), Queue *queue, void *(*producer)(void *arg), int *tJobIn, int *tDrift,
              pthread_mutex_t *tMut) {
    timer->period = period;
    timer->tasksToExecute = tasksToExecute;
    timer->startDelay = startDelay;
    timer->timerFcn = timerFcn;
    timer->errorFcn = errorFcn;

    timer->queue = queue;
    timer->producer = producer;
    timer->tJobIn = tJobIn;
    timer->tDrift = tDrift;
    timer->tMut = tMut;
}

void stopFcn(Timer *timer) {
    printf("Timer with period %d stopped.\n", timer->period);
}

void start(Timer *timer) {
    pthread_t pro;
    pthread_create(&pro, NULL, timer->producer, timer);
    pthread_detach(pro);
}

