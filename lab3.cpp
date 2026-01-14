#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    char id;
    int arrival;
    int burst;
    int priority;
    int finish;
    int wait;
    int turnaround;
    bool done;
};

void getInput(vector<Process>& processes) {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    
    for(int i = 0; i < n; i++) {
        Process p;
        p.id = 'A' + i;
        cout << "\nProcess " << p.id << ":\n";
        cout << "Arrival time: ";
        cin >> p.arrival;
        cout << "Burst time: ";
        cin >> p.burst;
        cout << "Priority (lower = higher priority): ";
        cin >> p.priority;
        p.done = false;
        processes.push_back(p);
    }
}

void runPriorityScheduling(vector<Process>& processes) {
    cout << "\n--- Non-Preemptive Priority Scheduling ---\n\n";
    
    int time = 0;
    int completed = 0;
    int n = processes.size();
    
    cout << "Gantt Chart:\n";
    cout << "Time\tProcess\n";
    cout << "----\t-------\n";
    
    while(completed < n) {
        int selected = -1;
        int highPriority = 9999;
        
        for(int i = 0; i < n; i++) {
            if(!processes[i].done && processes[i].arrival <= time) {
                if(processes[i].priority < highPriority) {
                    highPriority = processes[i].priority;
                    selected = i;
                }
            }
        }
        
        if(selected != -1) {
            cout << time << "-" << time + processes[selected].burst 
                 << "\t" << processes[selected].id << "\n";
            
            time += processes[selected].burst;
            processes[selected].finish = time;
            processes[selected].turnaround = processes[selected].finish - processes[selected].arrival;
            processes[selected].wait = processes[selected].turnaround - processes[selected].burst;
            processes[selected].done = true;
            completed++;
        } else {
            time++;
        }
    }
    
    cout << "\nResults:\n";
    cout << "Process\tArrival\tBurst\tPriority\tFinish\tWait\tTurnaround\n";
    cout << "-------\t-------\t-----\t--------\t------\t----\t----------\n";
    
    float totalWait = 0;
    float totalTurnaround = 0;
    
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.id < b.id;
    });
    
    for(int i = 0; i < n; i++) {
        cout << processes[i].id << "\t"
             << processes[i].arrival << "\t"
             << processes[i].burst << "\t"
             << processes[i].priority << "\t\t"
             << processes[i].finish << "\t"
             << processes[i].wait << "\t"
             << processes[i].turnaround << "\n";
        
        totalWait += processes[i].wait;
        totalTurnaround += processes[i].turnaround;
    }
    
    cout << "\nAverage Waiting Time: " << totalWait / n;
    cout << "\nAverage Turnaround Time: " << totalTurnaround / n << "\n\n";
}

int main() {
    vector<Process> processes;
    int choice;
    
    cout << "CPU Scheduling - Non-Preemptive Priority\n\n";
    
    do {
        cout << "Menu:\n";
        cout << "1. Enter processes\n";
        cout << "2. Run scheduling\n";
        cout << "3. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                processes.clear();
                getInput(processes);
                break;
            case 2:
                if(processes.empty()) {
                    cout << "Enter processes first.\n";
                } else {
                    runPriorityScheduling(processes);
                }
                break;
            case 3:
                cout << "Goodbye\n";
                break;
            default:
                cout << "Invalid choice\n";
        }
    } while(choice != 3);
    
    return 0;
}