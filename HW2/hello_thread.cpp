#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;

int a[] = {1, 2, 3};

// child threading function
void* child_thread(void* data){
    sleep(1);
    cout << "Child Pthread ID - " << pthread_self() << endl;
    int *str = (int*) data; // get data "Child"
    for(int i = 0 ; i < 3 ; i++){
        sleep(1);
        cout << a[*str] << endl;// output every second
    }
    pthread_exit(NULL); // exit child thread 
}

// main fuction
int main(void){
    pthread_t t;    // define thread 
    int n = 1;
    pthread_create(&t,NULL,child_thread,&n);   // create a child thread
    sleep(1);
    cout << "Master Pthread ID - " << pthread_self() << endl;   // output master thread's ID
    // pthread_join(t,NULL);   // wait for child threading finished, then output "Master"
    for(int i = 0 ; i < 3 ; i++){
        sleep(1);
        cout << "Master" << endl;

    }
    // pthread_join(t,NULL);// output "Master" during child thread outputing "Child"
    return 0;
}
