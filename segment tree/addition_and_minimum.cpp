#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;

struct segment{
	int size;
	vector<long long> operations;
	vector<long long> mins;

	void init(int n){
		size = 1;
		while(size < n) size*= 2;
		operations.assign(2*size, 0LL);
		mins.assign(2*size, 0LL);
	}

	void add(int l, int r, int v, int x, int lx, int rx){
		if(lx >= r || l >= rx) return;
		if(l <= lx && rx <= r){
			operations[x] += v;
			mins[x] += v;
			return;
		}

		int m = lx + (rx - lx)/2;
		add(l, r, v, 2*x + 1, lx, m);
		add(l, r, v, 2*x + 2, m, rx);
		mins[x] = min(mins[2*x+1], mins[2*x+2]) + operations[x];
	}

	void add(int l, int r, int v){
		add(l, r, v, 0, 0, size);
	}

	long long calc(int l, int r, int x, int lx, int rx){
		if(lx >= r || rx <= l) return LLONG_MAX;
		if(l <= lx && rx <= r) return mins[x];
		int m = lx + (rx - lx)/2;
		long long m1 = calc(l, r, 2*x+1, lx, m);
		long long m2 = calc(l, r, 2*x+2, m, rx);
		return min(m1, m2) + operations[x];
	}

	long long calc(int l, int r){
		return calc(l, r, 0, 0, size);
	}
};

int main(){

}