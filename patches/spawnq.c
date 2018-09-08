#include <sys/stat.h>
#include <fcntl.h>

void
spawnq(const Arg *arg) {
	if(fork() == 0) {
		int devnullno = open("/dev/null", O_WRONLY);
		dup2(devnullno, STDOUT_FILENO); /* doesn't matter if it's null (?) */
		dup2(devnullno, STDERR_FILENO);
		if(dpy)
			close(ConnectionNumber(dpy));
		setsid();
		execvp(((char **)arg->v)[0], (char **)arg->v);
		fprintf(stderr, "dwm: execvp %s: %s", ((char **)arg->v)[0], strerror(errno));
		exit(0);
	}
}
