#include<stdio.h>


struct process
{
      int arrival_time, burst_time, current_time, wait_time, turnaround_time, priority,status;
}process_queue[10];

int no_of_process;

void Sorting_of_Arrival_Time()
{
      struct process temp;
      int i, j;
      for(i = 0; i < no_of_process - 1; i++)
      {
            for(j = i + 1; j < no_of_process; j++)
            {
                  if(process_queue[i].arrival_time > process_queue[j].arrival_time)
                  {
                        temp = process_queue[i];
                        process_queue[i] = process_queue[j];
                        process_queue[j] = temp;
                  }
            }
      }
}

int main()
{
      printf("\nPress 1 for Round Robin Scheduling");
      printf("\nPress 2 for Priority Scheduling");
      printf("\nEnter your choice :: ");
      int choice;
      scanf("%d",&choice);
      switch(choice)
      {
       case 1:
       {
              int counter,j,n,total_time,left_process,flag=0,time_quantum; 
              int wait_time=0,turnaround_time=0,arrival_time[10],burst_time[10],remaining_time[10]; 
              printf("\nEnter no of process :: "); 
              scanf("%d",&n); 
              left_process=n; 
              for(counter=0;counter<n;counter++) 
              { 
                printf("\nProcess%d\n",counter+1); 
                printf("Enter Arrival time :: "); 
                scanf("%d",&arrival_time[counter]); 
                printf("Enter Burst time :: ");
                scanf("%d",&burst_time[counter]); 
                remaining_time[counter]=burst_time[counter]; 
              } 
              printf("Enter Time Quantum ::"); 
              scanf("%d",&time_quantum); 
              printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n"); 
              for(total_time=0,counter=0;left_process!=0;) 
              { 
                if(remaining_time[counter]<=time_quantum && remaining_time[counter]>0) 
                { 
                  total_time+=remaining_time[counter]; 
                  remaining_time[counter]=0; 
                  flag=1; 
                } 
                else if(remaining_time[counter]>0) 
                { 
                  remaining_time[counter]-=time_quantum; 
                  total_time+=time_quantum; 
                } 
                if(remaining_time[counter]==0 && flag==1) 
                { 
                  left_process--; 
                  printf("P%d\t|\t%d\t|\t%d\n",counter+1,total_time-arrival_time[counter],total_time-arrival_time[counter]-burst_time[counter]); 
                  wait_time+=total_time-arrival_time[counter]-burst_time[counter]; 
                  turnaround_time+=total_time-arrival_time[counter]; 
                  flag=0; 
                } 
                if(counter==n-1) 
                  counter=0; 
                else if(arrival_time[counter+1]<=total_time) 
                  counter++; 
                else 
                  counter=0; 
              } 
              printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n); 
              printf("Avg Turnaround Time = %f",turnaround_time*1.0/n); 
              break;
       }
       case 2:
       {
              int i, total_time = 0, burst_time = 0, largest;
              float wait_time = 0, turnaround_time = 0, average_wait_time, average_turnaround_time;
              printf("\nEnter Total Number of Processes :: ");
              scanf("%d", &no_of_process);
              for(i = 0; i < no_of_process; i++)
              {
                    printf("\nProcess%d\n", i+1);
                    printf("Enter Arrival time :: "); 
                    scanf("%d", &process_queue[i].arrival_time );
                    printf("Enter Burst time :: ");
                    scanf("%d", &process_queue[i].burst_time);
                    printf("Enter Priority:\t");
                    scanf("%d", &process_queue[i].priority);
                    process_queue[i].status = 0;
                    burst_time = burst_time + process_queue[i].burst_time;
              }
              Sorting_of_Arrival_Time();
              process_queue[9].priority = -10000;
              printf("\nProcess Name\tArrival Time\tBurst Time\tPriority\tWaiting Time");
              for(total_time = process_queue[0].arrival_time; total_time < burst_time;)
              {
                    largest = 9;
                    for(i = 0; i < no_of_process; i++)
                    {
                          if(process_queue[i].arrival_time <= total_time && process_queue[i].status != 1 && process_queue[i].priority > process_queue[largest].priority)
                          {
                                largest = i;
                          }
                    }
                    total_time = total_time + process_queue[largest].burst_time;
                    process_queue[largest].current_time = total_time;
                    process_queue[largest].wait_time = process_queue[largest].current_time - process_queue[largest].arrival_time - process_queue[largest].burst_time;
                    process_queue[largest].turnaround_time = process_queue[largest].current_time - process_queue[largest].arrival_time;
                    process_queue[largest].status = 1;
                    wait_time = wait_time + process_queue[largest].wait_time;
                    turnaround_time = turnaround_time + process_queue[largest].turnaround_time;
                    printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", largest+1, process_queue[largest].arrival_time, process_queue[largest].burst_time, process_queue[largest].priority, process_queue[largest].wait_time);
              }
              average_wait_time = wait_time / no_of_process;
              average_turnaround_time = turnaround_time / no_of_process;
              printf("\n\nAverage waiting total_time:\t%f\n", average_wait_time);
              printf("Average Turnaround Time:\t%f\n", average_turnaround_time);
              break;
       }            
      }
     
}
