#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <conio.h>
using namespace std;

int main(){
  string parrafo;
  int aux;
  int arreglo[26];
  bool ok;
  int j;
  
  ifstream in("exercise-1.txt");
  
  while( getline (in,parrafo), parrafo[0]!='*' ){
    for( j = 0 ; j < 26 ; j++ ){
      arreglo[j] = 0;           
    }
    ok = false;
    for( int i = 0 ; i < parrafo.size() ; i++ ){
      aux = parrafo[i]-'a';
      if(aux >=0 && aux<26){
        arreglo[aux] = 1;
      }
    }
    for( j = 0 ; j < 26 ; j++ ){
      if( arreglo[j] != 1 ){
        break;
      }      
    }
    if( j == 26 ) ok = true;      
    if(ok)  cout << "Y" << endl;
    else cout << "N" << endl;    
  }
  getch();
  return 0; 
}
