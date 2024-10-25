#include <iostream>
using namespace std;


typedef struct leader* lRef;
typedef struct trailer* tRef;

struct leader{
	int key;
	int count;
	lRef next;
	tRef trail;
};

struct trailer{
	lRef id;
	tRef next;
};

lRef addList(lRef& head, lRef& tail, int key){
	lRef h = head; tail->key = key;
	while(h->key != key) h = h->next;
	if(h == tail){
		tail->next = new leader; tail = tail->next;
		tail->count = 0, tail->next = nullptr, tail->trail = nullptr;
	}
	return h;
}

void printList(lRef head, lRef tail){
	while(head != tail){
		cout << head->key << " ";
		head = head->next;
	}

	cout << endl;
}

lRef findTail(lRef head, lRef tail){
	if(head == tail) return nullptr;
	while(head->next != tail) head = head->next;
	return head;
}


void sortTopological(lRef& head, lRef& tail){
	// Lay ra mot danh sach lien ket chua cac phan tu co count = 0,
	// tuc la cong viec nay can uu tien giai quyet dau tien

	// con tro traversal se la con tro duyet qua cac
	// nut cua danh sach lien ket
	lRef traversal = head;
	lRef retrieve_head = tail;

	// con tro prev se la con tro tro den vi tri phia truoc
	// con tro traversal, mang y nghia theo sau
	lRef prev = nullptr;
	while(traversal != tail){
		prev = traversal, traversal = traversal->next;
		if(prev->count == 0){
			// them prev vao danh sach lien ket can trich xuat
			prev->next = retrieve_head;
			retrieve_head = prev;
		}
	}

	lRef retrieve_tail = findTail(head, tail);

	lRef q = retrieve_head;
	while(q){
		tRef q_trailer = q->trail;
		while(q_trailer){
			lRef q_parent = q_trailer->id; q_parent->count--;
			if(q_parent->count == 0){
				q_parent->next = retrieve_tail->next;
				retrieve_tail->next = q_parent;
				retrieve_tail = retrieve_tail->next;
			}
			q_trailer = q_trailer->next;
		}
		q = q->next;
	}

}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("a.txt", "w", stdout);
	lRef head = new leader;
	head->count = 0, head->next = nullptr, head->trail = nullptr;
	lRef tail = head;

	// Them phan tu vao danh sach lien ket
	int total; cin >> total;
	int x, y;
	for(int i = 0; i < total; i++){
		cin >> x >> y;
		lRef child = addList(head, tail, x);
		lRef parent = addList(head, tail, y);

		parent->count++;
		tRef t = new trailer;
		t->id = parent; t->next = child->trail; child->trail = t;
	}

	sortTopological(head, tail);	
	printList(head, tail);
}