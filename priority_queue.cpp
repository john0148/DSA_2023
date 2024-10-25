#include <iostream>
#include <queue>

// Định nghĩa một struct node
struct Node {
    int value;
    // Các trường khác của struct (nếu có)

    // Constructor
    Node(int val) : value(val) {}
};

int main() {
    // Sử dụng std::priority_queue với lambda function để tùy chỉnh phép so sánh
    auto compare = [](const Node& a, const Node& b) {
        return a.value > b.value; // Sắp xếp theo thứ tự giảm dần
    };

    std::priority_queue<Node, std::vector<Node>, decltype(compare)> myPriorityQueue(compare);

    // Thêm các phần tử vào priority_queue
    myPriorityQueue.push(Node(3));
    myPriorityQueue.push(Node(1));
    myPriorityQueue.push(Node(5));

    // Lấy và in ra các phần tử theo thứ tự ưu tiên
    while (!myPriorityQueue.empty()) {
        std::cout << myPriorityQueue.top().value << " ";
        myPriorityQueue.pop();
    }

    return 0;
}
