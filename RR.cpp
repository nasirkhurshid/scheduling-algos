#include "process.h";
#include <queue>

int main() 
{
    int np, tq;
    cout << "Enter the number of processes: ";
    cin >> np;
    cout << "Enter time quantum: ";
    cin >> tq;
    process *p=new process[np];
    queue <int> q;
    queue <process> q1,q11; 
    int* completed = new int[np], * mark = new int[np];

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
        mark[i] = 0;
    }

    int total_turnaround_time = 0, total_waiting_time = 0;
    sort(p, np, 1);
    q.push(0);
    int idx;
    int current_time = 0;
    int no_comp = 0;
    mark[0] = 1;

    while (no_comp != np) {
        idx = q.front();
        q.pop();
        q1.push(p[idx]);
        if (p[idx].remaining_time == p[idx].burst_time) {
            p[idx].start_time = max(current_time, p[idx].arrival_time);
            current_time = p[idx].start_time;
        }
        if (p[idx].remaining_time - tq > 0) {
            p[idx].remaining_time -= tq;
            current_time += tq;
        }
        else {
            current_time += p[idx].remaining_time;
            p[idx].remaining_time = 0;
            no_comp++;
            if (no_comp == 3) {
                cout << endl;
            }
            p[idx].terminal_time = current_time;
            p[idx].turnaround_time = p[idx].terminal_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
            q11.push(p[idx]);
        }

        for (int i = 1; i < np; i++) {
            if (p[i].remaining_time > 0 && p[i].arrival_time <= current_time && mark[i] == 0) {
                q.push(i);
                mark[i] = 1;
            }
        }
        if (p[idx].remaining_time > 0) {
            q.push(idx);
        }

        if (q.empty()) {
            for (int i = 1; i < np; i++) {
                if (p[i].remaining_time > 0) {
                    q.push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }
    }

    float avg_turnaround_time = (float)total_turnaround_time / np;
    float avg_waiting_time = (float)total_waiting_time / np;
    cout << endl;
    table(p, np);
    cout << endl;
    cout << "Average Turnaround Time = " << avg_turnaround_time << endl;
    cout << "Average Waiting Time = " << avg_waiting_time << endl;
    cout << endl;
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
    process p2;
    while (!q2.empty()) {
        process p = q2.front();
        p2 = q11.front();
        q2.pop();
        if (prev != p.id) {
            if (p2.terminal_time < i) {
                cout << p2.terminal_time << "-";
                q11.pop();
            }
            else if (i > 9) {
                cout <<i;
            }
            else{
                cout << i << "-";
            }
            prev = p.id;
        }
        else {
            cout << "--";
        }
        i += tq;
    }
    cout << p2.terminal_time << endl;
    return 0;
}