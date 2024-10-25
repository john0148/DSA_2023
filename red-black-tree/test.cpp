#include <iostream>
#include <algorithm>
#define RED 1
#define BLACK 0
using namespace std;

// Definition of a pointer to a 'node' structure as 'Ref'
typedef struct node* Ref;

// Definition of the 'node' structure for the red-black tree
struct node{
	int key;			// Key value of the node
	int color;			// Color of the node (RED or BLACK)
	Ref parent;			// Pointer to the parent node
	Ref left, right;	// Pointer to the left and right child node
};

// Function to create a new node with a given key and nil references
Ref getNode(int key, Ref nil){
	Ref p = new node;		// Allocating memory for a new node
	if(!p) return nil;		// If memory allocation fails, return nil

	// Initializing the new node's properties
	p->color = RED;			// Setting the node's color to RED
	p->key = key;			// Assigning the key value to the node
	p->parent = p->left = p->right = nil;	// Initializing parent, left, and right children to nil
	return p;	// Returning the new node
}

void printTree(Ref r, Ref nil, int pos = 0){
	if(r == nil) return;
	if(pos == 0) cout << "Root - " << r->key << " color - " << r->color << endl;
	else if(pos == 1) cout << "L - " << r->key << " color - " << r->color << endl;
	else cout << "R - " << r->key << " color - " << r->color << endl;
	printTree(r->left, nil, 1);
	printTree(r->right, nil, 2);
}


// Performs a left rotation on the red-black tree
void leftRotate(Ref &root, Ref &rotatedRoot, Ref nil){
	Ref childNode = rotatedRoot->right;		// Get the right child of the node to be rotated
	rotatedRoot->right = childNode->left;	// Move child's left subtree to rotated node's right subtree
	if(childNode->left != nil){
		childNode->left->parent = rotatedRoot;	// Adjust parent pointer of the moved subtree
	}

	// Set the child as the new root of the subtree
	childNode->parent = rotatedRoot->parent;
	if(rotatedRoot->parent == nil){	// If rotatedRoot was the root, update the tree root
		root = childNode;
	}
	else{	// Otherwise, adjust the parent's child pointer
		if(rotatedRoot->parent->left == rotatedRoot){
			rotatedRoot->parent->left = childNode;	// Adjust parent pointer of the moved subtree
		}
		else{
			rotatedRoot->parent->right = childNode;
		}
	}

	// Complete the rotation
	childNode->left = rotatedRoot;
	rotatedRoot->parent = childNode;
}

// Performs a right rotation on the red-black tree
void rightRotate(Ref &root, Ref &rotatedRoot, Ref nil){
	Ref childNode = rotatedRoot->left;	// Get the left child of the node to be rotated

	rotatedRoot->left = childNode->right;	// Move child's right subtree to rotated node's left subtree
	if(childNode->right != nil){
		childNode->right->parent = rotatedRoot;
	}

	// Set the child as the new root of the subtree
	childNode->parent = rotatedRoot->parent;
	if(rotatedRoot->parent == nil){	// If rotatedRoot was the root, update the tree root
		root = childNode;
	}
	else{	// Otherwise, adjust the parent's child pointer
		if(rotatedRoot->parent->left == rotatedRoot){
			rotatedRoot->parent->left = childNode;
		}
		else{
			rotatedRoot->parent->right = childNode;
		}
	}

	// Complete the rotation
	childNode->right = rotatedRoot;
	rotatedRoot->parent = childNode;
}

// Adjusts the tree after an insertion, when the added node's parent is on the left
void insertion_leftAdjust(Ref &root, Ref &addNode, Ref nil){
	Ref u = addNode->parent->parent->right; // Uncle of the added node
	if(u->color == RED){
		// Recolor and move up the tree if the uncle is red
		addNode->parent->color = u->color = BLACK;
		addNode->parent->parent->color = RED;
		addNode = addNode->parent->parent;
	}
	else{
		// Perform rotations and recolor if the uncle is black
		if(addNode->parent->right == addNode){	
			addNode = addNode->parent;
			leftRotate(root, addNode, nil);
		}

		addNode->parent->color = BLACK;
		addNode->parent->parent->color = RED;
		addNode = addNode->parent->parent;
		rightRotate(root, addNode, nil);
	}
}

// Adjusts the tree after an insertion, when the added node's parent is on the right
void insertion_rightAdjust(Ref &root, Ref &addNode, Ref nil){
	Ref u = addNode->parent->parent->left;	// Uncle of the added node
	if(u->color == RED){
		// Recolor and move up the tree if the uncle is red
		addNode->parent->color = u->color = BLACK;
		addNode->parent->parent->color = RED;
		addNode = addNode->parent->parent;
	}
	else{
		// Perform rotations and recolor if the uncle is black
		if(addNode->parent->left == addNode){
			addNode = addNode->parent;
			rightRotate(root, addNode, nil);
		}

		addNode->parent->color = BLACK;
		addNode->parent->parent->color = RED;
		addNode = addNode->parent->parent;
		leftRotate(root, addNode, nil);
	}	
}

// Fixes the red-black tree properties after an insertion
void insertion_Fix(Ref &root, Ref &addNode, Ref nil){
	// Fix the tree up to the root
	while(addNode->parent->color == RED){
		if(addNode->parent->parent->left == addNode->parent) insertion_leftAdjust(root, addNode, nil);
		else insertion_rightAdjust(root, addNode, nil);
	}
	root->color = BLACK; // Ensure the root is always black
}

// Inserts a node into the red-black tree and fixes any violations
void RBT_insertion(Ref &root, Ref &addNode, Ref nil){
	Ref prev = nil;	// Previous node for insertion point
	Ref r = root;	// Current node in the tree
	// Find the insertion point
	while(r != nil){
		prev = r;
		if(addNode->key < r->key) r = r->left;
		else if(addNode->key > r->key) r = r->right;
		else return;	// Key already exists, do not insert
	}

	// Insert the node
	if(prev == nil) root = addNode; // Tree was empty, new node is root
	else{
		addNode->parent = prev;
		if(addNode->key < prev->key) prev->left = addNode;
		else prev->right = addNode;
	}
	insertion_Fix(root, addNode, nil); // Fix the red-black tree properties
}

// Searches for a node with a given key in the red-black tree
Ref searchNode(Ref r, int key, Ref nil){
	// Traverse the tree to find the key
	while(r != nil){
		if(key < r->key) r = r->left;
		else if(key > r->key) r = r->right;
		else return r; // Key found
	}
	return nil; // Key not found
}

// Function to find the node to replace a node being deleted
Ref alternativeNode(Ref deletableNode, Ref nil){
	Ref alterNode = deletableNode->left; // Start from the left child of the deletable node
	while(alterNode->right != nil) alterNode = alterNode->right; // Find the rightmost child
	return alterNode; // This node will replace the deletable node
}

// Adjusts the tree after a deletion when the marked node is on the left
void deletion_leftAdjust(Ref &root, Ref &markNode, Ref nil){
	Ref sibNode = markNode->parent->right; // Sibling of the marked node
	if(sibNode->color == RED){
		// Case 1: Red sibling
		sibNode->color = BLACK;
		markNode->parent->color = RED;
		markNode = markNode->parent;
		leftRotate(root, markNode, nil);
		markNode = markNode->left;
		sibNode = markNode->parent->right;
	}

	// Case 2: Both of sibling's children are black
	if(sibNode->left->color == BLACK && sibNode->right->color == BLACK){
		sibNode->color = RED;
		markNode = markNode->parent;
	}
	else{
		// Case 3: Sibling's right child is black
		if(sibNode->right->color == BLACK){
			sibNode->color = RED;
			sibNode->left->color = BLACK;
			rightRotate(root, sibNode, nil);
			sibNode = markNode->parent->right;
		}

		// Case 4: Sibling's right child is red
		sibNode->color = markNode->parent->color;
		markNode->parent->color = sibNode->right->color = BLACK;
		sibNode = sibNode->parent;
		leftRotate(root, sibNode, nil);
		markNode = root;
	}
}

// Adjusts the tree after a deletion when the marked node is on the right
void deletion_rightAdjust(Ref &root, Ref &markNode, Ref nil){
	Ref sibNode = markNode->parent->left; // Sibling of the marked node
	if(sibNode->color == RED){
		// Case 1: Red sibling
		sibNode->color = BLACK;
		markNode->parent->color = RED;
		markNode = markNode->parent;
		leftRotate(root, markNode, nil);
		markNode = markNode->right;
		sibNode = markNode->parent->left;
	}

	// Case 2: Both of sibling's children are black
	if(sibNode->left->color == BLACK && sibNode->right->color == BLACK){
		sibNode->color = RED;
		markNode = markNode->parent;
	}
	else{
		// Case 3: Sibling's left child is black
		if(sibNode->left->color == BLACK){
			sibNode->color = RED;
			sibNode->right->color = BLACK;
			leftRotate(root, sibNode, nil);
			sibNode = markNode->parent->left;
		}

		// Case 4: Sibling's left child is red
		sibNode->color = markNode->parent->color;
		markNode->parent->color = sibNode->left->color = BLACK;
		sibNode = sibNode->parent;
		rightRotate(root, sibNode, nil);
		markNode = root;
	}
}

// Fixes the tree to maintain red-black properties after a deletion
void deletion_Fix(Ref &root, Ref &markNode, Ref nil){
	while(markNode->color != RED && markNode != root){
		// Adjust based on whether the marked node is a left or right child
		if(markNode->parent->left == markNode) deletion_leftAdjust(root, markNode, nil);
		else deletion_rightAdjust(root, markNode, nil);
	}
	markNode->color = BLACK; // Ensuring the root is black
}

void RBT_deletion(Ref &root, int key, Ref nil){
	Ref deletableNode = searchNode(root, key, nil); // Find the node to be deleted
	if(deletableNode == nil) return; // Node not found, return

	// Choose the node to be actually deleted (could be the deletable node or its successor)
	Ref delNode = (deletableNode->left == nil || deletableNode->right == nil) ? deletableNode : alternativeNode(deletableNode, nil);

	if(delNode != deletableNode){
		deletableNode->key = delNode->key; // Copy the key from the successor
	}

	// Mark the node that will replace the deleted node
	Ref markNode = (delNode->left == nil) ? delNode->right : delNode->left;
	markNode->parent = delNode->parent;	// Update the parent

	// Remove the deleted node from the tree
	if(delNode->parent == nil){
		root = markNode;	
	}
	else{
		if(delNode->parent->left == delNode){
			delNode->parent->left = markNode;
		}
		else delNode->parent->right = markNode;
	}

	// Fix the tree if the deleted node was black
	if(delNode->color == BLACK){
		deletion_Fix(root, markNode, nil);
	}

	delete delNode; // Free the memory of the deleted node
	delNode = nullptr; // Avoid dangling pointer
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("a.txt", "w", stdout);
	Ref nil = new node;
	nil->parent = nil;
	nil->color = BLACK;
	nil->left = nil->right = nullptr;

	Ref root = nil;
	int n; cin >> n;
	for(int i = 0; i < n; i++){
		int key; cin >> key;
		Ref addNode = getNode(key, nil);
		RBT_insertion(root, addNode, nil);
	}

	RBT_deletion(root, 35, nil);
	RBT_deletion(root, 50, nil);

	printTree(root, nil);
}