#include <iostream>
#include <sstream>
#include <ctype.h>
using namespace std;

int main()
{
    string str;
    while( getline(cin,str) && str[0]!='*')
    {
           bool ok = true;
           char aux = tolower(str[0]);
           istringstream iss(str);
           string word;
           while(iss >> word)
           {                     
                     if(aux!=tolower(word[0]))
                                     ok = false;       
           }          
           if(ok)
                 cout << 'Y' << endl;
           else
               cout << 'N' << endl;
    }    
    return 0;   
}
