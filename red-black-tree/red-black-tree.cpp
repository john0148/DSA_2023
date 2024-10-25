#include <iostream>
#include <algorithm>
#include <climits>
#define RED 1
#define BLACK 0
using namespace std;

typedef struct node* Ref;
struct node{
	int key;
	int color;
	Ref parent;
	Ref left;
	Ref right;
};

Ref getNode(int key, Ref nil){
	Ref p = new node;
	if(!p) return nullptr;
	p->key = key;
	p->color = RED;
	p->parent = p->left = p->right = nil;
	return p;
}

void printTree(Ref r, Ref nil, int pos = 0){
	if(r == nil) return;
	if(pos == 0) cout << "Root - " << r->key << " color - " << r->color << endl;
	else if(pos == 1) cout << "L - " << r->key << " color - " << r->color << endl;
	else cout << "R - " << r->key << " color - " << r->color << endl;
	printTree(r->left, nil, 1);
	printTree(r->right, nil, 2);
}

//Phép quay sang trái
void leftRotate(Ref &root, Ref &x, Ref nil){
	Ref y = x -> right;
	x->right = y->left;
	if(y->left != nil){
		y->left->parent = x;
	}
	y->parent = x->parent;
	if(x->parent == nil){
		root = y;
	}
	else{
		if(x->parent->left == x){
			x->parent->left = y;
		}
		else{
			x->parent->right = y;
		}
	}

	y->left = x;
	x->parent = y;
}

//Phép quay sang phải
void rightRotate(Ref &root, Ref &x, Ref nil){
	Ref y = x->left;
	x->left = y->right;
	if(y->right != nil){
		y->right->parent = x;
	}
	y->parent = x ->parent;

	if(x->parent == nil){
		root = y;
	}
	else{
		if(x->parent->left == x){
			x->parent->left = y;
		}
		else if(x->parent->right == x){
			x->parent->right =  y;
		}
	}
	y->right = x;
	x->parent = y;
}

void insertion_leftAdjust(Ref &root, Ref &x, Ref nil){
	Ref u = x->parent->parent->right;
	if(u->color == RED){
		x->parent->color = u->color = BLACK;
		x->parent->parent->color = RED;
		x = x->parent->parent;
	}
	else{
		if(x->parent->right == x){
			x = x->parent;
			leftRotate(root, x, nil);
		}
		x->parent->color = BLACK;
		x->parent->parent->color = RED;
		x = x->parent->parent;
		rightRotate(root, x, nil);
	}
}

void insertion_rightAdjust(Ref &root, Ref &x, Ref nil){
	Ref u = x->parent->parent->left;
	if(u->color == RED){
		x->parent->color = u->color = BLACK;
		x->parent->parent->color = RED;
		x = x->parent->parent;
	}
	else{
		if(x->parent->left == x){
			x = x->parent;
			rightRotate(root, x, nil);
		}
		x->parent->color = BLACK;
		x->parent->parent->color = RED;
		x = x->parent->parent;
		leftRotate(root, x, nil);
	}
}

void insertion_Fix(Ref &root, Ref &x, Ref nil){
	while(x->parent->color == RED){
		if(x->parent->parent->left == x->parent){
			insertion_leftAdjust(root, x, nil);
		}
		else{
			insertion_rightAdjust(root, x, nil);
		}
	}
	root->color = BLACK;
}

void RBT_insertion(Ref &root, Ref &x, Ref nil){
	Ref prev = nil;
	Ref r = root;
	while(r != nil){
		prev = r;
		if(x->key < r->key) r = r->left;
		else if(x->key > r->key) r = r->right;
		else return;
	}

	if(prev == nil) root = x;
	else{
		x->parent = prev;
		if(prev->key > x->key) prev->left = x;
		else prev->right = x;
	}
	insertion_Fix(root, x, nil);
}

Ref searchKey(Ref r, int key, Ref nil){
	while(r != nil){
		if(key < r->key) r = r->left;
		else if(key > r->key) r = r->right;
		else return r;
	}
	return nil;
}

Ref AlternativeNode(Ref deletableNode, Ref nil){
	Ref alterNode = deletableNode->left;
	while(alterNode->right != nil) alterNode = alterNode->right;
	return alterNode;
}

void deletion_leftAdjust(Ref &root, Ref &markNode, Ref nil){

	// sibNode là nút anh em của nút có dấu hiệu đen
	Ref sibNode = markNode->parent->right;

	// Trường hợp nút anh em của nút có dấu hiệu đen màu đỏ
	if(sibNode->color == RED){
		sibNode->color = BLACK;
		markNode->parent->color = RED;
		markNode = markNode->parent;
		leftRotate(root, markNode, nil);
		markNode = markNode->left;
		sibNode = markNode->parent->right;
	}

	// Trường hợp nút con của nút anh em đều màu đen
	if(sibNode->left->color == BLACK && sibNode->right->color == BLACK){
		sibNode->color = RED;
		markNode = markNode->parent;
	} // Trường hợp nút con của nút anh em có ít nhất một nút đỏ
	else{
		if(sibNode->right->color == BLACK){
			sibNode->color = RED;
			sibNode->left->color = BLACK;
			rightRotate(root, sibNode, nil);
			sibNode = markNode->parent->right;
		}

		sibNode->color = markNode->parent->color;
		markNode->parent->color = sibNode->right->color = BLACK;
		sibNode = sibNode->parent;
		leftRotate(root, sibNode, nil);
		markNode = root;
	}

}

void deletion_rightAdjust(Ref &root, Ref &markNode, Ref nil){

	// sibNode là nút anh em của nút có dấu hiệu đen
	Ref sibNode = markNode->parent->left;

	// Trường hợp nút anh em của nút có dấu hiệu đen màu đỏ
	if(sibNode->color == RED){
		sibNode->color = BLACK;
		markNode->parent->color = RED;
		markNode = markNode->parent;
		leftRotate(root, markNode, nil);
		markNode = markNode->right;
		sibNode = markNode->parent->left;
	}

	// Trường hợp nút con của nút anh em đều màu đen
	if(sibNode->left->color == BLACK && sibNode->right->color == BLACK){
		sibNode->color = RED;
		markNode = markNode->parent;
	} // Trường hợp nút con của nút anh em có ít nhất một nút đỏ
	else{
		if(sibNode->left->color == BLACK){
			sibNode->color = RED;
			sibNode->right->color = BLACK;
			leftRotate(root, sibNode, nil);
			sibNode = markNode->parent->left;
		}

		sibNode->color = markNode->parent->color;
		markNode->parent->color = sibNode->left->color = BLACK;
		sibNode = sibNode->parent;
		rightRotate(root, sibNode, nil);
		markNode = root;
	}

}

void deletion_Fix(Ref &root, Ref &markNode, Ref nil){
	while(markNode->color != RED && markNode != root){
		if(markNode->parent->left == markNode)
			deletion_leftAdjust(root, markNode, nil);
		else
			deletion_rightAdjust(root, markNode, nil);
	}
	markNode->color = BLACK;
}

void RBT_deletion(Ref &root, int key, Ref nil){
	Ref deletableNode = searchKey(root, key, nil);
	if(deletableNode == nil) return;
	Ref delNode = (deletableNode->left == nil || deletableNode->right == nil) ? deletableNode : AlternativeNode(deletableNode, nil);

	if(delNode != deletableNode) deletableNode->key = delNode->key;

	Ref markNode = (delNode->left == nil) ? delNode->right : delNode->left;
	markNode->parent = delNode->parent;
	if(delNode->parent == nil){
		root = markNode;
	}
	else{
		if(delNode->parent->left == delNode){
			delNode->parent->left = markNode;
		}
		else{
			delNode->parent->right = markNode;
		}
	}

	if(delNode->color == BLACK){
		deletion_Fix(root, markNode, nil);
	}
	delete delNode; delNode = nullptr;
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("a.txt", "w", stdout);
	Ref nil = new node;
	nil->color = BLACK;
	nil->parent = nil;
	nil->left = nullptr;
	nil->right = nullptr;

	Ref root = nil;
	int n; cin >> n;
	for(int i = 0; i < n; i++){
		int key; cin >> key;
		Ref x = getNode(key, nil);
		RBT_insertion(root, x, nil);
	}

	RBT_deletion(root, 35, nil);
	RBT_deletion(root, 50, nil);
	// RBT_deletion(root, 40, nil);
	// RBT_deletion(root, 38, nil);
	// RBT_deletion(root, 30, nil);
	// RBT_deletion(root, 45, nil);
	// RBT_deletion(root, 39, nil);
	// RBT_deletion(root, 37, nil);
	// RBT_deletion(root, 10, nil);
	// RBT_deletion(root, 36, nil);
	// RBT_deletion(root, 60, nil);
	printTree(root, nil);
}