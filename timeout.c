#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sysexits.h>
#include <signal.h>
#include <getopt.h>
#include <err.h>

static const char usage[] = "usage: timeout [-q] <seconds> <command>\n";
static volatile sig_atomic_t alarmed;

static void
onalrm(int sig)
{
	alarmed = 1;
	alarm(0);
}

static int
stosecs(char *s)
{
	int num;
	char *end;

	num = (int)strtol(s, &end, 10);
	if (!*end || !strcmp(end, "s"))
		return num;
	else if (!strcmp(end, "m"))
		return num * 60;
	else if (!strcmp(end, "h"))
		return num * 3600;
	else
		return -1;
}

int
main(int argc, char **argv)
{
	int opt, secs, quiet=0, signo=SIGHUP, ret;
	static pid_t child;

	while ((opt = getopt(argc, argv, "qs:")) != -1) {
		switch (opt) {
		case 'q':
			quiet = 1;
			break;
		case 's':
			if (!(signo = atoi(optarg)))
				errx(EX_USAGE, "bad signal: %d", signo);
			break;
		default:
			fputs(usage, stderr);
			exit(EX_USAGE);
		}
	}
	argc -= optind;
	argv += optind;

	if (argc < 2) {
		fputs(usage, stderr);
		exit(EX_USAGE);
	}
	if ((secs = stosecs(argv[0])) <= 0)
		errx(EX_USAGE, "bad timeout: %s", argv[0]);

	switch ((child = fork())) {
	case -1:
		err(1, "fork");
	case 0:
		execvp(argv[1], &argv[1]);
		err(126, "exec(%s)", argv[1]);
	}

	signal(SIGALRM, onalrm);
	siginterrupt(SIGALRM, 1);
	alarm((unsigned)secs);

	if (wait(&ret) != -1)
		return ret;
	else if (errno == EINTR && alarmed) {
		if (!quiet)
			warnx("%s exceeded %s", argv[1]);
		kill(child, SIGHUP);
	} else
		err(1, "wait(%s)", argv[1]);
}
