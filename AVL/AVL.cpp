#include <iostream>
#include <algorithm>

using namespace std;

typedef struct node* Ref;

struct node{
	int key;
	int height;
	Ref left;
	Ref right;
};


struct AVL_tree{
	Ref root;
	AVL_tree()
		: root(nullptr)
	{}

	int height(Ref r){
		if(r == nullptr) return -1;
		return r->height;
	}

	Ref getNode(int key){
		Ref p = new node;
		if(!p) return nullptr;
		p->key = key;
		p->height = 0;
		p->left = p->right = nullptr;
		return p;
	}


	void printTree(Ref r, int type = 0){
		if(r == nullptr) return;
		if(type == 0) cout << "Root - " << r->key << endl;
		else if(type == 1) cout << "L - " << r->key << endl;
		else if(type == 2) cout << "R - " << r->key << endl;

		printTree(r->left, 1);
		printTree(r->right, 2);
	}

	void printTree(){
		printTree(root);
	}

	int getBalance(Ref r){
		return height(r->left) - height(r->right);
	}

	// rotate in case L-L
	Ref LL_rotate(Ref& rotateNode){
		Ref childNode = rotateNode->left;
		rotateNode->left = childNode->right;
		childNode->right = rotateNode;

		rotateNode->height = 1 + max(height(rotateNode->left), height(rotateNode->right));
		childNode->height = 1 + max(height(childNode->left), height(childNode->right));
		return childNode;
	}


	// rotate in case L-R
	Ref LR_rotate(Ref& rotateNode){
		Ref childNode = rotateNode->left;
		Ref graChildNode = childNode->right;
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
	Ref RR_rotate(Ref& rotateNode){
		Ref childNode = rotateNode->right;
		rotateNode->right = childNode->left;
		childNode->left = rotateNode;

		rotateNode->height = 1 + max(height(rotateNode->left), height(rotateNode->right));
		childNode->height = 1 + max(height(childNode->left), height(childNode->right));

		return childNode;
	}


	// Rotate in case R-L
	Ref RL_rotate(Ref& rotateNode){
		Ref childNode = rotateNode->right;
		Ref graChildNode = childNode->left;
		rotateNode->right = graChildNode->left;
		childNode->left = graChildNode->right;
		graChildNode->left = rotateNode;
		graChildNode->right = childNode;

		rotateNode->height = 1 + max(height(rotateNode->left), height(rotateNode->right));
		childNode->height = 1 + max(height(childNode->left), height(childNode->right));
		graChildNode->height = 1 + max(height(graChildNode->left), height(graChildNode->right));

		return graChildNode;
	}


	Ref balanceTree(Ref& r){
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

	Ref AVL_searchAdd(Ref& r, int key){
		if(r == nullptr){
			return getNode(key);
		}

		if(key < r->key) r->left = AVL_searchAdd(r->left, key);
		else if(key > r->key) r->right = AVL_searchAdd(r->right, key);

		r->height = 1 + max(height(r->left), height(r->right));

		return balanceTree(r);
	}

	void add(int key){
		root = AVL_searchAdd(root, key);
	}

	Ref findDelNode(Ref r){
		while(r->right) r = r->right;
		return r;
	}

	Ref AVL_searchDel(Ref& r, int key){
		if(r == nullptr) return nullptr;

		if(key < r->key) r->left = AVL_searchDel(r->left, key);
		else if(key > r->key) r->right = AVL_searchDel(r->right, key);
		else{
			if(r->left == nullptr || r->right == nullptr){
				Ref alterNode = (r->left) ? r->left : r->right;
				if(alterNode == nullptr){
					alterNode = r;
					r = nullptr;
				}
				else *r = *alterNode;

				delete alterNode, alterNode = nullptr;
			}
			else{
				Ref alterNode = findDelNode(r->left);
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

	void del(int key){
		root = AVL_searchDel(root, key);
	}

};


int height(Ref r){
	if(r == nullptr) return -1;
	return r->height;
}

Ref getNode(int key){
	Ref p = new node;
	if(!p) return nullptr;
	p->key = key;
	p->height = 0;
	p->left = p->right = nullptr;
	return p;
}

void printTree(Ref r, int type = 0){
	if(r == nullptr) return;
	if(type == 0) cout << "Root - " << r->key << endl;
	else if(type == 1) cout << "L - " << r->key << endl;
	else if(type == 2) cout << "R - " << r->key << endl;

	printTree(r->left, 1);
	printTree(r->right, 2);
}


int getBalance(Ref r){
	return height(r->left) - height(r->right);
}


// rotate in case L-L
Ref LL_rotate(Ref& rotateNode){
	Ref childNode = rotateNode->left;
	rotateNode->left = childNode->right;
	childNode->right = rotateNode;

	rotateNode->height = 1 + max(height(rotateNode->left), height(rotateNode->right));
	childNode->height = 1 + max(height(childNode->left), height(childNode->right));
	return childNode;
}

// rotate in case L-R
Ref LR_rotate(Ref& rotateNode){
	Ref childNode = rotateNode->left;
	Ref graChildNode = childNode->right;
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
Ref RR_rotate(Ref& rotateNode){
	Ref childNode = rotateNode->right;
	rotateNode->right = childNode->left;
	childNode->left = rotateNode;

	rotateNode->height = 1 + max(height(rotateNode->left), height(rotateNode->right));
	childNode->height = 1 + max(height(childNode->left), height(childNode->right));

	return childNode;
}

// Rotate in case R-L
Ref RL_rotate(Ref& rotateNode){
	Ref childNode = rotateNode->right;
	Ref graChildNode = childNode->left;
	rotateNode->right = graChildNode->left;
	childNode->left = graChildNode->right;
	graChildNode->left = rotateNode;
	graChildNode->right = childNode;

	rotateNode->height = 1 + max(height(rotateNode->left), height(rotateNode->right));
	childNode->height = 1 + max(height(childNode->left), height(childNode->right));
	graChildNode->height = 1 + max(height(graChildNode->left), height(graChildNode->right));

	return graChildNode;
}

Ref balanceTree(Ref& r){
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

Ref AVL_searchAdd(Ref& r, int key){
	if(r == nullptr){
		return getNode(key);
	}

	if(key < r->key) r->left = AVL_searchAdd(r->left, key);
	else if(key > r->key) r->right = AVL_searchAdd(r->right, key);

	r->height = 1 + max(height(r->left), height(r->right));

	return balanceTree(r);
}

Ref findDelNode(Ref r){
	while(r->right) r = r->right;
	return r;
}

Ref AVL_searchDel(Ref& r, int key){
	if(r == nullptr) return nullptr;

	if(key < r->key) r->left = AVL_searchDel(r->left, key);
	else if(key > r->key) r->right = AVL_searchDel(r->right, key);
	else{
		if(r->left == nullptr || r->right == nullptr){
			Ref alterNode = (r->left) ? r->left : r->right;
			if(alterNode == nullptr){
				alterNode = r;
				r = nullptr;
			}
			else *r = *alterNode;

			delete alterNode, alterNode = nullptr;
		}
		else{
			Ref alterNode = findDelNode(r->left);
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

int main(){
	freopen("input.txt", "r", stdin);
	freopen("a.txt", "w", stdout);
	int n; cin >> n;

	// Ref root = nullptr;
	AVL_tree tree;
	for(int i = 0; i < n; i++){
		int key; cin >> key;
		// root = AVL_searchAdd(root, key);
		tree.add(key);
	}

	// root = AVL_searchDel(root, 25);
	// root = AVL_searchDel(root, 9);
	// root = AVL_searchDel(root, 1);

	// printTree(root);
	tree.printTree();
}