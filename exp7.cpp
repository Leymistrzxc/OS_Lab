#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>

using namespace std;

enum class ID { SYSTEM, INTERACTIVE, BATCH };
enum class S { ACTIVE, RUNNING, BLOCKED, TERMINATED };

struct C {
    int ID;
    int AT;
    int BT;
    int RT;
    int WT;
    int TAT;
    int PR;
    S state;
    ID type;
    int queue;
    int response;
};

vector<C> RQ;
vector<C> BQ;

CC(0, 0, 0, 0, 0, 0, 0, ID::SYSTEM, S::ACTIVE, 0, 0),
CC(1, 0, 0, 0, 0, 0, 0, ID::INTERACTIVE, S::ACTIVE, 0, 0),
CC(2, 0, 0, 0, 0, 0, 0, ID::BATCH, S::ACTIVE, 0, 0);

class M {
    private:
        vector<vector<int>> available;
        vector<vector<int>> allocated;
        vector<vector<int>> max;

    public:
        M(vector<vector<int>> initialResource) {
            available = initialResource;
            allocated = vector<vector<int>>(initialResource.size(), vector<int>(initialResource[0].size(), 0));
            max = vector<vector<int>>(initialResource.size(), vector<int>(initialResource[0].size(), 0));
        }

        bool PROG1(shared_ptr<C> request) {
            for (size_t i = 0; i < request.size(); ++i) {
                if (request[i] > available[i]) {
                    return false;
                }
            }

            for (size_t i = 0; i < request.size(); ++i) {
                available[i] -= request[i];
                allocated[request->ID][i] += request[i];
            }

            for (size_t i = 0; i < request.size(); ++i) {
                if (request[i] > max[request->ID][i]) {
                    for (size_t j = 0; j < request.size(); ++j) {
                        available[j] += request[j];
                        allocated[request->ID][j] -= request[j];
                    }
                    return false;
                }
            }

            bool canAllocate = true;
            for (size_t i = 0; i < request.size(); ++i) {
                if (available[i] < max[request->ID][i] - allocated[request->ID][i]) {
                    canAllocate = false;
                }
            }

            if (canAllocate) {
                for (size_t i = 0; i < request.size(); ++i) {
                    available[i] += allocated[request->ID][i];
                    allocated[request->ID][i] = 0;
                }
                return true;
            }

            return false;
        }
};

void SJF(const vector<C>& RQ) {
    vector<C> sortedRQ = RQ;
    sort(sortedRQ.begin(), sortedRQ.end(), [](const C& a, const C& b) {
        return a.BT < b.BT;
    });

    for (const auto& process : sortedRQ) {
        cout << "Process ID: " << process.ID << "\n";
        cout << "Burst Time: " << process.BT << "\n";
    }
}

class T {
    private:
        vector<vector<int>> queues;
        vector<int> timeQuantum;
        int currentQueue;

    public:
        T(int numQueues, const vector<int>& quanta, const vector<int>& aging) {
            timeQuantum = quanta;
            queues = vector<vector<int>>(numQueues);
            currentQueue = 0;
        }

        void OC(shared_ptr<C> p) {
            queues[p->queue].push_back(p->ID);
        }

        void VC() {
            for (size_t i = 0; i < queues.size(); ++i) {
                for (size_t j = 0; j < queues[i].size(); ++j) {
                    if (queues[i][j] == -1) {
                        queues[i].erase(queues[i].begin() + j);
                        --j;
                    }
                }
            }

            for (size_t i = 0; i < queues.size(); ++i) {
                for (size_t j = 0; j < queues[i].size(); ++j) {
                    if (queues[i][j] != -1) {
                        cout << "Queue " << i << ": " << queues[i][j] << "\n";
                    }
                }
            }
        }
};

int main() {
    vector<int> timeQuantum = { 5, 10, 15 };
    vector<int> aging = { 1, 2, 3 };

    T scheduler(3, timeQuantum, aging);

    vector<vector<int>> initialResource = {
        {10, 5, 7},
        {3, 2, 2},
        {9, 0, 2}
    };

    M resourceManager(initialResource);

    vector<shared_ptr<C>> processes = {
        make_shared<C>(C{0, 0, 5, 5, 0, 0, 0, ID::SYSTEM, S::ACTIVE, 0, 0}),
        make_shared<C>(C{1, 1, 3, 3, 0, 0, 0, ID::INTERACTIVE, S::ACTIVE, 0, 0}),
        make_shared<C>(C{2, 2, 8, 8, 0, 0, 0, ID::BATCH, S::ACTIVE, 0, 0})
    };

    for (auto& p : processes) {
        scheduler.OC(p);
    }

    scheduler.VC();

    int current = 0;
    int time = 0;

    while (true) {
        if (current >= processes.size()) {
            current = 0;
        }

        if (processes[current]->state == S::TERMINATED) {
            ++current;
            continue;
        }

        if (processes[current]->state == S::ACTIVE) {
            cout << "Running process: " << current << "\n";
            processes[current]->state = S::RUNNING;
            --processes[current]->RT;
            ++time;
        }

        if (processes[current]->RT == 0) {
            processes[current]->state = S::TERMINATED;
            cout << "Process " << current << " completed.\n";
        }

        ++current;

        if (all_of(processes.begin(), processes.end(), [](const shared_ptr<C>& p) {
            return p->state == S::TERMINATED;
        })) {
            break;
        }
    }

    cout << "\nSimulation finished.\n";
    return 0;
}
