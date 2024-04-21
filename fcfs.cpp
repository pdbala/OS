// EASY ONE 
#include <bits/stdc++.h>
using namespace std;

class Process {
public:
	int at;
	int bt;
	int ct;
	int tat;
	int wt;
	int pid;

	void update_after_ct()
	{
		tat = ct - at;
		wt = tat - bt;
	}

	void display()
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid, at, bt, ct,
			tat, wt);
	}
};

float average(vector<Process> P)
{
	int total = 0;
	for (auto temp : P) {
		total += temp.wt;
	}
	return (float)total / P.size();
}

int main()
{
	int n;
	cin >> n;
	int counter = 0;
	vector<Process> P(n);

	for(int i=0;i<P.size();i++){
	    P[i].pid =counter++;
	    cin >> P[i].at>>P[i].bt;
	}
	sort(P.begin(), P.end(),
		[](Process first, Process second) {
			return first.at < second.at;
		});
	printf("pid\tat\tbt\tct\ttat\twt\n");
	P[0].ct = P[0].at + P[0].bt;
	P[0].update_after_ct();
	P[0].display();
	for (int i = 1; i < P.size(); i++) {
    //clash
		if (P[i].at < P[i - 1].ct) {
			P[i].ct = P[i - 1].ct + P[i].bt;
		}
    //no clash
		else {
//   	printf("curr['at'] : %d, prev['ct'] : %d\n",P[i].at, P[i - 1].ct);
			P[i].ct = P[i].at + P[i].bt;
		}
		P[i].update_after_ct();
		P[i].display();
	}

	printf("Average waiting time : %f\n", average(P));
	return 0;
}


#include<iostream>
#include<vector>
using namespace std;

int main(){
  int n;
  cout<<"Enter the number of processes : ";
  cin>>n;
  int process[n];
   int arrival[n];
    int burst[n];
  cout<<"Enter the arrival time for processes : ";
  for(int i=0;i<n;i++){
     int x;
     cin>>x;
     process[i] = i+1;
     arrival[i] = x;
  }
  cout<<"Enter the burst time for processes : ";
  for(int i=0;i<n;i++){
     int y;
     cin>>y;
     burst[i] = y;
  }

  //sort the process
for(int i=0;i<n;i++){
int pos = i;
for(int j=i+1;j<n;j++){
 if(arrival[j]<arrival[pos])
     pos = j;
 }

 int temp;
 temp = arrival[i];
 arrival[i] = arrival[pos];
 arrival[pos] = temp;

 int temp1;
 temp1 = burst[i];
 burst[i] = burst[pos];
 burst[pos] = temp1;

 int temp2;
 temp2 = process[i];
 process[i] = process[pos];
 process[pos] = temp2;
}

  int wt[n];
  int tt[n];
  vector<int> ct(n, 0);
  ct[-1] = 0;
   for(int i=0;i<n;i++){
    ct[i] = ct[i-1] + burst[i];
  }

  for(int i=0;i<n;i++){
    //Turnaround time = waiting time + burst time or TAT = CT - AT
     tt[i] = ct[i] - arrival[i];
  }


  for(int i=0;i<n;i++){
    //waiting time = burst of prev + waiting time of prev  or TAT - BT
     wt[i] = tt[i] - burst[i];
  }

  float totalct = 0;
  for(int i=0;i<n;i++){
    totalct += ct[i];
  }
 float totaltt = 0;
  for(int i=0;i<n;i++){
    totaltt += tt[i];
  }
  float totalwt = 0;
  for(int i=0;i<n;i++){
    totalwt += wt[i];
  }

   cout<<"Process id"<<"\t"<<"Arrival Time"<<"\t"<<"Burst Time"<<"\t"<<"Completion Time"<<"\t"<<"Tunraround Time"<<"\t"<<"Waiting Time"<<endl;
   for(int i=0;i<n;i++){
    cout<<process[i]<<"\t\t"<<arrival[i]<<"\t\t"<<burst[i]<<"\t\t"<<ct[i]<<"\t\t"<<tt[i]<<"\t\t"<<wt[i]<<endl;
  }
  cout<<"Total Completion time for process is : ";
  cout<<totalct;
  cout<<" milliseconds\n";
  cout<<"Average Waiting time for process is : ";
  float avgwt = totalwt/n;
  cout<<avgwt;
  cout<<"\n";
  cout<<"Average Turnaround time for process is : ";
  float avgtt = totaltt/n;
  cout<<avgtt;
  cout<<"\n";
  return 0;
}
