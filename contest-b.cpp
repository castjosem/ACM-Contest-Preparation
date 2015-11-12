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
#include <set>
#include <algorithm>
using namespace std;

//ifstream in("contest-b.txt");
//#define cin in
struct player
{
	string firstname;
	string lastname;
	int db;
	int mb;
	int yb;
	int r;
	int age;
};

vector<player> players;

int mesToInt(string str)
{
	if (str[0]=='j' && str[1]=='a' && str[2]=='n')
		return 1;
	if (str[0]=='f' && str[1]=='e' && str[2]=='b')
		return 2;
	if (str[0]=='m' && str[1]=='a' && str[2]=='r')
		return 3;
	if (str[0]=='a' && str[1]=='p' && str[2]=='r')
		return 4;
	if (str[0]=='m' && str[1]=='a' && str[2]=='y')
		return 5;
	if (str[0]=='j' && str[1]=='u' && str[2]=='n')
		return 6;
	if (str[0]=='j' && str[1]=='u' && str[2]=='l')
		return 7;
	if (str[0]=='a' && str[1]=='u' && str[2]=='g')
		return 8;
	if (str[0]=='s' && str[1]=='e' && str[2]=='p')
		return 9;
	if (str[0]=='o' && str[1]=='c' && str[2]=='t')
		return 10;
	if (str[0]=='n' && str[1]=='o' && str[2]=='v')
		return 11;
	if (str[0]=='d' && str[1]=='e' && str[2]=='c')
		return 12;
}

bool comparar(int i, int j)
{
	if (players[i].lastname<players[j].lastname ||
		(players[i].lastname==players[j].lastname && players[i].firstname<players[j].firstname))
			return true;
	return false;
}

int main()
{
    int n;
    int m;
    int dc, mc, yc;
    cin>>n;
    for(int caso=1;caso<=n;caso++)
    {
		string mes,mesCompetencia,basura;
		
		cin>>dc>>mesCompetencia>>yc;
		mc=mesToInt(mesCompetencia);
		
		cin>>m; 
		players.clear();
	
		for(int i=0;i<m;i++)
		{
			string pl;
			player aux;
			cin>>aux.lastname>>aux.firstname>>basura>>
				aux.db>>mes>>aux.yb>>basura>>
				aux.r;
			aux.mb=mesToInt(mes);
			players.push_back(aux);
		}

		set<int> edades;
		for(int i=0;i<players.size();i++)
		{
			if(players[i].mb < mc)
				players[i].age=(yc-players[i].yb)+1;
			else if(players[i].mb == mc)
			{
				if(players[i].db <= dc)
					players[i].age=(yc-players[i].yb)+1;
				else
					players[i].age=(yc-players[i].yb);
			}
			else
				players[i].age=(yc-players[i].yb);
			edades.insert(players[i].age);
		}
		
		cout<<"Contest "<<caso<<": "<<dc<<" "<<mesCompetencia<<" "<<yc<<endl;
		cout<<"All participants are winners with"<<endl;
		set<int>::iterator it;
		for(it=edades.begin(); it!=edades.end(); it++)
		{
			int edad=(*it);
			int maxRating=0;
			vector<int> ganadores;
			for(int i=0;i<players.size();i++)
			{
				if (players[i].age == edad)
				{
					if (players[i].r > maxRating)
					{
						maxRating = players[i].r;
						ganadores.clear();
						ganadores.push_back(i);
					}
					else if (players[i].r == maxRating)
					{
						ganadores.push_back(i);
					}
				}
			}
			
			sort(ganadores.begin(), ganadores.end(), comparar);
			
			cout<<players[ganadores[0]].lastname<<" "<<players[ganadores[0]].firstname<<" is best under "<<edad<<endl;
			for (int i=1; i<ganadores.size(); i++)
			{
				cout<<"and also "<<players[ganadores[i]].lastname<<" "<<players[ganadores[i]].firstname<<endl;
			}
		}
	}
	//system("PAUSE");
    return 0;    
}
