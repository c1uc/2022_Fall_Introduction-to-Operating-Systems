#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;

#define MAX 500
#define _ ios_base::sync_with_stdio(0); cin.tie(0);

int N = 10;
int k[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

int matA[MAX][MAX];
int matB[MAX][MAX];

long long mulsum[20] = {0};
long long addsum[20] = {0};
long long add = 0, mul = 0;


void* child_thread(void* data){
    int n = *((int *) data);
    int i = n;
    while(i < MAX) {
        for(int j = 0;j < MAX;j++) {
            addsum[n] += matA[i][j] + matB[i][j];
            for(int k = 0;k < MAX;k++) {
                mulsum[n] += matA[i][k] * matB[k][j];
            }
        }
        i += N;
    }
    pthread_exit(NULL);
}


int main(int argc, char *argv[]){_
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin >> matA[i][j];
        }
    }
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin >> matB[i][j];
        }
    }
    pthread_t t[N];
    for(int i = 0;i < N;i++) {
        pthread_create(&t[i],NULL,child_thread,(void *)(k + i));
    }
    for(int i = 0;i < N;i++) {
        pthread_join(t[i],NULL);
    }
    for(int i = 0;i < N;i++) {
        add += addsum[i];
        mul += mulsum[i];
    }
    cout << add << '\n' << mul << '\n';
    return 0;
}
