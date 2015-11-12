/* @JUDGE_ID:  000000  100  C++  "Easy algorithm hehe" */
    
/**************
 solution to problem 1
 by: Jose Castillo
 date: 25/02/10

**************/
#include <iostream>
#include <vector>
using namespace std;

vector<unsigned int> arr;

unsigned int cycle( unsigned int num  )
{
    if( (num < arr.size()) && (arr[num]!=0) )
        return arr[num]; 
    
    else{        
        if( num == 1 ) {
            arr[num] = num;
            return 1;
        }
        int aux;
        if( num%2 == 0 ) aux = cycle(num/2)+1;
        else aux = cycle(num*3+1)+1;
        
        if(num < arr.size())
            arr[num] = aux;        
        return aux;
    }
};

int main(){
    
    
    unsigned int i,j,result,major,minor;
    arr.resize(1000000,0);
    for( unsigned int y = 1 ; y < arr.size() ; y++){
         cycle(y);
    }  
    while ( cin >> i >>  j ){
          result = 1;
          if ( i < j ){
             minor = i;
             major = j;
          }
          else{
             minor = j;
             major = i;
          }          
          while( minor <= major ){
               if( arr[minor] >result) result = arr[minor];         
               minor++;
          }              
          cout << i << " " << j << " " << result << endl; 
    }    
    return 0;  
    
}
