#include <iostream>
#include <string>
using namespace std;

float calcValor( char nota ){	
	switch(nota){		
		case 'W':
			return 1;
		case 'H':
			return (0.5);
		case 'Q':
			return (0.25);
		case 'E':
			return (0.125);
		case 'S':
			return (0.0625);
		case 'T':
			return (0.03125);
		case 'X':
			return (0.015625);
		default:
			return 0;
	}		
}


int main(){
	string str;
	int cont;
	float compas;
	bool nuevo;
	while (getline(cin,str)){
		if(str[0] != '*' && str[1] != '*'){
			cont = 0;		
			compas = 0;	
			string::iterator it;
			for ( it=str.begin() ; it < str.end(); it++ ){
				if(*it=='/'){				
					if(compas == 1.0)
						cont++;
					compas = 0;					
				}
				compas += calcValor(*it);
			}
			cout << cont << endl;
		}
		else
			break;
	}
	return 0;
}
