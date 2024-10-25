#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Hàm thêm cạnh vào đồ thị
void addEdge(unordered_map<int, vector<int>>& graph, int node1, int node2) {
    bool addedNode1 = true, addedNode2 = true;

    // Thêm node1 vào đồ thị nếu nó chưa tồn tại
    if (graph.find(node1) == graph.end()) {
        graph[node1] = vector<int>();
    }
    else{
        addedNode1 = (std::find(graph[node1].begin(), graph[node1].end(), node2) != graph[node1].end()) ? false : true;
    }

    // Thêm node2 vào đồ thị nếu nó chưa tồn tại
    if (graph.find(node2) == graph.end()) {
        graph[node2] = vector<int>();
    }
    else{
        addedNode2 = (std::find(graph[node2].begin(), graph[node2].end(), node1) != graph[node2].end()) ? false : true;
    }

    // Thêm cạnh vào danh sách kề
    if(addedNode1) graph[node1].push_back(node2);
    if(addedNode2) graph[node2].push_back(node1);  // Bỏ dòng này nếu đồ thị là đồ thị có hướng
}

// // Hàm thêm một node mới vào đồ thị
// void addNode(std::unordered_map<int, std::vector<int>>& graph, int newNode, const std::vector<int>& neighbors) {
//     // Thêm node mới vào đồ thị. Nếu node đã tồn tại, phần này sẽ không làm gì cả.
//     graph.insert({newNode, {}});

//     // Thêm các cạnh liên kết node mới với các node khác
//     for (int neighbor : neighbors) {
//         // Thêm neighbor vào danh sách kề của newNode
//         graph[newNode].push_back(neighbor);

//         // Thêm newNode vào danh sách kề của neighbor, nếu neighbor tồn tại trong đồ thị
//         if (graph.find(neighbor) != graph.end()) {
//             graph[neighbor].push_back(newNode);
//         }
//         else{
            
//         }
//     }
// }

void removeNode(unordered_map<int, vector<int>>& graph, int node) {
    // Xóa tất cả các tham chiếu đến node trong danh sách kề của các node khác
    for (auto& pair : graph) {
        auto& neighbors = pair.second;
        neighbors.erase(remove(neighbors.begin(), neighbors.end(), node), neighbors.end());
    }

    // Xóa node khỏi đồ thị
    graph.erase(node);
}

void printGraph(const unordered_map<int, vector<int>>& graph) {
    for (const auto& pair : graph) {
        cout << "Node " << pair.first << " ke voi: ";
        for (int neighbor : pair.second) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}

int main() {
    unordered_map<int, vector<int>> graph;

    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);  // Node 4 sẽ được tự động thêm vào đồ thị

    cout << "Do thi ban dau:" << endl;
    printGraph(graph);

    removeNode(graph, 3);

    cout << "Do thi sau khi xoa node 3:" << endl;
    printGraph(graph);

    return 0;
}

