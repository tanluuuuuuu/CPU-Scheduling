#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

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
bool compareFunction(process, process);

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

bool compareFunction(process a , process b) {
	return a.burst_time > b.burst_time;
}

void SJF(const vector<process>& processes, int n)
{
	// Khoi tao cac gia tri
	map<int, int> mapp;
	for (int i = 0; i < n; i++)
	{
		mapp[p[i].ID] = i;
	}

	int star[n], finish[n], tat[n], wat[n];
	vector<process> temp;
	int j = 0;
	int sum_wt = 0, sum_tat = 0;
	int thoidiem = 0;
	for (int i = 0; i < n; i++)
	{
		if (i == 0)
		{
			star[i] = p[i].arrival_time;
			wat[i] = star[i] - p[i].arrival_time;
			finish[i] = star[i] + p[i].burst_time;
			tat[i] = finish[i] - p[i].arrival_time;
			thoidiem = finish[i];
			j++;
			while (j < n && p[j].arrival_time <= thoidiem)
			{
				temp.push_back(p[j++]);
			}
			sort(temp.begin(), temp.end(), compareFunction);
		}
		else
		{
			process pp = temp.back();
			temp.pop_back();

			star[ mapp[pp.ID] ] = thoidiem;
			wat[mapp[pp.ID]] = star[mapp[pp.ID]] - pp.arrival_time;
			finish[mapp[pp.ID]] = star[mapp[pp.ID]] + pp.burst_time;
			tat[mapp[pp.ID]] = finish[mapp[pp.ID]] - pp.arrival_time;

			thoidiem = thoidiem + pp.burst_time;
			while (j < n && p[j].arrival_time <= thoidiem)
			{
				temp.push_back(p[j++]);
			}
			sort(temp.begin(), temp.end(), compareFunction);
		}
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
