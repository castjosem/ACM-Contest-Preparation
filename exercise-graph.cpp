#include <iostream>
#include <vector>
#include <fstream>
#define cin in
using namespace std;

ifstream in("exercise-graph.txt");  

int dx[] = {-1,1,0,0};
int dy[] = { 0,0,1,-1};

bool adentro(int i, int j, int n, int m)
{
	return (i>=0 && i<n && j>=0 && j<m);
}

int dijkstra(vector< vector<unsigned int> > matriz, int i1,int j1,int i2,int j2,int n, int m){
	vector< vector<bool> > visitados (n,vector<bool>(m,false));
	vector< vector<unsigned int> > distancias (n,vector<unsigned int>(m,INT_MAX));
	distancias[i1][j1] = 0;
	int dmin, ix,jy;
	while(1)
	{		
		visitados[i1][j1] = true;	
		for(int k=0; k<4 ; k++)
		{
			ix = i1 + matriz[i1][j1]*dx[k];
			jy = j1 + matriz[i1][j1]*dy[k];
			if(adentro(ix,jy,n,m) && !visitados[ix][jy])
				if(distancias[ix][jy] > distancias[i1][j1] + matriz[i1][j1] )
				{
					distancias[ix][jy] = distancias[i1][j1] + matriz[i1][j1];
				}
		}		
		i1 = -1, j1 = -1;
		dmin = INT_MAX;
				
		for(int i=0; i<n ; i++)
			for(int j=0; j<m ;j++)
				if(!visitados[i][j] && distancias[i][j] < dmin)
				{
					dmin = distancias[i][j];
					i1 = i;
					j1 = j;
				}
		if( i1== -1)
			break;
	}
	return distancias[i2][j2];
}


int main()
{
	int n,m;
	while(cin>>n>>m && n!=0 && m!=0)
	{
		vector< vector<unsigned int> > matriz (n, vector<unsigned int>(m));	
		int aux, i1,j1,i2,j2;
		for(int i=0 ; i<n ; i++)
			for(int j=0 ; j<m ; j++)
			{
				cin>>aux;
				matriz[i][j] = aux;
			}
		cin >> i1 >> j1 >> i2 >> j2;
		cout << dijkstra(matriz,i1,j1,i2,j2,n,m) << endl;		
	}
	system("pause");
	return 0;	
}
