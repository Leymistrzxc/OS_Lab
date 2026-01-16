#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

void printLine(int width) {
    std::cout << "+" << std::string(width, '-') << "+\n";
}

void calculateFCFS(const std::vector<int>& burstTimes) {
    int n = burstTimes.size();
    std::vector<int> waitingTime(n, 0);
    std::vector<int> turnaroundTime(n, 0);

    
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
    std::cout << "| Process | Burst Time | Waiting Time | Turnaround Time |\n";
    printLine(width);
    for (int i = 0; i < n; ++i) {
        std::cout << "| P" << std::setw(6) << i + 1 << " | "
                  << std::setw(10) << burstTimes[i] << " | "
                  << std::setw(12) << waitingTime[i] << " | "
                  << std::setw(15) << turnaroundTime[i] << " |\n";
    }
    printLine(width);

    std::cout << "\nAverage Waiting Time: " << std::fixed << std::setprecision(2) << avgWT << "\n";
    std::cout << "Average Turnaround Time: " << std::fixed << std::setprecision(2) << avgTAT << "\n";
}

int main() {
    std::vector<int> burstTimes = {3, 5, 4, 3, 2, 1, 0, 7, 8, 1};

    std::cout << "First-Come-First-Serve (FCFS) Scheduling Simulation\n";
    calculateFCFS(burstTimes);

    return 0;
}