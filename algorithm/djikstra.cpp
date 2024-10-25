#include <iostream>
#include <queue>
#include <vector>
#include <climits>
const int MAX = 2e5 + 5;
using namespace std;

vector<pair<int, int>> adj[MAX];
int dist[MAX];
bool process[MAX];

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	priority_queue<pair<int, int>> q;
	int n, m; cin >> n >> m;

	int a, b, w;
	for(int i = 0; i < m; i++){
		cin >> a >> b >> w;
		adj[a].push_back({w, b});
		adj[b].push_back({w, a});
	}

	for(int i = 1; i <= n; i++) dist[i] = INT_MAX;
	q.push({0, 1});
	dist[1] = 0;

	while(!q.empty()){
		int node = q.top().second; q.pop();
		if(process[node]) continue;
		process[node] = true;
		for(auto child : adj[node]){
			int b = child.second, w = child.first;
			if(dist[b] > dist[node] + w){
				dist[b] = dist[node] + w;
				q.push({-dist[b], b});
			}
		}
	}

	for(int i = 1; i <= n; i++) cout << i << " : " << dist[i] << endl;


}

//code dijkstra cho unordered_map<int, vector<pair<int, int>>> 


/*
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>
using namespace std;

struct Node {
    int vertex, weight;
    Node(int v, int w) : vertex(v), weight(w) {}

    bool operator<(const Node& other) const {
        return weight > other.weight;
    }
};

void dijkstra(unordered_map<int, vector<pair<int, int>>>& graph, int start) {
    unordered_map<int, int> distances;
    priority_queue<Node> pq;

    // Khởi tạo khoảng cách cho tất cả các đỉnh
    for (const auto& pair : graph) {
        distances[pair.first] = INT_MAX;
    }

    distances[start] = 0;
    pq.push(Node(start, 0));

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int vertex = current.vertex;
        int weight = current.weight;

        if (distances[vertex] < weight) continue;

        for (const auto& neighbor : graph[vertex]) {
            int next_vertex = neighbor.first;
            int next_weight = weight + neighbor.second;

            if (next_weight < distances[next_vertex]) {
                distances[next_vertex] = next_weight;
                pq.push(Node(next_vertex, next_weight));
            }
        }
    }

    for (const auto& pair : distances) {
        if (pair.second == INT_MAX) {
            cout << "Khong the den duoc dinh " << pair.first << endl;
        } else {
            cout << "Khoang cach den dinh " << pair.first << " la: " << pair.second << endl;
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    unordered_map<int, vector<pair<int, int>>> graph;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        // Neu do thi khong huong, bo dong comment duoi day
        // graph[v].push_back({u, w});
    }

    dijkstra(graph, start, n);

    return 0;
}


*/