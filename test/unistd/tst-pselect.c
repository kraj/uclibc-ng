#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/select.h>

// our SIGALRM handler
void handler(int signum) {
	(void)signum;
	puts("got signal\n");
}

static int
do_test (void)
{
	int rc;
	sigset_t wait_mask, mask_sigchld;
	struct sigaction act;

	// block SIGALRM. We want to handle it only when we're ready
	sigemptyset(&mask_sigchld);
	sigaddset(&mask_sigchld, SIGALRM);
	sigprocmask(SIG_BLOCK,  &mask_sigchld, &wait_mask);
	sigdelset(&wait_mask, SIGALRM);

	// register a signal handler so we can see when the signal arrives
	memset(&act, 0, sizeof(act));
	sigemptyset(&act.sa_mask); // just in case an empty set isn't all 0's (total paranoia)
	act.sa_handler = handler;
	sigaction(SIGALRM, &act, NULL);

	// send ourselves a SIGARLM. It will pend until we unblock that signal in pselect()
	printf("sending ourselves a signal\n");
	kill(getpid(), SIGALRM);

	printf("signal is pending; calling pselect()\n");
	rc = pselect(0, NULL, NULL, NULL, NULL, &wait_mask);
	if (rc != -1 || errno != EINTR) {
		int e = errno;
		printf("pselect() returned %d, errno %d (%s)\n", rc, e, strerror(e));
		exit(1);
	}

	return 0;
}

#define TEST_FUNCTION do_test ()
#include <test-skeleton.c>
