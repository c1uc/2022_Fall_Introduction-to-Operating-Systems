#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
using namespace std;

int main() {
    bool exit = false, wait_ = true;
    stringstream ss;
    string s, input;
    vector<string> arg;
    int argc;
    char **argv;
    pid_t pid;
    while(!exit) {
        fflush(stdout);
        cout << "osh>";
        getline(cin, input);

        ss << input;
        while(getline(ss, s, ' ')) {
            if(s == "&") {
                wait_ = false;
            } else if(s == "exit") {
                return 0;
            } else {
                arg.push_back(s);
            }
        }
        argc = arg.size();
        if(argc == 0) {
            ss.clear();
            arg.clear();
            continue;
        }
        argv = new char*[argc + 1];
        for(int i = 0;i < argc;i++) {
            argv[i] = new char[arg[i].size()];
            strcpy(argv[i], arg[i].c_str());
        }
        argv[argc] = new char;
        argv[argc] = NULL;

        pid = fork();
        if(pid == 0) {
            execvp(argv[0], argv);
            return 0;
        } else {
            if(wait_) {
                waitpid(pid, NULL, 0);
            }
        }

        ss.clear();
        arg.clear();
        wait_ = true;
        for(int i = 0;i < argc;i++) {
            delete [] argv[i];
        }
        delete argv;
    }
    return 0;
}