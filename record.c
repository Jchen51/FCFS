#include <stdlib.h>
#include <stdio.h>
#include "process.c"
#include "record.h"

#define MAX_TABLE_SIZE 20

Record newRecord()
{
    return *((Record*) malloc(sizeof(Record)));
}

void addProcess(Record* r, Process p)
{
    (*r).processCount = (*r).processCount + 1;
    Process* newArray = (Process*) malloc(sizeof(Process) * (*r).processCount);
    int i;
    for(i = 0; i < (*r).processCount - 1; i++)
    {
        newArray[i] = (*r).process[i];
    }
    newArray[(*r).processCount - 1] = p;
    (*r).process = newArray;
}

void addTimeslice(Record* r, Timeslice t)
{
    (*r).timesliceCount = (*r).timesliceCount + 1;
    Timeslice* newArray = (Timeslice*) malloc(sizeof(Timeslice) * (*r).timesliceCount);
    int i;
    for(i = 0; i < (*r).timesliceCount - 1; i++)
    {
        newArray[i] = (*r).timeslice[i];
    }
    newArray[(*r).timesliceCount - 1] = t;
    (*r).timeslice = newArray;
}

void printRecord(Record r)
{
    printf(" PID | Arrival | Priority | Duration | Response | Wait | Turnaround | Fin @ \n");
    printf("-----+---------+----------+----------+----------+------+------------+-------\n");
    int i;
    float totalResponse = 0.0f;
    float totalWait = 0.0f;
    float totalTurnaround = 0.0f;
    for(i = 0; i < r.processCount; i++)
    {
        printf(" %3c | %7.1f | %8d | %8.1f | %8.1f | %4.1f | %10.1f | %d \n", r.process[i].id, r.process[i].arrival, r.process[i].priority, r.process[i].runtime, r.process[i].responseTime, r.process[i].waitTime, r.process[i].turnaroundTime, r.process[i].timeFinished);
        totalResponse += r.process[i].responseTime;
        totalWait += r.process[i].waitTime;
        totalTurnaround += r.process[i].turnaroundTime;
    }
    int base;
    for(base = 0; base < r.timesliceCount; base = base + MAX_TABLE_SIZE)
    {
        printf("-----------+");
        for(i = 0; base + i < r.timesliceCount && i < MAX_TABLE_SIZE; i++)
        {
            printf("-----+");
        }
        printf("\n");
        printf(" Timeslice |");
        for(i = 0; base + i < r.timesliceCount && i < MAX_TABLE_SIZE; i++)
        {
            printf(" %3d |", r.timeslice[base + i].index);
        }
        printf("\n");
        printf("   Process |");
        for(i = 0; base + i < r.timesliceCount && i < MAX_TABLE_SIZE; i++)
        {
            printf(" %3c |", r.timeslice[base + i].pid);
        }
        printf("\n");
        printf("-----------+");
        for(i = 0; base + i < r.timesliceCount && i < MAX_TABLE_SIZE; i++)
        {
            printf("-----+");
        }
        printf("\n");
    }
    printf(" ~~~ Averages ~~~\n");
    printf("  Response: %.1f\n", totalResponse / r.processCount);
    printf("      Wait: %.1f\n", totalWait / r.processCount);
    printf("Turnaround: %.1f\n", totalTurnaround / r.processCount);
    printf("~~~ Throughput ~~~\n");
    printf(" Processes: %d\n", r.processCount);
    printf("      Time: %d\n", r.timesliceCount);
    printf("Throughput: %.1f processes per 100 quanta\n", 100 * ((float) r.processCount) / r.timesliceCount);
}

