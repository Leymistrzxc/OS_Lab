#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
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
    int start_time;  // Added to track when process starts
};

void getInput(vector<Process>& processes) {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    
    processes.clear();  // Clear vector before adding new processes
    
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
        p.wait = 0;
        p.turnaround = 0;
        p.finish = 0;
        p.start_time = -1;
        processes.push_back(p);
    }
}

void runPriorityScheduling(vector<Process>& processes) {
    cout << "\n--- Non-Preemptive Priority Scheduling ---\n\n";
    
    int time = 0;
    int completed = 0;
    int n = processes.size();
    
    // Reset all processes
    for(int i = 0; i < n; i++) {
        processes[i].done = false;
        processes[i].wait = 0;
        processes[i].turnaround = 0;
        processes[i].finish = 0;
        processes[i].start_time = -1;
    }
    
    cout << "Gantt Chart:\n";
    cout << "Time\tProcess\n";
    cout << "----\t-------\n";
    
    // Find minimum arrival time to start from
    int min_arrival = 9999;
    for(int i = 0; i < n; i++) {
        if(processes[i].arrival < min_arrival) {
            min_arrival = processes[i].arrival;
        }
    }
    time = min_arrival;
    
    while(completed < n) {
        int selected = -1;
        int highPriority = 9999;
        int earliestArrival = 9999;
        
        // Find the process with highest priority (lowest number)
        // If priority is same, choose the one with earliest arrival
        // If arrival is same, choose the one with smaller process ID
        for(int i = 0; i < n; i++) {
            if(!processes[i].done && processes[i].arrival <= time) {
                if(processes[i].priority < highPriority) {
                    highPriority = processes[i].priority;
                    earliestArrival = processes[i].arrival;
                    selected = i;
                }
                else if(processes[i].priority == highPriority && processes[i].arrival < earliestArrival) {
                    earliestArrival = processes[i].arrival;
                    selected = i;
                }
                else if(processes[i].priority == highPriority && processes[i].arrival == earliestArrival) {
                    // Tie-breaker: choose process with smaller ID
                    if(selected != -1 && processes[i].id < processes[selected].id) {
                        selected = i;
                    }
                }
            }
        }
        
        if(selected != -1) {
            // Process found, execute it
            processes[selected].start_time = time;
            cout << time << "-" << time + processes[selected].burst 
                 << "\t" << processes[selected].id << "\n";
            
            time += processes[selected].burst;
            processes[selected].finish = time;
            processes[selected].turnaround = processes[selected].finish - processes[selected].arrival;
            processes[selected].wait = processes[selected].turnaround - processes[selected].burst;
            processes[selected].done = true;
            completed++;
        } else {
            // No process available, jump to next arrival time
            int next_arrival = 9999;
            for(int i = 0; i < n; i++) {
                if(!processes[i].done && processes[i].arrival > time && processes[i].arrival < next_arrival) {
                    next_arrival = processes[i].arrival;
                }
            }
            
            if(next_arrival == 9999) {
                break;  // No more processes
            }
            
            // Jump to next arrival time
            time = next_arrival;
        }
    }
    
    cout << "\nResults:\n";
    cout << left << setw(8) << "Process" 
         << setw(8) << "Arrival" 
         << setw(8) << "Burst" 
         << setw(10) << "Priority" 
         << setw(8) << "Finish" 
         << setw(8) << "Wait" 
         << setw(12) << "Turnaround" << "\n";
    
    cout << string(62, '-') << "\n";
    
    float totalWait = 0;
    float totalTurnaround = 0;
    
    // Sort by process ID for display
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.id < b.id;
    });
    
    for(int i = 0; i < n; i++) {
        cout << left << setw(8) << processes[i].id 
             << setw(8) << processes[i].arrival 
             << setw(8) << processes[i].burst 
             << setw(10) << processes[i].priority 
             << setw(8) << processes[i].finish 
             << setw(8) << processes[i].wait 
             << setw(12) << processes[i].turnaround << "\n";
        
        totalWait += processes[i].wait;
        totalTurnaround += processes[i].turnaround;
    }
    
    cout << fixed << setprecision(2);
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
        cout << "\n";
    } while(choice != 3);
    
    return 0;
}