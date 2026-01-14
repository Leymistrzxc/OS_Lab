#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Process {
    int id;
    int arrival;
    int burst;
    int remaining;
    int finish;
    int wait;
    int turnaround;
};

void roundRobinScheduling(vector<Process>& processes, int quantum);
void displayResults(vector<Process>& processes);
void getInput(vector<Process>& processes);

int main() {
    vector<Process> processes;
    int choice, quantum;
    
    cout << "CPU Scheduling - Round Robin Algorithm\n\n";
    
    do {
        cout << "Menu:\n";
        cout << "1. Enter processes\n";
        cout << "2. Run Round Robin Scheduling\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                getInput(processes);
                break;
                
            case 2:
                if(processes.empty()) {
                    cout << "No processes entered. Use option 1 first.\n\n";
                } else {
                    cout << "Enter time quantum: ";
                    cin >> quantum;
                    roundRobinScheduling(processes, quantum);
                }
                break;
                
            case 3:
                cout << "Goodbye!\n";
                break;
                
            default:
                cout << "Invalid choice!\n";
        }
    } while(choice != 3);
    
    return 0;
}

void getInput(vector<Process>& processes) {
    int n, arrival, burst;
    
    processes.clear();
    
    cout << "\nHow many processes? ";
    cin >> n;
    
    for(int i = 0; i < n; i++) {
        cout << "\nProcess " << i + 1 << ":\n";
        cout << "Arrival time: ";
        cin >> arrival;
        cout << "Burst time: ";
        cin >> burst;
        
        processes.push_back({i + 1, arrival, burst, burst, 0, 0, 0});
    }
    
    cout << "\n" << n << " processes entered successfully.\n\n";
}

void roundRobinScheduling(vector<Process>& processes, int quantum) {
    cout << "\nRound Robin Scheduling with Quantum = " << quantum << "\n\n";
    
    
    for(auto& p : processes) {
        p.remaining = p.burst;
        p.finish = 0;
        p.wait = 0;
        p.turnaround = 0;
    }
    
    
    sort(processes.begin(), processes.end(), 
         [](const Process& a, const Process& b) {
             return a.arrival < b.arrival;
         });
    
    queue<int> readyQueue;
    vector<bool> inQueue(processes.size(), false);
    vector<bool> completed(processes.size(), false);
    
    int currentTime = 0;
    int completedCount = 0;
    int n = processes.size();
    int currentProcess = -1;
    
    cout << "Execution Timeline:\n";
    cout << "Time\tProcess\n";
    cout << "----\t-------\n";
    
    
    for(int i = 0; i < n; i++) {
        if(processes[i].arrival == 0) {
            readyQueue.push(i);
            inQueue[i] = true;
        }
    }
    
    while(completedCount < n) {
        
        if(currentProcess == -1 && readyQueue.empty()) {
            int nextArrival = 9999;
            for(int i = 0; i < n; i++) {
                if(!completed[i] && processes[i].arrival > currentTime) {
                    if(processes[i].arrival < nextArrival) {
                        nextArrival = processes[i].arrival;
                    }
                }
            }
            
            if(nextArrival != 9999) {
                cout << currentTime << "-" << nextArrival << "\tIDLE\n";
                currentTime = nextArrival;
                
                
                for(int i = 0; i < n; i++) {
                    if(!completed[i] && !inQueue[i] && processes[i].arrival <= currentTime) {
                        readyQueue.push(i);
                        inQueue[i] = true;
                    }
                }
            }
        }
        
       
        if(currentProcess != -1 && processes[currentProcess].remaining > 0) {
            readyQueue.push(currentProcess);
            inQueue[currentProcess] = true;
        }
        
       
        if(!readyQueue.empty()) {
            currentProcess = readyQueue.front();
            readyQueue.pop();
            inQueue[currentProcess] = false;
            
            int execTime = min(quantum, processes[currentProcess].remaining);
            
            cout << currentTime << "-" << currentTime + execTime 
                 << "\tP" << processes[currentProcess].id << "\n";
            
            currentTime += execTime;
            processes[currentProcess].remaining -= execTime;
            
            
            if(processes[currentProcess].remaining == 0) {
                processes[currentProcess].finish = currentTime;
                processes[currentProcess].turnaround = processes[currentProcess].finish - processes[currentProcess].arrival;
                processes[currentProcess].wait = processes[currentProcess].turnaround - processes[currentProcess].burst;
                
                completed[currentProcess] = true;
                completedCount++;
                currentProcess = -1;
            }
            
            // Add newly arrived processes to queue
            for(int i = 0; i < n; i++) {
                if(!completed[i] && !inQueue[i] && processes[i].arrival <= currentTime) {
                    readyQueue.push(i);
                    inQueue[i] = true;
                }
            }
        } else {
            currentProcess = -1;
        }
    }
    
    displayResults(processes);
}

void displayResults(vector<Process>& processes) {
    float totalWait = 0;
    float totalTurnaround = 0;
    
    cout << "\nResults:\n";
    cout << "Process\tArrival\tBurst\tFinish\tWait\tTurnaround\n";
    cout << "-------\t-------\t-----\t------\t----\t----------\n";
    
    
    sort(processes.begin(), processes.end(), 
         [](const Process& a, const Process& b) {
             return a.id < b.id;
         });
    
    for(const auto& p : processes) {
        cout << "P" << p.id << "\t" << p.arrival << "\t" << p.burst << "\t"
             << p.finish << "\t" << p.wait << "\t" << p.turnaround << "\n";
        
        totalWait += p.wait;
        totalTurnaround += p.turnaround;
    }
    
    cout << "\nAverage Waiting Time: " << totalWait / processes.size() << "\n";
    cout << "Average Turnaround Time: " << totalTurnaround / processes.size() << "\n";
    
    
    int totalTime = 0;
    for(const auto& p : processes) {
        if(p.finish > totalTime) totalTime = p.finish;
    }
    cout << "Throughput: " << processes.size() / (float)totalTime << " processes/unit time\n\n";
}