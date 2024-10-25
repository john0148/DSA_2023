#include<iostream>
#include<string.h>
#include<queue>

using namespace std;

typedef struct node* Ref;

struct infor{
	char src[50];
	char dest[50];
	char code[50];
	int business_chair;
	int economy_chair;
	int hours;
	int minutes;


	infor& operator=(const infor& other){
		if(this != &other){
			strcpy(src, "");
			strcpy(src, other.src);
			strcpy(dest, "");
			strcpy(dest, other.dest);
			strcpy(code, "");
			strcpy(code, other.code);
			business_chair = other.business_chair;
			economy_chair = other.economy_chair;
			hours = other.hours;
			minutes = other.minutes;
		}
		return *this;
	}

	bool operator<(const infor& other) const {
		if(strcmp(src, other.src)) return (strcmp(src, other.src) == -1) ? true:false;
		else return (strcmp(dest, other.dest) == -1) ? true:false;
	}

	bool operator>(const infor& other) const {
		if(strcmp(src, other.src)) return (strcmp(src, other.src) == 1) ? true:false;
		else return (strcmp(dest, other.dest) == 1) ? true:false;
	}
};

struct node{
	infor key;
	int height;
	Ref left, right;
};

Ref getNode(infor key){
	Ref p = new node;
	if(!p) return nullptr;
	p->key = key;
	p->height = 0;
	p->left = p->right = nullptr;
	return p;
}

int height(Ref r){
	if(r == nullptr) return -1;
	return r->height;
}

bool search(Ref r, infor key){
	while(r){
		if(key < r->key) r = r->left;
		else if(key > r->key) r = r->right;
		else return true;
	}
	return false;
}

void printInfor(infor key){
	cout << key.src << "," << key.dest << "," << key.code << "," 
			<< key.business_chair << "," << key.economy_chair << "," 
			<< key.hours << "," << key.minutes << endl;
}

void printKey(Ref r, int pos = 1){
	if(r  == nullptr)return;
	if(pos == 1) {
		cout << "Root - ";
		printInfor(r->key);
	}
	else if(pos == 0) {
		cout << "L - ";
		printInfor(r->key);
	}
	else if(pos == 2) {
		cout << "R - ";
		printInfor(r->key);
	}
	printKey(r->left, 0);
	printKey(r->right, 2);
}


// Rotate in case left-left
Ref LL_rotate(Ref& rotateNode){
	Ref childNode = rotateNode->left;
	rotateNode->left = childNode->right;
	childNode->right = rotateNode;

	rotateNode->height = 1 + max(height(rotateNode->left), height(rotateNode->right));
	childNode->height = 1 + max(height(childNode->left), height(childNode->right));
	return childNode;
}

// Rotate in case left-right
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


// Rotate in case right-right
Ref RR_rotate(Ref& rotateNode){
	Ref childNode = rotateNode->right;
	rotateNode->right = childNode->left;
	childNode->left = rotateNode;

	rotateNode->height = 1 + max(height(rotateNode->left), height(rotateNode->right));
	childNode->height = 1 + max(height(childNode->left), height(childNode->right));

	return childNode;
}

// Rotate in case left-right
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


int getBalance(Ref r){
	if(r == nullptr) return 0;
	return height(r->left) - height(r->right);
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

Ref AVLsearchAdd(Ref &r, infor key){
	if(r == nullptr) {
		return getNode(key);
	}

	if(key < r->key) r->left = AVLsearchAdd(r->left, key);
	else if(key > r->key) r->right = AVLsearchAdd(r->right, key);

	r->height = 1 + max(height(r->left), height(r->right));
	
	return balanceTree(r);
}

Ref findDelNode(Ref r){
	while(r->right) r = r->right;
	return r;
}

Ref AVLsearchDel(Ref& r, Ref& markNode, infor key){
	if(r == nullptr) return nullptr;

	if(key < r->key) r->left = AVLsearchDel(r->left, markNode, key);
	else if(key > r->key) r->right = AVLsearchDel(r->right, markNode, key);
	else{
		if(r->left == nullptr || r->right == nullptr){
			Ref alterNode = (r->left) ? r->left : r->right;
			if(alterNode == nullptr){
				alterNode = r;
				r = nullptr;
			}
			else *r = *alterNode;
			markNode = r;
			delete alterNode, alterNode = nullptr;
		}
		else{
			Ref alterNode = findDelNode(r->left);
			r->key = alterNode->key;
			r->left = AVLsearchDel(r->left, markNode, alterNode->key);
			markNode = r;
		}
	}

	if(r){
		r->height = 1 + max(height(r->left), height(r->right));
		r = balanceTree(r);
	}

	return r;
}


void DFS(int level, int &h, Ref r){
	if(h == level) {
		printInfor(r->key);
		return;
	}
	h++;
	if(r->left) DFS(level, h, r->left);
	if(r->right) DFS(level, h, r->right);
	h--;
}

void DFS_del(Ref& root, Ref r, char c){
	while(r != nullptr && r->key.src[0] == c) {
		root = AVLsearchDel(root, r, r->key);
	}
	if(r) DFS_del(root, r->left, c);
	if(r) DFS_del(root, r->right, c);
}

void DFS_findMax(Ref r, int& max){
	if(r == nullptr) return;
	if(max < r->key.business_chair + r->key.economy_chair){
		max = r->key.business_chair + r->key.economy_chair;
	}
	DFS_findMax(r->left, max);
	DFS_findMax(r->right, max);
}

void DFS_addArr(Ref r, int max, vector<vector<Ref>> &v){
	if(r == nullptr) return;
	if(r->key.business_chair + r->key.economy_chair == max){
		v[height(r)].push_back(r);
	}

	DFS_addArr(r->left, max, v);
	DFS_addArr(r->right, max, v);
}

void printMaxChair(Ref root){
	int max = -1;
	DFS_findMax(root, max);
	if(max == -1) return;

	vector<vector<Ref>> v;
	v.resize(height(root) + 1);
	DFS_addArr(root, max, v);
	for(int i = 0; i <= height(root); i++){
		int n = v[i].size();
		if(n > 0) cout << "height " << i << ":" << endl;
		for(int j = 0; j < n; j++){
			printInfor(v[i][j]->key);
		}
	}
}

int main(){
	FILE* file = fopen("input.txt", "r");
	if(!file){
		cout << "Cannot open file!\n";
		return 1;
	}
	// Bai 1
	Ref root = nullptr;
	int read = 0;
	do{
		infor key;
		read = fscanf(file, "{\"%49[^,],%49[^\"]\": [\"%49[^\"]\", \"%d business, %d economy\", \"%d hours, %d minutes\"]}\n",
						key.src,
						key.dest,
						key.code,
						&key.business_chair,
						&key.economy_chair,
						&key.hours,
						&key.minutes);

		if(read != 7 && !feof(file)){
			cout << "file format incorrect!\n";
			return 1;
		}

		if(ferror(file)){
			cout << "Error reading file!\n";
			return 1;
		}

		root = AVLsearchAdd(root, key);
	}while(!feof(file));

	// Bai 2
	// int h = 0;
	// DFS(1, h, root);

	//Bai 3
	char arrChar[] = {'B', 'A'};
	int n = sizeof(arrChar)/sizeof(arrChar[0]);
	for(int i = 0; i < n; i++){
		DFS_del(root, root, arrChar[i]);
	}

	//Bai 4
	printKey(root);
	// printMaxChair(root);


}