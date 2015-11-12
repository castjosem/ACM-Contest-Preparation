#include <iostream>
//#include <fstream>
#include <conio.h>
using namespace std;

int main(){
    int t,n,x,y,z;
    long long k;
    bool ok;
    ifstream in("codejam-a.txt");    
    cin >> t;  
    for( x=0 ; x<t ; x++ ){                  
         cin >> n >> k;
         
         ok = false;
         int arreglo[n+1];
         for( y=0 ; y<=n ; y++ )
              arreglo[y]=0;         
         
         for( y=1 ; y<=k ; y++ ){
              arreglo[0] = 1;              
              for( z = 1 ; z<=y ; z++ ){   
                   if( arreglo[z-1]== 1 && arreglo[z] == 0){
                          arreglo[z] = 1;  
                          arreglo[z-1] = 0;             
                   }                   
              }            
         } 
         for( y=0 ; y<n ; y++ )
              if( arreglo[y]!=1 )
                  break;
         
         if( ok )
             cout << "Case #" << x << ": ON" << endl;
         else
             cout << "Case #" << x << ": OFF" << endl;
    }    
    getch();
    return 0; 
}
