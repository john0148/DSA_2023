#include<iostream>
#include<vector>
#include<deque>
const int MAX = 1e2 + 5;

using namespace std;

int n, m;
bool visited[MAX];
bool adj[MAX][MAX];

void topological_sort(int node, vector<int> &T){
	visited[node] = true;
	for(int j = 0; j < n; j++){
		if(adj[node][j] == true && visited[j] == false){
			topological_sort(j, T);
		}
	}
	T.push_back(node);
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("a.txt", "w", stdout);
	cin >> n >> m;
	int a, b;
	for(int i = 0; i < m; i++) {
		cin >> a >> b;
		adj[a][b] = true;
	}

	vector<int> T;
	for(int i = 0; i < n; i++){
		if(!visited[i]){
			topological_sort(i, T);
		}
	}

	for(int i = 0; i < (int)T.size(); i++){
		cout << T[i] << " ";
	}
	cout << endl;

}