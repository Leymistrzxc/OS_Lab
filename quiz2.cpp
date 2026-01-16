#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;
void printLine(int width) {
    cout << "+" << string(width, '-') << "+\n";
}

void calculateFCFS(const vector<int>& burstTimes) {
    int n = burstTimes.size();
    vector<int> waitingTime(n, 0);
    vector<int> turnaroundTime(n, 0);

    
    for (int i = 1; i < n; ++i) {
        waitingTime[i] = waitingTime[i - 1] + burstTimes[i - 1];
    }

    
    for (int i = 0; i < n; ++i) {
        turnaroundTime[i] = waitingTime[i] + burstTimes[i];
    }

   
    double totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; ++i) {
        totalWT += waitingTime[i];
        totalTAT += turnaroundTime[i];
    }

    double avgWT = totalWT / n;
    double avgTAT = totalTAT / n;

    
    int width = 50;
    printLine(width);
    cout << "| Process | Burst Time | Waiting Time | Turnaround Time |\n";
    printLine(width);
    for (int i = 0; i < n; ++i) {
        cout << "| P" << setw(6) << i + 1 << " | "
                  << setw(10) << burstTimes[i] << " | "
                  << setw(12) << waitingTime[i] << " | "
                  << setw(15) << turnaroundTime[i] << " |\n";
    }
    printLine(width);

    cout << "\nAverage Waiting Time: " << fixed << setprecision(2) << avgWT << "\n";
    cout << "Average Turnaround Time: " << fixed << setprecision(2) << avgTAT << "\n";
}

int main() {
    vector<int> burstTimes = {3, 5, 4, 3, 2, 1, 0, 7, 8, 1};

    cout << "First-Come-First-Serve (FCFS) Scheduling Simulation\n";
    calculateFCFS(burstTimes);

    return 0;
}