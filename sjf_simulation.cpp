#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

struct Process {
    int id;
    double burstTime;
    double waitingTime;
    double turnaroundTime;
};

bool compareBurstTime(const Process& a, const Process& b) {
    return a.burstTime < b.burstTime;
}

void calculateSJF(std::vector<Process>& processes) {
    int n = processes.size();

    // Sort processes by burst time
    std::sort(processes.begin(), processes.end(), compareBurstTime);

    // Calculate waiting time and turnaround time
    double totalWT = 0, totalTAT = 0;
    processes[0].waitingTime = 0;
    processes[0].turnaroundTime = processes[0].burstTime;

    for (int i = 1; i < n; ++i) {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
        totalWT += processes[i].waitingTime;
        totalTAT += processes[i].turnaroundTime;
    }

    totalTAT += processes[0].turnaroundTime; // Add first process TAT

    // Display results
    std::cout << "Process\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (const auto& process : processes) {
        std::cout << "P" << process.id << "\t\t" << process.burstTime << "\t\t" << process.waitingTime << "\t\t" << process.turnaroundTime << "\n";
    }

    std::cout << "\nAverage Waiting Time: " << std::fixed << std::setprecision(2) << totalWT / n << "\n";
    std::cout << "Average Turnaround Time: " << std::fixed << std::setprecision(2) << totalTAT / n << "\n";
}

int main() {
    std::vector<Process> processes = {
        {1, 50.54, 0, 0},
        {2, 10.11, 0, 0},
        {3, 33.32, 0, 0},
        {4, 2.5, 0, 0},
        {5, 101.1, 0, 0}
    };

    std::cout << "Shortest Job First (SJF) Scheduling Simulation\n";
    calculateSJF(processes);

    return 0;
}