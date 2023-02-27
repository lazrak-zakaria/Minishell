#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

int main() {
    int status;
    pid_t pid;

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // child process
        // do some work...
        exit(127); // simulate a termination by Ctrl+C
    } else { // parent process
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) { // child exited normally
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) { // child exited due to a signal
            printf("Child terminated by signal %d\n", WTERMSIG(status));
        }
    }
    return 0;
}