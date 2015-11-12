#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <string>
#include <iostream>
using namespace std;
#define DEBUG
#ifdef DEBUG
#	define SDEBUG(var)	cerr<<var<<endl;
#	define CDEBUG(var)	cerr<<#var<<"="<<var<<endl;
#	define DVAR(var)	" "<<#var<<"="<<var<<" "
#else
#	define SDEBUG(var)
#	define CDEBUG(var)
#	define DVAR(var)
#endif


//EXTRA componentes fuertemente conexas
/*Arboles*/
/*typedef int ttype;
typedef vector<ttype> tree;
#define tnull
#define newTree(n) tree(n,vacio)
void insert*/
/*Grafos*/
#define gtype int
#define gnull -1
typedef vector< vector<bool> > graph;
typedef vector< vector<gtype> > graphe;
#define newGraph( n) graph( n, vector<bool>( n, false ) )
#define newGraphe(n) graphe( n, vector<gtype>( n , gnull) )
//Algoritmo de los caminos mas cortos entre todos los nodos
vector<vector<int> > floyd(graphe& g)
{

	vector<vector<int> > p(g.size(),vector<int>(g.size(), -1));//sirve para recuperar el camino
	for(int k=0; k<g.size(); k++)
	{
		for(int i=0; i<g.size(); i++)
		{
			for(int j=0; j<g.size(); j++)
			{
				if(g[i][k]!=gnull && g[k][j]!=gnull)
				{
					int t=g[i][k]+g[k][j];
					if(t < g[i][j] || g[i][j]==gnull)
					{
						g[i][j]=t;
						p[i][j]=k;
					}
				}
			}
		}
	}
	return p;
}
//recupera el camino generado con floyd
void camino(int i, int j, const vector<vector<int> > &p, list<int> &c)
{
	int k=p[i][j];
	if(k==-1)return;
	camino(i,k, p, c);
	c.push_back(k);
	camino(k,j, p, c);
}
//camino mas corto entre v y los demas vertices
vector<int> dijkstra(const graphe& g, int v, vector<int> &dis)
{
	vector<bool> s(g.size(), false);
	//vector<int> dis(g.size());
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
//prim y kruskal arbol de costo minimo
//arbol abarcador de costo minimo, grafos no dirigidos
//usa 0 como infinito
//TODO PRUEBAME
graphe prim(graphe g)
{
	int cercano[g.size()];
	gtype menor[g.size()];
	//int i,j,k,min;
	graphe arbol=newGraphe( g.size());
	for(int i=1; i<g.size(); i++)
	{
		menor[i]=g[0][i];
		cercano[i]=0;
	}
	for(int i=1; i<g.size(); i++)
	{
		int min=-1;
		for(int j=1; j<g.size(); j++)
		{
			if(menor[j]>0 && (min<0 || menor[j] < menor[min]))
			{
				min=j;
			}
		}
		arbol[min][cercano[min]]=menor[min];
		arbol[cercano[min]][min]=menor[min];
		menor[min]=-1;

		for(int j=1; j<g.size(); j++)
		{
			if((g[min][j]>0) && (menor[j]<=0 || g[min][j]<menor[j]))
			{
				menor[j]=g[min][j];
				cercano[j]=min;
			}
		}
	}
	return arbol;
}
//orden topologico con prueba de aciclicidad
list<int> ordenTopologico(graph g)
{
	list<int> pila;
	vector<bool> array(g.size(), false);
	int c=g.size();
	while(c>0)
	{
		int i;
		for(i=0; i<g.size(); i++)
		{
			if(!array[i])
			{
				int j;
				for(j=0; j<g.size(); j++)
				{
					if(g[j][i])
						break;
				}
				if(j==g.size())
					break;
			}
		}
		if(i==g.size())
			return list<int>();
		array[i]=true;
		pila.push_back(i);//AQUI
		for(int k=0; k<g.size(); k++)
			g[i][k]=false;
		c--;
	}
	return pila;
}
//orden topologico, necesita el vertice de inicio, no tiene prueba de aciclicidad
/*list<int> ordenTopologico(const graph &g, int v, vector<bool> *array=NULL, list<int>* c=NULL)
{
	if(array==NULL)
	{
		array=new vector<bool>(g.size(), false);
		c=new list<int>();
	}
	(*array)[v]=true;
	for(int i=g.size()-1;i>=0; i--)
	//for(int i=0;i<g.size(); i++)
	{
		if(!(*array)[i])
		{
			if( g[v][i] )
				ordenTopologico(g, i, array,c);
		}
	}
	c->push_front(v);
	return *c;
}*/
//recorrido en ahcho
//TODO no ha sido probado
void bea(const graph &g, int v, vector<bool> &array)
{
	queue<int> cola;
	cola.push(v);

	array[v]=true;

	while( !cola.empty())
	{
		int t=cola.front();cola.pop();
		//aqui
		for(int i=0; i<g.size(); i++)
		{
			if(g[t][i] && !array[i])
			{
				cola.push(i);
				array[i]=true;
			}
		}
	}
}
//recorrido en profundidad
void bpf(const graph &g, int v, vector<bool> &array)
{
	array[v]=true;
	//aqui
	for(int i=0;i<g.size(); i++)
	{
		if(!array[i])
		{
			if( g[v][i] )
				bpf(g, i, array);
		}
	}
	//o aqui
}
//Version iterativa;		// No se puede hacer inverso
void bpfi(const graph &g, int v, vector<bool> &marc)
{
	stack<int> pila;
	pila.push( v );
	while ( !pila.empty() )
	{
		v = pila.top(); pila.pop();
		if ( !marc[ v ] )
		{
			marc[ v ] = true;
			//aqui
			for(int i=0; i<g.size(); i++)
			{
				//if(g[v][i])
				if(g[v][i] && !marc[i])
					pila.push( i );
			}
		}
	}
}
//necesario para fulkerson
graphe operator-(const graphe& g, const graphe &e)
{
	graphe r=newGraphe(g.size());
	for(int i=0; i<g.size(); i++)
	{
		for(int j=0; j<g.size(); j++)
		{
			r[i][j]=g[i][j]-e[i][j];
		}
	}
	return r;
}
//busca camino entre O y D		p[i]=el vertice que esta antes de i
bool buscarCamino(const graphe &g, const int &o, const int &d, vector<int>& p)
{
	vector<bool> marc(g.size(), false);
	stack<int> pila;
	pila.push( o );
	while ( !pila.empty() )
	{
		int v = pila.top(); pila.pop();
		if ( !marc[ v ] )
		{
			marc[ v ] = true;
			for(int i=0; i<g.size(); i++)
			{
				if(g[v][i]!=gnull && !marc[i])
				{
					p[i]=v;
					if(i==d)
						return true;
					pila.push( i );
				}
			}
		}
	}
	return false;
}
bool buscarCamino(const graphe &g, const int &o, const int &d, list<int>& p)
{
	vector<int> a(g.size(), -1);		//guarda el vertice anterior
	p.clear();
	if(buscarCamino(g,o,d,a))
	{
		int i=d;
		p.push_front(i);
		while(i!=o)
		{
			p.push_front(a[i]);
			i=a[i];
		}
		return true;
	}
	return false;
}
//flujo, funciona para grafos etiquetados aciclicos
graphe fordfulkerson(const graphe& g, const int &s, const int &t)
{
	graphe e=newGraphe(g.size());
	graphe r=g-e;
	list<int> p;
	while(buscarCamino(r, s, t, p))
	{
		int min=-1;		//busco el enlace minimo del camino
		list<int>::iterator i;
		for(i=p.begin(); i!=(--p.end()); )
		{
			int o=*i, d=*(++i);
			int c=r[ o ][ d ];
			if(min==-1 || c<min)
				min=c;
		}
		//le incremento o resto el camino
		for(i=p.begin(); i!=(--p.end()); )
		{
			int o=*i, d=*(++i);
			e[ o ][ d ]+=min;
			e[ d ][ o ]-=min;
		}
		r=g-e;
	}
	return e;
}
//devuelve el numero de componentes conexas de un grafo no dirigido
int componentesConexas(const graph &g)
{
	vector<bool> array(g.size(), false);
	int c=0;
	for(int i=0; i<g.size(); i++)
	{
		if(!array[i])
		{
			c++;
			bpf(g,i,array);
		}
	}
	return c;
}
//cerradura transitiva; te dice que vertices tienen caminos a que vertices
graph warshall(const graph &c)
{
	int nVert=c.size();
	graph a=newGraph(nVert);
	for ( int i = 0; i < nVert; i++ )
		for ( int j = 0; j < nVert; j++ )
			a[ i ][ j ] = c[i][j];
	for ( int k = 0; k < nVert; k++ )
		for ( int i = 0; i < nVert; i++ )
			for ( int j = 0; j < nVert; j++ )
				if ( !a[ i ][ j ] )
					a[ i ][ j ] = a[ i ][ k ] && a[ k ][ j ];
	return a;
}
//devuelve true si un grafo es aciclico
//TODO ineficiente
bool isAciclic(const graph &g)
{
	graph r=warshall(g);
	for(int i=0; i<g.size(); i++)
		if(r[i][i])
			return false;
	return true;
}
//Devuelve true si hay un camino de v a v2
//TODO no ha sido probado
bool depend(const graph &g, int v, int v2)
{
	vector<bool> marc(g.size(), false);
	stack<int> pila;
	pila.push( v );
	while ( !pila.empty() )
	{
		v = pila.top(); pila.pop();
		if ( !marc[ v ] )
		{
			marc[ v ] = true;
			for(int i=0; i<g.size(); i++)
			{
				//if(g[v][i])
				if(g[v][i] && !marc[i])
				{
					if(i==v2)
						return true;
					pila.push( i );
				}
			}
		}
	}
	return false;
}
//Devuelve la cantidad de antecesores que tiene cada vertice de un grafo aciclico
void nivelTopologico(const graph &g, int v, vector<int>& array, int m=0)
{
	array[v]=m;
	for(int i=0;i<g.size(); i++)
	{
		if(array[i]<=m)
		{
			if( g[v][i] )
				nivelTopologico(g, i, array, m+1);
		}
	}
}
//
vector<int> nivelTopologico(const graph &g)
{
	vector<int> array(g.size(), -1);
	for(int i=0; i<g.size(); i++)
		if(array[i]<0)
			nivelTopologico(g,i,array);
	return array;
}
