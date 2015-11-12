#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#define cin in
fstream in("clase-segunda-test.txt");

int main()
{
    int n;
    string str;
    /*
    while (cin>>str)
	{
		cout << str << endl;   
	}
    
    while (getline(cin,str))
	{
		cout << str << endl;   
	}
    
    while( getline(cin,str) && str[0]!='*')
    {
           cout << str << endl;           
    }        
    */
    
    /*
    while (getline(cin, str))
	{
		// Problemas con getline, que pasa si el cursor ya esta en algun punto X de la linea
		int numero;
		string basura;
		cin>>numero;
		cout << numero << endl;
		getline(cin, basura);
		n++;
	}
	*/
	
	/*
	n=0;
	while (getline(in, str))
    {
		istringstream iss(str);
		int num;		
		int sumatoria=0;
		while (iss>>num)
		{
			sumatoria+=num;
		}
		cout<<"suma: "<<sumatoria<<endl;		
		n++;
	}
	cout<<"cantidad: "<<n<<endl;
	*/
	
	
    system("pause");
    return 0;   
}
