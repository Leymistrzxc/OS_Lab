//Implement SJF. 5 process, BT: 50.54,10.11,33.34,2.5,101.1 
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    int n{5};
    double wtavg{0.0}, tatavg{0.0};

    vector<int> p(n);
    vector<double> bt{50.54, 10.11, 33.34, 2.5, 101.1};
    vector<double> wt(n), tat(n);

    for (int i = 0; i < n; i++) {
        p[i] = i;
    }

    for (int i = 0; i < n; i++) {
        for (int k = i + 1; k < n; k++) {
            if (bt[i] > bt[k]) {
                swap(bt[i], bt[k]);
                swap(p[i], p[k]);
            }
        }
    }

    wt[0] = 0;
    tat[0] = bt[0];
    wtavg = 0.0;
    tatavg = bt[0];

    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
        tat[i] = tat[i - 1] + bt[i];
        wtavg += wt[i];
        tatavg += tat[i];
    }

    // Output 
    cout << "\n\t PROCESS \tBURST TIME \t WAITING TIME\t TURNAROUND TIME\n";
    for (int i = 0; i < n; i++) {
        cout << "\n\t P" << p[i] << "\t\t " << bt[i] << "\t\t " << wt[i] << "\t\t " << tat[i];
    }

    cout << "\nAverage Waiting Time -- " << fixed << setprecision(2) << wtavg / n;
    cout << "\nAverage Turnaround Time -- " << tatavg / n << "\n";

    return 0;
}