#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <math.h>
#include <queue>
using namespace std;

//ifstream in("contest-a.txt");
//#define cin in
      
int main()
{
	string name;
    int team, problem, caso=1;
    while (cin>>team>>problem && !(team==0 && problem==0))
    {
		vector<vector<int> > M(team, vector<int>(problem));
		for (int i=0; i<team; i++)
		{
			cin>>name;
			for (int j=0; j<problem; j++)
				cin>>M[i][j];
		}
		
		int score=0;
		
		vector<bool> solved(problem, false);
		for (int i=0; i<team; i++)
			for (int j=0; j<problem; j++)
				if (M[i][j]==1)
					solved[j]=true;
		int count=0;
		for (int j=0; j<problem; j++)
			if (solved[j])
				count++;
		if (count==problem)
			score+=1;
		
		vector<int> teamsolved(team, 0);
		for (int i=0; i<team; i++)
			for (int j=0; j<problem; j++)
				if (M[i][j]==1)
					teamsolved[i]++;
		
		count=0;
		for (int i=0; i<team; i++)
			if (teamsolved[i]>=2)
				count++;
		if (count>team*0.9)
			score+=2;
			
		count=0;
		for (int i=0; i<team; i++)
			if (teamsolved[i]==problem)
				count++;	
		
		if (count==0)
			score+=2;
					
		cout<<"Contest "<<caso<<": "<<score<<endl;
		caso++;
	}
	//system("PAUSE");
    
    return 0;    
}
