#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

void LCA(string s, int *lca){
	int n = s.size();
	int l = 0, r = 1;
	lca[0] = 0;
	while(r < n){
		if(s[l] == s[r]){
			lca[r] = l + 1;
			l++;
			r++;
		}
		else if(l == 0){
			lca[r] = 0;
		}
		else{
			l = lca[l-1];
		}
	}
}

int main(){
	string text;
	string pat;

	int n = text.size();
	int m = pat.size();

	int j = 0;
	for(int i = 0; i < n;){
		if(text[i] == )
	}
}