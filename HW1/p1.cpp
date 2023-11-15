#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;

int main() {
    pid_t pid;
    pid = fork(); //fork0
    printf("fork0\n");
    printf("ppid: %d, pid: %d, fork(): %d\n", getppid(), getpid(), pid);
    if(pid == 0) {
        pid = fork(); //fork1
        printf("fork1\n");
        printf("ppid: %d, pid: %d, fork(): %d\n", getppid(), getpid(), pid);
        if(pid > 0) {
            wait(NULL);
        }
        else if(pid == 0) {
            pid = fork(); //fork2
            printf("fork2\n");
            printf("ppid: %d, pid: %d, fork(): %d\n", getppid(), getpid(), pid);
            if(pid > 0) {
                wait(NULL);
            }
        }
    }
    else if(pid > 0) {
        wait(NULL);
        pid = fork(); //fork3
        printf("fork3\n");
        printf("ppid: %d, pid: %d, fork(): %d\n", getppid(), getpid(), pid);
        if(pid > 0) {
            wait(NULL);
        }
    }
    else {
        printf("Error!");
    }
    pid = fork(); //fork4
    printf("fork4\n");
    printf("ppid: %d, pid: %d, fork(): %d\n", getppid(), getpid(), pid);
    if(pid > 0) {
        wait(NULL);
    }
    return 0;
}