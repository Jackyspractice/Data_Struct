#include<iostream>
#include<string.h>

using namespace std;

int main(){
    string a = "數學系";
    string b = "資訊工程學系";
    if (strcmp("數學", "資訊工程學系") > 0) cout << "true";
    else cout << "false";
    cout << endl;
    if (a > b) cout << "true";
    else cout << "false";
}