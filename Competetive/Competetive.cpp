// Competetive.cpp : Your Program Goes in the Program() function
//

#include <iostream>
#include <stdio.h>
#include <chrono>
using namespace std;
using namespace chrono;

void Program()
{
	// Your Code Here
}

int main()
{
	auto start = high_resolution_clock::now();
	Program();
	auto stop = high_resolution_clock::now();
	auto ds  = duration_cast<seconds>(stop - start);
	auto dn = duration_cast<nanoseconds>(stop - start);
	cout << endl << "Execution Time in seconds = " << ds.count() << "." << dn.count() % int(1e+9) << endl;
	return 0;
}

