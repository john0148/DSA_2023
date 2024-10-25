#include<iostream>
#include<string>
const int MAX = 100;
using namespace std;


struct fraction {
	int numer, denomin;
	bool operator> (const fraction& p) const {
		return numer * p.denomin > p.numer * denomin;
	}
	bool operator< (const fraction& p) const {
		return numer * p.denomin < p.numer* denomin;
	}
	bool operator== (const fraction& p) const {
		return numer * p.denomin == p.numer * denomin;
	}
};


istream& operator>>(istream& INDEV, fraction& ps) {
	INDEV >> ps.numer >> ps.denomin;
	return INDEV;
}

ostream& operator<<(ostream& OUTDEV, const fraction p) {
	if ((p.numer == 0) || (p.denomin == 1))OUTDEV << p.numer;
	else
	{
		OUTDEV << p.numer << "/" << p.denomin;
	}
	return OUTDEV;
}


template<class T>
void SWAP(T* a, T* b) {
	T tmp = *a;
	*a = *b;
	*b = tmp;
}

template<class T>
bool GREATER(T a, T b) {
	return a > b;
}

template<class T>
bool LOWER(T a, T b) {
	return a < b;
}

template<class T>
void SortArr(T* a, int n, bool (*Compare)(T x, T y)) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (!Compare(a[i], a[j])) {
				SWAP<T>(&a[i], &a[j]);
			}
		}
	}
}

template<class T>
struct Snode {
	T data;
	Snode<T>* next;
};

template<class T>
struct list {
	Snode<T>* head;
	Snode<T>* tail;
};

template<class T>
void INIT(list<T>& l) {
	l.head = nullptr;
	l.tail = nullptr;
}

template<class T>
Snode<T>* makeNode(T data, Snode<T>* next) {
	Snode<T>* p = new Snode<T>;
	p->data = data;
	p->next = next;
	return p;
}

template<class T>
void addTail(list<T>& l, T data) {
	if (!l.head) l.head = l.tail = makeNode<T>(data, nullptr);
	else l.tail = l.tail->next = makeNode<T>(data, nullptr);
}

template<class T>
void InputList(list<T>& l) {
	cout << "Moi thay nhap so luong phan tu N = ";
	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		cout << "Moi thay nhap phan tu thu " << i + 1 << " = ";
		T x;  cin >> x;
		addTail<T>(l, x);
	}
}

template<class T>
void removeHead(list<T>& l) {
	if (!l.head) return;
	struct Snode<T>* p = l.head;
	l.head = l.head->next;
	if (!l.head) l.tail = nullptr;
	delete p; p = nullptr;
}

template<class T>
void deleteList(list<T>& l) {
	while (l.head) removeHead<T>(l);
}

template<class T>
void printList(list<T> l) {
	if (!l.head) {
		cout << "Danh sach rong.\n";
		return;
	}
	for (Snode<T>* p = l.head; p; p = p->next) {
		cout << p->data;
		if (p->next)cout << " -> ";
	}
	cout << endl;
}


template<class T>
void SortList(list<T>& l, bool (*Compare)(T x, T y)) {
	for (Snode<T>* p = l.head; p && p->next; p = p->next) {
		for (Snode<T>* q = p->next; q; q = q->next) {
			if (!Compare(p->data, q->data)) {
				SWAP<T>(&p->data, &q->data);
			}
		}
	}
}

template<class T>
void printArr(T* arr, int n) {
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

template<class T>
void InputArr(T* arr, int &n) {
	cout << "Moi thay nhap so phan tu N = "; cin >> n;
	for (int i = 0; i < n; i++) {
		cout << "Moi thay nhap vao phan tu thu " << i + 1 << " = ";
		cin >> arr[i];
	}
}

template<class T>
void processing5_1() {
	T arr[MAX]; int n;
	InputArr<T>(arr, n);
	cout << "Day la day phan tu thay vua nhap.\n";
	printArr<T>(arr, n);
	cout << "Day la sap xep theo tang dan.\n";
	SortArr<T>(arr, n, &LOWER<T>);
	printArr<T>(arr, n);
	cout << "Day la sap xep theo giam dan.\n";
	SortArr<T>(arr, n, &GREATER<T>);
	printArr<T>(arr, n);
}

void deleteString(struct list<string>& l) {
	for (struct Snode<string>* p = l.head; p; p = p->next) {
		p->data.~basic_string();
	}
} 


int main() {
	cout << "Day la bai 5.1 - mo phong ham sap xep tong quat cho kieu string va phan so thong qua mang tinh.\n";
	cout << "\nKieu phan so.\n";
	cout << "De nhap mot phan so, thay hay nhap: a b tuong ung voi a/b.\n";
	processing5_1<fraction>();
	cout << "\nKieu string.\n";
	processing5_1<string>();
	cout << endl;

	cout << "Day la bai 5.2 - mo phong ham sap xep tong quat cho kieu string va phan so thong qua linked list.\n";

	cout << "\nKieu phan so.\n";
	cout << "De nhap mot phan so, thay hay nhap: a b tuong ung voi a/b.\n";
	struct list<fraction> l; INIT<fraction>(l);
	InputList<fraction>(l);
	cout << "Danh sach thay vua nhap la:\n";
	printList<fraction>(l);
	cout << "Day la sap xep theo tang dan.\n";
	SortList<fraction>(l, &LOWER<fraction>);
	printList<fraction>(l);
	cout << "Day la sap xep theo giam dan.\n";
	SortList<fraction>(l, &GREATER<fraction>);
	printList<fraction>(l);
	deleteList<fraction>(l);

	cout << "\nKieu string.\n";
	struct list<string> q; INIT<string>(q);
	InputList<string>(q);
	cout << "Danh sach thay vua nhap la:\n";
	printList<string>(q);
	cout << "Day la sap xep theo tang dan.\n";
	SortList<string>(q, &LOWER<string>);
	printList<string>(q);
	cout << "Day la sap xep theo giam dan.\n";
	SortList<string>(q, &GREATER<string>);
	printList<string>(q);
	deleteString(q);
	deleteList<string>(q);
}