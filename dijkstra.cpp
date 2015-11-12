#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;


#define MAX 100  
#define cin in

vector<vector<int> > graph;
int total;           
vector<int> distances[MAX];          
vector<int> father[MAX];     
vector<bool> visit[MAX]; 

void dijkstra(int start)
{
	priority_queue<pair<int,int> > queue;
	pair <int,int> nodotmp;
  	int i, j;
  
  	for (i=1; i<=total; i++) 
	{
		distances[i] = INT_MAX;
    	father[i] = -1;
    	visit[i] = false;
    }
 
  	distances[start] = 0;
  	queue.push(pair <int,int> (distances[start], start));
 
  	while(!queue.empty()) 
	{
		nodotmp = queue.top();  
    	queue.pop();
    	i = nodotmp.second;
    	if (!visit[i]) 
		{
			visit[i] = true;
      		for (j = 1; j<=total; j++)
        		if (!visit[j] && graph[i][j] > 0 && distances[i] + graph[i][j] < distances[j]) 
				{
					distances[j] = distances[i] + graph[i][j];
          			father[j] = i;
          			queue.push(pair <int,int>(-distances[j], j));
		      	}
    	}
  	}
}


void getPath(int end) {
  cout << end << " ";
  while (father[end]!= -1) { 
    cout << father[end] << " ";
    end = father[end];
  }
  cout << endl;
}

int main()
{
   ifstream in("Dijkstra.txt");
   int a, b, c;
   int tedges;
   
   graph = vector<vector<int> >(MAX, vector<int>(MAX, 0));
   
   cin >> total >> tedges;
   for (int i=0; i<tedges; i++) {
     cin >> a >> b >> c;
     graph[a][b] = c;
   }
   for(int i=1; i<=total; i++) {
      for(int j=1; j<=total; j++)
         cout << setw(3) << graph[i][j];
      cout << endl;
   }
   
   for (int i=1; i<=total; i++) {
     dijkstra(i);
     cout << endl << "Dijkstra desde :" << i << endl;
     for(int i=1; i<=total; i++) {
        if( distances[i] == INT_MAX )
            cout << setw(3) << "--";
        else
            cout << setw(3) <<  distances[i];
     }
     cout << endl;
     cout << "Pred: " << endl;
     for(int i=1; i<=total; i++)
     {
        cout << setw(3) << father[i];
     }
     cout << endl;
     getPath(2);
   }
   system("PAUSE");
   return 0;
}
