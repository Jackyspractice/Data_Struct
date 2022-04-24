#include<iostream>
#include<string>

using namespace std;

int main(){
	string a = "abc	bac	cab";
	string n[3] = {"\0"};
	int k = 0;
	for(int i = 0; i < a.size(); i++){
		if(a[i] != '\t'){
			n[k] = n[k] + a[i];
		}
		else k++;
	}
	cout << n[2];
}