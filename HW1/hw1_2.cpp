#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;

int main() {
    cout << "Main Process ID : " << getpid() << endl;
    pid_t pid;
    pid = fork(); //fork 1
    if(pid == 0) { //fork 1 child
        cout << "Fork 1. I'm the child " << getpid() << ", my parent is " << getppid() << "." << endl;
        pid = fork(); // fork 2
        if(pid == 0) { // fork 2 child
            cout << "Fork 2. I'm the child " << getpid() << ", my parent is " << getppid() << "." << endl;
            pid = fork(); //fork 3
            if(pid == 0) { // fork 3 child
                cout << "Fork 3. I'm the child " << getpid() << ", my parent is " << getppid() << "." << endl;
            } else { // fork 3 parent
                wait(NULL);
            }
        } else { // fork 2 parent
            wait(NULL);
        }
    } else { // fork 1 parent
        wait(NULL);
        pid = fork(); //fork 4
        if(pid == 0) { // fork 4 child
            cout << "Fork 4. I'm the child " << getpid() << ", my parent is " << getppid() << "." << endl;
        } else { // fork 4 parent
            wait(NULL);
            pid = fork(); //fork 6
            if(pid == 0) { // fork 6 child
                cout << "Fork 6. I'm the child " << getpid() << ", my parent is " << getppid() << "." << endl;
            } else { // fork 6 parent
                wait(NULL);
            }
        }
        pid = fork(); //fork 5
        if(pid == 0) { // fork 5 child
            cout << "Fork 5. I'm the child " << getpid() << ", my parent is " << getppid() << "." << endl;
        } else { // fork 5 parent
            wait(NULL);
        }
    }
    return 0;
}