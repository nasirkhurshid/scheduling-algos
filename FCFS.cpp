#include "process.h";

int main()
{
    int np;
    cout << "Enter number of Processes: ";
    cin >> np;
    process* p = new process[np];
    input(p, np);
    sort(p, np, 1);
    double avg_tat = 0, avg_wt = 0;
    time(p, np, avg_tat, avg_wt);
    cout << "\nFor FCFS:-\n";
    table(p, np);
    cout << "\nAverage Turnaround Time: " << avg_tat / np;
    cout << "\nAverage Waiting Time: " << avg_wt / np << endl;
    gantt_chart(p, np, 0);
    cout << endl << endl;
    gantt_chart(p, np, 1);
    cout << endl;

    return 0;
} 
