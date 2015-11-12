#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
	int h2,m2;
	while( scanf("%d:%d\n",&h2,&m2)>0)
//	while( scanf("%d:%d\n",&h2,&m2), h2!=0 || m2!=0)
	{
		float ah,am,a,h,m;
		h=h2;m=m2;
		//angulo de la aguja de horas
		ah=h*360/12;	//12 horas 360º
		//la aguja de horas varia segun los minutos transcurridos
		ah+=m*30/60;	//60 min 30º	60*12=30*12 -> 60min*12horas=360º
		
		//angulo de la aguja de minutos
		am=m*360/60;	//60minutos=360º
		a=ah-am;
		if(a<0)a*=-1;
		if(a>180)a=360-a;

		cout.setf(ios::fixed);
		cout<<setprecision(3)<<a<<endl;
	}
	return 0;
}