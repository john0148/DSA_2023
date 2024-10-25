#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void removeNode(vector<std::vector<int>>& matrix, int node) {
    int size = matrix.size();

    // Kiểm tra xem node có tồn tại trong ma trận không
    if (node < 0 || node >= size) {
        cout << "Node " << node << " không tồn tại trong ma trận." << std::endl;
        return;
    }

    // Xóa hàng tương ứng với node
    matrix.erase(matrix.begin() + node);

    // Xóa cột tương ứng với node
    for (auto& row : matrix) {
        row.erase(row.begin() + node);
    }
}

void printMatrix(const vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

void addNode(vector<vector<int>>& matrix, const vector<int>& connectedNodes) {
    int newSize = matrix.size() + 1;


    // Thêm một hàng mới; mặc định tất cả các giá trị là 0
    vector<int> newRow(newSize, 0);


    // Cập nhật hàng mới dựa trên các đỉnh được kết nối
    for (int node : connectedNodes) {
        if (node >= 0 && node < (int)matrix.size()) {
            newRow[node] = 1; // Đặt giá trị là 1 nếu có liên kết
        }
    }

    // Thêm một cột mới vào mỗi hàng hiện tại và cập nhật nếu có liên kết
    for (int i = 0; i < (int)matrix.size(); ++i) {
        int value = (std::find(connectedNodes.begin(), connectedNodes.end(), i) != connectedNodes.end()) ? 1 : 0;
        matrix[i].push_back(value);
    }

    // Thêm hàng mới vào ma trận
    matrix.push_back(newRow);

}

void addNodeIfNeeded(vector<vector<int>>& matrix, int node) {
    while (node >= (int)matrix.size()) {
        for (auto& row : matrix) {
            row.push_back(0);
        }
        matrix.push_back(vector<int>(matrix.size() + 1, 0));
    }
}

void addEdge(vector<vector<int>>& matrix, int node1, int node2) {
    addNodeIfNeeded(matrix, max(node1, node2));
    matrix[node1][node2] = 1;
    matrix[node2][node1] = 1; // Bỏ dòng này nếu đồ thị là đồ thị có hướng
}

int main() {
    // Ví dụ về ma trận kề
    vector<vector<int>> matrix = {
        {0, 1, 1, 0},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {0, 0, 1, 0}
    };

    cout << "ma tran ke:" << endl;
    printMatrix(matrix);

    // Xóa node 2
    removeNode(matrix, 2);

    cout << "ma tran ke sau khi xoa node 2" << endl;
    printMatrix(matrix);

    // Thêm một đỉnh mới kết nối với đỉnh 0 và 1
    std::vector<int> connectedNodes = {0, 1};
    addNode(matrix, connectedNodes);

    cout << "ma tran ke sau khi them nut moi" << endl;
    printMatrix(matrix);

    // Thêm một cạnh mới từ đỉnh 1 đến đỉnh 2
    addEdge(matrix, 1, 2);

    cout << "Ma tran ke sau khi them canh 1-2:" << endl;
    printMatrix(matrix);

    return 0;
}
