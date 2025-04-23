#include <stdio.h>
#include <limits.h>

void fcfs_scheduling() {
    int n, i, j;
    int arrival_time[100], burst_time[100], waiting_time[100], turnaround_time[100];
    float avg_waiting = 0, avg_turnaround = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter arrival time and burst time for each process:\n");
    for(i = 0; i < n; i++) {
        printf("Process %d: ", i+1);
        scanf("%d %d", &arrival_time[i], &burst_time[i]);
    }

    // Sort processes by arrival time
    for(i = 0; i < n-1; i++) {
        for(j = i+1; j < n; j++) {
            if(arrival_time[i] > arrival_time[j]) {
                // Swap arrival times
                int temp = arrival_time[i];
                arrival_time[i] = arrival_time[j];
                arrival_time[j] = temp;
                
                // Swap burst times
                temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;
            }
        }
    }

    // Calculate waiting and turnaround times
    waiting_time[0] = 0;
    turnaround_time[0] = burst_time[0];
    
    for(i = 1; i < n; i++) {
        waiting_time[i] = turnaround_time[i-1] - arrival_time[i] + arrival_time[i-1];
        if(waiting_time[i] < 0) waiting_time[i] = 0;
        turnaround_time[i] = waiting_time[i] + burst_time[i];
    }

    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", i+1, arrival_time[i], burst_time[i], 
               waiting_time[i], turnaround_time[i]);
        avg_waiting += waiting_time[i];
        avg_turnaround += turnaround_time[i];
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting/n);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround/n);
}

void sjf_scheduling() {
    int n, i, time = 0, shortest;
    int arrival_time[100], burst_time[100], waiting_time[100], turnaround_time[100];
    int completed[100] = {0}, remaining_time[100];
    float avg_waiting = 0, avg_turnaround = 0;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter arrival time and burst time for each process:\n");
    for(i = 0; i < n; i++) {
        printf("Process %d: ", i+1);
        scanf("%d %d", &arrival_time[i], &burst_time[i]);
        remaining_time[i] = burst_time[i];
    }

    int completed_processes = 0;
    while(completed_processes < n) {
        shortest = -1;
        int min_burst = INT_MAX;
        for(i = 0; i < n; i++) {
            if(!completed[i] && arrival_time[i] <= time && burst_time[i] < min_burst) {
                min_burst = burst_time[i];
                shortest = i;
            }
        }
        
        if(shortest == -1) {
            time++;
            continue;
        }
        
        waiting_time[shortest] = time - arrival_time[shortest];
        time += burst_time[shortest];
        turnaround_time[shortest] = time - arrival_time[shortest];
        completed[shortest] = 1;
        completed_processes++;
    }

    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", i+1, arrival_time[i], burst_time[i], 
               waiting_time[i], turnaround_time[i]);
        avg_waiting += waiting_time[i];
        avg_turnaround += turnaround_time[i];
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting/n);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround/n);
}

void priority_scheduling() {
    int n, i, time = 0;
    int arrival_time[100], burst_time[100], priority[100];
    int waiting_time[100], turnaround_time[100], completed[100] = {0};
    float avg_waiting = 0, avg_turnaround = 0;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter arrival time, burst time and priority for each process (lower number = higher priority):\n");
    for(i = 0; i < n; i++) {
        printf("Process %d: ", i+1);
        scanf("%d %d %d", &arrival_time[i], &burst_time[i], &priority[i]);
    }

    int completed_processes = 0;
    while(completed_processes < n) {
        int highest_priority = INT_MAX, selected = -1;
        
        for(i = 0; i < n; i++) {
            if(!completed[i] && arrival_time[i] <= time && priority[i] < highest_priority) {
                highest_priority = priority[i];
                selected = i;
            }
        }
        
        if(selected == -1) {
            time++;
            continue;
        }
        
        waiting_time[selected] = time - arrival_time[selected];
        time += burst_time[selected];
        turnaround_time[selected] = time - arrival_time[selected];
        completed[selected] = 1;
        completed_processes++;
    }

    printf("\nProcess\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", i+1, arrival_time[i], burst_time[i], 
               priority[i], waiting_time[i], turnaround_time[i]);
        avg_waiting += waiting_time[i];
        avg_turnaround += turnaround_time[i];
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting/n);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround/n);
}

void round_robin() {
    int n, i, time = 0, tq, completed_processes = 0;
    int arrival_time[100], burst_time[100], remaining_time[100];
    int waiting_time[100] = {0}, turnaround_time[100] = {0};
    float avg_waiting = 0, avg_turnaround = 0;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter arrival time and burst time for each process:\n");
    for(i = 0; i < n; i++) {
        printf("Process %d: ", i+1);
        scanf("%d %d", &arrival_time[i], &burst_time[i]);
        remaining_time[i] = burst_time[i];
    }
    printf("Enter time quantum: ");
    scanf("%d", &tq);

    while(completed_processes < n) {
        for(i = 0; i < n; i++) {
            if(arrival_time[i] <= time && remaining_time[i] > 0) {
                if(remaining_time[i] > tq) {
                    time += tq;
                    remaining_time[i] -= tq;
                } else {
                    time += remaining_time[i];
                    waiting_time[i] = time - arrival_time[i] - burst_time[i];
                    turnaround_time[i] = time - arrival_time[i];
                    remaining_time[i] = 0;
                    completed_processes++;
                }
            }
        }
    }

    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", i+1, arrival_time[i], burst_time[i], 
               waiting_time[i], turnaround_time[i]);
        avg_waiting += waiting_time[i];
        avg_turnaround += turnaround_time[i];
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting/n);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround/n);
}

void preemptive_sjf_scheduling() {
    int n, i, time = 0, shortest;
    int arrival_time[100], burst_time[100], remaining_time[100];
    int waiting_time[100] = {0}, turnaround_time[100] = {0}, completed[100] = {0};
    float avg_waiting = 0, avg_turnaround = 0;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter arrival time and burst time for each process:\n");
    for(i = 0; i < n; i++) {
        printf("Process %d: ", i+1);
        scanf("%d %d", &arrival_time[i], &burst_time[i]);
        remaining_time[i] = burst_time[i];
    }

    int completed_processes = 0;
    while(completed_processes < n) {
        shortest = -1;
        int min_remaining = INT_MAX;
        
        for(i = 0; i < n; i++) {
            if(!completed[i] && arrival_time[i] <= time && remaining_time[i] < min_remaining) {
                min_remaining = remaining_time[i];
                shortest = i;
            }
        }
        
        if(shortest == -1) {
            time++;
            continue;
        }
        
        remaining_time[shortest]--;
        time++;
        
        if(remaining_time[shortest] == 0) {
            turnaround_time[shortest] = time - arrival_time[shortest];
            waiting_time[shortest] = turnaround_time[shortest] - burst_time[shortest];
            completed[shortest] = 1;
            completed_processes++;
        }
    }

    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", i+1, arrival_time[i], burst_time[i], 
               waiting_time[i], turnaround_time[i]);
        avg_waiting += waiting_time[i];
        avg_turnaround += turnaround_time[i];
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting/n);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround/n);
}

void preemptive_priority_scheduling() {
    int n, i, time = 0;
    int arrival_time[100], burst_time[100], priority[100], remaining_time[100];
    int waiting_time[100] = {0}, turnaround_time[100] = {0}, completed[100] = {0};
    float avg_waiting = 0, avg_turnaround = 0;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter arrival time, burst time and priority for each process (lower number = higher priority):\n");
    for(i = 0; i < n; i++) {
        printf("Process %d: ", i+1);
        scanf("%d %d %d", &arrival_time[i], &burst_time[i], &priority[i]);
        remaining_time[i] = burst_time[i];
    }

    int completed_processes = 0;
    while(completed_processes < n) {
        int highest_priority = INT_MAX, selected = -1;
        
        for(i = 0; i < n; i++) {
            if(!completed[i] && arrival_time[i] <= time && priority[i] < highest_priority && remaining_time[i] > 0) {
                highest_priority = priority[i];
                selected = i;
            }
        }
        
        if(selected == -1) {
            time++;
            continue;
        }
        
        remaining_time[selected]--;
        time++;
        
        if(remaining_time[selected] == 0) {
            turnaround_time[selected] = time - arrival_time[selected];
            waiting_time[selected] = turnaround_time[selected] - burst_time[selected];
            completed[selected] = 1;
            completed_processes++;
        }
    }

    printf("\nProcess\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", i+1, arrival_time[i], burst_time[i], 
               priority[i], waiting_time[i], turnaround_time[i]);
        avg_waiting += waiting_time[i];
        avg_turnaround += turnaround_time[i];
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting/n);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround/n);
}

void FIFO() {
    int frames, pages[100], frame[10], n, i, j, k = 0, flag, fault = 0;
    printf("Enter number of frames: ");
    scanf("%d", &frames);
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter the reference string:\n");
    for(i = 0; i < n; i++) scanf("%d", &pages[i]);

    for(i = 0; i < frames; i++) frame[i] = -1;
    printf("\nPage\tFrames\n");

    for(i = 0; i < n; i++) {
        flag = 0;
        for(j = 0; j < frames; j++) {
            if(frame[j] == pages[i]) {
                flag = 1;
                break;
            }
        }
        if(flag == 0) {
            frame[k] = pages[i];
            k = (k + 1) % frames;
            fault++;
        }
        printf("%d\t", pages[i]);
        for(j = 0; j < frames; j++)
            printf("%d ", frame[j]);
        printf("\n");
    }
    printf("\nTotal page faults = %d\n", fault);
}

void LRU() {
    int frames, pages[100], frame[10], time[10];
    int n, i, j, pos, fault = 0, count = 0, flag1, flag2;
    printf("Enter number of frames: ");
    scanf("%d", &frames);
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter the reference string:\n");
    for(i = 0; i < n; i++) scanf("%d", &pages[i]);

    for(i = 0; i < frames; i++) {
        frame[i] = -1;
        time[i] = 0;
    }

    printf("\nPage\tFrames\n");
    for(i = 0; i < n; i++) {
        flag1 = flag2 = 0;
        for(j = 0; j < frames; j++) {
            if(frame[j] == pages[i]) {
                count++;
                time[j] = count;
                flag1 = flag2 = 1;
                break;
            }
        }
        if(!flag1) {
            for(j = 0; j < frames; j++) {
                if(frame[j] == -1) {
                    count++;
                    frame[j] = pages[i];
                    time[j] = count;
                    fault++;
                    flag2 = 1;
                    break;
                }
            }
        }
        if(!flag2) {
            pos = 0;
            for(j = 1; j < frames; j++) {
                if(time[j] < time[pos]) {
                    pos = j;
                }
            }
            count++;
            frame[pos] = pages[i]
            time[pos] = count;
            fault++;
        }
        printf("%d\t", pages[i]);
        for(j = 0; j < frames; j++)
            printf("%d ", frame[j]);
        printf("\n");
    }
    printf("\nTotal page faults = %d\n", fault);
}

int main() {
    int choice;
    while(1) {
        printf("\nMenu-driven program for scheduling algorithms\n");
        printf("1. NON-preemptive FCFS Scheduling\n");
        printf("2. NON-preemptive SJF Scheduling\n");
        printf("3. NON-preemptive Priority Scheduling\n");
        printf("4. Preemptive SJF Scheduling\n");
        printf("5. Round Robin Scheduling\n");
        printf("6. Preemptive Priority Scheduling\n");
        printf("7. FIFO (Page Replacement)\n");
        printf("8. LRU (Page Replacement)\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: fcfs_scheduling(); break;
            case 2: sjf_scheduling(); break;
            case 3: priority_scheduling(); break;
            case 4: preemptive_sjf_scheduling(); break;
            case 5: round_robin(); break;
            case 6: preemptive_priority_scheduling(); break;
            case 7: FIFO(); break;
            case 8: LRU(); break;
            case 9: return 0;
            default: printf("Invalid choice\n");
        }
    }
}