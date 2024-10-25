#include<iostream>
#include<vector>
#include<algorithm>


using namespace std;

void solve(){
	int n; cin >> n;
	vector<int> v(n,0);

	for(int i = 0; i < n-1; i++) cin >> v[i];

	for(int i = n-2; i > 0; i--) v[i] -= v[i-1];
	sort(v.begin(), v.begin() + n-1);


	int i = 0, j = 1, s = 0;
	while(i < n && j <= n){
		if(v[i] < j) i++;
		else if(v[i] > j) j++;
		else{
			v[i] = 0;
			s += j;
			i++; j++;
		}
	}

	int cnt = 0, index;
	for(int i = 0; i < n; i++){
		if(v[i]){
			cnt++;
			index = i;
		}
	}

	cout << s << endl;

	if((cnt == 1 && s + v[index] == n*(n+1)/2) || (cnt == 0 && s + n == n*(n+1)/2)){
		cout << "YES\n";
		return;
	}
	
	cout << "NO\n";
}


int main(){
	freopen("input.txt", "r", stdin);
	freopen("a.txt", "w", stdout);
	int t; cin >> t;
	for(int i = 0; i < t; i++){
		solve();
	}
}