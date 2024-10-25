#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string.h>

using namespace std;


void ReplaceChar(fstream& fs, char src, char dest){
	char c;
	while(fs.get(c)){
		if(c == src){
			int pos = fs.tellg();
			pos--;
			fs.seekp(pos);
			fs.put(dest);
			fs.seekg(pos+1);
		}
	}
}


void copyFile(ifstream& inDEV, ofstream& outDEV){
	char c;
	while(inDEV.get(c)){
		outDEV<<c;
	}
}


struct fraction{
	int numer, denomin;
	double proximate(){
		return (double)numer/(double)denomin;
	}
};



ifstream& operator>>(ifstream& inDev, fraction *ps){
	inDev>>ps->numer>>ps->denomin;
	return inDev;
}

ofstream& operator<<(ofstream& outDEV, const fraction *ps){
	if(ps->denomin == 1 || ps->numer == 0)outDEV<<ps->numer;
	else outDEV<<ps->numer<<" "<<ps->denomin;
	return outDEV;
}

fraction* inputArrFraction(ifstream& inDev, int &n){
	n = 0;
	fraction *arr = (fraction*)malloc((n+1)*sizeof(fraction));
	if(arr == NULL){
		cout<<"Loi cap phat du lieu.\n";
		return NULL;
	}
	while(inDev >> (arr + n)){

		n++;
		if(inDev.eof()){
			return arr;
		}

		if(inDev.fail()){
			free(arr); arr = NULL; n = 0; return NULL;
		}

		arr = (fraction*)realloc(arr,(n+1)*sizeof(fraction));
	}
	return NULL;
}

void SortFraction(fraction* p, int n){
	for(int i = 0; i < n; i++){
		for(int j = i+1; j < n; j++){
			if((p+j) -> proximate() < (p+i) -> proximate()){
				fraction temp = *(p+i);
				*(p+i) = *(p+j);
				*(p+j) = temp;
			}
		}
	}
}

void outArrFraction(ofstream& outDEV, fraction* p, int n){
	for(int i = 0; i < n; i++){
		outDEV<<p+i<<endl;
	}
}


void CountAppearances(ifstream& inDEV, ofstream& outDEV){
	int cnt[256] = {};
	char c;
	while(inDEV.get(c)){
		cnt[int(c)]++;
	}

	for(int i = 65; i <= 122; i++){
		if(cnt[i]){
			outDEV<<char(i)<<": "<<cnt[i]<<endl;
		}
	}		
}

int main(){
	//Day la bai 1
	fstream fileBai1("bai1.txt", ios::in | ios::out);
	if(!fileBai1){ cout << "Loi mo file bai 1.\n"; return 1; }
	//Moi thay nhap ki tu cu can duoc thay the
	//bang cach sua ki tu thay the trong ma nguon o duoi.
	char src = 'A';
	char dest = 'c';
	ReplaceChar(fileBai1,src,dest);


	//Day la bai 2
	ifstream inFileBai2("bai2in.txt");
	ofstream outFileBai2("bai2out.txt");
	if(!inFileBai2 || !outFileBai2){cout<<"Loi mo file bai 2.\n"; return 1;}
	copyFile(inFileBai2,outFileBai2);

	//Day la bai 3
	ifstream inFileBai3("bai3in.txt");
	ofstream outFileBai3("bai3out.txt");
	if(!inFileBai3 || !outFileBai3){cout<<"Loi mo file bai 3.\n"; return 1;}
	int n;
	fraction *p = inputArrFraction(inFileBai3,n);
	SortFraction(p,n);
	outArrFraction(outFileBai3,p,n);

	//Day la bai 4
	ifstream inFileBai4("bai4in.txt");
	ofstream outFileBai4("bai4out.txt");
	if(!inFileBai4 || !outFileBai4){cout<<"Loi mo file bai 4.\n"; return 1;}
	CountAppearances(inFileBai4,outFileBai4);
}


	