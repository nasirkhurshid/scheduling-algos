#include "process.h";
#include <queue>

int main() {
    int np;
    cout << "Enter the number of processes: ";
    cin >> np;
    process *p=new process[np];
    queue < process> q1;
    int* completed = new int[np];

    for (int i = 0; i < np; i++) {
        cout << "Enter ID for process P" << i + 1 << ": ";
        cin >> p[i].id;
        cout << "Enter arrival time of process P" << i + 1 << ": ";
        cin >> p[i].arrival_time;
        cout << "Enter burst time of process P" << i + 1 << ": ";
        cin >> p[i].burst_time;
        p[i].remaining_time = p[i].burst_time;
        cout << endl;
        completed[i] = 0;
    }

    int current_time = 0, no_comp = 0, total_turnaround_time = 0, total_waiting_time = 0;
    while (no_comp != np) {
        int idx = -1, min = 1000;
        for (int i = 0; i < np; i++) {
            if (p[i].arrival_time <= current_time && completed[i] == 0) {
                if (p[i].remaining_time < min) {
                    min = p[i].remaining_time;
                    idx = i;
                }
                if (p[i].remaining_time == min) {
                    if (p[i].arrival_time < p[idx].arrival_time) {
                        min = p[i].remaining_time;
                        idx = i;
                    }
                }
            }
        }
        if (idx != -1) {
            p[idx].remaining_time -= 1;
            current_time++;
            q1.push(p[idx]);
            if (p[idx].remaining_time == 0) {
                p[idx].terminal_time = current_time;
                p[idx].turnaround_time = p[idx].terminal_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;
                completed[idx] = 1;
                no_comp++;
            }
        }
        else {
            current_time++;
        }
    }

    float avg_turnaround_time = (float)total_turnaround_time / np;
    float avg_waiting_time = (float)total_waiting_time / np;
    cout << endl << endl;
    table(p, np);
    cout << "Average turnaround time = " << avg_turnaround_time << endl;
    cout << "Average waiting time = " << avg_waiting_time << endl;

    int prev = -1;
    queue<process> q2 = q1;
    cout << "\nGantt Chart:\n";
    while (!q1.empty()) {
        process p = q1.front();
        q1.pop();
        if (prev != p.id) {
            prev = p.id;
            cout << p.id << " ";
        }
        else {
            cout << "  ";
        }
    }
    cout << endl;
    int i = 0;
    while (!q2.empty()) {
        process p = q2.front();
        q2.pop();
        if (prev != p.id) {
            if (i > 9) {
                cout << i;
            }
            else{
                cout << i << "-";
            }
            prev = p.id;
        }
        else {
            cout << "--";
        }
        i++;
    }
    cout << i << endl;
    
    return 0;
}
