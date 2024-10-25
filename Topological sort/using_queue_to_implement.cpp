#include <iostream>
#include <vector>
#include <deque>
const int MAX = 1e2 + 5;
using namespace std;

bool adj[MAX][MAX];
bool visited[MAX];


int main(){

	freopen("input.txt", "r", stdin);
	freopen("a.txt", "w", stdout);

	int n; cin >> n;
	int m; cin >> m;
	int a, b;
	for(int i = 0; i < m; i++){
		cin >> a >> b;
		adj[a][b] = true;
	}

	vector<int> in_degree(n, 0);

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(adj[i][j]) in_degree[j]++;
		}
	}

	deque<int> dq;

	for(int i = 0; i  < n; i ++){
		if(in_degree[i] == 0){
			dq.push_back(i);
			visited[i] = true;
		}
	}

	vector<int> T;

	while(!dq.empty()){
		int vertex = dq.front();
		dq.pop_front();
		T.push_back(vertex);
		for(int j = 0; j < n; j++){
			if(adj[vertex][j] && visited[j] == false){
				in_degree[j]--;
				if(in_degree[j] == 0){
					dq.push_back(j);
					visited[j] = true;
				}
			}
		}
	}

	for(int i = 0; i < (int)T.size(); i++){
		cout << T[i] << " ";
	}
	cout << endl;

}