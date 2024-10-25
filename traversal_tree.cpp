#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef struct node* Ref;
struct node{
	int key;
	Ref left;
	Ref right;
};

Ref getNode(int key){
	Ref p = new node;
	if(!p) return nullptr;
	p->key = key;
	p->left = p->right = nullptr;
	return p;
}

Ref addNode(Ref& root, int key){
	if(root == nullptr){
		return getNode(key);
	}

	if(key < root->key) root->left = addNode(root->left, key);
	else if(key > root->key) root->right = addNode(root->right, key);

	return root;
}

void printTree(Ref r, int type = 0){
	if(r == nullptr) return;
	if(type == 0) cout << "Root - ";
	else if(type == 1) cout << "L - ";
	else if(type == 2) cout << "R - ";
	cout << r->key << endl;
	printTree(r->left, 1);
	printTree(r->right, 2);

}

void preOrder(Ref r){
	if(r){
		preOrder(r->left);
		cout << r->key << " ";
		preOrder(r->right);
	}
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n; cin >> n;
	Ref root = nullptr;
	for(int i = 0; i < n; i++){
		int key; cin >> key;
		root = addNode(root, key);
	}

	// printTree(root);
	preOrder(root);
	cout << endl;
}