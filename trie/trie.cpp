#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <climits>
using namespace std;

// Define the size of the alphabet used in the trie
const int ALPHABET_SIZE = 26;

// trie node
// Define the structure of a node in the trie
struct TrieNode {
	// Integer to store the node's ID
	int ID;
	// Array of pointers to next nodes in the trie
	struct TrieNode* next[ALPHABET_SIZE];
};

// Returns new trie node (initialized to NULLs)
// Function to create a new trie node
struct TrieNode* getNode()
{
	// Define the structure of a node in the trie
	struct TrieNode* pNode = new TrieNode;

	 // Initialize the node ID with the minimum integer value
	pNode->ID = INT_MIN;

	// Initialize all next pointers to nullptr
	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->next[i] = nullptr;

	return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
// Function to insert a key into the trie
void Insert(struct TrieNode* &Dic, string word, int ID)
{
	struct TrieNode* pCrawl = Dic;

	// Variable to store the index of a character
	int index;

	// Iterate over each character in the key
	for (int i = 0; i < (int)word.length(); i++) {
		// Calculate the character index (for lowercase a-z)
		index = word[i] - 'a';

		// If the character is not present, add a new node
		if (!pCrawl->next[index])
			pCrawl->next[index] = getNode();

		// Move to the next node in the trie
		pCrawl = pCrawl->next[index];
	}

	// Set the ID at the last node of the key
	pCrawl->ID = ID;
}

//create Trie tree from dictionary file
void createTrie(TrieNode* &Dic, string DicFile){
	// Open the file specified by DicFile
	ifstream inputFile(DicFile);

	// Check if the file is successfully opened
	if (!inputFile.is_open()) {
		cout << "Cannot open file!\n"; // Print error message if file cannot be opened
		return; // Exit the function if file opening fails
    }

    string word; // Variable to store a word from the file
    int ID; // Variable to store the associated ID with the word

    string line;// Variable to store each line read from the file
    // Read the file line by line
    while (getline(inputFile, line)) {
        istringstream iss(line);// Create a string stream from the line
        // Extract word and ID from the line; break loop on failure
        if (!(iss >> word >> ID)) { break; } // Error handling in case of bad input format
        Insert(Dic, word, ID); // Insert the word and its ID into the trie
    }

    inputFile.close(); // Close the file after reading all lines
}


// Function to search for a key in the trie
int lookUp(struct TrieNode* Dic, string word)
{
	struct TrieNode* pCrawl = Dic;

	// If all characters of the word have been processed
	for (int i = 0; i < (int)word.length(); i++) {
		int index = word[i] - 'a';
		// If any next node is NULL, the word does not present in trie
		if (!pCrawl->next[index])
			return -1;

		pCrawl = pCrawl->next[index];
	}

	// Returns ID if word presents in trie, else
	// Return -1
	return (pCrawl != nullptr && pCrawl->ID != INT_MIN) ? pCrawl->ID : -1;
}

// Recursive function to search for all strings that start with the current prefix in the trie
void searchStringWithPrefix(TrieNode* p, vector<string> &res, string &currentPrefix){

	// If the current node has a valid ID, add the current prefix to the result
	if(p->ID != INT_MIN){
		res.push_back(currentPrefix);
	}

	// Iterate over all possible character nodes	
	for(int i = 0; i < ALPHABET_SIZE; i++){
		// If the next character node exists
		if(p->next[i]) {
			// Add the character to the current prefix
			currentPrefix.push_back(i + 'a');
			// Recursively search for more strings starting with the new prefix
			searchStringWithPrefix(p->next[i], res, currentPrefix);
			// Remove the last character to backtrack in the trie
			currentPrefix.pop_back();
		}
	}
}

// Function to look up all strings in the trie that start with a given prefix
vector<string> lookUpPrefix(TrieNode* Dic, string prefix){
	vector<string> res = {}; // Initialize an empty vector to store the results

	struct TrieNode* pCrawl = Dic; // Start from the root of the trie

	// Navigate the trie according to the given prefix
	for (int i = 0; i < (int)prefix.length(); i++) {
		int index = prefix[i] - 'a';// Compute the index for the current character
        // If the character is not in the trie, return an empty result
		if (!pCrawl->next[index])
			return res;

		pCrawl = pCrawl->next[index]; // Move to the next node
	}

	string currentPrefix = prefix; // Initialize the current prefix
	// If the end of the prefix is reached in the trie, search for all strings starting from here
	if(pCrawl != nullptr) searchStringWithPrefix(pCrawl, res, currentPrefix);
	return res; // Return the list of strings that match the prefix
}

// Function to check if a trie node is empty
bool isEmpty(TrieNode* root)
{
	// Iterate through all possible next nodes
	for (int i = 0; i < ALPHABET_SIZE; i++)
		// If any next node is not NULL, the trie node is not empty
		if (root->next[i])
			return false;
	return true;
}

// Recursive function to delete a word from given Trie
TrieNode* Remove(TrieNode* Dic, string word, int depth)
{
	// If trie node is NULL or depth < 0, do nothing
	if (!Dic || depth < 0)
		return nullptr;

	// If all characters of the word have been processed
	if (depth == (int)word.size()) {

		// This node is no more end of word after
		// removal of given key
		if (Dic->ID != INT_MIN) Dic->ID = INT_MIN;

		// If given is not prefix of any other word
		// Check if the node can be deleted
		if (isEmpty(Dic)) {
			delete (Dic);
			Dic = nullptr;
		}

		return Dic;
	}

	// If not last character, recur for the child
	// obtained using ASCII value
	int index = word[depth] - 'a';
	Dic->next[index] = Remove(Dic->next[index], word, depth + 1);

	// If root does not have any child (its only child got 
	// deleted), and it is not end of another word.
	// Check if the node can be deleted
	if (isEmpty(Dic) && Dic->ID == INT_MIN) {
		delete (Dic);
		Dic = NULL;
	}

	return Dic;
}

void Remove(TrieNode* &Dic, string word){
	Remove(Dic, word, 0);
}

// int main()
// {
// 	// Input keys (use only 'a' through 'z'
// 	// and lower case)
// 	struct TrieNode* Dic = getNode();

// 	// Construct trie
// 	createTrie(Dic, "input.txt");

// 	Remove(Dic, "khang");

// 	vector<string> res = lookUpPrefix(Dic, "kh");
// 	for(int i = 0; i < (int)res.size(); i++) cout << res[i] << endl;
// 	return 0;
// }
