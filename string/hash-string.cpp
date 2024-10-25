#include<iostream>
#include<string>
#include<math.h>
#include<vector>
const long long BASE = 1042004;
const long long MOD = 1e9 + 7;
using namespace std;

long long pw(long long a, long long n, long long MOD){
	if(n == 0) return 1;
	long long q = pw(a, n / 2, MOD);
	if(n % 2 == 0) return q * q % MOD;
	else return q * q % MOD * a % MOD;
}

struct hashString{
	vector<long long> pref, inv;
	hashString(string s)
	{
		long long invB = pw(BASE, MOD - 2, MOD);
		int n = s.size();

		pref.resize(n + 1); pref[0] = 0;
		inv.resize(n + 1); inv[0] = 1;

		long long curpw = 1;
		for(int i = 1; i <= n; i++){
			inv[i] = inv[i - 1] * invB % MOD;
			pref[i] = (pref[i - 1] + s[i - 1] * curpw % MOD) % MOD;
			curpw = curpw * BASE % MOD;
		}
	}

	long long query(int l, int r){
		l++, r++;
		return (pref[r] - pref[l-1] + MOD) * inv[l] % MOD;
	}
};


int main(){
	freopen("input.txt", "r", stdin);
	freopen("a.txt", "w", stdout);
	string text, pat;
	cin >> text >> pat;

	hashString hashT(text);
	hashString hashP(pat);

	int n = text.size();
	int m = pat.size();

	long long hashPat = hashP.query(0, m-1);
	int res = 0;
	for(int i = 0; i < n; i++){
		if(hashT.query(i, i + m-1) == hashPat) res++;
	}

	cout << res << endl;
}