#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <iomanip>
using namespace std;

template <typename T>
struct node{
	T key;
	int height;
	node<T> *left;
	node<T> *right;
};

template <typename T>
struct AVL_tree{
	node<T> *root;

	AVL_tree() : root(nullptr) {}

	int height(node<T> *r){
		if(r == nullptr) return -1;
		return r->height;
	}

	node<T>* getNode(T key){
		node<T> *p = new node<T>;
		if(!p) return nullptr;
		p->key = key;
		p->height = 0;
		p->left = p->right = nullptr;
		return p;
	}

	void printTree(node<T>* r, int indent = 0) {
	    if (r != nullptr) {
	        if (r->right) {
	            printTree(r->right, indent + 4);
	        }
	        if (indent > 0) {
	            cout << setw(indent) << " ";
	        }
	        cout << r->key << endl;
	        if (r->left) {
	            printTree(r->left, indent + 4);
	        }
	    }
	}

	void printTree(){
		printTree(root);
	}

	// bool search(T key){
	// 	node<T> *r = root;
	// 	while(r){
	// 		if(key < r->key) r = r->left;
	// 		else if(key > r->key) r = r->right;
	// 		else return true;
	// 	}
	// 	return false;
	// }

	node<T>* find(T key){
		node<T> *r = root;
		while(r){
			if(key < r->key) r = r->left;
			else if(key > r->key) r = r->right;
			else return r;
		}
		return nullptr;
	}

	int getBalance(node<T> *r){
		return height(r->left) - height(r->right);
	}

	// rotate in case L-L
	node<T>* LL_rotate(node<T>*& rotateNode){
		node<T> *childNode = rotateNode->left;
		rotateNode->left = childNode->right;
		childNode->right = rotateNode;

		rotateNode->height = 1 + max(height(rotateNode->left), height(rotateNode->right));
		childNode->height = 1 + max(height(childNode->left), height(childNode->right));
		return childNode;
	}


	// rotate in case L-R
	node<T>* LR_rotate(node<T>*& rotateNode){
		node<T> *childNode = rotateNode->left;
		node<T> *graChildNode = childNode->right;
		rotateNode->left = graChildNode->right;
		childNode->right = graChildNode->left;
		graChildNode->left = childNode;
		graChildNode->right = rotateNode;

		rotateNode->height = 1 + max(height(rotateNode->left), height(rotateNode->right));
		childNode->height = 1 + max(height(childNode->left), height(childNode->right));
		graChildNode->height = 1 + max(height(graChildNode->left), height(graChildNode->right));

		return graChildNode;
	}

	//rotate in case R-R
	node<T>* RR_rotate(node<T>*& rotateNode){
		node<T> *childNode = rotateNode->right;
		rotateNode->right = childNode->left;
		childNode->left = rotateNode;

		rotateNode->height = 1 + max(height(rotateNode->left), height(rotateNode->right));
		childNode->height = 1 + max(height(childNode->left), height(childNode->right));

		return childNode;
	}

	// Rotate in case R-L
	node<T>* RL_rotate(node<T>*& rotateNode){
		node<T> *childNode = rotateNode->right;
		node<T> *graChildNode = childNode->left;
		rotateNode->right = graChildNode->left;
		childNode->left = graChildNode->right;
		graChildNode->left = rotateNode;
		graChildNode->right = childNode;

		rotateNode->height = 1 + max(height(rotateNode->left), height(rotateNode->right));
		childNode->height = 1 + max(height(childNode->left), height(childNode->right));
		graChildNode->height = 1 + max(height(graChildNode->left), height(graChildNode->right));

		return graChildNode;
	}

	node<T>* balanceTree(node<T>*& r){
		int balance = getBalance(r);

		if(balance > 1){ // In this case, the tree leans towards the left side.
			if(height(r->left->left) >= height(r->left->right)){
				r = LL_rotate(r);
			}
			else r = LR_rotate(r);
		}
		else if(balance < -1){ // In this case, the tree leans towards the right side
			if(height(r->right->left) <= height(r->right->right)){
				r = RR_rotate(r);
			}
			else r = RL_rotate(r);
		}

		return r;
	}

	node<T>* AVL_searchAdd(node<T>*& r, T key){
		if(r == nullptr){
			return getNode(key);
		}

		if(key < r->key) r->left = AVL_searchAdd(r->left, key);
		else if(key > r->key) r->right = AVL_searchAdd(r->right, key);

		r->height = 1 + max(height(r->left), height(r->right));

		return balanceTree(r);
	}

	void add(T key){
		root = AVL_searchAdd(root, key);
	}


	node<T>* findDelNode(node<T>* r){
		while(r && r->right) r = r->right;
		return r;
	}

	node<T>* AVL_searchDel(node<T>*& r, T key){
		if(r == nullptr) return nullptr;

		if(key < r->key) r->left = AVL_searchDel(r->left, key);
		else if(key > r->key) r->right = AVL_searchDel(r->right, key);
		else{
			if(r->left == nullptr || r->right == nullptr){
				node<T>* alterNode = (r->left) ? r->left : r->right;
				if(alterNode == nullptr){
					alterNode = r;
					r = nullptr;
				}
				else *r = *alterNode;

				delete alterNode;
			}
			else{
				node<T>* alterNode = findDelNode(r->left);
				r->key = alterNode->key;
				r->left = AVL_searchDel(r->left, alterNode->key);
			}
		}

		if(r){
			r->height = 1 + max(height(r->left), height(r->right));
			r = balanceTree(r);
		}

		return r;
	}

	void del(T key){
		root = AVL_searchDel(root, key);
	}

};

struct leader{
	int key;
	AVL_tree<int> trail;

	leader& operator=(const leader& other){
		if(this != &other){
			key = other.key;
			trail = other.trail;
		}
		return *this;
	}

	// Overload toán tử "<" cho struct leader
    bool operator<(const leader& other) const {
        return key < other.key;
    }

    // Overload toán tử "<" cho struct leader
    bool operator<(const int& other_key) const {
        return key < other_key;
    }

    // Overload toán tử ">" cho struct leader
    bool operator>(const leader& other) const {
        return key > other.key;
    }

    // Overload toán tử ">" cho struct leader
    bool operator>(const int& other_key) const {
        return key > other_key;
    }
};

// istream& operator>>(istream& INDEV, leader& l) {
// 	INDEV >> l.key;
// 	return INDEV;
// }

ostream& operator<<(ostream& OUTDEV, const leader l) {
	OUTDEV << l.key;
	return OUTDEV;
}

node<leader>* addList(AVL_tree<leader>& adj, int key){
	leader leader_key;
	leader_key.key = key;
	if(adj.find(leader_key) == nullptr){
		adj.add(leader_key);
	}
	return adj.find(leader_key);
}

void addEdge(AVL_tree<leader>& adj, int a, int b){
	node<leader>* p = addList(adj, a);
	node<leader>* q = addList(adj, b);
	p->key.trail.add(b);
	q->key.trail.add(a);
}

void printArr(node<leader>* root){
	cout << root->key.key << " : ";
	queue<node<int>*> q;

	q.push(root->key.trail.root);
	while(!q.empty()){
		node<int>* r = q.front();
		q.pop();
		cout << r->key << " ";
		if(r->left) q.push(r->left);
		if(r->right) q.push(r->right);
	}

	cout << endl;
}

void printADJ(node<leader>* r){
	if(r == nullptr) return;
	printArr(r);

	printADJ(r->left);
	printADJ(r->right);
}


int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	// lRef head = getNode();
	// lRef tail = head;
	// int n; cin >> n;
	// string a, b;
	// for(int i = 0; i < n; i++){
	// 	cin >> a >> b;
	// 	lRef p = addList(head, tail, a)
	// 	lRef q = addList(head, tail, b);

	// 	tRef t_a = new trailer;
	// 	tRef t_b = new trailer;
	// 	t_a->id = b; t_a->next = p->trail; p->trail = t_a;
	// 	t_b->id = a; t_b->next = q->trail; q->trail = t_b;
	// }

	// printNode(head, tail);
	// lRef p = findLeader(head, tail, "A");
	// if(!p) cout << "NO\n";
	// else {
	// 	tRef t = findTrailer(p, "D");
	// 	if(!t) cout << "trailer not in leader\n";
	// 	else cout << "trailer in leader\n";
	// }

	AVL_tree<leader> adj;

	int n; cin >> n;
	int a, b;
	for(int i = 0; i < n; i++){
		cin >> a >> b;
		addEdge(adj, a, b);
	}

	adj.printTree();
	printADJ(adj.root);
}