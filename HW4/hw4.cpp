#include <iostream>
#include <queue>
#include <set>
using namespace std;

int N, K;
int X[105];

int FIFO() {
    set<int> s;
    queue<int> q;
    int sum = 0;
    for(int i = 0;i < N;i++) {
        if(s.count(X[i])) {
            continue;
        } else {
            if(q.size() == K) {
                s.erase(q.front());
                q.pop();
            }
            s.insert(X[i]);
            q.push(X[i]);
            sum++;
        }
    }
    return sum;
}

int main() {
    cin >> K >> N;
    for(int i = 0;i < N;i++) cin >> X[i];
    cout << FIFO() << endl;
    return 0;
}