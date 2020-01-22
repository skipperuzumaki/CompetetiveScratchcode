#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <exception>

using namespace std;

void FastIO()
{
	ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
}

int scanint()
{
    int number;
    bool negative = false;
    register int c;
    number = 0;
    c = getchar();
    if (c=='-')
    {
        negative = true;
        c = getchar();
    }
    for (; (c>47 && c<58); c = getchar()) {
        number = number *10 + c - 48;
    }
    if (negative) {
        number *= -1;
    }
    return number;
}

template <typename T>
vector<T> scanvec(T (*f)(T)){
	int n;
	T k;
	cin >> n;
	std::vector<T> v(n);
	for (int i = 0; i < n ; i++) {
		cin >> k;
		k = (*f)(k);
		v[i] = k;
	}
	return v;
}

template <typename T>
vector<T> scanvec(){
	int n;
	T k;
	cin >> n;
	std::vector<T> v(n);
	for (int i = 0; i < n ; i++) {
		cin >> k;
		v[i] = k;
	}
	return v;
}

