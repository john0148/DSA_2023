#include <fstream>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

// BeginCodeSnip{DSU}
class DSU {
  private:
	vector<int> parent;
	vector<int> size;

  public:
	DSU(int size) : parent(size), size(size, 1) {
		for (int i = 0; i < size; i++) { parent[i] = i; }
	}

	int get_top(int n) {
		return parent[n] == n ? n : (parent[n] = get_top(parent[n]));
	}

	bool link(int n1, int n2) {
		n1 = get_top(n1);
		n2 = get_top(n2);
		if (n1 == n2) { return false; }
		if (size[n2] > size[n1]) { return link(n2, n1); }
		parent[n2] = n1;
		size[n1] += size[n2];
		return true;
	}
};
// EndCodeSnip

struct Wormhole {
	int c1, c2;
	int width;
};

int main() {
	std::ifstream read("wormsort.in");
	int cow_num;
	int wormhole_num;
	read >> cow_num >> wormhole_num;

	vector<int> cows(cow_num);
	for (int &c : cows) {
		read >> c;
		c--;  // make the cows 0-indexed
	}

	int max_width = 0;
	vector<Wormhole> wormholes(wormhole_num);
	for (Wormhole &w : wormholes) {
		read >> w.c1 >> w.c2 >> w.width;
		w.c1--;
		w.c2--;
		max_width = std::max(max_width, w.width);
	}

	int lo = 0;
	int hi = max_width + 1;
	int valid = -1;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;

		DSU dsu(cow_num);
		for (const Wormhole &w : wormholes) {
			if (w.width >= mid) { dsu.link(w.c1, w.c2); }
		}

		bool sortable = true;
		for (int c = 0; c < cow_num; c++) {
			if (dsu.get_top(c) != dsu.get_top(cows[c])) {
				sortable = false;
				break;
			}
		}

		if (sortable) {
			valid = mid;
			lo = mid + 1;
		} else {
			hi = mid - 1;
		}
	}

	std::ofstream("wormsort.out")
	    << (valid == max_width + 1 ? -1 : valid) << endl;
}