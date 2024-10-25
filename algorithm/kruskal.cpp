#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct DSU {
	vector<int> e;

	DSU(int N) : e(N, -1) {}

	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }

	bool connected(int a, int b) { return get(a) == get(b); }

	int size(int x) { return -e[get(x)]; }

	bool unite(int x, int y) {
		x = get(x), y = get(y);
		if (x == y) { return false; }
		if (e[x] > e[y]) { swap(x, y); }
		e[x] += e[y];
		e[y] = x;
		return true;
	}
};

template <class T> T kruskal(int N, vector<pair<T, pair<int, int>>> edges) {
	sort(edges.begin(), edges.end());
	T ans = 0;
	DSU D(N + 1);  // edges that unite are in MST
	for (pair<T, pair<int, int>> &e : edges) {
		if (D.unite(e.second.first, e.second.second)) { ans += e.first; }
	}
	// -1 if the graph is not connected, otherwise the sum of the edge lengths
	return (D.size(1) == N ? ans : -1);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<pair<long long, pair<int, int>>> edges;
	for (int i = 0; i < m; i++) {
		int a, b;
		long long c;
		cin >> a >> b >> c;
		edges.push_back({c, {a, b}});
	}

	long long ans = kruskal(n, edges);
	if (ans >= 0) {
		cout << ans;
	} else {
		cout << "IMPOSSIBLE";
	}
}


/*

#include <algorithm>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>

using namespace std;

struct DSU {
    unordered_map<string, string> parent;
    unordered_map<string, int> rank;

    string find(const string& s) {
        if (parent.find(s) == parent.end()) {
            parent[s] = s;
            rank[s] = 0;
        }
        if (s != parent[s]) {
            parent[s] = find(parent[s]);
        }
        return parent[s];
    }

    bool unite(string a, string b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;

        if (rank[a] < rank[b]) swap(a, b);
        if (rank[a] == rank[b]) rank[a]++;
        parent[b] = a;
        return true;
    }
};

template <class T> T kruskal(const unordered_map<string, vector<pair<string, T>>>& adj_list) {
    vector<pair<T, pair<string, string>>> edges;
    for (const auto& adj : adj_list) {
        for (const auto& edge : adj.second) {
            edges.push_back({edge.second, {adj.first, edge.first}});
        }
    }

    // Remove duplicate edges
    sort(edges.begin(), edges.end());
    edges.erase(unique(edges.begin(), edges.end()), edges.end());

    T ans = 0;
    DSU D;

    sort(edges.begin(), edges.end());
    for (const auto& e : edges) {
        if (D.unite(e.second.first, e.second.second)) {
            ans += e.first;
        }
    }
    
    // Check if all vertices are connected
    string root = D.find(edges.begin()->second.first);
    for (const auto& adj : adj_list) {
        if (D.find(adj.first) != root) {
            return -1; // The graph is not connected
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    unordered_map<string, vector<pair<string, int>>> adj_list;

    for (int i = 0; i < m; i++) {
        string a, b;
        int c;
        cin >> a >> b >> c;
        adj_list[a].push_back({b, c});
        adj_list[b].push_back({a, c}); // For undirected graph
    }

    int ans = kruskal(adj_list);
    if (ans >= 0) {
        cout << ans;
    } else {
        cout << "IMPOSSIBLE";
    }
}


*/