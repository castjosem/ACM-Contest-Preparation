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

//ifstream in("contest-f.txt");
//#define cin in
      
int main()
{
    int C, R, Q;
    while (cin>>C && C!=0)
    {
		vector<vector<int> > M(C,vector<int>(C,INT_MAX));
		vector<string> cities(C);
		
		for (int c=0; c<C; c++)
			cin>>cities[c];
		
		string road, str;
		cin>>R;
		
		string dummy;
		getline(cin, dummy);
		for (int r=0; r<R; r++)
		{
			getline(cin, str);
			istringstream iss(str);
			string city;
			
			vector<int> indices;
			while (iss>>str>>city)
			{
				for (int i=0; i<C; i++)
					if (cities[i]==city)
					{
						indices.push_back(i);
						break;
					}
			}
			for (int i=0; i<indices.size(); i++)
				for (int j=0; j<indices.size(); j++)
					M[indices[i]][indices[j]]=1;
		}
		
		//floyd warshall
		for (int k=0; k<C; k++)
			for (int i=0; i<C; i++)
				if (M[i][k]!=INT_MAX)
					for (int j=0; j<C; j++)
						if (M[k][j]!=INT_MAX)
							if (M[i][j] > M[i][k] + M[k][j])
								M[i][j] = M[i][k] + M[k][j];
		
		for (int i=0; i<C; i++)
			M[i][i]=0;
			
		cin>>Q;
		for (int q=0; q<Q; q++)
		{
			string origen, destino;
			cin>>origen>>destino;
			int u, v;
			for (u=0; u<C; u++)
				if (cities[u]==origen)
					break;
			for (v=0; v<C; v++)
				if (cities[v]==destino)
					break;
			
			
		
		/*
		for (int i=0; i<C; i++)
		{
			for (int j=0; j<C; j++)
				cout<<M[i][j]<<" ";
			cout<<endl;
		}
		cout<<endl;*/
		
			cout<<"Number of roads needed from "<<origen<<" to "<<destino<<" is "<<M[u][v]<<"."<<endl;
		}
	}
    
    //system("PAUSE");
    return 0;    
}
