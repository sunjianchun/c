#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    pid_t pid;

    pid = fork();

    if(pid < 0) {
        fprintf(stderr, "Fork Failed");
        exit(-1);
    } else if (pid == 0) {
        execlp("/bin/service httpd status", "service httpd status", NULL);
    } else {
        wait(NULL);
        fprintf(stdout, "Child process complete and the child pid is %d\n", pid);
        exit(0);
    }
    return 0;
}
