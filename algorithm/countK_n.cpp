#include <iostream>
#include <vector>
using namespace std;

// Hàm kiểm tra xem có thể tạo thành K_n từ tập đỉnh cho trước hay không
bool isKn(const vector<int>& vertices, const vector<vector<bool>>& graph) {
    for (int i = 0; i < (int)vertices.size(); i++) {
        for (int j = i + 1; j < (int)vertices.size(); j++) {
            if (!graph[vertices[i]][vertices[j]]) {
                return false;
            }
        }
    }
    return true;
}

// Hàm tạo tất cả các tổ hợp của n đỉnh từ đồ thị để kiểm tra
void combinationUtil(int n, int k, vector<int>& temp, int start,
                     const vector<vector<bool>>& graph, int& found) {
    if ((int)temp.size() == k) {
        if (isKn(temp, graph)) {
            found++;
        }
        return;
    }

    for (int i = start; i < n; i++) {
        temp.push_back(i);
        combinationUtil(n, k, temp, i + 1, graph, found);
        temp.pop_back();
    }
}

// Hàm chính để kiểm tra K_n trong G
int checkKnInGraph(int n, int k, const vector<vector<bool>>& graph) {
    vector<int> temp;
    int found = 0;
    combinationUtil(n, k, temp, 0, graph, found);
    return found;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m; // n là số đỉnh, m là số cạnh của G
    cin >> n >> m;

    vector<vector<bool>> graph(n, vector<bool>(n, false));
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u --, v--;
        graph[u][v] = graph[v][u] = true;
    }

    int k = 4; // Số đỉnh của K_n cần kiểm tra

    cout << checkKnInGraph(n, k, graph) << endl;

    return 0;
}
