#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define READ_END 0
#define WRITE_END 1
#define FIRSTPROG 0
#define INTPROG 1
#define LASTPROG 2

int main(int argc, char *argv[])
{
    if (argc <= 1) { // too little arguments
        exit(EINVAL);
    }
    
    int prevFD[2];
    int progNum = FIRSTPROG;

    if (argc == 2) { // there is only one program to run
        // int fd[2];
        // pipe(fd);
        // pid_t pid = fork();
        if (execlp(argv[1], argv[1], NULL) == -1){
            printf("Error %d: Command execution failed\n", errno);
            exit(errno);
		}
        exit(0);
    }

    // more than a singular program
    for (int i = 1; i < argc; i++) {
        int fd[2];
        if (i == 1) {
            progNum = FIRSTPROG;
            pipe(fd);
        }
        else if (i == argc-1) {
            progNum = LASTPROG;
        }
        else {
            progNum = INTPROG;
            pipe(fd);
        }

        pid_t p = fork();
        if (p < 0) exit(ECHILD); // child creation failed
        else if (p == 0) { // inside child process
            if (progNum == FIRSTPROG) {
                dup2(fd[WRITE_END], STDOUT_FILENO);
                close(fd[WRITE_END]);
                close(fd[READ_END]);
            }
            else if (progNum == INTPROG) {
                dup2(prevFD[READ_END], STDIN_FILENO);
                close(prevFD[READ_END]);
                dup2(fd[WRITE_END], STDOUT_FILENO);
                close(fd[WRITE_END]);
                close(fd[READ_END]);
            }
            else if (progNum = LASTPROG) {
                dup2(fd[READ_END], STDIN_FILENO);
                close(fd[READ_END]);
            }
            if (execlp(argv[i], argv[i], NULL) == -1){
                exit(errno);
            }
            exit(0);
        }
        else { // inside parent process
            if (progNum == FIRSTPROG) {
                close(fd[WRITE_END]);
            }
            else if (progNum == INTPROG) {
                close(prevFD[READ_END]);
                close(fd[WRITE_END]);
            }
            else if (progNum = LASTPROG) {
                close(fd[READ_END]);
            }

            int status = 0;
            if (waitpid(p, &status, 0) < 0) {
                exit(errno);
            }
            if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
                exit(WEXITSTATUS(status));
            }
        }
        prevFD[READ_END] = fd[READ_END];
        prevFD[WRITE_END] = fd[WRITE_END];
    }
    return 0;
}
