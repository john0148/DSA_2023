#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define pb push_back

int main() {
	int N, M;
	cin >> N >> M;
	vi dist(N + 1, INT_MAX), parent(N + 1);
	vector<vi> adj(N + 1);
	while (M--) {
		int a, b;
		cin >> a >> b;
		adj[a].pb(b), adj[b].pb(a);
	}
	queue<int> q;
	dist[1] = 0;
	q.push(1);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int t : adj[x])
			if (dist[t] == INT_MAX) {
				dist[t] = dist[x] + 1;
				parent[t] = x;
				q.push(t);
			}
	}
	if (dist[N] == INT_MAX) cout << "IMPOSSIBLE";
	else {
		cout << dist[N] + 1 << "\n";
		vi v{N};
		while (v.back() != 1) v.pb(parent[v.back()]);
		reverse(begin(v), end(v));
		for (int t : v) cout << t << " ";
	}
}