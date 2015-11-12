#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <string>
#include <iostream>
using namespace std;

ostream& operator<<(ostream& out, const vector<int>& n)
{
	for(int i=0; i<n.size(); i++)
	{
		out<<n[i];
	}
	return out;
}

void permutation(vector<int> &o, vector<int> &aux)
{
	int n=o.size();
	if(n==0)
	{
		//Algo
                cout<<aux<<endl;
		return;
	}
	int i=0;
	for(int i=0; i<n; i++)
	{
		int p=o[i];o.erase(o.begin()+i);
		aux.push_back(p);
                
		permutation(o, aux);
                
		o.insert(o.begin()+i, p);
		aux.pop_back();
	}
}

int main()
{
    vector<int> o;
    for(int i=0; i<3; i++)
    {
      o.push_back(i);
    }
    
    vector<int> aux;
    permutation(o, aux);
  	
  	system("pause");
  	return 0;
}
