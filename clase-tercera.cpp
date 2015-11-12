#include <iostream>
using namespace std;


//Memoization
//In the algorithm implementation process, the calculated values, stored
//in memory inside. Next time if they need the same values, do not have
//to recalculate it again, just use the memory inside the information on it.

//Example: Find all the integers from 1 to n cube, and, n range from 1 to 10 ( 1 <= n <= 10 )

//A direct way, accumulation of each cube. (This can also have the formula solution, 
//but in order to facilitate the example, it does not use the formula here.)

int sum_of_cubes(int n)
{
	int v = 0;
	for (int i=1; i<=n; i++) 
		v += i * i * i;
	return v;
}

int memo[10 + 1];   //The value 0 is set to not have the answer into

int sum_of_cubes(int n)
{
	//If you already have calculated that the answer to return
	if (memo[n] != 0) return memo[n];

	//If not counted for the calculation again, and stored
	int v = 0;
	for (int i=1; i<=n; i++) 
		v += i * i * i;
	return memo[n] = v;
}
 
int main()
{
	int n;
	while (cin >> n) 
		cout << sum_of_cubes(n);
	return 0;
}





//Pre-Calculation
//In the beginning of the algorithm will be first used to calculate the value 
//stored in memory inside, so you do not have the algorithm implementation 
//process, take the time to repeatedly calculate these values. Such as pi, 
//the length of the string, the number of common quality.


int table[10 + 1];  // Create cube form to facilitate the calculation
  
void build_table()
{
	for (int i=1; i<=10; ++i)
		table[i] = i * i * i;
}

int sum_of_cubes(int n)
{
	// cube has been calculated, will not have to re-calculate the number of cubic
	int v = 0;
	for (int i=1; i<=n; ++i) 
		v += table[i];
	return v;
}

int main()
{
	build_table();
	int n;
	while (cin >> n) 
		cout << sum_of_cubes(n);
	return 0;
}


//***************************** Continua Pre-Calculo
// After the first operator to write a good answer to death inside the program
int table[10 + 1] = {0, 1, 8, 27, 64, 125, 216, 343, 512, 729, 1000};

int main()
{
	int n;
	//Printed directly on the answer form to
	while (cin >> n) 
		cout << table[n];
	return 0;
}


// Ejercicios
// UVa 
// 141 
// 10260
// 10082
// 10222
// 10738
// 417
// 10894
// 759
// 105
// 10415







//Simulation
//Simulation is the "simulation. " Write a program to simulate a behavior.
//Simulation is often a problem, will elaborate on the definition of the function 
//of the program and effect, and provides a fixed set of operating procedures, the 
//program must have a suit, do the action. Programmers do not need the additional
//design complexity of the algorithm, only according to the description of topics 
//to construct an appropriate data structure to store information, write code that 
//acts similar to it.

//Simulation programming primarily to test the skill to write code, rather than 
//test the program designer's wittiness and creativity. Simulation can be said that 
//the basic ? ? programming made it clear the problem, not the design of complex 
//algorithms, as long as done according to regulations like. Such questions were 
//very suitable for programming beginners.

//Simulation of the problems sometimes very tough. If the provisions of the 
//intricacies of the problem, then write the code since it is very tiring. If 
//accidentally made a mistake, only looked at the long-winded, chaotic code to 
//find out where the error is quite painful.

//In addition, there are some questions not yet resolved the classic, 
//because there is no good algorithm, so we encountered this problem, we 
//can obediently do according to the requirements of title. This type of 
//subject will become the subject of Simulation.



