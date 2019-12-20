// Time.cpp : Measures Execution time for your program
//
// Includes
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <string>
// Namespaces
using namespace std;
using namespace chrono;

void Program()
{
	// Code
}

double time(steady_clock::time_point start, steady_clock::time_point stop) {
	auto ds = duration_cast<seconds>(stop - start);
	auto dn = duration_cast<nanoseconds>(stop - start);
	double ns = double(double(dn.count() % int(1e9)) / double(1e9));
	return (double(ds.count()) + ns);
}

int main()
{
	auto start = high_resolution_clock::now();
	Program();
	auto stop = high_resolution_clock::now();
	cout << time(start, stop) << endl << "Enter Any Charecter To Exit : ";
	char _;
	cin >> _;
	return 0;
}

