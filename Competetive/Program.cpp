// Time.cpp : Measures Execution time for your program

//Includes
#include <iostream>
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <string>
#include <vector>
//Namespaces
using namespace std;
using namespace std;
using namespace chrono;
//Globals
vector<system_clock::time_point> Timings;

void Program()
{
	//Code
	for (int i = 0; i < 1e9; ++i)
	{
		i++;
	}
}

double time(system_clock::time_point start, system_clock::time_point stop) {
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
	cout << endl;
	cout << "Timings" << endl;
	for (int i = 1; i < Timings.size(); i++) {
		cout << time(Timings[0], Timings[i]) << endl;
	}
	cout << "Enter Any Charecter To Exit : ";
	char _;
	cin >> _;
	return 0;
}

