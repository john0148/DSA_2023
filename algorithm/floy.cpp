#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> adj, ans;
vector<vector<int>> radj;

void fill_radj(int x) {
	for (auto &child : radj[x]) {
		/*
		 * As all nodes in the cycle are processed in function floyd,
		 * the recursive call will only start at the nodes which
		 * combine the cycle with the acyclic part of the connected component
		 * where one of its outgoing arrows points to the node that is not
		 * processed yet.
		 */
		if (ans[child] == -1) {
			ans[child] = ans[x];
			fill_radj(child);
		}
	}
}

void floyd(int x) {
	int y = x;
	do {  // find a cycle using Floyd's algorithm
		x = adj[x];
		y = adj[adj[y]];
	} while (y != x);
	do {  // set ans[x] = x for all x along cycle
		ans[x] = x;
		x = adj[x];
	} while (y != x);
	do {  // set ans'es for all x not along cycle
		fill_radj(x);
		x = adj[x];
	} while (y != x);
}

int main() {
	cin >> n;

	adj.assign(n, -1);
	for (auto &e : adj) {
		cin >> e;
		e--;
	}

	/*
	 * For each node, we have to use a vector to store its children;
	 * at nodes combining the cycle with other parts of the connected component,
	 * there would be more than one outgoing arrow in the reversed adjacency
	 * list
	 */
	radj.assign(n, {});
	for (int i = 0; i < n; i++) radj[adj[i]].push_back(i);

	ans.assign(n, -1);
	// we run Floyd's algorithm for each connected component
	for (int i = 0; i < n; i++)
		if (ans[i] == -1) floyd(i);

	for (auto &a : ans) cout << a + 1 << " ";
}