#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
const int MAX = 1e5+5;
using namespace std;

int n, m; 
vector<int> a;

struct segment{
	int size;
	vector<int> values;

	void init(int n){
		size = 1;
		while(size < n) size*=2;
		values.assign(2*size, 0LL);
	}

	void build(vector<int> &a, int x, int lx, int rx){
		if(rx - lx == 1){
			if(lx < (int)a.size()){
				values[x] = a[lx];
			}
			return;
		}
		int m = lx + (rx-lx)/2;
		build(a, 2*x + 1, lx, m);
		build(a, 2*x + 2, m, rx);
		values[x] = min(values[2*x+1], values[2*x+2]);
	}

	void build(vector<int> &a){
		build(a, 0, 0, size);
	}

	// void set(int i, int v, int x, int lx, int rx){
	// 	if(rx - lx == 1){
	// 		sums[x] = v;
	// 		return;
	// 	}
	// 	int m = (rx-lx)/2 + lx;
	// 	if(i < m) set(i, v, 2*x+1, lx, m);
	// 	else set(i, v, 2*x+2, m, rx);
	// 	sums[x] = sums[2*x + 1] + sums[2*x + 2];
	// }

	// void set(int i, int v){
	// 	set(i, v, 0, 0, size);
	// }

	int min_segment(int l, int r, int x, int lx, int rx){
		if(rx <= l || r <= lx) return INT_MAX;
		if(l <= lx && rx <= r) return values[x];
		int m = (rx - lx)/2 + lx;
		int v1 = min_segment(l, r, 2*x+1, lx, m);
		int v2 = min_segment(l, r, 2*x+2, m, rx);
		return min(v1, v2);
	}

	int min_segment(int l, int r){
		return min_segment(l, r, 0, 0, size);
	}
};

int main(){
	freopen("input.txt", "r", stdin);
	freopen("a.txt", "w", stdout);
	cin >> n >> m;
	a.resize(n);
	segment st;
	st.init(n);

	for(int i = 0; i < n; i++) {
		cin >> a[i];
	}

	st.build(a);

	int l, r;
	for(int i = 0; i< m; i++){
		cin >> l >> r;
		cout << st.min_segment(l,r) << endl;
	}

}
