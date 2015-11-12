#include <iostream>
#include <stack>
using namespace std;

int main(){    
    stack<char> pila;
    string linea, dummy;
    char aux;
    int num;
    bool ok;
    cin >> num;
    getline(cin, dummy);
    for(int j = 0 ; j<num ; j++){
         getline(cin, linea);
         ok = true; 
         while(!pila.empty())
               pila.pop();           
               
         for(int i = 0; i< linea.size() && ok==true; i++){     
               if(linea[i]=='(' || linea[i]== '[')
                    pila.push(linea[i]);
               else
               {
                  if(!pila.empty())
                  {
                      aux = pila.top();
                      pila.pop();
                      if((linea[i]==')' && aux!='(') || (linea[i]==']' && aux!='['))
                         ok = false;  
                    }
                    else ok = false;              
               }                 
         }       
         if(ok && pila.empty())
              cout << "Yes" << endl;
         else
              cout << "No" << endl;              
                            
    }  
    return 0;
}
