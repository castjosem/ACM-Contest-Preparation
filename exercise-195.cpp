//WRONG ANSWER
//Anagramas
//permutaciones
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	int nnn;
	cin>>nnn;
	for(int cn=0; cn<nnn; cn++)
	{
		string s;
		cin>>s;
		vector<char> v;
		for(int i=0; i<s.length(); i++)
			v.push_back(s[i]);
		sort(v.begin(), v.end());

		do
		{
			for(int i=0; i<s.length(); i++)
				cout<<v[i];
			cout<<endl;
		}while(next_permutation(v.begin(), v.end()));
	}

	return EXIT_SUCCESS;
}
