#include <iostream>
#include <string>
#include <algorithm>
const int MAX = 1e5;
using namespace std;


void preprocessing(int* badChar, string pat){
	for(int i = 0; i < MAX; i++) badChar[i] = -1;

	for(int i = 0; i < (int)pat.size(); i++){
		badChar[(int)pat[i]] = i;
	}
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("a.txt", "w", stdout);
	string text;
	string pat;
	cin >> text >> pat;
	int n = text.size();
	int m = pat.size();

	int badChar[MAX];

	preprocessing(badChar, pat);


	int s = 0;
	int cnt = 0;
	while(s <= n - m){
		int j = m-1;
		while(j >= 0 && text[s + j] == pat[j]) j--;

		if(j < 0){
			cnt++;
			s += (s + m < n) ? max(1, m - badChar[(int)text[s + m]]) : 1;
		}
		else{
			s += (s + m < n) ? max(1, j - badChar[(int)text[s + j]]) : 1;
		}
	}
	cout << cnt << endl;
}