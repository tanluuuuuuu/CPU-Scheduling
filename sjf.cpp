#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct process
{
	int ID;
	int arrival_time;
	int burst_time;
};

void swap(process&, process&);
void sort(vector<process>& processes, int);
void SJF(const vector<process>& processes, int);

int main()
{
	// Nhap thong tin
        int n;
        printf("Nhap so luong process: ");
        scanf("%d", &n);
        vector<process> processes(n);
        
        for (int i = 0; i < n; i++)
        {
                printf("Nhap lan luot ID process, arrival time va burst time: ");
                scanf("%d%d%d", &processes[i].ID, &processes[i].arrival_time, &processes[i].burst_time);
        }
        
        // Sap xep theo thu tu xuat hien
        // Neu thu tu xuat hien bang nhau, sap xep theo thu tu tang dan
        // cua thoi gian thuc hien
        sort(processes, n);
        
        // Thuc hien giai thuat Shortest Job First
        SJF(processes, n);
}

void swap(process& a, process& b)
{
	process t = a;
	a = b;
	b = t;
}

void sort(vector<process>& processes, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			// Sap xep tang dan theo thoi gian xuat hien
			if (processes[i].arrival_time > processes[j].arrival_time)
			{
				swap(processes[i], processes[j]);
			}
			// Sap xep tang dan theo thoi gian burst time
			else if (processes[i].arrival_time == processes[j].arrival_time && processes[i].burst_time > processes[j].burst_time)
			{
				swap(processes[i], processes[j]);
			}
		}
	}
}

void SJF(const vector<process>& processes, int n)
{
	// Khoi tao cac gia tri
	int start_time[n], finish_time[n], tat[n], wt[n];
	int thoidiem = processes[0].arrival_time;
	int sum_wt = 0, sum_tat = 0;
	for (int i = 0; i < n; i++)
	{
		start_time[i] = (processes[i].arrival_time > thoidiem) ? processes[i].arrival_time : thoidiem;
		finish_time[i] = start_time[i] + processes[i].burst_time;
		tat[i] = finish_time[i] - processes[i].arrival_time;
		wt[i] = start_time[i] - processes[i].arrival_time;
		
		thoidiem = finish_time[i];
	}
	
	printf("\nName\tArrTime\tBurtime\tStart\tTAT\tFinish");

	for (int i = 0; i < n; i++)
	{
			printf("\n%d\t%6d\t%6d\t%6d\t%6d\t%6d",processes[i].ID,processes[i].arrival_time,
	processes[i].burst_time, start_time[i], tat[i], finish_time[i]);
		sum_tat += tat[i];
		sum_wt += start_time[i] - processes[i].arrival_time;
	}
	printf("\nAverage waiting time: %f", (float)sum_wt / n);
	printf("\nAverage turnaround time: %f\n", (float)sum_tat / n);
	printf("\n");	
}
