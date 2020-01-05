#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int max(int a, int b)  
{  
    return (a > b)? a : b;  
}
int max(int x, int y, int z)
{ 
    return max(max(x, y), z);
}
int min(int a, int b)  
{  
    return (a < b)? a : b;  
}
int min(int x, int y, int z)
{ 
    return min(min(x, y), z);
}

pair<int,string> LCS(string& X , string& Y, bool rtn){
	int m = X.size();
	int n = Y.size();
	int L[m+1][n+1];
   	for (int i=0; i<=m; i++){
   	    for (int j=0; j<=n; j++){
       		if (i == 0 || j == 0){
         		L[i][j] = 0;
       		}
       		else if (X[i-1] == Y[j-1]){
         		L[i][j] = L[i-1][j-1] + 1;
       		}
       		else{
         		L[i][j] = max(L[i-1][j], L[i][j-1]);
       		}
     	}
   	}
   	int index = L[m][n];
   	string lcs(index + 1,' ');
   	if (!rtn){
   		return make_pair(index,lcs);
   	}
   	else{
   		int i = m, j = n; 
   		while (i > 0 && j > 0){
      		if (X[i-1] == Y[j-1]) { 
          		lcs[index-1] = X[i-1];
          		i--; j--; index--;
      		}
      		else if (L[i-1][j] > L[i][j-1]){
         		i--; 
      		}
      		else{
         		j--; 
      		}
   		} 
   	}
   	return make_pair(index,lcs);
}

template <typename T>
int BSceilind(std::vector<T>& v, std::vector<T>& t, int l, int r, T key)
{
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (v[t[m]] >= key){
            r = m;
        }
        else{
            l = m;
        }
    }
    return r;
}

template <typename T>
pair<int,vector<T>> LIS(vector<T> &v,bool rtn){
	vector<int> Tailind(v.size(), 0);
	vector<int> Prevind(v.size(), -1);
    int length = 1;
    int pos;
    for (size_t i = 1; i < v.size(); i++) {
        if (v[i] < v[Tailind[0]]){
            Tailind[0] = i;
        }
        else if (v[i] > v[Tailind[length - 1]]){
            Prevind[i] = Tailind[length - 1];
            Tailind[length++] = i;
        }
        else{
            pos = BSceilind<T>(v ,Tailind, -1, length - 1, v[i]);
			Prevind[i] = Tailind[pos - 1]; 
            Tailind[pos] = i; 
        }
    }
    vector<T> ret(length);
    if (rtn){
    	int l = 0;
    	for (int i = Tailind[length - 1]; i >= 0; i = Prevind[i]){
    		ret[l] = v[i];
    		l++;
    	}
    	reverse(ret.begin(),ret.end());
	}
	return make_pair(length,ret);
}