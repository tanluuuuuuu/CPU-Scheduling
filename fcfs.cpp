#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;

struct process
{
	int ID;
	int arrival_time;
	int burst_time;
};

void swap(process&, process&);
void sort(vector<process>&, int);
void FCFS(const vector<process>&, int);

int main()
{
	// Nhap thong tin
        int n;
        cout << "Nhap so luong process: ";
        cin >> n;
        vector<process> processes(n);
        
        for (int i = 0; i < n; i++)
        {
                cout << "Nhap lan luot ID process, arrival time va burst time: ";
                cin >> processes[i].ID;
                cin >> processes[i].arrival_time;
                cin >> processes[i].burst_time;
        }
        
        // Sap xep theo thu tu xuat hien
        // Input: danh sach process do user nhap theo thu tu nhap
        // Output: danh sach process do user nhap theo thu tu xuat hien (arrival time)
        sort(processes, n);
        
        // Thuc hien giai thuat first come first serve
        FCFS(processes, n);
}

void swap(process& a, process& b)
{
	process t = a;
	a = b;
	b = t;
}

void sort(vector<process>& processes, int n)
{
	// Giai thuat 
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (processes[i].arrival_time > processes[j].arrival_time)
			{
				swap(processes[i], processes[j]);
			}
		}
	}
}

void FCFS(const vector<process>& processes, int n)
{
	//Khoi tao cac gia tri
	// start_time: Start time cua cac tien trinh
	// finish_time: Finish time cua cac tien trinh
	// tat: Turnaround time cua cac tien trinh
	// wt: Waiting time cua cac tien trinh
	// sum_tat: Tong Turnaround time cua cac tien trinh
	// sum_wt: Tong waiting time cua cac tien trinh
	
	vector<int> start_time(n), finish_time(n), tat(n), wt(n);
	int thoidiem = processes[0].arrival_time;
	int sum_tat = 0, sum_wt = 0;
	
	for (int i = 0; i < n; i++)
	{
		start_time[i] = (processes[i].arrival_time > thoidiem) ? processes[i].arrival_time : thoidiem;
		finish_time[i] = start_time[i] + processes[i].burst_time;
		tat[i] = finish_time[i] - processes[i].arrival_time;
		wt[i] = start_time[i] - processes[i].arrival_time;
		
		thoidiem = finish_time[i];
	}
	
	cout << "\nName\tArrTime\tBurtime\tStart\tTAT\tFinish" << endl;

	for (int i = 0; i < n; i++)
	{
			printf("\n%d\t%6d\t%6d\t%6d\t%6d\t%6d",processes[i].ID,processes[i].arrival_time,
	processes[i].burst_time, start_time[i], tat[i], finish_time[i]);
		sum_tat += tat[i];
		sum_wt += start_time[i] - processes[i].arrival_time;
	}
	printf("\nAverage waiting time: %f", (float)sum_wt / n);
	printf("\nAverage turnaround time: %f\n", (float)sum_tat / n);
}
