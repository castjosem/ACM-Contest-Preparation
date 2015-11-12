#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <stdlib.h>
#include <math.h>
using namespace std;



dec       setf(ios_base::dec, ios_base::basefield)
hex       setf(ios_base::hex, ios_base::basefield)
oct       setf(ios_base::oct, ios_base::basefield)
fixed       setf(ios_base::fixed, ios_base::floatfield)
scientific       setf(ios_base::scientific, ios_base::floatfield)
setfill(char_type c)       fill(c)
setprecision(int n)       precision(n)
setw(int n)       width(n)

Manipulator	Description	Input	Output
resetiosflags( long f )	Turn off the flags specified by f	X 	X 
setbase( int base )	Sets the number base to base		X 
setfill( char ch )	Sets the fill character to ch		X 
setiosflags( long f )	Turn on the flags specified by f	X 	X 
setprecision( int p )	Sets the number of digits of precision		X 
setw( int w )	Sets the field width to w		X 


#include <cctype>
int isalnum( int ch );
int isalpha( int ch );
int iscntrl( int ch );
int isdigit( int ch );
int isgraph( int ch );
int islower( int ch );
int isprint( int ch );
int ispunct( int ch );
int isspace( int ch );
int isupper( int ch );
int isxdigit( int ch );
int tolower( int ch );
int toupper( int ch );





// Dijkstra
distancia[u]=0;
while(u!=-1)
{
	visitados[u]=true;
	for (int v=0; v<N; v++)
		if (M[u][v] && !visitados[v])
			if (distancia[v] > distancia[u]+M[u][v])
			{
				distancia[v] = distancia[u]+M[u][v];
				pred[v]=u;
			}

	distMin=INT_MAX;
	u=-1;
	for (int i=0; i<N; i++)
		if (!visitados[i] && distancia[i] < distMin)
		{
			distMin = distancia[i];
			u = i;
		}
}











// Floyd-Warshall
pred[i][j]=i;
	
for(int i=0 ; i<N ; i++)
{
	pred[i][i] = -1;
}
	
for(int k=0 ; k<N ; k++)
	for(int i=0 ; i<N ; i++)
		if (dist[i][k]!=INT_MAX)
			for(int j=0 ; j<N ; j++)
				if (dist[k][j]!=INT_MAX)
					if (dist[i][j] > dist[i][k] + dist[k][j])
					{
						dist[i][j] = dist[i][k] + dist[k][j];
						pred[i][j] = pred[k][j];
					}
int i=origen;
int j=dest;
while(i!=j)
{
	j=pred[i][j];
}

















// Bellman-Ford

vector<int> distance(N, INT_MAX);
distance[0]=0;

int aux;
for (int i=0; i<N-1; i++)
	for (int m=0; m<M; m++)
	{
		aux=distance[E[m].u]+E[m].t;
		if (distance[E[m].v] > aux)
			distance[E[m].v] = aux;
	}

bool negative=false;
for (int m=0; m<M; m++)
	if (distance[E[m].v] > distance[E[m].u]+E[m].t)
		negative=true;




















// Articulation Point
void tarjan(int u)
{
	dfsnum[u]=low[u]=depth++;
	int child=0;
	for (int v=0; v<N; v++)
	{
		if (M[u][v])
		{
			if (dfsnum[v]==-1)
			{
				tarjan(v);
				low[u]=min(low[u], low[v]);
				if (u==0)
				{
					child++;
					if (child>=2)
						CV[u]=true;
				}
				else if (low[v] >= dfsnum[u])
					CV[u]=true;
			}
			else
				low[u]=min(low[u], dfsnum[v]);
		}
	}
}

























// Bridge ??? N/A
void tarjan(int u)
{
	dfsnum[u]=low[u]=depth++;
	int child=0;
	for (int v=0; v<N; v++)
	{
		if (M[u][v])
		{
			if (dfsnum[v]==-1)
			{
				tarjan(v);
				if (low[v] > dfsnum[u])
					// (u,v) is bridge
				low[u]=min(low[u], low[v]);
			}
			else
				low[u]=min(low[u], dfsnum[v]);
		}
	}
}
// Strongly Connected Components
void tarjan(int u)
{
	dfsnum[u]=low[u]=depth++;
	pila.push_back(u);
	for (int v=0; v<26; v++)
	{
		if (used[v])
		{
			if (M[u][v] && sccnum[v]==-1)
			{
				if (dfsnum[v]==-1)
					tarjan(v);
				low[u]=min(low[u], low[v]);
			}
		}
	}
	
	if (dfsnum[u]==low[u])
	{
		while (sccnum[u]!=scc)
		{
			sccnum[pila.back()]=scc;
			pila.pop_back();
		}
		scc++;
	}
}




















// Ford-Fulkerson
vector<int> pred;
vector<int> min_capacity;
vector< vector<int> > capacity;
vector< vector<int> > flow;

bool bfs(int source , int sink , int size)
{
	vector<bool> visit = vector<bool>(size,false);
	pred = vector<int>(size,-1);	
	min_capacity = vector<int>(size,INT_MAX);
	queue<int> queue;
	queue.push(source);
	int i,residual;
	visit[source] = true;
	while(!queue.empty())
	{
		i = queue.front();
		queue.pop();
		for(int j=0 ; j<size ; j++)
		{			
			residual = capacity[i][j]-flow[i][j];
			if(!visit[j]&& residual>0)
			{
				pred[j] = i;
				min_capacity[j] = min(min_capacity[i] , residual);
				visit[j] = true;				
				queue.push(j);
			}		
		}
	}
	if(min_capacity[sink]!=INT_MAX)
		return true;
	return false;
}

int Ford_Fulkerson(int source , int sink , int size)
{
	flow =  vector< vector<int> >(size , vector<int>(size));
	int max_flow = 0,i,j;
	while(bfs(source,sink,size))
	{
		max_flow += min_capacity[sink];
		j = sink;
		i = 0;
		while(j!=source)
		{
			i = pred[j];
			flow[i][j] += min_capacity[sink];
			flow[j][i] -= min_capacity[sink];
			j = i;			
		}		
	}
	return max_flow;	
}
//Stable Matching
function stableMatching {
    Initialize all m ∈M and w ∈W to free
    while ∃ free man m who still has a woman w to propose to {
       w = m's highest ranked such woman who he has not proposed to yet
       if w is free
         (m, w) become engaged
       else some pair (m', w) already exists
         if w prefers m to m'
           (m, w) become engaged
           m' becomes free
         else
           (m', w) remain engaged
    }
}





















//Assignment Problem

# define SIZE 5
void matching(int c[2*SIZE][2*SIZE],int n,int m[2*SIZE])
{ 
	int qsize=n+1,q[2*SIZE+1],rear,front,par[2*SIZE],level[2*SIZE],i,j,k,last;
	for(i=0;i<n;i++) m[i]=-1;
	for(k=0;k<n;k++)
	if(m[k]==-1)
	{
		last=-1;
		for(i=0;i<n;i++)
		{
			level[i]=0; par[i]=-1;
		}
		rear=front=0; level[k]=1; q[rear++]=k;
		if(rear==qsize) rear=0;
		while(rear!=front)
		{
			if(last!=-1) break;
				i=q[front++];
			if(front==qsize) front=0;
			if(level[i]%2)
			{
				for(j=0;j<n;j++)
				if(c[i][j] && level[j]==0)
				{
					level[j]=level[i]+1; par[j]=i;
					if(m[j]==-1)
					{
						last=j; break;
					}
					else
					{
						q[rear++]=j;
						if(rear==qsize) rear=0;
					}
				}
			}
			else
			{
				j=m[i]; level[j]=level[i]+1;
				par[j]=i; q[rear++]=j;
				if(rear==qsize) rear=0;
			}
		}
		while(last!=-1)
		{
			m[last]=par[last]; m[par[last]]=last; last=par[par[last]];
		}
	}
}
int isperfect(int m[],int n)
{ int i;
	for(i=0;i<n;i++)
		if(m[i]==-1) return 0;
	return 1;
}
void dfs(int k,int i,int mark[2][SIZE],int e[SIZE][SIZE],int n,int m[],int depth)
{
	int j;
	if(depth) mark[k][i]=1;
	if(k==0)
	{
		for(j=0;j<n;j++)
			if(e[i][j]==0 && m[i]!=j+n)
			{
				mark[k][i]=1;
				if(mark[1][j]==0) dfs(1,j,mark,e,n,m,depth+1);
			}
	}
	else{
		for(j=0;j<n;j++)
			if(e[j][i]==0 && m[i+n]==j)
			{
				mark[k][i]=1;
				if(mark[0][j]==0) dfs(0,j,mark,e,n,m,depth+1);
			}
	}
}
void OptimalAssignment(int w[SIZE][SIZE],int n,int m[])
{ int u[SIZE],v[SIZE],e[SIZE][SIZE],c[2*SIZE][2*SIZE];
	int mark[2][SIZE],i,j,k,eta;
	for(i=0;i<n;i++)
	{
		u[i]=v[i]=0;
		for(j=0;j<n;j++)
			if(w[i][j]>u[i]) u[i]=w[i][j];
	}
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			e[i][j]=u[i]+v[j]-w[i][j];
	for(i=0;i<2*n;i++)
		for(j=0;j<2*n;j++)
			c[i][j]=0;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(e[i][j]==0) c[i][n+j]=c[n+j][i]=1;
	matching(c,2*n,m);
	while(!isperfect(m,2*n))
	{
		for(i=0;i<n;i++)
			mark[0][i]=mark[1][i]=0;
		for(i=0;i<n;i++)
			if(m[i]==-1 && mark[0][i]==0) dfs(0,i,mark,e,n,m,0);
		eta=-1;
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				if(mark[0][i] && mark[1][j]==0)
					if(eta==-1 || eta>u[i]+v[j]-w[i][j]) eta=u[i]+v[j]-w[i][j];
		for(i=0;i<n;i++)
		{
			if(mark[0][i]) u[i]-=eta;
			if(mark[1][i]) v[i]+=eta;
		}
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				e[i][j]=u[i]+v[j]-w[i][j];
		for(i=0;i<2*n;i++)
			for(j=0;j<2*n;j++)
				c[i][j]=0;
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				if(e[i][j]==0) c[i][n+j]=c[n+j][i]=1;
		matching(c,2*n,m);
	}
}
int main(void)
{ 
	int n=5,w[SIZE][SIZE]={{4,1,6,2,3},{5,0,3,7,6},{2,3,4,5,8},{3,4,6,3,4},{4,6,5,8,6}};
	int m[2*SIZE],i,total;
	OptimalAssignment(w,n,m);
	total=0;
	for(i=0;i<n;i++)
		total+=w[i][m[i]-n];
	printf("%d\n",total);
	return 0;
}

















 
class Point {
	public:
	double x, y;
	
	Point(double x1=0, double y1=0)
	{
		x=x1;
		y=y1;
	}
	
	Point & operator=(const Point &p)
	{
		x=p.x;
		y=p.y;
	}

	Point operator+(const Point &p)
	{
		return Point(x+p.x, y+p.y);
	}
			
	Point operator-(const Point &p)
	{
		return Point(x-p.x, y-p.y);
	}
	
	Point operator*(double s)
	{
		return Point(x*s, y*s);
	}
};
typedef Point Vector;

















// Linea
// p1 y p2 no pueden ser iguales
class Line
{	
	public:
	Point p1;
	Point p2;
	
	Line(Point p3 , Point p4)
	{
		p1 = p3;
		p2 = p4;
	} 
};
typedef Line Segment;

// producto punto
double dot(Vector &v1, Vector &v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

// producto cruz // no es un vector
double cross(Vector &v1, Vector &v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}

//Distance from a Point to the Origin
double distancePoint(Point &p)
{
	return sqrt(pow(p.x, 2) + pow(p.y,2 ));
}

//Distance from a Point to a Point
double distancePointPoint(Point& p1, Point& p2)
{
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

//Distance from a Point to a Line 
double distancePointLine(Point& p, Line& l)
{
    Vector v1 = p - l.p1, v2 = l.p2 - l.p1;
    return fabs(cross(v1, v2)) / distancePoint(v2);
}

//Distance from a Point to a Segment 
double distancePointSegment(Point& p, Segment& s)
{
    Vector p1p = p - s.p1, p1p2 = s.p2 - s.p1;
    Vector p2p = p - s.p2, p2p1 = s.p1 - s.p2;
 
    double d1 = dot(p1p, p1p2), d2 = dot(p2p, p2p1);
 
    if (d1 <= 0)    
//      return distance(p, p1);
        return distancePoint(p1p);
    else if (d2 <= 0)
//      return distance(p, p2);
        return distancePoint(p2p);
    else
		return distancePointLine(p, s);
}

double distanceSegmentLine(Segment& s, Line& l)
{
    Vector v = l.p2 - l.p1;
    Vector v1 = s.p1 - l.p1, v2 = s.p2 - l.p1;
    double c1 = cross(v, v1), c2 = cross(v, v2);
 
    if (c1 > 0 && c2 > 0 || c1 < 0 && c2 < 0)
        return min( distancePointLine(s.p1, l), distancePointLine(s.p2, l));
    else
        return 0.0;
}

// solamente devuelve true si los 2 segmentos no son paralelos y se intersectan
// no se sabe si se intersectan cuando los 2 segmentos son paralelos, por lo tanto siempre devuelve false
bool intersectSegmentSegment(Segment& s1, Segment& s2)
{
    Vector v1 = s2.p1 - s1.p1, v2 = s1.p2 - s2.p1;
    Vector v3 = s2.p2 - s1.p2, v4 = s1.p1 - s2.p2;
    
    double c1 = cross(v1, v2), c2 = cross(v2, v3);
    double c3 = cross(v3, v4), c4 = cross(v4, v1);
    
    return (c1 > 0 && c2 > 0 && c3 > 0 && c4 > 0)
        || (c1 < 0 && c2 < 0 && c3 < 0 && c4 < 0);
}
 
double distanceSegmentSegment(Segment& s1, Segment& s2)
{
    if (intersectSegmentSegment(s1, s2)) 
        return 0.0;
    else   
        return  min (distancePointSegment(s1.p1, s2),
				min (distancePointSegment(s1.p2, s2),
				min (distancePointSegment(s2.p1, s1),
                     distancePointSegment(s2.p2, s1))));
}

 
double distanceLineLine(Line& l1, Line& l2)
{
    Vector v1 = l1.p2 - l1.p1, v2 = l2.p2 - l2.p1;
 
    if (cross(v1, v2) == 0)
        return distancePointLine(l1.p1, l2); 
    else
        return 0.0;
}

Point INF(1e9, 1e9);
 
Point intersectionLineLine(Line &l1, Line &l2)
{
    Vector v12 = l1.p2 - l1.p1,
	       v13 = l2.p1 - l1.p1,
		   v34 = l2.p2 - l2.p1;
    double c1 = cross(v12, v34), c2 = cross(v13, v34);
 
    if (c1 == 0)
        if (c2 == 0)
            return INF; // solapar - una encima de la otra //infinitos puntos de interseccion
        else
            return INF; // paralelo
    else
        return l1.p1 + (v12 * (c2 / c1)); // Si hay interseccion
}

Point intersectionSegmentSegment(Segment &s1,Segment &s2)
{
    Vector v12 = s1.p2 - s1.p1,
	       v13 = s2.p1 - s1.p1,
		   v34 = s2.p2 - s2.p1;
    double c1 = cross(v12, v34), c2 = cross(v13, v34);
    Vector v31 = s1.p1 - s2.p1;
    double c3 = cross(v34, v12), c4 = cross(v31, v12);
 
    if (c1 < 0) c1 = -c1, c2 = -c2; // ???????,????
    if (c3 < 0) c3 = -c3, c4 = -c4;
 
    if (c1 == 0)
        if (c2 == 0)
            return INF; // 2 lineas en parelelo // no se sabe si se intersecta o no
        else
            return INF; // paralelo y no intersecta
    else
        if (c2 >= 0 && c2 <= c1 && c4 >= 0 && c4 <= c3)
            return s1.p1 + (v12 * (c2 / c1));
        else
            return INF; // no paralelo y no intersecta
}


void polygon_area()
{
	p[N] = p[0];

	double area = 0.0;
	for (int i=0; i<N; ++i)
		area += cross(p[i], p[i+1]);

	cout << "多邊形面積為" << area/2.0;
}
bool point_in_polygon(Point& t)
{
	bool c = false;
	for (int i = 0, j = 10-1; i < 10; j = i++)
		if ((p[i].y > t.y) != (p[j].y > t.y) &&
			t.x < (p[j].x-p[i].x)*(t.y-p[i].y)/(p[j].y-p[i].y)+p[i].x)
			c = !c;
	return c;
}















//Convex Hull – Graham Scan

// P為平面上散佈的點。設定為點。
// CH為凸包上的頂點。設定為逆時針方向排列。可以視作一個stack。
struct Point {int x, y;} P[10+1], CH[10+1];

// 向量OA外積向量OB。大於零表示從OA到OB為逆時針旋轉。
int cross(Point& o, Point& a, Point& b)
{
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

// 小於。用以找出最低最左邊的點。
bool compare_position(const Point& a, const Point& b)
{
	return (a.y < b.y) || (a.y == b.y && a.x < b.x);
}

// 小於。以P[0]當中心點做角度排序，角度由小排到大（即逆時針方向）。
// 角度相同時，距離較離中心點較近的點排前面。
bool compare_angle(Point& a, Point& b)
{
	// 加入角度相同時，距離長度的判斷。
	int c = cross(P[0], a, b);
	return c > 0 ||
			c == 0 && length2(P[0], a) < length2(P[0], b);
}

void Graham_scan()
{
	// 這裡用最低最左邊的點作為起點，並將中心點換到第零點。O(N)
	swap(P[0], *min_element(P, P+10, compare_position));

	// 其餘各點依角度排序。O(NlogN)
	sort(P+1, P+10, compare_angle);

	// 直接把中心點作為起點，開始包覆，逆時針方向。O(N)
	P[N] = P[0];	// 讓程式方便處理包至最後一點的情況。

	int m = 0;		// m 為凸包頂點數目
	for (int i=0; i<=10; ++i)
	{
		while (m >= 2 && cross(CH[m-2], CH[m-1], P[i]) < 0) m--;
		CH[m++] = P[i];
	}

	m--;	// 最後一個點是重複出現的起點，故要減一。
}
 

















//Matrix Chain Multiplication (MCM)
for (k=1;k<N;k++)
{
    for (i=0;i<N-k;i++)
    {
        j=i+k;
        A[i][j]=INT_MAX;
        for (l=i;l<j;l++)
        {
            aux = (A[i][l] + A[l+1][j] + rows[i]*columns[l]*columns[j]);
            if (aux < A[i][j])
            {
                A[i][j]=aux;
                str[i][j] = "(" + str[i][l] + " x " + str[l+1][j] + ")" ;
            }
        }
    }
}









//Maximum Sum
int main()
{
	int n;
	int sub[101];
	int t,minimo;
	while(cin>>n)
	{
		vector<vector <int> > array (n, vector<int> (n , 0 ));
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				cin>>array[i][j];
		minimo=INT_MIN;
		for(int k=0;k<n;k++)
		{
			for(int i=0;i<n;i++)
				sub[i]=0;
			for(int j=k;j<n;j++)
			{
				t=0;
				for(int i=0;i<n;i++)
				{
					sub[i]+=array[j][i];
					t+=sub[i];
					if(t > minimo)
						minimo=t;
					if(t < 0)
						t=0; 
				}
			}
		}
		cout<<minimo<<endl;
	}
    //system("PAUSE");
    return 0;
}
//Counting Change
#include <stdio.h>
#define MAXTOTAL 10000
long long nway[MAXTOTAL+1];
int coin[5] = { 50,25,10,5,1 };
void main()
{
	int i,j,n,v,c;
	scanf("%d",&n);
	v = 5;
	nway[0] = 1;
	for (i=0; i<v; i++)
	{
		c = coin[i];
		for (j=c; j<=n; j++)
			nway[j] += nway[j-c];
	}
	printf("%lld\n",nway[n]);
}


//Longest Increasing Subsequence (LIS)
for i = 1 to total-1
	for j = i+1 to total
		if height[j] > height[i] then
			if length[i] + 1 > length[j] then
				length[j] = length[i] + 1
				predecessor[j] = i

//Zero-One Knapsack
for (i=0;i<=N ;i++) C[i][0] = 0;
	for (w=0;w<=MW;w++) C[0][w] = 0;
		for (i=1;i<=N;i++)
			for (w=1;w<=MW;w++)
			{
				if (Wi[i] > w)
					C[i][w] = C[i-1][w];
				else
					C[i][w] = max(C[i-1][w] , C[i-1][w-Wi[i]]+Vi[i]);
			}
output(C[N][MW]);
 













// Big Num

const int MAXD = 1005, DIG = 9, BASE = 1000000000;
const unsigned long long BOUND = numeric_limits <unsigned long long> :: max () - (unsigned long long) BASE * BASE;

struct bignum
{
    int D, digits [MAXD / DIG + 2];

    inline void trim ()
    {
        while (D > 1 && digits [D - 1] == 0)
            D--;
    }

    inline void init (long long x)
    {
        memset (digits, 0, sizeof (digits));
        D = 0;

        do
        {
            digits [D++] = x % BASE;
            x /= BASE;
        }
        while (x > 0);
    }

    inline bignum (long long x)
    {
        init (x);
    }

    inline bignum (int x = 0)
    {
        init (x);
    }

    inline bignum (char *s)
    {
        memset (digits, 0, sizeof (digits));
        int len = strlen (s), first = (len + DIG - 1) % DIG + 1;
        D = (len + DIG - 1) / DIG;

        for (int i = 0; i < first; i++)
            digits [D - 1] = digits [D - 1] * 10 + s [i] - '0';

        for (int i = first, d = D - 2; i < len; i += DIG, d--)
            for (int j = i; j < i + DIG; j++)
                digits [d] = digits [d] * 10 + s [j] - '0';

        trim ();
    }

    inline char *str ()
    {
        trim ();
        char *buf = new char [DIG * D + 1];
        int pos = 0, d = digits [D - 1];

        do
        {
            buf [pos++] = d % 10 + '0';
            d /= 10;
        }
        while (d > 0);

        reverse (buf, buf + pos);

        for (int i = D - 2; i >= 0; i--, pos += DIG)
            for (int j = DIG - 1, t = digits [i]; j >= 0; j--)
            {
                buf [pos + j] = t % 10 + '0';
                t /= 10;
            }

        buf [pos] = '\0';
        return buf;
    }

    inline bool operator < (const bignum &o) const
    {
        if (D != o.D)
            return D < o.D;

        for (int i = D - 1; i >= 0; i--)
            if (digits [i] != o.digits [i])
                return digits [i] < o.digits [i];

        return false;
    }

    inline bool operator == (const bignum &o) const
    {
        if (D != o.D)
            return false;

        for (int i = 0; i < D; i++)
            if (digits [i] != o.digits [i])
                return false;

        return true;
    }

    inline bignum operator << (int p) const
    {
        bignum temp;
        temp.D = D + p;

        for (int i = 0; i < D; i++)
            temp.digits [i + p] = digits [i];

        for (int i = 0; i < p; i++)
            temp.digits [i] = 0;

        return temp;
    }

    inline bignum operator >> (int p) const
    {
        bignum temp;
        temp.D = D - p;

        for (int i = 0; i < D - p; i++)
            temp.digits [i] = digits [i + p];

        for (int i = D - p; i < D; i++)
            temp.digits [i] = 0;

        return temp;
    }

    inline bignum range (int a, int b) const
    {
        bignum temp = 0;
        temp.D = b - a;

        for (int i = 0; i < temp.D; i++)
            temp.digits [i] = digits [i + a];

        return temp;
    }

    inline bignum operator + (const bignum &o) const
    {
        bignum sum = o;
        int carry = 0;

        for (sum.D = 0; sum.D < D || carry > 0; sum.D++)
        {
            sum.digits [sum.D] += (sum.D < D ? digits [sum.D] : 0) + carry;

            if (sum.digits [sum.D] >= BASE)
            {
                sum.digits [sum.D] -= BASE;
                carry = 1;
            }
            else
                carry = 0;
        }

        sum.D = max (sum.D, o.D);
        sum.trim ();
        return sum;
    }

    inline bignum operator - (const bignum &o) const
    {
        bignum diff = *this;

        for (int i = 0, carry = 0; i < o.D || carry > 0; i++)
        {
            diff.digits [i] -= (i < o.D ? o.digits [i] : 0) + carry;

            if (diff.digits [i] < 0)
            {
                diff.digits [i] += BASE;
                carry = 1;
            }
            else
                carry = 0;
        }

        diff.trim ();
        return diff;
    }

    inline bignum operator * (const bignum &o) const
    {
        bignum prod = 0;
        unsigned long long sum = 0, carry = 0;

        for (prod.D = 0; prod.D < D + o.D - 1 || carry > 0; prod.D++)
        {
            sum = carry % BASE;
            carry /= BASE;

            for (int j = max (prod.D - o.D + 1, 0); j <= min (D - 1, prod.D); j++)
            {
                sum += (unsigned long long) digits [j] * o.digits [prod.D - j];

                if (sum >= BOUND)
                {
                    carry += sum / BASE;
                    sum %= BASE;
                }
            }

            carry += sum / BASE;
            prod.digits [prod.D] = sum % BASE;
        }

        prod.trim ();
        return prod;
    }

    inline double double_div (const bignum &o) const
    {
        double val = 0, oval = 0;
        int num = 0, onum = 0;

        for (int i = D - 1; i >= max (D - 3, 0); i--, num++)
            val = val * BASE + digits [i];

        for (int i = o.D - 1; i >= max (o.D - 3, 0); i--, onum++)
            oval = oval * BASE + o.digits [i];

        return val / oval * (D - num > o.D - onum ? BASE : 1);
    }

    inline pair <bignum, bignum> divmod (const bignum &o) const
    {
        bignum quot = 0, rem = *this, temp;

        for (int i = D - o.D; i >= 0; i--)
        {
            temp = rem.range (i, rem.D);
            int div = (int) temp.double_div (o);
            bignum mult = o * div;

            while (div > 0 && temp < mult)
            {
                mult = mult - o;
                div--;
            }

            while (div + 1 < BASE && !(temp < mult + o))
            {
                mult = mult + o;
                div++;
            }

            rem = rem - (o * div << i);

            if (div > 0)
            {
                quot.digits [i] = div;
                quot.D = max (quot.D, i + 1);
            }
        }

        quot.trim ();
        rem.trim ();
        return make_pair (quot, rem);
    }

    inline bignum operator / (const bignum &o) const
    {
        return divmod (o).first;
    }

    inline bignum operator % (const bignum &o) const
    {
        return divmod (o).second;
    }

    inline bignum power (int exp) const
    {
        bignum p = 1, temp = *this;

        while (exp > 0)
        {
            if (exp & 1) p = p * temp;
            if (exp > 1) temp = temp * temp;
            exp >>= 1;
        }

        return p;
    }
};

inline bignum gcd (bignum a, bignum b)
{
    bignum t;

    while (!(b == 0))
    {
        t = a % b;
        a = b;
        b = t;
    }

    return a;
}


