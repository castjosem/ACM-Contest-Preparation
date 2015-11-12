#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <string>
#include <iostream>
using namespace std;


#define gtype int
#define gnull -1
typedef vector< vector<bool> > graph;
typedef vector< vector<gtype> > graphe;
#define newGraph( n) graph( n, vector<bool>( n, false ) )
#define newGraphe(n) graphe( n, vector<gtype>( n , gnull) )

//camino mas corto entre v y los demas vertices
vector<int> dijkstra(const graphe& g, int v)
{
	vector<bool> s(g.size(), false);
	vector<int> dis(g.size());
	s[v]=true;
	vector<int> p(g.size(), v);	//pare recuperar los caminos
	for(int i=0; i<g.size(); i++)
		dis[i]=g[v][i];
	for(int i=0; i<g.size()-1; i++)
	{
		//busca el vertice menor que no este en s
		int min=-1;
		for(int j=0; j<g.size(); j++)
		{
			if(!s[j])
			{
				if(dis[j]!=gnull && (min<0 || dis[j]<dis[min]))
				{
					min=j;
				}
			}
		}
		if(min==-1)return p;
		s[min]=true;
		for(int j=0; j<g.size(); j++)
		{
			if(dis[min]!=gnull && g[min][j]!=gnull)
			{
				if(dis[min]+g[min][j] < dis[j] || dis[j]==gnull)
				{
					dis[j]=dis[min]+g[min][j];
					p[j]=min;
				}
			}
		}
	}
	return p;
}
ostream& operator<<(ostream& out, const graph &g)
{
	for(int i=0; i<g.size(); i++)
	{
		for(int j=0; j<g.size(); j++)
		{
			cout.width(3);
			out<<g[i][j]<<"  ";
		}
		out<<endl;
	}
	return out;
}


//AQUI EMPIEZA EL CODIGO
int n,m;
bool dentro(int x, int y)
{
  if(x<0 || y<0)
    return false;
  if (x>n || y>m)
    return false;
  return true;
}
int pos(int x, int y)
{
  return x*m+y;
}
int main()
{
  
  cin>>n>>m;
  graphe g=newGraphe(n*m);
  int dirx[]={0,0,1,-1};
  int diry[]={-1,1,0,0};
  for(int i=0; i<n;i++)
  {
    for(int j=0; j<m; j++)
    {
      int dis;
      cin>>dis;
      for(int d=0; d<4; d++)
      {
	if(dentro(i+dirx[d], j+diry[d]))
	{
	  g[pos(i,j)][pos(i+dirx[d], j+diry[d])]=1;
	  g[pos(i,j)][pos(i+dirx[d], j+diry[d])]=1;
	}
      }
    }
  }
  int xo, yo, xd, yd;
  cin>>xo>>yo>>xd>>yd;
  cout<<dijkstra(g, pos(xo, yo))[pos(xd,yd)]<<endl;
}



