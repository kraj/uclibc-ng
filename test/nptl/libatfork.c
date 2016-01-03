#include <stdio.h>
#include <pthread.h>

static void atfork_prepare(void)
{
    /*  nothing to do  */
}

static void atfork_parent(void)
{
    /*  nothing to do  */
}

static void atfork_child(void)
{
    /*  nothing to do  */
}

static __attribute__((constructor)) void init(void)
{
    pthread_atfork(atfork_prepare, atfork_parent, atfork_child);
}

static __attribute__((destructor)) void done(void)
{
    /*  nothing to do  */
}
