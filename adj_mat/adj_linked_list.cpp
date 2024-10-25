#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
	
typedef struct leader* lRef;
typedef struct trailer* tRef;
struct leader{
	string key;
	lRef next;
	tRef trail;
};

struct trailer{
	string id;
	tRef next;
};

lRef getNode(){
	lRef p = new leader;
	p->next = nullptr;
	p->trail = nullptr;
	return p;
}

lRef addList(lRef& head, lRef& tail, string key){
	lRef h = head;
	tail->key = key;
	while(h->key != key) h = h->next;
	if(h == tail){
		tail->next = getNode(); tail = tail->next;
		h->next = tail;
	}
	return h;
}

lRef findLeader(lRef head, lRef tail, string key){
	while(head != tail){
		if(head->key == key) return head;
		head = head->next;
	}
	return nullptr;
}

tRef findTrailer(lRef p, string id){
	if(p == nullptr) return nullptr;

	tRef t = p->trail;
	while(t != nullptr){
		if(t->id == id) return t;
		t = t->next;
	}

	return nullptr;
}

void printNode(lRef head, lRef tail){
	while(head != tail){
		cout << head->key << " : ";
		tRef t = head->trail;
		while(t != nullptr){
			cout << t->id << " ";
			t = t->next;
		}
		cout << endl;
		head = head->next;
	}
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	lRef head = getNode();
	lRef tail = head;
	int n; cin >> n;
	string a, b;
	for(int i = 0; i < n; i++){
		cin >> a >> b;
		lRef p = addList(head, tail, a);
		lRef q = addList(head, tail, b);

		tRef t_a = new trailer;
		tRef t_b = new trailer;
		t_a->id = b; t_a->next = p->trail; p->trail = t_a;
		t_b->id = a; t_b->next = q->trail; q->trail = t_b;
	}

	printNode(head, tail);
	lRef p = findLeader(head, tail, "A");
	if(!p) cout << "NO\n";
	else {
		tRef t = findTrailer(p, "D");
		if(!t) cout << "trailer not in leader\n";
		else cout << "trailer in leader\n";
	}
}