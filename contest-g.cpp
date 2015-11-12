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

//ifstream in("contest-g.txt");
//#define cin in

bool bfs(vector<bool> &visit , vector< vector<int> > &list , int origen , int destino)
{
	visit[origen] = true;
	vector<int> dist (list.size() , INT_MAX);
	dist[origen] = 0;
	queue<int> cola;
	cola.push(origen);

	int aux;
	while(!cola.empty())
	{
		aux = cola.front();
		cola.pop();
		
		for(int i=0 ; i<list[aux].size() ; i++)
		{
			if(!visit[list[aux][i]])
			{
				cola.push(list[aux][i]);
				visit[list[aux][i]] = true;
				dist[list[aux][i]] = dist[aux] + 1;			
			}
		}	
	}	
	if(dist[destino] != INT_MAX)
		return true;
	return false;
}
	  
int main()
{
	int tour;
	int edges;
	string str , str2;
	
	while(cin >> tour && tour!=0)
	{
		  vector<string> cities;
		  vector< vector<int> > list;
		  
		  for(int i=0 ; i<tour ; i++)
		  {
			   cin >> str;
			   vector<int> aux;
			   cities.push_back(str);
			   list.push_back(aux);   
		  }
		  cin >> edges;
		  
		  for(int k=0 ; k<edges ; k++)
		  {
			   cin >> str;
			   int i,j;
			   for(i=0 ; i<cities.size() ; i++)
					   if(cities[i]==str)
							   break;
			   if( i == cities.size() )
			   {
				   vector<int> aux;
				   cities.push_back(str);
				   list.push_back(aux);				  
			   }			   
			   
			   cin >> str2;
			   for(j=0 ; j<cities.size() ; j++)
					   if(cities[j]==str2)
							   break;
			   if( j == cities.size() )
			   {
				   vector<int> aux;
				   cities.push_back(str2);
				   list.push_back(aux);				  
			   }	  
			   list[i].push_back(j);
			    
		  }			
		  bool ok = true;		  		 
	 	for(int i=0 ; i<tour-1 && ok ; i++)
		{
				  vector<bool> visit (cities.size() , false); 
				  for(int j=0 ; j<tour ; j++)
						visit[j] = true;
				  visit[i+1] = false;
				  
				ok = bfs(visit , list , i , i+1);		 
		  }
			  
		  if(ok)
			   cout << "The tour can be planned." << endl;
		  else
		  	   cout << "The tour cannot be planned with the given flight segments." << endl;	
	}	
	return 0;
}
