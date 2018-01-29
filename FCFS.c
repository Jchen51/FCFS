//
//  main.c
//  P2
//
//  Created by Jason Chen on 1/23/18.
//  Copyright © 2018 Jason Chen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>



struct Job{
    int arrival_time;
    int service_time;
    int priority;
    char name;
};

typedef struct node{
    struct Job data;
    struct node* next;
};

struct Job* genjobs(int amount){
    struct Job* jobs = malloc(sizeof(struct Job)*amount);
    //srand(seed);
    for (int i = 0; i < amount; i++){
        int at = rand()%100;
        int st = (rand() % 11);
        if (st == 0) st++;
        int p = rand() % 5;
        if (p == 0) p += 1;
        struct Job temp;
        temp.arrival_time = at;
        temp.service_time = st;
        //printf("%d, ", st);
        temp.priority = p;
        temp.name = i+65;
        jobs[i] = temp;
    }
    return jobs;
}


int compare(const void *s1, const void *s2)
{
    struct Job *e1 = (struct Job *)s1;
    struct Job *e2 = (struct Job *)s2;
    return e1->arrival_time - e2->arrival_time;
}

void sort(struct Job* a, int jobsize){
    qsort(a, jobsize, sizeof(struct Job), compare);
}

void FCFS(){
    float throughput;
    int turnaroundavg = 0;
    int waitingavg = 0;
    int responseavg = 0;
    
    for (int a = 0; a < 5; a++){
    
        int turnaround = 0;
        int waiting = 0;
        int response = 0;
    
        struct node* head;
        
    static int quanta[100];
    struct Job* jobs;
    
    int enough = 0;
    int jobtotal = 10;
    while (enough == 0){
        for (int i = 0; i < 100; i++){
            quanta[i] = 0;
        }
        jobs = genjobs(jobtotal);
        
        //simulate CPU, check for empty quanta
        for (int i = 0; i < jobtotal; i++){
            //printf("%d, ", jobs[i].service_time);
            for (int j = jobs[i].arrival_time; j < jobs[i].arrival_time+jobs[i].service_time; j++){
                
                quanta[j]++;
            }
            //printf("%c\n", jobs[i].name);
        }
        int start = 0;
        int gap = 0;
        for (int k = 0; k < 100; k++){
            if (quanta[k] > 0){
                start = k;
            }
            if ((k >= start)&&(quanta[k] == 0)){
                gap++;
            }
            if (gap == 2){
                break;
            }
            //printf("%d,", quanta[k]);
            
        }
        //for(int i = 0; i < jobtotal; i++){
        //    printf("%d, %d, %c\n", jobs[i].arrival_time, jobs[i].service_time, jobs[i].name);
        //}
        
        if (gap == 2){
            jobtotal += 1;
        }else{

            enough = 1;
        }
    }
    //printf("Jobs: %d\n", jobtotal);
        /*
        int lowest = jobs[0].service_time;
        struct Job* jobqueue = malloc(sizeof(struct Job)*jobtotal);
        int full = 0, i = 1, j = i;
        while(full < 100){
            if (lowest > jobs[i].service_time){
                lowest = jobs[i].service_time;
                j = i;
            }
            if (i == jobtotal-1){
                jobqueue[i] = jobs[j];
            }
        }*/
    
    //printf("final copy\n");
    for(int i = 0; i < jobtotal; i++){
        printf("%d, %d, %c\n", jobs[i].arrival_time, jobs[i].service_time, jobs[i].name);
    }
    sort(jobs, jobtotal);
    //printf("post sort\n");
    //for(int i = 0; i < jobtotal; i++){
    //    printf("%d, %d, %c\n", jobs[i].arrival_time, jobs[i].service_time, jobs[i].name);
    //}
        struct Job* jobqueue = malloc(sizeof(struct Job)*jobtotal);
        
        int totalexec = 0, counter = 0;
        while ((counter != jobtotal)&&(totalexec < 100)){
            //printf("totalexec: %d\n", totalexec);
            jobqueue[counter] = jobs[counter];
            totalexec += jobqueue[counter].service_time;
            //printf("%d, ", jobs[counter].arrival_time);
            counter++;
        }
    int startingspot = jobqueue[0].arrival_time;
    int waitingtime, turnaroundtime, responsetime;
    //printf("jobqueue\n");
    for(int i = 0; i < counter; i++){
        //printf("%d, %d, %c\n", jobqueue[i].arrival_time, jobqueue[i].service_time, jobqueue[i].name);
        printf("%c", jobqueue[i].name);
        waitingtime = startingspot-jobqueue[i].arrival_time;
        turnaroundtime = startingspot+jobqueue[i].service_time-jobqueue[i].arrival_time;
        //differs for round robin?
        responsetime = waitingtime;
        //printf("waiting time: %d, turnaround time %d\n", waitingtime, turnaroundtime);
        waiting += waitingtime;
        turnaround += turnaroundtime;
        startingspot += jobqueue[i].service_time;
    }
    printf("\n");
    
    waiting = waiting/counter;
    turnaround = turnaround/counter;
        response = waiting;
    printf("AVG waiting time: %i\n", waiting);
    printf("AVG turnaround time: %i\n", turnaround);
    printf("AVG response time: %i\n", response);
    
    
        printf("Throughput: %f\n", (float)counter/(float)(startingspot-jobqueue[0].arrival_time));
        throughput += (float)counter/(float)(startingspot-jobqueue[0].arrival_time);
    
        waitingavg += waiting;
        turnaroundavg += turnaround;
        responseavg += response;
    free(jobs);
    
        
        
    //printf("%d", jobtotal);
    }
    waitingavg /= 5;
    turnaroundavg /= 5;
    responseavg /= 5;
    throughput /= 5;
    printf("TRUE AVG waiting time: %i\n", waitingavg);
    printf("TRUE AVG turnaround time: %i\n", turnaroundavg);
    printf("TRUE AVG response time: %i\n", responseavg);
    printf("AVG throughput: %f\n", throughput);
    

}

int main()
{
    float seed = time(NULL);
    srand(seed);
    
    FCFS();
    //SJF
    //SRT
    //RR
    //HPF NonPreemptive
    //HPF Preemptive
    return 0;
}
