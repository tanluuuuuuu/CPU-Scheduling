#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <list>

using namespace std;

struct process
{
	int ID;
	int arr_time;
	int brt_time;
	int str_time;
	int fin_time;
	int tat_time;
	int w_time;
	process()
	{
		ID = -1;
		arr_time = 0;
		brt_time = -1;
		str_time = -1;
		fin_time = -1;
		tat_time = -1;
		w_time = 0;
	}
	
	bool operator < (const process& prs) const
	{
		return brt_time < prs.brt_time;
	}
};

void swap(struct process&, struct process&);
void sort(vector<process>&, int);
void SRT(const vector<process>&, int, int);
bool compare_brt_time(const process& a, const process& b)
{
	return a.brt_time < b.brt_time;
}

int main()
{
	int n;
	cout << "Nhap so tien trinh: ";
	cin >> n;
	
	int sum_time = 0;
	vector<process> processes(n);
	for (int i = 0; i < n; i++)
	{
		cout << "Nhap ID, arrival time, burst time cua tien trinh: ";
		cin >> processes[i].ID >> processes[i].arr_time >> processes[i].brt_time;
		
	}
	
	// Sap xep tang dan tien trinh theo thu tu xuat hien
	// va theo thoi gian thuc hien
	// Bang thuat toan interchange sort
	sort(processes, n);
	
	for (int i = 0; i < n; i++)
	{
		if (i == 0)
		{
			sum_time += processes[i].arr_time + processes[i].brt_time;
		}
		else if (processes[i].arr_time > sum_time)
		{
			sum_time = processes[i].arr_time + processes[i].brt_time;
		}
		else
		{
			sum_time += processes[i].brt_time;
		}
	}
	
	// Thuc hien thuat toan shortest remaining time
	SRT(processes, n, sum_time);
	
}

void swap(struct process& a, struct process& b)
{
	struct process t;
	t = a;
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
			if (processes[i].arr_time > processes[j].arr_time)
			{
				swap(processes[i], processes[j]);
			}
			// Sap xep tang dan theo thoi gian burst time
			else if (processes[i].arr_time == processes[j].arr_time && processes[i].brt_time > processes[j].brt_time)
			{
				swap(processes[i], processes[j]);
			}
		}
	}
}

void SRT(const vector<process>& processes, int n, int sum_time)
{
	queue<process> process_q;
	map<int, int> brt_t;
	vector<process> result;
	
	for (int i = 0; i < n; i++)
	{
		brt_t[processes[i].ID] = processes[i].brt_time;
		process_q.push(processes[i]);
	}
		
	list<process> wait_l;

	for (int thoidiem = max(0, processes[0].arr_time); thoidiem <= sum_time; thoidiem++)
	{
		while(!process_q.empty() && process_q.front().arr_time <= thoidiem)
		{
			wait_l.push_back(process_q.front());
			process_q.pop();
		}
		wait_l.sort(compare_brt_time);
		
		wait_l.front().brt_time--;
		
		if (!wait_l.empty() && wait_l.front().str_time == -1)
			wait_l.front().str_time = thoidiem;
		
		if (!wait_l.empty() && wait_l.front().brt_time <= 0)
		{
			wait_l.front().fin_time = thoidiem + 1;
			wait_l.front().tat_time = wait_l.front().fin_time - wait_l.front().arr_time;
			wait_l.front().w_time = wait_l.front().tat_time - brt_t[wait_l.front().ID];
			result.push_back(wait_l.front());
			
			wait_l.pop_front();
		}
	}
	
	int sum_tat = 0, sum_w = 0;
	cout << "ID\tArrival\tBurst\tStart\tFinish\tTAT\tWait" << endl;
	for (int i = 0 ; i < n; i++)
	{
		cout << result[i].ID << "\t";
		cout << result[i].arr_time << "\t";
		cout << brt_t[result[i].ID] << "\t";
		cout << result[i].str_time << "\t";
		cout << result[i].fin_time << "\t";
		cout << result[i].tat_time << "\t";
		cout << result[i].w_time << "\t";
		cout << endl;
		sum_tat += result[i].tat_time;
		sum_w += result[i].w_time;
	}	
	cout << "Average waiting time: " << (float)sum_w/n << endl;
	cout << "Average turnaround time: " << (float)sum_tat/n << endl;
}
