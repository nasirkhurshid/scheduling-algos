#include "process.h";

int main()
{
    int np;
    cout << "Enter number of Processes: ";
    cin >> np;
    process* processes = new process[np];
    input(processes, np);
    sort(processes, np, 1);
    for (int i = 0; i < np - 1; i++) {
        int min = i;
        for (int j = i; j < np; j++) {
            if (processes[i].arrival_time == processes[j].arrival_time) {
                if (processes[min].burst_time > processes[j].burst_time) {
                    min = j;
                }
                if (min != i) {
                    process temp = processes[min];
                    processes[min] = processes[i];
                    processes[i] = temp;
                }
            }
        }
    }
    processes[0].terminal_time = processes[0].burst_time + processes[0].arrival_time;
    for (int i = 1; i < np - 1; i++) {
        int min = i, check = 0;
        for (int j = i + 1; j < np; j++) {
            if (processes[i].arrival_time <= processes[i - 1].terminal_time
                && processes[j].arrival_time <= processes[i - 1].terminal_time) {
                if (processes[min].burst_time > processes[j].burst_time) {
                    min = j;
                    check = 1;
                }
            }
        }
        if (check) {
            if (min != i) {
                process temp = processes[min];
                processes[min] = processes[i];
                processes[i] = temp;
            }
        }
        if (processes[i].arrival_time > processes[i - 1].terminal_time) {
            processes[i].terminal_time = (processes[i].arrival_time - processes[i - 1].terminal_time) + processes[i].burst_time + processes[i - 1].terminal_time;
        }
        else {
            processes[i].terminal_time = processes[i - 1].terminal_time + processes[i].burst_time;
        }
    }
    if (np != 1) {
        processes[np - 1].terminal_time = processes[np - 2].terminal_time + processes[np].burst_time;
    }

    double avg_tat = 0, avg_wt = 0;
    time(processes, np, avg_tat, avg_wt);
    cout << "\nFor SJF:-\n";
    table(processes, np);
    cout << "\nAverage Turnaround Time: " << avg_tat / np;
    cout << "\nAverage Waiting Time: " << avg_wt / np << endl;
    gantt_chart(processes, np, 1);
    cout << endl << endl;
    gantt_chart(processes, np, 0);
    cout << endl;

    return 0;
}
