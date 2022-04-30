#include<iostream>
#include<string>

using namespace std;

int main(){
	int size = 1;
	int *arr = new int[size];
	size = 10;
	cout << sizeof(arr)/sizeof(arr[0]);
}