#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

struct process_attributes 
{
	int arrival_time;
	int service_time;
	int priority;
};

/*
int jobs_input(int jobs)
{
	printf("How many random processes you want to generate?\n");
	scanf("%d", &jobs);
	//returning the user input of processes number
	return jobs;
}
*/
void SRT (int jobs)
{
	int j = 0;
	int z = 0;
	int check = 0;
	int remaining_time [jobs];
	int process_in_queue = 0;
	int quantum_time = 0;
	int minimum  = INT_MAX;
	int process_executed = 0;
	int waiting_time[jobs];
	int finish_time[jobs];
	int turnaround_time[jobs];
	int complete = 0;
	int w = 0;
	int f = 0;
	int ww = 0;


	int seed = 0;
//	int jobs = 0;
	int i =0;
//	jobs = jobs_input(jobs);
	struct process_attributes process[jobs];
	seed = time(NULL);			//seed is assigned once, and then rand generate different numbers
	srand(seed);				//so seed is outside the for loop to gurantee different values
	
	for (i = 0; i < jobs; i++)
	{
		process[i].arrival_time = rand() % 100;	//%100 to generate random arrival_time for each process < 100 (value = 1,2, ... ,99)
		process[i].service_time = rand() % 11;		//%11  to generate random service_time for each process < 11  (value = 1,2, ... ,10)
		process[i].priority = rand() % 5;		//%5   to generate random priority for each process < 5       (value = 1,2,3,4)

		if (process[i].service_time == 0) process[i].service_time += 1;	//to avoid zero service time for a process
		if (process[i].priority == 0) process[i].priority += 1;		//to avoid zero priority for a process
	}



	for (z = 0; z < jobs; z++)
	{
		remaining_time[z] = process[z].service_time;
	}

	while (process_in_queue != jobs)
	{
		printf("|%3d", quantum_time);
		w++;

		for (z = 0; z < jobs; z++)
		{
			if ( (process[z].arrival_time <= quantum_time) && (remaining_time[z] < minimum) && (remaining_time[z] > 0) )
			{
				check = 1;
				minimum = remaining_time[z];
				process_executed = z;
				complete = 0;
			}
		}

			if (remaining_time[process_executed] > 0 && minimum != INT_MAX)
			{
				printf("#P%2d#|", process_executed);
			}
			if (minimum == INT_MAX)
			{
				printf("#IDLE|");
			}

		if (check == 0)				//This if statement is needed in case no process matched remaining time
		{					//which means that the processor wss idle, so we need to increase 
			quantum_time++;			//the quantum time, example @t=0 no process arrived then bool check remains false
							//or minimum remaining time
			if (w == 10) { 
				w = 0;
				printf("\n");	}
			continue;
		}

		remaining_time[process_executed]--;

		if (remaining_time[process_executed] < 0)
		{
			remaining_time[process_executed] = 0;
		}

		minimum = remaining_time[process_executed];
		if (minimum == 0)
		{
			minimum = INT_MAX;

		}
		if (remaining_time[process_executed] == 0 && complete == 0)
		{
		process_in_queue++;
		complete = 1;
		f = quantum_time + 1;
		finish_time[process_executed] = f;
		waiting_time[process_executed] = finish_time[process_executed] - process[process_executed].arrival_time - process[process_executed].service_time;
		turnaround_time[process_executed] = waiting_time[process_executed] + process[process_executed].service_time;

		}
		quantum_time++;
		if (w == 10)
		{
			w = 0;
			printf("\n");
		}


	}
do 
{
ww = quantum_time % 10;
printf("|%3d", quantum_time);
printf("#IDLE|");
if (ww == 9)
{
	printf("\n");
	ww = 0;
}
quantum_time++;
//printf("%d",ww);
} while (quantum_time <= 100);


printf("\n\n\n");

printf("%0s %5s %5s %5s %5s %5s %5s\n", "Process#", "Arrival_Time#", "Service_Time#", "Priority#", "Finish_Time#", "Waiting_Time#", "TurnAround_Time");

	for (j = 0; j < jobs; j++)
	{
		printf("P%d",j);
		printf("%14d", process[j].arrival_time);
		printf("%14d", process[j].service_time);
		printf("%14d", process[j].priority);
		printf("%14d", finish_time[j]);
		printf("%14d", waiting_time[j]);
		printf("%14d\n", turnaround_time[j]);

	}
	float avg_w = 0;
	float avg_t = 0;
	float pthroughput = 0;
	float jobsf = jobs;
	float qt = quantum_time - 1;

	for (j = 0; j < (jobs); j++)
	{
		avg_w += waiting_time[j];
		avg_t += turnaround_time[j];
	}
	avg_w = avg_w/jobs;
	pthroughput = (jobsf/qt)*100 ;
	avg_t = avg_t/jobs;

	printf("\n\n");
	printf("Average Waiting Time = %.2f\n", avg_w);
	printf("Average Response Time = %.2f\n", avg_w);
	printf("Average Turnaround Time = %.2f\n", avg_t);
	printf("Process Throughput = %.2f%\n", pthroughput);

}
/*
int main(int argc, char *argv[])
{

	int jobs = 0;

	printf("How many random processes you want to generate?\n");
	scanf("%d", &jobs);

	processing(jobs);

		return (0);
}
*/
