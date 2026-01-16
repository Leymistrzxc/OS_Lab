//RR- 5 Proceses,  BT: 50.54,10.11,33.34,2.5,101.1, TQ: 20
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    int n{5};
    double wtavg{0}, tatavg{0};

    vector<int> p(n);
    vector<double> bt{50.54, 10.11, 33.34, 2.5, 101.1};
    vector<int> TQ{20};
    vector<int> wt(n), tat(n);

    for (int i = 0; i < n; i++) {
        p[i] = i;
    }

    vector<double> remaining(bt.begin(), bt.end()); // Copy burst times
    int quantum = TQ[0];
    int time = 0; // Current time
    int done = 0; // Number of processes completed
    while(done < n)
    {
        for(int i=0; i<n; i++)
        {
            if(remaining[i] > 0)
            {
                if(remaining[i] > quantum)
                {
                    time += quantum;
                    remaining[i] -= quantum;
                }
                else
                {
                    time += static_cast<int>(remaining[i]);
                    wt[i] = time - static_cast<int>(bt[i]); // Waiting time = Completion time - Burst time
                    remaining[i] = 0;
                    done++;
                }
            }
        }
    }
    
    // Calculate Turnaround Time and averages
    for(int i=0; i<n; i++)
    {
        tat[i] = bt[i] + wt[i];
        wtavg += wt[i];
        tatavg += tat[i];
    }

    // Output 
    cout << "\n\t PROCESS \tBURST TIME \t WAITING TIME\t TURNAROUND TIME\n";
    for (int i = 0; i < n; i++) {
        cout << "\n\t P" << p[i] << "\t\t " << bt[i] << "\t\t " << wt[i] << "\t\t" << tat[i] << "\n";
    }
    cout << "\nQuantum Time -- " << TQ[0]<< "";
    cout << "\nAverage Waiting Time -- " <<fixed << setprecision(2) << wtavg / n;
    cout << "\nAverage Turnaround Time -- " << tatavg / n << "\n";

    return 0;
}