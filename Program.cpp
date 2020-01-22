// Time.cpp : Measures Execution time for your program

//Includes
#include "IO.h"
#include "Graph.h"
//Includes (Essential) add STL include Files here
#include <iostream>
#include <vector>
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

//Code

void Code() {
	FastIO();
	int t = scanint();
	if (t %2 == 0){
		cout << "YES\n";
	}
	else {
		cout << "NO\n";
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
	Code();
	Timings.push_back(high_resolution_clock::now());
	cout << endl;
	cout << "Timings" << endl;
	for (int i = 1; i < Timings.size(); i++) {
		cout << time(Timings[0], Timings[i]) << endl;
	}
	return 0;
}

