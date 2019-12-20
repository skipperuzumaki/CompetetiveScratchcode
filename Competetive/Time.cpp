// Time.cpp : Measures Execution time for your program

//Includes
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <string>
#include <vector>
//Namespaces
using namespace std;
using namespace chrono;
//Globals
vector<steady_clock::time_point> Timings;

void Program()
{
	//Code
}

double time(steady_clock::time_point start, steady_clock::time_point stop) {
	auto ds = duration_cast<seconds>(stop - start);
	auto dn = duration_cast<nanoseconds>(stop - start);
	double ns = double(double(dn.count() % int(1e9)) / double(1e9));
	return (double(ds.count()) + ns);
}

int main()
{
	Timings.push_back(high_resolution_clock::now());
	Program();
	Timings.push_back(high_resolution_clock::now());
	for (int i = 1; i < Timings.size(); i++) {
		cout << time(Timings[0], Timings[i]) << endl;
	}
	cout << "Enter Any Charecter To Exit : ";
	char _;
	cin >> _;
	return 0;
}

