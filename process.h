#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct process{
	int id, arrival_time, burst_time, turnaround_time, remaining_time, waiting_time, terminal_time, start_time;
};

void input(process* p, const int& np) {
    for (int i = 0; i < np; i++) {
        cout << "Enter ID for Process P" << i + 1 << ": ";
        cin >> p[i].id;
        cout << "Enter arrival time for Process P" << i + 1 << ": ";
        cin >> p[i].arrival_time;
        cout << "Enter burst time for Process P" << i + 1 << ": ";
        cin >> p[i].burst_time;
        cout << endl;
    }
}

void sort(process* processes, const int& np, int arrival) {
    int min;
    if (arrival == 1) {
        for (int i = 0; i < np - 1; i++) {
            min = i;
            for (int j = i + 1; j < np; j++) {
                if (processes[j].arrival_time < processes[min].arrival_time) {
                    min = j;
                }
            }
            if (min != i) {
                process temp = processes[min];
                processes[min] = processes[i];
                processes[i] = temp;
            }
        }
    }
    else if (arrival == 0) {
        for (int i = 0; i < np - 1; i++) {
            min = i;
            for (int j = i + 1; j < np; j++) {
                if (processes[j].burst_time < processes[min].burst_time) {
                    min = j;
                }
            }
            if (min != i) {
                process temp = processes[min];
                processes[min] = processes[i];
                processes[i] = temp;
            }
        }
    }
}


void table(process* p, int np) {
    cout << "Table of data: \n";
    cout << "-----------------------------------------------------------------------------------------------\n";
    cout << "Process\t\t| ID\t| Arrival Time\t| Burst Time\t| Turnaround Time\t| Waiting Time|\n";
    for (int i = 0; i < np; i++) {
        cout << "P" << p[i].id << "\t\t| " << p[i].id << "\t| " << setw(12) << left << p[i].arrival_time << "\t| "
            << setw(10) << left << p[i].burst_time << "\t| " << setw(15) << left << p[i].turnaround_time
            << "\t| " << setw(12) << left << p[i].waiting_time << "|" << endl;
    }
    cout << "-----------------------------------------------------------------------------------------------\n";
}

void time(process* p, int np, double& avg_tat, double& avg_wt) {
    for (int i = 0; i < np; i++) {
        if (i == 0) {
            p[i].terminal_time = p[i].burst_time;
        }
        else {
            p[i].terminal_time = p[i - 1].terminal_time + p[i].burst_time;
        }
        p[i].turnaround_time = p[i].terminal_time - p[i].arrival_time;
        avg_tat += p[i].turnaround_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        avg_wt += p[i].waiting_time;
    }
}

void gantt_chart(process* p, int np, int chart) {
    cout << "\nGantt Chart:\n";
    if (chart == 1) {
        for (int i = 0; i < np; i++) {
            for (int j = 0; j < p[i].burst_time; j++) {
                cout << "--";
            }
            cout << "-";
        }
        cout << "\n|";
        for (int i = 0; i < np; i++) {
            for (int j = 0; j < p[i].burst_time - 1; j++) {
                cout << " ";
            }
            cout << "P" << p[i].id;
            for (int j = 0; j < p[i].burst_time - 1; j++) {
                cout << " ";
            }
            cout << "|";
        }
        cout << endl;
        for (int i = 0; i < np; i++) {
            for (int j = 0; j < p[i].burst_time; j++) {
                cout << "--";
            }
            cout << "-";
        }
        cout << "\n" << p[0].arrival_time;
        for (int i = 0; i < np; i++) {
            for (int j = 0; j < p[i].burst_time; j++) {
                cout << "  ";
            }
            if (p[i].terminal_time > 9) {
                cout << "\b";
            }
            cout << p[i].terminal_time;
        }
        cout << " ";
    }
    else {
        for (int i = 0; i < np; i++) {
            string str = "P";
            str = str + to_string(p[i].id);
            cout << setw(p[i].burst_time + 2) << str;
        }
        cout << endl;
        cout << p[0].arrival_time << "-";
        for (int i = 0; i < np; i++) {
            cout << setw(p[i].burst_time + 2) << setfill('-') << right << p[i].terminal_time;
        }
    }
}
