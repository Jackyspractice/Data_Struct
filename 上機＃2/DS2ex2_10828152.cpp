#include<iostream>

using namespace std;

class collegeType{
    public:
        string number;//serial
        string school;
        string department;
        string dayclub;
        string level;
        string sNO;//nuber of students
};collegeType collegeType;

int main(){

    while(1){
        //which
        int which = 777;
        cout << "(Stop, 23Tree, AVL) = (0, 1, 2)\n";
        cin >> which;
        if (which == 0) return 0;
        else if (which != 1 && which != 2 && which != 3){
            cout << "Enter error!!!\n";
            continue;
        }
        //read file

    }








    cin >> collegeType.sNO;
    cout << collegeType.sNO;


}