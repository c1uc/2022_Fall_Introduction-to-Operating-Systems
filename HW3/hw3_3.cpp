#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
using namespace std;

struct process {
    int id;
    int arrival;
    int burst;
    int tt = 0;
    int wt = 0;
    int deadline = -1;
} q[20];

class arriving {
    public:
        bool operator() (const process& lhs, const process& rhs) {
            return lhs.arrival < rhs.arrival;
        }
} arrivingSort;

int main() {
    int N, timeQ;
    cin >> N;
    for (int i = 0;i < N;i++) {
        q[i].id = i;
        cin >> q[i].arrival;
    }
    for (int i = 0;i < N;i++) {
        cin >> q[i].burst;
    }
    cin >> timeQ;
    vector<process> arriveQueue(q, q + N);
    deque<process> RRQueue;
    deque<process> FCFSQueue;
    sort(arriveQueue.begin(), arriveQueue.end(), arrivingSort);
    int cur_time = arriveQueue.front().arrival;
    int elapse_time;
    int wt = 0;
    int tt = 0;
    while (!arriveQueue.empty() || !RRQueue.empty() || !FCFSQueue.empty()) {
        if (RRQueue.empty() && FCFSQueue.empty()) {
            cur_time = arriveQueue.front().arrival;
        }
        while (!arriveQueue.empty() && arriveQueue.front().arrival <= cur_time) {
            RRQueue.emplace_back(arriveQueue.front());
            arriveQueue.erase(arriveQueue.begin());
        }
        if (!RRQueue.empty()) {
            auto tmp = RRQueue.front();
            RRQueue.pop_front();

            if (tmp.deadline < cur_time) {
                tmp.deadline = cur_time + min(timeQ, tmp.burst);
            }

            elapse_time = tmp.deadline - cur_time;
            if (!arriveQueue.empty()) {
                elapse_time = min(arriveQueue.front().arrival - cur_time, tmp.deadline - cur_time);
            }

            tmp.burst -= elapse_time;
            for (auto it: RRQueue) {
                q[it.id].wt += elapse_time;
            }
            for (auto it: FCFSQueue) {
                q[it.id].wt += elapse_time;
            }

            // cout << cur_time << " Process " << tmp.id << " run for " << elapse_time << "s" << endl;
            cur_time += elapse_time;
            if (tmp.deadline > cur_time) {
                RRQueue.push_front(tmp);
            } else if (tmp.burst != 0) {
                FCFSQueue.push_back(tmp);
            } else {
                q[tmp.id].tt = cur_time - tmp.arrival;
            }
        } else {
            auto tmp = FCFSQueue.front();
            FCFSQueue.pop_front();

            if (!arriveQueue.empty()) {
                elapse_time = min(tmp.burst, arriveQueue.front().arrival - cur_time);
            } else {
                elapse_time = tmp.burst;
            }

            tmp.burst -= elapse_time;
            for (auto it: FCFSQueue) {
                q[it.id].wt += elapse_time;
            }

            // cout << cur_time << " Process " << tmp.id << " run for " << elapse_time << "s" << endl;
            cur_time += elapse_time;
            if (tmp.burst != 0) {
                FCFSQueue.push_back(tmp);
            } else {
                q[tmp.id].tt = cur_time - tmp.arrival;
            }
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