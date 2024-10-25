// C++ program to illustrate
// strcpy() function in C/C++
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	// Strings Declared
	char str1[] = "Hello Geeks!";
	char str2[] = "GeeksforGeeks";

	char str3[40];
	char str4[40];

	char str5[] = "GfG";

	// String copy used
	strcpy(str2, str1);
	strcpy(str3, "Copy successful");
	strcpy(str4, str5);	

	// Strings Printed
	cout << "str1: " << str1 << "\nstr2: " << str2
		<< "\nstr3: " << str3 << "\nstr4: " << str4;

	return 0;
}
