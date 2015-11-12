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

//ifstream in("contest-d.txt");
//#define cin in
      
int main()
{
    int month, ciclo;
    while (cin>>month && month != 0)
    {
		vector<vector<bool> > M(month, vector<bool> ( 1000,false));
		vector<int> days(month);
		int maxDay=0;
		for (int d=0; d<month; d++)
		{
			cin>>days[d];
			maxDay=max(maxDay,days[d]);
		}
		
		char ch;
		int dia,mes,ano;
		cin>>ciclo;
		cin>>dia>>ch>>mes>>ch>>ano;
		
		dia--, mes--;
		
		//simular
		bool ok=false;
		if (maxDay > ciclo)
		{
			while (true)
			{
				dia+=ciclo;
				if (dia<days[mes])
				{
					ok=true;
					cout<<"The next Blue Moon Festival will be held on "<<(dia+1)<<"/"<<(mes+1)<<"/"<<ano<<"."<<endl;
					break;
				}
				else
				{
					while (dia>=days[mes])
					{
						dia=dia-days[mes];
						mes++;
						if (mes>=month)
						{
							mes=0;
							ano++;
						}
					}
					
					if (M[mes][dia])
						break;
					M[mes][dia]=true;	
				}
			}
		}
		if (!ok)
			cout<<"There can never be a Blue Moon Festival."<<endl;
	}
    //system("PAUSE");
    return 0;    
}
