#include <iostream>

using namespace std;

struct STUDENT{
	char type;
	char name[50];
	int age;
	double average;
};


int main(){
	FILE* file = fopen("input.txt", "r");
	if(!file){
		cout << "Cannot open file!\n";
		return 1;
	}

	STUDENT students[100];
	int read = 0;
	int records = 0;
	do{
		read = fscanf(file, "%c, %49[^,], %d, %lf\n",
							&students[records].type,
							students[records].name,
							&students[records].age,
							&students[records].average);
		if(read == 4) records++;

		if(read != 4 && !feof(file)){
			cout << "File format incorrect!\n";
			return 1;
		}

		if(ferror(file)){
			cout << "Error reading file!\n";
			return 1;
		}
	}while(!feof(file));

	fclose(file);

	for(int i = 0; i < records; i++){
		printf("%c %s %d %lf\n",
							students[i].type,
							students[i].name,
							students[i].age,
							students[i].average);
	}
	return 0;
}