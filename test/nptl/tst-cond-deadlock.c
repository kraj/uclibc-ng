/*
 * Copyright (C) 2016 Martin Willi <martin@strongswan.org>
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <pthread.h>

static pthread_mutex_t m;
static pthread_cond_t c;
static pthread_t t;
static volatile int ready;

static void cancelcb(void *arg)
{
    pthread_mutex_unlock(&m);
}

static void* threadcb(void *arg)
{
    pthread_mutex_lock(&m);
    pthread_cleanup_push(cancelcb, NULL);

    ready = 1;
    while (1)
        pthread_cond_wait(&c, &m);
    pthread_cleanup_pop(1);
}

static int
do_test (void)
{
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&c, NULL);

    pthread_create(&t, NULL, threadcb, NULL);

    while (!ready);

    pthread_cancel(t);
    pthread_join(t, NULL);

    pthread_cond_signal(&c);
    pthread_cond_destroy(&c);
    pthread_mutex_destroy(&m);

    return 0;
}

#define TEST_FUNCTION do_test ()
#define TIMEOUT 100
#include "../test-skeleton.c"
