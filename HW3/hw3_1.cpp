#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct process {
    int id;
    int arrival;
    int burst;
    int tt = 0;
    int wt = 0;
};

class arriving {
    public:
        bool operator() (const process& lhs, const process& rhs) {
            return lhs.arrival < rhs.arrival;
        }
} arrivingSort;

class waiting {
    public:
        bool operator() (const process& lhs, const process& rhs) {
            return lhs.burst < rhs.burst;
        }
} waitingSort;

int main() {
    int N;
    cin >> N;
    process q[20];
    for (int i = 0;i < N;i++) {
        q[i].id = i;
        cin >> q[i].arrival;
    }
    for (int i = 0;i < N;i++) {
        cin >> q[i].burst;
    }
    vector<process> arriveQueue(q, q + N);
    vector<process> waitingQueue;
    sort(arriveQueue.begin(), arriveQueue.end(), arrivingSort);
    int cur_time = arriveQueue.front().arrival;
    int elapse_time;
    int wt = 0;
    int tt = 0;
    while (!arriveQueue.empty() || !waitingQueue.empty()) {
        if (waitingQueue.empty()) {
            cur_time = arriveQueue.front().arrival;
        }
        while (!arriveQueue.empty() && arriveQueue.front().arrival <= cur_time) {
            waitingQueue.emplace_back(arriveQueue.front());
            sort(waitingQueue.begin(), waitingQueue.end(), waitingSort);
            arriveQueue.erase(arriveQueue.begin());
        }
        if (arriveQueue.empty()) {
            elapse_time = waitingQueue.front().burst;
        } else {
            elapse_time = min(waitingQueue.front().burst, arriveQueue.front().arrival - cur_time);
        }
        auto tmp = waitingQueue.front();
        waitingQueue.erase(waitingQueue.begin());
        
        tmp.burst -= elapse_time;
        for (auto it: waitingQueue) {
            q[it.id].wt += elapse_time;
        }

        // cout << cur_time << " Process " << tmp.id << " run for " << elapse_time << "s" << endl;
        cur_time += elapse_time;
        if (tmp.burst != 0) {
            waitingQueue.emplace_back(tmp);
            sort(waitingQueue.begin(), waitingQueue.end(), waitingSort);
        } else {
            q[tmp.id].tt = cur_time - tmp.arrival;
        }
    }
    for (int i = 0;i < N;i++) {
        wt += q[i].wt;
        tt += q[i].tt;
        cout << q[i].wt << " " << q[i].tt << endl;
    }
    cout << wt << endl << tt << endl;
    return 0;
}