#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

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
};

void swap(struct process&, struct process&);
void sort(vector<process>&, int);
void RR(const vector<process>&, int, int);

int main()
{
	int n;
	cout << "Nhap so tien trinh: ";
	cin >> n;
	int t_sl;
	cout << "Nhap timeslice: ";
	cin >> t_sl;
	
	vector<process> processes(n);
	for (int i = 0; i < n; i++)
	{
		cout << "Nhap ID, arrival time, burst time cua tien trinh: ";
		cin >> processes[i].ID >> processes[i].arr_time >> processes[i].brt_time;
	}
	
	// Sap xep danh sach tien trinh theo arrival time
	// bang thuat toan interchange sort
	sort(processes, n);
	
	// Thuc hien giai thuat round robin
	RR(processes, n, t_sl);
	
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
			if (processes[i].arr_time > processes[j].arr_time)
			{
				swap(processes[i], processes[j]);
			}
		}
	}
}

void RR(const vector<process>& processes, int n, int t_slice)
{
	queue<process> process_q;
	for (int i = 0; i < n; i++)
		process_q.push(processes[i]);
		
	queue<process> wait_q;
	
	vector<process> result;
	
	map<int, int> brt_t_remain;
	
	for (int i = 0; i < n; i++)
	{
		brt_t_remain[processes[i].ID] = processes[i].brt_time;
	}
	
	int thoidiem = process_q.front().arr_time;
	bool popyet = false;
	
	do
	{
		// Lay cac tien trinh dua vao hang doi
		while(!process_q.empty() && process_q.front().arr_time <= thoidiem)
		{
			wait_q.push(process_q.front());
			process_q.pop();
		}
		if (!process_q.empty() && process_q.front().arr_time > thoidiem && wait_q.empty())
		{
			thoidiem = process_q.front().arr_time;
			continue;
		}
		
		if (!popyet)
		{
			// Dua ve cuoi hang doi
			wait_q.push(wait_q.front());
			wait_q.pop();
		}
		popyet = true;
		
		// Xem tien trinh dang xu ly 
		cout << wait_q.front().ID << endl;
		
		if (wait_q.front().str_time == -1)
			wait_q.front().str_time = thoidiem;
	
		// Luc xong
		if (brt_t_remain[wait_q.front().ID] <= t_slice)
		{	
			wait_q.front().fin_time = thoidiem + brt_t_remain[wait_q.front().ID];
			wait_q.front().tat_time = wait_q.front().fin_time - wait_q.front().arr_time;
			wait_q.front().w_time = wait_q.front().tat_time - wait_q.front().brt_time;
			
			thoidiem += brt_t_remain[wait_q.front().ID];
			brt_t_remain[wait_q.front().ID] = 0;
			
			// Dua vao ket qua
			result.push_back(wait_q.front());
			wait_q.pop();
			
			popyet = true;
			
			cout << "Current time: " << thoidiem << endl;
		}
		else // Luc chua xong
		{			
			// Giam thoi` gian thuc thi con` lai
			brt_t_remain[wait_q.front().ID] -= t_slice;
			
			// Tang thoi diem
			thoidiem += t_slice;
			
			popyet = false;
			
			cout << "Current time: " << thoidiem << endl;
		}
	}while (!wait_q.empty() || !process_q.empty());
	
	int sum_tat = 0, sum_w = 0;
	cout << "ID\tArrival\tBurst\tStart\tFinish\tTAT\tWait" << endl;
	for (int i = 0 ; i < n; i++)
	{
		cout << result[i].ID << "\t";
		cout << result[i].arr_time << "\t";
		cout << result[i].brt_time << "\t";
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
